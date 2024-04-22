#ifndef __ANSWER2_H__
#define __ANSWER2_H__
#include <stdio.h>

//Binary tree struct
typedef struct _treenode {
   int id;                                     //Value held within the tree node for each room assignment
   struct _treenode *left;
   struct _treenode *right;
   int x;                                     //right bottom corner x value
   int y;                                     //Left bottom corner y value
   char vh;                                   //Whether it is a v or H node
   int width;                                //Width of the box
   int height;                               //height of the box
    
} treenode;


treenode *load_input_file(FILE *filename);        //Checks to open input fle and it calls reucrsive function

treenode *loading_tree(FILE *filename);   //This is the recursive function creating the tree 

treenode *create_node(); //Allocates storage for each node

void destroy_tree(treenode *root); //Frees the tree at the very end of the code

void save_out1_open(treenode *tree, FILE *filename); //Opens the output file to save to and calls the recrusive function

void save_out1(treenode *tree, FILE *fo); //Createa a save function to printf out tree values in post order fashinon

void save_out2_open(treenode *tree, FILE *filename); //Opens the output file to save and calls recursive function

void save_out2(treenode *tree, FILE *fo); //Reucrsive function that outputs the smallest rectagnular room

void save_out3_open(treenode *tree, FILE *filename); //Function that opens the file and calls the recursive function

void save_out3(treenode *tree, FILE *fo); //This is the recursive function that outputs the results to output 3 file






#endif