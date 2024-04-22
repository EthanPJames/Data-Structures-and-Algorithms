#include "answer2.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//************************************************************************************************************************
treenode *load_input_file(FILE *filename)
{
    //Check to see if file can be opened
    // FILE *fp = fopen(filename, "r");
    // if(fp == NULL)
    // {
    //     return(NULL);
    // }
    treenode *root = loading_tree(filename);
    fclose(filename);
    return root;
    
}
//*******************************************************************************************************************
treenode *create_node()
{
    treenode *temp = (treenode *)malloc(sizeof(treenode)); //Malloc each node in recursion call
    if(temp == NULL) //Checks to see if able to malloced
    {
        return (NULL);
    }
    temp->right = NULL;
    temp->left = NULL;

    return(temp);
}

//*************************************************************************************************************
treenode *loading_tree(FILE *fp)
{
    treenode *temp = create_node();
    if(temp == NULL) //Checks to see if able to malloced
    {
        return (NULL);
    }
    

    int id, width, height;
    int num_vals_read = fscanf(fp, "%d(%d,%d)\n", &id, &width, &height); //Reads in
    if(num_vals_read == 3)
    {
        //printf("read numbers in: %d(%d,%d)\n",id, width, height);  //Delete when done
        temp->id = id;
        temp->width = width;
        temp->height= height;
        temp->vh = 0;
        return temp;
    }

    char split_dir = 0;
    num_vals_read = fscanf(fp, "%c\n", &split_dir); //Reads in the v or h
    if(num_vals_read == 1)
    {
        //printf("read character %c\n", split_dir);
        temp->vh = split_dir;
        temp->left = loading_tree(fp);
        temp->right = loading_tree(fp);
        //Might have to set with id and height to a null value
        return temp;
    }

   
    free(temp);

    return (NULL);
}
//******************************************************************************************************************
void destroy_tree(treenode *root)
{
    if(root == NULL) //Empty tree so nothing past null
    {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    
    free(root);
}
//******************************************************************************************************************
void save_out1_open(treenode *tree, FILE *filename)
{
    //Open an output file for writing to 
    // FILE *fo = fopen(filename, "w");
    // if(fo == NULL)
    // {
    //     return;
    // }
    
   save_out1(tree, filename);
   
    
   fclose(filename);
   //printf("Enter here2\n");
   return;

   
    

}
//********************************************************************************************************************
void save_out1(treenode *tree, FILE *fo)
{
    if (tree == NULL)
    {   
        return;
    }
        

    save_out1(tree->left, fo);
    save_out1(tree->right, fo);
    if((tree->vh == 'V') || tree->vh == 'H')
    {
        fprintf(fo, "%c\n", tree->vh);
    }
    else
    {
        fprintf(fo, "%d(%d,%d)\n", tree->id, tree->width, tree->height);
    }
    
    
}
//*******************************************************************************************************************************************

void save_out2_open(treenode *tree, FILE *filename)
{
    // FILE *fo = fopen(filename, "w");
    // if(fo == NULL)
    // {
    //     return;
    // }
    //Call the recursive function here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    save_out2(tree, filename);

    fclose(filename);
    return;
}
//****************************************************************************************************************
void save_out2(treenode *tree, FILE *fo)
{
    if(tree == NULL)
    {
        return;
    }
    //Recursive calls
    save_out2(tree->left, fo);
    save_out2(tree->right, fo);

    if(tree->vh == 'V') //If value is a non-leaf leaf node and hits a v
    {
        tree->width = (tree->left->width + tree->right->width);
        if(tree->left->height > tree->right->height)
        {
            tree->height = tree->left->height;
        }
        else
        {
            tree->height = tree->right->height;
        }
        fprintf(fo, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);

        
    }
    else if(tree->vh == 'H') //If value is a non-leaf node and hits an H
    {
        tree->height = tree->left->height + tree->right->height;
        if(tree->left->width > tree->right->width)
        {
            tree->width = tree->left->width;
        }
        else
        {
            tree->width = tree->right->width;
        }
        fprintf(fo, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);
    }
    else //Should print the values if its a leaf node with no kids
    {
        fprintf(fo, "%d(%d,%d)\n", tree->id, tree->width, tree->height);

    }


}
//**************************************************************************************************************
void save_out3_open(treenode *tree, FILE *filename)
{
    // FILE *fo_2 = fopen(filename, "w");
    // if(fo_2 == NULL)
    // {
    //     return;
    // }

    //Add recursive function call here
    tree->x = 0;
    tree->y = 0;
    save_out3(tree, filename);

    fclose(filename);
    return;
}
//*********************************************************************************************************************
void save_out3(treenode *tree, FILE *fo)
{
    if(tree == NULL)
    {
        return;
    }
    
   
    if(tree->vh == 'H')
    {
        tree->right->x = tree->x;
        tree->right->y = tree->y;

        tree->left->x = tree->x;
        tree->left->y = tree->y + tree->right->height;

    }
    else if(tree->vh == 'V')
    {
        tree->left->x = tree->x;
        tree->left->y = tree->y;

        tree->right->x = tree->x + tree->left->width;
        tree->right->y = tree->y;
    }
    else
    {
       fprintf(fo, "%d((%d,%d)(%d,%d))\n", tree->id, tree->width, tree->height, tree->x, tree->y); 
    }
    


    save_out3(tree->left, fo);
    save_out3(tree->right, fo);


 


}
//**************************************************************************************************************************************