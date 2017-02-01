/*  dartboard game model description:
    In this dartboard game, we will follow the rules and measurements below:
    1.R is the distance from center(the inner bullseye to the place we hit the
      dart). we assume the total distance(center to outmost white line) is 1;
      and such measurement for the game;
              0~0.1: bullseye (no point)
          0.1~0.45: 1x area (1 times the score you get by hit that piece)
          0.45~0.5: 3x area
          0.5~0.95: 1x area
          0.95~1: 2x area
    2.A is the angle between the straight upward(have a picmiddle of 20 points piece) and
      the place we hit. It should be between 0 to 360(degrees).Each piece will
      have 18(degree). For example, 30 means we hit the area of 18(9 + 18 = 27,
      30 - 27 = 3 < 18). The only abnormal one is piece of 20 points, it is 0~9
      and 351~360.
   3.input:
      There are two inputs in this program. one if capability, how good this
      player in playing dartboard game, from 1 to 100. This will affect the
      rate he hit on his target or miss it. Also, it will affect the point he/
      she is aiming(for fun), if the capability is under 20, he/she will try to
      aim inner bullseye instead of 3x area of 20 points piece. The second input
      is where the player aims to. The default target is 3x area of 20 points
      piece for normal player and inner bullseye for player under 20.(deeply explain how capability affects the result.)
     
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double dis_rand(double mean, double sigma);  //0.0 to 1.0 for distance of dartboard
double angle_rand();  //0 to 360 for angle of dartboard
int getting_score(float distance, float angle);  //get a score between 1 and 60 upon the location of dart on board

int main(){
  srand((long)time(NULL));//seed random function
  /*here are the value user input:
   user_dis: the distance a player aims at
   user_angle: the angle of a player aims at, 
               but since they are not good at this game,
	       we throw this data away,and let angle be random
   capacity: determines the value of sigma.
   */
  float user_dis,user_angle;
  int capacity;

  float distance, angle;//the actual location of dart
  int score = 0;//always remember to initialize 

  //user input process
  printf("Please enter where you aim at:\n");
  printf("distance(range from 0 to 1): ");
  scanf("%f", &user_dis);
  printf("angle(range from 0 to 360): ");
  scanf("%f", &user_angle);
  printf("How good are you playing this game(0 to 100): ");
  scanf("%d", &capacity);

  //change capacity to a valid sigma value;
  float sigma = 10.0 / capacity;
  printf("%f\n",sigma);
  //process the user input to actual location
  distance = dis_rand(user_dis,sigma);
  angle = angle_rand();

  
  //test utilization 
  printf("random distance is: %f\nrandom angle: %f\n", distance,angle);

  //get score by shooting one dart
  score = getting_score(distance, angle);
  printf("the final score is: %d\n", score);
}

//function is inspired and modified by wikipedia box and Muller Algorithms
double dis_rand(double mean, double sigma) {
  double epsilon = 0.000001;
  double two_pi = 2.0*3.14159265358979323846;
  double z;
  double temp1, temp2;
  double result;
  //generate a random number for standard normalize;
  do{
    temp1 = rand()/(double)RAND_MAX;
    temp2 = rand()/(double)RAND_MAX;
  }while( temp1 <= epsilon );
  
  //standard normalize for only one variable
  z = sqrt(-2.0 * log(temp1)) * cos(two_pi * temp2);
  /*
    if(z < 0){
       z = -z;
    }
  */
  
  result = z * sigma + mean;
  //test whether the result is valid
  //the best way is to let angle add 180 degree but hard to implement
  if(result < 0){
    result = -1 * result;
  }
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
  return score;
}
