﻿#pragma once

//appearances
#define KOOPA_GREEN 1
#define KOOPA_RED 2

#define KOOPA_TYPE_NORMAL 0
#define KOOPA_TYPE_FLY 1

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DEFEND 16

#define KOOPA_BBOX_HEIGHT_FLY 28

#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_MAX_SPEED 0.5f
#define KOOPA_FLY_SPEED_Y 0.155f
#define KOOPA_TIME_FOR_EACH_FLY	2000

#define KOOPA_ACCELERATION_DEFLECT 0.0006f
#define KOOPA_SLIDING_ACCELERATION 0.0008f

#define KOOPA_DEFEND_TIMEOUT 8000
#define KOOPA_COMBACK_TIMEOUT 2000

// states
#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DEFEND 200
#define KOOPA_STATE_IS_KICKED 300
#define KOOPA_STATE_UPSIDE 400
#define KOOPA_STATE_JUMP 500
#define KOOPA_STATE_IS_HOLDING 600
#define KOOPA_STATE_DIE_UPSIDE 700
#define KOOPA_STATE_COMEBACK 800
#define KOOPA_STATE_FLY 900

// Animation Ids
// red
#define ID_ANI_KOOPA_RED_WALKING_RIGHT 601001
#define ID_ANI_KOOPA_RED_WALKING_LEFT 601002
#define ID_ANI_KOOPA_RED_DEFEND 601003
#define ID_ANI_KOOPA_RED_IS_KICKED 601004
#define ID_ANI_KOOPA_RED_COMEBACK 601005
#define ID_ANI_KOOPA_RED_FLY_LEFT 601006
#define ID_ANI_KOOPA_RED_FLY_RIGHT 601007

// green
#define ID_ANI_KOOPA_GREEN_WALKING_RIGHT 601011
#define ID_ANI_KOOPA_GREEN_WALKING_LEFT 601012
#define ID_ANI_KOOPA_GREEN_DEFEND 601013
#define ID_ANI_KOOPA_GREEN_IS_KICKED 601014
#define ID_ANI_KOOPA_GREEN_COMEBACK 601015
#define ID_ANI_KOOPA_GREEN_FLY_LEFT 601016
#define ID_ANI_KOOPA_GREEN_FLY_RIGHT 601017
