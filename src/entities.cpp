#include "entities.h"

Block::Block() {
  initialize();
  saveid = 1;
  solid = true;
  moves = false;
  bshape.setFillColor(sf::Color::White);
}

void Block::on_end_draw() {

}

WavingBlock::WavingBlock() {
  initialize();
  saveid = 3;
  solid = true;
  bshape.setFillColor(sf::Color::Green);
  tsp = 1;
}

void WavingBlock::on_create() {
  t = 0;

  basey = pos.y;
  basex = pos.x;
}

void WavingBlock::on_step() {
  t+=tsp;
  pos.y = basey+sin(t/60)*100;
  pos.x = basex+cos(t/60)*100;
}

void WavingBlock::on_end_draw() {

}
