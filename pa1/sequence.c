#include "shell_array.h"
#include "sequence.h"
#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>


//*********************************************************************************************************************//

long *Generate_2p3q_Seq(int n, int *seq_size)
{
    //int size = 0; 
    int i = 0; //Loop contorl variable
    //long three_pow = 1;
    if(n == 0) //Chcker for n val
    {
        
        *seq_size = 0;
        return(NULL);
        
    }
    if(n == 1) //Checker for n val
    {
        
        *seq_size = 0;
        return(NULL);
    }
  
    long *seq = (long *) malloc(n * sizeof(long)); //Allocate memory for sequence
    if(seq == NULL)
    {
        
        *seq_size = 0;
        return(NULL);
    }
    //Variable def
    *seq_size = 0; //Reset
    int f = 2;
    int p = 0;
    int counter1 = 1;
    int new = 0;
    int row = 0;
    int q = 0;
    int combo = 0;
    int added = 0;
    int max_row = 0;
    while(counter1 < n)
    {
        counter1 = counter1 * 2;
        p = p + 1;
    }
    row = p;
    max_row = row;
    seq[0] = 1;
    *seq_size = *seq_size + 1;
    while(f < n)
    {
        
        //if((f % 2 == 0) || (f % 3 == 0))
        //{
            row = max_row; //Number of rows
            while(row > 0)  //Run until you reach end of rows
            {
                
                p = row - 1;
                new = f;
                q = 0;
                combo = 0;
                while(combo < row)
                {
                    
                    new = f; //Reset variable declaration
                    
                    for(i = p; i > 0; i--)
                    {
                        
                        
                        if(new % 2 != 0) //Check to make sure a value of 2
                        {
                            
                            break;
                        }
                        if((new / 2 == 1) && (new % 2 == 0)) //Check to filter overlap
                        {
                            
                       
                            seq[*seq_size] = f; //Insert in to sequence
                            *seq_size = *seq_size + 1; //Get size
                            added = 1;
                            break;
                        }
                        new = new /2;

                       
                    }
                    if(added == 1)
                    {
                        break;
                    }
                    for(i = q; i > 0; i--)
                    {
                        
                        
                        if(new % 3 != 0) //Check to make sure a value of 3
                        {
                            
                            break;
                        }
                        if((new / 3 == 1) && (new % 3 == 0)) //Check to filter out any overlap
                        {
                            
                            seq[*seq_size] = f; //Insert in to sequence
                            *seq_size = *seq_size + 1;
                            added = 1;
                            break;

                        }
                        new = new / 3;
                        
                        
                    }
                    if(added == 1)
                    {
                        break;
                    }
                    p = p - 1;
                    q = q + 1;
                  
                    if(new == 1)
                    {
                       
                        seq[*seq_size] = f; //Insert in to sequence
                        *seq_size = *seq_size + 1;
                        added = 1;
                        break;
                        
                    }
                    combo = combo + 1;
                    
                }
                if(added == 1)
                {
                    added = 0;
                    break;
                }
                row = row - 1;
            }
            
          
        
        f = f + 1;
    }
   



    return(seq);
}

//*******************************************************************************************************************************//
