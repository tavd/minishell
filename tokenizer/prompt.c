#include <stdio.h>
#include <readline/history.h>

int main() {
    char *line;

    while ((line = readline("Enter a line: ")) != NULL) {
        printf("You entered: %s\n", line);
        add_history(line);
        free(line);
    }

    return 0;
}
