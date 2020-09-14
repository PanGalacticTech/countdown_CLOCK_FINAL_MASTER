// Global Variables Go Here.





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Colour Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Custom Colour Creator:
// use savedColour Constructor to craete custom colours that can be passed to the display

struct savedColour {             // data structure to save named RGB values that could be passed to functions
  uint8_t r;
  uint8_t g;
  uint8_t b;
};


// Pick and Name Colours here, then add them to the colourArray to make them easily accessable


savedColour  skyroraBlue = { 0, 90, 255};    // Data structure for "skyroraBlue" colour as an RGB value

savedColour  offWhite = { 160, 255, 200};      // data structure for an offwhite colour, all LEDs on max (these figures chave been calibrated to produce a cleaner white)

savedColour  yellowOrange = {255, 160, 0};     // Holds Orange Colour as a nice contrast to the blue

savedColour  blackout = {0 , 0 , 0};          // data structure holding "black" - all LEDS off.

savedColour  currentColour;                  // data structure to hold the current LED colour


savedColour colourArray[3] = {skyroraBlue, offWhite, yellowOrange};     // array to hold different colour data structures. Makes it easy to cycle through them

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~







//'''''''''''' Input Variables ''''''''''''''''''''''''''

// Can be used for switches or switchable options

bool demoMode = false;                              // demo mode for animations // Defaults to OFF

int8_t demoPin = 15;                              // Short this pin to GND on boot up to force demo mode

int8_t demoPinValue;                                // Stores the value of demopin on boot up.


//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''










//####################################### Clock Variables ############################################################


// ~~~~~~~~~~~~ Global Timing Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// These Hold the current displayed time in Seconds Minuites and Hours.
// Values can be negative or positive.

struct countDownTime {                                          //This is a data structure that contains the time as hours minutes and seconds
  int8_t h;
  int8_t m;
  int8_t s;
};

countDownTime countdownTime;     // Create an instance of the structure above to hold our master clock value

countDownTime outputTime;    // time data structure used to return the results of millisToTime Function. 

// int32_t countDownMillis;   //an alternative master clock that only counts in milliseconds.  (Not implimented in the end)


// Initial Timing Settings // This acts as a constant for the inital setup in the case of no other external start time input.
// These variables are not updated on every loop,
countDownTime initalCountdownTime{-0, -0, -10};           //( hours, minutes, seconds )
//



int32_t millisOffset;     // This variable is subtracked from millis() reading in order to allow the clock to be updated periodically from database reads, then run off its own clock between updates. (Not Implemented Yet)









//###################################################################################################################


// ---------- Clock / Display Variables --------                                                These variables are used in translating clock variables above into the printed digits below.

// These variables hold the values printed to each digit of the display
int8_t secondsLSF;     //seconds least significant figure
int8_t secondsMSF;      // seconds most singnificant figure

int8_t minutesLSF;     //minutes least significant figure
int8_t minutesMSF;      // minites  most singnificant figure

int8_t hoursLSF;     //hours least significant figure
int8_t hoursMSF;      // hours  most singnificant figure

int8_t sixDigits[6] = {};   // array to hold variables above, allows us to iterate through them in a loop, writing each one to the displayed digit variable in order. (Not yet implemented as I only have a single digit to write to)

int8_t activeDigit = 0;  // this value used to control the digit that is currently being written to

// --------------------------------------------------------------------------------




//::::::::::::::::::::::::::::::::::::::::::::::::::::::: Neopixel to Seven Segment Variables :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// The following data structures are intended to make the neopixles function effectivly like a traditional 7 segment display.


struct digitSeg {                                // Data Structure to contain the data for "characters" divided up into 7 segments. Each segment can be on or off.
  uint8_t A;                                       // Segments mirror the wiring of traditional 7 segment display
  uint8_t B;
  uint8_t C;
  uint8_t D;
  uint8_t E;
  uint8_t F;
  uint8_t G;
};


// These values are passed bit arrays to print specific digits to each character in the display

digitSeg seconds0;                                          // Holds the current displayed least significant seconds figure
digitSeg seconds1;                                           // holds the current displayed most significant seconds figure

digitSeg minutes2;                                          // Holds the current displayed least significant minuitesfigure
digitSeg minutes3;                                           // holds the current displayed most significant minuites figure

digitSeg hours4;                                          // Holds the current displayed least significant hours figure
digitSeg hours5;                                           // holds the current displayed most significant hours figure

digitSeg plusminus;                                       // Holds the positive or negative (might be a better way of doing this as it only requires 2 bytes of data, not 7
digitSeg dots;                                             // holds the values for the dots (also could be done differently, as it only needs one bit for control, but 4 LED id's


digitSeg displayedDigits[6] = {seconds0, seconds1, minutes2, minutes3, hours4, hours5};   // holds the data values above in an array making referencing in functions and loops easier.





// these constant data structures hold the arrays for each unique character. Bits mirror the segments of a typical 7 segment display. Other letters and Characters can be added by adding arrays

digitSeg zero = {1, 1, 1, 1, 1, 1, 0};
digitSeg one = {0, 1, 1, 0, 0, 0, 0};
digitSeg two = {1, 1, 0, 1, 1, 0, 1};
digitSeg three = {1, 1, 1, 1, 0, 0, 1};
digitSeg four = {0, 1, 1, 0, 0, 1, 1};
digitSeg five = {1, 0, 1, 1, 0, 1, 1};
digitSeg six = {1, 0, 1, 1, 1, 1, 1};
digitSeg seven = {1, 1, 1, 0, 0, 0, 0};
digitSeg eight = {1, 1, 1, 1, 1, 1, 1};
digitSeg nine = {1, 1, 1, 0, 0, 1, 1};


digitSeg alldigits[10] = {zero, one, two, three, four, five, six, seven, eight, nine};   // array to hold data structures above. Array number matches the character being recalled.

// This can be accessed as:

//alldigits[0];   // contains the display data for the character 0
//alldigits[1];   // Contains the display data for the character 1
// et al

//Other Letters and characters that could be easily printed (needs arrays to be filled in);

digitSeg A;
digitSeg E;
digitSeg i;
digitSeg O;
digitSeg o;
digitSeg U;
digitSeg u;

digitSeg B;
digitSeg C;
digitSeg F;
digitSeg H;
digitSeg J;

digitSeg P;
digitSeg S;



digitSeg b;
digitSeg c;
digitSeg d;
digitSeg g;
digitSeg h;
digitSeg l;
digitSeg n;
digitSeg p;
digitSeg qu;
digitSeg r;
digitSeg t;
digitSeg y;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::




// NONE OF THIS WAS NESSISSARY! Leaving in for now to show what a stupid idea looks like.

// Each digit is made of 7 segments, each of these has 3 LEDs. these structures hold the ID of each of the LEDS to reference later:

/*
  struct digit0ID {

  uint8_t idA[3] = {0 , 1, 2};                        // arrays that contain the ID numbers for each LED in the 0 digit
  uint8_t idB[3] = {3 , 4, 5};
  uint8_t idC[3] = {6 , 7, 8};
  uint8_t idD[3] = {9 , 10, 11};
  uint8_t diE[3] = {12 , 13, 14};
  uint8_t idF[3] = {15 , 16, 17};
  uint8_t idG[3] = {28 , 19, 20};

  };


  struct digit1ID {

  uint8_t idA[3] = {21 , 22, 23};                        // arrays that contain the ID numbers for each LED in the 1 digit
  uint8_t idB[3] = {24 , 25, 26};
  uint8_t idC[3] = {27 , 28, 29};
  uint8_t idD[3] = {30 , 30, 32};
  uint8_t diE[3] = {33 , 34, 35};
  uint8_t idF[3] = {36 , 37, 38};
  uint8_t idG[3] = {39 , 40, 41};

  };


  struct digit2ID {

  uint8_t idA[3] = {21 , 22, 23};                        // arrays that contain the ID numbers for each LED in the 2 digit
  uint8_t idB[3] = {24 , 25, 26};
  uint8_t idC[3] = {27 , 28, 29};
  uint8_t idD[3] = {30 , 30, 32};
  uint8_t diE[3] = {33 , 34, 35};
  uint8_t idF[3] = {36 , 37, 38};
  uint8_t idG[3] = {39 , 40, 41};

  };


  struct digit3ID {

  uint8_t idA[3] = {42 , 43, 44};                        // arrays that contain the ID numbers for each LED in the 3 digit
  uint8_t idB[3] = {45 , 46, 47};
  uint8_t idC[3] = {48 , 47, 50};
  uint8_t idD[3] = {51 , 52, 53};
  uint8_t diE[3] = {54 , 55, 56};
  uint8_t idF[3] = {57 , 58, 59};
  uint8_t idG[3] = {60 , 61, 62};

  };


  struct digit4ID {

  uint8_t idA[3] = {21 , 22, 23};                        // arrays that contain the ID numbers for each LED in the 4 digit
  uint8_t idB[3] = {24 , 25, 26};
  uint8_t idC[3] = {27 , 28, 29};
  uint8_t idD[3] = {30 , 30, 32};
  uint8_t diE[3] = {33 , 34, 35};
  uint8_t idF[3] = {36 , 37, 38};
  uint8_t idG[3] = {39 , 40, 41};

  };

  struct digit5ID {

  uint8_t idA[3] = {21 , 22, 23};                        // arrays that contain the ID numbers for each LED in the 5 digit
  uint8_t idB[3] = {24 , 25, 26};
  uint8_t idC[3] = {27 , 28, 29};
  uint8_t idD[3] = {30 , 30, 32};
  uint8_t diE[3] = {33 , 34, 35};
  uint8_t idF[3] = {36 , 37, 38};
  uint8_t idG[3] = {39 , 40, 41};

  };

*/
// Yes this does feel like a dumb way to do this.

// I could just use the first array, then to access the other IDs, by adding (21*(digitNumber)) to the written value
