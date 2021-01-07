#include "renderer.h"
#include "tgaimage.h"
#include "Model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

void linesweep(Vec2i& p0, Vec2i& p1, Vec2i& q0, Vec2i& q1, int y, TGAImage& image, const TGAColor& color) {
  // line p0 => p1
  float rp = (float) (y - p0.y) / (float) (p1.y - p0.y);
  auto vp = p0 + (p1 - p0) * rp;

  // line q0 => q1
  float rq = (float) (y - q0.y) / (float) (q1.y - q0.y);
  auto vq = q0 + (q1 - q0) * rq;

  // draw horizontal line
  int x0 = std::min(vp.x, vq.x);
  int x1 = std::max(vp.x, vq.x);

  for (int x = x0; x <= x1; x++) {
    image.set(x, y, color);
  }
}

void triangle(Vec2i t[3], TGAImage& image, const TGAColor& color) {
  if (t[0].y > t[1].y) {
    std::swap(t[0], t[1]);
  }
  if (t[1].y > t[2].y) {
    std::swap(t[1], t[2]);
  }
  if (t[0].y > t[1].y) {
    std::swap(t[0], t[1]);
  }

  for (int y = t[0].y; y <= t[1].y; y++) {
    linesweep(t[0], t[1], t[0], t[2], y, image, color);
  }

  for (int y = t[1].y; y <= t[2].y; y++) {
    linesweep(t[1], t[2], t[0], t[2], y, image, color);
  }
}

int main() {
  const int width = 200;
  const int height = 200;
  TGAImage image(width, height, TGAImage::RGB);

  Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
  Vec2i t1[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
  Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

  triangle(t0, image, red);
  triangle(t1, image, white);
  triangle(t2, image, green);

  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
