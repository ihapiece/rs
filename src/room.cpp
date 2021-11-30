#include "game.h"
#include "entities.h"
#include <fstream>

//defines room and game's room functions
Room::Room() {}
Room::Room(std::string fname) {load(fname);}

bool Room::load(std::string fname) {
  std::ifstream f(fname);
  if (!f) {return false;}
  std::string s;
  while (f) {
    std::getline(f, s);
    if (s != "") {objects.push_back(s);}
  }
  f.close();
  return true;
}

bool Room::save() {
  std::ofstream f("assets/" + name, std::ios::trunc);
  if (!f) {return false;}
  for (std::string s : objects) {
    f << s << std::endl;
  }
  f.close();
  return true;
}

Room Game::create_room() {
  Room room;
  room.name = current_room;

  for (auto i : entities) {
    if (i->saveid != -1) {
      std::stringstream saveline;
      saveline << i->saveid << " ";
      switch (i->saveid) {
        case 0: { //0 posx posy
          Player* player = static_cast<Player*>(i.get());

          saveline << player->pos.x << " ";
          saveline << player->pos.y;
          break;
        }

        case 1: { //1 posx posy halfsizex halfsizey
          Entity* b = i.get();
          saveline << b->pos.x << " ";
          saveline << b->pos.y << " ";
          saveline << b->bbr.x << " ";
          saveline << b->bbr.y;
          break;
        }

        case 3: { //3 posx posy halfsizex halfsizey rotatespeed
          WavingBlock* wb = static_cast<WavingBlock*>(i.get());
          saveline << wb->pos.x << " ";
          saveline << wb->pos.y << " ";
          saveline << wb->bbr.x << " ";
          saveline << wb->bbr.y << " ";
          saveline << wb->tsp;
          break;
        }
      }
      room.objects.push_back(saveline.str());
    }
  }

  int n = 0;
  for (auto i : subspaces) {
    for (int r = 0; r < i->members.size(); r++) {
      std::stringstream saveline;
      saveline << 2 << " " << n << " " << i->members[r].canmove << " " << i->members[r].tl.x << " " << i->members[r].tl.y << " ";
      saveline << i->members[r].br.x-i->members[r].tl.x << " " << i->members[r].br.y-i->members[r].tl.y;
      room.objects.push_back(saveline.str());
    }
    n++;
  }

  std::cout << "created room " << room.name << " with the following objects:" << std::endl;
  for (auto i : room.objects) {
    std::cout << i << std::endl;
  }

  return room;
}

void Game::deploy_room(Room& room) {
  entities.clear();
  subspaces.clear();

  current_room = room.name;
  std::map<int, Subspace*> subs;

  for (std::string s : room.objects) {
    std::stringstream o(s);
    int type;
    o >> type;
    switch (type) { //should probably make an enum for these
      case 0: { //0 posx posy
        Player* player = static_cast<Player*>(instance_add(std::make_shared<Player>()));
        // we don't really need to cast here but player might have unique params in the future
        o >> player->pos.x;
        o >> player->pos.y;
        break;
      }

      case 1: { //1 posx posy halfsizex halfsizey
        Entity* b = instance_add(std::make_shared<Block>());
        o >> b->pos.x;
        o >> b->pos.y;
        o >> b->bbr.x;
        o >> b->bbr.y;
        b->btl = b->bbr*-1.0f;
        break;
      }

      case 2: { //2 subspace tlx tly sizex sizey
        int sub;
        o >> sub;
        bool canmove;
        o >> canmove;
        Vec tl;
        Vec size;
        o >> tl.x;
        o >> tl.y;
        bool sized = false;
        if (o >> size.x) {
          sized = true;
          o >> size.y;
        }

        if (subs.count(sub)) {
          if (sized) {subs[sub]->add(tl, size, canmove);} else {subs[sub]->add(tl, canmove);}
        } else {
          if (!sized) {std::cout << "No size given for initial rift!\n";}
          subs[sub] = subspace_add(tl, size, canmove);
        }

        break;
      }

      case 3: { //3 posx posy halfsizex halfsizey rotatespeed
        WavingBlock* wb = static_cast<WavingBlock*>(instance_add(std::make_shared<WavingBlock>()));
        o >> wb->pos.x;
        o >> wb->pos.y;
        o >> wb->bbr.x;
        o >> wb->bbr.y;
        wb->btl = wb->bbr*-1.0f;
        o >> wb->tsp;
        break;
      }
    }
  }
}
