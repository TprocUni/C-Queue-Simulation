#!/bin/bash
gcc -ansi -c runOneSimulation.c -o runOneSimulation.o
gcc runOneSimulation.o -o runOneSimulation
gcc -ansi -c runSimulations.c -o runSimulations.o
gcc runSimulations.o -o runSimulations
./runSimulations
