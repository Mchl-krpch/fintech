/*
task: the input is the text of the program, which may contain comments
text: you need to remove all comments and output the program without them

 input: input text of a program
output: text of the program without user-commments
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void delete_comments ();
void delete_comments () {
	int switch_mode = 0;

		// #2 start reading
	int ch = getc (stdin);
	while(ch != EOF) {
			// #3 check program-comments chars
		if (ch == '\'') {
			if (switch_mode == -1)       {switch_mode =  0;}
			else if (switch_mode == 0)   {switch_mode = -1;}
		}

		else if (ch == '\"') {
			if (switch_mode == -2)       {switch_mode =  0;}
			else if (switch_mode == 0)   {switch_mode = -2;}
		}

			// #4 check user-comments chars
		else if (ch == '/' && switch_mode == 0) {
			int next_ch = getc (stdin);

			if (next_ch == '/') {
				switch_mode = 1;
				ch = next_ch;
			}

			else if (next_ch == '*') {
				switch_mode = 2;
				ch = next_ch;
			}

			else {
				printf ("%c", ch);
				ch = next_ch;
				continue;
			}
		}

			// #5 check special close symbol
		else if (switch_mode == 2 && ch == '*') {
			ch = getc (stdin);
			if (ch == '/') {
				switch_mode = 0;
				ch = ' ';
			}
		}

		if (switch_mode == 1 && ch == '\n') {switch_mode = 0;}
		else if (ch == EOF && switch_mode == 1) {
			printf ("%c", ch);
			break;
		}
		if (switch_mode == 0 || switch_mode == -1 || switch_mode == -2) {printf ("%c", ch);}
		
		ch = getc(stdin);
	}
}

int main() {
		// #1 start delete
	delete_comments ();
}
/*
algorithm comment:
read the file by character and implement the logic
of opening / closing comments (+ if the user displays,
for example, messages in quotes - we do not consider
characters in program comments as user ones - this is
part of the program output).

algo: O(N)
memo: -
*/