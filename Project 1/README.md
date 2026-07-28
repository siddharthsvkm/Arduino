# Joystick Position and LED Controller
Siddharth Sivakumar (siddharthsvkm)
July 27, 2026
Emulated using Wokwi

## Summary
This project uses a joystick to control a virtual position and a set of LEDs on the breadboard. The virtual position uses xy coordinates (x,y) and increases/decreases infinitely. When the joystick is pushed towards a relative/spatial direction, the corresponding LED light is turned on. In the instance where the joystick is pushed in two directions (e.g. left and down), the two RGB LEDs, towards the top of the breadboard, light up with the combined color made from mixing the colors of the LED, as well as the two LED lights (in their color) corresponding to those directions.

## Used Components:
- 1x MEGA Controller Board
- 1x Joystick
- 1x LCD (16x2)
- 2x RGB LED
- 4x LED (Purple, Red, Blue, Green)
- 1x Potentiometer
- 10x 220Ω Resistors
- 1x 10kΩ Resistor
- 37x Jumper Wires

## Reflection
I tried to reduce the number of conditional statements in my code by creating arrays and using mathematical equations to access the elements, instead of using a conditional statement and assigning values to variables within the conditional. This goal was hard to implement because coming up with the equations was actually quite difficult for me.
