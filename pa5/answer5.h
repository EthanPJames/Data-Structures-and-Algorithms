#ifndef __ANSWER5_H__
#define __ANSWER5_H__
#include <stdio.h>
#include <limits.h>


typedef struct _Adj{
    int index; //Vertex value
    struct _Adj *next; //Weight of path
    struct _Node *coor;
    int weight;
} Adj;

typedef struct _Node{
    int index;
    int predecessor;
    //struct _Node *pred;
    int hasBoard;
    Adj *pointer;
    int distance; //Need for dijkstra, acts as a weight basically
    int actd;
    int visited;
    int dd;
    int x1;
    int y1;
    int x2;
    int y2;
    int heap_i;
} Node;





typedef struct _Graph{
    int num_verticies; //Num of verticies
    int adj_mat[SHRT_MAX][SHRT_MAX]; //Adjaeency matrix
} Graph;



void source_create(Node **array, int M, int N); //Should it be **array!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void sink_create(Node **array, int M, int N, int size); //Shoudl it be **array!!!!!!!!!!!!!!!!!!!!!!!
Node **loading_input(FILE *fo, int *m, int *n);
void dijkstra(Node **list, int m, int n);
void PQ(Node **pointer, int m, int n, Node **list, int size);
Node *extract_min(Node **pointer, int *size);
void uph(Node **pointer, int index, int *size);
void save_out1(FILE *fo1, Node **list, int m, int n, int length, int *path);
int *find_path(Node **list, int end, int size, int *i);



#endif