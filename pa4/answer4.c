#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer4.h"
#include "hbt.h"

//-e functions
//*********************************************************************************************************
Tnode *create_node(int key)
{
    Tnode *temp = (Tnode *)malloc(sizeof(Tnode)); //Malloc each node in recursion call
    if(temp == NULL) //Checks to see if able to malloced
    {
        return (NULL);
    }
    temp->right = NULL;
    temp->left = NULL;
    temp->key = key;
    temp->balance = 0;

    return(temp);
}
//*********************************************************************************************************
Tnode *load_from_file(FILE *fp) //I want to pass in the already opened file here, this is function i call from main that loads in the tree
{
    
    int key_val;
    char branch;

    fread(&key_val, sizeof(int), 1, fp);
    fread(&branch, sizeof(char), 1, fp); //Should the char be 1??????????????????????????????????????????????????????????????????

    Tnode *tree = create_node(key_val);
    tree->key = key_val;
    tree->balance = 0; //Added
    
    if ((branch & 3) == 3) //Checks to see if equal to 3 or 0011
    { // left and right child exist
        tree->left = load_from_file(fp);
        tree->right = load_from_file(fp);
    } else if (branch & 1) //As long as its not zero essential 0001
    { //only right child exist
        tree->right = load_from_file(fp);
    } else if (branch & 2) //Checkng for 0010
    { // only left child exist
        tree->left = load_from_file(fp);
    } else 
    { // no child exist
        tree->left = NULL;
        tree->right = NULL;
    }
        
    return(tree); //Returns the tree
}

//********************************************************************************************************
int isBSTUtil(Tnode *node, int min, int max) //Checks to see if its A BST
{
    if (node == NULL) 
    {     
        return 1;
    }
    //Checks to see if the key value specified is less than valyes guven speicified, called recursively
    if (node->key < min || node->key > max) {
        // printf("Key Val: %ld\n", node->key);
        // printf("Min val: %ld\n", min);
        // printf("Max val: %ld\n", max);
        return 0;
    }
    return isBSTUtil(node->left, min, node->key) && isBSTUtil(node->right, node->key, max); //Took off a 1 and 2
}
//**********************************************************************************************************
int height(Tnode *tree) //Get the height of the tree
{
    int hz = 0; //If height is zero
    if(tree == NULL)
    {
        return(hz);
    }
    int lefth = height(tree->left); ///Gets height of left subtree
    int righth = height(tree->right); //Gets hieght of right subtree
    if(lefth > righth)
    {
        return(1 + lefth);
    }
    else
    {
        return(1 + righth);
    }
}
//**********************************************************************************************************
int isHB(Tnode *tree)
{
    int lefth; //Height of left subtree
    int righth; //Height of right subtree
    int bal = 1; //If it is balanced
    int not_bal = 0; //If it is inot balanced

    if(tree == NULL)
    {
        return (bal);
    }
    lefth = height(tree->left); //Height of left subtreee
    righth = height(tree->right); //Height of right subtree
    int height = lefth = righth;

    if (abs(height) <= 1 && isHB(tree->left) && isHB(tree->right)) //if current node and all its subtrees are height balanced
    {
        return(bal);
    }

    return(not_bal); //If it gets here it means the tree is not height balanced
}
//**********************************************************************************************************************************************
void destroy_tree(Tnode *root)
{
    if(root == NULL) //Empty tree so nothing past null
    {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    
    free(root);
}
//***********************************************************************************************************************************************
//Must have a destroy tree function after

//-b functions
//****************************************************************************************************************************************
Tnode *read_in(FILE *fp, int size)
{
    int key_val = 0;
    char i_d;
    Tnode *tree = NULL; //Would is need to malloc this or create the node
    Tnode *temp = NULL;

    while(ftell(fp) != size) //While it is not at the end of the function
    {
        fread(&key_val, sizeof(int), 1, fp);//Reads in the key
        fread(&i_d, sizeof(char), 1, fp); //reads in the insert or deltion character, shoudl the char be 1???????????????????????????
        
        //printf("ID value: %c\n", i_d);
        
        if(i_d == 'i')
        {
            //printf("Should hit this 10 times\n\n");
            temp = insertion(&tree, key_val); //Tree is not of the right type???????????????????????????????????????????????????????????????????
            //printf("Read in KEY VAL Insert: %d\n", key_val);
        }
        else
        {
            
            temp = deletion(tree, key_val); //Call the deletion function
            //printf("Read in KEY Value Deletion: %d\n", key_val);
        }
        
    }
    //printf("Read in KEY VAL: %dd\n", key_val);
    //printf("Are we able to return the tree\n");
    return(tree);

}
//******************************************************************************************************************************************
int balance_update(Tnode *tree) //Is this a correct balance update
{
    int lh = 0;
    int rh = 0;
    if(tree->left)
    {
        lh = height(tree->left); //Update balance for left subtre
    }
    if(tree->right)
    {
        rh = height(tree->right); //Update balance for right subtree
    }
    tree->balance = lh - rh; //Final total balance updated
    return(tree->balance);
}   
//********************************************************************************************************************************************

//*********************************************************************************************************************************************
Tnode *cw_r(Tnode *tree)
{
    //From class notes
    Tnode *new_root = tree->left; 
    tree->left = new_root->right;
    new_root->right = tree;
    // balance_update(tree);
    // balance_update(new_root);
    return(new_root);

}
//********************************************************************************************************************************************
Tnode *ccw_r(Tnode *tree)
{
    //From class notes
    Tnode *new_root = tree->right;
    tree->right = new_root->left;
    new_root->left = tree;
    // balance_update(tree);
    // balance_update(new_root);
    return(new_root);

}
//**********************************************************************************************************************************************
Tnode *deletion(Tnode *root, int key_val)
{
    if(root == NULL)
    {
        return(NULL);
    }
    if(key_val < root->key) //If the key to be deleted is smaller than its on the left, ITOOK OUT THE EQUAL TO
    {
        root->left = deletion(root->left, key_val);
    }
    else if(key_val > root->key) //IF the key to be deleted is bigger than its on the right
    {
        root->right = deletion(root->right, key_val);
    }
    else //If the keys are the same than this is what you must delete
    {
        //printf("Do we ever enter this else statment checking for child node\n");
        //For one child
        if(root->left == NULL)
        {
            //printf("Enter root->left\n");
            Tnode *temp = root->right;
            free(root);
            return(temp);
        }
        if(root->right == NULL)
        {
            //printf("Enter root->right\n");
            Tnode *temp = root->left;
            free(root);
            return(temp);
        }
        //Otherwise it will have two children
        Tnode *temp = max(root->left);
        root->key = temp->key;
       // printf("\nROOT->KEY == %d\n", root->key);
        //root->left = deletion(root->left, temp->key);
        root->left = delete_predecessor(root->left, temp->key);
        //root = delete_predecessor(root, key_val);
    }
    //Now we shoudl update the balance here
    root->balance = balance_update(root);
    
    //How do i decide whihc rotations to do here????????????????????????????
    //Do i need a while loop to iterate through the neitre tree??????????????????????????????????????????????????????????????????????
    //How do I know if i am going through and rebalancing the entire tree correctly
    root = deletion_balancing(root); //Do the rotations where its needed

    //Would I want to include a balnce updatea here???????????????????????

    //Possibel need to redo the balance here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    root->balance = balance_update(root);

    return(root);

}
//***************************************************************************************************************
Tnode *delete_predecessor(Tnode *node, int key)
{
    //Tnode *parent; //Predecessor node
    Tnode *temp;
    if(node->right != NULL)
    {
        node->right = delete_predecessor(node->right, key);
    }
    else
    {
        temp = node->left;
        free(node);
        return(temp);
        
    }
    node->balance = balance_update(node);
    node = deletion_balancing(node);
    node->balance = balance_update(node);
    return(node);
    
   

}
//*******************************************************************************************************************
Tnode *deletion_balancing(Tnode *tree)
{
    //printf("\n\nEnter rotation\n\n");
    if(tree == NULL)
    {
        //printf("Tree is null\n");
        return(NULL);
    }
    if(tree->balance < 2 && tree->balance > -2)
    {
        //printf("Tree is balanced\n");
        return(tree);
    }
    Tnode *child = NULL;
    if(tree->balance == 2)
    {
        child = tree->left;
    }
    else if(tree->balance == -2)
    {
        child = tree->right;
    }
    //Check for the proper rotations
    if(tree->balance == 2 && child->balance == -1) //Polarity change
    {
        //printf("Case 1\n");
        tree->left = ccw_r(child); //Is this correct child balance comes first
        tree = cw_r(tree); //Is this correct
        
    }
    if(tree->balance == 2 && child->balance == 0)
    {
        //printf("Case 2\n");
        tree = cw_r(tree); //Clockwise rotation

    }
    if(tree->balance == 2 && child->balance == 1)
    {
        //printf("Case 3\n");
        tree = cw_r(tree); //Clockwise rotation

    }
    if(tree->balance == -2 && child->balance == -1)
    {
        //printf("Case 4\n");
       tree = ccw_r(tree);
    }
    if(tree->balance == -2 && child->balance == 0)
    {
        //printf("Case 5\n");
        tree= ccw_r(tree);
    }
    if(tree->balance == -2 && child->balance == 1) //Polarity change
    {
        //printf("Case 6\n");
        // child = cw_r(child);
        // tree = ccw_r(tree);

        tree->right = cw_r(child);
        tree = ccw_r(tree);
    }
    return(tree); //Would I return tree value????????????????????????????????????????????????????????????????????????????????

    //Would I want to do a balance update within the nodes??????????????


}
//*************************************************************************************************************************************
Tnode *max(Tnode *tree) //Finds the max so I know what to remove 
{
    if(tree == NULL)
    {
        return(NULL);
    }
    while(tree->right != NULL) //Go all the way right
    {
        tree = tree->right;
    }
    return(tree);
}
//**************************************************************************************************************************************
void save_out1(Tnode *tree, FILE *fop) //Pre order traversal
{
    if(tree == NULL)
    {
        return;
    }
    
    int key_val = tree->key;
    char bit_val = 0;
    
    //printf("KEY VAL: %d\n", key_val);
    if(tree->right != NULL) //Has a right child
    {
        bit_val += 1; //Set but 0 to 1 if right child
    }
    if(tree->left != NULL) //Has a left child
    {
        bit_val += 2; //Set bit 1 to 1 if left child
    }
    //printf("Printing KEY VAL Save Function : %d\n", key_val);
    //printf("Print Number: %d\n", bit_val);
    fwrite(&key_val, sizeof(key_val), 1, fop); //Fwrite the int to the file in binary
    fwrite(&bit_val, sizeof(bit_val), 1, fop);
    
    save_out1(tree->left, fop);
    save_out1(tree->right, fop);
    
    

}
//***********************************************************************************************************************************
Tnode *insertion(Tnode **tree, int key)// This is the key value
{
    //*******************************************KOH'S CODE***************************************************************
    //Copy the insertion function
    //Delete line 4
    //In the fourth to last line add an equal sign
    Tnode *ya = *tree; //Youngest ancestor
    Tnode *curr = *tree;
    Tnode *pya = NULL; //Parent of youngest ancestor
    Tnode *pcurr = NULL;
    Tnode *q = NULL;
    Tnode *child = NULL;
    
    while(curr != NULL)
    {
        if(key <= curr->key) //Shoudl this be "<="?????????????????
        {
            q = curr->left;
        }
        else
        {
            q = curr->right;
        }
        if((q != NULL) && (q->balance != 0))
        {
            pya = curr;
            ya = q;
        }
        pcurr = curr;
        curr = q;
    }
    q = create_node(key); //Should this be key;
    q->balance = 0;
    if(pcurr == NULL)
    {
        
        *tree = q;
    }
    else //This else may entail more of the code??????????????????????????????????????????????????????????
    {
        if(key <= pcurr->key)
        {
            pcurr->left = q;
        }
        else
        {
            pcurr->right = q;
        }
        //This is where
        //Updat the balance from youngest ancestor to parent of the new node
        curr = ya;
        while(curr != q)
        {
            if(key <= curr->key)
            {
                curr->balance += 1;
                curr = curr->left;
            }
            else
            {
                curr->balance -= 1;
                curr = curr->right;
            }
        }
        //Check if balancing required
        //Balance of ya = -1,0,1 no balancing needed
        if((ya->balance < 2) && (ya->balance > -2))
        {
            //printf("Do we enter here\n");
            return q;
        }
        //Find child into which q is inserted
        if(key <= ya->key)
        {
            child = ya->left;
        }
        else
        {
            child = ya->right;
        }
        //Take care of balancing
        if((ya->balance == 2) && (child->balance == 1))
        {
            curr = cw_r(ya); //The clockwise rotation takes care of balancing is that requried
            ya->balance = 0;
            child ->balance = 0;
        }
        if((ya->balance == -2) && (child->balance == -1))
        {
            curr = ccw_r(ya);
            ya->balance = 0;
            child->balance = 0;
        }
        if((ya->balance == 2) && (child->balance == -1))
        {
            ya->left = ccw_r(child);
            curr = cw_r(ya);
            if(curr->balance == 0)
            {
                ya->balance = 0;
                child->balance = 0;
            }
            else{
                if(curr->balance == 1)
                {
                    ya->balance = -1;
                    child->balance = 0;
                }
                else
                {
                    ya->balance = 0;
                    child->balance = 1;
                    
                }
                curr->balance = 0; //Is this in the right postion or should it be in the else?????????????
            }
        }
        if((ya->balance == -2) && (child->balance == 1))
        {
            ya->right = cw_r(child);
            curr = ccw_r(ya);
            if(curr->balance == 0)
            {
                ya->balance = 0;
                child->balance = 0;
            }
            else{ 
                if(curr->balance == -1)
                {
                    ya->balance = 1;
                    child->balance = 0;
                }
                else 
                {
                    ya->balance = 0;
                    child->balance = -1;

                }
                curr->balance = 0;
            }
        }
        if(pya == NULL)
        {
            
            *tree = curr;
        }
        else if(key <= pya->key)
        {
            pya->left = curr;
        }
        else
        {
            
            pya->right = curr;
        }
    }
    //printf("Q val: %d", q->key);
    return q;

}
//*********************************************************************************************************************************************************
