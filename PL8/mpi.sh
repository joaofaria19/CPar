#!/bin/bash
#SBATCH --ntasks=4
#SBATCH --partition=cpar

mpirun -np 4 ./a.out
