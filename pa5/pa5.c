#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer5.h"
#include <math.h>
#include <limits.h>

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        return(EXIT_FAILURE);
    }

    //Open the input file
    FILE *fo = fopen(argv[1], "r");
    if(fo == NULL)
    {
        return(EXIT_FAILURE);
    }
    //Must now call the loading in file
    int rows;
    int columns;
    
    //Create the graph
    Node **list = loading_input(fo, &rows, &columns); //This creates the link list
    //int size = rows * (columns - 1);
    int size = (rows * (columns-1)) + (columns *(rows - 1)) + 2;
    // for(int i = 0; i < size - 1; i ++)
    // {
    //     printf("list: %d\n",list[i]->index);
    //     //printf("Board %d: (%d,%d), (%d, %d)\n", i, list[i]->x1, list[i]->y1, list[i]->x2, list[i]->y2);

    // }
    // Adj *ccurrent1 = list[10]->pointer;
    // while(ccurrent1 != NULL)
    // {
    //     printf("ADJ INDEX: %d\n", ccurrent1->index);
    //     ccurrent1 = ccurrent1->next;
    // }
    
    
    // for(int i = 1; i < 2*rows - 1; i = i + 2)
    // {
    //     printf("Last col vals: %d\n", list[i][columns - 1].distance);
    // }
    
    //Pass into dijkstra's
    dijkstra(list,rows, columns); //Should this be called here or will it be called in the save out functions
    // for(int i = 0; i < 14; i++)
    // {
    //     printf("list distances: %d\n", list[i]->dd);
    // }


    
    int length = 0;
    int *path = find_path(list, size -1, size, &length); //Finds shortest path
    // printf("LENGTH VAL: %d\n", length);

    FILE *fo1 = fopen(argv[2], "w"); //open output file one
    if(fo1 == NULL)
    {
        free(list);
        fclose(fo);
        return(EXIT_FAILURE);
    }
    save_out1(fo1, list, rows, columns, length, path); //Is this the proper call???????????????????????????????????????????????????????????????
    
   
    //Call save out func 2
    Adj *free_cur = NULL;
    //Free what needs to be freed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int e = 0; e < size; e++)
    {
        free_cur = list[e]->pointer;
        //for(int t = 0; t < columns; t++)
        //{
            while(free_cur != NULL)
            {
                Adj *temp = free_cur;
                free_cur = free_cur->next;
                free(temp);

            }
            free(list[e]);
        //}
       
    }
    FILE *fo2 = fopen(argv[3], "w"); //open output file one
    if(fo2 == NULL)
    {
        free(list);
        fclose(fo);
        fclose(fo1);
        return(EXIT_FAILURE);
    }

    free(list);
    fclose(fo);
    fclose(fo1);
    fclose(fo2);
    return(EXIT_SUCCESS);

}