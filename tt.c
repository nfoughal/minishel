#include <stdio.h>
#include <string.h>

void removeChar(char *str, char c) {
    int i, j = 0;
    int len = strlen(str);
    char newStr[len+1];
    
    for (i = 0; i < len; i++) {
        if (str[i] != c) {
            newStr[j++] = str[i];
        }
    }
    
    newStr[j] = '\0';
    strcpy(str, newStr);
}

int main() {
    char str[100] = "Hello, world!";
    removeChar(str, 'o');
    printf("%s\n", str); // Output: Hell, wrld!
    return 0;
}
