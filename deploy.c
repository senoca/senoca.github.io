#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char comment[100];

    for (int i = 1; i < argc; i++) { // Start from argv[1]
        if (strlen(comment) + strlen(argv[i]) + 2 >= sizeof(comment)) {
            printf("Error: comment size exceeded\n");
            return 1;
        }

        if (i > 1) {
            strncat(comment, " ", sizeof(comment) - strlen(comment) - 1); // Add space separator
        }

        strncat(comment, argv[i], sizeof(comment) - strlen(comment) - 1);
    }

    snprintf(buf, sizeof(buf), "git commit -m \"%s\"", comment);
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
