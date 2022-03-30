# mpi_learn

Learn parallels programming with **C** and MPI, Pthread, OpenMP this three of API. I am using MacOS while I would provide the way to install **mpich** in Ubuntu20.04.

### MacOS

``` bash
$ brew install mpich
```

### Ubuntu20.04

``` bash
$ sudo apt install mpich
```
## the learning order

I suggest you could follow the number of each file to learning, which I will write an overview in the future.

## copmile with mpicc

I didn't provide the executable file because I extremely recommend you to compile by yourself, which experience will enhance your competence of the compiling process of the file.



``` bash
$ mpicc file.c -o file.out  # "file" is your file name
```

``` bash
$ mpiexec -n process ./file.out  
# fill the total process in "process"
# "./file.out" is your executable file
```