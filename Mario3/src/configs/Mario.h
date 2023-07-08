#pragma once
#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL_SUIT 3

//appearances
#define MARIO_SMALL_BBOX_WIDTH  14
#define MARIO_SMALL_BBOX_HEIGHT 15
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 30
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18
#define MARIO_BIG_TAIL_SUIT_BBOX_WIDTH  20

#define MARIO_LEVEL_MAP_BBOX_WIDTH  14
#define MARIO_LEVEL_MAP_BBOX_HEIGHT 14

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_UNTOUCHABLE_TIME 1000
#define MARIO_MAX_POWER 6
#define MARIO_POWER_DURATION_FLY 3000
#define MARIO_TIME_OUT_POWER_UP 300
#define MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE 32
#define MARIO_LEVEL_MAP_SPEED 0.17f

#define MARIO_WALKING_SPEED		0.12f
#define MARIO_RUNNING_SPEED		0.22f
#define MARIO_FLYING_SPEED		0.45f
#define MARIO_ENTER_PIPE_SPEED		0.03f

#define MARIO_ACCEL_WALK_X	0.000258f
#define MARIO_ACCEL_RUN_X	0.00044f

#define MARIO_JUMP_SPEED_Y		0.55f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.45f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_DIE				-10

#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	-100

#define MARIO_STATE_RUNNING_RIGHT	200
#define MARIO_STATE_RUNNING_LEFT	-200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_SIT				400
#define MARIO_STATE_SIT_RELEASE		401

#define MARIO_STATE_HOLDING_KOOPA	500
#define MARIO_STATE_HOLDING_KOOPA_RELEASE	501

#define MARIO_STATE_UNTOUCHABLE 600

#define MARIO_STATE_FLY 700
#define MARIO_STATE_FLY_RELEASE 701

#define MARIO_STATE_SMASH_TAIL_RIGHT 800
#define MARIO_STATE_SMASH_TAIL_LEFT 801

#define MARIO_LEVEL_MAP_STATE_MOVING_RIGHT 900
#define MARIO_LEVEL_MAP_STATE_MOVING_LEFT 901
#define MARIO_LEVEL_MAP_STATE_MOVING_UP 902
#define MARIO_LEVEL_MAP_STATE_MOVING_DOWN 903
#define MARIO_LEVEL_MAP_STATE_MOVING_SPECIAL_POS 904

#define MARIO_STATE_ENTER_PIPE 1000
#define MARIO_STATE_OUTER_PIPE 1001

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_HOLDING_RUNNING_RIGHT 602
#define ID_ANI_MARIO_HOLDING_RUNNING_LEFT 603

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_HOLDING_RUNNING_RIGHT 1302
#define ID_ANI_MARIO_SMALL_HOLDING_RUNNING_LEFT 1303

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// appearcance change
#define ID_ANI_MARIO_IDLE_APPEARANCE_CHANGING_RIGHT 1700
#define ID_ANI_MARIO_IDLE_APPEARANCE_CHANGING_LEFT 1701

#define ID_ANI_MARIO_WALKING_APPEARANCE_CHANGING_RIGHT 1800
#define ID_ANI_MARIO_WALKING_APPEARANCE_CHANGING_LEFT 1801

#define ID_ANI_MARIO_RUNNING_APPEARANCE_CHANGING_RIGHT 1900
#define ID_ANI_MARIO_RUNNING_APPEARANCE_CHANGING_LEFT 1901

#define ID_ANI_MARIO_JUMP_WALK_APPEARANCE_CHANGING_RIGHT 2000
#define ID_ANI_MARIO_JUMP_WALK_APPEARANCE_CHANGING_LEFT 2001

#define ID_ANI_MARIO_JUMP_RUN_APPEARANCE_CHANGING_RIGHT 2100
#define ID_ANI_MARIO_JUMP_RUN_APPEARANCE_CHANGING_LEFT 2101

#define ID_ANI_MARIO_BRACE_APPEARANCE_CHANGING_RIGHT 2200
#define ID_ANI_MARIO_BRACE_APPEARANCE_CHANGING_LEFT 2201

#define ID_ANI_MARIO_SIT_APPEARANCE_CHANGING_RIGHT 2300
#define ID_ANI_MARIO_SIT_APPEARANCE_CHANGING_LEFT 2301

// tail mario
#define ID_ANI_TAIL_MARIO_IDLE_RIGHT 3000
#define ID_ANI_TAIL_MARIO_IDLE_LEFT 3001

#define ID_ANI_TAIL_MARIO_WALKING_RIGHT 3100
#define ID_ANI_TAIL_MARIO_WALKING_LEFT 3101

#define ID_ANI_TAIL_MARIO_RUNNING_RIGHT 3200
#define ID_ANI_TAIL_MARIO_RUNNING_LEFT 3201

#define ID_ANI_TAIL_MARIO_JUMP_WALK_RIGHT 3300
#define ID_ANI_TAIL_MARIO_JUMP_WALK_LEFT 3301

#define ID_ANI_TAIL_MARIO_SIT_RIGHT 3400
#define ID_ANI_TAIL_MARIO_SIT_LEFT 3401

#define ID_ANI_TAIL_MARIO_BRACE_RIGHT 3500
#define ID_ANI_TAIL_MARIO_BRACE_LEFT 3501

#define ID_ANI_TAIL_MARIO_FLY_RIGHT 3600
#define ID_ANI_TAIL_MARIO_FLY_LEFT 3601

#define ID_ANI_TAIL_MARIO_TAIL_SMASH_RIGHT 3700
#define ID_ANI_TAIL_MARIO_TAIL_SMASH_LEFT 3701

#define ID_ANI_MARIO_LEVEL_MAP_SMALL_FORWARD 3800
#define ID_ANI_MARIO_LEVEL_MAP_BIG_FORWARD 3900
#define ID_ANI_MARIO_LEVEL_MAP_TAIL_FORWARD 4000

#define ID_ANI_MARIO_TAIL_FORWARD 4100
#define ID_ANI_MARIO_SMALL_FORWARD 4200
#define ID_ANI_MARIO_BIG_FORWARD 4300

#pragma endregion
