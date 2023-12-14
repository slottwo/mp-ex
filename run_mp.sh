if [-f bin/"$1"]; then
    rm bin/"$1"
fi

gcc -fopenmp -c lib/generators.c
gcc -fopenmp -c src/MP/$1.c

gcc -fopenmp *.o -o bin/$1
rm *.o

if [-f bin/"$1"]; then
    ./bin/"$1"
fi
