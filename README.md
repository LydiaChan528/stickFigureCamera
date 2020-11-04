# Stick Figure Simulator

by [Andy Khuu](https://github.com/AndyLKhuu) and [Lydia Chan](https://github.com/LydiaChan528)

Stick Figure Simulator is a lenses through which you can see yourself as a stick figure! Based on our love for
stick figures and animations, this project allows you to become a stick figure in a fun and interactive way - 
it's like being in your own comic. 

We used a thermal camera from Adafruit in order to track the motion of the user, based on the person's head and arms, 
and draw them as a stick figure in the frame. The player can interact with on-screen elements, like balls falling from the sky. 
But it's game over if they are hit.

Below is a breakdown of what each of us designed and created for this project:
### Both

- Interface with thermal camera through I2C protocol
- Implement motion and redrawing of game elements
- Integrate all parts
  <img src="https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/gameInAction.png" width="50">
  
  <img src="https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/gameOver.png" width="50">
  
 
### Andy: 
- Interpolation of thermal camera data from 8x8 to 29x29
- Game mechanics: element boundaries and collision detection
  <img src="https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/No%20interpolation.PNG" width="100">
  <img src="https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/15x15.PNG" width="200">
  <img src="https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/29x29.PNG" width="200">

### Lydia: <br/>
- Stick Figure: heuristic head and arm detection from camera data <br/>
  ![Stick Figure](https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/stickFigureRendering.png)
- Graphics: rendering lines, circles, and stick figure** <br/>
  ![Arm Detection](https://github.com/LydiaChan528/stickFigureCamera/blob/master/images/armDetection.png)
  ![Thermal Camera Data for Head/Arm Detection, Case 1](images/headArmDetection.png)
  ![Thermal Camera Data for Head/Arm Detection, Case 2](https://github.com/cs107e/AndyLKhuu-lchan528-project/blob/master/images/headArmDetection2.png)

Sources <br/>
(*)We used the I2C driver in the CS107E library.<br/>
(**)The circle-drawing algorithm is based the Mid-Point Circle Drawing Algorithm from GeeksforGeeks.<br/>

