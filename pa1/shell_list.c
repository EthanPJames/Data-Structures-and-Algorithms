#include "shell_array.h"
#include "sequence.h"
#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>


Node* List_Load_From_File(char* filename) 
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) 
    {
        return NULL;
    }
    fseek(fp, 0l, SEEK_END);
    long size = ftell(fp) / sizeof(long); //Get size
    fseek(fp, 0, SEEK_SET);

    Node* head = NULL;
    Node* tail = NULL;
    for (long i = 0; i < size; i++) 
    {
        Node* node = malloc(sizeof(Node));
        if (node == NULL) 
        {
            fclose(fp);
            return NULL;
        }
        node->next = NULL;

        if (fread(&(node->value), sizeof(long), 1, fp) != 1) 
        {
            free(node);
            fclose(fp);
            return NULL;
        }
        //Take out values
        //node->value = node->value % 50;

        if (head == NULL) 
        {
            head = node;
        } else 
        {
            tail->next = node;
        }
        tail = node;
    }

    fclose(fp);
    return head;
}
//******************************************************************************************************************************************
int List_Save_To_File(char *filename, Node *list)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    if(fp == NULL)
    {
        return(0); //what should my return code here be?????????????????????????????????????????????????????????
    }
    int counter = 0; // Will be a counter for number of integers written into the file

    Node *cur = list;
    while(cur != NULL)
    {
        fwrite(&(cur->value),sizeof(long),1, fp);
        counter = counter + 1;
        cur = cur->next;
    }

    fclose(fp); //Close file so no memory errors
    return(counter);
}
//**********************************************************************************************************************************************
static Node *bb1(Node *list, long *n_comp, long total)
{
    //printf("How many times do we enter here?\n");
    Node dummy;
    dummy.next = list;
    Node *prev = &dummy;
    Node *curr = prev->next;

    while(curr->next != NULL)
    {
        if(prev->next->value > curr->next->value)
        {
            Node *temp = curr->next;
            curr->next = temp->next;
            //curr->next = prev;
            temp->next = curr;
            prev->next = temp;
            prev = temp;
            //prev->next = temp;
            //prev = curr;
            curr = prev->next;
        }
        prev = curr;
        if(curr->next == NULL) //Only required for the 10000 case for some odd reason
        {
            break;
        }
        curr = curr->next;
        

        
    }
    list = dummy.next;
    
    return(list);
    
}
static Node *bubblesort(Node *list, long *n_comp, long n, long total)
{
    //printf("How many times do we enter here\n");
//     printf("\n\n");
//    printf("%ld\n", n);
    if(list == NULL || list->next == NULL)
    {
        return(list);
    }
    Node dummy;
    dummy.next = list;
    int sorted = 0;
    
    long last_exchange = total; //K value
    // for(int g = 0; g < total; g++)
    // {
    //     if(g % n == 0)
    //     {
    //         last_exchange = g;
    //     }
    // }
    Node *prev = &dummy;
    Node *curr = list;
    Node *temp = NULL;
    Node *curr_track = NULL;
    Node *prev_track = NULL;
    while(sorted != 1)
    {
        long last_element = last_exchange - 1;
        curr = list;
        prev = &dummy;
        sorted = 1;
        curr_track = curr;
        prev_track = prev;
        for(int e = 0; e < n; e++)
        {
            // printf("enter here\n");
            if(curr_track == NULL)
            {
                last_element = 0;
            }
            else
            {
                prev_track = curr_track;
                curr_track = curr_track->next;
                
            }
        }
        
        for(int i = 1; i <= last_element; i++) //Should go to last element
        {
            // printf("Curr Val: %ld\n", curr->value);
            (*n_comp)++;
            if(curr->value > curr_track->value)
            {
                temp = curr->next;
                // if(prev != NULL)
                // {
                //     prev->next = temp;
                // }
                // else
                // {
                //     list = temp;
                // }
                // curr->next = temp->next;
                // temp->next = curr;
                prev->next = curr_track;
                prev_track->next = curr;
                curr->next = curr_track->next;
                curr_track->next = temp;
                curr = prev->next;
                curr_track = prev_track->next;

                last_exchange = i; //This could be the issue
                sorted = 0;

            }
            // if(prev == NULL)
            // {
            //     prev = list;
            // }
            // else
            // {
            //     prev = prev->next;
            //     prev_track = prev_track->next;
            // }
            prev = curr; //prev->next;
            prev_track = curr_track; //prev_track->next;
            curr = curr->next; //prev->next;
            
            
            if(curr_track->next == NULL)
            {
                
                last_element = 0;
            }
            curr_track = curr_track->next;//prev_track->next;
  
        }

        last_element = last_exchange -1 ;
    }
    list = (dummy.next);
    return(list);

}


//Shellsrot ATUAL FUNCTION******************************************************************************************************
Node *List_Shellsort(Node *list, long *n_comp)
{
    long n = 0;
    Node *curr = list;
    while(curr != NULL)//Can find out from main, for a million shoot for uner 30 seconds
    {
        n = n + 1;
        curr = curr->next;
    }
    int seq_size;
    long *sequence = Generate_2p3q_Seq(n, &seq_size);
    // for(int i = 0; i < seq_size; i++)
    // {
    //     printf("%ld\n", sequence[i]);
    // }
    //printf("seq size: %d\n", seq_size);
    if(sequence == NULL)
    {
        return(NULL);
    }
    
    //list = bubblesort(list, n_comp, 1, n);
    for(int i = seq_size - 1; i >= 0; i--)
    {
        long temp_list = sequence[i]; //Startst at the last value in the sequence and sorts in descedning order
        if(temp_list == 1)
        {
            list = bb1(list, n_comp, n); //here is where I call the bubblesort
            break; 
        }
        Node *head_temp = list;
        head_temp = bubblesort(head_temp, n_comp, temp_list, n);
        list = head_temp;
    }
    free(sequence);
    return(list);
}


