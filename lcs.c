#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DIA 100
#define UP 10
#define LEFT 1
int rowSize,coloumnSize;
struct Line {
	char * string;
	int length;
}Line;
void printMatrix(int row, int coloumn, int (*ptr_arr)[coloumn]){
  int i,j;
  //printf("Inside printMatrix lcs\n");
  for (i = 0; i < row; ++i)
  {
    for ( j = 0; j < coloumn; ++j)
      {
        if(ptr_arr[i][j]>=999){
        printf("%7s","INF");
        }else{
        printf("%7d",ptr_arr[i][j]);
        }
        
      }
      printf("\n");
  }
  
}

void printPathMatrix(int row, int coloumn, int (*ptr_arr)[coloumn]){
  int i,j;
  //printf("Inside Path Matrix lcs\n");
  for (i = 0; i < row; ++i)
  {
    for ( j = 0; j < coloumn; ++j)
      {
        if(ptr_arr[i][j]==100){
        	printf("%7s","DIA");
        }else if(ptr_arr[i][j]==10){
        	printf("%7s","UP");
        }else if(ptr_arr[i][j]==1){
        	printf("%7s","LEFT");
        }else{
        printf("%7d",ptr_arr[i][j]);
        }
      }
      printf("\n");
  }
  
}
void printLCS(int row,int coloumn, int (*ptr_arr)[coloumn],char *a, char *b){
	int i,j;
	
   int index = ptr_arr[row-1][coloumn-1];
   int finalSize=index-1;
  // Create a character array to store the lcs string
   char lcs[index+1];
   lcs[index] = '\0'; // Set the terminating character
    i = row-1, j = coloumn-1;

   while (i > 0 && j > 0)
   {
      // If current character in X[] and Y are same, then
      // current character is part of LCS
      if (a[i-1] == b[j-1])
      {		
      		
        	lcs[index-1] = a[i-1]; // Put current character in result
        	i--; j--; index--;     // reduce values of i, j and index
      }
 
      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (ptr_arr[i-1][j] > ptr_arr[i][j-1])
         i--;
      else
         j--;
   }
   	
   	printf("================LCS===============\n%s %d\n",lcs,finalSize);
	printf("\n");
}

void lcs(int aSize, char *a, int bSize, char *b){
	
	rowSize= aSize+1;
	coloumnSize = bSize+1;

	
	int i,j;
	int graph[rowSize][coloumnSize];
	int path[rowSize][coloumnSize];

     for (i = 0; i < rowSize; ++i) // intializing grpah with 0
      {
      	for (j = 0; j < coloumnSize; ++j)
      	{
      		graph[i][j]=0;
      		path[i][j]=0;
      		
      	}
      } 
	
	
	for ( i = 1; i < rowSize; ++i)
	{
		for ( j = 1; j < coloumnSize; ++j)
		{	
			
			if(*(a+(i-1))==*(b+(j-1))){
				graph[i][j]=graph[i-1][j-1]+1;
				path[i][j]=DIA;
			}else{
				if(graph[i-1][j]>=graph[i][j-1]){
					graph[i][j]=graph[i-1][j];
					path[i][j]=UP;
				}else{
					graph[i][j]=graph[i][j-1];
					path[i][j]=LEFT;				}
			}
		}
	}
	printf("Graph\n");
	printMatrix(rowSize,coloumnSize,graph);
	printf("Path\n");
	printPathMatrix(rowSize,coloumnSize,path);
	printLCS(rowSize,coloumnSize,graph,a,b);
}
int main(int argc, char *args[]){
	

	FILE * fp;
	int i=0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    struct Line linelist[2];
    fp = fopen(args[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        
        // if(read==1 || read==0){
        //     printf("Incorrect Size of the String\n");
        //     exit(EXIT_SUCCESS);
        // }

        if('\n'!=line[read]){

        	strcat(line,"");
        	read++;
        }
        linelist[i].string=line;
		    linelist[i].length=read;
        i++;
        line = NULL;
    }
    
    fclose(fp);
    if(i!=2){
      printf("Two String are required\n");
      if (line){
        free(line);
      } 
      exit(0);
    }
    lcs(linelist[0].length,linelist[0].string,linelist[1].length,linelist[1].string);

	if (line){
        free(line);
  }
    exit(EXIT_SUCCESS);
}