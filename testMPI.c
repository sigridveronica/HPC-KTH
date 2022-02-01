#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

//S'ha d'arreglar: no funciona del tot be perque shauria de fer amb send receive amb el teu algoritme. Si no no. 

#define g2m(i,j) (i+ NX*j)
#define proc2Glob(i, j) (i+ posProcX*accuracy + (j+posProcY*accuracy)*NX)
#define prova(i,j) (j*NX +i) + NX*process_Rank //Aquest algoritme es de prova per veure si es podia fer un barrido horitzontal pero no es pot fer aixi que cal seguir treballant en el tema 
#define local(i, j) (j*accuracy +i)

int main(int argc, char** argv){
    int borrar =2;



      MPI_Init(&argc, &argv);

    int process_Rank, nProcs;

    //Number of cells for each processor
    int accuracy = 4;


    MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    //Number of processors in X and Y to fill the grid (now it must be the same)
    int nProcsX, nProcsY;
    nProcsX = nProcs/2;
    nProcsY = nProcs/2;

    double *refvec;
  
    
    //Number of cells in the grid
    int NX, NY;

    NX = nProcsX*accuracy;
    NY = nProcsY*accuracy;


    //Field allocations
    //GlobalField: field for the whole grid, procField: field for each of the processors
    double* procField = NULL;
    double* GlobalField;

    if (process_Rank ==0){

    GlobalField =  (double*)malloc(NX*NY*sizeof(double));
    refvec = GlobalField +1;
    //procField = (double*) malloc((double)accuracy*(double)accuracy*(sizeof(double))); //accuracy == number of cells per processor in X and Y axis (now is the same)
    }


   MPI_Barrier(MPI_COMM_WORLD);

    int posProcX, posProcY; //Cartesian position of each processor. Ex; if 4 processors in total: (0,0) for processor 0, (0,1) for processor 1, (0,1) for processor 2, (1,0) for processor 3
       
        //Decide where goes each Processor
            posProcX = process_Rank%nProcsX;
            posProcY = process_Rank/nProcsY;

       //printf("X = %d, Y= %d, and Processor %d \n", posProcX, posProcY, process_Rank);

       int a;


double ref;
double *localField = NULL;
              

  // if(process_Rank== 2){

    localField  =  (double*)malloc(accuracy*accuracy*sizeof(double));
       // printf("I am proessor  %d\n", process_Rank);
               posProcX = process_Rank%nProcsX;
            posProcY = process_Rank/nProcsY;

         //printf("I am process %d, index (%d, %d)\n", process_Rank, posProcX, posProcY);

//if (process_Rank==borrar) {
    

        for (int j=0; j<accuracy ; j++) {
            for (int i=0; i<accuracy; i++) {

                ref = proc2Glob(i, j);
                


                localField[(accuracy*j+i)]= ref;
                
              
               
                printf("%d ",(int)localField[(accuracy*j+i)]);
            }
          printf("\n");
        }
//}


//if (process_Rank==borrar){
MPI_Send(localField, 16, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//printf("Je;pppppp    %d",(int)sizeof(localField));
//}

MPI_Barrier(MPI_COMM_WORLD);



if (process_Rank==0){

 for (int k=0; k<nProcs;k++) {
 
    MPI_Recv(localField, 16, MPI_DOUBLE, k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

   posProcX = k%nProcsX;
   posProcY =  k/nProcsX;

  for (int i=0; i<accuracy; i++) {
     for (int j=0; j<accuracy ; j++) {
          
                GlobalField[proc2Glob(i,j)] = localField[i+j*(accuracy)];
                //printf("%ld ", sizeof(localField) );
                  printf("%d ",(int)localField[(accuracy*j+i)]);
            }
            printf("\n");
     }
 }


    printf ("\n \n");
      for (int j=0; j<NY; j++){
     for(int i=0; i<NX ; i++) {
      
       
          
                //GlobalField[g2m(i,j)] = g2m(i,j);
                //printf("%d ", (int)GlobalField[g2m(i,j)]);

                a = (int)(GlobalField[NX*j+i]);
                printf("%d ",a);
            }
            printf("\n");
        }


             
          free(GlobalField);
    }



   

    MPI_Finalize();
    return 0;   
}

