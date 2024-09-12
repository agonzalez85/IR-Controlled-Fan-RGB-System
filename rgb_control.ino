#include <IRremote.h>

/**
  * IR-Controlled RGB LED Lighting System
  *
  * This Arduino project creates an infrared (IR) remote-controlled RGB LED lighting system.
  * Users can change colors, adjust brightness, and toggle the lights on/off using a standard IR remote.
  * The system interprets IR signals to set specific colors, increase or decrease intensity, 
  * and perform various lighting effects, offering a customizable and interactive lighting experience.
  *
  @author Andy Gonzalez
  @date 2/2023
*/

// Pin definitions for IR receiver and RGB LED
const int IR_PIN = 9;     // IR receiver pin
const int RED_PIN = 6;    // Red LED pin
const int GREEN_PIN = 5;  // Green LED pin
const int BLUE_PIN = 10;  // Blue LED pin

// IR receiver setup
IRrecv IR(IR_PIN);        // Create IR receiver object
decode_results cmd;       // Variable to store decoded IR signals

// RGB LED variables
int redBright = 255;      // Red LED brightness (0-255)
int greenBright = 255;    // Green LED brightness (0-255)
int blueBright = 255;     // Blue LED brightness (0-255)
double factor = 1.0;      // Intensity factor for all LEDs

void setup() 
{
    Serial.begin(9600);   // Initialize serial communication for debugging
    IR.enableIRIn();      // Start the IR receiver
    
    // Set RGB LED pins as outputs
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void loop() 
{
    // Check if an IR signal is received
    if (IR.decode(&cmd)) 
    {
        String myCommand = getCommand(cmd.value);  // Convert IR value to command string
        executeCommand(myCommand);                 // Execute the command
        updateLEDs();                              // Update LED colors and brightness
        delay(1500);                               // Delay to prevent multiple reads
        IR.resume();                               // Resume IR receiver
    }
}

// Function to convert IR values to command strings
String getCommand(long value) 
{
  if(cmd.value==0xFF6897 || cmd.value==0xC101E57B) //zero
  {
    myCommand="zero";
  }
  else if(cmd.value==0xFF30CF  || cmd.value==0x9716BE3F) //1
  {
    myCommand="one";
  }
  else if(cmd.value==0xFF18E7 || cmd.value==0x3D9AE3F7) //2
  {
    myCommand="two";
  } 
  else if(cmd.value==0xFF7A85 || cmd.value==0x6182021B) //3
  {
    myCommand="three";
  }
  else if(cmd.value==0xFF10EF || cmd.value==0x8C22657B) //4
  {
    myCommand="four";
  }
  else if(cmd.value==0xFF38C7 || cmd.value==0x488F3CBB) //5
  {
    myCommand="five";
  }
  else if(cmd.value==0xFF5AA5 || cmd.value==0x449E79F) //6
  {
    myCommand="six";
  }
  else if(cmd.value==0xFF42BD || cmd.value==0x32C6FDF7) //7
  {
    myCommand="seven";
  }
  else if(cmd.value==0xFF4AB5 || cmd.value==0x1BC0157B) //8
  {
    myCommand="eight";
  }
  else if(cmd.value==0xFF52AD  || cmd.value==0x3EC3FC1B) //9
  {
    myCommand="nine";
  }
  else if(cmd.value==0xFFA25D || cmd.value==0xE318261B) //power
  {
    myCommand="power";
  }
  else if(cmd.value==0xFF629D || cmd.value==0x511DBB) //volume+
  {
    myCommand="v+";
  }
  else if(cmd.value==0xFFE21D || cmd.value==0xEE886D7F) //stop
  {
    myCommand="stop";
  }
  else if(cmd.value==0xFF22DD || cmd.value==0x52A3D41F) //back
  {
    myCommand="back";
  }
  else if(cmd.value==0xFF02FD || cmd.value==0xD7E84B1B) //play
  {
    myCommand="play";
  }
  else if(cmd.value==0xFFC23D || cmd.value==0x20FE4DBB) //forward
  {
    myCommand="forward";
  }
  else if(cmd.value==0xFFE01F || cmd.value==0xF076C13B) //down
  {
    myCommand="down";
  }
  else if(cmd.value==0xFFA857 || cmd.value==0xA3C8EDDB) //volume-
  {
    myCommand="v-";
  }
  else if(cmd.value==0xFF906F || cmd.value==0xE5CFBD7F) //up
  {
    myCommand="up";
  }
  else if(cmd.value==0xFF9867 || cmd.value==0x97483BFB) //eq
  {
    myCommand="eq";
  }
  else if(cmd.value==0xFFB04F || cmd.value==0xF0C41643) //repeat
  {
    myCommand="rept";
  }
}

// Function to execute commands based on IR input
void executeCommand(String myCommand) 
{
    Serial.println(myCommand);  // Print command for debugging

    // Execute different actions based on the received command
    if (myCommand == "power") {
        setColor(255, 255, 255);  // Set color to white
        factor = 1.0;             // Set full brightness
    } else if (myCommand == "stop") {
        setColor(0, 0, 0);        // Turn off all LEDs
        factor = 0.0;             // Set brightness to zero
    } else if (myCommand == "up") {
        adjustIntensity(1.3);     // Increase brightness by 30%
    } else if (myCommand == "down") {
        adjustIntensity(0.5);     // Decrease brightness by 50%
    } else if (myCommand == "play") {
        factor = 1.0;             // Reset to full brightness
    } else if (myCommand == "one") {
        setColor(255, 0, 0);      // Set color to red
    } else if (myCommand == "two") {
        setColor(0, 255, 0);      // Set color to green
    } else if (myCommand == "three") {
        setColor(0, 0, 255);      // Set color to blue
    } else if (myCommand == "four") {
        setColor(255, 255, 0);    // Set color to yellow
    } else if (myCommand == "five") {
        setColor(0, 255, 255);    // Set color to cyan
    } else if (myCommand == "six") {
        setColor(255, 0, 255);    // Set color to magenta
    }
}

// Function to set RGB LED color
void setColor(int red, int green, int blue)
{
    redBright = red;
    greenBright = green;
    blueBright = blue;
}

// Function to adjust LED intensity
void adjustIntensity(double adjustment) 
{
    factor *= adjustment;                  // Apply adjustment to intensity factor
    factor = constrain(factor, 0.0, 1.0);  // Ensure factor is between 0 and 1
}

// Function to update LED outputs
void updateLEDs() 
{
    // Apply intensity factor to each LED color and write to pins
    analogWrite(RED_PIN, redBright * factor);
    analogWrite(GREEN_PIN, greenBright * factor);
    analogWrite(BLUE_PIN, blueBright * factor);
}
