# Elevator Project 
This project was a part of the course TTK4235 - Embedded Systems at NTNU.

## Description
This software is designed to control a single elevator across ```n``` floors. The software reads inputs from buttons, just like a normal elevator and commands the elevator to take action. It is spesifically designed for the hardware on the NTNU real-time lab elevators, but a simulator is also provided. 

The underlying design is based on a simple state machine structure
![image](https://user-images.githubusercontent.com/55540484/109494767-9f361b00-7a8e-11eb-8137-5b507543065e.png)
## Instructions

1. To use with the simulator, set `SIM=true` in Makefile and build using `make`.
2. Run `./SimElevatorServer` binary to start the simulator. 
3. Run ```./elevator``` binary to run the controller code. 

## Simulator Instructions
- Up: *QWE*
- Down: *ASD*
- Cab: *ZXCV*
