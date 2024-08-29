# unfairUndyne
Ece 241 project


# # Running instructions:
To run the game you must create a new project on the Intel Monitor Program, and add the submitted header files and main file. Make sure that the main file is set as the top level program to ensure that the compiler builds the correct order of files. Compile the project with the NIOS II architecture and download it onto the FPGA. Plug in a PS2 keyboard and connect it to a speaker system. Enjoy and beat your friends in a fun competition!

Within the header files there are header guards to ensure compilation does not experience redefinitions when compiling. The headers themselves are also structured using external variables to allow for a hierarchy of headers to be used such that higher level header files already have lower level header files included for simplicity. There is also a magic number header file which is used for organizing any important values such as arrow speeds based on difficulty, input delays, clock speeds, hitboxes, animation frame rates, etc in order for easy modifications to be made to the game.
