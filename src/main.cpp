#include "tgaimage.h"
#include "geometry.h"
#include "Model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }

  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int dx = x1 - x0;
  int dy = y1 - y0;
  int derror2 = std::abs(dy) * 2;
  int error2 = 0;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    if (steep) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }

    error2 += derror2;
    if (error2 > dx) {
      y += y1 > y0 ? 1 : -1;
      error2 -= dx * 2;
    }
  }
}

int main() {
  const int width = 400;
  const int height = 400;
  TGAImage image(width, height, TGAImage::RGB);
  Model model("../src/obj/african_head.obj");

  for (int i = 0; i < model.nfaces(); i++) {
    auto face = model.face(i);
    for (int j = 0; j < 3; j++) {
      auto v0 = model.vert(face[j]);
      auto v1 = model.vert(face[(j+1) % 3]);

      int x0 = (v0.x + 1.0) * width / 2.0;
      int y0 = (v0.y + 1.0) * height / 2.0;
      int x1 = (v1.x + 1.0) * width / 2.0;
      int y1 = (v1.y + 1.0) * height / 2.0;

      line(x0, y0, x1, y1, image, white);
    }
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
