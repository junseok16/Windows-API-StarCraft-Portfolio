#pragma once

/********************
	엔진 열거체
********************/

/***************
	키 상태
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
	키 종류
***************/
enum class EKeyType
{
	// 마우스
	LEFT_MOUSE_BUTTON = VK_LBUTTON,
	RIGHT_MOUSE_BUTTON = VK_RBUTTON,

	// 엔터
	ENTER = VK_RETURN,

	// ESC
	ESC = VK_ESCAPE,

	// 스페이스
	SPACE = VK_SPACE,
	
	// 탭
	TAB = VK_TAB,

	// 캡스락
	CAPS_LOCK = VK_CAPITAL,

	// 시프트
	LEFT_SHIFT = VK_LSHIFT,
	RIGHT_SHIFT = VK_RSHIFT,

	// 컨트롤
	LEFT_CTRL = VK_LCONTROL,
	RIGHT_CTRL = VK_RCONTROL,

	// 커서
	CURSOR_UP = VK_UP,
	CURSOR_DOWN = VK_DOWN,
	CURSOR_LEFT = VK_LEFT,
	CURSOR_RIGHT = VK_RIGHT,

	// 숫자 키패드
	ZERO = VK_NUMPAD0,
	ONE = VK_NUMPAD1,
	TWO = VK_NUMPAD2,
	THREE = VK_NUMPAD3,
	FOUR = VK_NUMPAD4,
	FIVE = VK_NUMPAD5,
	SIX = VK_NUMPAD6,
	SEVEN = VK_NUMPAD7,
	EIGHT = VK_NUMPAD8,

	// 알파벳
	A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F', G = 'G',
	H = 'H', I = 'I', J = 'J', K = 'K', L = 'L', M = 'M', N = 'N',
	O = 'O', P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T', U = 'U',
	V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z'
};

/***************
	콜라이더 모양 타입
***************/
enum class EColliderType
{
	RECTANGLE,
	CIRCLE,
	ENUM_END
};

/***************
	콜리전 레이어 타입
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
	오브젝트 레이어 타입(?)
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
	타일 타입
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
	신 타입
***************/
enum class ESceneType
{
	TEST,
	COMPETE,
	ENUM_END
};


/***************
	버튼 상태
***************/
enum class EButtonState
{
	ENABLE,		// 버튼이 활성화된 상태
	RELEASE,	// 버튼에 마우스를 내린 상태
	HOVER,		// 버튼에 마우스를 올린 상태
	PRESS,		// 버튼을 누르고 있는 상태
	CLICK,		// 버튼을 클릭한 상태
	DISABLE,	// 버튼이 비활성화된 상태
	ENUM_END
};


/***************
	사운드 타입
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
	콘텐츠 열거체
********************/

/***************
	사용자 인터페이스 타입
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
	소유자 타입
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
	종족 타입
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
	테란 종류
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
	테란 건물 종류
***************/
enum class ETerranBuildingType
{
	// 기본 건물
	COMMAND_CENTER,
	SUPPLY_DEPOT,
	REFINERY,
	BARRACKS,
	ENGINEERING_BAY,
	ACADEMY,
	MISSILE_TURRET,
	BUNKER,

	// 응용 건물
	FACTORY,
	ARMORY,
	STARPORT,
	SCIENCE_FACILITY,

	// 에드온
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
	테란 유닛 종류
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
	테란 업그레이드 종류
***************/
enum class ETerranUpgradeType
{
	// 엔지니어링 베이
	INFANTRY_WEAPONS_1,
	INFANTRY_WEAPONS_2,
	INFANTRY_WEAPONS_3,
	INFANTRY_ARMOR_1,
	INFANTRY_ARMOR_2,
	INFANTRY_ARMOR_3,

	// 아카데미
	U238_SHELLS,
	STIMPACK_TECH,
	RESTORATION,
	OPTICAL_FLARE,
	CADUCEUS_REACTOR,

	// 아머리
	VIHICLE_WEAPONS_1,
	VIHICLE_WEAPONS_2,
	VIHICLE_WEAPONS_3,
	VIHICLE_PLATING_1,
	VIHICLE_PLATING_2,
	VIHICLE_PLATING_3,

	SHIP_WEAPONS,
	SHIP_PLATING,
	
	// 뉴클리어 사일로
	ARM_NUCLEAR_SILO,

	// 사이언스 퍼실리티
	IRRADIATE,
	TITAN_REACTOR,

	// 머신샵
	ION_THRUSTERS,
	SPIDER_MINES,
	SIEGE_TECH,
	CHARON_BOOSTERS,

	// TODO: 컨트롤 타워

	// TODO: 피직스 랩
	YAMATO_CANNON,
	COLOSSUS_REACTOR,

	// TODO: 코버트 옵스

	ENUM_END
};

/***************
	유닛 명령 종류
***************/
enum class ECommandType
{
	// *** 유닛 ***
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

	// *** 유닛 생산 ***
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

	// *** 건물 건설 ***
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

	// *** 업그레이드 ***
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

	// 마린, 파이어뱃
	USE_STIMPACK,

	// 메딕
	USE_HEAL,

	// 고스트
	//CLOCK,
	//LOCK_DOWN,
	USE_NUCLEAR_STRIKE,

	// 벌쳐
	//SPIDER_MINE,

	// 탱크
	SIEGE_MODE,
	TANK_MODE,

	// 사이언스 배슬
	USE_DEFENSIVE_MATRIX,
	USE_IRRADIATE,

	// 배틀쿠르저
	USE_YAMATO_CANNON,

	// *** 건물 ***
	// LIFT_OFF,
	// LAND,

	// SCANNER_SWEEP,

	// *** 취소 ***
	// 건물 선택 취소
	GO_BACK,
	CANCEL,
	CANCEL_LAST,
	CANCEL_UPGRADE,
	// CANCEL_CONSTRUCTION,

	ENUM_END
};


enum class ECommandWidgetState
{
	STATE_A,// 기본값
	STATE_B,// 기본 건물
	STATE_C,// 응용 건물
	STATE_D,// 뒤로 가기		cancel
	STATE_E,// 명령 취소		cancel
	STATE_F,// 유닛 생산 취소	cancel last
	STATE_G,// 업그레이드 취소	cancel upgrade
	STATE_H,// 건설 취소
	STATE_Z,// 빈 공간
	ENUM_END
};