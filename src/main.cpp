#include <ncurses.h>
#include "Maze.h"

/**
 * Sample program for the Maze Class. It creates a maze and the generates the
 * maze with an animation in 500 ms steps. After that it also prints the
 * resulting maze to stdout
*/
int main(void)
{
  initscr();
  Maze maze = Maze(6, 6);
  maze.generate(500);
  endwin();
  maze.print(false);

  return 0;
}
