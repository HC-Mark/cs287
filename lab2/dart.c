/*  dartboard game model 
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define threads 4
double dis_rand(double mean, double sigma);  //0.0 to 1.0 for distance of dartboard
double angle_rand();  //0 to 360 for angle of dartboard
int getting_score(float distance, float angle);  //get a score between 1 and 60 upon the location of dart on board

int main(int argc, char *argv[]){
  //set up for timing -- normal
  /*
  clock_t start,end;
  start = clock();
  double total = 0.0;
  */
  
  //main program begins
  srand((long)time(NULL));//seed random function
  
  /*here are the value user input:
   user_dis: the distance a player aims at
   user_angle: the angle of a player aims at, 
               but since they are not good at this game,
	       we throw this data away,and let angle be random
   capacity: determines the value of sigma.
   */
  double user_dis = 0.0;
  double user_angle = 0.0;
  int capacity =0;
  long test = 0;
  int i;

  double distance=0.0;
  double angle = 0.0;//the actual location of dart
  double score = 0.0;//always remember to initialize
  int nthreads = threads;

  if (argc > 1)
    {	test = atoi(argv[1]);
    }
  if (argc > 2)
    {	nthreads = atoi(argv[2]);
    }

  //user input process
  printf("Please enter where you aim at:\n");
  
  //input the radius of the location player aims at.
  printf("distance(range from 0 to 1): ");
  scanf("%lf", &user_dis);
  //make sure user_dis is between 0 to 1 to avoid crashing of program.
  if(user_dis < 0 || user_dis > 1){
    printf("Please enter an valid number for radius(0 to 1)!\n");
    return -1;
  }


  //input how good player is
  printf("How good are you playing this game(0 to 100): ");
  scanf("%d", &capacity);
  //make sure capacity is between 0 to 100
  if(capacity < 0 || capacity > 100){
    printf("Please enter an valid number for capacity(0 to 100, integer)!\n");
    return -1;
  }
  
  //change capacity to a valid sigma value;
  double sigma = 10.0 / capacity;
  //printf("%lf\n",sigma);
  
  //process the user input to actual location
  //add a for loop here to conduct experiment
  int totalscore = 0;
  double avg_score = 0;
  //test = test / nthreads;
  double start_time = omp_get_wtime();
#pragma omp parallel num_threads(nthreads)
  {
    printf("num_test in %d is %ld\n",omp_get_thread_num(), test);
    #pragma omp for reduction (+:totalscore)
    for(i = 0; i < test; i++){
      distance = dis_rand(user_dis,sigma);
      angle = angle_rand();
      // printf("random distance is: %f",distance);

      //get score by shooting one dart
      score = getting_score(distance, angle);
      
      totalscore +=  score;
    }
  }
  //end = clock();
  double time = omp_get_wtime() - start_time;
  printf("\n");
  printf("total score is %d\n", totalscore);
  avg_score = totalscore/(double)test;
  printf("The average score is: %lf\n", avg_score);
  //end timing
  //total = (double)(end - start)/CLOCKS_PER_SEC;
  //report the total time
  printf("Total time taken by CPU for this task: %lf seconds\n", time);

  return 0;
}




//function is inspired and modified by wikipedia box and Muller Algorithms
double dis_rand(double mean, double sigma) {
  double epsilon = 0.000001; //make sure the number is valid for a Z value
  double two_pi = 2.0*3.14159265358979323846;// constant for 2 pi
  double z;
  double temp1, temp2;//temporary variables to store uniformly random numbers
  double result;//the final radius the dart shot on
  
  //generate a random number for standard normalize;
  do{
    temp1 = rand()/(double)RAND_MAX;
    temp2 = rand()/(double)RAND_MAX;
  }while( temp1 <= epsilon );
  
  //standard normalize for only one variable
  z = sqrt(-2.0 * log(temp1)) * cos(two_pi * temp2);
  
  //get the final radius of dart
  result = z * sigma + mean;
  //if the radius is smaller than 0, change to its absolute value
  //But the best way is to let angle add 180 degree but hard to implement
  if(result < 0){
    result = -1 * result;
  }
  //output final radius
  return result;
}

//function to generate random angle 
double angle_rand(){
  return  360 * (rand()/(double)RAND_MAX);

}

 //apply the rule of dartboard
int getting_score(float distance, float angle){
  int score;
  
  //defining score area.
  if(distance <= 0.1|| distance > 1.0){
    return  0;
  }
  //a very long conditional group to check score
  if(angle <= 9 && angle > 351){
    score = 20;
  }
  if(angle <= 27 && angle > 9){
     score = 1;
  } 
  if(angle <= 45 && angle > 27){
    score = 18;
  }
  if(angle <= 63 && angle > 45){
    score = 4;
  }
  if(angle <= 81 && angle > 63){
    score = 13;
  }
  if(angle <= 99 && angle > 81){
    score = 6;
  }
  if(angle <= 117 && angle > 99){
    score = 10;
  }
  if(angle <= 135 && angle > 117){
    score = 15;
  }
  if(angle <= 153 && angle > 135){
    score = 2;
  }
  if(angle <= 171 && angle > 153){
    score = 17;
  }
  if(angle <= 189 && angle > 171){
    score = 3;
  }
  if(angle <= 207 && angle > 189){
    score = 19;
  }
  if(angle <= 225 && angle > 207){
    score = 7;
  }
  if(angle <= 243 && angle > 225){
    score = 16;
  }
  if(angle <= 261 && angle > 243){
    score = 8;
  }
  if(angle <= 279 && angle > 261){
    score = 11;
  }
  if(angle <= 297 && angle > 279){
    score = 14;
  }
  if(angle <= 315 && angle > 297){
    score = 9;
  }
  if(angle <= 333 && angle > 315){
    score = 12;
  }
  if(angle <= 351 && angle > 333){
    score = 5;
  }
  //end of if condition TT too many of them

  //start to check mutiple rate
  if(distance > 0.1 && distance <= 0.45){
    score = score * 1;
  }
  if(distance > 0.45 && distance <= 0.5){
    score = score *3;
  }
  if(distance > 0.5 && distance <= 0.95){
    score = score * 1;
  }
  if(distance > 0.95 && distance <= 1.0){
    score = score * 2;
  }
  //output the final score
  return score;
}
