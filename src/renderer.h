#ifndef TINYRENDERER_IMPL_RENDERER_H
#define TINYRENDERER_IMPL_RENDERER_H

#include "tgaimage.h"
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color);
void line(Vec2i v0, Vec2i v1, TGAImage& image, const TGAColor& color);
void triangle(Vec2i t[3], TGAImage& image, const TGAColor& color);

#endif //TINYRENDERER_IMPL_RENDERER_H
