#include <stdio.h>
#include <string.h>

#define max 126  

int main() {
    char user_name[max];

    printf("Enter your name: ");
    fgets(user_name, sizeof(user_name), stdin);

    size_t len = strlen(user_name);
    if(len > 0 && user_name[len-1] == '\n') {
        user_name[len-1] = '\0';
    }

    printf("Hello, %s!\n", user_name);

    return 0;
}
