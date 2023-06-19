#include "Tile.h"
#include <iostream>

Tile::Tile()
{
  this->top.ptr = nullptr;
  this->bottom.ptr = nullptr;
  this->left.ptr = nullptr;
  this->right.ptr = nullptr;

  this->top.reachable = false;
  this->bottom.reachable = false;
  this->left.reachable = false;
  this->right.reachable = false;

  this->reached = false;
}

int Tile::getOptionCount()
{
  int cnt = 0;

  if (!this->top.reachable && this->top.ptr && !this->top.ptr->reached)
    cnt = cnt + 1;
  if (!this->bottom.reachable && this->bottom.ptr && !this->bottom.ptr->reached)
    cnt = cnt + 1;
  if (!this->left.reachable && this->left.ptr && !this->left.ptr->reached)
    cnt = cnt + 1;
  if (!this->right.reachable && this->right.ptr && !this->right.ptr->reached)
    cnt = cnt + 1;

  return cnt;
}

OptionType Tile::removeOption(int option_num)
{
  if (option_num >= getOptionCount())
  {
    return ERROR;
  }

  if (!this->top.reachable && this->top.ptr && !this->top.ptr->reached)
  {
    if (option_num == 0)
    {
      this->top.ptr->reached = true;
      this->top.ptr->bottom.reachable = true;
      this->top.reachable = true;
      return TOP;
    }
    else
    {
      option_num--;
    }
  }
  if (!this->bottom.reachable && this->bottom.ptr && !this->bottom.ptr->reached)
  {
    if (option_num == 0)
    {
      this->bottom.ptr->reached = true;
      this->bottom.ptr->top.reachable = true;
      this->bottom.reachable = true;
      return BOTTOM;
    }
    else
    {
      option_num--;
    }
  }
  if (!this->left.reachable && this->left.ptr && !this->left.ptr->reached)
  {
    if (option_num == 0)
    {
      this->left.ptr->reached = true;
      this->left.ptr->right.reachable = true;
      this->left.reachable = true;
      return LEFT;
    }
    else
    {
      option_num--;
    }
  }
  if (!this->right.reachable && this->right.ptr && !this->right.ptr->reached)
  {
    if (option_num == 0)
    {
      this->right.ptr->reached = true;
      this->right.ptr->left.reachable = true;
      this->right.reachable = true;
      return RIGHT;
    }
    else
    {
      return ERROR;
    }
  }
  return ERROR;
}

void Tile::print()
{
  std::cout <<
    "Pointers (t,b,l,r): " << this->top.ptr << " " <<
    this->bottom.ptr << " " << this->left.ptr << " " <<
    this->right.ptr << " " <<
  std::endl;

  std::cout <<
    "Reachable (t,b,l,r): " << this->top.reachable <<
    " " << this->bottom.reachable << " " << this->left.reachable <<
    " " << this->right.reachable << " " <<
  std::endl;
}

void Tile::reset()
{
  this->top.reachable = false;
  this->bottom.reachable = false;
  this->left.reachable = false;
  this->right.reachable = false;
  this->reached = false;
}

void Tile::setReached(bool reached)
{
  this->reached = reached;
}

bool Tile::getReached()
{
  return this->reached;
}

void Tile::setPointers(Tile* top, Tile* bottom, Tile* left, Tile* right)
{
  this->top.ptr = top;
  this->bottom.ptr = bottom;
  this->left.ptr = left;
  this->right.ptr = right;
}