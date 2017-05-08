/*this time we use omp to see what is difference
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define threads 4

struct cell{
  int x; //x-aixs
  int y; //y-axis
  int step; //the total number of steps to go this cell from starting point
};

int main(int argc, char *argv[]){
  struct cell queue[2501]; // the maximum size of map is 50*50, so the maximum number of possible is 2500;
  int maze[51][51] = {0};
  int book[51][51] = {0};//book the cell already stepped on

  int next[4][2] = { {0,1},
		     {1,0},
		     {0,-1},
                     {-1.0}};
  int head,tail;
  int n,m; // size of maze, n is number of rows, m is number of columns
  int startx,starty,destx,desty;
  int nthreads = threads;
  //set up time

  if(argc > 1){
    nthreads = atoi(argv[1]);
  }
  //build the maze and set up
  printf("size of maze is:");
  scanf("%d %d",&n,&m);
  printf("setting the maze now(0 is normal path, 1 is rock)\n");
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      scanf("%d",&maze[i][j]);
    }
  }
  printf("coordinate of start point:");
  scanf("%d %d",&startx,&starty);
  printf("coordinate of end point:");
  scanf("%d %d",&destx,&desty);

  //initialize the queue
  head = 1;
  tail = 1;
  //set coordinate of enter point of maze to queue
  queue[tail].x = startx;
  queue[tail].y = starty;
  queue[tail].step = 0;
  tail++;
  book[startx][starty] = 1;

  int flag = 0;//book whether we achieve the destination we set
  //when queu is not empty we start searching
  double start_time = omp_get_wtime();
  while(head < tail){
#pragma omp parallel num_threads(nthreads)
    {
    //test the four possible movement in this point
#pragma omp for schedule(static, 1)
      for(int k = 0; k <= 3; k++){
	int tx = queue[head].x + next[k][0];
	int ty = queue[head].y + next[k][1];
	
	//test whether the coordinate exceeds the boundary
	if(tx < 1 || tx > n || ty < 1 || ty > m)
	continue;
	//test whether there is rock in the way or we have stepped this point
	if(maze[tx][ty] == 0 && book[tx][ty] == 0)
	  {
	    //mark this point
	    book[tx][ty] = 1;
	    //add a new point to the queue
	    queue[tail].x = tx;
	    queue[tail].y = ty;
	    queue[tail].step = queue[head].step + 1; //its total step number is one more than its parent
	    tail++;
	  }
	//if we arrive at the destination, we stop and leave loop
	if(tx == destx && ty == desty)
	  {
	    flag = 1;
	  }
      }
    }//pragma ends
    if(flag == 1)
      break;
    head++; //when we finish one point, we need add one on head to keep doing the same thing on next point.
  }
  double time = omp_get_wtime() - start_time;
  printf("the shortest steps to destination is: %d\n", queue[tail-1].step);//since the tail points to the next position of current end of queue, so we need to minus one.
  printf("Total time taken by CPU for this task: %lf seconds\n",time);
  
  return 0;
  
  
}
