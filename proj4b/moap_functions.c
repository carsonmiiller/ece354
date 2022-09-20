
// for each of the following functions 
// correct the prototype
// write function body
// replace return with the correct return statement
//
// you may write as many helper functions here as you wish

int algorithm_1() {
	int x = 8000;
	int y = 63;
	x = x + y;
	int z = x;
	return z;
}

int algorithm_2(int x, int y) {
	int a = x;
	int b = y;
	if(a >= b)
		return x / y;
	else
		return 3 * x + y;
}

int algorithm_3(int x, int y) {
	int a = 0;
	for(int i = 0; i < x; i++)
		a = a + y;
	return a;
}

void algorithm_4(int x, int *y) {
	*y = x * 3;
}



