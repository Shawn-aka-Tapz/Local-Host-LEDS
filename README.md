# Local-Host-LEDS
This is a code that can be loaded onto an ESP82666 arduino board and allows users to control the lights. 

#####IMPORTANT#####
If you are using a long LED strip you will have to change number of LEDS in the code and also use an external power source to power the LEDS.
The ground wire should run from your power source and split into the arduino an into the LED strip.
It may also be necessary to connect 5V/data/G from both ends to limit voltage drop

For setup:
1. Make sure that the LEDS are suitable for 5V use do not go over the required voltage as it will fry the strip
2. Connect the LED strip to the arduino board make sure the ground and 5v wires are lined up right
3. Ensure that the data pin is connected to arduino GPIO Digital 4
4. Copy paste the code into a sketch and replace placeholders with wifi name, wifi pasword. 
5. Ensure that all ports are right and number of LEDS are correct
6. Upload the code to arduino and open up the serial monitor and set it to 115200 baud 
7. Wait for the dots and an IP will show up
8. Connect to that IP on your browser and enjoy

####EXTRAS#####
I will be keeping this updated as I make patterns this is the base and more will be added if changes are made just do steps 1-8 again with the new code. 


What I used to build the project:
- LEDS: https://www.amazon.ca/gp/product/B01LSF4QDM/ref=ppx_yo_dt_b_asin_title_o00?ie=UTF8&psc=1
- ARDUINO BOARD: https://www.amazon.ca/gp/product/B076F53B6S/ref=ppx_yo_dt_b_asin_title_o01?ie=UTF8&psc=1 (3 pack)
- JUMPER WIRES: https://www.amazon.ca/IZOKEE-240pcs-Solderless-Breadboard-Arduino/dp/B08151TQHG/ref=sr_1_3?dchild=1&keywords=jumper+wires&qid=1598310417&s=electronics&sr=1-3 (variety pack)
