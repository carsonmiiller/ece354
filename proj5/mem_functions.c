#include "mem.h"
extern BLOCK_HEADER* first_header;



// return 1 if BLOCK_HEADER* current is free
// return 0 if BLOCK_HEADER* current isn't free
int isFree(BLOCK_HEADER* current){
	if(current->size_alloc % 2)
		return 0;
	return 1;
}

// executes bitwise AND with size_alloc to keep all bits the same
// except the alloc-bit which is cleared to represent this 
// BLOCK_HEADER* current as free
void setFree(BLOCK_HEADER* current){
	current->size_alloc = current->size_alloc & 0xFFFFFFFE;
}

// executes bitwise OR with size_alloc to keep all bits the same
// except the alloc-bit which is set to 1 to represent
// BLOCK_HEADER* current as allocated
void setAllocated(BLOCK_HEADER* current){
	current->size_alloc = current->size_alloc | 0x00000001;
}

// returns the size of the current BLOCK_HEADER* by
// ANDing the size_alloc with 0xFFFFFFFE to clear the alloc-bit first
int getSize(BLOCK_HEADER* current){
	int ret = current->size_alloc & 0xFFFFFFFE;
	return ret;
}

// returns the next header following the current header
BLOCK_HEADER* getNextHeader(BLOCK_HEADER* current){
	BLOCK_HEADER* ret = (BLOCK_HEADER*)((unsigned long)current + getSize(current));
	return ret;
}

// returns the padding size of unsplit allocated block
int getTotalPadding(BLOCK_HEADER* current, int size){
	int ret = getSize(current) - 8 - size;
	return ret;
}

// returns the required padding size based upon the requested allocation size
int getPadding(int size){
	int ret = 16 - ((size + 8) % 16);
	if((size + 8) % 16 != 0){
		return ret;
	}
	return 0;
}

// return 1 if passed the last block, 0 otherwise
int isLastBlock(BLOCK_HEADER* current){
	if(current->size_alloc == 1)
		return 1;
	return 0;
}



// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
	int remainingSize = 0;
	BLOCK_HEADER* space = first_header;
	
	do{
		// break once you reach the last block
		if(isLastBlock(space))
			break;
		int spaceBlockSize = getSize(space);
		remainingSize += spaceBlockSize;
		space = (BLOCK_HEADER*)((unsigned long)space + spaceBlockSize);
	}while(1);
	
	if((remainingSize - 8) < size)
		return NULL;
		
    // find a free block that's big enough
	BLOCK_HEADER* current = first_header;
	do{
        // already allocated
        if (current->size_alloc & 1){
            int blockSize = getSize(current);
            remainingSize = remainingSize - blockSize;
            current = (BLOCK_HEADER *)((unsigned long)current + blockSize);
            continue;
        }
        // if you find the last one
        else if(isLastBlock(current)){
            return NULL;
        }
        // free block big enough
        else if (size <= getSize(current)){
            break;
        }
        int blockSize = getSize(current);
        current = (BLOCK_HEADER *)((unsigned long)current + blockSize);
    }while(1);

    // allocate the block
	int nextBlockDistance = current->size_alloc;
	
	current->payload = size;
	current->size_alloc = size + 8 + getPadding(size);
	setAllocated(current);
	int blockSize = getSize(current);
	
	if(nextBlockDistance < remainingSize)
		remainingSize = nextBlockDistance - blockSize;
	
	BLOCK_HEADER* nextBlock = (BLOCK_HEADER*)((unsigned long)current + blockSize);
	// if the next available block is the last block, return pointer to current block
	if(isLastBlock(nextBlock))
		return (void*)((unsigned long)current + 8);
	
	int nextSize = 1 + remainingSize - current->size_alloc;
	nextBlock->payload = nextSize - 8;
	nextBlock->size_alloc = nextSize;
	
	return (void*)((unsigned long)current + 8);
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    // traverse the list and check all pointers to find the correct block 
	BLOCK_HEADER* last = first_header;
	BLOCK_HEADER* current = last;
	void* userPointer;
	do{
		userPointer = (void*)((unsigned long)current + 8);
		// if you reach the end of the list without finding it return -1
		if(isLastBlock(current))
			return -1;
		// break if you find the user's pointer
		else if(userPointer == ptr)
			break;
		// move to next block
		last = current;
		current = (BLOCK_HEADER*)((unsigned long)current + getSize(current));
	}while(1);
	
    BLOCK_HEADER* next = (BLOCK_HEADER*)((unsigned long)current + getSize(current));
    // coalesce adjacent free blocks
	int size = 0;
	// if the next block is free
	if(isFree(next)){
		// if the last block is free
		if(isFree(last)){
			// combine all three
			size = last->size_alloc + current->size_alloc + next->size_alloc - 1;
			last->payload = size - 8;
			last->size_alloc = size;
		}
		else{
			// combine current and next blocks
			size = current->size_alloc + next->size_alloc - 1;
			current->payload = size - 8;
			current->size_alloc = size;
		}
	}
	// if the last block is free, but next block isn't
	else if(isFree(last)){
		// combine current and last
		size = current->size_alloc - 1;
		last->payload = last->payload + size;
		last->size_alloc = last->size_alloc + size;
	}
	// only current is free
	else{
		// don't combine
		size = getSize(current);
		current->payload = size - 8;
		current->size_alloc = size;
	}
    return 0;
}

