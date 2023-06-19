#pragma once

// bounding box size
#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32

// speed and other
#define PLANT_SPEED_UP_DOWN 0.025f
#define DISTANCE_PIPE_LONG_SHORT 8

// time out
#define TIME_OUT_UP_STATE 5000 // the time between after down and then up
#define TIME_OUT_DOWN_STATE 6500	// the time between after up and then down
#define TIME_RELOAD_BULLET 100

// type
#define PLANT_SHOOT_RED 1

#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_STATE_DEATH 300

#pragma region ANIMATION

// top and under is the position of plant with mario
#define ID_ANI_PLANT_LEFT_NOT_SHOOT_UNDER 602001
#define ID_ANI_PLANT_LEFT_SHOOT_UNDER 602002

#define ID_ANI_PLANT_LEFT_NOT_SHOOT_TOP 602003
#define ID_ANI_PLANT_LEFT_SHOOT_TOP 602004

#define ID_ANI_PLANT_RIGHT_NOT_SHOOT_UNDER	602005
#define ID_ANI_PLANT_RIGHT_SHOOT_UNDER	602006

#define ID_ANI_PLANT_RIGHT_NOT_SHOOT_TOP 602007
#define ID_ANI_PLANT_RIGHT_SHOOT_TOP 602008

#pragma endregion