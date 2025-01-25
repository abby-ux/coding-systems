#include <stdio.h>
#include <string.h>

int main() {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("record.out> %s", buffer);
    }
    return 0;
}
