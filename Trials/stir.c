
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

const char* filename = "26.txt";
int main(int argc, char *argv[])
{
    char *token;
    FILE *fp, *f;
    char *fu;
    char *d;
    fp= fopen("26.txt", "r"); //open a file for reading (r indicates reading) - The funciton gives a pointer (fp)
    
        printf("Printing the document \n");
    if (fp==NULL){
        printf("Error opening the file\n\n");
        exit(EXIT_FAILURE);
    }
    struct stat sb;
    stat(filename, &sb);
 
   //char * fc; -- this gives segmentation fault
    char *fc = malloc(sizeof(char)*100);

    int n=1; 
for (int i=0; i<=n;i++){
        fscanf(fp, "%[^\n]", fc);
       //printf("%s\n", fc);


       token = strtok(fc,"\t");
    while(token!=NULL){
      printf("%s\n",token);
      token = strtok(NULL,"\t");
    }
}



 
   

}