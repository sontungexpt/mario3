#pragma once

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX_BBOX_BLACK -99
#define ID_SPRITE_BLACK_BACKGROUND 103090

#define BBOX_ALPHA 0.25f		// Bounding box transparency
#define TRANSPARENT_COLOR 0.0f

#define UNKNOWN_STATE -1

#define CALCULATE_COLOR(src_color,src_alpha,dest_color ) (src_color * src_alpha + dest_color * (1 - src_alpha))