# Stick Figure Simulator

Stick Figure Simulator is a lenses through which you can see yourself as a stick figure! Based on our love for
stick figures and animations, this project allows you to become a stick figure in a fun and interactive way - 
it's like being in your own comic. 

We used a thermal camera from Adafruit in order to track the motion of the user, based on the person's head and arms, 
and draw them as a stick figure in the frame. The player can interact with on-screen elements, like balls falling from the sky. 
But it's game over if they are hit.

Below is a breakdown of what each of us designed and created for this project: <br/>
### Both: <br/>
- Interface with thermal camera through I2C protocol <br/>
- Implement motion and redrawing of game elements <br/>
  ![Game in Action](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/gameInAction.png)
- Integrate everything <br/>
  ![Game Over](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/gameOver.png)
### Andy: <br/>
- Interpolation of thermal camera data from 8x8 to 29x29 <br/>
  ![No Interpolation](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/No%20interpolation.PNG) <br/>
  
  ![15x15](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/15x15.PNG) <br/>
  
  ![29x29](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/29x29.PNG) <br/>
  
- Game mechanics: element boundaries and collision detection <br/>
### Lydia: <br/>
- Stick Figure: heuristic head and arm detection from camera data <br/>
  ![Stick Figure](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/stickFigureRendering.png)
- Graphics: rendering lines, circles, and stick figure <br/>
  ![Thermal Camera Data for Head/Arm Detection, Case 1](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/headArmDetection.png)
  ![Thermal Camera Data for Head/Arm Detection, Case 2](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/headArmDetection2.png)

The circle-drawing algorithm is based the Mid-Point Circle Drawing Algorithm from GeeksforGeeks.