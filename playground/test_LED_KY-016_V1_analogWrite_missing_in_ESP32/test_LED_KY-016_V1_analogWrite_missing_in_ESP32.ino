int Led_Red = 12;
int Led_Green = 13;
int Led_Blue = 14;
 
int val;



 
void setup () {
  // Output pin initialization for the LEDs
  pinMode (Led_Red, OUTPUT); 
  pinMode (Led_Green, OUTPUT); 
  pinMode (Led_Blue, OUTPUT); 
}
void loop () {
   // In this for loop, the two LEDs will get different PWM-Values. 
   // Via mixing the brightness of the different LEDs, you will get different colors. 
   for (val = 255; val> 0; val--)
      {
      analogWrite (Led_Red, val);
      analogWrite (Led_Blue, 255-val);
      analogWrite (Led_Green, 128-val);
      delay (15);
   }
   // You will go backwards through the color range in this second loop.
   for (val = 0; val <255; val++)
      {
//      analogWrite (Led_Red, val);
//      analogWrite (Led_Blue, 255-val);
 //     analogWrite (Led_Green, 128-val);
      delay (15);
   }
}
