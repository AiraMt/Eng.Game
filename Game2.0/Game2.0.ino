#include <Adafruit_CircuitPlayground.h>

volatile bool Leftbutton = 0;
volatile bool Rightbutton = 0;
volatile bool switchFlag = 0; 
volatile bool Activated = 0;
int Color=1;
int LevelSayer=1;
int RightbuttonPressed=0;
int LeftbuttonPressed=0;
int levelup=0;
int NextLevel=0;
int switchpin= 7;
int FlashcolorSay=1;
int Limiter=1;
int Sayer=1;
int ScoreNum=0;
int Lbutton = 4;
int Intro=1; 
int Rbutton= 5;
int TheColor=0;
int ColorChange= 1;
int ColorFlashDone=0;
float midi[127],RandomColor;
int ForSoundMath = 440;
int Start[7][2]={
  {86,400},
  {86,200},
  {86,200},
  {86,200},
  {83,200},
  {84,200},
  {86,200}
 };
int Youwon[15][2]={
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


void setup() {
CircuitPlayground.begin();
Serial.begin(9600);
randomSeed(analogRead(0));
while(!Serial);
pinMode(Lbutton,3);
pinMode(Rbutton,3);
pinMode(switchpin,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(switchpin),onOFF,CHANGE);
attachInterrupt(digitalPinToInterrupt(Lbutton),Lpressed,FALLING);
attachInterrupt(digitalPinToInterrupt(Rbutton),Rpressed,FALLING);
generateMIDI();

}

void loop() {
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
    for(int P = 0; P < sizeof(Start) / sizeof(Start[0]); P++) 
    {
      CircuitPlayground.playTone(midi[Start[P][0]], Start[P][1]); 
    }
   CircuitPlayground.clearPixels();
   Intro=0;
  }

  if(switchFlag){
    delay(200);
    Activated=1;
    switchFlag= 0;
  } else if(Rightbutton){
    RightbuttonPressed=1;
    delay(1000);
    Rightbutton=0;
  } else if(Leftbutton){
    LeftbuttonPressed=1;
    delay(1000);
    Leftbutton=0;
  } else {}
  
  if (LeftbuttonPressed){
    ColorChange=++Color; //color increases, color change is being set to that color
    delay(30);
    if(ColorChange > 6){ // if colorchange is greater than 6, it 
     Color=1;
     ColorChange=Color;
    }
    else if(ColorChange < 1){
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
    ColorChange=--Color;
    if(ColorChange < 1){
      Color=6;
      delay(30);
      ColorChange=Color;
    }
    else if(ColorChange > 6){
     Color=1;
     delay(30);
     ColorChange=Color;
    }
    Serial.print("Color Value: ");
    Serial.println(ColorChange);
    RightbuttonPressed=0;
  }

  if(Intro==0){
    if(NextLevel<3){
      switch(NextLevel){
        case 0:
          if(Limiter==1){
            if(LevelSayer==1){
            Serial.println("Level 1:");
          }
          delay(30);
          RandomColor=random(1,6);
            if(RandomColor==1){
              for(int Q=0;Q<10;Q++){
                CircuitPlayground.setPixelColor(Q,181,3,243);
              }
            }else if(RandomColor==2){
              for(int J=0;J<10;J++){
                CircuitPlayground.setPixelColor(J,255,0,0);
              }
            }else if(RandomColor==3){
              for(int P=0;P<10;P++){
                CircuitPlayground.setPixelColor(P,0,255,0);
              }
            }else if(RandomColor==4){
              for(int S=0;S<10;S++){
                CircuitPlayground.setPixelColor(S,0,0,255);
              }
            }else if(RandomColor==5){
              for(int F=0;F<10;F++){
                CircuitPlayground.setPixelColor(F,242,238,0);
              }
            }else if(RandomColor==6){
              for(int G=0;G<10;G++){
                CircuitPlayground.setPixelColor(G,0,232,255);
              }
            }
          delay(1000);
          CircuitPlayground.clearPixels();
          ColorFlashDone=1;
          Limiter=0;
        }
        break;
      case 1:
        if(Limiter==1){ // makes it print once
        if(LevelSayer==2){
          Serial.println("Level 2:");
        }
        delay(30);
        RandomColor=random(1,6);
        if(RandomColor==1){
          for(int Q=0;Q<10;Q++){
            CircuitPlayground.setPixelColor(Q,181,3,243); //purple
          }
        }else if(RandomColor==2){
          for(int J=0;J<10;J++){
            CircuitPlayground.setPixelColor(J,255,0,0); //Red
          }
        }else if(RandomColor==3){
          for(int P=0;P<10;P++){
            CircuitPlayground.setPixelColor(P,0,255,0); //Green
          }
        }else if(RandomColor==4){
          for(int S=0;S<10;S++){
            CircuitPlayground.setPixelColor(S,0,0,255); //blue
          }
        }else if(RandomColor==5){
          for(int F=0;F<10;F++){
            CircuitPlayground.setPixelColor(F,242,238,0); //yellow
          }
        }else if(RandomColor==6){
          for(int G=0;G<10;G++){
            CircuitPlayground.setPixelColor(G,0,232,255); //teal
          }
        }
        delay(600);
        CircuitPlayground.clearPixels();
        ColorFlashDone=1;
        Limiter=0;
        }
        break;
      case 2:
      if(Limiter==1){
        if(LevelSayer==3){
          Serial.println("Level 3:");
        }
        delay(30);
      RandomColor=random(1,6);
      if(RandomColor==1){
        for(int Q=0;Q<10;Q++){
          CircuitPlayground.setPixelColor(Q,181,3,243);
        }
      }else if(RandomColor==2){
        for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0);
        }
      }else if(RandomColor==3){
        for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0);
        }
      }else if(RandomColor==4){
        for(int S=0;S<10;S++){
          CircuitPlayground.setPixelColor(S,0,0,255);
        }
      }else if(RandomColor==5){
        for(int F=0;F<10;F++){
          CircuitPlayground.setPixelColor(F,242,238,0);
        }
      }else if(RandomColor==6){
        for(int G=0;G<10;G++){
          CircuitPlayground.setPixelColor(G,0,232,255);
        }
  }
        delay(300);
        CircuitPlayground.clearPixels();
        ColorFlashDone=1;
        Limiter=0;
        }
      default:
        break;
    }
    if(ColorFlashDone){
      if (FlashcolorSay==1){
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
        CircuitPlayground.setPixelColor(Q,181,3,243);
      }}else if(ColorChange==2){
        for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0);
        }
      }else if(ColorChange==3){
        for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0);
      }}else if(ColorChange==4){
          for(int S=0;S<10;S++){
            CircuitPlayground.setPixelColor(S,0,0,255);
      }}else if(ColorChange==5){
          for(int F=0;F<10;F++){
            CircuitPlayground.setPixelColor(F,242,238,0);
      }}else if(ColorChange==6){
        for(int G=0;G<10;G++){
            CircuitPlayground.setPixelColor(G,0,232,255);
      }}}
    if(ColorChange==RandomColor && Activated==1){
      Serial.println("Correct!!");
      ScoreNum=++ScoreNum;
      Serial.print("Score: ");
      Serial.println(ScoreNum);
      delay(2000);
      CircuitPlayground.clearPixels();
      NextLevel=++NextLevel;
      LevelSayer=++LevelSayer;
      Color=1;
      ColorFlashDone=0;
      FlashcolorSay=1;
      Limiter=1;
      Activated=0;
    }else if(!(ColorChange==RandomColor) && Activated==1){
      Serial.println("Wrong!!Try again");
      for(int L=0;L<10;L++){
        CircuitPlayground.setPixelColor(L,255,0,0); 
        delay(200);
        CircuitPlayground.setPixelColor(L,199,21,133); 
        delay(100);
        CircuitPlayground.clearPixels();
      }
      delay(100);
      for(int D=10;D>0;D--){
        CircuitPlayground.setPixelColor(D,255,0,0); 
        delay(200);
        CircuitPlayground.setPixelColor(D,199,21,133); 
       delay(100);
       CircuitPlayground.clearPixels();
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
     if(NextLevel==3){
      Serial.println("You won!!!");
      rainbowCycle(100, 10);
      for(int Z = 0; Z < sizeof(Youwon) / sizeof(Youwon[0]); Z++){
       CircuitPlayground.playTone(midi[Youwon[Z][0]], Youwon[Z][1]);
       delay(50);
      }
      exit(0); // ends the program
    }
  }
  
}


void pleasent(){
  CircuitPlayground.setPixelColor(0,239,62,91);
  CircuitPlayground.setPixelColor(1,75,37,109);
  CircuitPlayground.setPixelColor(2,63,100,126);
  CircuitPlayground.setPixelColor(3,0,176,178);
  CircuitPlayground.setPixelColor(4,149,212,122);
  CircuitPlayground.setPixelColor(5,250,157,0);
  CircuitPlayground.setPixelColor(6,254,171,185);
  CircuitPlayground.setPixelColor(7,176,0,81);
  CircuitPlayground.setPixelColor(8,103,146,103);
  CircuitPlayground.setPixelColor(9,172,152,193);
}
void onOFF(){
  switchFlag = 1; 
}
void Lpressed(){
  Leftbutton = 1;
}
void Rpressed(){
  Rightbutton = 1; 
}
void rainbowCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
}
void generateMIDI()
 {
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (ForSoundMath / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
 }

//End