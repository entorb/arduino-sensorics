// LED_KY-016 3-color LED


int Led_Red = 12;
int Led_Green = 13;
int Led_Blue = 14;
  
void setup ()
{
  // Output pin initialization for the LEDs
  pinMode (Led_Red, OUTPUT); 
  pinMode (Led_Green, OUTPUT);
  pinMode (Led_Blue, OUTPUT); 
}
  
void loop () //main program loop
{
  digitalWrite (Led_Red, HIGH); // LED will be switched ON
  digitalWrite (Led_Green, LOW); // LED will be switched OFF
  digitalWrite (Led_Blue, LOW); // LED will be switched OFF
  delay (3000); // Waitmode for 3 seconds
  
  digitalWrite (Led_Red, LOW); // LED will be switched OFF
  digitalWrite (Led_Green, HIGH); // LED wwill be switched ON
  digitalWrite (Led_Blue, LOW); // LED will be switched OFF
  delay (3000); // Waitmode for another 3 seconds in which the LEDs will be shifted.
   
  digitalWrite (Led_Red, LOW); // LED will be switched OFF
  digitalWrite (Led_Green, LOW); // LED will be switched OFF
  digitalWrite (Led_Blue, HIGH); // LED will be switched ON
  delay (3000); // Waitmode for another 3 seconds in which the LEDs will be shifted.
}
