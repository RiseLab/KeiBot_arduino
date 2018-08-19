#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN 13

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servoCamH;
Servo servoCamV;

String inputString = "";

void setup()
{
  Serial.begin(57600);
  
  pinMode(LED_PIN, OUTPUT);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
  servoCamH.attach(9, 544, 2340);
  servoCamH.write(90);
  
  servoCamV.attach(10, 674, 2400);
  servoCamV.write(90);
}

void loop()
{
  if (Serial.available()){
    
    char symb = Serial.read();
    
    if (symb == ';'){
      
      int comStartPos = inputString.indexOf("KC=");
      String command = (comStartPos != -1) ? inputString.substring(comStartPos + 3) : "";

      if (command != ""){

        Serial.println(command);

        inputString = "";

        // move forward command
        if (command == "mf"){
            //digitalWrite(LED_PIN, HIGH);
            motor1.run(FORWARD);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(FORWARD);
            return;
        }

        // move backward command
        if (command == "mb"){
            motor1.run(BACKWARD);
            motor2.run(BACKWARD);
            motor3.run(BACKWARD);
            motor4.run(BACKWARD);
            return;
        }

        // turn left command
        if (command == "tl"){
            motor1.run(FORWARD);
            motor3.run(FORWARD);
            motor2.run(BACKWARD);
            motor4.run(BACKWARD);
            return;
        }

        // turn right command
        if (command == "tr"){
            motor1.run(BACKWARD);
            motor3.run(BACKWARD);
            motor2.run(FORWARD);
            motor4.run(FORWARD);
            return;
        }

        // stop command
        if (command == "ms"){
            //digitalWrite(LED_PIN, LOW);
            motor1.run(RELEASE);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(RELEASE);
            return;
        }

        // cam rotate horizontal
        if (command.indexOf("crh") != -1){
          servoCamH.write(command.substring(3).toInt());
          return;
        }

        // cam rotate vertical
        if (command.indexOf("crv") != -1){
          servoCamV.write(command.substring(3).toInt());
          return;
        }
      }
    } else {
      inputString += symb;
    }
  }
}
