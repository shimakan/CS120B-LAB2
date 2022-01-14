// C++ code
/*        Your Name & E-mail: David Gonzalez, dgonz162@ucr.edu

*          Lab Section: 021

*         Assignment: Lab 2  Exercise 6

*         Exercise Description: Fuel lvl stored in A0-A3 and is read from a
        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
         
*         Demo Link: 

*/
enum SM_states { SM_SMStart, IN, OUTPUT_LED} SM_state;
unsigned char count = 0x0;
const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;

int a = 0x00;
int a0, a1, a2, a3;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  Serial.begin(9600);
}

void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a3 = (a >> 3) & 0x01;
  a2 = (a >> 2) & 0x01;
  a1 = (a >> 1) & 0x01;
  a0 = (a >> 0) & 0x01;
  digitalWrite(A0,a0);
  digitalWrite(A1,a1);
  digitalWrite(A2,a2);
  digitalWrite(A3,a3);
}

void resetB()
{
  digitalWrite(b6,LOW);
  digitalWrite(b5,LOW);
  digitalWrite(b4,LOW);
  digitalWrite(b3,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}

void writeToB()
{
  if (a == 1 || a == 2){
    resetB();
    digitalWrite(b6,HIGH);
    digitalWrite(b5,HIGH);
  }
  else if (a == 3 || a == 4){
    resetB();
    digitalWrite(b6,HIGH);
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
  }
  else if (a == 5 || a == 6){
    resetB();
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
  }
  else if (a == 7 || a == 8 || a == 9){
    resetB();
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
  }
  else if (a == 10 || a == 11 || a == 12){
    resetB();
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
    digitalWrite(b1,HIGH);
  }
  else if (a == 13 || a == 14 || a == 15){
    resetB();
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b0,HIGH);
  }
}

void TickFct_SM()
{
  switch(SM_state){
    case SM_SMStart:
      SM_state = IN;
      break;
    case IN:
    SM_state = OUTPUT_LED;
    break;

    case OUTPUT_LED:
    SM_state = IN;
    break;
    
    default:
      SM_state = SM_SMStart;
  }//transitions
  
  switch(SM_state){
    case IN:
    readData();
    break;
    
    case OUTPUT_LED:
        writeToB();
    break;
    
    default:
    break;
  }//actions
}

void loop()
{
  TickFct_SM();
}
