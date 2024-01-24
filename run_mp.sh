if [ ! -d "bin" ]; then
    mkdir bin
fi

cd bin

gcc -fopenmp -c ../lib/gen.c
gcc -fopenmp -c ../src/MP/$1.c

gcc -fopenmp *.o -o $1
rm *.o

if [ -f "$1" ]; then
    ./"$1"
fi
