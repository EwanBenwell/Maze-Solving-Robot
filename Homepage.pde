import processing.serial.*;//import the libary allowing communication with arduino
import controlP5.*; //import the libary to design ui objects such as buttons

ControlP5 cp5;//create a Control cp5 object

Serial port;

void setup(){
  size(700, 600); //create the size of the gui window (x ,y)
  printArray(Serial.list()); //prints all available serial ports
  port = new Serial(this, "COM1", 9600); //allow communication with physical port 1, at a bitrate of 9600
  cp5 = new ControlP5(this);
  cp5.addButton("Red") //create a button to trun on the red LED
   .setPosition(250,90)
   .setSize(75, 53);
   
  cp5.addButton("Blue") //create a button to turn on the blue LED
   .setPosition(400,90)
   .setSize(75, 53);

  cp5.addButton("Off") //create a button to turn of all LEDs
   .setPosition(550, 90)
   .setSize(75, 53);

  cp5.addButton("Maze")//create a button to switch the device to navigation mode
    .setPosition(250, 320)
    .setSize(75,53);
    
  cp5.addButton("NoMaze")//create a button to allow the device to roam freely
    .setPosition(400, 320)
    .setSize(75,53);
}

void draw(){
  background(150, 150 ,150); //set the background colour of the display (r, g, b)
  text ("MAZE SOLVING ROBOT", 175, 50); // add text and it's position to the display (text, x, y)
  fill(100, 100, 150); //text colour
  textSize(25);
  text("LED Control:", 75, 125);
  text("Options:",75,350);
}

void Red(){
  port.write('r'); //when the 'red' button is clicked, send an 'r' character to the arduino serial port
}

void Blue(){
  port.write('b');//when the 'blue' button is clicked, send an 'b' character to the arduino serial port
}

void Off(){
  port.write('f');//when the 'off' button is clicked, send an 'f' character to the arduino serial port
}

void Maze(){
  port.write('y');
}

void NoMaze(){
  port.write('n');
}
