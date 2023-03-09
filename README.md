# Arduino Real-Time FIR
This library computes Finite Impulse Response Filter. </br>
Filter coefficients, for example, could be evaluate in Matlab (R) and then passed as arguments in the FIR constructor method.

## Usage example
Arduino_RealTime_FIR is a library composed by one class: RT_FIR. </br>
RT_FIR class has a constructor and 3 methods. Uses of this library is very simple:
1. create an instance of RT_FIR object defining filter coefficients
2. filter each sample of your signal
### How to make a RT_FIR instance
To make a RT_FIR instance you need to declare a RT_FIR object and then pass the filter parameters to the constructor method:</br>
``` 
...
RT_FIR <T> fir = new RT_FIR(nb, b);
...
```
Where: b is an array (of type:T, eg: T = double or float) contains numerator coeffs, nb is the length of b array. </br>
RT_IIR is a template class, so you are allow to filter float or double (or other type) typed samples. 

### How to filter samples
To filter new sample acquired you have to call ``` fir.add(T sample) ``` method as follows: </br>
```
...
filteredSample = fir.add(sample);
...
```
``` fir.add(T sample) ``` add a new sample to the list of samples in processing and computes the filtering operation. This method return the result of the filtering operation. </br>
``` fir.compute() ``` return the result of filtering operation without any new sample added to the filtering samples queue. </br>
``` fir.getLastOutput() ``` return the value of the last result obtained by ```fir.add(T sample)``` or ```fir.compute()``` method.

## Application example: moving average filter applied to AD8232 output using Arduino
This example uses RealTime_FIR library to filter the signal acquired from an AD8232 connected to an Arduino Uno (Single-Lead, heart rate monitor front-end): [AD8232 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad8232.pdf)

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
