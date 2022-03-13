/*             example (3 2 4) below ->  2   4
  task: we have sequences 0)a  1)baa  2)c|baa|baa  3)dcbaabaacbaabaa ...
        'level' - it is 'index)' in upper line   ~~^
        and index 'from'[= for example 4] and 'to'[= for example 10]
  text: we should print in sequence with index 'level' piece from 'from'-index to 'to'-index  

 input: 3 2 4
output: 'baa' - you can chec it in first line of this comment
*/
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void drow_section (int from, int to, int cur_ch, char *section, int seq_level, int offset) {
	if (seq_level == -1) {return;}
	assert (section);

	  // chars for sequence
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

	  // drow only one sym in this iteration
	if (cur_ch >= from && cur_ch <= to) {section[cur_ch - from] = alphabet[seq_level];}

	  // repeat drowing 2 times
	drow_section (from, to, cur_ch + 1,      section, seq_level - 1, offset / 2);
	drow_section (from, to, cur_ch + offset, section, seq_level - 1, offset / 2);

	return;
}

int main () {
	  //input
	int seq_level = 0;
	int from = 0;
	int to = 0;
	scanf ("%d %d %d", &seq_level, &from, &to);

	  // calculate offset for string iteration
	int offset = 1;
	for (int time = 0; time < seq_level - 1; time++) {offset *= 2;}

	  // create seqtion
	  // creating sequence
	char *section  = (char *)calloc (to - from + 2, sizeof (char));
	assert (section);
	int cur_ch = 0;
	drow_section (from - 1, to - 1, cur_ch, section, seq_level - 1, offset);
	printf ("%s\n", section);

	free (section);
}
/*
algorithm comment:
the program does a recursive descent, comparing
the current index in the string with a power
of two

algo: O(N)
algo: O(N)
*/