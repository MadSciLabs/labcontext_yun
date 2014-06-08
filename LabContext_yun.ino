/*

  Input Output

 Demonstrates how to create a sketch that sends and receives all standard
 spacebrew data types, and a custom data type. Every time data is 
 received it is output to the Serial monitor.

 Make sure that your Yun is connected to the internet for this example 
 to function properly.
 
 The circuit:
 - No circuit required
 
 created 2013
 by Julio Terra
 
 This example code is in the public domain.
 
 More information about Spacebrew is available at: 
 http://spacebrew.cc/
 
 */

#include <Bridge.h>
#include <SpacebrewYun.h>

const int pin_left = 4;
const int pin_right = 3;
const int pin_fire = 5;
const int pin_thrust = 2;

int arrPins[] = {2,3,4,5};
String arrNames[] = {"thrust", "right", "left", "fire"};
int arrVals[] = {0, 0, 0, 0};

// create a variable of type SpacebrewYun and initialize it with the constructor
String sb_handle = String("LabContext_Yun_a") + String(random(10000));
SpacebrewYun sb = SpacebrewYun(sb_handle, "Arduino Yun spacebrew test");

// create variables to manage interval between each time we send a string
long last = 0;
int interval = 2000;

int counter = 0;
int _val = 0;
String _sbname = "";

void setup() { 

        //sb = SpacebrewYun("LabContext_Yun_1", "Arduino Yun spacebrew test");
        
	// start the serial port
	Serial.begin(57600);

	// for debugging, wait until a serial console is connected
	delay(4000);
	//while (!Serial) { ; }
 
        for (int i=0; i<=3; i++) {
          pinMode(arrPins[i], OUTPUT);
        }
 
	// start-up the bridge
	Bridge.begin();

	// configure the spacebrew object to print status messages to serial
	sb.verbose(true);

        for (int i=0; i<=3; i++) {
          sb.addPublish(arrNames[i] + "_on", "boolean");
          sb.addPublish(arrNames[i] + "_off", "boolean");
        }

	// connect to cloud spacebrew server at "sandbox.spacebrew.cc"
	sb.connect("50.112.244.54"); 
	// we give some time to arduino to connect to sandbox, otherwise the first sb.monitor(); call will give an error
	delay(1000);

Serial.println("Start this thing.");

} 


void loop() {
  
	// monitor spacebrew connection for new data
	//sb.monitor();

	// connected to spacebrew then send a string every 2 seconds
	if ( true) { //sb.connected() ) {

            for (int i=0; i<=3; i++) {
              _val = digitalRead(arrPins[i]);
              //Serial.println("out " + String(i) + " " + _val);
              
              if (_val != arrVals[i]) {
                Serial.println("Sending");
                if (_val == 0) {
                  _sbname = arrNames[i] + "_off";
                } else {
                  _sbname = arrNames[i] + "_on";
                }
                arrVals[i] = _val;
                sb.send(_sbname, true);
                Serial.println(_sbname);
              }
 
            }
            //Serial.println("");
 
            //sb.send("boolean test", true);
            //delay(1000);
            //sb.send("boolean test", false);
  /*
		// check if it is time to send a new message
		if ( (millis() - last) > interval ) {
			String test_str_msg = "testing, testing, ";
			test_str_msg += counter;
			
                        counter ++;
                        if (counter > 1023) { counter=0;}

			//sb.send("string test", test_str_msg);
			sb.send("range test", counter);
			//sb.send("boolean test", true);
			//sb.send("custom test", "youre loco");

			last = millis();

		}
*/
	} else {
  Serial.println("Not connected.");
}
	//delay(2000);
} 

// define handler methods, all standard data type handlers take two appropriate arguments

void handleRange (String route, int value) {
	Serial.print("Range msg ");
	Serial.print(route);
	Serial.print(", value ");
	Serial.println(value);
}

void handleString (String route, String value) {
	Serial.print("String msg ");
	Serial.print(route);
	Serial.print(", value ");
	Serial.println(value);
}

void handleBoolean (String route, boolean value) {
	Serial.print("Boolen msg ");
	Serial.print(route);
	Serial.print(", value ");
	Serial.println(value ? "true" : "false");
}

// custom data type handlers takes three String arguments

void handleCustom (String route, String value, String type) {
	Serial.print("Custom msg ");
	Serial.print(route);
	Serial.print(" of type ");
	Serial.print(type);
	Serial.print(", value ");
	Serial.println(value);
}

