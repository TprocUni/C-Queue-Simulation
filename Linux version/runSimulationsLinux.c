/*run sims main, accepts params from cmd line*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    printf("\nIncorrect number of arguments input, please attempt again after reading the README.");
  }
  else {
    /*array that stores all the results*/
    float results [100][8];
    /*split params and assign them, as well as check their validity*/
    /*convert param into variables*/
    float lArrivalRate = atof(argv[1]);
    int lPeriod = atoi(argv[2]);
    float rArrivalRate = atof(argv[3]);
    int rPeriod = atoi(argv[4]);

    /*clear out empty file*/
    char *filename = "data.txt";
    FILE *fpr = fopen(filename, "w");
    fclose(fpr);

    /*check given args in bounds*/
    if ((lArrivalRate < 0.0 || lArrivalRate > 1.0) || (rArrivalRate < 0.0 || rArrivalRate > 1.0) || (lPeriod < 1)  || (rPeriod < 0)) {
      printf("\nParameters regarding arrival rate of vehicles are out of bounds,\nplease try again after reading the README.");
    }
    else {
      /*run program 100 times*/
      int i;
          for (i = 0; i < 100; i++) {
            char command[1024];
            sprintf(command, "./runOneSimulation %f, %d, %f, %d", lArrivalRate, lPeriod, rArrivalRate, rPeriod);
            system(command);
          }
      }



      FILE *fp = fopen(filename, "r");

      if (fp == NULL)
      {
          printf("Error: could not open file %s", filename);
          return 1;
      }

      const unsigned MAX_LENGTH = 40000;
      char buffer[MAX_LENGTH];

      int counter = 0;

      float lNoOfVs = 0;
      float lAvWait = 0;
      float lMaxWait = 0;
      float lClearance = 0;

      float rNoOfVs = 0;
      float rAvWait = 0;
      float rMaxWait = 0;
      float rClearance = 0;

      while (fgets(buffer, MAX_LENGTH, fp)){
          char * token = strtok(buffer, " ");

          while( token != NULL ) {
              float temp = atof(token);

              if ((counter % 8) == 0){
                lNoOfVs += temp;
                printf( "%s\n", token );
                printf("\nlNoOfVs = %f\n", lNoOfVs);

              } else if ((counter % 8) == 1){
                lAvWait += temp;
              } else if ((counter % 8) == 2){
                lMaxWait += temp;
              } else if ((counter % 8) == 3){
                lClearance += temp;
              } else if ((counter % 8) == 4){
                rNoOfVs += temp;
              } else if ((counter % 8) == 5){
                rAvWait += temp;
              } else if ((counter % 8) == 6){
                rMaxWait += temp;
              } else if ((counter % 8) == 7){
                rClearance += temp;
              }

              token = strtok(NULL, " ");
              counter++;
          }
      }

      fclose(fp);

    printf("%f\n", lNoOfVs);
    printf("%f\n", lAvWait);
    printf("%f\n", lMaxWait);
    printf("%f\n", lClearance);

    printf("%f\n", rNoOfVs);
    printf("%f\n", rAvWait);
    printf("%f\n", rMaxWait);
    printf("%f\n", rClearance);




    /*produce average of each*/
    int i;
    lNoOfVs /= 100;
    rNoOfVs /= 100;
    lAvWait /= 100;
    rAvWait /= 100;
    lMaxWait /= 100;
    rMaxWait /= 100;
    lClearance /= 100;
    rClearance /= 100;
    /*output formatted nicely*/
    printf("\n\nResults (averaged over 100 runs):");
    printf("\n   From left:");
    printf("\n    Number of vehicles:   %5.2f", lNoOfVs);
    printf("\n    Average waiting time: %5.2f", lAvWait);
    printf("\n    Maximum waiting time: %5.2f", lMaxWait);
    printf("\n    Clearance time:       %5.2f", lClearance);
    printf("\n   From right:");
    printf("\n    Number of vehicles:   %5.2f", rNoOfVs);
    printf("\n    Average waiting time: %5.2f", rAvWait);
    printf("\n    Maximum waiting time: %5.2f", rMaxWait);
    printf("\n    Clearance time:       %5.2f", rClearance);
    }
    /* code */
    /*kill*/
    return 0;
  }
