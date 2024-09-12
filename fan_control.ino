#include <IRremote.h>

/**
  * IR-Controlled Fan System
  *
  * This Arduino project implements an infrared (IR) remote-controlled fan system. 
  * It allows users to control a DC motor's speed and direction using a standard IR remote.
  * The system interprets IR signals to adjust fan speed, change direction, and perform 
  * on/off operations, providing a versatile and user-friendly fan control solution.
  *
  @author Andy Gonzalez
  @date 2/2023
*/

// Pin definitions for IR receiver and motor control
const int IR_PIN = 9;    // IR receiver pin
const int SPEED_PIN = 5; // Motor speed control pin (PWM)
const int DIR_PIN1 = 4;  // Motor direction control pin 1
const int DIR_PIN2 = 3;  // Motor direction control pin 2

// IR receiver setup
IRrecv IR(IR_PIN);       // Create IR receiver object
decode_results cmd;      // Variable to store decoded IR signals

// Motor variables
int motorSpeed = 255;    // Initial motor speed (full speed)

void setup() 
{
    Serial.begin(9600);  // Initialize serial communication for debugging
    IR.enableIRIn();     // Start the IR receiver

    // Set motor control pins as outputs
    pinMode(SPEED_PIN, OUTPUT);
    pinMode(DIR_PIN1, OUTPUT);
    pinMode(DIR_PIN2, OUTPUT);
    
    // Set initial motor direction (forward)
    digitalWrite(DIR_PIN1, HIGH);
    digitalWrite(DIR_PIN2, LOW);
}

void loop() 
{
    // Check if an IR signal is received
    if (IR.decode(&cmd)) 
    {
        String myCommand = getCommand(cmd.value);  // Convert IR value to command string
        executeCommand(myCommand);                 // Execute the command
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
        setMotorDirection(false);  // Set motor direction to reverse
        setMotorSpeed(255);        // Set motor to full speed
    } else if (myCommand == "stop") {
        setMotorSpeed(0);          // Stop the motor
    } else if (myCommand == "back") {
        setMotorDirection(true);   // Set motor direction to forward
        setMotorSpeed(motorSpeed); // Maintain current speed
    } else if (myCommand == "forward") {
        setMotorDirection(false);  // Set motor direction to reverse
        setMotorSpeed(motorSpeed); // Maintain current speed
    } else if (myCommand == "v+" || myCommand == "up") {
        adjustMotorSpeed(50);      // Increase speed by 50
    } else if (myCommand == "v-" || myCommand == "down") {
        adjustMotorSpeed(-50);     // Decrease speed by 50
    } else if (myCommand >= "zero" && myCommand <= "nine") {
        // Set speed based on numeric input (0-9)
        int speed = (myCommand == "zero") ? 0 : (myCommand[0] - '0') * 28;
        setMotorSpeed(speed);
    }
}

// Function to set motor direction
void setMotorDirection(bool forward) 
{
    digitalWrite(DIR_PIN1, forward ? HIGH : LOW);
    digitalWrite(DIR_PIN2, forward ? LOW : HIGH);
}

// Function to set motor speed
void setMotorSpeed(int speed) 
{
    motorSpeed = constrain(speed, 0, 255);  // Ensure speed is within valid range
    analogWrite(SPEED_PIN, motorSpeed);     // Set PWM value for motor speed
}

// Function to adjust motor speed
void adjustMotorSpeed(int adjustment)
{
    setMotorSpeed(motorSpeed + adjustment);  // Adjust speed and apply constraints
}
