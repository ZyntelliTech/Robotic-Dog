# Robotic-Dog

## Project Description

This project aims to independently develop a high-performance robot dog capable of free movement in three-dimensional space. The robot weighs 10 kg and has an arm span of approximately 100 cm. It uses brushless servo motors to control joint motion and achieves efficient control via CAN communication.

![Robotic Dog](/images/RoboticDog.jpg)

## Hardware Design
### Powertrain : 
- Each leg is equipped with three motors to ensure flexible movement in three-dimensional space. The knee joint motor is driven by a synchronous belt design to reduce energy loss during movement.
### Control system :
*  Host computer: Use NVIDIA Orin NX high-performance computer to support high-computing power applications.
* Lower computer: It consists of two STM32H7 microcontrollers, which communicate with the upper computer through SPI, parse instructions and control the motor.
* Power management: Implement three-way Buck switch step-down voltage regulator circuits of 24V-19V, 19V-5V, and 5V-3.3V, with load ripple within 30mV.
* Communication : Four CAN buses achieve a communication rate of 1Mbps, and the SPI bus supports a speed of 16Mbps, ensuring efficient and stable data transmission.

## Software Design
### Control program : 
- The host computer implements the underlying SPI sending program and gait planning program. At the same time, a Xiaomi motor driver library is developed to support control through ROS or C++.
### IoT integration : 
- Through the MQTT protocol, the robot dog's sensor data is uploaded to the IoT platform and visualized on the web to enhance the user experience.

## Mechanical Design
### Component design : 
- A total of 79 components and 276 bolt holes were designed (incomplete statistics), and the design was verified through over 100 3D printing tests to ensure its feasibility and stability.
### Material selection : 
- CNC-processed aluminum alloy parts were finally used for assembly to improve the structural strength and durability of the robot dog.

## Project Properties
### System Architecture:

- Mainly composed of upper computer, lower computer, motor and mechanical structure

- The lower computer system is composed of two STM32H7 and peripheral circuits to realize a three-level synchronous buck circuit, two SPI buses, four CAN buses, and mount 12 joint servo motors respectively.

- The lower computer and the upper computer use the SPI protocol for high-speed communication to meet the high real-time and high-frequency motion control and posture monitoring communication requirements.

- The host computer system consists of JETSON-ORIN NX and external devices to achieve posture analysis and control, laser SLAM, environment modeling, autonomous motion and navigation

### Mechanical structure:

- The mechanical structure consists of four mechanical legs, the robot body, and internal and external equipment fixing frames.

- The following is a detailed explanation of the design of the mechanical legs:

- The robotic leg consists of three joint motors and a transmission structure. The three joint motors are integrated at the hip joint through the transmission structure to reduce motion inertia.

- The overall structure is as follows:

![Robotic Dog](/images/Leg.jpeg)

- Specific structural BOOM diagram (this diagram is generated for the initial version of the structure, but only some dimensions were changed later, and the overall structure remained unchanged):

![Robotic Dog](/images/Leg%20Assembly.png)

- The overall structure of the robot dog:

![Robotic Dog](/images/Dog%20Assembly.jpeg)

### Lower computer system

- Connect to the host computer via a 40PIN cable and fix it to the host computer hole position via M3 copper pillars
- The main controller is two STM32H750RCT6
- It is equipped with four CAN buses, each of which is equipped with three servo joint motors, for a total of 12 servo motors. The maximum baud rate is 1M.
- Two SPI channels, responsible for communication between each microcontroller and the host computer, with a maximum baud rate of 15M
- Onboard MPU6050 gyroscope
- Three DC-DC converters provide synchronous step-down voltages: 24V to 19V, 19V to 5V, and 5V to 3.3V. The 19V voltage powers the ORIN NX robot dog host computer (XT30), while the 5V and 3.3V voltages power the microcontroller system.
- It also integrates a power distribution board, which can provide four 24V XT60 interfaces and one 24V XT30 interface.