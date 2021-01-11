#include <Wire.h>
#include <WiFi.h> 
#include <IRremote.h>

const char* ssid = "ESP32";
const char* password = "123456789";

WiFiServer server(80);

//Variable to store the header HTTP request
String header;

int st = 0; //st(state of the robot)

// Sound sensor pin
int soundSensor=19;

// variable to store the incoming data from th Slave(Arduino)
int c;

//IR reciever pin
#define IRPIN 18

IRrecv irrecv(IRPIN);
decode_results results;

 
void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting a Connection....");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(IP);
  server.begin();  
   Wire.begin();

  pinMode(soundSensor,INPUT);
   irrecv.enableIRIn();

}
 
void loop() {
// Getting data from the Arduino (Slave)
Wire.requestFrom(0x04,1);

  c=Wire.read();
  Serial.print(c);
   
   if (c==0){
        st=5;}
   else if (c==2){
       st=0;  
   }
   else if (c==3){
        st=1;}
//Variable to store the digital value of the sound sensor        
int ssd=digitalRead(soundSensor); 
        
 WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client is connected.");// print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Checking which button was pressed on the HTML page
            // Getting the required robot state from the header of the webpage and change the st value depending on each header
            if (header.indexOf("GET /forward") >= 0) {
              st = 1;
            } else if (header.indexOf("GET /stop") >= 0) {
              st = 0;
            } else if (header.indexOf("GET /back") >= 0) {
              st = 2;
            } else if (header.indexOf("GET /right") >= 0) {
              st = 3;
            } else if (header.indexOf("GET /left") >= 0) {
              st = 4;
            } 


            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // The background color and font-size attributes 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Osama's Robot</h1>");
            // Displaying the buttons on the webpage according to the state(st) of the robot
            if (st==0) {
              client.println("<p><a href=\"/forward\"><button class=\"button\">Forward</button></a></p>");
              client.println("<p><a href=\"/back\"><button class=\"button\">Back</button></a></p>");     
              client.println("<p><a href=\"/right\"><button class=\"button\">Right</button></a></p>");       
              client.println("<p><a href=\"/left\"><button class=\"button\">Left</button></a></p>");
              client.println("<p><a href=\"/stop\"><button class=\"button button2\">Stop</button></a></p>");
              
            } else if (st==1) {
              client.println("<p><a href=\"/forward\"><button class=\"button button2\">Forward</button></a></p>");
              client.println("<p><a href=\"/back\"><button class=\"button\">Back</button></a></p>");     
              client.println("<p><a href=\"/right\"><button class=\"button\">Right</button></a></p>");       
              client.println("<p><a href=\"/left\"><button class=\"button\">Left</button></a></p>");
              client.println("<p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p>");
              
            } 

             else if (st==2) {
              client.println("<p><a href=\"/forward\"><button class=\"button\">Forward</button></a></p>");
              client.println("<p><a href=\"/back\"><button class=\"button button2\">Back</button></a></p>");     
              client.println("<p><a href=\"/right\"><button class=\"button\">Right</button></a></p>");       
              client.println("<p><a href=\"/left\"><button class=\"button\">Left</button></a></p>");
              client.println("<p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p>");
              
            } 
                else if (st==3) {
              client.println("<p><a href=\"/forward\"><button class=\"button\">Forward</button></a></p>");
              client.println("<p><a href=\"/back\"><button class=\"button\">Back</button></a></p>");     
              client.println("<p><a href=\"/right\"><button class=\"button button2\">Right</button></a></p>");       
              client.println("<p><a href=\"/left\"><button class=\"button\">Left</button></a></p>");
              client.println("<p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p>");
              
            } 
                else if (st==4) {
              client.println("<p><a href=\"/forward\"><button class=\"button \">Forward</button></a></p>");
              client.println("<p><a href=\"/back\"><button class=\"button\">Back</button></a></p>");     
              client.println("<p><a href=\"/right\"><button class=\"button\">Right</button></a></p>");       
              client.println("<p><a href=\"/left\"><button class=\"button button2\">Left</button></a></p>");
              client.println("<p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p>");
              
            } 
              
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client is disconnected.");
    Serial.println("");
  }

  
//Sound sensor code
if(ssd==1){
           if(st==0){
              st=1;}
           else{
              st=0;}
           }

// IR reciever code                    
if (irrecv.decode(&results)) {
      Serial.println(results.value);
      
      switch (results.value) {
        
         case 16718055:            
            st=1;
            break;

         case 16716015:            
            st=4;
            break;
               
         case 16726215:            
            st=0;
            break;

         case 16734885:            
            st=3;
            break;
 
         case 16730805:            
            st=2;
            break;
 
         
         }      
   irrecv.resume();
   }

// Transmission of the data from the Esp32(Master) to Arduino(Slave)                    
  delay(50);
  Wire.beginTransmission(0x04);
  Wire.write(st);
  Wire.endTransmission();
 
}
