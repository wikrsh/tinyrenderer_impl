#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
  for (int x = x0; x <= x1; x++) {
    float t = (x - x0) / (float) (x1 - x0);
    int y = y0 * (1.0 - t) + y1 * t;
    image.set(x, y, color);
  }
}

int main() {
  TGAImage image(400, 400, TGAImage::RGB);

  line(80, 90, 300, 200, image, white);
  line(90, 80, 200, 300, image, red);
  line(300, 200, 80, 90, image, red);

  image.write_tga_file("output.tga");

  return 0;
}
