

// A constant that describes when its dark enough to
// light the LED. A value close to 600 will light the led
// with less darkness. Play with this number.

const int sensorDark1 = 17;
const int sensorDark2 = 17;

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

    // read our photocell
    analogValuePh1 = analogRead(photocellPin0);
    analogValuePh2 = analogRead(photocellPin1);

    // The higher the analogValue reading is the darker it is.
    // If its at least as dark as our constant "sensorDark"
    // light the LED
    if ( analogValuePh1 < sensorDark1)
    {
        digitalWrite(outputPin2, HIGH);
    }
    // Otherwise turn the LED off
    else
    {
        digitalWrite(outputPin2, LOW);
    }
	
	if (analogValuePh2 < sensorDark2)
    {
        digitalWrite(outputPin3, HIGH);
    }
    // Otherwise turn the LED off
    else
    {
        digitalWrite(outputPin3, LOW);
    }
	
	

    // wait 1ms for better quality sensor readings
    delay(100);
}
