bfs: bfs.c
	gcc -o bfs bfs.c -std=c99
run_bfs: bfs
	./bfs
bfs_omp:bfs_omp.c
	gcc -O3 -o bfs_omp bfs_omp.c -fopenmp
run_bfs_omp: bfs_omp
	./bfs_omp
