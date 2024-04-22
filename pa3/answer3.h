#ifndef __ANSWER3_H__
#define __ANSWER3_H__
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
   int height;  
   int value;                             //height of the box
   int alreadyRerooted;
   int reerooted_w;
   int reerooted_h;
    
} treenode;

typedef struct _stack {
   struct _stack *next;
   treenode *root;

} stack;

treenode *pop(stack **head); //Returns head from linked list

stack *push(treenode *value, stack *head); //Puts item in front onto the link list

treenode *load_input_file(FILE *filename);        //Checks to open input fle and it calls reucrsive function

treenode *loading_tree(FILE *filename);   //This is the recursive function creating the tree 

treenode *create_node(); //Allocates storage for each node

treenode *gen_reroot(treenode *root, int case_check); //Cretes all the different types of reroots


void destroy_tree(treenode *root); //Frees the tree at the very end of the code

treenode *save_out1_open(treenode *tree, FILE *filename); //Opens the output file to save to and calls the recrusive function

void save_out1(treenode *tree, FILE *fo); //Createa a save function to printf out tree values in post order fashinon

treenode *reroote1(treenode *tree); //Rerrot the tree

treenode *save_out2_open(treenode *tree, FILE *filename); //Opens the output file to save and calls recursive function

void save_out2(treenode *tree, FILE *fo); //Reucrsive function that outputs the smallest rectagnular room

treenode *reroote2(treenode *tree); //Does rerooting for output file 2

void reroote3(treenode *tree, int tracker); //Will do the re rooting for output file 3

void calc_size(treenode *tree);

treenode *inverseReroot(treenode *root, int type);

void pre_print(treenode *tree, FILE *fo, int height);
void save_out2a(treenode *tree);

treenode *save_out3_open(treenode *tree, FILE *filename);

void pre_order_print1(treenode *tree);
#endif