// libaries
#include <Adafruit_CircuitPlayground.h>

// global variables for sound, setting input and output
volatile bool Leftbutton = 0; // used in interrupt
volatile bool Rightbutton = 0; // used interrupt
volatile bool switchFlag = 0; // used  interrupt
volatile bool Activated = 0; // used in switchFlag if statement
int Color=1; //value that changes when the buttons are pressed
int LevelSayer=1; // prints the level you are on
int RightbuttonPressed=0;// used in an if statement that decreases Color value
int LeftbuttonPressed=0;// used in an if statement that increases Color value
int NextLevel=0; // used to determine what case to run
int switchpin= 7; // used to declare the switch
int FlashcolorSay=1; // used to deterimine if the random color is finshed displaying so the player can choose a color
int Limiter=1; // used to print "level" once
int ScoreNum=0; // starting score number
int Lbutton = 4; // used to declare the left button
int Intro=1; // runs introduction and used to start flashing code
int Rbutton= 5;// used to declare the right button
int ColorChange= 1; // set by the varible color
int ColorFlashDone=0; // used to run the code when the flashing of the random color is done
float midi[127],RandomColor; // float holds number with a decimal point
int ForSoundMath = 440; //440 hz
int Start[7][2]={ // start song notes playing 200ms and 400ms and MIDI numbers
  {86,400},
  {86,200},
  {86,200},
  {86,200},
  {83,200},
  {84,200},
  {86,200}
 };
int Youwon[15][2]={ // Winning song 200ms duration and MIDI numbers
  {65,200},
  {64,200},
  {62,200},
  {64,200},
  {65,200},
  {67,200},
  {69,200},
  {65,200},
  {64,200},
  {62,200},
  {64,200},
  {65,200},
  {67,200},
  {69,400},
  {65,200},
};


void setup() { // Has interrupts, serial print seed, create random numbers,sets pins, and generates MIDI values
CircuitPlayground.begin();
Serial.begin(9600);
randomSeed(analogRead(0));
while(!Serial);// code wont run till serial monitor is open
pinMode(Lbutton,3); // 3 means INPUT_PULLDOWN
pinMode(Rbutton,3); // 3 mean INPUT_PULLDOWN
pinMode(switchpin,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(switchpin),onOFF,CHANGE); // pin,callback,mode
attachInterrupt(digitalPinToInterrupt(Lbutton),Lpressed,FALLING); //...
attachInterrupt(digitalPinToInterrupt(Rbutton),Rpressed,FALLING);//...
generateMIDI(); // Custom function for calculating and storing the frequency value associated for each MIDI pitch number

}

void loop() {
  // prints the instruction, prints score, plays Start song ans sets Intro to zero.
  if(Intro==1){
    Serial.print("In this game a color will flash at you and you will have to cycle through colors to find the one that flashed at you");
    Serial.println("To start the game, tap the nail. To submit the color you that flashed at you, move the switch");
    Serial.println("If the answer is right, the board will show rainbow lights, and if it is wrong, the board will display red checked lights.");
    Serial.println("If you answer the board wrong you will start at level one.");
    delay(200);
    pleasent();
    Serial.print("Score: ");
    Serial.println(ScoreNum);
    delay(1000);
    for(int P = 0; P < sizeof(Start) / sizeof(Start[0]); P++) // Plays a tone from the array related to P and P increases till it reaches the end of the array
    {
      CircuitPlayground.playTone(midi[Start[P][0]], Start[P][1]); 
    }
   CircuitPlayground.clearPixels();
   Intro=0;
  }
  //.....

  if(switchFlag){  // SwitchFlag connected to the interrupt. When pin 7 "switch" has changed activate is set to 1 and switchFlag is set to 0.
    delay(200);
    Activated=1;
    switchFlag= 0;
  } else if(Rightbutton){ //Rightbutton is attached to an interrupt. When button D5 is pressed RightbuttonPressed
    RightbuttonPressed=1;
    delay(1000);
    Rightbutton=0;
  } else if(Leftbutton){ //Leftbutton is attached to an interrupt. When button D4 is pressed LeftbuttonPressed
    LeftbuttonPressed=1;
    delay(1000);
    Leftbutton=0;
  } else {}
  
  if (LeftbuttonPressed){
    ColorChange=++Color; //color increases, color change is being set to that color
    delay(30);
    if(ColorChange > 6){ // if colorchange is greater than 6, set Color to 1. Set ColorChange to new value
     Color=1;
     ColorChange=Color;
    }
    else if(ColorChange < 1){ // color is less than 1 the variable Color is set to zero. Prints color values. set Color to 1. Set ColorChange to new value
      Color=6;
      delay(30);
      ColorChange=Color;
    }
    Serial.print("Color Value: ");
    Serial.println(ColorChange);
    LeftbuttonPressed=0;
  }
  if (RightbuttonPressed){
    delay(30);
    ColorChange=--Color;//color decreases, color change is being set to that color
    if(ColorChange < 1){ // color is less than 1 the variable Color is set to zero. Prints color values. set Color to 1. Set ColorChange to new value
      Color=6;
      delay(30);
      ColorChange=Color;
    }
    else if(ColorChange > 6){ // if colorchange is greater than 6, set Color to 1. Set ColorChange to new value. Print color value
     Color=1;
     delay(30);
     ColorChange=Color;
    }
    Serial.print("Color Value: ");
    Serial.println(ColorChange);
    RightbuttonPressed=0;
  }

  if(Intro==0){ // when the intro has printed the instruction, played the tone, and flashed the opening lights. this code will start
    if(NextLevel<3){ // When level is less than 3 preform the switch case
      switch(NextLevel){// case will run through using the value of NextLevel
        case 0:
          if(Limiter==1){ //makes it print "Level 1:" once
            if(LevelSayer==1){
            Serial.println("Level 1:");
          }
          delay(30);
          RandomColor=random(1,6); // Sets RandomColor to a value between 1 and 6
            if(RandomColor==1){ // RandomColor is equal to 1 all pixels are set to purple
              for(int Q=0;Q<10;Q++){
                CircuitPlayground.setPixelColor(Q,181,3,243);
              }
            }else if(RandomColor==2){// RandomColor is equal to 2 all pixels are set to red
              for(int J=0;J<10;J++){
                CircuitPlayground.setPixelColor(J,255,0,0);
              }
            }else if(RandomColor==3){ // RandomColor is equal to 3 all pixels are set to green
              for(int P=0;P<10;P++){
                CircuitPlayground.setPixelColor(P,0,255,0);
              }
            }else if(RandomColor==4){ // RandomColor is equal to 4 all pixels are set to blue
              for(int S=0;S<10;S++){
                CircuitPlayground.setPixelColor(S,0,0,255);
              }
            }else if(RandomColor==5){ // RandomColor is equal to 5 all pixels are set to yellow
              for(int F=0;F<10;F++){
                CircuitPlayground.setPixelColor(F,242,238,0);
              }
            }else if(RandomColor==6){ // RandomColor is equal to 6 all pixels are set to teal
              for(int G=0;G<10;G++){
                CircuitPlayground.setPixelColor(G,0,232,255);
              }
            }
          delay(1000);
          CircuitPlayground.clearPixels(); // sets all pixels to 0,0,0
          ColorFlashDone=1;
          Limiter=0;
        }
        break;
      case 1:
        if(Limiter==1){ //makes it print "Level 2:" once
        if(LevelSayer==2){
          Serial.println("Level 2:");
        }
        delay(30);
        RandomColor=random(1,6); // Sets RandomColor to a value between 1 and 6
        if(RandomColor==1){
          for(int Q=0;Q<10;Q++){
            CircuitPlayground.setPixelColor(Q,181,3,243); // RandomColor is equal to 1 all pixels are set to purple
          }
        }else if(RandomColor==2){
          for(int J=0;J<10;J++){
            CircuitPlayground.setPixelColor(J,255,0,0); // RandomColor is equal to 2 all pixels are set to red
          }
        }else if(RandomColor==3){
          for(int P=0;P<10;P++){
            CircuitPlayground.setPixelColor(P,0,255,0); // RandomColor is equal to 3 all pixels are set to green
          }
        }else if(RandomColor==4){
          for(int S=0;S<10;S++){
            CircuitPlayground.setPixelColor(S,0,0,255); // RandomColor is equal to 4 all pixels are set to blue
          }
        }else if(RandomColor==5){
          for(int F=0;F<10;F++){
            CircuitPlayground.setPixelColor(F,242,238,0); // RandomColor is equal to 5 all pixels are set to yellow
          }
        }else if(RandomColor==6){
          for(int G=0;G<10;G++){
            CircuitPlayground.setPixelColor(G,0,232,255); // RandomColor is equal to 6 all pixels are set to teal
          }
        }
        delay(600);
        CircuitPlayground.clearPixels(); // sets all pixels to 0,0,0
        ColorFlashDone=1;
        Limiter=0;
        }
        break;
      case 2:
      if(Limiter==1){ //makes it print "Level 3:" once
        if(LevelSayer==3){
          Serial.println("Level 3:");
        }
        delay(30);
      RandomColor=random(1,6); // Sets RandomColor to a value between 1 and 6
      if(RandomColor==1){
        for(int Q=0;Q<10;Q++){
          CircuitPlayground.setPixelColor(Q,181,3,243); // RandomColor is equal to 1 all pixels are set to purple
        }
      }else if(RandomColor==2){
        for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0); // RandomColor is equal to 2 all pixels are set to red
        }
      }else if(RandomColor==3){
        for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0); // RandomColor is equal to 3 all pixels are set to green
        }
      }else if(RandomColor==4){
        for(int S=0;S<10;S++){
          CircuitPlayground.setPixelColor(S,0,0,255); // RandomColor is equal to 4 all pixels are set to blue
        }
      }else if(RandomColor==5){
        for(int F=0;F<10;F++){
          CircuitPlayground.setPixelColor(F,242,238,0); // RandomColor is equal to 5 all pixels are set to yellow
        }
      }else if(RandomColor==6){
        for(int G=0;G<10;G++){
          CircuitPlayground.setPixelColor(G,0,232,255); // RandomColor is equal to 6 all pixels are set to teal
        }
  }
        delay(300);
        CircuitPlayground.clearPixels(); // sets all pixels to 0,0,0
        ColorFlashDone=1;
        Limiter=0;
        }
      default:
        break;
    }
    if(ColorFlashDone){ // When the random color finishes flashing, the code to choose a color begins
      if (FlashcolorSay==1){ // prints the color value and tell the player they can choose a color
        Serial.println("Now choose a color");
        delay(100);
        ColorChange=Color;
        Serial.print("Color Value: ");
        Serial.println(ColorChange);
        delay(100);
        FlashcolorSay=0;
      }
      if(ColorChange==1){
      for(int Q=0;Q<10;Q++){
        CircuitPlayground.setPixelColor(Q,181,3,243); // ColorChange is equal to 1 all pixels are set to purple
      }}else if(ColorChange==2){
        for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0); // ColorChange is equal to 2 all pixels are set to red
        }
      }else if(ColorChange==3){
        for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0); // ColorChange is equal to 3 all pixels are set to green
      }}else if(ColorChange==4){
          for(int S=0;S<10;S++){
            CircuitPlayground.setPixelColor(S,0,0,255); // ColorChange is equal to 4 all pixels are set to blue
      }}else if(ColorChange==5){
          for(int F=0;F<10;F++){
            CircuitPlayground.setPixelColor(F,242,238,0); // ColorChange is equal to 5 all pixels are set to yellow
      }}else if(ColorChange==6){
        for(int G=0;G<10;G++){
            CircuitPlayground.setPixelColor(G,0,232,255); // ColorChange is equal to 6 all pixels are set to teal
      }}}
    if(ColorChange==RandomColor && Activated==1){ // When the choosen color is the same as the random one and the switch postion was changes. Print the choosen color was correct
      Serial.println("Correct!!");
      CircuitPlayground.playTone(midi[86],200);
      ScoreNum=++ScoreNum; // ScoreNum increases by 1
      Serial.print("Score: ");
      Serial.println(ScoreNum);
      delay(2000);
      CircuitPlayground.clearPixels(); // set all pixels to 0,0,0
      NextLevel=++NextLevel; // NextLevel increases by 1
      LevelSayer=++LevelSayer; //LevelSayer increases by 1
      Color=1;
      ColorFlashDone=0;
      FlashcolorSay=1;
      Limiter=1;
      Activated=0;
    }else if(!(ColorChange==RandomColor) && Activated==1){ // When the choosen color is not eqaul to the random value and the switch has changed print that the choosen color is wrong.
      Serial.println("Wrong!!Try again");
      for(int L=0;L<10;L++){ // red and pink lights run accross the circuit board left to right clearing between each lighting
        CircuitPlayground.setPixelColor(L,255,0,0); 
        delay(200);
        CircuitPlayground.setPixelColor(L,199,21,133); 
        delay(100);
        CircuitPlayground.clearPixels(); // set all pixels to 0,0,0
      }
      delay(100);
      for(int D=10;D>0;D--){ // red and pink lights run accross the circuit board right to left clearing between each lighting
        CircuitPlayground.setPixelColor(D,255,0,0); 
        delay(200);
        CircuitPlayground.setPixelColor(D,199,21,133); 
       delay(100);
       CircuitPlayground.clearPixels(); // set all pixels to 0,0,0
      }  
      NextLevel=0;
      LevelSayer=1;
      Limiter=1;
      ScoreNum=0;
      Color=1;
      FlashcolorSay=1;
      ColorFlashDone=0;
      Serial.print("Score: ");
      Serial.println(ScoreNum);
      Activated=0;
    }
    }
     if(NextLevel==3){ // When NextLevel is equal to 3 prints the player has Won and the song YouWon plays
      Serial.println("You won!!!");
      rainbowCycle(100, 10);
      for(int Z = 0; Z < sizeof(Youwon) / sizeof(Youwon[0]); Z++){ // Plays a tone from the array related to Z and Z increases till it reaches the end of the array
       CircuitPlayground.playTone(midi[Youwon[Z][0]], Youwon[Z][1]);
       delay(50);
      }
      exit(0); // ends the program
    }
  }
  
}


void pleasent(){ // All Neopixels are set to a color
  CircuitPlayground.setPixelColor(0,239,62,91); // redish pink
  CircuitPlayground.setPixelColor(1,75,37,109); // purple
  CircuitPlayground.setPixelColor(2,63,100,126); // gray blue
  CircuitPlayground.setPixelColor(3,0,176,178); //teal
  CircuitPlayground.setPixelColor(4,149,212,122); // lime
  CircuitPlayground.setPixelColor(5,250,157,0); //dark purple
  CircuitPlayground.setPixelColor(6,254,171,185); // light pink
  CircuitPlayground.setPixelColor(7,176,0,81); // dark red pink
  CircuitPlayground.setPixelColor(8,103,146,103); // sage green
  CircuitPlayground.setPixelColor(9,172,152,193); // lavender
}
void onOFF(){ // Interrupt relating to the switch ( pin 7) is activated switchFlag is set to 1
  switchFlag = 1; 
}
void Lpressed(){ // Interrupt relating to the Left button ( pin D4) is activated Leftbutton is set to 1
  Leftbutton = 1;
}
void Rpressed(){ // Interrupt relating to the Right button ( pin D5) is activated Rightbutton is set to 1
  Rightbutton = 1; 
}
void rainbowCycle(int currentSpeed, int stripLen) { // myfunction that makes all the pixels cycles through the rainbow
 uint32_t /*  u means unsigned,int means integer,always 32 bits, _t standard*/ offset = millis() / currentSpeed; //millis() returns a number of milliseconds since the device has been on divied by currentspeed
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255)); // pixels that display a color converted by colorwheel from i times 256 divided by stripLen value + offset and 225 *& is a bit wise*
  }
}
void generateMIDI() // converts array values to tones
 {
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (ForSoundMath / 32.0) * pow(2.0, ((x - 9.0) / 12.0)); // 440 is divied by 32 mulitpied by 2.0 raised to the power of an x minus 9.0 divided by 12
  }
 }

//End