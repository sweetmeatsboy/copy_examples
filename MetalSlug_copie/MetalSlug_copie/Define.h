#pragma once

extern HWND g_hWnd;
extern HINSTANCE g_hInst;
extern HDC g_hdc;


const float TIME_SCALE = 1.f;
const int WINCX = 800;
const int WINCY = 600;

const int SECOND = 1000;

const float PI = 3.141592653589f;
const float GRAVITY = 0.98f;

template<typename T>
inline void Safe_Delete(T _t)
{
	if (_t != nullptr)
		delete _t;
	_t = nullptr;
}

enum GAME_STATE
{
	GAME_IDLE,
	GAME_PLAYING,
	GAME_RESULT,
};

enum PLAYER_TYPE
{
	PLAYER_NONE,
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	PLAYER_SLUG,
};

enum OBJ_TYPE
{
	OBJ_ITEM,
	OBJ_SLUG,
	OBJ_NPC,
	OBJ_MONSTER,
	OBJ_P_BULLET,
	OBJ_E_BULLET,
	OBJ_EFFECT,
	OBJ_PLAYER,
	OBJ_OBJECT,
	OBJ_END,
};

enum STAGE_STATE
{
	STAGE_INTRO,
	STAGE_1,
	STAGE_2,
	STAGE_END,
};

//Character���� ���µ�
enum P_STATE
{
	P_IDLE, //������ �ִ� ����. [�ʱ� ����]
	P_JUMP, //������ ������ ������ JUMP
	P_JUMPING, //�ö󰡴� ����
	P_LANDING, //���� �� �����ϴ� ������ LANDING
	P_LAND, //���鿡 �浹�� ������ ���´� LAND
};

//Ű�Է� ����.	[�ִϸ��̼Ƕ� ���]
enum KEY_INPUT
{
	KEY_IDLE,
	KEY_UP,
	KEY_UP_TO_RIGHT,
	KEY_RIGHT_TO_UP,
	KEY_RIGHT,
	KEY_RIGHT_TO_DOWN,
	KEY_DOWN_TO_RIGHT,
	KEY_DOWN,
	KEY_DOWN_TO_LEFT,
	KEY_LEFT_TO_DOWN,
	KEY_LEFT,
	KEY_LEFT_TO_UP,
	KEY_UP_TO_LEFT
};

//��׷�?
enum ATK_STATE
{
	ATK_STATE_IDLE,
	ATK_STATE_ATK,
};

enum SIT_STATE
{
	SIT_IDLE,			//28�� �ִϴ� IDLE
	SIT_RUN,			//29�� �ִϴ� �ϴ� �ɾƼ� �����̴� �ɷ� ����.
	SIT_KNIFE,			//31
	SIT_SHOOT_NORMAL,	//30
	SIT_BOMB,			//32
	SIT_NONE,
};

enum STAND_STATE
{
	STAND_IDLE,
	STAND_SIT,
};

//��ü ���� [�ִϸ��̼� ���]
enum LEG_STATE
{
	LEG_IDLE,
	LEG_RUN,
	LEG_DIR_JUMP,
	LEG_JUMP,
	LEG_NONE
};

//��ü ���� [�ִϸ��̼� ���.]
enum BODY_STATE
{
	BODY_IDLE,
	BODY_RUN,
	BODY_JUMP,
	BODY_DIR_JUMP,
	BODY_WEAPON_IDLE,

	BODY_LOOK_NOMAL_UP,
	BODY_LOOK_NOMAL_DOWN,
	BODY_SHOOT_NOMAL_UP,
	BODY_SHOOT_NOMAL,
	BODY_SHOOT_NOMAL_DOWN,

	BODY_WEAPON_RUN,
	BODY_WEAPON_JUMP,
	BODY_WEAPON_DIR_JUMP,
	BODY_LOOK_WEAPON_UP,
	BODY_LOOK_WEAPON_DOWN,

	BODY_SHOOT_WEAPON_UP,
	BODY_SHOOT_WEAPON_UP_TO_LEFT,
	BODY_SHOOT_WEAPON_UP_TO_RIGHT,

	BODY_SHOOT_WEAPON_DOWN,
	BODY_SHOOT_WEAPON_DOWN_TO_LEFT,
	BODY_SHOOT_WEAPON_DOWN_TO_RIGHT,

	BODY_SHOOT_WEAPON_LEFT,
	BODY_SHOOT_WEAPON_LEFT_TO_UP,
	BODY_SHOOT_WEAPON_LEFT_TO_DOWN,

	BODY_SHOOT_WEAPON_RIGHT,
	BODY_SHOOT_WEAPON_RIGHT_TO_UP,
	BODY_SHOOT_WEAPON_RIGHT_TO_DOWN,

	BODY_KNIFE,
	BODY_BOMB,
	BODY_NONE
};

//���� ������ [�ӽŰ�, ��ź, ����, ȭ������, ������]
enum W_ITEM_TYPE
{
	W_ITEM_H,
	W_ITEM_R,
	W_ITEM_F,
	W_ITEM_S,
	W_ITEM_RELOAD_BOMB,
	W_ITEM_RECHARGE_OIL,
	W_ITEM_RELOAD_BULLET,
	W_ITEM_CHANGE_FIREBOMB,
	W_ITEM_CHANGE_BOMB,
	W_ITEM_RELOAD_SLUG_BOMB,
};

//���� ����
enum W_TYPE
{
	W_KNIFE,	//Į
	W_NOMAL,	//����
	W_BOMB,	//��ź.
	W_H,	//�ӽŰ�
	W_R,	//���Ϸ���
	W_F,	//�����Ӽ�1
	W_S,	//����1
};

enum EW_TYPE
{
	EW_KNIFE,	//Į�� �簢�� ��Ʈ
	EW_NOMAL,	//�Ϲ� �Ѿ�.
	EW_MINE,	//����
	EW_BOMB_1,	//����ź
	EW_BOMB_2,	//������ ��ź?
	EW_FIREWORK,	//���ư��� ����
	EW_BAKGEOK,	//�ڰ���
	EW_BALLING_BOMB,	//������ ��ź.
	EW_TANK_NOMAL_BULLET		//�Ϲ� ��ũ�� ��ź ���׶� ��.
};

//�Ϲ� ������ Ÿ��
enum N_ITEM_TYPE	
{
	N_ITEM_CURE,
	N_ITEM_FISH,
	N_ITEM_BREAD,
	N_ITEM_CAN,
	N_ITEM_BANANA,
	N_ITEM_CHICKEN,
	N_ITEM_MANDOO
};

typedef struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

	tagInfo(void)
	{	}

	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		:fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY)
	{	}

}INFO;
