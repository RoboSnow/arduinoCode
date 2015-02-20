/*
Changes:
Added coding for plow, lights, and motor control
Removed the old template code from V1
*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>

// you can find this written on the board of some Arduino Ethernets or shields
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// NOTE: Alternatively, you can assign a fixed IP to configure your
//       Ethernet shield.
//       byte ip[] = { 192, 168, 0, 154 };

//Variables
//{
  

int serverPort  = 8000; //TouchOSC (incoming port)
int destPort = 9000;    //TouchOSC (outgoing port)

int rightMotorPin =  3;       
int leftMotorPin =  5;       

int plowPinUp = 9;       
int plowPinDwn = 6;
int lxPin = 11;       

int rightMotorState = LOW;
int leftMotorState = LOW;
int plowState = LOW;
int lxState = LOW;

int ipSend = 0;

//Create UDP message object
EthernetUDP Udp;
//}

void setup(){
  
  
  pinMode(rightMotorPin,OUTPUT);
  pinMode(leftMotorPin,OUTPUT);
  pinMode(lxPin,OUTPUT);
  
  Serial.begin(9600); //9600 for a "normal" Arduino board (Uno for example)
  Serial.println("Yukita Alpha");

  // start the Ethernet connection:
  // NOTE: Alternatively, you can assign a fixed IP to configure your
  //       Ethernet shield.
  //       Ethernet.begin(mac, ip);   
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  

  // print your local IP address:
  Serial.print("Yukita's IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
    
  }
  Serial.println(" ");

  Udp.begin(serverPort);
  
  
  
}

void loop(){
  //process received messages
  OSCMsgReceive();
}


void OSCMsgReceive(){

  OSCMessage msgIN;
  int size;
  if((size = Udp.parsePacket())>0){
    while(size--)
      msgIN.fill(Udp.read());
    if(!msgIN.hasError()){
      msgIN.route("/Controls/plowUp",plowUp); //if plowUp is toggled go to the plowUp code
      msgIN.route)"Controld/plowDwn",plowDwn); //if plowDwn is toggled go to the plowDwn code
      msgIN.route("/Controls/rightMotor",rightMotorCode); //if rightMotor is toggled go to the rightMotor code
      msgIN.route("/Controls/leftMotor",leftMotorCode); //if leftMotor is toggled go to the leftMotor code
      msgIN.route("/Controls/lights",lxCode); //if lights are toggled go to the lighting code
    }
  }
}

void plowUp(OSCMessage &msg, int addrOffset){
  plowState = (boolean) msg.getFloat(0);
  OSCMessage msgOUT("/Controls/plowUp");

  digitalWrite(plowPinUp, plowState);

  msgOUT.add(plowState);
  if (plowState) {
    Serial.println("PlowUp State on");
  }
  else {
    Serial.println("PlowUp State off");
  }

  plowState = !plowState;		 // toggle the state from HIGH to LOW to HIGH to LOW ...

  
  //send osc message back to controll object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface whe the conrol receives this message.
  Udp.beginPacket(Udp.remoteIP(), destPort);
  msgOUT.send(Udp); // send the bytes
  Udp.endPacket(); // mark the end of the OSC Packet
  msgOUT.empty(); // free space occupied by message
}

void plowDwn(OSCMessage &msg, int addrOffset){
  plowState = (boolean) msg.getFloat(0);
  OSCMessage msgOUT("/Controls/plowDwn");

  digitalWrite(plowPinDwn, plowState);

  msgOUT.add(plowState);
  if (plowState) {
    Serial.println("PlowDwn State on");
  }
  else {
    Serial.println("PlowDwn State off");
  }

  plowState = !plowState;		 // toggle the state from HIGH to LOW to HIGH to LOW ...

  
  //send osc message back to controll object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface whe the conrol receives this message.
  Udp.beginPacket(Udp.remoteIP(), destPort);
  msgOUT.send(Udp); // send the bytes
  Udp.endPacket(); // mark the end of the OSC Packet
  msgOUT.empty(); // free space occupied by message
}

void rightMotorCode(OSCMessage &msg, int addrOffset){
  rightMotorState = (boolean) msg.getFloat(0);
  OSCMessage msgOUT("/Controls/rightMotor");

  digitalWrite(rightMotorPin, rightMotorState);

  msgOUT.add(rightMotorState);
  if (rightMotorState) {
    Serial.println("Right Motor on");
  }
  else {
    Serial.println("Right Motor off");
  }

  rightMotorState = !rightMotorState;		 // toggle the state from HIGH to LOW to HIGH to LOW ...

  //send osc message back to controll object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface whe the conrol receives this message.
  Udp.beginPacket(Udp.remoteIP(), destPort);
  msgOUT.send(Udp); // send the bytes
  Udp.endPacket(); // mark the end of the OSC Packet
  msgOUT.empty(); // free space occupied by message
}
void leftMotorCode(OSCMessage &msg, int addrOffset){
  leftMotorState = (boolean) msg.getFloat(0);
  OSCMessage msgOUT("/Controls/leftMotor");

  digitalWrite(leftMotorPin, leftMotorState);

  msgOUT.add(leftMotorState);
  if (leftMotorState) {
    Serial.println("Left Motor on");
  }
  else {
    Serial.println("Left Motor off");
  }

  leftMotorState = !leftMotorState;		 // toggle the state from HIGH to LOW to HIGH to LOW ...

  //send osc message back to controll object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface whe the conrol receives this message.
  Udp.beginPacket(Udp.remoteIP(), destPort);
  msgOUT.send(Udp); // send the bytes
  Udp.endPacket(); // mark the end of the OSC Packet
  msgOUT.empty(); // free space occupied by message
}
void lxCode(OSCMessage &msg, int addrOffset){
lxState = (boolean) msg.getFloat(0);
OSCMessage msgOUT("/Controls/lights");

digitalWrite(lxPin, lxState);

msgOUT.add(lxState);
if (lxState) {
  Serial.println("Lights on");
}
else {
  Serial.println("Lights off");
}

lxState = !lxState;		 // toggle the state from HIGH to LOW to HIGH to LOW ...


//send osc message back to controll object in TouchOSC
//Local feedback is turned off in the TouchOSC interface.
//The button is turned on in TouchOSC interface whe the conrol receives this message.
Udp.beginPacket(Udp.remoteIP(), destPort);
msgOUT.send(Udp); // send the bytes
Udp.endPacket(); // mark the end of the OSC Packet
msgOUT.empty(); // free space occupied by message
}
