

//
//          Code for A.C.E.D. Project, MSE 101/102.                            Written by Q. Mike Andrews
//                                                                                         March 17, 2015
//
//      This code uses 2 light sensors and 1 limit switch to control the operation
//      of a chickn coop door through 2 mosfets that control 2 relays that operate
//      a 12v motor hooked up to a 12v battery.
//




// constant that sets the sensitivity of the light sensors. 10 is aboslute minimum (needs pitch black)
// around 200 to 300 makes it sensitive to a passing shadow
const int sensorDark1 = 37;
const int sensorDark2 = 37;

// used for timing door movments
int doorUp = 0, doorDown = 0;

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

void setup()
{
    // initialize the pins
    pinMode(outputPin2, OUTPUT);
    pinMode(outputPin3, OUTPUT);
    pinMode(limitSw1Pwr, OUTPUT);
    pinMode(limitSw1In, INPUT);
}

void loop()  // main loop that runs the operations of the circiut
{
    int analogValuePh1;
    int analogValuePh2;
    int digitalValueSw1;
    digitalWrite(limitSw1Pwr, HIGH);
    
    
    // if a loop need to end
    boolean loopExit = false;

    // read our photocells at different times, with a built in delay
    delay(300);
    analogValuePh1 = analogRead(photocellPin0);
    delay(400);
    analogValuePh2 = analogRead(photocellPin1);
	
    // read limit switch
    digitalValueSw1 = digitalRead(limitSw1In);
    
    
    // Door Opening Section
    while ( ((analogValuePh1 < sensorDark1) && (analogValuePh2 < sensorDark2)) && ((doorOpen == false) && (loopExit == false)) && (digitalValueSw1 == HIGH) )
    {
        digitalWrite(outputPin2, HIGH);
	doorUp++;
        delay(11);
        
        analogValuePh1 = analogRead(photocellPin0);
        delay(7);
        analogValuePh2 = analogRead(photocellPin1);
        
        digitalValueSw1 = digitalRead(limitSw1In);
        if (digitalValueSw1 == LOW) {loopExit = true; doorOpen = true;}
        
        // check once if the door was nuisance tripped         
        if ( ((analogValuePh1 > sensorDark1) || (analogValuePh2 > sensorDark2)) || (digitalValueSw1 == LOW) )
        {
		digitalWrite(outputPin2, LOW);
		delay(10);
		digitalWrite(outputPin3, LOW);
		delay(1);
                loopExit = true; 		          
        }
                
        if (doorUp > 450)
	{
        digitalWrite(outputPin2, LOW);
        delay(10);
        digitalWrite(outputPin3, LOW);
        delay(1);        
        doorOpen = true; // sets door to open after opening finishes
        loopExit = true; 
	}
                
       
    } // end of Door Opening Section
    
    
    // Door Closing Section
    
    while ( ((analogValuePh1 > sensorDark1) && (analogValuePh2 > sensorDark2)) && ((doorOpen == true) && (loopExit == false)) )
    {
        // set motor in reverse and start lowering door
        digitalWrite(outputPin3, HIGH);
        delay(10);
        digitalWrite(outputPin2, HIGH);
	doorUp--;
	delay(1);
	if (doorUp < 0) {doorUp = 0;}        
        
        // check photocells again
        analogValuePh1 = analogRead(photocellPin0);
        delay(7);
        analogValuePh2 = analogRead(photocellPin1);
        
        // check once if the door was nuisance tripped         
        if ( ((analogValuePh1 < sensorDark1) || (analogValuePh2 < sensorDark2)) )
        {
		digitalWrite(outputPin2, LOW);
		delay(10);
		digitalWrite(outputPin3, LOW);
		delay(1);  
		loopExit = true;           
        }
        
	if (doorUp < 1)
	{
          digitalWrite(outputPin2, LOW);
          delay(10);
          digitalWrite(outputPin3, LOW);
          delay(1);        
          doorOpen = false; // sets door to closed
          loopExit = true; 
	}
        
        
       
    } // end of Door Close Section
   
   
   
}  // restart loop
