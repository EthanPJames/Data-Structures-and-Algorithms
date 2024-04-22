#include "shell_array.h"
#include "sequence.h"
#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        return (EXIT_FAILURE);
    }
    
    char a_val = strcmp(argv[1], "-a"); // If equal to 0 then they are equal strings
    char l_val = strcmp(argv[1], "-l"); // If equal to 0 ten they are equal strings
    int size_check = 0;

    if (a_val == 0) // For "-a" input array
    {
        long *array_op = Array_Load_From_File(argv[2], &size_check); // Loads long intergers to be sorted and store them in an array
        if (array_op == NULL)                                        // If the array is empty
        {
            
            return (EXIT_FAILURE);
        }
       
        long comp;
        Array_Shellsort(array_op, size_check, &comp);                 // Woudl the first paramter need to be an &percent????????????????????????????????????????
        // for(int i = 0; i < size_check; i++)  //Must comment out eventua
        // {
        //     fprintf(stderr, "S: %ld\n", array_op[i]);
        // }
       
        int save = Array_Save_To_File(argv[3], array_op, size_check); //Save to file
      
        fprintf(stdout, "%ld\n", comp);
     
        free(array_op);
    }
    else if (l_val == 0) // For "-l" input linked list
    {
       
        long comp1 = 0;
        Node *load = List_Load_From_File(argv[2]); //Creates the link list
        //  Node *current = load;
        // while(current != NULL)
        // {
        //     printf("%ld\n", current->value);
        //     current = current->next;
        // }
        // printf("\n\n");
        
  
        Node *sort = List_Shellsort(load, &comp1); //Now this should sort the link list
        //This should print sorted list 
        // current = sort;
        // while(current != NULL)
        // {
        //     printf("%ld\n", current->value);
        //     current = current->next;
        // }
        //printf("%ld\n", current->value);
       
        int save2 = List_Save_To_File(argv[3], sort); 

        fprintf(stdout, "%ld\n", comp1);
        
        

        
        Node *curr = sort;
        while(curr != NULL)
        {
            //printf("%ld\n", curr->value);

            Node *temp = curr;
            if(curr->next != NULL && curr->value > curr->next->value)
            {
                printf("Wrong order\n");
            }
            curr = curr->next;
            free(temp);
        }
           
    
    }
    else
    {
        
        return (EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}