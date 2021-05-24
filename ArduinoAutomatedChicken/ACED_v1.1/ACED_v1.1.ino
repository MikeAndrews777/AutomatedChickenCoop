

// constant that sets the sensitivity of the light sensors.
// 10 is aboslute minimum (needs pitch black)
// around 200 to 300 makes it sensitive to a passing shadow

const int sensorDark1 = 37;
const int sensorDark2 = 37;

boolean doorOpen = false;

// the photocell voltage divider pin
int photocellPin0 = A0;
int photocellPin1 = A1;
// the LED pin
int outputPin2 = 2;
int outputPin3 = 3;

void setup()
{
    // initialize the LED pin as output
    pinMode(outputPin2, OUTPUT);
    pinMode(outputPin3, OUTPUT);
}

void loop()
{
    int analogValuePh1;
    int analogValuePh2;

    // read our photocells at different times, with a built in delay
    delay(300);
    analogValuePh1 = analogRead(photocellPin0);
    delay(400);
    analogValuePh2 = analogRead(photocellPin1);

    //ckeck if it is light out or not
    if ( (analogValuePh1 < sensorDark1) && (analogValuePh2 < sensorDark2) && (doorOpen == false) )
    {
        digitalWrite(outputPin2, HIGH);
        delay(2000);
        
        analogValuePh1 = analogRead(photocellPin0);
        delay(700);
        analogValuePh2 = analogRead(photocellPin1);
        
        //check once if the door was nusance tripped         
        while ( ((analogValuePh1 > sensorDark1) || (analogValuePh2 > sensorDark2)) && (doorOpen == false) )
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
          
          
          break; //exits the 'door check' statment      
          
              
           
        }
        
        delay(2000);
        digitalWrite(outputPin2, LOW);
        delay(200);
        
        doorOpen = true; //sets door to open after opening finishes
        
        
       
    }
    
    
    // Door Closing Section
    
    if ( (analogValuePh1 > sensorDark1) && (analogValuePh2 > sensorDark2) && (doorOpen == true) )
    {
        //set motor in reverse and start lowering door
        digitalWrite(outputPin3, HIGH);
        delay(200);
        digitalWrite(outputPin2, HIGH);
        delay(2000);
        
        //check photocells again
        analogValuePh1 = analogRead(photocellPin0);
        delay(700);
        analogValuePh2 = analogRead(photocellPin1);
        
        //check once if the door was nusance tripped         
        while ( ((analogValuePh1 < sensorDark1) || (analogValuePh2 < sensorDark2)) && (doorOpen == true) )
        {
          digitalWrite(outputPin2, LOW);
          delay(700);          
          digitalWrite(outputPin3, LOW);
          delay(200);
          digitalWrite(outputPin2, HIGH);
          delay(2700);
          digitalWrite(outputPin2, LOW);
          delay(200);
          
          
          break; //exits the 'door check' statment      
          
              
           
        }
        
        delay(2000);
        digitalWrite(outputPin2, LOW);
        delay(200);
        digitalWrite(outputPin3, LOW);
        delay(200);
        
        doorOpen = false; //sets door to open after opening finishes
        
        
       
    }
   
}
