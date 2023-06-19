#include <cstdio>
#include <iostream>
#include <malloc.h>
#include <ncurses.h>
#include <new>
#include <string>
#include <unistd.h>
#include "Tile.h"

struct Point
{
  int x;
  int y;
};

struct Endpoint
{
  Point point;
  int distance;
};

class Maze
{
  private:

    Tile*** tiles;

    size_t height, width;

    /**
     * One recursion step in the maze generation algorithm. Moves if it has a
     * option to move forward or returns if not
     * @param anim_speed the delay of one animation step
     * @param start_pos the current position
     * @param recursion_depth the current depth of recursion used in the
     *   calculation of the end point
    */
    int walk(size_t anim_speed, Point start_pos, size_t recursion_depth);

    Point start_point;

    Endpoint end_point;

  public:

    /**
     * Constructor for the Maze class.
     * Creates an empty Maze with the specified height and width (empty means
     * that no cells have been visited)
     * @param width width of the new maze
     * @param height height of the new maze
    */
    Maze(size_t width, size_t height);

    /**
     * Destructor for the Maze class freeing all needed resources
    */
    ~Maze();

    /**
     * Clears the Mazes path and resets it to a fresh maze (as provided by the
     * Constructor)
    */
    void reset();

    /**
     * Prints the current maze state including the start and end point (if
     * specified)
     * @param ncurses
     * true: the maze gets printed using ncurses (WARNING
     *       it assumes that initscr has already been called)
     * false: the maze gets printed in the terminal without ncurses
    */
    void print(bool ncurses);

    /**
     * Generates a new labyrinth in the maze. The method calls reset before it
     * does so
     * @param anim_speed
     * 0: no animation is displayed and the maze is not printed automatically
     * >0: each generation step is printed out with anim_speed as delay in
     *     miliseconds (WARNING it assumes that initscr has already been called)
     * @param start_pos the start pos of the new maze
    */
    int generate(size_t anim_speed, Point start_pos);

    /**
     * Generates a new labyrinth in the maze. The method calls reset before it
     * does so. Calling it without the start_pos argument will take a random
     * point as start point
     * @param anim_speed
     * 0: no animation is displayed and the maze is not printed automatically
     * >0: each generation step is printed out with anim_speed as delay in
     *     miliseconds (WARNING it assumes that initscr has already been called)
    */
    int generate(size_t anim_speed);
};
