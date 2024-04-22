#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer4.h"
#include <math.h>
#include <limits.h>
#include "hbt.h"




int main(int argc, char **argv)
{
    //printf("Begin\n\n");
    // if((argc != 3) || (argc != 4))
    // {
        
    //     return (EXIT_FAILURE);
    // }
    
    //Check for mode
    char b_mode = strcmp(argv[1], "-b");
    char e_mode = strcmp(argv[1], "-e");

    if(b_mode == 0) //Check to see if in b mode
    {
        int fail = -1;
        int success = 1;
        int middle = 0;
        //Check to see if input file can be opened succesfully
        FILE *fp = fopen(argv[2], "rb");
        if(fp == NULL)
        {
            fprintf(stdout, "%d\n", fail);
            return(EXIT_FAILURE);
        }
        fseek(fp, 0, SEEK_END);
        long int size_file = ftell(fp);
        fseek(fp, 0, SEEK_SET); //Back to beginning of file

        Tnode *tree_build = read_in(fp, size_file); //Builds the tree
        //printf("DO we get past the read in function\n");
        
        
        
        //FIGURE OUT IF FILE IS OF WRONG FORMAT OR MEMORY CANNOT BE STORED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        
        
        //Open an output file
        FILE *fop = fopen(argv[3], "wb"); //Do i need to do this for wb????????????????????????????????
        if(fop == NULL)
        {
            fclose(fp);
            destroy_tree(tree_build);
            return(EXIT_FAILURE);
        } 
        //printf("Do we get to the save function\n");
        save_out1(tree_build, fop);
        
        int supposed_size = sizeof(int) + sizeof(char);
        if(size_file % supposed_size != 0)
        {
            fprintf(stdout, "%d\n", middle);
            fclose(fp);
            fclose(fop);
            destroy_tree(tree_build);
            return(EXIT_FAILURE);
        }
        
        
        //IF everything is successfull
        fprintf(stdout, "%d\n", success);
        fclose(fp); //Close the input file
        fclose(fop);
        destroy_tree(tree_build); //May need in other spots
        return(EXIT_SUCCESS);
    }
    else if(e_mode == 0) //Check to see if in e mode
    {
        //printf("Enter e mode chekcker\n\n");
        int file_open_check = 0;
        int b_checker;
        int h_checker;
        //Check if input file can be opened
        FILE *fp = fopen(argv[2], "rb");
        if(fp == NULL)
        {
            //printf("Enter here1\n\n");
            file_open_check = -1;
        }
        //If can be opened but wrong format set it equal to 0????????????????????????????????????????????? How to check this 
        fseek(fp, 0, SEEK_END);
        long int nob = ftell(fp); //number of bytes
        fseek(fp, 0, SEEK_SET); //Rest file pointer back to beginning
        int supposed_size = sizeof(int) + sizeof(char);
        if(nob % supposed_size != 0)
        {
            file_open_check = 0;
        }

        file_open_check = 1;
        //printf("Enter here 2\n\n");

        Tnode *tree = load_from_file(fp); //This is where the reconstructed tree would be stored
        //printf("Enter here 3\n\n");
        //Then we would want to pass it into a function that would check if its a BST
        int bst_check = isBSTUtil(tree, HBT_MIN, HBT_MAX); //?????????????????????????????????????????????
        if(bst_check == 1)
        {
            b_checker = 1;
        }
        else
        {
            b_checker = 0;
        }
        //Then we would want to pass it into a function that would check if its a height balanced
        int balanced = isHB(tree);
        if(balanced == 1)
        {
            h_checker = 1;
        }
        else
        {
            h_checker = 0;
        }
        //printf("Enter here 4\n\n");

        if(file_open_check == -1 || file_open_check == 0)
        {
            fprintf(stdout, "%d,%d,%d\n", file_open_check, b_checker, h_checker);
            fclose(fp);
            destroy_tree(tree); //Check to see if this function is written correctly
            return(EXIT_FAILURE);
        }
        else
        {
            fprintf(stdout, "%d,%d,%d\n", file_open_check, b_checker, h_checker);
            fclose(fp);
            destroy_tree(tree); //Check to see if this function is written correctly
            return(EXIT_SUCCESS);

        }
        
        
    }
    else
    {
        return(EXIT_FAILURE);
    }

}