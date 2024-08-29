# # unfairUndyne
Ece 241 project

# Description:
The game is based on a minigame of the video game Undertale. In this minigame there are two players. While one player shoots arrows at the heart, the other must block the incoming arrows using a shield. The game has two difficulties: “Pet the vegetables” (easy) and “Atone for my sins” (hard). You can change the difficulty from the main menu with the up and down arrows. When your desired difficulty is highlighted you can start the game by pressing the spacebar key.

# Running instructions:
To run the game you must create a new project on the Intel Monitor Program, and add the submitted header files and main file. Make sure that the main file is set as the top level program to ensure that the compiler builds the correct order of files. Compile the project with the NIOS II architecture and download it onto the FPGA. Plug in a PS2 keyboard and connect it to a speaker system. Enjoy and beat your friends in a fun competition!

Within the header files there are header guards to ensure compilation does not experience redefinitions when compiling. The headers themselves are also structured using external variables to allow for a hierarchy of headers to be used such that higher level header files already have lower level header files included for simplicity. There is also a magic number header file which is used for organizing any important values such as arrow speeds based on difficulty, input delays, clock speeds, hitboxes, animation frame rates, etc in order for easy modifications to be made to the game.
