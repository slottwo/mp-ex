mpicc -o program src/MPI/$1.c

N=3
if [ $# -gt 1 ]; then
   N=$2
fi

if [ -f program ]; then
   mpiexec -n $N ./program
   rm program
fi
