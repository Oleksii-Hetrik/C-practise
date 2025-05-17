#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char date[31];
    char name[31];
    int participants;
    int priority;
} EVENT;

int cmp(const void *left, const void *right)
{
    EVENT *a = (EVENT *) left;
    EVENT *b = (EVENT *) right;
    if(a->priority != b->priority)
    {
        return - (a->priority - b->priority);
    }
    if(a->participants != b->participants)
    {
        return a->participants - b->participants;
    }
    if(strcmp(a->date, b->date))
    {
        return strcmp(a->date, b->date);
    }
}

int main(int argc, char *argv[])
{
    EVENT events[300];
    char line[111];

    if(argc < 2)
    {
        fprintf(stderr, "No input argument");
        return 3;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        fprintf(stderr, "input can't be oened");
        return 4;
    }
    int count = 0;
    while(fgets(line, sizeof(line), file))
    {
        if(line[0] == 'E' && line[1] == 'N' && line[2] == 'D')
        {
       //     printf("END\n");
            break;
        }
        strcpy(events[count].date, strtok(line, ";"));
        strcpy(events[count].name, strtok(NULL, ";"));
        events[count].participants = atoi(strtok(NULL, ";"));
        events[count].priority = atoi(strtok(NULL, ";"));
     /*   printf("%s;%s;%d;%d\n", 
        events[count].date,
        events[count].name,
        events[count].participants,
        events[count].priority); */
        count++;
    }
    fclose(file);
   // printf("success 1\n");
    qsort(events, count, sizeof(EVENT), cmp);
    
   // printf("success 2\n");
    if(argc < 3)
    {
        fprintf(stderr, "No output argument");
        return 5;
    }
    file = fopen(argv[2], "w");
    if(!file)
    {
        fprintf(stderr, "output can't be oened");
        return 6;
    }
    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%s;%s;%d;%d\n", 
        events[i].date,
        events[i].name,
        events[i].participants,
        events[i].priority  
        );
    }
    fprintf(file, "END\n");
    fclose(file);
  //  printf("success 3\n");
    return EXIT_SUCCESS;
}