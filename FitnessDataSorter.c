#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}


int main() 
{
    //create an array of type FITNESS_DATA to store the records
    FitnessData listoffitnessdata[500]; //given up to 500 records

    //create temp variables to then move into the typedef array
    char tempdate[11]; //using typedef
    char temptime[6]; //using typedef
    int tempsteps; //should not pass 9999 steps

    int linecount = 0; //to count number of lines/records in the csv  


    //Open file
    char *filename = "FitnessData_2023.csv";

    FILE *file = fopen(filename, "r"); //to read
    if (file == NULL)
    {
        perror("");
        return 1;
    }
    int buffer_size = 500; //allow up to 500 lines
    char line_buffer[buffer_size];

    while (fgets(line_buffer, buffer_size, file) != NULL) //loop through the csv record by record
    {
        tokeniseRecord(line_buffer, ',', tempdate, temptime, *tempsteps); //use the tokeniseRecord to 
        //copy all the temporary data from the cycle to the array of fitness_data
        strcpy(listoffitnessdata[linecount].date ,tempdate);
        strcpy(listoffitnessdata[linecount].time, temptime);
        listoffitnessdata[linecount].steps = tempsteps; 
        
        printf("%s\n",tempdate);
        printf("%s\n",temptime);
        printf("%d\n",tempsteps);

        printf("%s/%s/%d\n",listoffitnessdata[linecount].date, listoffitnessdata[linecount].time, listoffitnessdata[linecount].steps);
        linecount = linecount + 1; 
    }
}
