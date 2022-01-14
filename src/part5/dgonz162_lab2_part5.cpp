// C++ code
/*        Your Name & E-mail: David Gonzalez, dgonz162@ucr.edu

*          Lab Section: 021

*         Assignment: Lab 2  Exercise 5


*         Exercise Description: Turns two LEDs on and off according to lab criteria

*         I acknowledge all content contained herein, excluding template or example code, is my own original work.

*         Demo Link: 

*/
#define LED_2 2
#define LED_3 3
enum SM_states { SM_SMStart, OFF, P2, P3} SM_state;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void TickFct_SM()
{
  switch(SM_state){
    case SM_SMStart:
      SM_state = OFF;
      break;
    case OFF:
      if( (digitalRead(A0) == LOW && digitalRead(A1) == LOW) || (digitalRead(A0) == LOW && digitalRead(A1) == LOW) ){
          SM_state =  OFF;  
      }
      else if(digitalRead(A0) == HIGH && digitalRead(A1) == LOW){
          SM_state = P2;
      }
      else if(digitalRead(A0) == LOW && digitalRead(A1) == HIGH){
          SM_state = P3;
      }
    break;

    case P2:
      if(digitalRead(A0) == HIGH && digitalRead(A1) == LOW){
          SM_state =  P2;  
      }
      else if( (digitalRead(A0) == LOW && digitalRead(A1) == LOW) || (digitalRead(A0) == HIGH && digitalRead(A1) == HIGH) ){
          SM_state = OFF;
      }
      else if(digitalRead(A0) == LOW && digitalRead(A1) == HIGH){
          SM_state =  P3;  
      }     
    break;

    case P3:
      if(digitalRead(A0) == LOW && digitalRead(A1) == HIGH){
          SM_state =  P3;  
      }
      else if( (digitalRead(A0) == LOW && digitalRead(A1) == LOW) || (digitalRead(A0) == HIGH && digitalRead(A1) == HIGH) ){
          SM_state = OFF;
      }
      else if(digitalRead(A0) == HIGH && digitalRead(A1) == LOW){
          SM_state =  P2;  
      }     
    break;    
    
    default:
      SM_state = SM_SMStart;
  }//transitions
  
  switch(SM_state){
    case OFF:
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3,LOW);
    break;
    
    case P2:
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, LOW);
    break;

    case P3:
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, HIGH);
    break;
    
    default:
    break;
  }//actions
}

void loop()
{
  TickFct_SM();
}
