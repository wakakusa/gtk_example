ifort -openmp hello.f90 -o hello.exe 
export OMP_NUM_THREADS 4
./hello.exe