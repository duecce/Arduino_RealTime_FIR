# Arduino Real-Time FIR
A basic library that can help you to process data in real-time with Arduino. This library compute a FIR filtering. To store data it uses a circular linked list.
## Usage example: 
I test this FIR processing with the AD8232 (Single-Lead, heart rate monitor front-end): [AD8232 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad8232.pdf)

```
#include "RealTime_FIR.hpp"

// To implement a more complex FIR filter you can get the FIR coefficients using Matlab or http://t-filter.engineerjs.com/
// or in many other way

float FIRcoeff[] = {0.25, 0.25, 0.25, 0.25}; // Simple coefficients for a moving average with n=4
RT_FIR<float> fir = RT_FIR<float>(4, FIRcoeff);

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
