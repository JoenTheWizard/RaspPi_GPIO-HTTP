# Raspberry Pi GPIO control with HTTP protocol
Controlling Raspberry PI GPIO pins (using pigpio) using HTTP protocol via Linux raw TCP sockets in C.

The current layout of the program only has a GPIO PIN 24 as OUT. It has an LED with a 220 ohm resistor as the current layout. For the webserver interface it has two options to turn on or off the LED. `Turn on` will send a GET response on `/on` and `Turn off` will send to `/off`. These request paths will handle the GPIO calls

## Usage
`sudo ./webserver [--port | -p] <port-no>`
