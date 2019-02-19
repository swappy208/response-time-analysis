/*

@author : Swapnil Tamrakar

----------------------------------------------

Instructions to run:

1. Create a txt file with the content such as :

a 80     40 1 80
b 40 10         2   15
c 20    5   3   5

2. Go to the folder containing this c program

3. In the terminal type the command to compile the c program:

    gcc response-time-analysis.c 

4. In the terminal type the command to run the c program:

    ./a.out <TXT_FILE_PATH>

    for example: ./a.out ./test.txt

Sample Output :

Process	Period	ComputationTime	Priority	Response	CalcResponse
c	20	5		3		5		5
Process	Period	ComputationTime	Priority	Response	CalcResponse
b	40	10		2		15		10
Process	Period	ComputationTime	Priority	Response	CalcResponse
a	80	40		1		80		40

*/

#include<stdio.h>
#include<math.h>
int main(int argc, char const *argv[])
{
    int count, t[20], c[20], p[20], r[20], response[20], pos, w, oldw, temp;
    char process[20]; // process names
    FILE *fp;
    if (argc == 2){ //check if file is provided in command line
        fp = fopen(argv[1], "r"); //read file
    }
    else{ //if no file provided
        printf("Error: Missing file in command line. Please enter the file name as a parameter in the command line");
        return 0;
    }
    count = 0; //initialize count
    while (fscanf(fp, "%s", &process[count])==1) // read files and populate variables
    {
        fscanf(fp, "%d", &t[count]);
        fscanf(fp, "%d", &c[count]);
        fscanf(fp, "%d", &p[count]);
        fscanf(fp, "%d", &r[count]);
        count = count + 1;
    }

    //sort processes in descending order of priority
    for(int i=0 ; i<count ; i++)
    {
        pos = i;
        for(int j=i+1 ; j<count ; j++)
        {
            if(p[j]>p[pos])
                pos=j;
        }
 
        temp=t[i];
        t[i]=t[pos];
        t[pos]=temp;

        temp=c[i];
        c[i]=c[pos];
        c[pos]=temp;

        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
 
        temp=r[i];
        r[i]=r[pos];
        r[pos]=temp;
 
        char tempc=process[i];
        process[i]=process[pos];
        process[pos]=tempc;
    }

    //first process has response 
    response[0] = c[0];

    for (int i=1; i<count; i++) // for each other process
    {
        // starting w value is the computation value
        oldw = c[i];
        w = c[i];
        while (oldw<=t[i]){
            //sum of higher priorities
            w = c[i];
            for (int j = i - 1; j>=0; j--)
            {
                w = w + ceil((double)oldw/t[j]) * c[j];
            }
            // exit if R found
            if (w == oldw){
                response[i] = w;
                break;
            }
            oldw = w;
        }
        // if cannot be scheduled, return -1
        if (!response[i])
        {
            printf("Task %c cannot be scheduled", process[i]);
            response[i] = -1;
        }
    }

    //print output in the order of execution
    printf("Process\tPeriod\tComputationTime\tPriority\tResponse\tCalcResponse\t\n");
    for (int i=0; i<count; i++)
    {
        printf("%c\t%d\t%d\t\t%d\t\t%d\t\t%d\n", process[i], t[i], c[i], p[i], r[i], response[i]);
    }

    fclose(fp);
    return 0;
}
