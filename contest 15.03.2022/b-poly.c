/*Babichev-contest-1
  task: You have polynomial like: [a_n(x^n)] + [a_n-1(x^n-1)] + ... + [a_1(x1)] + a_0
  text: You should calculate it's remainder by  'mod' 

 input: first-line: degree, number of points, mod
        secon-line: | (degree + 1)-lines of odds {a_n, a_n-1, ... a_1, a_0}
                    |

        x-lines     | (number of points + 1)-lines of points
                    |

 output: (number of points + 1)-lines of answers 
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int solve (int degree, int mod, int *odds, int x) {
	assert (odds);

	int result = 0;
	for (int step = degree; step >= 0; --step) {
		result = (int) (((long long)result * x + odds[step]) % mod);
	}
	// printf ("res: %d\n", result)
	return result;
}

int main () {
	  //reading settings of program's work
	int degree = 0;
	int points = 0;
	int mod = 0;
	scanf ("%d %d %d", &degree, &points, &mod);

	  //reading odds
	int *odds = (int *)calloc (degree + 1, sizeof (int));
	assert (odds);
	for (int odd = degree; odd >= 0; --odd) {scanf ("%d", odds + odd);}

	  //results repos
	int *results = (int *)calloc (points, sizeof (int));
	assert (results);

	  //read new x & solve equation
	int cur_x = 0;
	for (int num_of_solution = 0; num_of_solution < points; num_of_solution++) {
		scanf ("%d", &cur_x);
		results[num_of_solution] = solve (degree, mod, odds, cur_x);
	}

	  //output
	for (int result = 0; result < points; result++) {printf ("%d\n", results[result]);}

	free (odds);
	free (results);
}
/*
algorithm comment:
- program reads current value of x and solve equation with it
- afrer that it writes answer in array of results

program use horner algorithm
algo: O(N)
memo: O(N)
*/