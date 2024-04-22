#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "answer2.h"

int main(int argc, char **argv)
{
   if (argc != 5)
   {
      return (EXIT_FAILURE);
   }

   FILE *fp = fopen(argv[1], "r");
   if(fp == NULL)
   {
      return(EXIT_FAILURE);
   }
   treenode *node = load_input_file(fp); //Here is where the treee is stored
   if(node == NULL)
   {
      //Do i need to include the destro_ tree function here in this call???????????????????????????????????????????????????????
      return (EXIT_FAILURE); 
   }

   //Create output fiel one
   FILE *fo = fopen(argv[2], "w");
   if(fo == NULL)
   {
      destroy_tree(node); //Frees the tree created, should be at the very end of the code
      return (EXIT_FAILURE);
   }
   save_out1_open(node, fo); //Produce output file 1
   
   //Create output file two
   FILE *fo1 = fopen(argv[3], "w");
   if(fo1 == NULL)
   {
      destroy_tree(node); //Frees the tree created, should be at the very end of the code
      return(EXIT_FAILURE);
   }
   save_out2_open(node, fo1); //Produce output file 2
   
   //Create output File two
   FILE *fo2 = fopen(argv[4], "w");
   if(fo2 == NULL)
   {
      destroy_tree(node); //Frees the tree created, should be at the very end of the code
      return(EXIT_FAILURE);
   }
   save_out3_open(node, fo2); //Producce output file 3
   
   destroy_tree(node); //Frees the tree created, should be at the very end of the code
   return EXIT_SUCCESS;
}
