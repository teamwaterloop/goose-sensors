# Balluff photoelectric contrast sensor

This is a simple explanation of how to use the Balluff BKT0005 photoelectric contrast sensor. The sensor is used to measure contrast of a marking on a given background. Here is a simple scheme of the wiring you should use.
![Alt text](/screenshots/a.jpg?raw=true)
As you can see, there are four subwires inside the Balluff's sensor wire. The brown subwire is for the positive probe of your battery while the blue subwire is for the negative probe of your battery. The white subwire is your analog out signal, which tells the value of the contrast read, and the black wire is for your PNP interface (digital pin that has a value of 1 if the wiring is set to PNP mode).
![Alt text](/screenshots/b.jpg?raw=true)
Here we connect our power wires to the battery.
![Alt text](/screenshots/c.jpg?raw=true)
Here, we connect our  signal wires to our Elegoo 2560 board. The white wire goes at Analog 8 and the green wire (connected to the black subwire) goes to Digital 24 to correspond to our example code.
![Alt text](/screenshots/d.jpg?raw=true)
Here, the sensor is set at a range of 9mm from the marking. The sensor has a tolerance of plus or minus 3mm. To read in static setting, we want to let the sensor as shown and press the SET key until "SEt1" appears on the screen. The sensor's emission will change color to determine the best for this marking. When "SEt2" appears on the screen and the OUT led blinks, we must have the background under the beam and not move it during the scan. After that, we must press SET to let the sensor change its beam color again. After this, the sensor is correctly set and ready as soon as the RDY led turns on. To restart in case of an error, press SET once. For information on how to use the sensor in a dynamic setting or for a lot more details, please follow this link to Balluff's website where you can find the complete instruction manual and other useful ressources: https://www.balluff.com/local/ca/productfinder/#?data=selection%5Bca%5D%3DA0001%26selection%5Bcg%5D%3DG0103%26selection%5Bproduct%5D%3DF01324%26selection%5Bproduct_variant%5D%3DPV123248
![Alt text](/screenshots/e.jpg?raw=true)
