# Math Library Functions Program
The purpose of this code is to implement many of the functions that we usually use from the math.h library and get a feel for how they might actually work. The ones in this program are arcSin(x), arcCos(x), arcTan(x), and log(x). Although there is a difference between what the math.h library and this programs implementation, the approximation is close.

## Build

        $ Typing "make" will build it.
        $ Typing "format" will format it.
        $ Typing "clean" will remove the binaries

## Running

        $ ./mathlib-test along with any of the command line options will run the program.
        $ ./mathlib-test -a will run the tests for all functions which include arcSin, arcCos, arcTan, and log.
        $ ./mathlib-test -s will run the tests for the arcSin funtion and will display the input, the implemented function's output, the math library's output, and the difference between the two.
        $ ./mathlib-test -c will run the tests for the arcCos funtion and will display the input, the implemented function's output, the math library's output, and the difference between the two.
        $ ./mathlib-test -t will run the tests for the arcTan funtion and will display the input, the implemented function's output, the math library's output, and the difference between the two.
        $ ./mathlib-test -l will run the tests for the log funtion and will display the input, the implemented function's output, the math library's output, and the difference between the two.
