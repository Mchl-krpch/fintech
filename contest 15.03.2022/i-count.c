/*
task:
text:

 input:
output:
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EOF '@'

int skip_simple_comment (const char cur_ch, const char ch) {
	char second_ch = ' ';
	while (1) {
		second_ch = (char)getchar ();
		if (second_ch != ch && second_ch != EOF) {
			if (second_ch == EOF) {break;}
		}
		if (second_ch == EOF) {break;}
		if (second_ch == ch) {break;}
	}
	if (second_ch == ch) {
		return 1;
	}
	if (second_ch == EOF) {
		return -1;
	}
	return 0;
}

int main () {
	int parentheses = 0;
	int braces = 0;
	int slashs = 0;
	int literals = 0;

	char cur_ch = ' ';
	while ((cur_ch = (char)getchar ()) != EOF ) {
		if (cur_ch == '(') {
			char second_ch = (char)getchar ();
			if (second_ch == '*') {
				while (1) {
					cur_ch = second_ch;
					second_ch = (char)getchar ();
					if (cur_ch == '*' && second_ch == ')') {break;}
					else if (second_ch == EOF) {break;}
				}
				if (cur_ch == '*' && second_ch == ')') {parentheses++;}
				if (second_ch == EOF) {cur_ch = EOF; break;}
			}
			else {cur_ch = second_ch;} 
		}
		if (cur_ch == '/') {
			char second_ch = (char)getchar ();
			if (second_ch == '/') {
				while (1) {
					cur_ch = second_ch;
					second_ch = (char)getchar ();
					if (second_ch == '\n') {break;}
					else if (second_ch == EOF) {break;}
				}
				if (second_ch == '\n') {slashs++;}
				if (second_ch == EOF) {cur_ch = EOF; break;}
			}
			else {cur_ch = second_ch;}
		}
		if (cur_ch == '{') {
			int cur_result = skip_simple_comment (cur_ch, '}');
			if (cur_result == -1) {cur_ch = EOF; break;}
			if (cur_result == 1) {braces++;}
		}
		else if(cur_ch == '\'') {
			int cur_result = skip_simple_comment (cur_ch, '\'');
			if (cur_result == -1) {cur_ch = EOF; break;}
			if (cur_result == 1) {literals++;}
		}
		else if (cur_ch == EOF) {break;}
	}
	printf ("%d %d %d %d\n", parentheses, braces, slashs, literals);
}
/*
algorithm comment:

*/