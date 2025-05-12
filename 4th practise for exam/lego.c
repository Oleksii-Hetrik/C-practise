#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char code[6];
    char name[51];
    char theme[31];
    int bricks;
} LEGO_SET;

int cmp(const void *left, const void *right)
{
    LEGO_SET *a = (LEGO_SET *) left;
    LEGO_SET *b = (LEGO_SET *) right;
    if(a->bricks != b->bricks)
    {
        return -(a->bricks - b->bricks);
    }
    else if(strcmp(a->theme, b->theme) != 0)
    {
        return strcmp(a->theme, b->theme);
    }
    else if(strcmp(a->name, b->name) != 0)
    {
        return strcmp(a->name, b->name);
    }
    else
    {
        return strcmp(a->code, b->code);
    }
}

int main(int argc, char *argv[])
{
    LEGO_SET lego[20];
    char line[101];

    //input + errors
    if (argc < 2)
    {
        printf("1st command-line argument is not present\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("file %s cannot be opened\n", argv[1]);
        return 2;
    }
    int number_of_lines = 0;
    // printf("file %s opened\n", argv[1]);
    while(number_of_lines < 20)
    {
        if(fgets(line, sizeof(line), file))
        {
            if(line[0] == 'E' && line[1] == 'N' && line[2] == 'D')
            {
                // printf("END exit\n");
                break;
            }
            strcpy(lego[number_of_lines].code, strtok(line, ";"));
            strcpy(lego[number_of_lines].name, strtok(NULL, ";"));
            strcpy(lego[number_of_lines].theme, strtok(NULL, ";"));
            lego[number_of_lines].bricks = atoi(strtok(NULL, ";"));
            /*printf("%s %s %s %d\n", lego[number_of_lines].code, 
                lego[number_of_lines].name, 
                lego[number_of_lines].theme, 
                lego[number_of_lines].bricks); */
            number_of_lines++;
        }
        else
        {
            printf("file %s is not in the correct format\n", argv[1]);
            break;
        }
    }
    fclose(file);
    // qsort
    qsort(lego, number_of_lines, sizeof(LEGO_SET), cmp);
    // output + errors
    if (argc < 3)
    {
        printf("2nd command-line argument is not present\n");
        return 3;
    }
    file = fopen(argv[2], "w");
    if(!file)
    {
        printf("file %s cannot be opened\n", argv[2]);
        return 4;
    }
    // printf("file %s opened\n", argv[2]);
    for(int i = 0; i < number_of_lines; i++)
    {
        fprintf(file, "%s;%s;%s;%d", 
            lego[i].code, 
            lego[i].name, 
            lego[i].theme, 
            lego[i].bricks);
        if(i != number_of_lines - 1)
        {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    // printf("success\n");
    return EXIT_SUCCESS;
}