/*
Changes:
IP address is sent over OSC to the control device
Software version number is sent over OSC to the device
plowUp and plowDwn code changed to plowCode
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
  
const long interval = 1000;
unsigned long previousMillis = 0;
const long interval1 = 1000;
unsigned long previousMillis1 = 0;
char ip[12] = "192.168.0.3";
char version[9] = "0.0.3";
int serverPort  = 8000; //TouchOSC (incoming port)
int destPort = 9000;    //TouchOSC (outgoing port)

int rightMotorPin =  3;       
int leftMotorPin =  5;       

int plowPin = 6;       
int lxPin = 9;       

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
  
  Serial.begin(9600); //9600 for a "normal" Arduino board (Uno for example). 115200 for a Teensy ++2 
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
  unsigned long currentMillis1 = millis();
  if(currentMillis1 - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis1;   
    
    
    const char version[9] = "0.0.3";
    
    
    OSCMessage versionmsgOUT("/Yukita/Version");
    
    versionmsgOUT.add(version);
    
    
    Udp.beginPacket(Udp.remoteIP(), destPort);
    
    versionmsgOUT.send(Udp);
    
    
    Udp.endPacket(); // mark the end of the OSC Packet
    
    versionmsgOUT.empty();
    
  }
  ipAddressSend();
  OSCMsgReceive();
}

void ipAddressSend(){
    

 unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    
    const char ip[12] = "192.168.0.3";
    
    
    OSCMessage ipmsgOUT("/Yukita/ipAddress");
    
    
    ipmsgOUT.add(ip);
    
    Udp.beginPacket(Udp.remoteIP(), destPort);
    
    ipmsgOUT.send(Udp); // send the bytes
    
    Udp.endPacket(); // mark the end of the OSC Packet
    
    ipmsgOUT.empty(); // free space occupied by message
  }
    
  
}

void OSCMsgReceive(){

  OSCMessage msgIN;
  int size;
  if((size = Udp.parsePacket())>0){
    while(size--)
      msgIN.fill(Udp.read());
    if(!msgIN.hasError()){
      msgIN.route("/Controls/plowUp",plowCode);
      msgIN.route("/Controls/rightMotor",rightMotorCode);
      msgIN.route("/Controls/leftMotor",leftMotorCode);
      msgIN.route("/Controls/lights",lxCode);
    }
  }
}

void plowCode(OSCMessage &msg, int addrOffset){
  plowState = (boolean) msg.getFloat(0);
  OSCMessage msgOUT("/Controls/plowUp");

  digitalWrite(plowPin, plowState);

  msgOUT.add(plowState);
  if (plowState) {
    Serial.println("Plow State on");
  }
  else {
    Serial.println("Plow State off");
  }

  plowState = !plowState;		 

  
  //send osc message back to control object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface when the control receives this message.
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

  rightMotorState = !rightMotorState;		 

  //send osc message back to control object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface whe  the control receives this message.
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

  leftMotorState = !leftMotorState;		 

  //send osc message back to control object in TouchOSC
  //Local feedback is turned off in the TouchOSC interface.
  //The button is turned on in TouchOSC interface when the control receives this message.
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

lxState = !lxState;		 


//send osc message back to control object in TouchOSC
//Local feedback is turned off in the TouchOSC interface.
//The button is turned on in TouchOSC interface when the control receives this message.
Udp.beginPacket(Udp.remoteIP(), destPort);
msgOUT.send(Udp); // send the bytes
Udp.endPacket(); // mark the end of the OSC Packet
msgOUT.empty(); // free space occupied by message
}
