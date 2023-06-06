#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
AsyncDelay delay_4s;

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
volatile bool IntroDone= 1; 
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
delay_4s.start(4000, AsyncDelay::MILLIS);

}

void loop() {
  if(Intro==1 && delay_4s.isExpired()){
    Serial.print("In this game you will receive a color and using the buttons and switch you will make the values of RGB to the color you are given.");
    Serial.println(" To submit your value answers both of the buttons will be pressed at the same time.");
    Serial.println("To see the color again, the nail will need to be tapped. If the answer is right, the board will show rainbow lights, and if it is wrong, the board will display red checked lights.");
    Serial.println("If you answer the board wrong three times, you will start at level one.");
    delay(200);
    Pleasent();
    Serial.print("Score: ");
    Serial.println(ScoreNum);
    delay(1000);
    for(int P = 0; P < sizeof(Start) / sizeof(Start[0]); P++) 
    {
      CircuitPlayground.playTone(midi[Start[P][0]], Start[P][1]); 
    }
   IntroDone=0;
   CircuitPlayground.clearPixels();
   Intro=0;
  }

  if(switchFlag){
    delay(5);
    Activated=1;
    delay(200);
    switchFlag= 0;
  }
  if(Rightbutton){
    RightbuttonPressed=1;
    delay(1000);
    Rightbutton=0;
  }
    if(Leftbutton){
    LeftbuttonPressed=1;
    delay(1000);
    Leftbutton=0;
  }
  if (LeftbuttonPressed){
    ColorChange=++Color;
    delay(30);
    if(ColorChange > 6){
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

  if(IntroDone==0){
    if(NextLevel<3){
    switch(NextLevel){
      case 0:
        if(Limiter==1){
        if(LevelSayer==1){
          Serial.println("Level 1:");
        }
        RandomColor= random(1,6);
        if(RandomColor==1){
          for(int Q=0;Q<10;Q++){
          CircuitPlayground.setPixelColor(Q,181,3,243);
        }}else if(RandomColor==2){
          for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0);
        }}else if(RandomColor==3){
          for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0);
       }}elseif(RandomColor==4){
          for(int S=0;S<10;S++){
          CircuitPlayground.setPixelColor(S,0,0,255);
        }}else if(RandomColor==5){
          for(int F=0;F<10;F++){
          CircuitPlayground.setPixelColor(F,242,238,0);
        }}else if(RandomColor==6){
          for(int G=0;G<10;G++){
          CircuitPlayground.setPixelColor(G,0,232,255);
        }}
        delay(1000);
        CircuitPlayground.clearPixels();
        ColorFlashDone=1;
        Limiter=0;
        }
      break;
      case 1:
        if(Limiter==1){
        if(LevelSayer==2){
          Serial.println("Level 2:");
        }
        RandomColor=random(1,6);
        if(RandomColor==1){
          for(int Q=0;Q<10;Q++){
          CircuitPlayground.setPixelColor(Q,181,3,243);
      }}else if(RandomColor==2){
          for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0);
        }}else if(RandomColor==3){
          for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0);
       }}else if(RandomColor==4){
          for(int S=0;S<10;S++){
          CircuitPlayground.setPixelColor(S,0,0,255);
        }}else if(RandomColor==5){
          for(int F=0;F<10;F++){
          CircuitPlayground.setPixelColor(F,242,238,0);
        }}else if(RandomColor==6){
          for(int G=0;G<10;G++){
          CircuitPlayground.setPixelColor(G,0,232,255);
        }}
        delay(850);
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
        RandomColor=random(1,6);
        if(RandomColor==1){
          for(int Q=0;Q<10;Q++){
          CircuitPlayground.setPixelColor(Q,181,3,243);
      }}else if(RandomColor==2){
          for(int J=0;J<10;J++){
          CircuitPlayground.setPixelColor(J,255,0,0);
        }}else if(RandomColor==3){
          for(int P=0;P<10;P++){
          CircuitPlayground.setPixelColor(P,0,255,0);
       }}else if(RandomColor==4){
          for(int S=0;S<10;S++){
          CircuitPlayground.setPixelColor(S,0,0,255);
        }}else if(RandomColor==5){
          for(int F=0;F<10;F++){
          CircuitPlayground.setPixelColor(F,242,238,0);
        }}else if(RandomColor==6){
          for(int G=0;G<10;G++){
          CircuitPlayground.setPixelColor(G,0,232,255);
        }}
        delay(750);
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
    }
  }
  
}

void Pleasent(){
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