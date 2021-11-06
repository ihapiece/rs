#pragma once
#include "game.h"

/*
Rooms: represents a .room in memory

Subspaces are declared
Make door entity that is given a destination room parameter
At deployment of a room the origin room is remembered and we'll look for a
corresponding door to spawn the player

Rooms can be serialized, the following is a file example (just the stuff that's been in main until now)
0 40 70
1 200 480 600 32
1 300 320 16 40
3 200 416 32 32 1
2 0 360 320 160 120
2 0 240 80
2 0 190 260
2 1 30 300 100 160
2 1 100 140

basically we just use the default whitespace text file reading to seperate params
and we'll use newlines to seperate different entities
for convenience, all of the lines are just converted to a vector of strings
player (0) spawns at 40,70
wall (1) at 200,480 with btl -600,-32 and bbr 600,32 (negativing taken care of)
wavingblock (3) at 200 416 with a t that increases by 1 each frame
rift (2) is created for subspace 0 (created since it doesn't exist)
rift (2) is added to subspace 0 at position 240 80 (size not given to add function)
etc.
*/

struct Room {
  std::vector<std::string> objects;
  std::string name;

  Room();
  Room(std::string fname);
  bool load(std::string fname);
  bool save();
};
