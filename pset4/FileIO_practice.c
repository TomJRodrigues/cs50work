#include <stdio.h>

int main(void)
{
    // creates file hello
    FILE* file = fopen("test.txt", "w");
    if (file != NULL)
    {
        // writes "Hello, world!" to the file
        fprintf(file, "Hello, world!\n");
        
        // close!
        fclose(file);
    }
    return 0;
}
