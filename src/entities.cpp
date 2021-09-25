#include "entities.h"

Block::Block() {
  initialize();
  name = "Block";
  solid = true;
  moves = false;
}

void Block::on_end_draw() {
  graphics->draw_set_color(0xff, 0xff, 0xff, 0x00);
  graphics->draw_rectangle(pos+btl, pos+bbr, false);
}

WavingBlock::WavingBlock() {
  initialize();
  name = "WavingBlock";
  solid = true;
}

void WavingBlock::on_create() {
  t = 0;
  basey = pos.y;
  basex = pos.x;
}

void WavingBlock::on_step() {
  t++;
  pos.y = basey+sin(t/60)*100;
  pos.x = basex+cos(t/60)*100;
}

void WavingBlock::on_end_draw() {
  graphics->draw_set_color(0xff, 0xff, 0xff, 0x00);
  graphics->draw_rectangle(pos+btl, pos+bbr, false);
}
