#include <Servo.h>
Servo rightArm;
Servo leftArm;
Servo gripper;
Servo headX;
Servo headY;

// ---------------- Servo Pins ----------------
const int RIGHT_SERVO   = 8;
const int LEFT_SERVO    = 9;
const int GRIPPER_SERVO = 7;
const int HEADX_SERVO   = 5;
const int HEADY_SERVO   = 6;

// ---------------- Motor Pins ----------------
const int RIGHT_IN1 = 10;
const int RIGHT_IN2 = 11;
const int LEFT_IN1 = 12;
const int LEFT_IN2 = 13;

// ---------------- Servo Angles ----------------
int rightAngle   = 90;
int leftAngle    = 90;
int gripAngle    = 30;   // 30 = open, 120 = closed
int headXAngle   = 90;   // 0 = left, 180 = right
int headYAngle   = 90;   // 0 = down, 180 = up

const int SERVO_DELAY = 15;

// ---------------- Gripper limits ----------------
const int GRIP_OPEN   = 30;
const int GRIP_CLOSED = 120;

// ---------------- Head limits ----------------
const int HEADX_LEFT   = 40;
const int HEADX_CENTER = 90;
const int HEADX_RIGHT  = 140;

const int HEADY_DOWN   = 60;
const int HEADY_CENTER = 90;
const int HEADY_UP     = 130;

// ---------------- Continuous Talk State ----------------
bool talking = false;
unsigned long lastTalkMove = 0;
int talkInterval = 250;   // randomized each cycle so movement isn't a repeating loop

//-------------------------------------------------
// Generic smooth-move helpers for each servo
//-------------------------------------------------
void smoothRight(int target)
{
  while(rightAngle != target)
  {
    if(rightAngle < target) rightAngle++;
    else rightAngle--;
    rightArm.write(rightAngle);
    delay(SERVO_DELAY);
  }
}
void smoothLeft(int target)
{
  while(leftAngle != target)
  {
    if(leftAngle < target) leftAngle++;
    else leftAngle--;
    leftArm.write(leftAngle);
    delay(SERVO_DELAY);
  }
}
void smoothGrip(int target)
{
  while(gripAngle != target)
  {
    if(gripAngle < target) gripAngle++;
    else gripAngle--;
    gripper.write(gripAngle);
    delay(SERVO_DELAY);
  }
}
void smoothHeadX(int target)
{
  while(headXAngle != target)
  {
    if(headXAngle < target) headXAngle++;
    else headXAngle--;
    headX.write(headXAngle);
    delay(SERVO_DELAY);
  }
}
void smoothHeadY(int target)
{
  while(headYAngle != target)
  {
    if(headYAngle < target) headYAngle++;
    else headYAngle--;
    headY.write(headYAngle);
    delay(SERVO_DELAY);
  }
}

//-------------------------------------------------
// Basic arm gestures
//-------------------------------------------------
void handsUp()
{
  smoothLeft(20);
  smoothRight(160);
}
void handsDown()
{
  smoothLeft(90);
  smoothRight(90);
}
void wave()
{
  handsUp();
  for(int i=0;i<3;i++)
  {
    smoothRight(120);
    smoothRight(160);
  }
  handsDown();
}
void salute()
{
  smoothRight(145);
  delay(600);
  smoothRight(90);
}

//-------------------------------------------------
// Gripper gestures
//-------------------------------------------------
void gripOpen()
{
  smoothGrip(GRIP_OPEN);
}
void gripClose()
{
  smoothGrip(GRIP_CLOSED);
}
void gripSqueeze()
{
  for(int i=0;i<2;i++)
  {
    smoothGrip(GRIP_CLOSED);
    delay(150);
    smoothGrip(GRIP_OPEN + 20);
    delay(150);
  }
  smoothGrip(GRIP_OPEN);
}

//-------------------------------------------------
// Head gestures
//-------------------------------------------------
void headCenter()
{
  smoothHeadX(HEADX_CENTER);
  smoothHeadY(HEADY_CENTER);
}
void lookLeft()
{
  smoothHeadX(HEADX_LEFT);
}
void lookRight()
{
  smoothHeadX(HEADX_RIGHT);
}
void lookUp()
{
  smoothHeadY(HEADY_UP);
}
void lookDown()
{
  smoothHeadY(HEADY_DOWN);
}
void nodYes()
{
  for(int i=0;i<3;i++)
  {
    smoothHeadY(HEADY_UP - 10);
    delay(120);
    smoothHeadY(HEADY_DOWN + 10);
    delay(120);
  }
  smoothHeadY(HEADY_CENTER);
}
void shakeNo()
{
  for(int i=0;i<3;i++)
  {
    smoothHeadX(HEADX_LEFT + 15);
    delay(120);
    smoothHeadX(HEADX_RIGHT - 15);
    delay(120);
  }
  smoothHeadX(HEADX_CENTER);
}
void scanArea()
{
  headCenter();
  lookLeft();
  delay(300);
  lookRight();
  delay(300);
  headCenter();
}
void curiousTilt()
{
  smoothHeadX(HEADX_LEFT + 10);
  smoothHeadY(HEADY_UP - 15);
  smoothRight(115);
  delay(500);
  headCenter();
  smoothRight(90);
}

//-------------------------------------------------
// Personality / combo gestures
//-------------------------------------------------
void greet()
{
  headCenter();
  lookUp();
  wave();
  gripOpen();
  delay(200);
  gripSqueeze();
  headCenter();
}
void happy()
{
  handsUp();
  lookUp();
  left();
  delay(250);
  right();
  delay(250);
  left();
  delay(250);
  stopRobot();
  wave();
  headCenter();
}
void excited()
{
  headCenter();
  handsUp();
  for(int i=0;i<2;i++)
  {
    lookLeft();
    smoothRight(160);
    delay(100);
    lookRight();
    smoothRight(120);
    delay(100);
  }
  gripSqueeze();
  headCenter();
  handsDown();
}
void sad()
{
  smoothHeadY(HEADY_DOWN);
  smoothLeft(70);
  smoothRight(110);
  delay(800);
  headCenter();
  handsDown();
}
void confused()
{
  shakeNo();
  curiousTilt();
  headCenter();
}
void thinking()
{
  lookUp();
  smoothHeadX(HEADX_RIGHT - 10);
  smoothLeft(75);
  delay(700);
  headCenter();
  smoothLeft(90);
}

//-------------------------------------------------
// Continuous talk animation (Solution 1 + 2 + 3)
// Python controls START/STOP. Arduino just plays
// small, randomized, natural-looking micro-moves
// for as long as "talking" stays true.
//-------------------------------------------------
void doRandomTalkMove()
{
  int choice = random(0, 8);   // 0-7, mix of arm + head micro-moves

  switch(choice)
  {
    case 0: smoothLeft(80);               break;   // small left arm dip
    case 1: smoothLeft(95);               break;   // small left arm lift
    case 2: smoothRight(100);             break;   // small right arm dip
    case 3: smoothRight(85);              break;   // small right arm lift
    case 4: smoothHeadX(HEADX_CENTER-10); break;    // tiny look left
    case 5: smoothHeadX(HEADX_CENTER+10); break;    // tiny look right
    case 6: smoothHeadY(HEADY_CENTER+8);  break;    // tiny nod up
    case 7: smoothHeadY(HEADY_CENTER-6);  break;    // tiny nod down
  }
}

void startTalking()
{
  talking = true;
  lastTalkMove = millis();
  talkInterval = random(180, 320);
}

void stopTalking()
{
  talking = false;
  smoothLeft(90);
  smoothRight(90);
  headCenter();
}

//-------------------------------------------------
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));   // seed randomness from floating pin noise

  rightArm.attach(RIGHT_SERVO);
  leftArm.attach(LEFT_SERVO);
  gripper.attach(GRIPPER_SERVO);
  headX.attach(HEADX_SERVO);
  headY.attach(HEADY_SERVO);

  rightArm.write(rightAngle);
  leftArm.write(leftAngle);
  gripper.write(gripAngle);
  headX.write(headXAngle);
  headY.write(headYAngle);

  pinMode(RIGHT_IN1,OUTPUT);
  pinMode(RIGHT_IN2,OUTPUT);
  pinMode(LEFT_IN1,OUTPUT);
  pinMode(LEFT_IN2,OUTPUT);

  stopRobot();
  Serial.println("Robot Ready");
}
//-------------------------------------------------
void loop()
{
  // ---- Non-blocking continuous talk animation ----
  if (talking && (millis() - lastTalkMove > talkInterval))
  {
    lastTalkMove = millis();
    talkInterval = random(180, 320);   // vary timing so it never looks looped
    doRandomTalkMove();
  }

  if(!Serial.available()) return;
  char cmd=Serial.read();
  switch(cmd)
  {
    // ---- Movement ----
    case 'F': forward(); break;
    case 'B': backward(); break;
    case 'L': left(); break;
    case 'R': right(); break;
    case 'S': stopRobot(); break;

    // ---- Arms (manual) ----
    case 'A': smoothLeft(140); break;
    case 'a': smoothLeft(20); break;
    case 'C': smoothRight(160); break;
    case 'c': smoothRight(90); break;
    case 'H': handsUp(); break;
    case 'D': handsDown(); break;

    // ---- Gripper (manual) ----
    case 'g': gripOpen(); break;
    case 'p': gripClose(); break;

    // ---- Head (manual) ----
    case 'i': lookUp(); break;
    case 'k': lookDown(); break;
    case 'j': lookLeft(); break;
    case 'l': lookRight(); break;
    case 'n': headCenter(); break;

    // ---- Talking animation (Python-controlled duration) ----
    case 'T': startTalking(); break;   // start talking loop
    case 't': stopTalking();  break;   // stop talking loop, return neutral

    // ---- Gestures ----
    case 'W': wave(); break;
    case 'X': salute(); break;
    case 'Y': happy(); break;
    case 'N': nodYes(); break;
    case 'M': shakeNo(); break;
    case 'V': scanArea(); break;
    case 'U': curiousTilt(); break;
    case 'Z': greet(); break;
    case 'E': excited(); break;
    case 'w': sad(); break;
    case 'Q': confused(); break;
    case 'y': thinking(); break;   // lowercase y = thinking (T/t reserved for talk loop now)
  }
}
//-------------------------------------------------
void forward()
{
  digitalWrite(RIGHT_IN1,HIGH);
  digitalWrite(RIGHT_IN2,LOW);
  digitalWrite(LEFT_IN1,HIGH);
  digitalWrite(LEFT_IN2,LOW);
}
void backward()
{
  digitalWrite(RIGHT_IN1,LOW);
  digitalWrite(RIGHT_IN2,HIGH);
  digitalWrite(LEFT_IN1,LOW);
  digitalWrite(LEFT_IN2,HIGH);
}
void left()
{
  digitalWrite(RIGHT_IN1,HIGH);
  digitalWrite(RIGHT_IN2,LOW);
  digitalWrite(LEFT_IN1,LOW);
  digitalWrite(LEFT_IN2,HIGH);
}
void right()
{
  digitalWrite(RIGHT_IN1,LOW);
  digitalWrite(RIGHT_IN2,HIGH);
  digitalWrite(LEFT_IN1,HIGH);
  digitalWrite(LEFT_IN2,LOW);
}
void stopRobot()
{
  digitalWrite(RIGHT_IN1,LOW);
  digitalWrite(RIGHT_IN2,LOW);
  digitalWrite(LEFT_IN1,LOW);
  digitalWrite(LEFT_IN2,LOW);
}
