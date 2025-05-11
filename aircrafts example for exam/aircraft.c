#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char registration_number[11];
    int capacity;
    char model[21];
    double wing_span;
} AIRCRAFT;
int cmp(const void *left, const void *right)
{
    AIRCRAFT *a = (AIRCRAFT *)left;
    AIRCRAFT *b = (AIRCRAFT *)right;
    if(a->wing_span != b->wing_span)
    {
        double diff = a->wing_span - b->wing_span;
        if(diff > 0)
            return 1;
        else if(diff < 0)
            return -1;
    } else if(strcmp(a->model, b->model) != 0)
    {
        return - strcmp(a->model, b->model);
    } else if(a->capacity != b->capacity)
    {
        return a->capacity - b->capacity;
    } else
    {
        return - strcmp(a->registration_number, b->registration_number);
    }
}
int main(int argc, char *argv[])
{
    AIRCRAFT aircrafts[240];
    char line[47];
    
    //input + errors
    if (argc < 2)
    {
        printf("1st command-line argument is not present\n");
        return 9;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("file %s cannot be opened\n", argv[1]);
        return 5;
    }

    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        strcpy(aircrafts[i].registration_number, strtok(line, ";"));
        aircrafts[i].capacity = atoi(strtok(NULL, ";"));
        strcpy(aircrafts[i].model, strtok(NULL, ";"));
        aircrafts[i].wing_span = atof(strtok(NULL, ";"));
        i++;
    }
    fclose(file);
    //qsort
    qsort(aircrafts, i, sizeof(AIRCRAFT), cmp);
    //output + errors
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
    for (int j = 0; j < i-1; j++)
    {
        fprintf(file, "%s;%d;%s;%.2f\n", 
            aircrafts[j].registration_number, 
            aircrafts[j].capacity,
            aircrafts[j].model, 
            aircrafts[j].wing_span);
    }
    // \n removal from last line
    fprintf(file, "%s;%d;%s;%.2f", 
            aircrafts[i-1].registration_number, 
            aircrafts[i-1].capacity,
            aircrafts[i-1].model, 
            aircrafts[i-1].wing_span);
    fclose(file);
    return EXIT_SUCCESS;
}