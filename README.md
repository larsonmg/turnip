Turnip
===

Turnip is a small project developed for the completion of EEP520 at the University of Washington. It contains a maze that was built using the Enviro  enviroment and a simulated robot that uses Enviro and Elma to navigate the constructed maze. The robot uses a wall following routine to follow the right hand wall to the end of the maze. This method allows it to navigate complex mazes with dead ends. When the robot completes the maze a message is displayed in the terminal and the robot is reset.

Key Challenges
===
Challenge 1:
I wanted the robot to be able to navigate any maze that is given to it without a predetermined path. This lead to research on the suggest methods including the wall fallowing method. Somewhat unintuitively a robot that follows a singe wall for long enough will always find the end of the maze. This ended up being a reasonbly approachable and effective method.

Challenge 2:
Initially friction between the robot and the wall eventually caused the robot to get stuck. To simplify the process and avoid failures, friction between the robot and wall was disabled.

Challenge 3:
Determining the end of the maze. Initially I tried using a block at then end of the maze to detect a collision with the robot and trigger the robot to be reset. This unfortunately caused weird bugs and the occasional "segmentation error". I overcame this by using the robot's position to determine when it has reached the top-right corner of the maze.

Installation
===

The source code for Elma [is on Github](https://github.com/klavinslab/elma).

From the Dockerfile
---

You can also build the docker environment, described in env/Dockerfile, yourself, with the following commands. These commands were tested using git bash within VS Code:

    git clone https://github.com/larsonmg/turnip.git
    cd turnip
    docker run -p80:80 -p8765:8765 -v "/$(pwd -W):/source" -it klavins/enviro:alpha bash
    esm start
    enviro

Sources:
- The below link from allaboutcircuits.com was used as the coneptual basis for the wall following code implemented for this project. The truth table supplied was the main resource utilized.
https://www.allaboutcircuits.com/projects/how-to-build-a-robot-follow-walls/
- This project uses Enviro and Elma provided through the EEP 520 course

This software is open source and uses the MIT license. Details can be found [here](https://github.com/klavinslab/elma).