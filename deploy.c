#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buf[100];
    printf("Deploying updates in blog...\n");
    if (argc < 2)
    {
        printf("You must specify the commit comment!\n");
        printf("The blog was not updated\n");
        return 1;
    }
    snprintf(buf, sizeof(buf), "rm -rf ./docs/*");
    if (system(buf) == -1) {
       printf("Error: Docs folder could not be emptied\n");
    }


    snprintf(buf, sizeof(buf), "hugo --minify -d docs");
    if (system(buf) == -1) {
       printf("Error: Static data could not be generated\n");
    }

    snprintf(buf, sizeof(buf), "git add .");
    if (system(buf) == -1)
    {
       printf("Error: Git could not add data\n");
    }

    snprintf(buf, sizeof(buf), "git commit -m \"%s\"", argv[1]);
    if (system(buf) == -1) {
       printf("Error: Git could not commit\n");
    }

    snprintf(buf, sizeof(buf), "git push");
    if (system(buf) == -1) {
       printf("Error: Git could not push\n");
    }

    printf("Blog updated\n");
   return 0;
}
