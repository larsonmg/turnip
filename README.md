Turnip
===

Turnip is a small project developed for the completion of EEP520 at the University of Washington. It contains a maze that was built using the Enviro  enviroment and a simulated robot that uses Enviro and Elma to navigate the constructed maze.

Installation
===

The source code for Elma [is on Github](https://github.com/klavinslab/elma).

From Dockerhub
---

To get started, you will need a C++ build environment. We have provided one with the Docker container `elma`, which you can use as follows:

    git clone https://github.com/klavinslab/elma.git
    cd elma
    docker run -v $PWD:/source -it klavins/elma:latest bash
    make
    examples/bin/basic

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