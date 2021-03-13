# Insignia-Receiver-RE
Reverse engineering an old Insignia Receiver for no reason at all

# Project Description
This project aims to take a working Insignia 2 channel stereo receiver and replace the main control chip (a small, undocumented IC) and replace it with an Arduino that will perform much of the same function.

Initially, the goal of this project was to see if it was possible to re-program the original control chip, but after extensive research to find any information on it, I determined that short of exposing the die and mapping the chip with a microscope, there was no way I was going to get anything close to a datasheet on it. There is also a fairly high chance that even with all that effort, the main firmware will be in ROM and therefore completely unwritable. Instead, we will isolate the chip completely, and maybe remove it from the board once all functions have been sufficiently emulated.

I have identified 3 separate challenges:
1. The Display Controller
2. The Volume, Input and EQ Controller
3. Ancillary functions like the front panel buttons, volume control and radio module

Each will be tackled somewhat individually and combined at the end in order to create our own firmware to run the device.

# Display Controller

This Insignia receiver uses an actual VFD for the display. In a world of fake VFD lookalikes using LCD panels (all of which don't quite match the clarity and brilliance of a true VFD) this was surprising in a unit as cheaply made as this one. Interestingly enough, there's a separate secondary on the main transformer to supply low voltage AC to the filament wires that connects directly to this board.

The VFD controller is a Silan Microelectronics SC16315. It's a fairly basic display controller that also has a few ancillary functions that aren't actually used in this application. It communicates with the main processor with a synchronous serial connection using simple commands of 1 byte each. It has built in memory of 24 bytes that it scans through automatically to light up the segments associated with each byte. The display controller is also capable of scanning and reporting buttons connected to it's multipurpose segment/key outputs, but this functionality is not used here. In fact, the serial out pin is completely disconnected.

The VFD controller also has 4 LED outputs that are used to turn on and off the two speaker select relays and the main amplifier relay. This is likely because it was simpler to use the built in LED outputs than add provisions for high current outputs on the main processor, despite the added cost of adding 3 more conductors to the flat flex cable that connects the two boards.

It is clear that this display board is used on multiple models because there are a significant amount of segments that correspond to features this unit does not have.

Despite the buttons being on the same physical board, they are completely disconnected from the VFD controller itself. I suspect they are simple resistor ladder type buttons and the main board uses an analog input for each of them.
