#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    char world[31];
    int height;
    int time;
} ROLLER_COASTER;

int cmp(const void *left, const void *right)
{
    ROLLER_COASTER *a = (ROLLER_COASTER *)left;
    ROLLER_COASTER *b = (ROLLER_COASTER *)right;
    if(a->time != b->time)
    {
        return a->time - b->time;
    }
    if(a->height != b->height)
    {
        return -(a->time - b->time);
    }
    return strcmp(a->name, b->name);
    
}

int main(int argc, char *argv[])
{
    ROLLER_COASTER rol[20];
    char line[101];
    if(argc < 2)
    {
        fprintf(stderr, "No input file gven\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");

    if(!file)
    {
        fprintf(stderr, "input file can not be opened\n");
        return 2;
    }
    int count = 0;
    for(int i = 0; i < 20; i++)
    {
        
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = '\0';
        if(line[0] == 'E' && line[1] == 'N' && line[2] == 'D')
        {
            break;
        }
        
        strcpy(rol[i].name, strtok(line, ";"));
        strcpy(rol[i].world, strtok(NULL, ";"));
        rol[i].height = atoi(strtok(NULL, ";"));
        rol[i].time = atoi(strtok(NULL, ";"));
        count++;
        
        
    }
    fclose(file);
    qsort(rol, count, sizeof(ROLLER_COASTER), cmp);

    if(argc < 3)
    {
        fprintf(stderr, "No output file gven\n");
        return 3;
    }
    file = fopen(argv[2], "w");

    if(!file)
    {
        fprintf(stderr, "output file can not be opened\n");
        return 4;
    }
    for(int i= 0; i < count; i++)
    {
        fprintf(file, "%s;%s;%d;%d\n",
        rol[i].name,
        rol[i].world,
        rol[i].height,
        rol[i].time
        );
    }
    fprintf(file, "END\n");
    printf("success\n");
    return EXIT_SUCCESS;
}