#include "renderer.h"
#include "tgaimage.h"
#include "Model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);

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
