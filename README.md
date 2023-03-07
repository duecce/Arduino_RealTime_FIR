# Arduino Real-Time FIR
This library computes Finite Impulse Response Filter. </br>
Filter coefficients, for example, could be evaluate in Matlab (R) and then passed as arguments in the FIR constructor method.

## Usage example: 
This example uses RealTime_FIR library to fitler the signal acquired from an AD8232 connected to an Arduino Uno (Single-Lead, heart rate monitor front-end): [AD8232 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad8232.pdf)

```
#include "RealTime_FIR.hpp"

// To implement a more complex FIR filter you can get the FIR coefficients using Matlab or http://t-filter.engineerjs.com/
// or in many other way

float FIRcoeff[] = {0.25, 0.25, 0.25, 0.25}; // Simple coefficients for a moving average with n=4
RT_FIR<float> fir = RT_FIR<float>(4, FIRcoeff); // RT_FIR instance

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}

// to correct filtering data you have to know the real adc sample frequency, in this example I didn't implement it
// It can be done using a timer
void loop() {
  float input;
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    input = (float) analogRead(0);
    Serial.println(fir.add(input));
  }
  delay(1);
}
```
