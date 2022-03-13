/*
  task: You have sequence of numbers arranged lexicographically
  text: you should caculate index of you number in this sequence

 input: N, K - number and total number quantity
output: index
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int calculate_num_position (int number, int total) {
      // #3 calculate max degree of ten which less than number
    int ten_degree = 1;
    while (ten_degree * 10 <= total) {ten_degree *= 10;}

      // save parameters before calculations
    int save_total = total;
    int save_degree = ten_degree;

      // #4 sum prefixes
    int num_place = 0;
    while (ten_degree >= 1) {
        num_place += (total - ten_degree + 1);
        ten_degree /= 10;
        total /= 10;
    }

      // return values
    total = save_total;
    ten_degree = save_degree;

      // #5 second part - we calculate quantity of numbers
      // which can be less in extra ten_degree
    if (total != ten_degree) {
        while (1) {
            ten_degree *= 10;
            if (ten_degree > number) {break;}

            total *= 10;
            if (number <= total) {
                num_place += (number - ten_degree + 1);
                break;
            }
            else {num_place += (total - ten_degree);}
        }
    }

    return num_place;
}

int main () {
      // #1 input
    int number = 0;
    int total;
    scanf ("%d %d", &number, &total);

      // #2 output & algo
    printf ("%d", calculate_num_position (number, total));
}
/*
algorithm comment:
we can sum prefixes of our number and check how many numbers
places before 'number'

algo: O( Log_10[N] )
memo: -
*/