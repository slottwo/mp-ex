mpicc -o $1 src/MPI/$1.c
N=2
if [ $# -gt 1 ]; then
   N=$2
fi
mpiexec -n $N ./$1
rm $1
