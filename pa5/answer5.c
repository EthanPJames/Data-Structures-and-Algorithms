#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer5.h"

//First Thing that must be done is create a reading in file that stores the values in a linked list

//*********************************************************************************************************************************************
Node **loading_input(FILE *fo, int *m, int *n)
{
    
    fscanf(fo, "%d %d\n", m, n); //Read in first two values of row # and columb #
    //M and N are read in correctly
    int M = *m;
    int N = *n;
    int size = (M * (N-1)) + (N * (M - 1)) + 2;
    Node **array = (Node**)malloc(sizeof(Node*) * size); 
    //Create for VERTICAL Nodes
    sink_create(array, M, N, size);
    for(int i = 0; i < M - 1; i++)
    {
        
        for(int j = 0; j < N; j++)
        {
            
            Node *array_pos = (Node*)malloc(sizeof(Node));
            array_pos->x1 = i; //Added j
            array_pos->y1 = j;
            //printf("V(%d,%d)(%d, %d)\n", i, j, i +1, j);
            array_pos->x2 = i + 1; //Added j
            array_pos->y2 = j;

            array_pos->dd = INT_MAX;
            array_pos->predecessor = -1;
            array_pos->visited = 0;
            array[((N - 1) * M) + 1 + j + (i * N)] = array_pos; //Change for hirzintal, might have to check
            //printf("Math: %d\n", ((N - 1) * M) + 1 + j + (i * N));
            array_pos->index = ((N - 1) * M) + 1 + j + (i * N); //Graph index position , change for horizontal
            int file_val = fgetc(fo); //Dont need for hor
            if(file_val == '0')
            {
                array_pos->hasBoard = 0;
            }
            else
            {   
                array_pos->hasBoard = 1;   
            }
            if(array_pos->hasBoard == 1)
            {
                array_pos->distance = 0; //Switched it from 0??????????????????????????????????????????????????????????????????????????????
            }
            else
            {
                array_pos->distance = 1; //Switched it from 1??????????????????????????????????????????????????????????????????????????????
            }
            //Fill up the adjacency list
            if(j == 0) //In horizontal j becomes i 
            {
                //printf("INDEX VAL: %d\n", array_pos->index);
                //printf("(%d,%d)(%d,%d)\n", array_pos->x1, array_pos->y1, array_pos->x2, array_pos->y2);
                // printf("I: %d\n", i);
                // printf("J: %d\n", j);
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = j + 1 + (N - 1) * i;
                //printf("V edge: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;
               
                Adj *node2 = (Adj*)malloc(sizeof(Adj));
                node2->index = (N - 1) + j + 1 + (N-1)*i;
                //printf("V2 edge: %d\n", node2->index);
                node->next = node2;
                node2->next = NULL;
            }
            else if(j == N - 1) //In horizontal N would become M
            {
                // printf("INDEX VAL: %d\n", array_pos->index);
                // //printf("(%d,%d)(%d,%d)\n", array_pos->x1, array_pos->y1, array_pos->x2, array_pos->y2);
                // printf("I: %d\n", i);
                // printf("J: %d\n", j);
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = j + i * (N -1);
                //printf("V end: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;

                Adj *node_next = (Adj*)malloc(sizeof(Adj));
                node_next->index = j + i * (N -1) + (N - 1);
                //printf("V2 end: %d\n", node_next->index);
                node->next = node_next;
                node_next->next = NULL;

                Adj *node3 = (Adj*)malloc(sizeof(Adj));
                node3->index = (M * (N-1)) + (N *(M - 1)) + 1;
                //printf("V3 end: %d\n", node3->index);
                node_next->next = node3;
                node3->next = NULL;
            }
            else
            {
                //Added coordinate incrementers here, could be wrong
                array_pos->x1 = array_pos->x1 + j; //Added j
                array_pos->x2 = array_pos->x2 + j; //Added j
                //*********************************

                // printf("INDEX VAL: %d\n", array_pos->index);
                // //printf("(%d,%d)(%d,%d)\n", array_pos->x1, array_pos->y1, array_pos->x2, array_pos->y2);
                // printf("I: %d\n", i);
                // printf("J: %d\n", j);
                // printf("Index board: %d\n", array_pos->index);
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = (i + 1) * (N - 1) + (j); //(N - 1) * (i + j); //(i - 1) * (N - 1) + (j); //This is done for 6
                //printf("V mid: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;
                
                Adj *node_next = (Adj*)malloc(sizeof(Adj));
                node_next->index = (i + 1) * (N - 1) + (j + 1); //(N - 1) * i + j; //Should get me 1 from the 8 and 3 from the 11
                //printf("V2 mid: %d\n", node_next->index);
                node->next = node_next;
                node_next->next = NULL;

                Adj *node3 = (Adj*)malloc(sizeof(Adj));
                node3->index = i * (N - 1) + (j);//j + i * (N -1); //This should get me from 8 to 2 and 11 to 4
                //printf("V3 mid: %d\n", node3->index);
                node_next->next = node3;
                node3->next = NULL;

                Adj *node4 = (Adj*)malloc(sizeof(Adj));
                node4->index = i * (N-1) + (j + 1);//(i + 1) * (N - 1) + (j-1);  //Gets me from 8 to 3 and 11 to 5, this equation is wrong
                //printf("V4 mid: %d\n", node4->index);
                node4->next = NULL;
                node3->next = node4;
            }

        }
        int skip = fgetc(fo); //Might not need
    }
    //Create for HORIZONTAL Nodes
    for(int j = 0; j < N; j++) //Sgould be N - 1
    //for(int j = 0; j < N; j++) //These are correct for M = N
    {
        for(int i = 0; i < M-1; i++)
        //for(int i = 0; i < M-1; i++) //These are correct for M = N
        {
            //CHANGE THIS???????????????????????????????????????????????????????????????????????????????????????????
            Node *array_pos = (Node*)malloc(sizeof(Node));
            array_pos->x1 = j;
            array_pos->y1 = i;
            //printf("H(%d,%d)(%d, %d)\n", j, i, j , i+1);
            array_pos->x2 = j;
            array_pos->y2 = i + 1;
            array_pos->dd = INT_MAX;
            array_pos->predecessor = -1;
            array_pos->visited = 0;
            //array[1 + (j*(N-1)) + (i)] = array_pos; //Change for hirzintal
            array[(M - 1) * j + i + 1] = array_pos;
            // printf("I val: %d\n", i);
            // printf("j val: %d\n", j);
            //printf("Math horizonat: %d\n",1 + (j*(N-1)) + (i));
            array_pos->index = (M - 1) * j + i + 1;//1 + (j*(N-1)) + (i); //Graph index position , change for horizontal
            //char file_val = fgetc(fo); //Dont need for hor
            //array_pos->weight = 1; //The weights of the boards, set the weights to 1 for horizon
            //???????????????????????????????????????????????????????????????????????????????????????????????????????
            array_pos->distance = 1; //weight is 1
            //Fill up the adjacency list
            if(j == 0) //In horizontal j becomes i 
            {
                printf("Index board: %d\n", array_pos->index);
                printf("I: %d\n", i);
                printf("J: %d\n", j);
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = (M)*(N-1) + j * N + i + 1;
                //printf("H edge: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;
                
                Adj *node2 = (Adj*)malloc(sizeof(Adj));
                node2->index = (M)*(N-1) + j * N + i + 1 + 1;
                //printf("H2 edge: %d\n", node2->index);
                node->next = node2;
                node2->next = NULL;

            }
            //else if(j == M - 1) //In horizontal N would become M
            else if((j > 0) && (j <= M - 1))
            {
                printf("Index board: %d\n", array_pos->index);
                printf("I: %d\n", i);
                printf("J: %d\n", j);
                // printf("J: %d\n", j);
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = M * (N-1) + (j - 1) * N + i + 1;//(M-1)*N + i + j + 2;
                //printf("H end: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;

                Adj *node_next = (Adj*)malloc(sizeof(Adj));
                node_next->index = M * (N-1) + (j - 1) * N + i + 2;
                //printf("H2 end: %d\n", node_next->index);
                node->next = node_next;
                node_next->next = NULL;
            }
            else
            {
                printf("Index board: %d\n", array_pos->index);
                printf("I: %d\n", i);
                printf("J: %d\n", j);
                //Must figure these out
                
                Adj *node = (Adj*)malloc(sizeof(Adj));
                node->index = (M-1) * (N-1) + j * N + i; //(M-1)*(N) + i + j; //from 3 to 7
                //printf("H mid: %d\n", node->index);
                node->next = NULL;
                array_pos->pointer = node;
                
                Adj *node_next = (Adj*)malloc(sizeof(Adj));
                node_next->index = (M-1) * (N-1) + (j) * N + i + 1; // from 3 to 10
                //printf("H2 mid: %d\n", node_next->index);
                node->next = node_next;
                node_next->next = NULL;

                Adj *node3 = (Adj*)malloc(sizeof(Adj));
                node3->index = (M) * (N-1) + j * N + i + 1; //from 3 to 8
                //printf("H3 mid: %d\n", node3->index);
                node_next->next = node3;
                node3->next = NULL;

                Adj *node4 = (Adj*)malloc(sizeof(Adj));
                node4->index = (M) * (N-1) + (j) * N + i + 1 + 1; //from 3 to 11
                //printf("H4 mid: %d\n", node4->index);
                node3->next = node4;
                node4->next = NULL;
            }

        }
    }
   

    //Create source node at the beginning
    source_create(array, M, N);
    //Create source node at the end
    

    //printf("pointer: %d\n", array[0]->index);

    return(array);
}
//*****************************************************************************************************************
void source_create(Node **array, int M, int N) //Should it be **array
{
    Node *dummy = (Node*)malloc(sizeof(Node));
    dummy->dd = INT_MAX;
    //Do I need to add the coordinates here???????????????????????????????????????????????????????????????????????????????????????
    dummy->distance = 0;
    dummy->x1 = -1;
    dummy->y1 = -1;
    dummy->x2 = -1;
    dummy->y2 = -1;
    dummy->predecessor = -1;
    dummy->visited = 0;
    array[0] = dummy; //Or would this be dummy == array[0]
    dummy->index = 0;

    Adj *node_s1 = (Adj*)malloc(sizeof(Adj));
    node_s1->index = (N-1) * M + 0*(N) + 1;//(i * M) + (N * 2) + 1; //Is this correct
    node_s1->next = NULL;
    dummy->pointer = node_s1; 
    for(int i = 1; i < M - 1; i++) //SHould this be <=
    {
        Adj *node_s2 = (Adj*)malloc(sizeof(Adj));
        node_s2->index = (N-1) * M + i*(N) + 1;//(i * M) + (N * 2) + 1; //Is this correct
        node_s2->next = NULL;
        node_s1->next = node_s2;
        node_s1 = node_s2; 
        
    }

}
//******************************************************************************************************************
void sink_create(Node **array, int M, int N, int size)
{
    Node *dummy2 = (Node*)malloc(sizeof(Node));
    //Do I need to add the coordinates here???????????????????????????????????????????????????????????????????????????????????????
    dummy2->dd = INT_MAX;
    dummy2->distance = 1;
    dummy2->x1 = -1;
    dummy2->y1 = -1;
    dummy2->x2 = -1;
    dummy2->y2 = -1;
    dummy2->predecessor = -1;
    dummy2->visited = 0;
    array[size - 1] = dummy2; //Is this correct?????????????????????????????????????????????????????????????????????????????
    dummy2->index = size - 1; //Should this be 0 or infinity

    Adj *sink = (Adj*)malloc(sizeof(Adj));
    sink->index = (N-1) * M + 0*(N) + N;
    sink->next = NULL;
    dummy2->pointer = sink;
    for(int i = 1; i < M -1; i++)
    {
        Adj *sink2 = (Adj*)malloc(sizeof(Adj));
        sink2->index = (N-1) * M + i*(N) + N;
        sink2->next = NULL;
        sink->next = sink2;
        sink = sink2;
    }

}
// //*******************************************************************************************************************
void dijkstra(Node **list, int m, int n)
{   
    int size = (m * (n-1)) + (n *(m - 1)) + 2; //
    //printf("Heap size: %d\n", size);
    Node **pointer = (Node**)malloc(sizeof(Node*)*size); //Data for Priority que
    for(int i = 0; i < size; i++) //Initializes each element in priority que
    {
        //printf("Do we enter\n");
        //printf("Pointer I value: %d\n", pointer[i]->index);
        pointer[i] = list[i];
        pointer[i]->dd = INT_MAX;
        //printf("Pointer i: %d\n", pointer[i]->index);
    }
    pointer[0]->dd = 0;
    PQ(pointer, m, n, list, size); //Upward heapify
    // for(int i = 0; i < size; i ++)
    // {
    //     printf("PQ: (%d, %d) ", pointer[i]->x1, pointer[i]->y1);
    //     printf("PQ dist: %d ", pointer[i]->dd);
    //     printf("PQ I: %d ", i);
    //     printf("PQ index: %d\n", pointer[i]->index);
    // }
    //size = 1;
    while(size != 0)
    {
        //printf("\nHow many times Extract MIn\n");
        Node *u = extract_min(pointer, &size);
        //printf("COmment: %d\n", u->index);
        // for(int i = 0; i < size; i ++)
        // {
        //     printf("PQ: (%d, %d) ", pointer[i]->x1, pointer[i]->y1);
        //     printf("PQ dist: %d ", pointer[i]->dd);
        //     printf("PQ I: %d ", i);
        //     printf("PQ index: %d\n", pointer[i]->index);
        // }
        u->visited = 1; //Visited the node
        Adj *cur = u->pointer;
        while(cur != NULL)
        {
            // printf("\nu->Index: %d\n", u->index);
            // printf("cur->index: %d\n", cur->index);
            // //printf("list[cur->index]->visited: %d\n", list[cur->index]->visited);
            // printf("list[cur->index]->dd: %d\n", list[cur->index]->dd);
            // //printf("u->dd + list[cur->index]->distance: %d\n", u->dd + list[cur->index]->distance);
            // printf("u->dd: %d\n", u->dd);
            // printf("u->distance: %d\n", u->distance);
            //printf("list[cur->index]->distance: %d\n", list[cur->index]->distance);

            if(((list[cur->index]->visited == 0)) && (list[cur->index]->dd > (u->dd + u->distance)))
            {
                list[cur->index]->dd = (u->dd + list[cur->index]->distance); //Finding the distance
                
                list[cur->index]->predecessor = u->index;
                // printf("list[cur->index]->predecessor: %d\n", list[cur->index]->predecessor);
                // printf("list[cur->index]->distance IF STATEMENT: %d\n", list[cur->index]->distance);
                uph(pointer, list[cur->index]->heap_i, &size);

            }
            cur = cur->next; //Iteartion variable
            //printf("%d\n", size);
            
            
        }
        
        
    }
    free(pointer);

    //Put values into the PQ function

}
//******************************************************************************************************************************************
void uph(Node **pointer, int index, int *size)
{
        Node *new = pointer[index]; 
        int child = index;
        int parent = (child -1) / 2;
        while((child > 0) && (pointer[parent]->dd > new->dd))
        {
            //printf("child: %d\n", child);
            pointer[child] = pointer[parent];
            pointer[child]->heap_i = child;
            //printf("child: %d\n", child);
            child = parent;

            parent = (child - 1) / 2;
            
        }
        pointer[child] = new;
        pointer[child]->heap_i = child;
        //(*size)+=1;

}
//**********************************************************************************************************************
//Include upward heapify code, inlcude min heap code, incluse PQ code, include save function codes
void PQ(Node **pointer, int m, int n, Node **list, int size) //Might not need to call
{
    int size_count = size;
    for(int i = 0; i < size; i++)
    {
        Node *new = pointer[i]; 
        int child = i;
        int parent = (child -1) / 2;
        while((child > 0) && (pointer[parent]->dd > new->dd))
        {
            pointer[child] = pointer[parent];
            pointer[child]->heap_i = child;
            child = parent;
            parent = (child - 1) / 2;
            
        }
        pointer[child] = new;
        pointer[child]->heap_i = child;

        
    }

    //No return values
}//********************************************************************************************************************************************
Node *extract_min(Node **pointer, int *size)
{
    Node *temp = pointer[0];
    pointer[0] = pointer[(*size)- 1];
    //pointer[(*size)-1] = temp;

    //Begin downward heapify
    int i = 0;
    int j = (2 * i) + 1; 
    Node *temp1 = pointer[i];
    while(j <= (*size)-1) 
    {
        if((j < (*size)-1) && (pointer[j]->dd > pointer[j+1]->dd))
        {
            j = j + 1;
        }
        if(temp1->dd <= pointer[j]->dd)
        {
            break;
        }
        else
        {
            pointer[i] = pointer[j];
            i = j;
            j = 2*i + 1; //Update the loop
        }
    }
    pointer[i] = temp1;
    *size = *size - 1;
    return(temp);

}
//********************************************************************************************************************************************
int *find_path(Node **list, int end, int size, int *i)
{
    *i = 0;
    //printf("END: %d\n", end);
    int *array = (int*)malloc(sizeof(int)*size);
    Node *path_node = list[end];
    array[0] = list[end]->index;
    *i = *i + 1;
    //printf("PATH NODE->PREDECESSOR: %d\n", path_node->predecessor);
    while(path_node->predecessor != -1)
    {
        //printf(" PRED %d\n", path_node->predecessor);
        array[*i] = path_node->predecessor;
        *i = *i + 1;
        path_node = list[path_node->predecessor];
        
    }
    return(array);
}
//****************************************************************************************************************************************
void save_out1(FILE *fo1, Node **list, int m, int n, int length, int *path) //May need to change m and n 
{
    Node *board = list[path[length-2]];
    fprintf(fo1,"(%d,%d)(%d,%d)\n", list[path[length-2]]->x1,list[path[length-2]]->y1-1,list[path[length-2]]->x1,list[path[length-2]]->y1);

    for(int i = length - 2; i > 0; i--)
    {

        //fprintf(fo1,"INDEX VALUES: %d\n ", path[i]);
        fprintf(fo1,"(%d,%d)(%d,%d)\n", list[path[i]]->x1,list[path[i]]->y1,list[path[i]]->x2,list[path[i]]->y2);
    }
    board = list[path[1]];
    fprintf(fo1,"(%d,%d)(%d,%d)\n", list[path[1]]->x1,list[path[1]]->y1,list[path[1]]->x1,list[path[1]]->y1+1);

    free(path);


}

//MUST STILL CREATE FREE FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// void save_out2()
// {

// }


