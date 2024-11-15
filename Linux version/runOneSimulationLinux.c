/*imported libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*constants and data structures*/
#define SIZE 500
enum lightColours {Green, Red};


/*function definitions*/
int main ( int argc, char *argv[]);
float randomFloat ();
void enqueue (int *queue1st, int *rear);
void dequeue (int *front);
void printQ (int *queue, int fp, int rp);
void emptyQueue (int *queue, int length);
void turnIncrement (int *queue, int fp, int rp);
void swapLights (enum lightColours *lL, enum lightColours *rL);
void printLights (enum lightColours *lL, enum lightColours *rL);
int totalVehicles (int *queue);
float averageWaitingTime (int *queue, int tot);
int maxWaitingTime (int *queue);
void writeToFile(int lVehicletotal, float lAverageWaitingTime, int lMaxWaitingTime, int lClearance, int rVehicletotal, float rAverageWaitingTime, int rMaxWaitingTime, int rClearance);



/*functions*/

/*main function, most of processes are combined to finalise the simulaiton here*/
int main ( int argc, char *argv[]) {
  /*args are float lArrivalRate,int lPeriod,float rArrivalRate,int rPeriod*/
  /*check arg vals*/
  if (argc != 5) {
    printf("\nIncorrect number of arguments input, please attempt again after reading the README. %d", argc);
  }
  else {
    /*setting up left queue structure*/
    int lQ [SIZE];
    /*left q front pointer and rear pointers*/
    int lQF = 0;
    int lQR = 0;

    /*setting up right queue structure*/
    int rQ [SIZE];
    /*right q front and rear pointers*/
    int rQF = 0;
    int rQR = 0;

    /*setting up lights*/
    /*the initial colours of the lights are inconsequential as the cars appear randomly from either side, meaning there is no*/
    /*weight to a particular side by having a specified initialisation.*/
    enum lightColours lLight = Green;
    enum lightColours rLight = Red;

    /*prepare queues by emtpying them*/
    emptyQueue(lQ,SIZE);
    emptyQueue(rQ,SIZE);

    /*create random seed*/
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    /*diagnostic varisables*/
    int lFound = 0;
    int rFound = 0;
    int lVehicletotal;
    float lAverageWaitingTime;
    int lMaxWaitingTime;
    int lClearance;
    int rVehicletotal;
    float rAverageWaitingTime;
    int rMaxWaitingTime;
    int rClearance;

    /*convert param into variables*/
    float lArrivalRate = atof(argv[1]);
    int lPeriod = atoi(argv[2]);
    float rArrivalRate = atof(argv[3]);
    int rPeriod = atoi(argv[4]);
    /*check given args in bounds*/
    if ((lArrivalRate < 0.0 || lArrivalRate > 1.0) || (rArrivalRate < 0.0 || rArrivalRate > 1.0) || (lPeriod < 1)  || (rPeriod < 0)) {
      printf("\nParameters regarding arrival rate of vehicles are out of bounds,\nplease try again after reading the README.");
    }
    else {

      /*simulation working*/
      /*counts iteration number*/
      int count = 0;
      /*counts iteration that light has been active*/
      int lightCount = 0;
      /*true condition for while loop*/
      int running = 0;
      while (running == 0) {
        /*checks if left light is green and has reached lPeriod bound, if so, swap lights*/
        if (lightCount == lPeriod && lLight == Green) {
          lightCount = 0;
          swapLights(&lLight, &rLight);
          count += 1;
        }
        /*checks if right light is green and has reached rPeriod bound, if so, swap lights*/
        else if (lightCount == rPeriod && rLight == Green) {
          lightCount = 0;
          swapLights(&lLight, &rLight);
          count+=1;
        }
        /*main set of functions*/
        else {
          /*count < 500*/
          if (count < 500) {
            /*left hand queue vehicle join*/
            if (randomFloat() < lArrivalRate) {
              /*add to LQ*/
              enqueue(lQ,&lQR);
            }
            /*right hand queue vehicle join*/
            if (randomFloat() < rArrivalRate) {
              /*add to RQ*/
              enqueue(rQ,&rQR);
            }
          }
          /*vehicle has option to pass through traffic lights for both left and right*/
          if (lLight == Green) {
            /*left car has option to go*/
            /*check if vehicle in left queue*/
            if (lQ[lQF] != -1) {
              dequeue(&lQF);
            }
          }
          else if (rLight == Green) {
            /*right vehicle has optin to go*/
            /*check if vehicle exists in right q*/
            if (rQ[rQF] != -1) {
              dequeue(&rQF);
            }
          }

          count += 1;
          lightCount += 1;

        }



      /*condition is when both queues are empty, when fp =rp for both, AND count > 500*/
      if (lFound == 0) {
        if (lQF == lQR && count >= 500) {
          lClearance = count-499;
          lFound = 1;
        }
      }
      if (rFound == 0) {
        if (rQF == rQR && count >= 500) {
          rClearance = count-499;
          rFound = 1;
        }
      }

      /*initial filter meaning fewer calcs are needed*/
      if ((count >= 500) && (lQF == lQR && rQF == rQR)) {
        /*do diagnositics*/

        lVehicletotal = totalVehicles(lQ);
        lAverageWaitingTime = averageWaitingTime(lQ, lVehicletotal);
        lMaxWaitingTime = maxWaitingTime(lQ);
        rVehicletotal = totalVehicles(rQ);
        rAverageWaitingTime = averageWaitingTime(rQ, rVehicletotal);
        rMaxWaitingTime = maxWaitingTime(rQ);

        printf("\nlVehicleTotal = %d\nrVehicleTotal = %d\n", lVehicletotal, rVehicletotal);
        printf("\nlAverageWaitingTime = %f\nrAverageWaitingTime = %f\n", lAverageWaitingTime,rAverageWaitingTime);
        printf("\nlMaxWaitingTime = %d\nrMaxWaitingTime = %d\n",  lMaxWaitingTime, rMaxWaitingTime);
        printf("\nlClearance = %d\nrClearance = %d\n",  lClearance, rClearance);

        writeToFile(lVehicletotal, lAverageWaitingTime, lMaxWaitingTime, lClearance, rVehicletotal, rAverageWaitingTime, rMaxWaitingTime, rClearance);

        /*pass to other sim*/


        running = 1;
      }

      turnIncrement(lQ, lQF, lQR);
      turnIncrement(rQ, rQF, rQR);
      }
    }
  }
}


/*creates a random val between0 and 1*/
float randomFloat () {
  return (float)rand() / (float)RAND_MAX;
}


/*function to add a 'vehicle' to a given queue*/
void enqueue (int *queue1st, int *rear) {
  /*we always add a 0, this value will be incremented for each turn it is in the queue*/
  int newVal = 0;
  /*find index to insert into*/
  int i;
  for (i = 0; i<*rear; i++) {
    queue1st++;
  }
  /*add 0 to queue, at index rear*/
  *queue1st = newVal;
  /*increment rear by 1*/
  *rear += 1;
}

/*function to remove first 'vehicle' from queue*/
void dequeue (int *frontp) {
  /*increase front pointer by 1, as we wish to store all vehicles still*/
  *frontp += 1;
}

/*prints the elements of the queue*/
void printQ (int *queue, int fp, int rp) {
  printf("\nqueue is:\n");
  int j;
  for (j = 0; j < fp; j++) {
    queue++;
  }
  int i;
  for(i = fp; i < rp; i++)
  {
      printf("Value of queue[%d] is: %d \n", i, *queue);
      queue++;
  }
}

/*for each element of the queue, replace the previuosly held value with -1*/
void emptyQueue (int *queue, int length) {
  int i;
  for (i = 0; i < length; i++) {
    *queue = -1;
    queue++;
  }
}

/*for each currently active vehicle, increment waiting turns by 1*/
void turnIncrement (int *queue, int fp, int rp) {
  int j;
  for (j = 0; j < fp; j++) {
    queue++;
  }
  int i;
  for(i = fp; i < rp; i++)
  {
      *queue+=1;
      queue++;
  }
}

/*swaps the lights status*/
void swapLights (enum lightColours *lL, enum lightColours *rL) {
  /*check current states, swap based on current states*/
  if (*lL == Green) {
    /*if left light is green swap to red, and vice versa for right light*/
    *lL = Red;
    *rL = Green;
  }
  /*opposite for any other condition (the only other condiditon).*/
  else {
    *lL = Green;
    *rL = Red;
  }
}

/*prints off the current state of the lights to the terminal*/
void printLights (enum lightColours *lL, enum lightColours *rL) {
  if (*lL == Green) {
    printf("\nLeft light status is Green\nRight light status is Red");
  }
  else {
    printf("\nLeft light status is Red\nRight light status is Green");
  }
}

/*iterates through a given queue until it hits an element with value -1, halts and returns iterations*/
int totalVehicles(int *queue) {
  /*iterate between queue start address and queue start + 500 (as max size), until -1 hit*/
  int i;
  for (i = 0; i < SIZE; i++) {
    if (*queue == -1) {
      /*returns when -1 found*/
      return (i);
    }
    else {
      /*otherwise increments*/
      queue++;
    }
  }
}

/*calculates the average waiting time of a queue*/
float averageWaitingTime (int *queue,int tot) {
  int sum = 0;
  int i;
  for (i = 0; i < SIZE; i++) {
    if (*queue != -1) {
      /*adds to sum*/
      sum += *queue;
      queue++;
    }
    else {
      /*breaks loop*/
      break;
    }
  }
  /*calculate average*/
  float averageWait = (float) sum / (float) tot;
  return averageWait;
}

/*calculates total waiting time of a queue*/
int maxWaitingTime (int *queue) {
  int maxWait = 0;
  int i;
  for (i = 0; i < SIZE; i++) {
    if (*queue == -1) {
      break;
    }
    else {
      if (*queue > maxWait) {
        maxWait = *queue;
      }
    }
    queue++;
  }
  return maxWait;
}

/*writes data to binary file*/
void writeToFile (int lVehicletotal, float lAverageWaitingTime, int lMaxWaitingTime, int lClearance, int rVehicletotal, float rAverageWaitingTime, int rMaxWaitingTime, int rClearance) {
  FILE *fp;
  float a[] = {
  (float)lVehicletotal,
  lAverageWaitingTime,
  (float)lMaxWaitingTime,
  (float)lClearance,
  (float)rVehicletotal,
  rAverageWaitingTime,
  (float)rMaxWaitingTime,
  (float)rClearance};
  /*
  fptr = fopen("data.data", "ab");
  fwrite (exampleArray, sizeof(float), sizeof(exampleArray), fptr);
  */
  fp = fopen("data.txt","a");
  int i;
  for (i = 0; i < 8; i++){
      fprintf(fp, "%f ", a[i]);
  }
  fprintf(fp, "\n");
  fclose(fp);
}
