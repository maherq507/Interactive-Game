// Interactive Cyclone Game for Arduino Circuit 
// Made by Quinn Maher

#include <Adafruit_CircuitPlayground.h>

//Global variables 

float midi[127];
int A_four = 440;  // a is 440 hz...

const byte buttonR = 4; //Button R declaration
const byte buttonL = 5; //Button L declaration

volatile bool butRflag = false; // Button R flag 
volatile bool butLflag = false; // Button L flag 

int randomT; //Declaring target
int playerDot; //Declaring playerDot
int gameLevel; //Declaring game level
int scaledLevel;

void setup() {

CircuitPlayground.begin();
Serial.begin(9600);
generateMIDI();
delay(5000);
Serial.println("Welcome to the game, you are currently on level 1");
pinMode(buttonR, INPUT_PULLDOWN);
pinMode(buttonL, INPUT_PULLDOWN);
attachInterrupt(digitalPinToInterrupt(buttonR), butR, FALLING);
attachInterrupt(digitalPinToInterrupt(buttonL), butL, FALLING);

randomT = random(0,10); //Setting the target
gameLevel = 500; //Setting the level as the lowest

}



void loop() {

  mainGame();

}




//Main game system 

void mainGame() {

  for(playerDot = 0; playerDot < 10; playerDot++ ) {
    CircuitPlayground.setPixelColor(randomT, 0xFFFFFF);  
    CircuitPlayground.setPixelColor(playerDot, 0x00FFFF);  // Set color from first half then replace it with second color
    delay(gameLevel);
    CircuitPlayground.setPixelColor(playerDot, 0x000000);  

  if (butRflag || butLflag == true) {
      butRflag = false;  // reset so it only triggers once
      butLflag = false;

      if (randomT == playerDot) {
        Serial.println("SUCCESS! You have made it to level ");
        scaledLevel = map(gameLevel, 50, 500, 1, 9);
        Serial.println(10 - scaledLevel + 1);
        winLights();
        randomT = random(0, 10); //Redeclare the random target
        gameLevel = gameLevel - 50; // Make game level harder
        if (gameLevel < 50) {
          rainbowCycle(20,10);
        }
        
      } else {
        Serial.println("MISSED! YOU LOSE!");
        loseLights();
        
      }
    }
  }
}



//Win, Lose & End light systems

void winLights() {

  CircuitPlayground.playTone(midi[73], 300);

  for(int i = 0; i < 10; i++) {                 // Code controlling green flash 
  CircuitPlayground.setPixelColor(i, 0x00FF00);
  } delay(500);
  for(int a = 0; a < 10; a++) {
  CircuitPlayground.setPixelColor(a, 0x000000);
  } delay(100);
  for(int b = 0; b < 10; b++) {
  CircuitPlayground.setPixelColor(b, 0x00FF00);
  } delay(500);
  for(int c = 0; c < 10; c++) {
  CircuitPlayground.setPixelColor(c, 0x000000);
  } delay(100);
  for (int d = 0; d < 10; d++) {
  CircuitPlayground.setPixelColor(d, 0x00FF00);
  }delay(500);

  CircuitPlayground.clearPixels(); //Clears all pixels before going back to game 
  
  return; //Break out of win lights and go back to game
}


void loseLights() {

 CircuitPlayground.playTone(midi[50], 300);

 for(int i = 0; i < 10; i++) {                 // Code controlling red flash 
  CircuitPlayground.setPixelColor(i, 0xFF0000);
  } delay(500);
  for(int a = 0; a < 10; a++) {
  CircuitPlayground.setPixelColor(a, 0x000000);
  } delay(100);
  for(int b = 0; b < 10; b++) {
  CircuitPlayground.setPixelColor(b, 0xFF0000);
  } delay(500);
  for(int c = 0; c < 10; c++) {
  CircuitPlayground.setPixelColor(c, 0x000000);
  } delay(100);
  for (int d = 0; d < 10; d++) {
  CircuitPlayground.setPixelColor(d, 0xFF0000);
  }delay(500);

  CircuitPlayground.clearPixels(); //Clears all pixels before going back to game 
  
  return; //Break out of lose lights and go back to game
}


//End of game lights 

void rainbowCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  
   for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
  Serial.println("CONGRATULATIONS YOU COMPLETED THE GAME!");
  delay(5000);
  gameLevel = 500;
  CircuitPlayground.clearPixels(); 
  return; //Break out of end lights and go back to game

}



// Button interrupts

void butR() {
  butRflag = true;
}

void butL() {
  butLflag = true;
}

void generateMIDI() {
  for (int x = 0; x < 127; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
  }
}
