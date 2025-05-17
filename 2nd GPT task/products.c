#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    char category[31];
    double price;
    int stock;
} PRODUCT;

int cmp(const void *left, const void *right)
{
    PRODUCT *a = (PRODUCT *) left;
    PRODUCT *b = (PRODUCT *) right;
    if(a->stock != b->stock)
    {
        return a->stock - b->stock;
    }
    if(a->price != b->price)
    {
        if(a->price < b->price)
        {
            return 1;
        }
        if(a->price < b->price)
        {
            return -1;
        }
    }
    return strcmp(a->name, b->name);
}
int main(int argc, char*argv[])
{
    PRODUCT prod[300];
    char line[111];
    int count = 0;

    if(argc < 2)
    {
        fprintf(stderr, "No input argument");
        return 4;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        fprintf(stderr, "input file cannot be opened");
        return 5;
    }
    while(fgets(line, sizeof(line), file))
    {
        strcpy(prod[count].name, strtok(line, ";"));
        strcpy(prod[count].category, strtok(NULL, ";"));
        prod[count].price = atof(strtok(NULL, ";"));
        prod[count].stock = atoi(strtok(NULL, ";"));
        count++;
    }
    fclose(file);
    qsort(prod, count, sizeof(PRODUCT), cmp);
    if(argc < 3)
    {
        fprintf(stderr, "No output argument");
        return 6;
    }
    file = fopen(argv[2], "w");
    if(!file)
    {
        fprintf(stderr, "output file cannot be opened");
        return 7;
    }
    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%s;%s;%.2f;%d\n",
        prod[i].name,
        prod[i].category,
        prod[i].price,
        prod[i].stock);
    }
    
   // printf("success\n");
    return EXIT_SUCCESS;
}