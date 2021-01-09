#include "tgaimage.h"
#include "Model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

Vec3f barycentric(Vec2i t[3], Vec2i p) {
  Vec3f v1 = Vec3f(t[2].x - t[0].x, t[1].x - t[0].x, t[0].x - p.x);
  Vec3f v2 = Vec3f(t[2].y - t[0].y, t[1].y - t[0].y, t[0].y - p.y);
  Vec3f u = v1 ^ v2;

  if (std::abs(u.z) < 1) return Vec3f(-1, -1, -1);

  return Vec3f(1.0 - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

void triangle(Vec2i t[3], TGAImage& image, const TGAColor& color) {
  // p_min and p_max represent the bounding box of the triangle
  Vec2i p_min(image.get_width() - 1, image.get_height() - 1);
  Vec2i p_max(0, 0);

  for (int i = 0; i < 3; i++) {
    p_min.x = std::min(p_min.x, t[i].x);
    p_min.y = std::min(p_min.y, t[i].y);
    p_max.x = std::max(p_max.x, t[i].x);
    p_max.y = std::max(p_max.y, t[i].y);
  }

  // Limits to image region
  p_min.x = std::max(p_min.x, 0);
  p_min.y = std::max(p_min.y, 0);
  p_max.x = std::min(p_max.x, image.get_width() - 1);
  p_max.y = std::min(p_max.y, image.get_height() - 1);

  for (int y = p_min.y; y <= p_max.y; y++) {
    for (int x = p_min.x; x <= p_max.x; x++) {
      // Check if (x, y) is on the triangle
      Vec2i p(x, y);
      auto bc = barycentric(t, p);
      if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;

      image.set(x, y, color);
    }
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
