#include <Adafruit_CircuitPlayground.h>

//Global variables 

const byte buttonR = 5; //Button R declaration
const byte buttonL = 4; //Button L declaration

volatile bool butRflag = false; // Button R flag 
volatile bool butLflag = false; // Button L flag 

int randomT = random(0,10); //Global variable for random target
volatile int playerDot = 0;


void setup() {

CircuitPlayground.begin();
Serial.begin(9600);
pinMode(buttonR, INPUT_PULLDOWN);
pinMode(buttonL, INPUT_PULLDOWN);
attachInterrupt(digitalPinToInterrupt(buttonR), butR, FALLING);
attachInterrupt(digitalPinToInterrupt(buttonL), butL, FALLING);

}

void loop() {

  // Main game start calling it's function
  
  mainGame();
  Serial.println(playerDot);

  
  // Logic calling both win and lose lights 

}



// Button interrupts

void butR() {
  butRflag = true;
}

void butL() {
  butLflag = true;
}

//All light systems, target, win, lose, etc

void mainGame() {


  for(int playerDot = 0; playerDot < 10; ++playerDot ) {
    CircuitPlayground.setPixelColor(randomT, 0xFFFFFF);  
    CircuitPlayground.setPixelColor(playerDot, 0x00FFFF);  // Set color from first half then replace it with second color
    delay(300);
    CircuitPlayground.setPixelColor(playerDot, 0x000000);  
    
  }


}


void winLights() {

}


void loseLights() {

}

