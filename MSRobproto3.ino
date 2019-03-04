#include <AFMotor.h> //import the adafruit libary
#define trigPinF 7 
#define echoPinF 6
#define trigPinL 3
#define echoPinL 2
#define trigPinR 4
#define echoPinR 5 // define the location of each sensor pin
AF_DCMotor motor1(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2,MOTOR12_8KHZ); //define the location and frequencies of each motor 
String firstRunS; //create the first string to store the turns 
boolean Navigated = false; //set the variable to test whether the maze has been navigated or not
int turns = 0; //create a counter for a number of turns
char firstRunA[150] = {'S'};//create the array to store the turns
boolean Optimised = false; //set the variable to test whether the path has been simplified or not
String optimisedRunS; //create the string to add the simplified turns to
char optimisedRunA[150] = {'S'}; //create the array to store the optimised path 
int a; //create the variable that will count in the first for loop
int b; //create the variable that will count in the second for loop
boolean Maze = true; //create the variable to give the user the option of not using a maze


void setup() { //this code will run once whenever the device is first switched on
 Serial.begin(9600);
  pinMode(trigPinF, OUTPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(trigPinR, OUTPUT); //allow to trigger pins to give an output
  pinMode(echoPinF, INPUT);
  pinMode(echoPinL, INPUT);
  pinMode(echoPinR, INPUT); //allow the echo pins to recieve and input
  pinMode(12, OUTPUT); //allow the red LED to output
  pinMode(13, OUTPUT); //allow the blue LED to output
  motor1.setSpeed(120);
  motor2.setSpeed(120); //set the speed of each motor
     
}

void loop() { //this code will continue as long as the device is on
  long DurationF, DistanceF; 
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2); //clear the previous data from the trig pin
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW); //send a pulse of sound out of the sensor.  
  DurationF = pulseIn(echoPinF, HIGH); //measure the time taken for the sound wave to return to the sensor.
  DistanceF = (DurationF/2) / 29.1; //convert the time to distance
  
  long DurationL, DistanceL; //repeat the procdeure for the other sensors.
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW); 
  DurationL = pulseIn(echoPinL, HIGH); 
  DistanceL = (DurationL/2) / 29.1;

  long DurationR, DistanceR; 
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW); 
  DurationR = pulseIn(echoPinR, HIGH); 
  DistanceR = (DurationR/2) / 29.1; 

  if(Serial.available()){ //check if data can be read at the serial ports
    char val = Serial.read();
    if (val == 'r') //if data recieved is "r"
    {
      digitalWrite(12, HIGH); //turn on red LED
    }
    if (val == 'b')//if data recieved is "b"
    {
      digitalWrite(13, HIGH); //turn on blue LED
    }  
    if (val == 'f')//if data recieved is "f"
    {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW); //turn off both LEDs
    }
    if (val == 'y')//if data recieved is "y"
    {
      Maze = true; //the user is using the default mode
    }
    if (val == 'n')//if data recieved is "n"
    {
      Maze = false;  //the user wishes to use the device without a maze
    }  

  while (Navigated = false and Maze = true) { //as long as the maze is NOT solved and the user wants to use a maze
    if (DistanceR < 1 and DistanceL < 1 and DistanceF > 1) //as long as both walls are detected and the way is open, move forward.
    {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
      else if (DistanceF < 1 and DistanceR < 1 and DistanceL <1) //if there is a dead end, turn around.
      {
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        delay(2000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'B';
        turns = turns+1;
      }
      else if (DistanceF > 1 and DistanceR > 1 and DistanceL < 1) //if the robot can turn right or continue straight on, turn right
      {
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);        
        firstRunS += 'R';
        turns = turns+1;
      }
      else if (DistanceF > 1 and DistanceR < 1 and DistanceL > 1) //if the robot can turn left or continue straight, continue straight
      {
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'S';
        turns = turns+1;  
      }
      else if (DistanceF > 1 and DistanceR > 1 and DistanceL > 1) //if there is a three-way crossroads, turn right
      {
        motor1.run(FORWARD);
        motor1.run(BACKWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'R';
        turns = turns+1;
      }
      else if (DistanceF < 1 and DistanceR < 1 and DistanceL > 1) //If there is only a left turn possible, turn left
      {
        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'L';
        turns = turns+1;
      }
      else if (DistanceF < 1 and DistanceR > 1 and DistanceL < 1) //If there is only a right turn possible, turn right
      {
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'R';
        turns = turns+1;
      }
      else if (DistanceF < 1 and DistanceR > 1 and DistanceL > 1) //if there is a two-way crossroads, turn right
      {
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        delay(1000);
        motor1.run(FORWARD);
        motor1.run(FORWARD);
        firstRunS += 'R';
        turns = turns+1;
      }
      else
      {
        motor1.run(RELEASE);
        motor2.run(RELEASE); //if the end of the maze is reached, stop moving
        Navigated = true;
        firstRunS.toCharArray(firstRunA, 100);//convert the string of turns into an array
        
      }
  }
     while (Navigated = true and Maze = true)
     {
       while (Optimised = false)
       {                        //once the maze has been solved and is not yet simplified
         if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "RBL")
         {
          optimisedRunS += "S";
          a = a+1;
         }
          else if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "RBS")
          {
           optimisedRunS += "L";
           a = a+1;
          }
          else if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "LBR")
          {
           optimisedRunS += "B";
           a = a+1; 
          }
          else if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "SBR")
          {
           optimisedRunS += "L";
           a = a+1;
          }
          else if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "SBS")
          {
           optimisedRunS += "B";
           a = a+1;
          }
          else if (firstRunA[a] + firstRunA[a+1] + firstRunA[a+2] == "RBR")
          {
           optimisedRunS += "S"; //compare the next three entries in the array against all possible simplifications
          } 
          else
          { 
           Optimised = true; //if no more simplifications can be made, the optimal route has been found and the optimised array can be created
           optimisedRunS.toCharArray(optimisedRunA, 100);
          }
        }
       }
       while (Optimised = true and Maze = true)//follow instructions as long as the route has been optimised 
       {
            if (DistanceF < 1 and DistanceR < 1 and DistanceL < 1) //as long as the path is straight, the array doesn't need to be read
            {
              motor1.run(FORWARD);
              motor2.run(FORWARD);  
            }
            else //if there is any turn in the maze, check what the next turn in the array is and execute that movement.
            {
              if (optimisedRunA[b] == "R") 
               {
                motor1.run(FORWARD);
                motor2.run(BACKWARD);
                delay(1000);
                motor1.run(FORWARD);
                motor1.run(FORWARD);
                b = b+1;  
               }
               else if (optimisedRunA[b] == "S")
               {
                motor1.run(FORWARD);
                motor2.run(FORWARD);
                b = b+1;              
               }
               else if (optimisedRunA[b] == "B")
               {
                motor1.run(FORWARD);
                motor2.run(BACKWARD);
                delay(2000);
                motor1.run(FORWARD);
                motor2.run(FORWARD);
                b = b+1;
               }
               else if (optimisedRunA[b] == "L")
               {
                motor1.run(BACKWARD);
                motor2.run(FORWARD);
                delay(1000);
                motor1.run(FORWARD);
                motor2.run(FORWARD);
                b = b+1;
               }
            }
          }
       }
     }
  if Maze = false{ //if the user doesn't want to use a maze, the device will run as it did in the first prototype
    if (DistanceF < 5){
    motor1.run(FORWARD);
    motor2.run(BACKWARD); //If there is an object close to the sensor, turn around until no longer facing it...
  }
  else {
    motor1.run(FORWARD);
    motor2.run(FORWARD); //...otherwise continue moving fowards    
  }
  }
  
}          

