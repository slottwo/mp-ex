gcc -fopenmp -c lib/generators.c
gcc -fopenmp -c src/MP/$1.c
gcc -fopenmp *.o -o bin/$1
rm *.o
./bin/"$1"
