#include <stdio.h>

int main() {
    int num = 42;       // A normal integer variable
    int *ptr = &num;    // A pointer storing the address of `num`

    printf("Value of num: %d\n", num);         // Prints 42
    printf("Address of num: %p\n", &num);      // Prints the address of `num`
    printf("Value using pointer: %d\n", *ptr); // Prints 42
    printf("Pointer address: %p\n", ptr);      // Prints the same address as &num

    // Changing the value of num using the pointer
    *ptr = 100;         // Change the value stored at the address `ptr` points to
    printf("Updated value of num: %d\n", num); // Prints 100

    return 0;
}






#include <stdio.h>

int main() {
    char name[] = "Hello";
    char *ptr = name;  // Pointer to the first character of the array

    printf("First character: %c\n", *ptr);      // 'H'
    printf("Second character: %c\n", *(ptr+1)); // 'e'
    printf("Third character: %c\n", *(ptr+2));  // 'l'

    // Printing the string using the pointer
    printf("String: %s\n", ptr);  // Prints "Hello"

    // Modifying the array using the pointer
    *(ptr + 1) = 'a';  // Changes 'e' to 'a'
    printf("Modified String: %s\n", name);  // Prints "Hallo"

    return 0;
}
