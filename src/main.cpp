#include "renderer.h"
#include "tgaimage.h"
#include "Model.h"

int main() {
  const int width = 400;
  const int height = 400;
  TGAImage image(width, height, TGAImage::RGB);

  Model model("../src/obj/african_head.obj");

  Vec3f light_dir(0, 0, -1);
  light_dir.normalize();

  for (int i = 0; i < model.nfaces(); i++) {
    auto face = model.face(i);

    Vec2i screen_coords[3];
    Vec3f world_coords[3];
    for (int j = 0; j < 3; j++) {
      Vec3f v = model.vert(face[j]);
      screen_coords[j] = Vec2i((v.x + 1.0) * width / 2.0, (v.y + 1.0) * height / 2.0);
      world_coords[j] = v;
    }

    Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
    n.normalize();

    auto intensity = n * light_dir;
    if (intensity > 0) {
      triangle(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
    }
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
