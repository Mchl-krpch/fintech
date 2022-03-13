/*
task: you have a number
text: you should write grey-code with len = number

 input: scale
output: grey-code strings
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void rec_gray_num  (char *gray_num, int index, int scale, int reverse) {
	assert (gray_num);
		// #3 max level of recursion
	if(index == scale) {
		printf("%s\n", gray_num);
		return;
	}
		// #4 continue recursion
	if (reverse == 0) {
		*(gray_num + index) = '0';
		rec_gray_num (gray_num, index + 1, scale, reverse);
		*(gray_num + index) = '1';
		rec_gray_num (gray_num, index + 1, scale, 1 - reverse);
	}
	else {
		*(gray_num + index)= '1';
		rec_gray_num (gray_num, index + 1, scale, 1 - reverse);
		*(gray_num + index) = '0';
		rec_gray_num (gray_num, index + 1, scale, reverse);
	}
}


int main() {
		// #1 input
	int scale = 0;
	scanf("%d", &scale);

		// #2 generate gray-code
	char *gray_num = (char *)calloc (scale, sizeof(char));
	assert (gray_num);
	rec_gray_num (gray_num, 0, scale, 0);

	free (gray_num);
}
/*
algorithm comment:
the algorithm receives the length of the code as
input and recursively receives the next digits of
the number

algo: O(N)
memo: -
*/