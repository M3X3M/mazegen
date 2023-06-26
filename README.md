# mazegen

Welcome to mazegen. A very simple tool to create mazes from the command line.  

![Generation Example](res/maze-example.gif)

## GENERAL

This project was created to learn more about the magic of creating mazes. 
Currently it only features the very simple [recursive backtracking algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm). 
The tool allows for easy visualisation of the creation process by using [ncurses](https://invisible-island.net/ncurses/). 

## USAGE

### Linux

To quickly get started with the project clone the repository to your device.  
Change directory into the cloned repository.
~~~bash
cd mazegen
~~~
A simple example for the maze generation is available as the *example* Makefile target. It will create a 8 by 8 maze with 100 miliseconds steps in the animation process.
~~~bash
make example
~~~
To customize the creation process one can call the program itself 
with the needed flags. Compilation is required first using:
~~~bash
make compile
~~~
The compiled binary is located in the *build/* folder of the project and can be called with:
~~~bash
./build/mazegen.out -x 6 -y 10 -a 20
~~~
This will create a maze of width 6 and height 10. The *-a* flag 
controlls the animation of the creation process. If it is not 
provided or 0 no animation and only the finished maze will be displayed. If it is provided it specifies the time each animation step will take (in miliseconds).  
In the maze the startpoint and the endpoint are marked with *S* and *E* respectivly.

## CONTRIBUTION

Feel free to experiment with the software. Contribution to the repository is welcomed.

