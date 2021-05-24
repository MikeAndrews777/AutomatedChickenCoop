
//          Code for A.C.E.D. Project, MSE 101/102.                                   Written by Q. Mike Andrews

//      This code uses 2 light sensors and 1 limit switch to control the operation
//      of a chickn coop door through 2 mosfets that control 2 relays that operate
//      a 12v motor hooked up to a 12v battery.


// constant that sets the sensitivity of the light sensors. 10 is aboslute minimum (needs pitch black)
// around 200 to 300 makes it sensitive to a passing shadow
const int sensorDark1 = 37;
const int sensorDark2 = 37;

// is door open or not
boolean doorOpen = false;

// input pins
int photocellPin0 = A0;
int photocellPin1 = A1;
int limitSw1In = 6;


// the output pins
int outputPin2 = 2;
int outputPin3 = 3;
int limitSw1Pwr = 5;
int limitSw1Out = 7;

void setup()
{
    // initialize the pins
    pinMode(outputPin2, OUTPUT);
    pinMode(outputPin3, OUTPUT);
    pinMode(limitSw1Pwr, OUTPUT);
    pinMode(limitSw1Out, OUTPUT);
    pinMode(limitSw1In, INPUT);
}

void loop()
{
    int analogValuePh1;
    int analogValuePh2;
    int digitalValueSw1;
    digitalWrite(limitSw1Pwr, HIGH);

    // read our photocells at different times, with a built in delay
    delay(300);
    analogValuePh1 = analogRead(photocellPin0);
    delay(400);
    analogValuePh2 = analogRead(photocellPin1);
	
    // read limit switch
    digitalValueSw1 = digitalRead(limitSw1In);
    
    if (digitalValueSw1 == HIGH) 
    {
    digitalWrite(limitSw1Out, HIGH);
    }
    else 
    {
    digitalWrite(limitSw1Out, LOW);
    }
    
	

    // ckeck if it is light out or not
    if ( (analogValuePh1 < sensorDark1) && (analogValuePh2 < sensorDark2) && (doorOpen == false) )
    {
        digitalWrite(outputPin2, HIGH);
        delay(2000);
        
        analogValuePh1 = analogRead(photocellPin0);
        delay(700);
        analogValuePh2 = analogRead(photocellPin1);
        
        // check once if the door was nusance tripped         
        if ( ((analogValuePh1 > sensorDark1) || (analogValuePh2 > sensorDark2)) && (doorOpen == false) )
        {
          digitalWrite(outputPin2, LOW);
          delay(700);          
          digitalWrite(outputPin3, HIGH);
          delay(200);
          digitalWrite(outputPin2, HIGH);
          delay(2700);
          digitalWrite(outputPin2, LOW);
          delay(200);          
          digitalWrite(outputPin3, LOW);
          delay(200);
          
        }
        else
        {        
        delay(2000);
        digitalWrite(outputPin2, LOW);
        delay(200);
        
        doorOpen = true; // sets door to open after opening finishes
        }
        
       
    }
    
    
    // Door Closing Section
    
    if ( (analogValuePh1 > sensorDark1) && (analogValuePh2 > sensorDark2) && (doorOpen == true) )
    {
        // set motor in reverse and start lowering door
        digitalWrite(outputPin3, HIGH);
        delay(200);
        digitalWrite(outputPin2, HIGH);
        delay(2000);
        
        // check photocells again
        analogValuePh1 = analogRead(photocellPin0);
        delay(700);
        analogValuePh2 = analogRead(photocellPin1);
        
        // check once if the door was nusance tripped         
        if ( ((analogValuePh1 < sensorDark1) || (analogValuePh2 < sensorDark2)) && (doorOpen == true) )
        {
          digitalWrite(outputPin2, LOW);
          delay(700);          
          digitalWrite(outputPin3, LOW);
          delay(200);
          digitalWrite(outputPin2, HIGH);
          delay(2700);
          digitalWrite(outputPin2, LOW);
          delay(200);
          
        }
        else
        {           
        delay(2000);
        digitalWrite(outputPin2, LOW);
        delay(200);
        digitalWrite(outputPin3, LOW);
        delay(200);
        
        doorOpen = false; // sets door to open after opening finishes
        }
        
       
    }
   
}
