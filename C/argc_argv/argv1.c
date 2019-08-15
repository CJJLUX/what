#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    apple = 1,
    pear,
    banana
} fuilts;

fuilts fts;

void func(void)
{
    char c;
    c = getc(stdin);
    if (atoi(&c) == 1)
        fts = apple;
    else 
        fts = pear;
}

int main(int argc, char **argv)
{
    int put_buf = -1;

 //   put_buf = atoi(argv[1]);
   // fts = put_buf;
    func();
    if (apple == fts) 
            printf("This is a apple\n");
    else if (pear == fts)
            printf("This is a pear\n");

    exit(0);
}

