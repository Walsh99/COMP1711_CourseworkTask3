#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here
//create an array of type FITNESS_DATA to store the records
FITNESS_DATA listoffitnessdata[500]; //given up to 500 records

//create temp variables to then move into the typedef array
char tempdate[11]; //using typedef
char temptime[6]; //using typedef
char tempsteps[4]; //should not pass 9999 steps

int linecount = 0; //to count number of lines/records in the csv  

// Function to tokenize a record
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) 
    {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) 
    {  
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() 
{
    //Open file
    char *filename = "FitnessData_2023.csv";
    FILE *inputfile = fopen(filename, "r"); //to read
    if (inputfile == NULL)
    {
        perror("");
        return 1;
    }
    int buffer_size = 500; //allow up to 500 lines
    char line_buffer[buffer_size];

    while (fgets(line_buffer, buffer_size, inputfile) != NULL) //loop through the csv record by record
    {
        tokeniseRecord(line_buffer, ",", tempdate, temptime, tempsteps); //use the tokeniseRecord to 
        //copy all the temporary data from the cycle to the array of fitness_data
        strcpy(listoffitnessdata[linecount].date ,tempdate);
        strcpy(listoffitnessdata[linecount].time, temptime);
        listoffitnessdata[linecount].steps = atoi(tempsteps); //had to use atoi to convert the str to int
        
        linecount = linecount + 1; 
    }
    fclose(inputfile); 
    
    //bubble sort to sort the data by descending order
    for (int i = 0; i < linecount - 1; i++)
    {
        for (int j = 0; j < linecount - 1; j++)
        {
            if (listoffitnessdata[j].steps > listoffitnessdata[j + 1].steps)
            {
                //swap array[j] and array[j + 1] around
                FITNESS_DATA temp = listoffitnessdata[j];
                listoffitnessdata[j] = listoffitnessdata[j + 1];
                listoffitnessdata[j + 1] = temp;
            }
        }
    }
    
    for (int x = 0; x < linecount; x++)
    {
        printf("%s\t%s\t%d\n",listoffitnessdata[x].date, listoffitnessdata[x].time, listoffitnessdata[x].steps);
    }

    char newfilename[strlen(filename)+4];
    strcpy(newfilename, filename);
    strcat(newfilename,".tsv");

    FILE *outputfile = fopen(newfilename, "w"); 
    for (int line = 0; line < linecount; line++) 
    {
        fprintf(outputfile, "%s\t%s\t%d\n",listoffitnessdata[line].date, listoffitnessdata[line].time, listoffitnessdata[line].steps);
    }
    fclose(outputfile);
    
    return 0;
}
