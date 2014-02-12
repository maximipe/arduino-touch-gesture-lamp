An arduino touch & gesture lamp
========================

This is my graduation project for my design degree. 
The program uses the data from an ultrasonic distance sensor to handle a servo motor connected to an
iris placed on top of a desktop lamp, in that way that the user controlls the light intensity by manipulating
the circle of light projected by the lamp on the table surface.

When the hand gesture runs from the enlighted area towards the sensor, the sketch maps the distance to angular
movement to run the servo, in this case to gradually open the iris. When the user make a gesture that runs away 
from the sensor, the opposite occurs.

<h2>Content</h2>

The sketches are divided into two groups, to handle the device wirelessly and by cable. Transmisor and receptor
sketches handle the wireless communication (using the Manchester library) besides the instructions for the sensor
and the servo. Prototipo is the wired more simplified version, containing the whole program in one sketch. 
