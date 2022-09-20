	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function
Find_Max:
// prologue - write code for the prologue here
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
	movq %rdi, %r12		# %r12 : stores n from %rdi
	movq %rax, %r13		# %r13 : stores address of first element of a from %rsi

// printf("The length of the array is %d\n", n);
// update this code if necessary to print the length of the array
// this block prints the value of register %edi
// initially the parameter n
	movl	%edi, %eax #puts 1st argument of function into return value register
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

// reserve space for local variables
/* make a table here the variables from 
 * your c code and the addresses used in assembly 
 * n - address of n    
 * a - address of a
 * i - address of i
 * 
*/ 


// this code calls Print_One_Number to 
// print the number found in register %eax - use this code to debug 
// replace $999 with a register or memory address you wish to print
    movl    %eax, %eax
	movl	%eax, %edi
	call	Print_One_Number@PLT

// write your code to find the index of the maximum value here
	movl %r12d, %edi		# %rdi : stores n from %r12
	movq %r13, %rsi			# %rsi : stores address of first element of a from %r13
	xorq %r8, %r8			# %r8 : stores 0 for inital max_index
	movl $1, %r14d			# %r14 : stores 1 for initial i local variable
	movl (%r13), %r9d		# %r9 : stores value of first element in a
	movl (%rsi), %r15d		# %r15 : stores greatest value found in a
	
LOOP:
	cmpl %r14d, %edi					# compare registers holding i and n
	jle RETURN 						# BRANCH statement - @1 if i >= n
	movl (%rsi, %r14, 4), %r10d		# %r10 : stores next value in array
	cmpl %r10d, %r9d 				# compare a[i] and a[max_index]
	jl CONDITIONAL 					# BRANCH statement - @2 if a[max_index] < a[i]
	
INC:
	incq %r14			# %r14 : increment i after every iteration
	jmp LOOP
	
CONDITIONAL:
	movl %r14d, %r8d 		# %r8 : stores max_index from register holding i
	movl %r10d, %r9d 	# %r13 : stores a[max_index] from register holding a[i]
	jmp INC
	
RETURN:
	movl %r8d, %eax #1 : END

// prepare the return value
// the template returns -1, you will need to update this
//	movl	$-1, %eax

// epilogue - complete the epilogue below
	leave
	ret
.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
