//C++ code
/*        Your Name & E-mail: David Gonzalez, dgonz162@ucr.edu

*          Lab Section: 021

*         Assignment: Lab 2  Exercise 2


*         Exercise Description: [optional - include for your own benefit]

*         I acknowledge all content contained herein, excluding template or example code, is my own original work.

*         Demo Link: 

*/
enum SM_states { SM_SMStart, COMPARE, EQUAL, greater, less} SM_state;

const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;
int a = 0x00;
int a0, a1, a2, a3, a4, a5, a6, a7;
void setup()
{
  SM_state = SM_SMStart;
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  Serial.begin(9600);
}

void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a7 = a >> 7;
  a6 = (a >> 6) & 0x01;
  a5 = (a >> 5) & 0x01;
  a4 = (a >> 4) & 0x01;
  a3 = (a >> 3) & 0x01;
  a2 = (a >> 2) & 0x01;
  a1 = (a >> 1) & 0x01;
  a0 = (a >> 0) & 0x01;
}

void resetB()
{
  digitalWrite(b7,LOW);
  digitalWrite(b6,LOW);
  digitalWrite(b5,LOW);
  digitalWrite(b4,LOW);
  digitalWrite(b3,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}

void writeToB(unsigned char temp)
{
  if ((temp>>7) & 0x01){digitalWrite(b7,HIGH);}
  if ((temp>>6) & 0x01){digitalWrite(b6,HIGH);}
  if ((temp>>5) & 0x01){digitalWrite(b5,HIGH);}
  if ((temp>>4) & 0x01){digitalWrite(b4,HIGH);}
  if ((temp>>3) & 0x01){digitalWrite(b3,HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(b2,HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
  if (temp & 0x01){digitalWrite(b0,HIGH);}
}
unsigned char GetBit(int x, int k) {

   return ((x & (0x01 << k)) != 0);

}

void check_equality(){
        readData();
        
        //check equality
        if( GetBit(a,3)==GetBit(a,1) && GetBit(a,2)==GetBit(a,0) ){
          SM_state = EQUAL;
          //return EQUAL;
        }
        //B0 > B1 ?
        else if( (a&0x03) > (a>>2)&0x03 && !(GetBit(a,3)==GetBit(a,1) && GetBit(a,2)==GetBit(a,0))){
          SM_state = greater;
          //return greater;
        }
        //B0 < B1
        else if( (a&0x03) < (a>>2)&0x03 && !(GetBit(a,3)==GetBit(a,1) && GetBit(a,2)==GetBit(a,0)) ){
          SM_state = less;
          //return less;
        }
        else{
          digitalWrite(b0,LOW);
          digitalWrite(b1,LOW);
        }
}

void TickFct_SM()
{
  switch(SM_state) {   // Transitions
     case SM_SMStart:  // Initial transition
        resetB();
        SM_state = COMPARE;
        break;
     case COMPARE:
        check_equality();
        break;
     case EQUAL:
        check_equality();
        break;
     case greater:
        check_equality();
        break;
     case less:
        check_equality();
        break;
      default:
         SM_state = SM_SMStart;
  } // Transitions
  
  switch(SM_state) {   // State actions
     case COMPARE:
          check_equality();
          break;
     case EQUAL:
        digitalWrite(b0,HIGH);
        digitalWrite(b1,HIGH);
        delay(400);
        break;
     case greater:
        digitalWrite(b0,HIGH);
        digitalWrite(b1,LOW);
        delay(400);
        break;
      case less:
        digitalWrite(b0,LOW);
        digitalWrite(b1,HIGH);
        delay(400);
        break;
     default:
        SM_state = SM_SMStart;
        break;
   } // State actions
}


void loop()
{
   TickFct_SM();
   delay(400);
}
