# Insignia-Receiver-RE
Reverse engineering an old Insignia Receiver for no reason at all

# Project Description
This project aims to take a working Insignia 2 channel stereo receiver and replace the main control chip (a small, undocumented IC) and replace it with an Arduino that will perform much of the same function.

Initially, the goal of this project was to see if it was possible to re-program the original control chip, but after extensive research to find any information on it, I determined that short of exposing the die and mapping the chip with a microscope, there was no way I was going to get anything close to a datasheet on it. There is also a fairly high chance that even with all that effort, the main firmware will be in ROM and therefore completely unwritable. Instead, we will isolate the chip completely, and maybe remove it from the board once all functions have been sufficiently emulated.
