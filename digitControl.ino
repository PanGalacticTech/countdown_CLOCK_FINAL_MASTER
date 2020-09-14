// Functions Relating to the control of the digits and data to the LEDs







void clocktodigits() {  // Function to split each clock value into seperate digits bfore printing to display


  secondsLSF = countdownTime.s % 10;                                    // Splits up seconds into most significant and least significant figure
  secondsMSF = countdownTime.s / 10;

  if (secondsLSF < 0) {                                          // If negative, inverts digit to work with our array
    secondsLSF = secondsLSF * -1;                                 // character selection.
  }
  if (secondsMSF < 0) {
    secondsMSF = secondsMSF * -1;
  }


  minutesLSF = countdownTime.m % 10;                                    // Splits up minuites into most significant and least significant figure
  minutesMSF =  countdownTime.m / 10;

  if (minutesLSF < 0) {                                          // If negative, inverts digit to work with our array
    minutesLSF =  minutesLSF * -1;                                 // character selection.
  }
  if (minutesMSF < 0) {
    minutesMSF =  minutesMSF * -1;
  }


  hoursLSF = countdownTime.h % 10;                                    // Splits up Hours into most significant and least significant figure
  hoursMSF =  countdownTime.h / 10;

  if (hoursLSF < 0) {                                          // If negative, inverts digit to work with our array
    hoursLSF =  hoursLSF * -1;                                 // character selection.
  }
  if (hoursMSF < 0) {
    hoursMSF =  hoursMSF * -1;
  }



  // Serial.printf("MSF: %i  LSF:  %i", secondsMSF, secondsLSF);    //For Testing not required
  //Serial.println(" ");

}






// this function needs to be a method for a "digit" object but I couldn't work out how to do that.
// This method is slightly more inelegent but it should work (UNTESTED with more than 1 digit but confident it will function)



void setDigit (digitSeg current, int8_t digitNumber, uint8_t red, uint8_t green, uint8_t blue ) {           // This function sets the first digit based on the data structure passed to it.


  // A new instance of digitSeg has been set up ready to take whatever data is placed into it
  // After this,  a variable to denote which digit we are setting is passed as an argument.
  // Also passed to function - rgb colour value, which sets the colour for the entire digit



  uint16_t  q = ((digitNumber) * (LED_PER_SEG * 7));  // This variable is added onto the array numbers, advancing down the LED array as each successive digit is selected to be written to.

//Serial.println(q);
  // Above algorithm may need updating once dots are added, as to sync any animated lighting effects, the led addresses for the : : Dots needs to come between the ids for each digit

  int16_t s = 0;    // Addr to advance the array through each segement of each digit

/*
  if (q > 0){
    q = q-1;
  }
*/


  if (current.A) {                                                        
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = (LED_PER_SEG);

  if (current.B) {
    ledString((s + q ), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 2);

  if (current.C) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 3);

  if (current.D) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 4);

  if (current.E) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 5);
  if (current.F) {
      ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 6);

  if (current.G) {
     ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }


}

// After all the arrays for the digits, ID for the dots starts again at ID:

//  (LED_PER_SEG * 7)* 6 to ((LED_PER_SEG * 7)* 6) + 4

void setDots(uint8_t red, uint8_t green, uint8_t blue ){

  int16_t d = ((LED_PER_SEG * 7) * 6);

   ledString(d, (d +4)) = CRGB(red, green, blue);
  

  
}

void setTeeMinus(){

  
}

void cycleColour() {   // Test Function to Cycle Colour of countdown clock periodically



  colourSelect++;                                     // increment current colour - cycle through colours
  if (colourSelect > 2) {                              // reset when reach the end of array
    colourSelect = 0;
  }


  // Just a way of testing the colour changing function through each cycle
  currentColour =  colourArray[colourSelect];            // pass currentColour the array containing data structure containing
  // colour data. Can be used in response to other events
  // in response to other events. e.g. when value turns negative
  // to positive.


}
