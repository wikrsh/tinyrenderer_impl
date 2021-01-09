#include "renderer.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color) {
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

void line(Vec2i v0, Vec2i v1, TGAImage& image, const TGAColor& color) {
  line(v0.u, v0.v, v1.u, v1.v, image, color);
}

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
