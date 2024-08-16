#pragma once

/********************
	���� ����ü
********************/

/***************
	Ű ����
***************/
enum class EKeyState
{
	RELEASED,
	DOWN,
	PRESSED,
	UP,
	ENUM_END
};

/***************
	Ű ����
***************/
enum class EKeyType
{
	// ���콺
	LEFT_MOUSE_BUTTON = VK_LBUTTON,
	RIGHT_MOUSE_BUTTON = VK_RBUTTON,

	// ����
	ENTER = VK_RETURN,

	// ESC
	ESC = VK_ESCAPE,

	// �����̽�
	SPACE = VK_SPACE,
	
	// ��
	TAB = VK_TAB,

	// ĸ����
	CAPS_LOCK = VK_CAPITAL,

	// ����Ʈ
	LEFT_SHIFT = VK_LSHIFT,
	RIGHT_SHIFT = VK_RSHIFT,

	// ��Ʈ��
	LEFT_CTRL = VK_LCONTROL,
	RIGHT_CTRL = VK_RCONTROL,

	// Ŀ��
	CURSOR_UP = VK_UP,
	CURSOR_DOWN = VK_DOWN,
	CURSOR_LEFT = VK_LEFT,
	CURSOR_RIGHT = VK_RIGHT,

	// ���� Ű�е�
	ZERO = VK_NUMPAD0,
	ONE = VK_NUMPAD1,
	TWO = VK_NUMPAD2,
	THREE = VK_NUMPAD3,
	FOUR = VK_NUMPAD4,
	FIVE = VK_NUMPAD5,
	SIX = VK_NUMPAD6,
	SEVEN = VK_NUMPAD7,
	EIGHT = VK_NUMPAD8,

	// ���ĺ�
	A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F', G = 'G',
	H = 'H', I = 'I', J = 'J', K = 'K', L = 'L', M = 'M', N = 'N',
	O = 'O', P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T', U = 'U',
	V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z'
};

/***************
	�ݶ��̴� ��� Ÿ��
***************/
enum class EColliderType
{
	RECTANGLE,
	CIRCLE,
	ENUM_END
};

/***************
	�ݸ��� ���̾� Ÿ��
***************/
enum class ECollisionType
{
	CURSOR,
	GROUND_UNIT,
	AIR_UNIT,
	BUILDING,

	MINERAL,
	GAS,
	GATHER,
	BUILD,

	ENUM_END
};

/***************
	������Ʈ ���̾� Ÿ��(?)
***************/
enum class EObjectType
{
	PLAYER,
	CURSOR,
	MAP,

	BUILDING,
	UNIT,

	EFFECT,
	MINERAL,
	VESPENE_GAS,
	TILEMAP,
	ENUM_END
};


/***************
	Ÿ�� Ÿ��
***************/
enum class ETileType
{
	PASSABLE	= 0,
	IMPASSABLE	= 1,
	UNIT		= 2,
	BUILDING	= 3,
	MINERAL,
	GAS,
	ENUM_END
};


/***************
	�� Ÿ��
***************/
enum class ESceneType
{
	TEST,
	COMPETE,
	ENUM_END
};


/***************
	��ư ����
***************/
enum class EButtonState
{
	ENABLE,		// ��ư�� Ȱ��ȭ�� ����
	RELEASE,	// ��ư�� ���콺�� ���� ����
	HOVER,		// ��ư�� ���콺�� �ø� ����
	PRESS,		// ��ư�� ������ �ִ� ����
	CLICK,		// ��ư�� Ŭ���� ����
	DISABLE,	// ��ư�� ��Ȱ��ȭ�� ����
	ENUM_END
};


/***************
	���� Ÿ��
***************/
enum class ESoundChannel
{
	BGM,
	ADVISOR,
	CONTROL_CENTER,
	UNIT,
	BUILDING,
	EFFECT,
	ENUM_END
};


/********************
	������ ����ü
********************/

/***************
	����� �������̽� Ÿ��
***************/
enum class EUIType
{
	STATIC_UI,
	DYNAMIC_UI,
	ENUM_END
};

enum class EDirectionState
{
	NORTH_WEST,
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	ENUM_END
};

/***************
	������ Ÿ��
***************/
enum class EOwnerType
{
	NONE,
	PLAYER,
	COMPUTER,
	NEUTRAL,
	ENUM_END
};


/***************
	���� Ÿ��
***************/
enum class ERaceType
{
	TERRAN,
	PROTOSS,
	ZERG,
	ENUM_END
};


enum class EUnitAttributeType
{
	BIOLOGICAL,
	MECHANICAL,
	ENUM_END
};

/***************
	�׶� ����
***************/
enum class ETerranObjectType
{
	GROUND_UNIT,
	AIR_UNIT,
	BUILDING,
	MINERAL,
	VESPENE_GAS,
	ENUM_END
};

/***************
	�׶� �ǹ� ����
***************/
enum class ETerranBuildingType
{
	// �⺻ �ǹ�
	COMMAND_CENTER,
	SUPPLY_DEPOT,
	REFINERY,
	BARRACKS,
	ENGINEERING_BAY,
	ACADEMY,
	MISSILE_TURRET,
	BUNKER,

	// ���� �ǹ�
	FACTORY,
	ARMORY,
	STARPORT,
	SCIENCE_FACILITY,

	// �����
	COMSAT_STATION,
	NUCLEAR_SILO,
	MACHINE_SHOP,
	CONTROL_TOWER,
	PHYSICS_LAB,
	COVERT_OPS,

	ENUM_END
};

enum class ETerranAddOnType
{
	COMSAT_STATION,
	NUCLEAR_SILO,
	MACHINE_SHOP,
	CONTROL_TOWER,
	PHYSICS_LAB,
	COVERT_OPS,
	ENUM_END
};

/***************
	�׶� ���� ����
***************/
enum class ETerranUnitType
{
	SCV,
	
	MARINE,
	FIREBAT,
	MEDIC,
	GHOST,

	VULTURE,
	TANK,
	SIEGE_TANK,
	GOLIATH,

	WRAITH,
	DROPSHIP,
	VALKYRIE,
	SCIENCE_VESSEL,
	BATTLE_CRUISER,

	ENUM_END
};


/***************
	�׶� ���׷��̵� ����
***************/
enum class ETerranUpgradeType
{
	// �����Ͼ ����
	INFANTRY_WEAPONS_1,
	INFANTRY_WEAPONS_2,
	INFANTRY_WEAPONS_3,
	INFANTRY_ARMOR_1,
	INFANTRY_ARMOR_2,
	INFANTRY_ARMOR_3,

	// ��ī����
	U238_SHELLS,
	STIMPACK_TECH,
	RESTORATION,
	OPTICAL_FLARE,
	CADUCEUS_REACTOR,

	// �ƸӸ�
	VIHICLE_WEAPONS_1,
	VIHICLE_WEAPONS_2,
	VIHICLE_WEAPONS_3,
	VIHICLE_PLATING_1,
	VIHICLE_PLATING_2,
	VIHICLE_PLATING_3,

	SHIP_WEAPONS,
	SHIP_PLATING,
	
	// ��Ŭ���� ���Ϸ�
	ARM_NUCLEAR_SILO,

	// ���̾� �۽Ǹ�Ƽ
	IRRADIATE,
	TITAN_REACTOR,

	// �ӽż�
	ION_THRUSTERS,
	SPIDER_MINES,
	SIEGE_TECH,
	CHARON_BOOSTERS,

	// TODO: ��Ʈ�� Ÿ��

	// TODO: ������ ��
	YAMATO_CANNON,
	COLOSSUS_REACTOR,

	// TODO: �ڹ�Ʈ �ɽ�

	ENUM_END
};

/***************
	���� ��� ����
***************/
enum class ECommandType
{
	// *** ���� ***
	MOVE,
	STOP,
	ATTACK,
	// PATROL,
	// HOLD_POSITION,
	
	// REPAIR,
	GATHER,
	BUILD_BASIC_STRUCTURE,
	BUILD_ADVANCED_STRUCTURE,
	
	SET_RALLY_POINT,

	// *** ���� ���� ***
	BUILD_SCV,

	BUILD_MARINE,
	BUILD_FIREBAT,
	BUILD_MEDIC,
	BUILD_GHOST,

	BUILD_VULTURE,
	BUILD_SIEGE_TANK,
	BUILD_GOLIATH,

	BUILD_SCIENCE_VESSEL,
	BUILD_BATTLECRUISER,

	// *** �ǹ� �Ǽ� ***
	BUILD_COMMAND_CENTER,
	BUILD_SUPPLY_DEPOT,
	BUILD_REFINERY,
	BUILD_ENGINEERING_BAY,
	BUILD_BARRACKS,
	BUILD_ACADEMY,

	BUILD_FACTORY,
	BUILD_STARPORT,
	BUILD_SCIENCE_FACILITY,
	BUILD_ARMORY,

	BUILD_COMSAT_STATION,
	BUILD_NUCLEAR_SILO,
	BUILD_MACHINE_SHOP,
	BUILD_CONTROL_TOWER,
	BUILD_PHYSICS_LAB,
	BUILD_COVERT_OPS,

	// *** ���׷��̵� ***
	UPGRADE_INFANTRY_WEAPONS,
	UPGRADE_INFANTRY_ARMOR,

	UPGRADE_U238_SHELLS,
	UPGRADE_STIMPACK_TECH,

	UPGRADE_ION_THRUSTERS,
	UPGRADE_SIEGE_TECH,

	UPGRADE_VIHICLE_WEAPONS,
	UPGRADE_VIHICLE_PLATING,

	UPGRADE_IRRADIATE,
	UPGRADE_YAMATO_CANNON,

	ARM_NUCLEAR_SILO,

	// ����, ���̾��
	USE_STIMPACK,

	// �޵�
	USE_HEAL,

	// ��Ʈ
	//CLOCK,
	//LOCK_DOWN,
	USE_NUCLEAR_STRIKE,

	// ����
	//SPIDER_MINE,

	// ��ũ
	SIEGE_MODE,
	TANK_MODE,

	// ���̾� �载
	USE_DEFENSIVE_MATRIX,
	USE_IRRADIATE,

	// ��Ʋ����
	USE_YAMATO_CANNON,

	// *** �ǹ� ***
	// LIFT_OFF,
	// LAND,

	// SCANNER_SWEEP,

	// *** ��� ***
	// �ǹ� ���� ���
	GO_BACK,
	CANCEL,
	CANCEL_LAST,
	CANCEL_UPGRADE,
	// CANCEL_CONSTRUCTION,

	ENUM_END
};


enum class ECommandWidgetState
{
	STATE_A,// �⺻��
	STATE_B,// �⺻ �ǹ�
	STATE_C,// ���� �ǹ�
	STATE_D,// �ڷ� ����		cancel
	STATE_E,// ��� ���		cancel
	STATE_F,// ���� ���� ���	cancel last
	STATE_G,// ���׷��̵� ���	cancel upgrade
	STATE_H,// �Ǽ� ���
	STATE_Z,// �� ����
	ENUM_END
};