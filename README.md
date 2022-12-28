# Raspberry Pi GPIO control with HTTP protocol
Controlling Raspberry PI GPIO pins (using pigpio) using HTTP protocol via raw TCP sockets in C.

The current layout of the program only has a GPIO PIN 24 as OUT. It has an LED with a 220 ohm resistor as the current layout.

## Usage
`sudo ./webserver [--port | -p] <port-no>`
