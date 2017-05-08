Compilation:
  I provide a makefile for you. To compile each file, you just need to type "make + filename(without.c)" it will compile. And type "make run_(filename)" to run the program.
  Notice: you can change different number of threads when you run *_omp by adding a number after "make run_(filename)"

Platform used:
The platform I used in this project is openMP, since in maze solver, when we try to move from a point, we have four possible path(normally) to go, so I want to use openMP to see whether it will help reduce the time on testing different possibility of path.

external files and structure description:
we have four files in this project, dfs, bfs,bfs_omp. dfs is a maze solver using depth first search, since we need to have a recursive call of the dfs function in dfs.c, we can not apply openMP on dfs.c . bfs is a maze solver using breadth first searchm, bfs_omp is very samiliar to bfs but having extra openMP commands.

