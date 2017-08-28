# Arduino Pong
By Stephen Miller

A simple two player Pong game, made using Arduino UNO and TVout Library.

# How to build it
You will need a:
- Arduino UNO/NANO (Other versions work too)
- Breadboard (Or solder the whole thing together)
- 2 x Potentiometer
- 1 x Button
- 1 x 470Ω resistor
- 1 x 1kΩ resistor
- 1 x 10kΩ resistor
- RCA cable
- TV/Monitor
- [TVout library](http://github.com/Avamander/arduino-tvout)

![Circuit Diagram](https://raw.githubusercontent.com/stephenmiller04/ArduinoPong/master/circuit_diagram.png)

Connect everything to the right place, then grab an RCA cable, it has two cables inside if you cut the cable. Video and ground, the inner cable is the video cable, the outer is the ground, I marked the video cable with yellow color on the diagram (inner cable) and with black color the ground (outer cable). If you are connected everything correctly, plug your Arduino into your PC, download the *TVout library* which you can found [here.](http://github.com/Avamander/arduino-tvout) Copy the content of the ZIP into *Documents/Arduino/Library*. If you are done with this, launch the Arduino IDE, open my code and upload it to your Arduino. That's all!
If you are done everything right, the game will show up on the connected Monitor/TV, push the button and you can play the game, enjoy!

Stephen Miller © 2017
[www.stephenmiller.hu](www.stephenmiller.hu)