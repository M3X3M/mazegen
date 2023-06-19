#include "Maze.h"

Maze::Maze(size_t width, size_t height)
{
  Tile* cur_tile;

  srand(time(0));

  this->height = height;
  this->width = width;

  this->tiles = (Tile***)malloc(width * sizeof(void*));

  this->start_point.x = -1;
  this->start_point.y = -1;

  this->end_point.distance = 0;
  this->end_point.point.x = -1;
  this->end_point.point.y = -1;

  for (size_t i = 0; i < width; i++)
  {
    this->tiles[i] = (Tile**)malloc(height * sizeof(void*));
  }

  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      cur_tile = new Tile();
      this->tiles[x][y] = cur_tile;
    }
  }

  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      this->tiles[x][y]->left.ptr = (x > 0) ? this->tiles[x-1][y] : nullptr;
      this->tiles[x][y]->right.ptr = (x < (width - 1)) ? this->tiles[x+1][y] : nullptr;
      this->tiles[x][y]->top.ptr = (y > 0) ? this->tiles[x][y-1] : nullptr;
      this->tiles[x][y]->bottom.ptr = (y < (height - 1)) ? this->tiles[x][y+1] : nullptr;
    }
  }
}

Maze::~Maze()
{
  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      delete this->tiles[x][y];
    }
  }

  free(this->tiles);
}

void Maze::print(bool ncurses)
{
  bool even_x, even_y;
  std::string cur_line;
  char char_to_add;
  Tile* probing_tile;
  Point probing_point;
  if(ncurses)
    clear();
  for (size_t y = 0; y < 2 * this->height + 1; y++)
  {
    cur_line = "";
    for (size_t x = 0; x <  2 * this->width + 1; x++)
    {
      // 0, 2, 4 ... Lines
      // 1, 3, 5 ... Tiles
      even_x = ((x % 2) == 0);
      even_y = ((y % 2) == 0);

      probing_point.x = ((x / 2) < this->width) ? (x / 2) : this->width - 1;
      probing_point.y = ((y / 2) < this->height) ? (y / 2) : this->height - 1;

      probing_tile = this->tiles[probing_point.x][probing_point.y];

      if (even_x && even_y)
      {
        char_to_add = '+';
      }
      else if (even_x)
      {
        char_to_add = (!probing_tile->left.reachable || x == 2 * this->width)
          ? '|' : ' ';
      }
      else if (even_y)
      {
        char_to_add = (!probing_tile->top.reachable || y == 2 * this->height)
          ? '-' : ' ';
      }
      else
      {
        if(probing_point.x == start_point.x && probing_point.y == start_point.y)
        {
          char_to_add = 'S';
        }
        else if(probing_point.x == end_point.point.x &&
          probing_point.y == end_point.point.y)
        {
          char_to_add = 'E';
        }
        else if(probing_tile->reached)
        {
          char_to_add = ' ';
        }
        else
        {
          char_to_add = 'X';
        }
      }

      cur_line += char_to_add;
    }

    if(ncurses)
      addstr((cur_line + "\n").c_str());
    else
      std::cout << cur_line << std::endl;
  }
  if(ncurses)
    refresh();
}

void Maze::reset()
{
  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      this->tiles[x][y]->reset();
    }
  }
}

int Maze::generate(size_t anim_speed)
{
  Point start_point = Point();
  start_point.x = (int)(rand() % width);
  start_point.y = (int)(rand() % height);
  return this->generate(anim_speed, start_point);
}

int Maze::generate(size_t anim_speed, Point start_pos)
{
  if (
    start_pos.x >= this->width ||
    start_pos.x < 0 ||
    start_pos.y >= this->height ||
    start_pos.x >= this->width
  )
    return -1;

  this->reset();

  this->start_point.x = start_pos.x;
  this->start_point.y = start_pos.y;
  this->tiles[start_pos.x][start_pos.y]->reached = true;

  size_t recursion_depth = 1;

  return this->walk(anim_speed, start_pos, recursion_depth);
}

int Maze::walk(size_t anim_speed, Point start_pos, size_t recursion_depth)
{
  int rand_num;
  int option_cnt = this->tiles[start_pos.x][start_pos.y]->getOptionCount();
  OptionType removed_op;
  Point next_pos;
  while(option_cnt > 0)
  {
    rand_num = rand() % option_cnt;

    removed_op = this->tiles[start_pos.x][start_pos.y]->removeOption(rand_num);

    if(removed_op == ERROR)
    {
      --recursion_depth;
      return -1;
    }
    else if(removed_op == TOP)
    {
      next_pos.x = start_pos.x;
      next_pos.y = start_pos.y-1;
    }
    else if(removed_op == BOTTOM)
    {
      next_pos.x = start_pos.x;
      next_pos.y = start_pos.y+1;
    }
    else if(removed_op == LEFT)
    {
      next_pos.x = start_pos.x-1;
      next_pos.y = start_pos.y;
    }
    else if(removed_op == RIGHT)
    {
      next_pos.x = start_pos.x+1;
      next_pos.y = start_pos.y;
    }

    if(recursion_depth > end_point.distance)
    {
      end_point.point = next_pos;
      end_point.distance = recursion_depth;
    }

    if (anim_speed)
    {
      usleep(anim_speed * 1000);
      this->print(true);
    }

    if(this->walk(anim_speed, next_pos, ++recursion_depth))
    {
      --recursion_depth;
      return -1;
    }

    option_cnt = this->tiles[start_pos.x][start_pos.y]->getOptionCount();
  }

  --recursion_depth;
  return 0;
}
