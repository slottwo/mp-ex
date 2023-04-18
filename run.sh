gcc -fopenmp -c lib/generators.c
gcc -fopenmp -c src/parallel/$1.c
gcc -fopenmp *.o -o $1
rm *.o
./"$1"
