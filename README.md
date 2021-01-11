In  this project a distributed and interactive systems has been implemented using a 2 wheel obstacle avoidence robot.
In this project Esp32 and Arduino uno has been connecting together and I2C communication has been chosen to be the way of communication between the two microcontrolleres.
The Esp32 has been set as a master and the Arduino as a slave.
Each microcontroller has its own code and the Arduino IDE was the software used write, compile and uploading the code to each microcontroller.
How to install Esp32 Board:
To use the Esp32 code with the Arduino IDE software, you shoud install Esp32 board first.
To do so, you should click on "file" then "preference",write this link https://dl.espressif.com/dl/package_esp32_index.json on the Additional Boards Manager URLs and press ok.
Click on "tools" then "boards" then "boards manager", search for Esp32 and then click install. Make sure to intsall the latest version.
Now the Esp32 boards have been added to the Arduino IDE.

Esp32 code:
We first start by including the libraries needed for this project. Then we define the pins connected to each sensor used. If you would like to change the pin connected to the sensor you can do so but you'll have to change the pin number in the code.
In Esp32 code there are two important variables that have been defined, c and st.The variable c is an integar which holds the data received from the arduino. Variable st is holding the data which the Esp32 sends to the arduino. he value of both variables changes while using the robot.
This code enables the Esp32 to create a standalone webserver that stores a webpage. The Esp32 is operated in the Soft Access Point (AP) mode. In this mode the Esp32 creates its own network and acts as a hub which set IP address to it.
The Esp32 prints the IP address on its serial monitor and uploading the code to the Esp32 board.
The webpage can be accessed by connecting any device that has a browser to the Esp32 network and typing the Esp32 IP address on the URL.This webpage consists of 5 buttons which enables the user to interact with the robot car by pressing any of these buttons.
The value of the variable st can be only one value from 0 to 5. When the user press the button stop the Esp32 changes the value of the variable st to 0.The five buttons are Forward, Backward, Right, Left and Stop. When the user press the button Forward the Esp32 changes the value of the variable st to 1 and if the user press the button Backward the Esp32 changes the st value to 2.and so on for the other 3 buttons. 
The webpage is not the only way of interaction with the robot. IR sensor and the sound sensor are another two ways of interaction with the robot
Each button on the remote control has its own code so when the user presses the upward arrow button of the remote, the Esp32 receives the code 16718055. In this case the Esp32 is programmed to change the st value st to 1. In the case of the user pressed the right arrow button it changes the value of the st to 3. When the user presses the ok button, the Esp32 changes the value of the st to 0 and so on for the backward and left arrows.
If the value of the st equal 0 and the sound sensor detects a loud noise sound, the ESP32 changes the vaue of the st to 1. If the value of the st was anything else except then the Esp32 changes its value to 0.
the variable c is used to store the received data from the arduino. If c = 0 then the Esp32 changes the st value to 5 but if the c value is 2 the Esp32 changes the value of the st to 0 and if the c value = 3 then the Esp32 changes st value to 1.
Each 50 milliseconds the Esp32 send the value of the st to the arduino using the I2C communication.

The two DC motors are connected to the arduino microcontroller which is responisble for moving the robot through these two DC motors
The The UltraSonic sensor which is used for the obstacle detection process is connected to the arduino.

Arduino Code:

In arduino code there are two important variables that have been defined, c and id. The variable c holds the data that the arduino sends to the Esp32 while the id variable holds the incoming data from the Esp32
when the ultrasonic sensor detects an object at a distance less than 15 cm, the arduino changes the c value to 0.
if the id (the variable holds the recevied data from the Esp32) = 0, the arduino stop the two DC motors. if it is 1 the arduino moves the robot in the forward direction. if the id value is 2, the car moves backward. If the id is 3 the arduino moves the robot in the right direction for 100 milliseconds and then change the value of the variable c to 3. In turn the Esp32 receives the new value of c and changes the stb value to 1 and send it to the arduino. if the value id is 4, the arduino moves the robot in the left direction for 100 milliseconds and change the value of variable c to 3. If the arduino recieves 5 as a value of id variable, then it stops the robot for 500 milliseconds and move backward for 500 milliseconds and change the value of the variable c to 2 to avoid the obstacle and wait for a new command from the Esp32.

