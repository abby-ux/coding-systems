#include <stdio.h>

int collatz(int n, int x) {
    if (n == 1) {
        return x; // Base case: sequence ends at 1
    } else if (n % 2 == 0) {
        return collatz(n / 2, x + 1); // Even case: n = n / 2
    } else {
        return collatz(3 * n + 1, x + 1); // Odd case: n = 3 * n + 1
    }
}

int collatz_start(int n) {
    return collatz(n, 1); // start colatx with x = 1
}

int main(int argc, char *argv[]) {

    // Loop through numbers 1 to 99
    for (int i = 1; i < 100; i++) {
        // Compute the Collatz sequence length for the current number
        int result = collatz_start(i);
        // Print the result
        printf("collatz(%d): %d\n", i, result);
    }

    return 0;
}