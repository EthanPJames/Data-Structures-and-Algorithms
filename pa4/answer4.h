#ifndef __ANSWER4_H__
#define __ANSWER4_H__
#include <stdio.h>
#include "hbt.h"

Tnode *create_node(int key); //Creates space for each node of the tree
Tnode *load_from_file(FILE *fp); //Loads the values for the -e
int isBSTUtil(Tnode *node, int min, int max); //Checks to see if it is a BST
int height(Tnode *tree); //Gets the height at each node
int isHB(Tnode *tree); //Checks to see if it is height balanced
void destroy_tree(Tnode *root); //Destroys the tree
Tnode *read_in(FILE *fp, int size); //Reads in the key values and i or d for -b
int balance_update(Tnode *tree); //balances the tree


Tnode *insertion(Tnode **tree, int key); //Inserts the key values

Tnode *cw_r(Tnode *tree); //Clockwise rotation
Tnode *ccw_r(Tnode *tree); //Counter clockwise rotation
Tnode *deletion(Tnode *root, int key_val); //Deletes the key value
Tnode *deletion_balancing(Tnode *tree); //Does all the root balancing 
Tnode *delete_predecessor(Tnode *node, int key); //Deletes the immediate predecessor!!!!!!!!!!!!!!!!!!!!!
Tnode *max(Tnode *tree); //Goes left and then all the way right
void save_out1(Tnode *tree, FILE *fop); //Save to the output file

#endif