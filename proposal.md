
Here is a suggested outline for your proposal. You don't need to follow this
outline, but it may help you focus your project.

* Project title
* Team members
* Description (1 pp describing the basic idea)
* Hardware required (itemize what hardware, if any, you need)
* Funds requested (the amount you will want to be reimbursed, remember you have
  a $20 budget per person)
* Major task breakdown and who is responsible for each task
* Goals for next week
* References and resources used

# Stick Figure Camera Thingy 

## Team Members: 
 * Lydia Chan
 * Andy Khuu

## Description: 
Stick Figure Camera Thingy is a project based on  love for stick figures and our desire to create something which is fun and interactive. The project will utilize a thermal camera from Adafruitour in order to track the major limbs of the body which through heuristic calculations will be able to draw the person in frame as a stick figure! The stick figure will act as the player who will go interact with the project through a variety of features such as picking up and dodging balls from the sky! More features to accompany the Stick Figure Camera Thingy Project to come later on. (Human Space Invaders, PacMan, etc.) 

## Hardware Required: 
* Adafruit AMG8833 IR Thermal Camera Breakout
* Monitor
* HDMI Cables
* Raspberry Pi, Breadboard, and Jumper Cables

## Funds Requested
* $40(hard cold ca$h)

## Major task breakdown and who is responsible for each task
- [ ] Sensor Interfacing - Andy <br/>
  * Utilize I2C protocol to interface with camera <br/>
  * Process and interpolate the data values <br/>
- [ ] Graphics Displaying - Lydia <br/>
  * Optimize writing graphics data to monitor to be fast and efficient <br/>
  * Handle drawing nice lines, arcs, and circles <br/>
- [ ] Player Handler - Andy and Lydia <br/>
  * Uses sensor values to decide location and sizes of stick figure elements  <br/>
  * Implement representation of stick figure  <br/>
- [ ] Game - Andy and Lydia <br/> 
  * Integrate game elements (balls) <br/>
  * Collision detection <br/>
  * Implement interaction and motion of game elements <br/>

## Goals for Next Week:
3/7: Plan out foundational outline of functions and classses <br/>
3/8: Sensor Arrives. Implement I2C/Thermal Camera Drivers necessary to obtain data and visualize it on the monitor <br/>
3/10: Have heuristic functions and calculations needed to draw stick figure person <br/>

## Timeline:
3/7: Plan out foundational outline of functions and classses <br/>
3/8: Sensor Arrives. Implement I2C/Thermal Camera Drivers necessary to obtain data and visualize it on the monitor <br/>
3/10: Have heuristic functions and calculations needed to draw stick figure person <br/>
3/12: Implement optimizations necessary to demo the live refreshing of a stick figure being moved on the monitor <br/>
3/14: Have Collision Detection completed and "balls from sky" working <br/>
3/18: Pick up ball feature working! <br/>
3/22: DONE :) <br/>

## References and Resources Used:
 * Bresenham's Circle Algorithm<br/>
 * Adafruit documentation<br/>
 * CS107E I2C Support Code<br/>

