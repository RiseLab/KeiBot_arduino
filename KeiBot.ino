#include <AFMotor.h>
#include <Servo.h>

#define LED_PIN 13

AF_DCMotor motor3(3);

Servo servoCamH;
Servo servoCamV;

String inputString = "";

void setup()
{
  Serial.begin(57600);
  
  pinMode(LED_PIN, OUTPUT);

  motor3.setSpeed(200);
  motor3.run(RELEASE);
  
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
            digitalWrite(LED_PIN, HIGH);
            motor3.run(FORWARD);
            return;
        }

        // stop command
        if (command == "ms"){
            digitalWrite(LED_PIN, LOW);
            motor3.run(RELEASE);
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
