#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <IRremote.h>
#include <IRremoteInt.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect stepper motor with 32 steps per revolution
// to motor port #1 (M1 and M2)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(32, 2);

/*----- Variables, Pins -----*/
int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 2

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);  // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(200);  // 200 rpm   
}


//main loop to listen for remote IR signal and move motor

void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?
    {
      
      Serial.println(results.value, HEX);
      switch (results.value)

      {

        case 0x20DF40BF: // UP button pressed
          myMotor->step(35, BACKWARD, SINGLE); //I need backward motion to turn my volume knob up
          myMotor->release(); //saves stepper from using voltage and getting hot at rest
          break;
  
        case 0x20DFC03F: // DOWN button pressed
          myMotor->step(35, FORWARD, SINGLE);
          myMotor->release();
          break;

      }

    irrecv.resume(); // receive the next value
  }


}

