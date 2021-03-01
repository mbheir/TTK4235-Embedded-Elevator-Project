# Elevator Project 
This project was a part of the course TTK4235 - Embedded Systems at NTNU.

## Description
This software is designed to control a single elevator across ```n``` floors. The software reads inputs from buttons, just like a normal elevator and commands the elevator to take action. It is spesifically designe for the elevators at NTNU sanntidsal, but a simulator is aslo provided. 

The underlying design is based on a simple state machine structure
![image](https://user-images.githubusercontent.com/55540484/109494767-9f361b00-7a8e-11eb-8137-5b507543065e.png)
## Instructions

1. Clone the repolistory
2. To run on the simulator, set SIM=true in Makefile. To run on the lab, set SIM=false. 
3. Run `make`, to build executable
4. Run ```./elevator``` to run the executable
