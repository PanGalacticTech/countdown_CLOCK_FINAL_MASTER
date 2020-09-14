#include <FastLED.h>
#include "globals.h"
#include <DateTime.h>
#include <autoDelay.h> 

FASTLED_USING_NAMESPACE      // I do not Know what This line does



#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    22                    // Data pin connection to LED string
//#define CLK_PIN   4                      // Not required for 3 pin LED strings
#define LED_TYPE    WS2812B                // This must be set to match the specific LED driver used

//#define LED_TYPE WS2811_400               //

#define COLOR_ORDER GRB

//#define NUM_LEDS   21                        // Number of LEDs in a single digit [Depreciated]

#define NUM_LEDS 272                             //Number of LEDS in 6 digits (will add more for the sign and dots later  need at least 7 for +- and 4 for dots   
#define LED_PER_SEG  6                            // number of individual neopixles in each segment

int ledsPerDigit;       // variable calculated from LED_PER_SEG

CRGBArray<NUM_LEDS> ledString;


autoDelay ledDelay;

long ledPrintDelay = 500;   // ms value to slow down writing data to LEDs
//uint8_t numberOfLEDs = NUM_LEDS               // alternative methods, depreciated for now

//CRGB leds[NUM_LEDS];                            // alternative methods, depreciated for now

//CRGBSet A(digitLEDs, 21);                        // alternative methods, depreciated for now

// I could not work out how  to make this work so we are going for the big dumb hammer approach
//CRGBArray<21> digit0, digit1, digit2, digit3, digit4, digit5;





//@@@@@@@@@@@\\\ Options ///@@@@@@@@@@@@@@@@@@@


uint8_t maxBrightness = 150;                      // Define the max brightness of all LEDs. 0 - 255. 20-50 reccomended for testing: MUST use seperate 5v supply for full brightness operation! Do not use USB power!

//   N.B. on power consumption:
// At full brightness each LED can draw 60 mA

// 60 mA * 126 = 7560 mA = 7.6 A !
// including the 14 extra = 8.4 A
// These LEDs can draw a decent amount of current and require a decent PSU. 10A @ 5v Recommended


int8_t colourSelect = 0;                        // selectes the display colour. 0 = skyrora blue, 1 = offwhite, 2 = yellowOrange. (currently cycles through each)

//@@@@@@@@@@@\\\ Options ///@@@@@@@@@@@@@@@@@@@



unsigned long updateDisplayDelay = 1000;  //   (will also be used to slow down printing to the serial monitor during testing)
unsigned long lastDisplayUpdate;        // save the time of the last update













// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void setup() {


  // Set up and get controller ready


  pinMode(demoPin, INPUT_PULLUP);                          // Set up input pins

  demoPinValue = digitalRead(demoPin);                   // read the demo pin once to see if shorted

  delay(3000); // 3 second delay for recovery

  Serial.begin(115200);                                    // Serial for debugging if required



  countdownTime = initalCountdownTime;                            // Pre load starting time



  Serial.printf("Countdown MATHS TEST Starts @: %+2i:%2i:%2i", countdownTime.h, countdownTime.m, countdownTime.s);         // Print The starting time
  Serial.println(" ");
  //  delay(2000);

  int32_t millisAddr;                                                                                  // Set up variable to hold milliseconds

  millisAddr = timeToMillis(countdownTime);                                                            // work out the value of our initial start time as milliseconds



  Serial.printf("Time to Millis: %+i", millisAddr);                                                  // Print for Testing
  Serial.println(" ");
  //  delay(2000);

  millisToTime(millisAddr);                                                                            // Convert milliseconds back into a time.

  countdownTime = outputTime;  // output time is passed from millisToTime as a global variable            // pass that time structure to out master clock


  Serial.printf("Countdown MATHS TEST Return: %+2i:%2i:%2i", countdownTime.h, countdownTime.m, countdownTime.s);       // print the values of the master clock. This is all superflous, but tests the algorithms and functions used to convert times
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" Above countdown times should match. If not Your Program is WRONG! ");

  // delay(2000);



  if (demoPinValue == 0) {                                       // if pin was shorted before, after delay check pin is still shorted
    demoPinValue = digitalRead(demoPin);
    if (demoPinValue == 0) {                                         // if false i.e (Shorted), set demoMode
      demoMode = true;
      Serial.println("Demo Mode Active");
    }
  } else {                                                                                                       // Else countdown clock is initialised and the starting time printed to the serial monitor
    Serial.println("Countdown Clock Initialised");
    Serial.printf("Countdown Starts @: %+2i:%2i:%2i", countdownTime.h, countdownTime.m, countdownTime.s);
    Serial.println(" ");
    Serial.println(" ");
  }


  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(ledString, NUM_LEDS).setCorrection(TypicalLEDStrip);            // This sets up our LED string object


  // set master brightness control
  FastLED.setBrightness(maxBrightness);                                                                        // Sets the brightness for the entire string


  currentColour = skyroraBlue;                                                                                 // Preset the starting LED colour, can be changed later in program

  

  clockSet();
  // internalClockReset() ;                                       // resets internal clock offset at zero < Last thing before ending setup
}















//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void loop() {



  // clock timing functions to take over when live data not available:

  //   countdownClock();      // Free Running Clock                                                            // Pick one function or the other

  internalClock();                   // internal Real Time Clock                                                        // Pick one function or the other



  // Function to split up clock into individual digits to feed to display algorithms
  clocktodigits();








  displayedDigits[0] = alldigits[secondsLSF];                                          // current display data handed a digit from alldigits array,
  displayedDigits[1] = alldigits[secondsMSF];

  displayedDigits[2] = alldigits[minutesLSF];                                          // current display data handed a digit from alldigits array,
  displayedDigits[3] = alldigits[minutesMSF];

  displayedDigits[4] = alldigits[hoursLSF];                                          // current display data handed a digit from alldigits array,
  displayedDigits[5] = alldigits[hoursMSF];

  // This line can be put into a for loop, and the pre seperated timing values passed to displayed digits array, then to the setDigit function


  if (!demoMode) {                                                                                                                             // if demo mode is inactive > Write the clock to the display


  setDigit(displayedDigits[5], 5, currentColour.r, currentColour.g, currentColour.b);
   setDigit(displayedDigits[4], 4, currentColour.r, currentColour.g, currentColour.b);

    setDigit(displayedDigits[3], 3, currentColour.r, currentColour.g, currentColour.b);
   setDigit(displayedDigits[2], 2, currentColour.r, currentColour.g, currentColour.b);

    setDigit(displayedDigits[1], 1, currentColour.r, currentColour.g, currentColour.b);
    setDigit(displayedDigits[0], 0, currentColour.r, currentColour.g, currentColour.b);                                      // Turns LED segments on and off. Brightness is already set in setup loop,.







    //     Colour for "ON" LEDs passed as seperate RGB values an argument to the function
    //      currentColour variable is passed as seperate .r .b .g values, so these can be replaced directly with RGB values 0-255
  }

  else {                                                                                                 // else run the demo program

    runDemo();

  }


  printTime(1000);   // Serial Monitoring Output (printDelayMs)

if (ledDelay.millisDelay(ledPrintDelay)){

  FastLED.show();    // trying this on every loop to see if it works more smoothly

  
}

  /*

    if (countdownTime.s == 60 || countdownTime.s == -60 || countdownTime.s == 0) {                     // if seconds reach 0 (every minuite) change colour.

    //  cycleColour();                                                               // Cycles colours once a minuite

    }

  */

}
