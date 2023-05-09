mpicc -o $1 src/MPI/$1.c

N=3
if [ $# -gt 1 ]; then
   N=$2
fi

if [ -f $1 ]; then
   mpiexec -n $N ./$1
   rm $1
fi
