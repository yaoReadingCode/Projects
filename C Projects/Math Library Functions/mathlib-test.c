#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

int main(int argc, char **argv) {
    int opt = 0;
    bool do_asin = false; // initalizing bool variables to false
    bool do_acos = false;
    bool do_atan = false;
    bool do_log = false;
    while (
        (opt = getopt(argc, argv, OPTIONS))
        != -1) { // each character in OPTIONS has a value. You input a character from the options while loop keeps going.
        switch (opt) {
        case 'a': // sets all tests to true
            do_asin = true;
            do_acos = true;
            do_atan = true;
            do_log = true;
            break;
        case 's': // sets arc-sin test to true
            do_asin = true;
            break;
        case 'c': // sets arc-cos test to true
            do_acos = true;
            break;
        case 't': // sets arc-tan test to true
            do_atan = true;
            break;
        case 'l': // sets log test to true
            do_log = true;
            break;
        default: // anything else retruns an error
            fprintf(stderr, " ");
            printf("Program usage: ./mathlib-test -[asctl]\n");
            printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
            printf("  -s   Runs arcsin tests\n");
            printf("  -c   Runs arccos tests\n");
            printf("  -t   Runs arctan tests\n");
            printf("  -l   Runs log tests\n");
        }
    }
    if (do_asin == true) { // if test was set true
        printf("  x            arcSin           Library        Difference\n"); // header
        printf("  -            ------           -------        ----------\n");
        double difference = 1.0; // initalizes difference
        for (double x = -1.0; x <= 1.0; x += 0.1) {
            if (x
                >= 0.7) { // uses a different trig identity when closer to -1 and 1 because taylor series is based around 0
                difference
                    = (((M_PI / 2) - arcSin(sqrt(1.0 - pow(x, 2)))) - asin(x)); // trig identity
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x,
                    ((M_PI / 2) - arcSin((sqrt(1.0 - pow(x, 2))))), asin(x), difference);
            } else if (x <= -0.7) { // same as above comment
                difference = (-((M_PI / 2) - arcSin(sqrt(1.0 - pow(x, 2)))) - asin(x));
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x,
                    -((M_PI / 2) - arcSin((sqrt(1.0 - pow(x, 2))))), asin(x), difference);
            } else { // when near 0, normal taylor series expansion works better
                difference = (arcSin(x) - asin(x));
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcSin(x), asin(x), difference);
            }
            // printf("sin x is %.20lf\n", Sin(x));
        }
    }
    if (do_acos == true) {
        printf("  x            arcCos           Library        Difference\n"); // header
        printf("  -            ------           -------        ----------\n");
        double difference = 1.0;
        for (double x = -1.0; x < 1.0; x += 0.1) {
            if (x
                >= 0.7) { // when near -1 and 1, trig identity calculation is used because Taylor series expansion is based around 0
                difference = (((M_PI / 2) - arcCos(sqrt(1.0 - pow(x, 2)))) - acos(x));
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x,
                    ((M_PI / 2) - arcCos((sqrt(1.0 - pow(x, 2))))), acos(x), difference);
            } else if (x <= -0.7) { // same as above comment
                difference = (((M_PI / 2) + arcCos(sqrt(1.0 - pow(x, 2)))) - acos(x));
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x,
                    ((M_PI / 2) + arcCos((sqrt(1.0 - pow(x, 2))))), acos(x), difference);
            } else { // normal taylor series expansion because it works better around 0
                difference = (arcCos(x) - acos(x));
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcCos(x), acos(x), difference);
            }
        }
    }
    if (do_atan == true) { // uses inverse method to calculate tan
        printf("  x            arcTan           Library        Difference\n"); // header
        printf("  -            ------           -------        ----------\n");
        for (double x = 1.0; x < 10.0; x += 0.1) {
            double difference = (arcTan(x) - atan(x));
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcTan(x), atan(x), difference);
        }
    }
    if (do_log == true) { // normal log calculation using exp function provided by teacher
        printf("  x            Log              Library        Difference\n"); // header
        printf("  -            ---              -------        ----------\n");
        for (double x = 1.0; x < 10.0; x += 0.1) {
            double difference = (Log(x) - log(x));
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Log(x), log(x), difference);
        }
    }
}
