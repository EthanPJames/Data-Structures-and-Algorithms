#include "answer3.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//************************************************************************************************************************
treenode *load_input_file(FILE *filename)
{
    treenode *root = loading_tree(filename);
    fclose(filename);
    return root;
}
//*******************************************************************************************************************
treenode *create_node() // Does this need to be created using post order traversal now??????????????????????????????
{
    treenode *temp = (treenode *)malloc(sizeof(treenode)); // Malloc each node in recursion call
    //treenode *temp = malloc(sizeof(*temp));
    if (temp == NULL)                                      // Checks to see if able to malloced
    {
        return (NULL);
    }
    temp->right = NULL;
    temp->left = NULL;
    temp->height = 0;
    temp->id = 0;
    temp->width = 0;

    // temp->id = 0;  //Added my take out!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    return (temp);
}

//*************************************************************************************************************
stack *push(treenode *value, stack *head)
{

    stack *new_node = (stack *)malloc(sizeof(stack));
    if (new_node == NULL)
    {
        return (NULL);
    }
    new_node->root = value;
    new_node->next = head;
    return (new_node);
}
//******************************************************************************************************************************************
treenode *pop(stack **head)
{
    if (*head == NULL)
    {
        return (NULL);
    }

    treenode *value = (*head)->root; // Shoudl it be root
    stack *temp = *head;
    *head = (*head)->next;

    free(temp);
    return (value);
}
//*****************************************************************************************************************************************
treenode *loading_tree(FILE *fp)
{
    stack *head = NULL; // Stack is intitally empty

    // printf("Enter here\n");
    int c;
    // while(!feof(fp)) //Check anohter way to iterate through the file???????????????????????????????????????????????????????????????????
    while ((c = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        // printf("Enter here 1\n");
        treenode *temp = create_node();
        if (temp == NULL) // Checks to see if able to malloced
        {
            return (NULL);
        }
        // printf("Enter here2\n");
        int id, width, height;
        int num_vals_read = fscanf(fp, "%d(%d,%d)\n", &id, &width, &height);
        if (num_vals_read == 3)
        {
            temp->id = id;
            temp->width = width;
            temp->height = height;
            temp->vh = 0;
            temp->reerooted_w = 0;
            temp->reerooted_h = 0;
            temp->alreadyRerooted = 0;

            head = push(temp, head);
        }
        else
        {
            char split_dir = 0;
            num_vals_read = fscanf(fp, "%c\n", &split_dir); // Reads in the v or h
            if (num_vals_read == 1)
            {

                temp->vh = split_dir;
                temp->reerooted_w = 0;
                temp->reerooted_h = 0;
                temp->alreadyRerooted = 0;
                temp->right = pop(&head);
                temp->left = pop(&head);

                head = push(temp, head);
            }
        }

        // printf("Enter here3\n");
    }

    // Outside while
    return (pop(&head)); // SHoudl return tree
}

//******************************************************************************************************************
void destroy_tree(treenode *root)
{
    if (root == NULL) // Empty tree so nothing past null
    {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);

    free(root);
}
//******************************************************************************************************************
treenode *save_out1_open(treenode *tree, FILE *filename)
{

    treenode *tree_rerout = reroote1(tree); // Call the rerout function to reroot the tree
    //printf("Save_out1\n");
    save_out1(tree_rerout, filename); // Calls the pritn function to post order print the reroute tree
    fclose(filename);
    // printf("Enter here2\n");
    return (tree_rerout);
}
//********************************************************************************************************************
void save_out1(treenode *tree, FILE *fo)
{
    if (tree == NULL)
    {
        return;
    }
    if ((tree->vh == 'V') || tree->vh == 'H')
    {
        fprintf(fo, "%c\n", tree->vh);
    }
    else
    {
        fprintf(fo, "%d(%d,%d)\n", tree->id, tree->width, tree->height);
    }
    save_out1(tree->left, fo);
    save_out1(tree->right, fo);
}
//**************************************************************************************************************************************************
treenode *gen_reroot(treenode *root, int case_check)
{
    treenode *new_root;
    if (case_check == 1 && root->left->vh != 0)
    {
        new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;
    }
    else if (case_check == 2 && root->left->vh != 0) // Output file 1
    {
        new_root = root->left;
        root->left = new_root->left;
        new_root->left = root;
    }
    else if (case_check == 3 && root->right->vh != 0) // Output file 1
    {
        //printf("Do we enter case 3\n\n");
        new_root = root->right;
        root->right = new_root->right;
        new_root->right = root;
    }
    else if (case_check == 4 && root->right->vh != 0)
    {
        new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;
        //root->right = new_root->left;
    }
    else
    {
        //printf("do we just enter root????\n");
        return(root);
    }
    return (new_root);
}
//****************************************************************************************************************************************
treenode *inverseReroot(treenode *root, int type)
{
    treenode *new_root;
    if (type == 1)
    {
        new_root = root->right;
        //new_root->left = 
        root->right = new_root->left;
        //root->right = new_root->left;
        new_root->left = root;
    
        //return (gen_reroot(root, 4));
        return(new_root);
    }
    else if (type == 2)
    {
        new_root = root->left;
        root->left = new_root->left;
        new_root->left = root;
        //return (gen_reroot(root, 2));
        return(new_root);
    }
    else if (type == 3)
    {
        new_root = root->right;
        root->right = new_root->right;
        new_root->right = root;
        //return (gen_reroot(root, 3));
        return(new_root);
    }
    else if (type == 4)
    {
        //printf("\n\nEnter inverse root 4\n\n");
        new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;
        //return (gen_reroot(root, 1));
        return(new_root);
    }
    else
    {
        fprintf(stderr, "Incorrect usage of inverse reroot, type=%d\n", type);
    }
    //Should enter every case correctly
}


//*******************************************************************************************************************************************
treenode *reroote1(treenode *tree)
{
    if (tree == NULL)
    {

        return (NULL);
    }
    if ((tree->left == NULL) || (tree->left->right == NULL))
    {

        return (tree);
    }
    while (1)
    {
        //printf("Do we enter this while loop for reroote 1\n");

        tree = gen_reroot(tree, 2); // Checks for case 2 reroot
        if (tree->right->left == NULL)
        {
            break;
        }
        tree = gen_reroot(tree, 3); // Checks for case 3 reroot
        if (tree->left->right == NULL)
        {
            break;
        }
    }

    return (tree);
}
//************************************************************************************************************************************
treenode *reroote2(treenode *tree)
{
    if (tree == NULL)
    {
        return (NULL);
    }
    if ((tree->right == NULL) || (tree->right->left == NULL)) // This statement may be incorrect?????????????????????????????????????
    {
        return (tree);
    }
    while (1)
    {
        //printf("Do we enter this while loop for reroote2\n");

        tree = gen_reroot(tree, 3); // Checks for case 3 reroot
        if (tree->left->right == NULL)
        {
            break;
        }
        tree = gen_reroot(tree, 2); // Checks for case 2 reroot
        if (tree->right->left == NULL)
        {
            break;
        }
    }

    return (tree);
}

//********************************************************************************************************************************************
treenode *save_out2_open(treenode *tree, FILE *filename)
{
    treenode *tree_rerout2 = reroote2(tree); // Call the rerout function to reroot the tree
    //printf("Save_out2\n");
    save_out2(tree_rerout2, filename); // Calls the pritn function to post order print the reroute tree
    fclose(filename);
    return (tree_rerout2);
}
//***********************************************************************************************************************************************
void save_out2(treenode *tree, FILE *fo)
{
    if (tree == NULL)
    {
        return;
    }
    if ((tree->vh == 'V') || tree->vh == 'H')
    {
        fprintf(fo, "%c\n", tree->vh);
    }
    else
    {
        fprintf(fo, "%d(%d,%d)\n", tree->id, tree->width, tree->height);
    }
    save_out2(tree->left, fo);
    save_out2(tree->right, fo);
}
//**********************************************************************************************************************************************
void reroote3(treenode *tree, int tracker)
{
    //printf("How many times do we reroot\n\n");
    
    if ((tree == NULL) || (tree->left == NULL) || (tree->right == NULL))
    {
        //printf("Do we enter reroote 3 null checker \n");
        return;
    }
    // printf("VH Val: %d\n\n", tree->vh);
    // printf("VH->right: %d\n\n", tree->right->vh);
    // printf("VH->left: %d\n\n", tree->left->vh);
    // printf("VH VAL: %d\n", tree->vh);
    
    // General cases
    if (tracker == 0) //If you are at the root
    {
        //printf("DO we enter tracker 0\n");
        if ((tree->left->left != NULL) || (tree->left->right != NULL))
        {
            //printf("Do we enter portion 1\n");
            
            tree->left->alreadyRerooted = 1;
            
            tree = gen_reroot(tree, 1);
            // printf("GVH Val: %d\n\n", tree->vh);
            // printf("GVH->right: %d\n\n", tree->right->vh);
            // printf("VGH->left: %d\n\n", tree->left->vh);

            //printf("Prior to calc_szie function called\n");
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            //printf("After calc_size function called\n");
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            reroote3(tree, 1); //Recursive call
            tree = inverseReroot(tree, 1);
            // printf("IVH Val: %d\n\n", tree->vh);
            // printf("IVH->right: %d\n\n", tree->right->vh);
            // printf("IGH->left: %d\n\n", tree->left->vh);

            //printf("do we enter portion 1b\n");
            
            tree = gen_reroot(tree, 2);
            // printf("Height1: %d\n", tree->left->left->height);
            // printf("Width1: %d\n", tree->left->left->width);
            // printf("Height2: %d\n", tree->left->right->height);
            // printf("Width3: %d\n", tree->left->right->width);
            //printf("Height: %d\n")
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 2);
            tree = inverseReroot(tree, 2);
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree->right);
            calc_size(tree);
            
        }
        if ((tree->right->right != NULL) || (tree->right->left != NULL)) //Modification made here
        {
            //Print out tree nodes
            // printf("Initial GVH Val: %d\n\n", tree->vh);
            // printf("Intial GVH->right: %d\n\n", tree->right->vh);
            // printf("Initial GVH->left: %d\n\n", tree->left->vh);
            // printf("Right->right %d\n", tree->right->right->vh);
            // printf("Right->Left %d\n\n", tree->right->left->vh);

            
            //printf("Do we enter portion 2\n");
            tree->right->alreadyRerooted = 1;
            //printf("do we enter protion 2a\n");
            tree = gen_reroot(tree, 4);
            // printf("GVH Val: %d\n\n", tree->vh);
            // printf("GVH->right: %d\n\n", tree->right->vh);
            // printf("GVH->left: %d\n\n", tree->left->vh);
            //  printf("Right->right %d\n", tree->left->right->vh);
            // printf("Right->Left %d\n\n", tree->left->left->vh);
            
            //printf("VH Val: %d\n\n", tree->vh);
            
            // printf("Right before calc size from portion 2\n\n");
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            // printf("After calc size in portion 2\n");
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 4);
            tree = inverseReroot(tree, 4);
            // printf("IVH Val: %d\n\n", tree->vh);
            // printf("IVH->right: %d\n\n", tree->right->vh);
            // printf("IGH->left: %d\n\n", tree->left->vh);
            // printf("do we enter portion 2b\n");

            
            // printf("Initial GVH Val: %d\n\n", tree->vh);
            // printf("Intial GVH->right: %d\n\n", tree->right->vh);
            // printf("Initial GVH->left: %d\n\n", tree->left->vh);
            // printf("Right->right %d\n", tree->right->right->vh);
            // printf("Right->Left %d\n\n", tree->right->left->vh);
            tree = gen_reroot(tree, 3);
            // printf("\n\nRight after gen_reroot 3 is called\n\n");
            // printf("GVH Val: %d\n\n", tree->vh);
            // printf("GVH->right: %d\n\n", tree->right->vh);
            // printf("GVH->left: %d\n\n", tree->left->vh);
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            // printf("Prior to reroote tracker 3 call\n\n");
            reroote3(tree, 3);
            tree = inverseReroot(tree, 3);
            // printf("IVH Val: %d\n\n", tree->vh);
            // printf("IVH->right: %d\n\n", tree->right->vh);
            // printf("IVH->left: %d\n\n", tree->left->vh);
            
            
        }


    }
    if (tracker == 1 && (tree->left->vh != 0)) //Case 1
    //(tracker == 1 && (tree->left->left != NULL) && (tree->left->right != NULL))
    {
        // printf("DO we enter tracker 1\n");
        if (!tree->left->alreadyRerooted)
        {
            // printf("Enter 1.1\n");
            tree->left->alreadyRerooted = 1;

            tree = gen_reroot(tree, 1);
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            reroote3(tree, 1);
            tree = inverseReroot(tree, 1);

            // printf("1.1 reroot prior to case 2 reroot");
            tree = gen_reroot(tree, 2);
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 2);
            tree = inverseReroot(tree, 2);
        }
    }
    if (tracker == 2 && (tree->right->vh != 0)) //Case 2
    //&& (tree->right->left != NULL) && (tree->right->right != NULL)
    {
        // printf("DO we enter tracker 2\n");
        if (!tree->right->alreadyRerooted)
        {
            // printf("Enter 2.1\n");
            tree->right->alreadyRerooted = 1;

            tree = gen_reroot(tree, 4);
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 4);
            tree = inverseReroot(tree, 4);

            tree = gen_reroot(tree, 3);
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            reroote3(tree, 3);
            tree = inverseReroot(tree, 3);
        }
    }
    if (tracker == 3 && (tree->left->vh != 0)) //Case 3
    //&& (tree->left->left != NULL) && (tree->left->right != NULL)
    {
        // printf("DO we enter tracker 3\n");
        if (!tree->left->alreadyRerooted)
        {
            // printf("Enter 3.1\n");
            tree->left->alreadyRerooted = 1;

            tree = gen_reroot(tree, 1);
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            reroote3(tree, 1);
            tree = inverseReroot(tree, 1);

            tree = gen_reroot(tree, 2);
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 2);
            tree = inverseReroot(tree, 2);
        }
    }
    if ((tracker == 4) && (tree->right->vh != 0)) //Case 4
    //&& (tree->right->right != NULL) && (tree->right->left != NULL)
    {
        // printf("DO we enter tracker 4\n");
        if (!tree->right->alreadyRerooted)
        {
            // printf("Enter 4.1\n");
            tree->right->alreadyRerooted = 1;

            tree = gen_reroot(tree, 4);
            //pre_order_print1(tree);
            calc_size(tree->left); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->right->reerooted_h = tree->height;
            tree->right->reerooted_w = tree->width;
            reroote3(tree, 4); //Changed fro, 4-2
            tree = inverseReroot(tree, 4);

            tree = gen_reroot(tree, 3);
            //pre_order_print1(tree);
            calc_size(tree->right); //Modified here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            calc_size(tree);
            tree->left->reerooted_h = tree->height;
            tree->left->reerooted_w = tree->width;
            reroote3(tree, 3);
            tree = inverseReroot(tree, 3);
        }
    }
    calc_size(tree->left);
    calc_size(tree->right);
    calc_size(tree);
    
    // printf("Do we make it to the end of the reroot3 function: %d\n\n", tracker);
    //Do I need to make this a treenode * function and return the tree so I can pass it into a print function
}
//***********************************************************************************************************************************************
treenode *save_out3_open(treenode *tree, FILE *filename)
{
    // printf("Enter the save_out3_open\n");
    tree->left->reerooted_w = 0;
    tree->left->reerooted_h = 0;
    tree->right->reerooted_h = 0;
    tree->right->reerooted_w = 0;
    
    reroote3(tree, 0);
    // printf("reeroote 3 success!!\n");
    
    pre_print(tree, filename, 0);
    // printf("pre print function success!!!\n");
    fclose(filename);
    // printf("fclose success!!\n");
    return(tree);
}
//*******************************************************************************************************************************************
void calc_size(treenode *tree)
{
    if(tree == NULL)
    {
        return;
    }
    if (tree->vh == 'V') // If value is a non-leaf leaf node and hits a v
    {
        //printf("Calc_size 1\n");
        tree->width = (tree->left->width + tree->right->width);
        if (tree->left->height > tree->right->height)
        {
            tree->height = tree->left->height;
        }
        else
        {
            tree->height = tree->right->height;
        }
        //fprintf(stderr, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);
    }
    if (tree->vh == 'H') // If value is a non-leaf node and hits an H
    {
        //printf("Calc_size 2\n");
        tree->height = tree->left->height + tree->right->height;
        if (tree->left->width > tree->right->width)
        {
            tree->width = tree->left->width;
        }
        else
        {
            tree->width = tree->right->width;
        }
        //fprintf(stderr, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);
    }
    return;
}
//****************************************************************************************************************
void pre_print(treenode *tree, FILE *fo, int height1)
{
    if(tree == NULL)
    {
        return;
    }
    if(height1 <= 1)
    {
        if(tree->vh == 0)
        {
            fprintf(fo,"%d\n", tree->id);

        }
        else
        {
            fprintf(fo,"%c\n", tree->vh);
        }
        
    }
    if(height1 > 1)
    {
        if(tree->vh == 0)
        {
           fprintf(fo, "%d(%d,%d)\n", tree->id, tree->reerooted_w, tree->reerooted_h);
        }
        else
        {
            fprintf(fo, "%c(%d,%d)\n", tree->vh, tree->reerooted_w, tree->reerooted_h);
        }

    }
    

    pre_print(tree->left, fo, height1+1);
    pre_print(tree->right, fo, height1+1);

}
//************************************************************************************************************************
void save_out2a(treenode *tree)
{
    if(tree == NULL)
    {
        return;
    }
    //Recursive calls
    save_out2a(tree->left);
    save_out2a(tree->right);

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
        //fprintf(fo, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);

        
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
        //fprintf(fo, "%c(%d,%d)\n", tree->vh, tree->width, tree->height);
    }
    else //Should print the values if its a leaf node with no kids
    {
        //fprintf(fo, "%d(%d,%d)\n", tree->id, tree->width, tree->height);

    }


}

void pre_order_print1(treenode *tree)
{
    if(tree == NULL)
    {
        return;
    }
    //printf("VH: %c\n\n", tree->vh);
    //printf("ID: %d\n\n", tree->id);


    //pre_order_print1(tree->left);
    //pre_order_print1(tree->right);
}

