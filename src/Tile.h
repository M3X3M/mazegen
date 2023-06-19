class Tile;

struct Neighbour
{
  Tile* ptr;
  bool reachable;
};

typedef enum OptionType
{
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
  ERROR
} OptionType;

class Tile
{
  public:
    Neighbour top;
    Neighbour bottom;
    Neighbour left;
    Neighbour right;

    bool reached;

  public:

    void setReached(bool reached);
    bool getReached();

    void setPointers(Tile* top, Tile* bottom, Tile* left, Tile* right);

    int getOptionCount();

    OptionType removeOption(int option_num);

    void reset();

    void print();

    Tile();
};