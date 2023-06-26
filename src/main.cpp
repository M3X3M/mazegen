#include <ncurses.h>
#include <unistd.h>
#include "Maze.h"

#define USAGE_TEXT "Usage: mazegen -x [WIDTH] -y [HEIGHT] [OPTIONS]\n\n  -a [SPEED] specifies that the generation of the maze should be animated (SPEED miliseconds per animation step)\n"
#define WIDTH_ERROR "Width argument not provided or faulty. Check your input\n"
#define HEIGHT_ERROR "Height argument not provided or faulty. Check your input\n"
#define ANIM_ERROR "Error in animation argument. Check your input\n"

/**
 * Command line tool for creating mazes
*/
int main(int argc, char** argv)
{
  int cur_flag;
  int height_arg = 0;
  int width_arg = 0;
  int anim_arg = 0;
  bool use_anim = false;

  // disable automatic error msg
  opterr = 1;

  while ((cur_flag = getopt(argc, argv, "x:y:a:")) != -1)
  {
    switch (cur_flag)
    {
      case 'x':
        width_arg = std::atoi(optarg);
        break;
      case 'y':
        height_arg = std::atoi(optarg);
        break;
      case 'a':
        use_anim = true;
        anim_arg = std::atoi(optarg);
        break;
      case '?':
        fprintf(stderr, USAGE_TEXT);
        return 1;
      default:
        abort();
    }
  }

  if(width_arg < 1)
  {
    fprintf(stderr, WIDTH_ERROR);
    return -1;
  }
  if(height_arg < 1)
  {
    fprintf(stderr, HEIGHT_ERROR);
    return -1;
  }
  if(anim_arg <= 0 && use_anim == true)
  {
    fprintf(stderr, WIDTH_ERROR);
    return -1;
  }

  initscr();
  Maze maze = Maze(width_arg, height_arg);
  maze.generate(anim_arg);
  endwin();
  maze.print(false);

  return 0;
}
