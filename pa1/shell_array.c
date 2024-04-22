#include "shell_array.h"
#include "sequence.h"
#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>
//********************************************************************************************************************************************
long *Array_Load_From_File(char *filename, int *size)
{
    FILE *fp;
    fp = fopen(filename, "r");
    //Check to see if the file can be opened
    if (fp == NULL)
    {
        *size = 0;
        return(NULL);
    }
    //
    fseek(fp, 0l, SEEK_END); //Go to the end of the file

    *size = ftell(fp); //Tells us current postion file is at or basically the size of the file which is what I want
    *size = *size/ sizeof(long); //Number of integers in the array
    fseek(fp, 0L, SEEK_SET); //Sets file pointer back to the beginning of the file// What is the difference between 0L/0????????????
    //Checl to see if the file has a size of 0
    /*if (size_file == 0)
    {
        *size = 0;  //Should this be size 0 if file size = 0??????????????????????????????????
        fclose(fp);  //Clsoe file so no memory leaks
        long return_num = 123456;
        return(&return_num); //???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    }*/
    long *array = (long *)malloc(*size * sizeof(long)); // allocate memeory to store long interger into an array
    //Check to see if space can be allocated
    if(array == NULL)
    {
        *size = 0;
        fclose(fp); //Close file so no memory leaks
        return(NULL);
    }
    

    fread(array, sizeof(long), *size, fp); //Read the integers from the file into the array
    fclose(fp); //Close file so no memory leaks

    return(array);

}
//***********************************************************************************************************************************************
int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *fp;
    fp = fopen(filename, "w");
    //Check if file can be opened
    if(fp == NULL)
    {
        return(0); //No integers could be saved meaning you would return the value 0
    }
    //Check if anyhting in the array
    if(array == NULL)
    {
        fclose(fp);
        return(0); //No integers could be saved meaning you would return the value 0
    }
    //Check if size is 0
    if(size == 0)
    {
        fclose(fp);
        return(0); //No integers could be saved meaning you would return the value 0  
    }
    int save = fwrite(array, sizeof(long), size, fp); //Save array to an external file
    fclose(fp);
    return(save);
}
//********************************************************************************************************************************************
void Array_Shellsort(long *array, int size, long *n_comp) 
{
    int i = 0; //secomd loop control variables
    int j = 0; //third loop control variable
    int l = 0;
    long temp;
    
    *n_comp = 0;
    int sq_size = 0;
    long sequence_val; 
    

    long *k_val = Generate_2p3q_Seq(size, &sq_size);
   
    for(l = (sq_size - 1); (l + 1  > 0); l--) //Go through each iteration of k
    {
        sequence_val = k_val[l];
        
        for(i = sequence_val; i < size; i++) //Keep track of comparisons and create a temp variable to hold array value at current position
        {
            temp = array[i]; //Temporary storage of array value
            *n_comp = *n_comp + 1; //Increment ncomp to keep track of number of comparisons
            
            for(j = i; ((j >= sequence_val) && (array[j - sequence_val] > temp)); j = j - sequence_val) //TA helped me with this portion
            {
                array[j] = array[j - sequence_val]; //Go through essentially k value and make the sub_ array and osrt
                *n_comp = *n_comp + 1;

            }

            array[j] = temp;
        }
    }
    free(k_val);
}

//***********************************************************************************************************************************************
