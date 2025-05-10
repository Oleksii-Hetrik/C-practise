#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char passport_number[16];
    int age;
    char full_name[51];
    double baggage_weight;
} PASSENGER;

int cmp(PASSENGER *a, PASSENGER *b)
{
    if(strcmp(a->full_name, b->full_name) != 0)
    {
        return - strcmp(a->full_name, b->full_name);
    } else if(a->baggage_weight != b->baggage_weight)
    {
        return a->baggage_weight - b->baggage_weight;
    } else if(a->age != b->age)
    {
        return a->age - b->age;
    } else
    {
        return - strcmp(a->passport_number, b->passport_number);
    }
}

int main(int argc, char *argv[])
{
    char line[77];
    if (argc < 2)
    {
        printf("1st command-line argument is not present\n");
        return 3;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("file %s cannot be opened\n", argv[1]);
        return 4;
    }
    int number_of_lines = atoi(fgets(line, sizeof(line), file));
    PASSENGER passengers[number_of_lines];

    for (int i = 0; i < number_of_lines; i++)
    {
        fgets(line, sizeof(line), file);
        strcpy(passengers[i].passport_number, strtok(line, ";"));
        passengers[i].age = atoi(strtok(NULL, ";"));
        strcpy(passengers[i].full_name, strtok(NULL, ";"));
        passengers[i].baggage_weight = atof(strtok(NULL, ";"));
    }
    fclose(file);

    qsort(passengers, number_of_lines, sizeof(PASSENGER), cmp);

    if (argc < 3)
    {
        printf("2nd command-line argument is not present\n");
        return 5;
    }
    file = fopen(argv[2], "w");
    fprintf(file, "%d\n", number_of_lines);
    if(!file)
    {
        printf("file %s cannot be opened\n", argv[2]);
        return 7;
    }
    for (int i = 0; i < number_of_lines; i++)
    {
        fprintf(file, "%s;%d;%s;%.2f\n", passengers[i].passport_number, passengers[i].age, passengers[i].full_name, passengers[i].baggage_weight);
    }

    fclose(file);
    return EXIT_SUCCESS;
}