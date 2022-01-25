To compile in mpi

```
mpicc <filename.c> -o <tag name>

```
To run the code
```
mpirun --oversubscribe -np <number of processors> <tag name>
```

Example:

``` 
mpicc mpiTEST.c -o test
```

```
mpirun --oversubscribe -np 4 test
```

