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

mpirun --oversubscribe -np 4 ./test

```
FOR MATLAB DISPLAY:
clear all
clc
close all

load -ascii color.txt

figure,
imagesc(color'),
colormap colorcube
axis square
axis off

```

```
OVERLEAF:
https://www.overleaf.com/1145998894zzzhyhyfbqrg

```
