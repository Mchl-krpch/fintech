/*
task: you have word 'abra'
text: you have to write all subwords in this words, '' - substring

 input: word
output: lines with subwords
*/
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define START_CAPACITY 75

void make_string (long long *chars, int8_t cur_word, long long capacity, char *answer, long long cur_index) {
	assert (chars);
	assert (answer);

		// #4 check len 
	if (chars[cur_word] > capacity) {
		answer[cur_index] = '0' + cur_word;
		answer[cur_index + 1] = '\0';
		printf("%s\n", answer);

			// #5 continue recursion
		make_string (chars, cur_word, capacity + 1, answer, cur_index + 1);
	}
		// #6 new recursion
	if (cur_word < START_CAPACITY - 1) {make_string (chars, cur_word + 1, 0, answer, cur_index);}
}

int main() {
		// #1 fill array with index of chars
	long long *chars = (long long *)calloc (START_CAPACITY, sizeof (long long));
	assert (chars);

		// #2 input data
	long long amount = 0;
	int cur_ch = 0;
	while ((cur_ch = getchar ()) != '\n') {
		chars[cur_ch - '0']++;
		amount++;
	}

		// #3 algo
	char *answer = (char *)calloc (sizeof (char), sizeof (char) * (amount + 1));
	assert (answer);
	make_string  (chars, 0, 0, answer, 0);
	printf ("\n");

	free (chars);
	free (answer);
}
/*
algorithm comment:
we perform recursion, putting a symbol in place in the word,
there are still a certain number of them, then we go into
recursion in the same word, but one letter ahead.
then it recurses on the next word

algo: O(N*M)
memo: O(M)
*/