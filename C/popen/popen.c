#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    FILE *fp = NULL;
    char buf[128] = {0};
    char *find = NULL;

    fp =  popen("ls -l","r");
    if (!fp) {
        perror("popen()"); 
        goto error;
    }
    while (memset(buf, 0, sizeof(buf)) && fgets(buf, sizeof(buf), fp)) { 
        find = strchr(buf, '\n');
        if (find) {
            *find = '\0';
        }
        puts(buf);
        printf("---------\n");
    }
    pclose(fp);

    exit(0);
error:
    exit(1);
}

