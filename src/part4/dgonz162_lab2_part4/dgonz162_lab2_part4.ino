// C++ code

/*        Your Name & E-mail: David Gonzalez, dgonz162@ucr.edu

*          Lab Section: 021

*         Assignment: Lab 2  Exercise 4


*         Exercise Description: Turns on LED if button is being pressed

*         I acknowledge all content contained herein, excluding template or example code, is my own original work.

*         Demo Link: 

*/

#define LED 2
enum SM_states { SM_SMStart, OFF, ON_PRESS} SM_state;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(LED, OUTPUT);
}

void TickFct_SM()
{
  switch(SM_state){
    case SM_SMStart:
    	SM_state = OFF;
   		break;
    case OFF:
      if(digitalRead(A0) == LOW){
          SM_state =  OFF;  
      }
      else if(digitalRead(A0) == HIGH){
          SM_state = ON_PRESS;
      }
    break;

    case ON_PRESS:
      if(digitalRead(A0) == LOW){
          SM_state =  OFF;  
      }
      else if(digitalRead(A0) == HIGH){
          SM_state = ON_PRESS;
      }
    break;
    
    default:
    	SM_state = SM_SMStart;
  }//transitions
  
  switch(SM_state){
    case OFF:
		digitalWrite(LED, LOW);
    break;
    
    case ON_PRESS:
      	digitalWrite(LED, HIGH);
    break;
    
    default:
    break;
  }//actions
}

void loop()
{
	TickFct_SM();
}
