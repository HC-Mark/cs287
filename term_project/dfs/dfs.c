/*
  name: Tianming Xu
  description: This is a small labyrinth game which find the shortest path from starting point to destination which player can set. I use deepth first search to find that path.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int row,col; // width and height of maze
int target_x, target_y; // the x , y coordinate of our destination
int min = 9999; // deafult minimum steps

int maze[51][51]; // we use two dimensional array to store maze,so it's max size if 50X50
int book[51][51]; // we use another array to store position we have already stepped

void dfs(int x, int y, int step);
  
int main(){
  int startx,starty;
  clock_t start,end;
  printf("please tell me the number of rows of maze:");
  scanf("%d",&row);
  printf("please tell me the number of columns of maze:");
  scanf("%d",&col);
  printf("row is %d col is %d\n",row,col);
  printf("please setup your maze:\n");
  //it should be <= row and col otherwise, it will be one row and one col less than what we want
  for(int i = 1; i <= row; i++){
    for(int j = 1; j <= col; j++){
      scanf("%d", &maze[i][j]);//set up the maze by user
    }
  }

  printf("tell me the starting coordinate:");
  scanf("%d %d",&startx,&starty);
  printf("startx is %d, starty is %d\n",startx,starty);
  printf("tell me the destination:");
  scanf("%d %d", &target_x,&target_y);
  printf("targetx is %d, targety is %d\n",target_x,target_y);
  start = clock();
  book[startx][starty] = 1;//book the starting point
  dfs(startx,starty,0);
  end = clock();
  double time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("the minimum steps of this maze is:%d\n",min);
  printf("Total time taken by CPU for this task: %lf seconds\n",time);
  return 0;
  
}

void dfs(int x, int y, int step){
  //printf("test\n");
  int next[4][2] = {{0,1},//goes right
                    {1,0},//goes down
                    {0,-1},//goes left
                    {-1,0}};//goes up
  int tx,ty;
  //check whether we arrive at the destination
  if(x == target_x && y == target_y){
    //update min
    //printf("test\n");
    printf("step is %d\n",step);
    if(step < min)
      min = step;
    return; // we find one possible path, so we return to find another one

  }

  //if not arrive, then we need to go somewhere
  for(int i = 0; i <=3 ; i++){
    //calculate the next coordinate
    tx = x + next[i][0]; //control rows
    ty = y + next[i][1]; //control cols

    //test whether we pass the boundary
    if(tx < 1 || tx > row  || ty < 1 || ty > col)
      continue; // not an avaliable path, find another way to go

    //see whether it has rock on the way or we have already passed
    // if maze[tx][tx] == 1, it means there is a rock there
    if(maze[tx][ty] == 0 && book[tx][ty] == 0){
      book[tx][ty] = 1; //book this position
      dfs(tx,ty,step+1);//test next step
      book[tx][ty] = 0; //after we finish one path, we will reset the location to 0, ready for the next try
    }
  }
  return;
}
