#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer3.h"

int main(int argc, char **argv)
{
   if (argc != 5)
   {
      return (EXIT_FAILURE);
   }

   FILE *fp = fopen(argv[1], "r");
   if(fp == NULL)
   {
      //printf("EXIT 1\n");
      return(EXIT_FAILURE);
   }
   treenode *node = load_input_file(fp);
   if(node == NULL)
   {
      //printf("EXIT 2\n");
      return (EXIT_FAILURE); 
   }
   

   //Create output fiel one
   FILE *fo = fopen(argv[2], "w");
   if(fo == NULL)
   {
      //printf("EXIT 3\n");
      destroy_tree(node); //Frees the tree created
      return (EXIT_FAILURE);
   }
   treenode *t_node = save_out1_open(node, fo); //Produce output file 1
   destroy_tree(t_node); //Frees the tree created, should be at the very end of the code


   
   //Get original tree back again from input file so I can re root it again
   FILE *fp2 = fopen(argv[1], "r");
   if(fp2 == NULL)
   {
      //printf("EXIT 4\n");
      return(EXIT_FAILURE);
   }
   fseek(fp2, 0, SEEK_SET);//Would i need to reset my file pointer if I am going to do it this way????????????????????
   treenode *node2 = load_input_file(fp2);
   if(node2 == NULL)
   {
      //printf("EXIT 5\n");
      return (EXIT_FAILURE); 
   }
   
   //Create output file two
   FILE *fo1 = fopen(argv[3], "w");
   if(fo1 == NULL)
   {
      //printf("EXIT 6\n");
      destroy_tree(node2); //Frees the tree created, should be at the very end of the code
      return(EXIT_FAILURE);
   }
   treenode *t_node2 = save_out2_open(node2, fo1); //Produce output file 2
   destroy_tree(t_node2); //Frees the tree created, should be at the very end of the code
   

   
   
   //Get original tree back again from input file so I can re root it again
   FILE *fp3 = fopen(argv[1], "r");
   if(fp3 == NULL)
   {
      //printf("EXIT 7\n");
      return(EXIT_FAILURE);
   }
   fseek(fp3, 0, SEEK_SET);//Would i need to reset my file pointer if I am going to do it this way????????????????????
   treenode *node3 = load_input_file(fp3);
   if(node3 == NULL)
   {
      //printf("EXIT 8\n");
      return (EXIT_FAILURE); 
   }
   save_out2a(node3);
   
   
   //Create output File three
   FILE *fo3 = fopen(argv[4], "w");
   //printf("Do we open the file\n");
   if(fo3 == NULL)
   {
      //printf("EXIT 9\n");
      destroy_tree(node3); //May need to edit this call
      return(EXIT_FAILURE);
   }
   //printf("Do we get to call save_out 3 open\n");
   treenode *t_node3 = save_out3_open(node3, fo3); //Producce output file 3
   destroy_tree(t_node3);
   
   
   return EXIT_SUCCESS;
}