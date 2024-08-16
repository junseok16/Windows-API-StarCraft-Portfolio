#include "pch.h"
#include "TestScene.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "MouseManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "SoundManager.h"

#include "Texture.h"

// TODO: 플레이어 테스트
#include "Map.h"
#include "Player.h"
#include "Cursor.h"

// TODO: 타일맵 테스트
#include "Tilemap.h"
#include "TilemapObject.h"
#include "StaticTilemapObject.h"
#include "DynamicTilemapObject.h"

// TODO: UI 테스트
#include "ButtonUI.h"
#include "TextUI.h"
#include "SpriteUI.h"
#include "SliderUI.h"
#include "AnimationUI.h"

#include "MiniMapWidget.h"
#include "SUnitProfileWidget.h"
#include "MUnitProfileWidget.h"
#include "CommandWidget.h"
#include "ResourceWidget.h"
#include "ControlCenter.h"
#include "CmdButton.h"

// TODO: 유닛 테스트
#include "UnitProperty.h"
#include "TerranObject.h"
#include "Unit.h"
#include "SCV.h"
#include "Marine.h"
#include "Firebat.h"
#include "Medic.h"
#include "Ghost.h"
#include "Vulture.h"
#include "SiegeTank.h"
#include "ScienceVessel.h"
#include "Battlecruiser.h"

#include "CommandCenter.h"
#include "Barracks.h"
#include "SupplyDepot.h"
#include "Academy.h"
#include "Factory.h"

// TODO: 자원 테스트
#include "Mineral.h"
#include "VespeneGas.h"
using namespace std;

void CTestScene::LoadTileTexture()
{
#pragma region Tilemap
	// 타일
	CTexture* pTileTexture = CResourceManager::GetManager()->LoadTexture(L"Tiles", L"Tilemap\\Tile\\Tiles.bmp", RGB(255, 0, 255));
	CSprite* pPassableTileSprite = CResourceManager::GetManager()->CreateSprite(L"PassableTile", pTileTexture, 0, 0, 32, 32);
	CSprite* pImpassableTileSprite = CResourceManager::GetManager()->CreateSprite(L"ImpassableTile", pTileTexture, 32, 0, 32, 32);
	CSprite* pResourceTileSprite = CResourceManager::GetManager()->CreateSprite(L"ImpassableTile", pTileTexture, 64, 0, 32, 32);
#pragma endregion
}

void CTestScene::LoadEffectTexture()
{
#pragma region Bang
	CTexture* pBangSTexture = CResourceManager::GetManager()->LoadTexture(L"BangS", L"Texture\\Multi\\Effect\\BangBangS.bmp", RGB(0, 255, 0));
	CTexture* pBangMTexture = CResourceManager::GetManager()->LoadTexture(L"BangM", L"Texture\\Multi\\Effect\\BangBangM.bmp", RGB(0, 255, 0));
	CTexture* pBangLTexture = CResourceManager::GetManager()->LoadTexture(L"BangL", L"Texture\\Multi\\Effect\\BangBangL.bmp", RGB(0, 0, 0));

	CResourceManager::GetManager()->CreateAnimation(L"BangS", pBangSTexture, L"BangS", true, { 0, 0 }, { 0, 8 }, { 128, 128 }, 0.7f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BangM", pBangMTexture, L"BangM", false, { 0, 10 }, { 0, 0 }, { 200, 200 }, 0.7f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BangL", pBangLTexture, L"BangL", false, { 0, 13 }, { 0, 0 }, { 252, 200 }, 0.7f, true, false);
#pragma endregion

#pragma region Defensive Matrix
	CTexture* pDfnsvMtrxSTexture = CResourceManager::GetManager()->LoadTexture(L"DfnsvMtrxS", L"Texture\\Multi\\Effect\\DefensiveMatrixS.bmp", RGB(0, 0, 0));
	CTexture* pDfnsvMtrxMTexture = CResourceManager::GetManager()->LoadTexture(L"DfnsvMtrxM", L"Texture\\Multi\\Effect\\DefensiveMatrixM.bmp", RGB(0, 255, 0));
	CTexture* pDfnsvMtrxLTexture = CResourceManager::GetManager()->LoadTexture(L"DfnsvMtrxL", L"Texture\\Multi\\Effect\\DefensiveMatrixL.bmp", RGB(0, 0, 0));

	CResourceManager::GetManager()->CreateAnimation(L"DfnsvMtrxS", pDfnsvMtrxSTexture, L"DfnsvMtrxS", false, { 0, 14 }, { 0, 0 }, { 32, 32 }, 0.8f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"DfnsvMtrxM", pDfnsvMtrxMTexture, L"DfnsvMtrxM", false, { 0, 4 }, { 0, 0 }, { 64, 64 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"DfnsvMtrxL", pDfnsvMtrxLTexture, L"DfnsvMtrxL", false, { 0, 14 }, { 0, 0 }, { 128, 128 }, 0.8f, false, true);
#pragma endregion
	
#pragma region Irradiate
	CTexture* pIrdtTexture = CResourceManager::GetManager()->LoadTexture(L"Irdt", L"Texture\\Multi\\Effect\\Irradiate.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"Irdt", pIrdtTexture, L"Irdt", false, { 0, 5 }, { 0, 0 }, { 120, 120 }, 0.4f, false, true);
#pragma endregion
}

void CTestScene::LoadUITexture()
{
#pragma region Map
	// 맵
	CTexture* pMainMapTexture = CResourceManager::GetManager()->LoadTexture(L"FightingSpirit", L"Texture\\Single\\Map\\FightingSpirit\\MainMap.bmp");
	CResourceManager::GetManager()->CreateSprite(L"FightingSpirit", pMainMapTexture, 0, 0, 4096, 4096);

	CTexture* pMiniMapTexture = CResourceManager::GetManager()->LoadTexture(L"MiniMap00", L"Texture\\Single\\Map\\FightingSpirit\\MiniMap.bmp");
	CResourceManager::GetManager()->CreateSprite(L"MiniMap00", pMiniMapTexture, 0, 0, 160, 160);
#pragma endregion

#pragma region Control Center
	// 컨트롤 센터
	CTexture* pCtrlCenterTexture = CResourceManager::GetManager()->LoadTexture(L"CtrlCenterUI", L"Texture\\Single\\UI\\TerranMainUI.bmp", RGB(0, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"CtrlCenterUI", pCtrlCenterTexture, 0, 0, 800, 600);
#pragma endregion

#pragma region Resource
	// 미네랄
	CTexture* pMineralTexture = CResourceManager::GetManager()->LoadTexture(L"MineralUI", L"Texture\\Single\\UI\\MineralUI.bmp", RGB(255, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"MineralUI", pMineralTexture, 0, 0, 14, 14);

	// 가스
	CTexture* pGasTexture = CResourceManager::GetManager()->LoadTexture(L"GasUI", L"Texture\\Single\\UI\\GasUI.bmp", RGB(255, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"GasUI", pGasTexture, 0, 0, 14, 14);

	// 보급품
	CTexture* pSplyTexture = CResourceManager::GetManager()->LoadTexture(L"SplyUI", L"Texture\\Single\\UI\\SupplyUI.bmp", RGB(255, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"SplyUI", pSplyTexture, 0, 0, 14, 14);
#pragma endregion

#pragma region Cursor
	// 커서
	CTexture* pCrsrTexture = CResourceManager::GetManager()->LoadTexture(L"Crsr", L"Texture\\Multi\\Cursor\\Cursor.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateAnimation(L"CrsrRls", pCrsrTexture, L"CrsrRls", false, { 0, 4 }, { 0, 0 }, { 50, 50 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrDrg", pCrsrTexture, L"CrsrDrg", false, { 5, 5 }, { 0, 0 }, { 50, 50 }, 1.0f, false, true);
	
	CResourceManager::GetManager()->CreateAnimation(L"CrsrE",	pCrsrTexture, L"CrsrE",	false, {  0,  1 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrNE",	pCrsrTexture, L"CrsrNE",false, {  2,  3 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrN",	pCrsrTexture, L"CrsrN", false, {  4,  5 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrNW",	pCrsrTexture, L"CrsrNW",false, {  6,  7 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrW",	pCrsrTexture, L"CrsrW", false, {  8,  9 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrSW",	pCrsrTexture, L"CrsrSW",false, { 10, 11 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrS",	pCrsrTexture, L"CrsrS",	false, { 12, 13 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrSE",	pCrsrTexture, L"CrsrSE",false, { 14, 15 }, { 1, 1 }, { 50, 50 }, 0.2f, false, true);
	
	CResourceManager::GetManager()->CreateAnimation(L"CrsrRttPlyr",  pCrsrTexture, L"CrsrRttPlyr",  false, {  0, 13 }, { 2, 2 }, { 50, 50 }, 1.5f,  false,true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrRttNtrl",  pCrsrTexture, L"CrsrRttNtrl",  false, {  0, 13 }, { 3, 3 }, { 50, 50 }, 1.5f,  false,true);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrRttCmptr", pCrsrTexture, L"CrsrRttCmptr", false, {  0, 13 }, { 4, 4 }, { 50, 50 }, 1.5f,  false,true);

	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrclPlyr",  pCrsrTexture, L"CrsrCrclPlyr", false, {  0,  3 }, { 5, 5 }, { 50, 50 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrclNtrl",  pCrsrTexture, L"CrsrCrclNtrl", false, {  5,  8 }, { 5, 5 }, { 50, 50 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrclCmptr", pCrsrTexture, L"CrsrCrclCmptr",false, { 10, 13 }, { 5, 5 }, { 50, 50 }, 0.2f, true, false);

	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrssPlyr",  pCrsrTexture, L"CrsrCrssPlyr", false, {  4,  4 }, { 5, 5 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrssNtrl",  pCrsrTexture, L"CrsrCrssNtrl", false, {  9,  9 }, { 5, 5 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CrsrCrssCmptr", pCrsrTexture, L"CrsrCrssCmptr",false, { 14, 14 }, { 5, 5 }, { 50, 50 }, 1.0f, true, false);
#pragma endregion

#pragma region Command Icon

	/*********************************************************************************************************/

	// 생산 아이콘
	CTexture* pBuildQueUnitTexture = CResourceManager::GetManager()->LoadTexture(L"BuildQueueUnit", L"Texture\\Multi\\Icon\\BuildQueueIcon.bmp", RGB(0, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"CmdSCVBuild", pBuildQueUnitTexture,  0, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdMrnBuild", pBuildQueUnitTexture,  40, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdFrbtBuild", pBuildQueUnitTexture, 80, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdMdcBuild", pBuildQueUnitTexture,  120, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdGhstBuild", pBuildQueUnitTexture, 160, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdVltrBuild", pBuildQueUnitTexture, 200, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdTnkBuild", pBuildQueUnitTexture,  240, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdGlthBuild", pBuildQueUnitTexture, 280, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdScncVslBuild", pBuildQueUnitTexture, 400, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdBtlcrsrBuild", pBuildQueUnitTexture, 480, 0, 40, 40);

	/*********************************************************************************************************/

	// 명령 아이콘
	CTexture* pCmdBttnTexture = CResourceManager::GetManager()->LoadTexture(L"CmdBttn", L"Texture\\Multi\\Icon\\CmdButton.bmp", RGB(0, 255, 0));

	// 이동 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdMoveRelease", pCmdBttnTexture, 0, 0, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMovePress",	pCmdBttnTexture, 44, 0, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMoveDisable", pCmdBttnTexture, 176, 0, 44, 44);

	// 정지 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdStopRelease", pCmdBttnTexture, 0, 44, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStopPress", pCmdBttnTexture, 44, 44, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStopDisable", pCmdBttnTexture, 176, 44, 44, 44);

	// 공격 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdAtckRelease", pCmdBttnTexture, 0, 88, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAtckPress", pCmdBttnTexture, 44, 88, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAtckDisable", pCmdBttnTexture, 176, 88, 44, 44);

	// 취소 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdCnclRelease", pCmdBttnTexture,	0,   220, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCnclPress", pCmdBttnTexture,		44,  220, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCnclDisable", pCmdBttnTexture,	176, 220, 44, 44);
	
	// 집결 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdRllyPntRelease", pCmdBttnTexture,   0, 264, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdRllyPntPress", pCmdBttnTexture,	 44, 264, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdRllyPntDisable", pCmdBttnTexture, 176, 264, 44, 44);

	// 채집 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdGthrRelease", pCmdBttnTexture,   0, 308, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGthrPress", pCmdBttnTexture,	 44, 308, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGthrDisable", pCmdBttnTexture, 176, 308, 44, 44);

	// 기본 건물 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdBscStrctrRelease", pCmdBttnTexture, 0,	396, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBscStrctrPress", pCmdBttnTexture, 44,		396, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBscStrctrDisable", pCmdBttnTexture, 176,	396, 44, 44);

	// 응용 건물 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdAdvcdStrctrRelease", pCmdBttnTexture, 0,	440, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAdvcdStrctrPress", pCmdBttnTexture, 44,	440, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAdvcdStrctrDisable", pCmdBttnTexture, 176,440, 44, 44);

	/*********************************************************************************************************/

	// SCV 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdSCVRelease",	pCmdBttnTexture, 0, 484, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSCVPress",	pCmdBttnTexture, 44, 484, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSCVDisable",	pCmdBttnTexture, 176, 484, 44, 44);

	// 마린 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdMrnRelease", pCmdBttnTexture, 0, 528, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMrnPress", pCmdBttnTexture, 44, 528, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMrnDisable", pCmdBttnTexture, 176, 528, 44, 44);

	// 파이어뱃 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdFrbtRelease", pCmdBttnTexture, 0, 572, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdFrbtPress", pCmdBttnTexture, 44, 572, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdFrbtDisable", pCmdBttnTexture, 176, 572, 44, 44);

	// 메딕 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdMdcRelease", pCmdBttnTexture, 0, 1848, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMdcPress", pCmdBttnTexture, 44, 1848, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMdcDisable", pCmdBttnTexture, 176, 1848, 44, 44);

	// 고스트 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdGhstRelease", pCmdBttnTexture, 0, 616, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGhstPress", pCmdBttnTexture, 44, 616, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGhstDisable", pCmdBttnTexture, 176, 616, 44, 44);

	/*********************************************************************************************************/

	// 벌쳐 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdVltrRelease", pCmdBttnTexture,   0, 660, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdVltrPress", pCmdBttnTexture,	  44, 660, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdVltrDisable", pCmdBttnTexture, 176, 660, 44, 44);

	// 탱크 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdTnkRelease", pCmdBttnTexture,   0, 704, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdTnkPress",	pCmdBttnTexture, 44, 704, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdTnkDisable", pCmdBttnTexture, 176, 704, 44, 44);

	// 시즈 탱크 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdSiegeTnkRelease", pCmdBttnTexture,   0, 2774, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSiegeTnkPress", pCmdBttnTexture,    44, 2774, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSiegeTnkDisable", pCmdBttnTexture, 176, 2774, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSiegeTnkUpgrade", pCmdBttnTexture, 88, 2774, 44, 44);

	// 골리앗 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdGlthRelease", pCmdBttnTexture,   0, 748, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGlthPress", pCmdBttnTexture,    44, 748, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdGlthDisable", pCmdBttnTexture, 176, 748, 44, 44);

	/*********************************************************************************************************/

	// 사이언스 배슬 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdScncVslRelease", pCmdBttnTexture,   0, 924, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdScncVslPress",   pCmdBttnTexture,  44, 924, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdScncVslDisable", pCmdBttnTexture, 176, 924, 44, 44);

	// 배틀쿠르저 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdBtlcrsrRelease", pCmdBttnTexture,   0, 880, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBtlcrsrPress",   pCmdBttnTexture,  44, 880, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBtlcrsrDisable", pCmdBttnTexture, 176, 880, 44, 44);

	/*********************************************************************************************************/

	// 커맨드 센터 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdCmndCntrRelease", pCmdBttnTexture, 0,	 968, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCmndCntrPress",	pCmdBttnTexture, 44, 968, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCmndCntrDisable", pCmdBttnTexture, 176, 968, 44, 44);

	// 서플라이 디포 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdSplyDptRelease", pCmdBttnTexture, 0,	 1012, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSplyDptPress",	pCmdBttnTexture, 44, 1012, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdSplyDptDisable", pCmdBttnTexture, 176, 1012, 44, 44);

	// 리파이너리 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdRfnryRelease", pCmdBttnTexture,	0,   1056, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdRfnryPress", pCmdBttnTexture,		44,  1056, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdRfnryDisable", pCmdBttnTexture,	176, 1056, 44, 44);

	// 배럭 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdBrcksRelease", pCmdBttnTexture, 0,	1100, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBrcksPress",	pCmdBttnTexture, 44,	1100, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdBrcksDisable", pCmdBttnTexture, 176,	1100, 44, 44);

	// 엔지니어링 베이 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdEngnrByRelease", pCmdBttnTexture, 0, 1144, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdEngnrByPress", pCmdBttnTexture, 44, 1144, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdEngnrByDisable", pCmdBttnTexture, 176, 1144, 44, 44);

	// 아카데미 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdAcdmyRelease", pCmdBttnTexture, 0,	1232, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAcdmyPress",	pCmdBttnTexture, 44,	1232, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdAcdmyDisable", pCmdBttnTexture, 176,	1232, 44, 44);

	// 팩토리 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdFctryRelease", pCmdBttnTexture, 0,	1320, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdFctryPress",	pCmdBttnTexture, 44,	1320, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdFctryDisable", pCmdBttnTexture, 176,	1320, 44, 44);

	// 스타포트 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdStrprtRelease", pCmdBttnTexture,	0,   1366, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStrprtPress", pCmdBttnTexture,	44,  1366, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStrprtDisable", pCmdBttnTexture,	176, 1366, 44, 44);

	// 사이언스 퍼실리티 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdScencFcltyRelease", pCmdBttnTexture,	 0, 1410, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdScencFcltyPress", pCmdBttnTexture,	44, 1410, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdScencFcltyDisable", pCmdBttnTexture, 176, 1410, 44, 44);

	// 아머리 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdArmryRelease", pCmdBttnTexture, 0,	1454, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdArmryPress", pCmdBttnTexture, 44,		1454, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdArmryDisable", pCmdBttnTexture, 176,	1454, 44, 44);

	/*********************************************************************************************************/

	// 콤셋 스테이션 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdCmstStnRelease", pCmdBttnTexture,   0, 1498, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCmstStnPress", pCmdBttnTexture,    44, 1498, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCmstStnDisable", pCmdBttnTexture, 176, 1498, 44, 44);

	// 뉴클리어 사일로 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrSloRelease", pCmdBttnTexture,   0, 1542, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrSloPress", pCmdBttnTexture,    44, 1542, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrSloDisable", pCmdBttnTexture, 176, 1542, 44, 44);

	// 코버트 옵스 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdCvrtOpsRelease", pCmdBttnTexture,   0, 1586, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCvrtOpsPress",   pCmdBttnTexture,  44, 1586, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCvrtOpsDisable", pCmdBttnTexture, 176, 1586, 44, 44);

	// 피직스 랩 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdPhyscLbRelease", pCmdBttnTexture,   0, 1630, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdPhyscLbPress",   pCmdBttnTexture,  44, 1630, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdPhyscLbDisable", pCmdBttnTexture, 176, 1630, 44, 44);

	// 컨트롤타워 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdCntrlTwrRelease", pCmdBttnTexture,   0, 1674, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCntrlTwrPress",   pCmdBttnTexture,  44, 1674, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdCntrlTwrDisable", pCmdBttnTexture, 176, 1674, 44, 44);

	// 머신샵 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdMchnShpRelease", pCmdBttnTexture,   0, 1718, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMchnShpPress", pCmdBttnTexture,    44, 1718, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdMchnShpDisable", pCmdBttnTexture, 176, 1718, 44, 44);

	/*********************************************************************************************************/

	// 마린 사거리 업그레이드 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdU238Release", pCmdBttnTexture,   0, 1936, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdU238Press", pCmdBttnTexture,    44, 1936, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdU238Disable", pCmdBttnTexture, 176, 1936, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdU238Upgrade", pCmdBttnTexture, 88, 1936, 44, 44);

	// 스팀팩 업그레이드 아이콘
	CResourceManager::GetManager()->CreateSprite(L"CmdStmpckRelease", pCmdBttnTexture,   0, 1980, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStmpckPress", pCmdBttnTexture,    44, 1980, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStmpckDisable", pCmdBttnTexture, 176, 1980, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdStmpckUpgrade", pCmdBttnTexture, 88, 1980, 44, 44);

	// 보병 공격력 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyWpnRelease", pCmdBttnTexture,   0, 2156, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyWpnPress", pCmdBttnTexture,    44, 2156, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyWpnDisable", pCmdBttnTexture, 176, 2156, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyWpnUpgrade", pCmdBttnTexture, 88, 2156, 44, 44);

	// 보병 방어력 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyArmrRelease", pCmdBttnTexture,   0, 2200, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyArmrPress", pCmdBttnTexture,    44, 2200, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyArmrDisable", pCmdBttnTexture, 176, 2200, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpInftyArmrUpgrade", pCmdBttnTexture, 88, 2200, 44, 44);

	// 이온 클러스터 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdUpIonKlstrRelease", pCmdBttnTexture,   0, 2686, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpIonKlstrPress", pCmdBttnTexture,    44, 2686, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpIonKlstrDisable", pCmdBttnTexture, 176, 2686, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpIonKlstrUpgrade", pCmdBttnTexture, 88, 2686, 44, 44);

	// 힐 아이콘
	CTexture* pCmdHealBttnTexture = CResourceManager::GetManager()->LoadTexture(L"CmdHealBttn", L"Texture\\Multi\\Icon\\CmdHealButton.bmp", RGB(255, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"CmdHealRelease",	pCmdHealBttnTexture, 0, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdHealPress",	pCmdHealBttnTexture, 0, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdHealDisable",	pCmdHealBttnTexture, 0, 0, 40, 40);

	// 차량 공격력 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclWpnRelease", pCmdBttnTexture,	  0, 2244, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclWpnPress",pCmdBttnTexture,		 44, 2244, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclWpnDisable", pCmdBttnTexture,	176, 2244, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclWpnUpgrade", pCmdBttnTexture,	 88, 2244, 44, 44);

	// 차량 방어력 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclPltngRelease", pCmdBttnTexture,	  0, 2332, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclPltngPress", pCmdBttnTexture,	 44, 2332, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclPltngDisable", pCmdBttnTexture, 176, 2332, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdUpVhclPltngUpgrade", pCmdBttnTexture,  88, 2332, 44, 44);

	// 디펜시브 매트릭스
	CTexture* pCmdDfnsvMtrxBttnTexture = CResourceManager::GetManager()->LoadTexture(L"CmdDfnsvMtrxBttn", L"Texture\\Multi\\Icon\\CmdDfnsvMtrxButton.bmp", RGB(255, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"CmdDfnsvMtrxRelease", pCmdDfnsvMtrxBttnTexture, 0, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdDfnsvMtrxPress", pCmdDfnsvMtrxBttnTexture, 0, 0, 40, 40);
	CResourceManager::GetManager()->CreateSprite(L"CmdDfnsvMtrxDisable", pCmdDfnsvMtrxBttnTexture, 0, 0, 40, 40);

	// 이레디에이트 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdIrdtRelease", pCmdBttnTexture,  0,  2464, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdIrdtPress",   pCmdBttnTexture,  44, 2464, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdIrdtDisable", pCmdBttnTexture, 176, 2464, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdIrdtUpgrade", pCmdBttnTexture,  88, 2464, 44, 44);

	// 아마토포 업그레이드
	CResourceManager::GetManager()->CreateSprite(L"CmdYmtRelease", pCmdBttnTexture,   0, 2862, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdYmtPress",   pCmdBttnTexture,  44, 2862, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdYmtDisable", pCmdBttnTexture, 176, 2862, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdYmtUpgrade", pCmdBttnTexture,  88, 2862, 44, 44);

	// 뉴클리어 사일로 무장
	CResourceManager::GetManager()->CreateSprite(L"CmdArmNclrSloRelease", pCmdBttnTexture,   0, 2950, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdArmNclrSloPress",   pCmdBttnTexture,  44, 2950, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdArmNclrSloDisable", pCmdBttnTexture, 176, 2950, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdArmNclrSloUpgrade", pCmdBttnTexture,  88, 2950, 44, 44);

	// 핵 공격
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrStrkRelease", pCmdBttnTexture,   0, 3302, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrStrkPress",   pCmdBttnTexture,  44, 3302, 44, 44);
	CResourceManager::GetManager()->CreateSprite(L"CmdNclrStrkDisable", pCmdBttnTexture, 176, 3302, 44, 44);

#pragma endregion

#pragma region Wireframe
	// 큰 와이어프레임
	CTexture* pBgWrfrmTexture = CResourceManager::GetManager()->LoadTexture(L"BgWrfrm", L"Texture\\Multi\\Wire\\BigWireframe.bmp", RGB(0, 0, 0));

	// SCV 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm0", pBgWrfrmTexture, 0,   0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm1", pBgWrfrmTexture, 64,  0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm2", pBgWrfrmTexture, 128, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm3", pBgWrfrmTexture, 192, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm4", pBgWrfrmTexture, 256, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SCVBgWrfrm5", pBgWrfrmTexture, 320, 0, 64, 64);

	// 마린 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm0", pBgWrfrmTexture, 0, 64, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm1", pBgWrfrmTexture, 64, 64, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm2", pBgWrfrmTexture, 128, 64, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm3", pBgWrfrmTexture, 192, 64, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm4", pBgWrfrmTexture, 256, 64, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MrnBgWrfrm5", pBgWrfrmTexture, 320, 64, 64, 64);

	// 파이어뱃 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm0", pBgWrfrmTexture, 0,	128, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm1", pBgWrfrmTexture, 64,	128, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm2", pBgWrfrmTexture, 128,	128, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm3", pBgWrfrmTexture, 192,	128, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm4", pBgWrfrmTexture, 256,	128, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FrbtBgWrfrm5", pBgWrfrmTexture, 320,	128, 64, 64);

	// 메딕 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm0", pBgWrfrmTexture, 0,	256, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm1", pBgWrfrmTexture, 64,	256, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm2", pBgWrfrmTexture, 128,  256, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm3", pBgWrfrmTexture, 192,  256, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm4", pBgWrfrmTexture, 256,  256, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MdcBgWrfrm5", pBgWrfrmTexture, 320,  256, 64, 64);
	
	// 고스트 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm0", pBgWrfrmTexture, 0,	192, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm1", pBgWrfrmTexture, 64,	192, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm2", pBgWrfrmTexture, 128, 192, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm3", pBgWrfrmTexture, 192, 192, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm4", pBgWrfrmTexture, 256, 192, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GhstBgWrfrm5", pBgWrfrmTexture, 320, 192, 64, 64);

	// 벌쳐 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm0", pBgWrfrmTexture,   0, 320, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm1", pBgWrfrmTexture,  64, 320, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm2", pBgWrfrmTexture, 128, 320, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm3", pBgWrfrmTexture, 192, 320, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm4", pBgWrfrmTexture, 256, 320, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VltrBgWrfrm5", pBgWrfrmTexture, 320, 320, 64, 64);

	// 탱크 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm0", pBgWrfrmTexture,   0,	384, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm1", pBgWrfrmTexture,  64,	384, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm2", pBgWrfrmTexture, 128,  384, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm3", pBgWrfrmTexture, 192,  384, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm4", pBgWrfrmTexture, 256,  384, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"TnkBgWrfrm5", pBgWrfrmTexture, 320,  384, 64, 64);

	// 시즈 탱크 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm0", pBgWrfrmTexture, 0,   448, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm1", pBgWrfrmTexture, 64,  448, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm2", pBgWrfrmTexture, 128, 448, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm3", pBgWrfrmTexture, 192, 448, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm4", pBgWrfrmTexture, 256, 448, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkBgWrfrm5", pBgWrfrmTexture, 320, 448, 64, 64);

	// 골리앗 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm0", pBgWrfrmTexture,   0, 512, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm1", pBgWrfrmTexture,  64, 512, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm2", pBgWrfrmTexture, 128, 512, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm3", pBgWrfrmTexture, 192, 512, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm4", pBgWrfrmTexture, 256, 512, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"GlthBgWrfrm5", pBgWrfrmTexture, 320, 512, 64, 64);

	// 사이언스 배슬 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm0", pBgWrfrmTexture,   0, 640, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm1", pBgWrfrmTexture,  64, 640, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm2", pBgWrfrmTexture, 128, 640, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm3", pBgWrfrmTexture, 192, 640, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm4", pBgWrfrmTexture, 256, 640, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslBgWrfrm5", pBgWrfrmTexture, 320, 640, 64, 64);

	// 배틀쿠르저 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm0", pBgWrfrmTexture,   0, 704, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm1", pBgWrfrmTexture,  64, 704, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm2", pBgWrfrmTexture, 128, 704, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm3", pBgWrfrmTexture, 192, 704, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm4", pBgWrfrmTexture, 256, 704, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrBgWrfrm5", pBgWrfrmTexture, 320, 704, 64, 64);

	/******************************************************************************************************************/

	// 커맨드 센터 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm0", pBgWrfrmTexture, 0,	960, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm1", pBgWrfrmTexture, 64,	960, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm2", pBgWrfrmTexture, 128, 960, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm3", pBgWrfrmTexture, 192, 960, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm4", pBgWrfrmTexture, 256, 960, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmndCntrBgWrfrm5", pBgWrfrmTexture, 320, 960, 64, 64);

	// 서플라이 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm0", pBgWrfrmTexture, 0,   1024, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm1", pBgWrfrmTexture, 64,  1024, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm2", pBgWrfrmTexture, 128, 1024, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm3", pBgWrfrmTexture, 192, 1024, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm4", pBgWrfrmTexture, 256, 1024, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyDptBgWrfrm5", pBgWrfrmTexture, 320, 1024, 64, 64);

	// 리파이너리 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm0", pBgWrfrmTexture, 0,   1088, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm1", pBgWrfrmTexture, 64,  1088, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm2", pBgWrfrmTexture, 128, 1088, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm3", pBgWrfrmTexture, 192, 1088, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm4", pBgWrfrmTexture, 256, 1088, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryBgWrfrm5", pBgWrfrmTexture, 320, 1088, 64, 64);

	// 배럭 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm0", pBgWrfrmTexture,	0,	 1152, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm1", pBgWrfrmTexture,	64,	 1152, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm2", pBgWrfrmTexture,	128, 1152, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm3", pBgWrfrmTexture,	192, 1152, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm4", pBgWrfrmTexture,	256, 1152, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksBgWrfrm5", pBgWrfrmTexture,	320, 1152, 64, 64);

	// 엔지니어링 베이 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm0", pBgWrfrmTexture, 0,   1216, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm1", pBgWrfrmTexture, 64,  1216, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm2", pBgWrfrmTexture, 128, 1216, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm3", pBgWrfrmTexture, 192, 1216, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm4", pBgWrfrmTexture, 256, 1216, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByBgWrfrm5", pBgWrfrmTexture, 320, 1216, 64, 64);

	// 아카데미 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm0", pBgWrfrmTexture, 0,   1344, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm1", pBgWrfrmTexture, 64,  1344, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm2", pBgWrfrmTexture, 128, 1344, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm3", pBgWrfrmTexture, 192, 1344, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm4", pBgWrfrmTexture, 256, 1344, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyBgWrfrm5", pBgWrfrmTexture, 320, 1344, 64, 64);

	// 팩토리 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm0", pBgWrfrmTexture, 0,   1472, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm1", pBgWrfrmTexture, 64,  1472, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm2", pBgWrfrmTexture, 128, 1472, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm3", pBgWrfrmTexture, 192, 1472, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm4", pBgWrfrmTexture, 256, 1472, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"FctryBgWrfrm5", pBgWrfrmTexture, 320, 1472, 64, 64);

	// 스타포트 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm0", pBgWrfrmTexture, 0,	 1536, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm1", pBgWrfrmTexture, 64,  1536, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm2", pBgWrfrmTexture, 128, 1536, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm3", pBgWrfrmTexture, 192, 1536, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm4", pBgWrfrmTexture, 256, 1536, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"StrprtBgWrfrm5", pBgWrfrmTexture, 320, 1536, 64, 64);
	
	// 사이언스 퍼실리티 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm0", pBgWrfrmTexture, 0,   1600, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm1", pBgWrfrmTexture, 64,  1600, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm2", pBgWrfrmTexture, 128, 1600, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm3", pBgWrfrmTexture, 192, 1600, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm4", pBgWrfrmTexture, 256, 1600, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyBgWrfrm5", pBgWrfrmTexture, 320, 1600, 64, 64);

	// 아머리 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm0", pBgWrfrmTexture, 0,   1664, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm1", pBgWrfrmTexture, 64,  1664, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm2", pBgWrfrmTexture, 128, 1664, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm3", pBgWrfrmTexture, 192, 1664, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm4", pBgWrfrmTexture, 256, 1664, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryBgWrfrm5", pBgWrfrmTexture, 320, 1664, 64, 64);

	/******************************************************************************************************************/

	// 콤셋 스테이션 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm0", pBgWrfrmTexture,   0, 1728, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm1", pBgWrfrmTexture,  64, 1728, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm2", pBgWrfrmTexture, 128, 1728, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm3", pBgWrfrmTexture, 192, 1728, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm4", pBgWrfrmTexture, 256, 1728, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CmstStnBgWrfrm5", pBgWrfrmTexture, 320, 1728, 64, 64);

	// 뉴클리어 사일로 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm0", pBgWrfrmTexture,   0, 1792, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm1", pBgWrfrmTexture,  64, 1792, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm2", pBgWrfrmTexture, 128, 1792, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm3", pBgWrfrmTexture, 192, 1792, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm4", pBgWrfrmTexture, 256, 1792, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloBgWrfrm5", pBgWrfrmTexture, 320, 1792, 64, 64);

	// 코버트옵스 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm0", pBgWrfrmTexture,   0, 1856, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm1", pBgWrfrmTexture,  64, 1856, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm2", pBgWrfrmTexture, 128, 1856, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm3", pBgWrfrmTexture, 192, 1856, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm4", pBgWrfrmTexture, 256, 1856, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsBgWrfrm5", pBgWrfrmTexture, 320, 1856, 64, 64);

	// 피직스랩 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm0", pBgWrfrmTexture,   0, 1920, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm1", pBgWrfrmTexture,  64, 1920, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm2", pBgWrfrmTexture, 128, 1920, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm3", pBgWrfrmTexture, 192, 1920, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm4", pBgWrfrmTexture, 256, 1920, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhyscLbBgWrfrm5", pBgWrfrmTexture, 320, 1920, 64, 64);
	
	// 컨트롤 타워 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm0", pBgWrfrmTexture,   0, 1984, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm1", pBgWrfrmTexture,  64, 1984, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm2", pBgWrfrmTexture, 128, 1984, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm3", pBgWrfrmTexture, 192, 1984, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm4", pBgWrfrmTexture, 256, 1984, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrBgWrfrm5", pBgWrfrmTexture, 320, 1984, 64, 64);

	// 머신샵 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm0", pBgWrfrmTexture,   0, 2048, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm1", pBgWrfrmTexture,  64, 2048, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm2", pBgWrfrmTexture, 128, 2048, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm3", pBgWrfrmTexture, 192, 2048, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm4", pBgWrfrmTexture, 256, 2048, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShpBgWrfrm5", pBgWrfrmTexture, 320, 2048, 64, 64);

	// 미네랄 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm0", pBgWrfrmTexture,   0, 2112, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm1", pBgWrfrmTexture,  64, 2112, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm2", pBgWrfrmTexture, 128, 2112, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm3", pBgWrfrmTexture, 192, 2112, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm4", pBgWrfrmTexture, 256, 2112, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MnrlBgWrfrm5", pBgWrfrmTexture, 320, 2112, 64, 64);

	// 가스 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm0", pBgWrfrmTexture,   0, 2176, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm1", pBgWrfrmTexture,  64, 2176, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm2", pBgWrfrmTexture, 128, 2176, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm3", pBgWrfrmTexture, 192, 2176, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm4", pBgWrfrmTexture, 256, 2176, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"VspnGasBgWrfrm5", pBgWrfrmTexture, 320, 2176, 64, 64);

	/******************************************************************************************************************/

	// 작은 와이어프레임
	CTexture* pSmllWrfrmTexture = CResourceManager::GetManager()->LoadTexture(L"SmllWrfrm", L"Texture\\Multi\\Wire\\SmallWireframe.bmp", RGB(255, 255, 255));

	// SCV 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm0", pSmllWrfrmTexture, 0,   0, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm1", pSmllWrfrmTexture, 32,  0, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm2", pSmllWrfrmTexture, 64,  0, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm3", pSmllWrfrmTexture, 96,  0, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm4", pSmllWrfrmTexture, 128, 0, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SCVSmllWrfrm5", pSmllWrfrmTexture, 160, 0, 32, 32);

	// 마린 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm0", pSmllWrfrmTexture, 0,   32, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm1", pSmllWrfrmTexture, 32,  32, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm2", pSmllWrfrmTexture, 64,  32, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm3", pSmllWrfrmTexture, 96,  32, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm4", pSmllWrfrmTexture, 128, 32, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MrnSmllWrfrm5", pSmllWrfrmTexture, 160, 32, 32, 32);

	// 파이어뱃 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm0", pSmllWrfrmTexture, 0,	64, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm1", pSmllWrfrmTexture, 32,	64, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm2", pSmllWrfrmTexture, 64,	64, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm3", pSmllWrfrmTexture, 96,	64, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm4", pSmllWrfrmTexture, 128, 64, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"FrbtSmllWrfrm5", pSmllWrfrmTexture, 160, 64, 32, 32);

	// 메딕 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm0", pSmllWrfrmTexture, 0,	128, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm1", pSmllWrfrmTexture, 32,	128, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm2", pSmllWrfrmTexture, 64,	128, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm3", pSmllWrfrmTexture, 96,	128, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm4", pSmllWrfrmTexture, 128,	128, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"MdcSmllWrfrm5", pSmllWrfrmTexture, 160,	128, 32, 32);

	// 고스트 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm0", pSmllWrfrmTexture, 0,   96, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm1", pSmllWrfrmTexture, 32,  96, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm2", pSmllWrfrmTexture, 64,  96, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm3", pSmllWrfrmTexture, 96,  96, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm4", pSmllWrfrmTexture, 128, 96, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"GhstSmllWrfrm5", pSmllWrfrmTexture, 160, 96, 32, 32);

	// 벌쳐 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm0", pSmllWrfrmTexture,   0, 160, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm1", pSmllWrfrmTexture,  32, 160, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm2", pSmllWrfrmTexture,  64, 160, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm3", pSmllWrfrmTexture,  96, 160, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm4", pSmllWrfrmTexture, 128, 160, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm5", pSmllWrfrmTexture, 160, 160, 32, 32);

	// 탱크 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm0", pSmllWrfrmTexture, 0,	192, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm1", pSmllWrfrmTexture, 32,	192, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm2", pSmllWrfrmTexture, 64,	192, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm3", pSmllWrfrmTexture, 96,	192, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm4", pSmllWrfrmTexture, 128,	192, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"TnkSmllWrfrm5", pSmllWrfrmTexture, 160,	192, 32, 32);

	// 시즈 탱크 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm0", pSmllWrfrmTexture, 0,	 224, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm1", pSmllWrfrmTexture, 32,	 224, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm2", pSmllWrfrmTexture, 64,  224, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm3", pSmllWrfrmTexture, 96,  224, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm4", pSmllWrfrmTexture, 128, 224, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"SgTnkSmllWrfrm5", pSmllWrfrmTexture, 160, 224, 32, 32);

	// 골리앗 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm0", pSmllWrfrmTexture,   0, 256, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm1", pSmllWrfrmTexture,  32, 256, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm2", pSmllWrfrmTexture,  64, 256, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm3", pSmllWrfrmTexture,  96, 256, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm4", pSmllWrfrmTexture, 128, 256, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"VltrSmllWrfrm5", pSmllWrfrmTexture, 160, 256, 32, 32);

	// 사이언스 배슬 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm0", pSmllWrfrmTexture,   0, 320, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm1", pSmllWrfrmTexture,  32, 320, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm2", pSmllWrfrmTexture,  64, 320, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm3", pSmllWrfrmTexture,  96, 320, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm4", pSmllWrfrmTexture, 128, 320, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslSmllWrfrm5", pSmllWrfrmTexture, 160, 320, 32, 32);

	// 배틀쿠르저 와이어프레임
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm0", pSmllWrfrmTexture,   0, 352, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm1", pSmllWrfrmTexture,  32, 352, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm2", pSmllWrfrmTexture,  64, 352, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm3", pSmllWrfrmTexture,  96, 352, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm4", pSmllWrfrmTexture, 128, 352, 32, 32);
	CResourceManager::GetManager()->CreateSprite(L"BtlcrsrSmllWrfrm5", pSmllWrfrmTexture, 160, 352, 32, 32);

#pragma endregion

#pragma region Profile Box
	// 프로필 박스
	CTexture* pProfileBoxTexture = CResourceManager::GetManager()->LoadTexture(L"PrflBx", L"Texture\\Multi\\UI\\ProfileBox.bmp", RGB(255, 0, 255));

	// 파란 작은 박스
	CResourceManager::GetManager()->CreateSprite(L"SmlPrflBx", pProfileBoxTexture, 0, 1170, 45, 45);
	CResourceManager::GetManager()->CreateSprite(L"SmlPrflEmptyBx", pProfileBoxTexture, 45, 1170, 45, 45);

	// 업그레이드 큐
	CResourceManager::GetManager()->CreateSprite(L"UpgrdBx", pProfileBoxTexture, 0, 270, 45, 45);
#pragma endregion

#pragma region Portrait
	// 부관 초상화
	CTexture* pAdvsrPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"AdvsrPrtrt", L"Texture\\Multi\\Portrait\\Advisor.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"AdvsrPrtrt", pAdvsrPrtrtTexture, L"AdvsrPrtrt", false, { 0, 74 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// SCV 초상화
	CTexture* pSCVPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"SCVPrtrt", L"Texture\\Multi\\Portrait\\SCV.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"SCVPrtrt", pSCVPrtrtTexture, L"SCVPrtrt", false, { 0, 74 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 마린 초상화
	CTexture* pMrnPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"MrnPrtrt", L"Texture\\Multi\\Portrait\\Marine.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"MrnPrtrt", pMrnPrtrtTexture, L"MrnPrtrt", false, { 0, 44 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 파이어뱃 초상화
	CTexture* pFrbtPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"FrbtPrtrt", L"Texture\\Multi\\Portrait\\Firebat.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"FrbtPrtrt", pFrbtPrtrtTexture, L"FrbtPrtrt", false, { 0, 64 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 메딕 초상화
	CTexture* pMdcPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"MdcPrtrt", L"Texture\\Multi\\Portrait\\Medic.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"MdcPrtrt", pMdcPrtrtTexture, L"MdcPrtrt", false, { 0, 74 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 고스트 초상화
	CTexture* pGhstPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"GhstPrtrt", L"Texture\\Multi\\Portrait\\Ghost.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"GhstPrtrt", pGhstPrtrtTexture, L"GhstPrtrt", false, { 0, 69 }, { 0, 0 }, { 60, 56 }, 5.0f, false, true);

	// 벌쳐 초상화
	CTexture* pVltrPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"VltrPrtrt", L"Texture\\Multi\\Portrait\\Vulture.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrtrt", pVltrPrtrtTexture, L"VltrPrtrt", false, { 0, 65 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 탱크 초상화
	CTexture* pSgTnkPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"SgTnkPrtrt", L"Texture\\Multi\\Portrait\\SiegeTank.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkPrtrt", pSgTnkPrtrtTexture, L"SgTnkPrtrt", false, { 0, 74 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 골리앗 초상화
	CTexture* pGlthPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"GlthPrtrt", L"Texture\\Multi\\Portrait\\Goliath.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"GlthPrtrt", pGlthPrtrtTexture, L"GlthPrtrt", false, { 0, 49 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 사이언스 배슬 초상화
	CTexture* pScncVslPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"ScncVslPrtrt", L"Texture\\Multi\\Portrait\\ScienceVessel.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslPrtrt", pScncVslPrtrtTexture, L"ScncVslPrtrt", false, { 0, 49 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

	// 배틀쿠르저 초상화
	CTexture* pBtlcrsrPrtrtTexture = CResourceManager::GetManager()->LoadTexture(L"BtlcrsrPrtrt", L"Texture\\Multi\\Portrait\\Battlecruiser.bmp");
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrtrt", pBtlcrsrPrtrtTexture, L"Btlcrsr", false, { 0, 49 }, { 0, 0 }, { 60, 56 }, 7.0f, false, true);

#pragma endregion

#pragma region Build Queue
	// 생산 큐
	CTexture* pBuildQueTexture = CResourceManager::GetManager()->LoadTexture(L"BuildQueue", L"Texture\\Multi\\UI\\BuildQueue.bmp", RGB(0, 255, 255));
	CResourceManager::GetManager()->CreateSprite(L"BuildQue", pBuildQueTexture, 0, 0, 194, 94);

	CResourceManager::GetManager()->CreateSprite(L"PrgrsBarEmpty", pBuildQueTexture, 0, 146, 132, 9);
	CResourceManager::GetManager()->CreateSprite(L"PrgrsBarFull", pBuildQueTexture, 0, 160, 132, 9);
#pragma endregion

#pragma region Blueprint
	// 커맨드 센터
	CTexture* pCmdCntrBPTexture = CResourceManager::GetManager()->LoadTexture(L"CmdCntrBP", L"Texture\\Multi\\Building\\Blueprint\\CommandCenterOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"CmdCntrO", pCmdCntrBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"CmdCntrX", pCmdCntrBPTexture, 128, 0, 128, 96);

	// 서플라이 디포
	CTexture* pSplyDptBPTexture = CResourceManager::GetManager()->LoadTexture(L"SplyDptBP", L"Texture\\Multi\\Building\\Blueprint\\SupplyDepotOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"SplyO", pSplyDptBPTexture, 0, 0, 96, 64);
	CResourceManager::GetManager()->CreateSprite(L"SplyX", pSplyDptBPTexture, 96, 0, 96, 64);

	// 리파이너리
	CTexture* pRfnryBPTexture = CResourceManager::GetManager()->LoadTexture(L"RfnryBP", L"Texture\\Multi\\Building\\Blueprint\\RefineryOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"RfnryO", pRfnryBPTexture, 0, 0, 128, 64);
	CResourceManager::GetManager()->CreateSprite(L"RfnryX", pRfnryBPTexture, 128, 0, 128, 64);

	// 배럭
	CTexture* pBrrcksBPTexture = CResourceManager::GetManager()->LoadTexture(L"BrrcksBP", L"Texture\\Multi\\Building\\Blueprint\\BarracksOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"BrrcksO", pBrrcksBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"BrrcksX", pBrrcksBPTexture, 128, 0, 128, 96);

	// 엔지니어링 베이
	CTexture* pEngnrByBPTexture = CResourceManager::GetManager()->LoadTexture(L"EngnrByBP", L"Texture\\Multi\\Building\\Blueprint\\EngineeringBayOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"EngnrByO", pEngnrByBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"EngnrByX", pEngnrByBPTexture, 128, 0, 128, 96);

	// 아카데미
	CTexture* pAcdmyBPTexture = CResourceManager::GetManager()->LoadTexture(L"AcdmyBP", L"Texture\\Multi\\Building\\Blueprint\\AcademyOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"AcdmyO", pAcdmyBPTexture, 0, 0, 96, 64);
	CResourceManager::GetManager()->CreateSprite(L"AcdmyX", pAcdmyBPTexture, 96, 0, 96, 64);

	// 벙커
	CTexture* pBnkrBPTexture = CResourceManager::GetManager()->LoadTexture(L"BnkrBP", L"Texture\\Multi\\Building\\Blueprint\\BunkerOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"BnkrO", pBnkrBPTexture, 0, 0, 96, 64);
	CResourceManager::GetManager()->CreateSprite(L"BnkrX", pBnkrBPTexture, 96, 0, 96, 64);

	// 팩토리
	CTexture* pFctryBPTexture = CResourceManager::GetManager()->LoadTexture(L"FctryBP", L"Texture\\Multi\\Building\\Blueprint\\FactoryOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"FctryO", pFctryBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"FctryX", pFctryBPTexture, 128, 0, 128, 96);

	// 스타포트
	CTexture* pStrprtBPTexture = CResourceManager::GetManager()->LoadTexture(L"StrprtBP", L"Texture\\Multi\\Building\\Blueprint\\StarportOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"StrprtO", pStrprtBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"StrprtX", pStrprtBPTexture, 128, 0, 128, 96);

	// 사이언스 퍼실리티
	CTexture* pScncFcltyBPTexture = CResourceManager::GetManager()->LoadTexture(L"ScncFcltyBP", L"Texture\\Multi\\Building\\Blueprint\\ScienceFacilityOX.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyO", pScncFcltyBPTexture, 0, 0, 128, 96);
	CResourceManager::GetManager()->CreateSprite(L"ScncFcltyX", pScncFcltyBPTexture, 128, 0, 128, 96);

	// 아머리
	CTexture* pArmryBPTexture = CResourceManager::GetManager()->LoadTexture(L"ArmryBP", L"Texture\\Multi\\Building\\Blueprint\\ArmoryOX.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"ArmryO", pArmryBPTexture, 0, 0, 96, 64);
	CResourceManager::GetManager()->CreateSprite(L"ArmryX", pArmryBPTexture, 96, 0, 96, 64);

	// 머신샵
	CTexture* pMchnShopBPTexture = CResourceManager::GetManager()->LoadTexture(L"MchnShopBP", L"Texture\\Multi\\Building\\Blueprint\\MachineShopOX.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"MchnShopO", pMchnShopBPTexture, 0, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"MchnShopX", pMchnShopBPTexture, 64, 0, 64, 64);

	// 컨트롤 타워
	CTexture* pCntrlTwrBPTexture = CResourceManager::GetManager()->LoadTexture(L"CntrlTwrBP", L"Texture\\Multi\\Building\\Blueprint\\ControlTowerOX.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrO", pCntrlTwrBPTexture, 0, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CntrlTwrX", pCntrlTwrBPTexture, 64, 0, 64, 64);

	// 피직스 랩
	CTexture* pPhscLbBPTexture = CResourceManager::GetManager()->LoadTexture(L"PhscLbBP", L"Texture\\Multi\\Building\\Blueprint\\PhysicsLabOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"PhscLbO", pPhscLbBPTexture, 0, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"PhscLbX", pPhscLbBPTexture, 64, 0, 64, 64);

	// 코버트 옵스
	CTexture* pCvrtOpsBPTexture = CResourceManager::GetManager()->LoadTexture(L"CvrtOpsBP", L"Texture\\Multi\\Building\\Blueprint\\CovertOpsOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsO", pCvrtOpsBPTexture, 0, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"CvrtOpsX", pCvrtOpsBPTexture, 64, 0, 64, 64);

	// 뉴클리어 사일로
	CTexture* pNclrSloBPTexture = CResourceManager::GetManager()->LoadTexture(L"NclrSloBP", L"Texture\\Multi\\Building\\Blueprint\\NuclearSiloOX.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateSprite(L"NclrSloO", pNclrSloBPTexture, 0, 0, 64, 64);
	CResourceManager::GetManager()->CreateSprite(L"NclrSloX", pNclrSloBPTexture, 64, 0, 64, 64);
#pragma endregion

#pragma region Circle Selection
	CTexture* pAllySlct0 = CResourceManager::GetManager()->LoadTexture(L"AllySlct0", L"Texture\\Multi\\Select\\AllySelect\\PSelect0.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct0", pAllySlct0, 0, 0, 32, 32);

	CTexture* pAllySlct1 = CResourceManager::GetManager()->LoadTexture(L"AllySlct1", L"Texture\\Multi\\Select\\AllySelect\\PSelect1.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct1", pAllySlct1, 0, 0, 40, 40);

	CTexture* pAllySlct2 = CResourceManager::GetManager()->LoadTexture(L"AllySlct2", L"Texture\\Multi\\Select\\AllySelect\\PSelect2.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct2", pAllySlct2, 0, 0, 64, 64);

	CTexture* pAllySlct3 = CResourceManager::GetManager()->LoadTexture(L"AllySlct3", L"Texture\\Multi\\Select\\AllySelect\\PSelect3.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct3", pAllySlct3, 0, 0, 64, 64);

	CTexture* pAllySlct4 = CResourceManager::GetManager()->LoadTexture(L"AllySlct4", L"Texture\\Multi\\Select\\AllySelect\\PSelect4.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct4", pAllySlct4, 0, 0, 80, 80);

	CTexture* pAllySlct5 = CResourceManager::GetManager()->LoadTexture(L"AllySlct5", L"Texture\\Multi\\Select\\AllySelect\\PSelect5.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct5", pAllySlct5, 0, 0, 96, 96);

	CTexture* pAllySlct6 = CResourceManager::GetManager()->LoadTexture(L"AllySlct6", L"Texture\\Multi\\Select\\AllySelect\\PSelect6.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct6", pAllySlct6, 0, 0, 128, 128);

	CTexture* pAllySlct7 = CResourceManager::GetManager()->LoadTexture(L"AllySlct7", L"Texture\\Multi\\Select\\AllySelect\\PSelect7.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct7", pAllySlct7, 0, 0, 128, 128);

	CTexture* pAllySlct8 = CResourceManager::GetManager()->LoadTexture(L"AllySlct8", L"Texture\\Multi\\Select\\AllySelect\\PSelect8.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct8", pAllySlct8, 0, 0, 148, 148);

	CTexture* pAllySlct9 = CResourceManager::GetManager()->LoadTexture(L"AllySlct9", L"Texture\\Multi\\Select\\AllySelect\\PSelect9.bmp", RGB(255, 0, 0));
	CResourceManager::GetManager()->CreateSprite(L"AllySlct9", pAllySlct9, 0, 0, 224, 224);
#pragma endregion
}

void CTestScene::LoadUnitTexture()
{
#pragma region SCV
	// SCV
	CTexture* pSCVTexture = CResourceManager::GetManager()->LoadTexture(L"SCV", L"Texture\\Multi\\Unit\\SCV.bmp", RGB(0, 255, 0));
	
	// SCV 정지, 이동
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopE",  pSCVTexture, L"SCVMoveStopE", false, { 0, 0 }, { 0, 0 },		{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopNE", pSCVTexture, L"SCVMoveStopNE", false, { 0, 0 }, { 2, 2 },		{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopN",  pSCVTexture, L"SCVMoveStopN", false, { 0, 0 }, { 4, 4 },		{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopNW", pSCVTexture, L"SCVMoveStopNW", false, { 0, 0 }, { 6, 6 },		{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopW",  pSCVTexture, L"SCVMoveStopW", false, { 0, 0 }, { 8, 8 },		{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopSW", pSCVTexture, L"SCVMoveStopSW", false, { 0, 0 }, { 10, 10 },	{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopS",  pSCVTexture, L"SCVMoveStopS", false, { 0, 0 }, { 12, 12 },	{ 72, 72 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SCVMoveStopSE", pSCVTexture, L"SCVMoveStopSE", false, { 0, 0 }, { 14, 14 },	{ 72, 72 }, 1.0f, true, false);

	// SCV 건설, 공격
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckE", pSCVTexture, L"SCVBldAttckE", false,	{ 1, 2 }, { 0, 0 },		{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckNE", pSCVTexture, L"SCVBldAttckNE", false, { 1, 2 }, { 2, 2 },		{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckN", pSCVTexture, L"SCVBldAttckN", false,	{ 1, 2 }, { 4, 4 },		{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckNW", pSCVTexture, L"SCVBldAttckNW", false, { 1, 2 }, { 6, 6 },		{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckW", pSCVTexture, L"SCVBldAttckW", false,	{ 1, 2 }, { 8, 8 },		{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckSW", pSCVTexture, L"SCVBldAttckSW", false, { 1, 2 }, { 10, 10 },	{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckS", pSCVTexture, L"SCVBldAttckS", false,	{ 1, 2 }, { 12, 12 },	{ 72, 72 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"SCVBldAttckSE", pSCVTexture, L"SCVBldAttckSE", false, { 1, 2 }, { 14, 14 },	{ 72, 72 }, 0.4f, false, true);

	// SCV 공격 이펙트
	CTexture* pSCVHtingTexture = CResourceManager::GetManager()->LoadTexture(L"SCVHting", L"Texture\\Multi\\Effect\\SCVFlame.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateAnimation(L"SCVHting", pSCVHtingTexture, L"SCVHting", true, { 0, 0 }, { 0, 9 }, { 48, 48 }, 0.6f, false, true);

#pragma endregion

#pragma region Marine
	// 마린
	CTexture* pMrnTexture = CResourceManager::GetManager()->LoadTexture(L"Mrn", L"Texture\\Multi\\Unit\\Marine.bmp", RGB(255, 255, 0));

	// 마린 정지
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopE", pMrnTexture, L"MrnStopE",	 false,	{ 0, 0 }, { 0, 0 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopNE", pMrnTexture, L"MrnStopNE", false,	{ 0, 0 }, { 2, 2 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopN", pMrnTexture, L"MrnStopN",	 false,	{ 0, 0 }, { 4, 4 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopNW", pMrnTexture, L"MrnStopNW", false,	{ 0, 0 }, { 6, 6 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopW", pMrnTexture, L"MrnStopW",	 false,	{ 0, 0 }, { 8, 8 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopSW", pMrnTexture, L"MrnStopSW", false,	{ 0, 0 }, { 10, 10 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopS", pMrnTexture, L"MrnStopS",	 false,	{ 0, 0 }, { 12, 12 }, { 50, 50 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MrnStopSE", pMrnTexture, L"MrnStopSE", false,	{ 0, 0 }, { 14, 14 }, { 50, 50 }, 1.0f, true, false);
																							 
	// 마린 이동																			 
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveE", pMrnTexture, L"MrnMoveE",	 false,	{ 1, 9 }, { 0, 0 }, { 50, 50 },   0.5f,	false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveNE", pMrnTexture, L"MrnMoveNE", false,	{ 1, 9 }, { 2, 2 }, { 50, 50 },   0.5f,	false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveN", pMrnTexture, L"MrnMoveN",	 false,	{ 1, 9 }, { 4, 4 }, { 50, 50 },   0.5f,	false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveNW", pMrnTexture, L"MrnMoveNW", false,	{ 1, 9 }, { 6, 6 }, { 50, 50 },   0.5f,	false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveW", pMrnTexture, L"MrnMoveW",	 false,	{ 1, 9 }, { 8, 8 }, { 50, 50 },	  0.5f,	false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveSW", pMrnTexture, L"MrnMoveSW", false,	{ 1, 9 }, { 10, 10 }, { 50, 50 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveS", pMrnTexture, L"MrnMoveS",	 false,	{ 1, 9 }, { 12, 12 }, { 50, 50 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnMoveSE", pMrnTexture, L"MrnMoveSE", false,	{ 1, 9 }, { 14, 14 }, { 50, 50 }, 0.5f, false, true);

	// 마린 공격															 
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckE",  pMrnTexture,  L"MrnAttckE", false, { 13, 14 }, { 0, 0 },   { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckNE", pMrnTexture, L"MrnAttckNE", false, { 13, 14 }, { 2, 2 },   { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckN",  pMrnTexture,  L"MrnAttckN", false, { 13, 14 }, { 4, 4 },   { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckNW", pMrnTexture, L"MrnAttckNW", false, { 13, 14 }, { 6, 6 },   { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckW",  pMrnTexture,  L"MrnAttckW", false, { 13, 14 }, { 8, 8 },   { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckSW", pMrnTexture, L"MrnAttckSW", false, { 13, 14 }, { 10, 10 }, { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckS",  pMrnTexture,  L"MrnAttckS", false, { 13, 14 }, { 12, 12 }, { 50, 50 }, 0.1f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MrnAttckSE", pMrnTexture, L"MrnAttckSE", false, { 13, 14 }, { 14, 14 }, { 50, 50 }, 0.1f, false, true);

	// 마린 사망																			 
	CResourceManager::GetManager()->CreateAnimation(L"MrnDie", pMrnTexture, L"MrnDie", false, { 0, 6 }, { 16, 16 }, { 100, 50 }, 0.7f, true, false);

	// 마린 피격 이펙트
	CTexture* pMrnHitTexture = CResourceManager::GetManager()->LoadTexture(L"MrnHit", L"Texture\\Multi\\Effect\\MarineHitSpark.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateAnimation(L"MrnHit", pMrnHitTexture, L"MrnHit", true, { 0, 0 }, { 0, 13 }, { 40, 40 }, 0.8f, true, false);
#pragma endregion

#pragma region Firebat
	// 파이어뱃
	CTexture* pFrbtTexture = CResourceManager::GetManager()->LoadTexture(L"Frbt", L"Texture\\Multi\\Unit\\Firebat.bmp", RGB(0, 255, 0));

	// 파이어뱃 정지
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopE",  pFrbtTexture, L"FrbtStopE", false,  { 1, 1 }, { 0, 0 },  { 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopNE", pFrbtTexture, L"FrbtStopNE", false, { 1, 1 }, { 2, 2 },  { 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopN",  pFrbtTexture, L"FrbtStopN", false,  { 1, 1 }, { 4, 4 },  { 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopNW", pFrbtTexture, L"FrbtStopNW", false, { 1, 1 }, { 6, 6 },  { 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopW",  pFrbtTexture, L"FrbtStopW", false,  { 1, 1 }, { 8, 8 },  { 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopSW", pFrbtTexture, L"FrbtStopSW", false, { 1, 1 }, { 10, 10 },{ 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopS",  pFrbtTexture, L"FrbtStopS", false,  { 1, 1 }, { 12, 12 },{ 32, 32 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtStopSE", pFrbtTexture, L"FrbtStopSE", false, { 1, 1 }, { 14, 14 },{ 32, 32 }, 1.0f, true, false);

	// 파이어뱃 이동																			 
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveE",  pFrbtTexture, L"FrbtMoveE", false,	{ 0, 7 }, { 0, 0 },  { 32, 32 },  0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveNE", pFrbtTexture, L"FrbtMoveNE", false,	{ 0, 7 }, { 2, 2 }, { 32, 32 },   0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveN", pFrbtTexture, L"FrbtMoveN", false,	{ 0, 7 }, { 4, 4 }, { 32, 32 },   0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveNW", pFrbtTexture, L"FrbtMoveNW", false,	{ 0, 7 }, { 6, 6 }, { 32, 32 },   0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveW", pFrbtTexture, L"FrbtMoveW", false,	{ 0, 7 }, { 8, 8 }, { 32, 32 },   0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveSW", pFrbtTexture, L"FrbtMoveSW", false,	{ 0, 7 }, { 10, 10 }, { 32, 32 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveS", pFrbtTexture, L"FrbtMoveS", false,	{ 0, 7 }, { 12, 12 }, { 32, 32 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtMoveSE", pFrbtTexture, L"FrbtMoveSE", false,	{ 0, 7 }, { 14, 14 }, { 32, 32 }, 0.5f, false, true);

	// 파이어뱃 공격
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckE",  pFrbtTexture, L"FrbtAttckE", false,  { 8, 9 }, { 0, 0 },  { 32, 32 },  0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckNE", pFrbtTexture, L"FrbtAttckNE", false, { 8, 9 }, { 2, 2 }, { 32, 32 },   0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckN",  pFrbtTexture, L"FrbtAttckN", false,  { 8, 9 }, { 4, 4 }, { 32, 32 },   0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckNW", pFrbtTexture, L"FrbtAttckNW", false, { 8, 9 }, { 6, 6 }, { 32, 32 },   0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckW",  pFrbtTexture, L"FrbtAttckW", false,  { 8, 9 }, { 8, 8 }, { 32, 32 },   0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckSW", pFrbtTexture, L"FrbtAttckSW", false, { 8, 9 }, { 10, 10 }, { 32, 32 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckS",  pFrbtTexture, L"FrbtAttckS", false,  { 8, 9 }, { 12, 12 }, { 32, 32 }, 0.4f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtAttckSE", pFrbtTexture, L"FrbtAttckSE", false, { 8, 9 }, { 14, 14 }, { 32, 32 }, 0.4f, false, true);

	// 파이어뱃 사망
	// Machine Explosion으로 대체합니다.

	// 파이어뱃 공격 이펙트
	CTexture* pFrbtHtingTexture = CResourceManager::GetManager()->LoadTexture(L"FrbtHting", L"Texture\\Multi\\Effect\\FirebatFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngE",  pFrbtHtingTexture, L"FrbtHitngE",	false, { 0, 4 }, {  0,  0 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngNE", pFrbtHtingTexture, L"FrbtHitngNE",	false, { 0, 4 }, {  4,  4 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngN",  pFrbtHtingTexture, L"FrbtHitngN",	false, { 0, 4 }, {  8,  8 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngNW", pFrbtHtingTexture, L"FrbtHitngNW",	false, { 0, 4 }, { 12, 12 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngW",  pFrbtHtingTexture, L"FrbtHitngW",	false, { 0, 4 }, { 16, 16 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngSW", pFrbtHtingTexture, L"FrbtHitngSW",	false, { 0, 4 }, { 20, 20 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngS",  pFrbtHtingTexture, L"FrbtHitngS",	false, { 0, 4 }, { 24, 24 }, { 224, 224 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FrbtHitngSE", pFrbtHtingTexture, L"FrbtHitngSE",	false, { 0, 4 }, { 28, 28 }, { 224, 224 }, 0.3f, true, false);
#pragma endregion

#pragma region Medic
	// 메딕
	CTexture* pMdcTexture = CResourceManager::GetManager()->LoadTexture(L"Mdc", L"Texture\\Multi\\Unit\\Medic.bmp", RGB(255, 0, 255));

	// 메딕 정지
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopE",  pMdcTexture, L"MdcStopE", false,	{ 0, 0 }, { 0, 0 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopNE", pMdcTexture, L"MdcStopNE", false, { 0, 0 }, { 2, 2 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopN",  pMdcTexture, L"MdcStopN", false,	{ 0, 0 }, { 4, 4 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopNW", pMdcTexture, L"MdcStopNW", false, { 0, 0 }, { 6, 6 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopW",  pMdcTexture, L"MdcStopW", false,	{ 0, 0 }, { 8, 8 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopSW", pMdcTexture, L"MdcStopSW", false, { 0, 0 }, { 10, 10 }, { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopS",  pMdcTexture, L"MdcStopS", false,	{ 0, 0 }, { 12, 12 }, { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MdcStopSE", pMdcTexture, L"MdcStopSE", false, { 0, 0 }, { 14, 14 }, { 64, 64 }, 1.0f, true, false);

	// 메딕 이동																			 
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveE",  pMdcTexture, L"MdcMoveE", false,	{ 1, 6 }, { 0, 0 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveNE", pMdcTexture, L"MdcMoveNE", false, { 1, 6 }, { 2, 2 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveN",  pMdcTexture, L"MdcMoveN", false,	{ 1, 6 }, { 4, 4 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveNW", pMdcTexture, L"MdcMoveNW", false, { 1, 6 }, { 6, 6 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveW",  pMdcTexture, L"MdcMoveW", false,	{ 1, 6 }, { 8, 8 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveSW", pMdcTexture, L"MdcMoveSW", false, { 1, 6 }, { 10, 10 }, { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveS",  pMdcTexture, L"MdcMoveS", false,	{ 1, 6 }, { 12, 12 }, { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcMoveSE", pMdcTexture, L"MdcMoveSE", false, { 1, 6 }, { 14, 14 }, { 64, 64 }, 0.5f, false, true);

	// 메딕 힐
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealE",  pMdcTexture, L"MdcHealE", false,  { 9, 10 }, { 0, 0 },   { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealNE", pMdcTexture, L"MdcHealNE", false, { 9, 10 }, { 2, 2 },   { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealN",  pMdcTexture, L"MdcHealN", false,  { 9, 10 }, { 4, 4 },   { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealNW", pMdcTexture, L"MdcHealNW", false, { 9, 10 }, { 6, 6 },   { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealW",  pMdcTexture, L"MdcHealW", false,  { 9, 10 }, { 8, 8 },   { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealSW", pMdcTexture, L"MdcHealSW", false, { 9, 10 }, { 10, 10 }, { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealS",  pMdcTexture, L"MdcHealS", false,  { 9, 10 }, { 12, 12 }, { 64, 64 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"MdcHealSE", pMdcTexture, L"MdcHealSE", false, { 9, 10 }, { 14, 14 }, { 64, 64 }, 0.3f, false, true);

	// 메딕 사망																			 
	CResourceManager::GetManager()->CreateAnimation(L"MdcDie", pMdcTexture, L"MdcDie", false, { 0, 5 }, { 16, 16 }, { 64, 64 }, 0.7f, true, false);
#pragma endregion

#pragma region Ghost
	// 고스트
	CTexture* pGhstTexture = CResourceManager::GetManager()->LoadTexture(L"Ghst", L"Texture\\Multi\\Unit\\Ghost.bmp", RGB(0, 255, 0));
	
	// 고스트 정지
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopE",  pGhstTexture,  L"GhstStopE", false, { 0, 0 }, { 0, 0 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopNE", pGhstTexture, L"GhstStopNE", false, { 0, 0 }, { 2, 2 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopN",  pGhstTexture,  L"GhstStopN", false, { 0, 0 }, { 4, 4 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopNW", pGhstTexture, L"GhstStopNW", false, { 0, 0 }, { 6, 6 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopW",  pGhstTexture,  L"GhstStopW", false, { 0, 0 }, { 8, 8 },   { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopSW", pGhstTexture, L"GhstStopSW", false, { 0, 0 }, { 10, 10 }, { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopS",  pGhstTexture,  L"GhstStopS", false, { 0, 0 }, { 12, 12 }, { 64, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstStopSE", pGhstTexture, L"GhstStopSE", false, { 0, 0 }, { 14, 14 }, { 64, 64 }, 1.0f, true, false);

	// 고스트 이동																			 
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveE",  pGhstTexture,  L"GhstMoveE", false, { 1, 8 }, { 0, 0 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveNE", pGhstTexture, L"GhstMoveNE", false, { 1, 8 }, { 2, 2 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveN",  pGhstTexture,  L"GhstMoveN", false, { 1, 8 }, { 4, 4 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveNW", pGhstTexture, L"GhstMoveNW", false, { 1, 8 }, { 6, 6 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveW",  pGhstTexture,  L"GhstMoveW", false, { 1, 8 }, { 8, 8 },   { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveSW", pGhstTexture, L"GhstMoveSW", false, { 1, 8 }, { 10, 10 }, { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveS",  pGhstTexture,  L"GhstMoveS", false, { 1, 8 }, { 12, 12 }, { 64, 64 }, 0.5f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"GhstMoveSE", pGhstTexture, L"GhstMoveSE", false, { 1, 8 }, { 14, 14 }, { 64, 64 }, 0.5f, false, true);

	// 고스트 공격															 
	CTexture* pGhstAtckTexture = CResourceManager::GetManager()->LoadTexture(L"GhstAtck", L"Texture\\Multi\\Unit\\GhostAttack.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckE",  pGhstAtckTexture, L"GhstAttckE",  false, { 0, 1 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckNE", pGhstAtckTexture, L"GhstAttckNE", false, { 2, 3 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckN",  pGhstAtckTexture, L"GhstAttckN",  false, { 4, 5 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckNW", pGhstAtckTexture, L"GhstAttckNW", false, { 6, 7 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckW",  pGhstAtckTexture, L"GhstAttckW",  false, { 8, 9 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckSW", pGhstAtckTexture, L"GhstAttckSW", false, { 10, 11 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckS",  pGhstAtckTexture, L"GhstAttckS",  false, { 12, 13 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstAttckSE", pGhstAtckTexture, L"GhstAttckSE", false, { 14, 15 }, { 0, 0 }, { 64, 64 }, 0.3f, true, false);

	// 고스트 핵 공격
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkE",  pGhstTexture, L"GhstNclrStrkE",  false, { 9, 11 }, { 0, 0 },   { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkNE", pGhstTexture, L"GhstNclrStrkNE", false, { 9, 11 }, { 2, 2 },   { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkN",  pGhstTexture, L"GhstNclrStrkN",  false, { 9, 11 }, { 4, 4 },   { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkNW", pGhstTexture, L"GhstNclrStrkNW", false, { 9, 11 }, { 6, 6 },   { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkW",  pGhstTexture, L"GhstNclrStrkW",  false, { 9, 11 }, { 8, 8 },   { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkSW", pGhstTexture, L"GhstNclrStrkSW", false, { 9, 11 }, { 10, 10 }, { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkS",  pGhstTexture, L"GhstNclrStrkS",  false, { 9, 11 }, { 12, 12 }, { 64, 64 }, 0.4f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"GhstNclrStrkSE", pGhstTexture, L"GhstNclrStrkSE", false, { 9, 11 }, { 14, 14 }, { 64, 64 }, 0.4f, true, false);

	// 고스트 사망																			 
	CResourceManager::GetManager()->CreateAnimation(L"GhstDie", pGhstTexture, L"GhstDie", false, { 0, 8 }, { 16, 16 }, { 64, 64 }, 0.7f, true, false);

	// 핵 투사체
	CTexture* pNclrPrjtlTexture = CResourceManager::GetManager()->LoadTexture(L"NclrPrjtl", L"Texture\\Multi\\Bullet\\NukeBullet.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"NclrPrjtl", pNclrPrjtlTexture, L"NclrPrjtl", false, { 1, 1 }, { 0, 0 }, { 48, 40 }, 1.0f, true, false);

	// 핵 공격
	CTexture* pNclrFlameTexture = CResourceManager::GetManager()->LoadTexture(L"NclrFlame", L"Texture\\Multi\\Effect\\NuclearHitFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"NclrFlame", pNclrFlameTexture, L"NclrFlame", true, { 0, 0 }, { 0, 25 }, { 252, 252 }, 3.0f, true, false);
#pragma endregion

#pragma region Vulture
	// 벌쳐
	CTexture* pVltrTexture = CResourceManager::GetManager()->LoadTexture(L"Vltr", L"Texture\\Multi\\Unit\\Vulture.bmp", RGB(255, 0, 255));

	// 벌쳐 정지, 이동, 공격
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkE", pVltrTexture,  L"VltrStpMvAttkE",  false, { 0, 0 }, { 0, 0 },   { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkNE", pVltrTexture, L"VltrStpMvAttkNE", false, { 0, 0 }, { 2, 2 },   { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkN", pVltrTexture,  L"VltrStpMvAttkN",  false, { 0, 0 }, { 4, 4 },   { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkNW", pVltrTexture, L"VltrStpMvAttkNW", false, { 0, 0 }, { 6, 6 },   { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkW", pVltrTexture,  L"VltrStpMvAttkW",  false, { 0, 0 }, { 8, 8 },   { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkSW", pVltrTexture, L"VltrStpMvAttkSW", false, { 0, 0 }, { 10, 10 }, { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkS", pVltrTexture,  L"VltrStpMvAttkS",  false, { 0, 0 }, { 12, 12 }, { 100, 100 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrStpMvAttkSE", pVltrTexture, L"VltrStpMvAttkSE", false, { 0, 0 }, { 14, 14 }, { 100, 100 }, 1.0f, true, false);

	// 벌쳐 피격 이펙트
	CTexture* pVltrHtedTexture = CResourceManager::GetManager()->LoadTexture(L"VltrHted", L"Texture\\Multi\\Effect\\VultureHitFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"VltrHted", pVltrHtedTexture, L"VltrHted", true, { 0, 0 }, { 0, 9 }, { 40, 40 }, 0.5f, true, false);

	// 벌쳐 공격 이펙트
	CTexture* pVltrHtngTexture = CResourceManager::GetManager()->LoadTexture(L"VltrHtng", L"Texture\\Multi\\Effect\\VultureFlame.bmp", RGB(0, 0, 0));
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngE",  pVltrHtngTexture, L"VltrHtngE",  true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngNE", pVltrHtngTexture, L"VltrHtngNE", true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngN",  pVltrHtngTexture, L"VltrHtngN",  true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngNW", pVltrHtngTexture, L"VltrHtngNW", true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngW",  pVltrHtngTexture, L"VltrHtngW",  true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngSW", pVltrHtngTexture, L"VltrHtngSW", true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngS",  pVltrHtngTexture, L"VltrHtngS",  true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"VltrHtngSE", pVltrHtngTexture, L"VltrHtngSE", true, { 0, 0 }, { 0, 7 }, { 64, 64 }, 0.5f, true, false);

	// 벌쳐 사망
	// BangS로 대체합니다.

	//벌쳐 투사체
	CTexture* ppVltrPrjctlTexture = CResourceManager::GetManager()->LoadTexture(L"pVltrPrjctl", L"Texture\\Multi\\Bullet\\VultureBullet.bmp", RGB(0, 0, 0));
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlE",  ppVltrPrjctlTexture, L"VltrPrjctlE",  true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlNE", ppVltrPrjctlTexture, L"VltrPrjctlNE", true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlN",  ppVltrPrjctlTexture, L"VltrPrjctlN",  true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlNW", ppVltrPrjctlTexture, L"VltrPrjctlNW", true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlW",  ppVltrPrjctlTexture, L"VltrPrjctlW",  true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlSW", ppVltrPrjctlTexture, L"VltrPrjctlSW", true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlS",  ppVltrPrjctlTexture, L"VltrPrjctlS",  true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"VltrPrjctlSE", ppVltrPrjctlTexture, L"VltrPrjctlSE", true, { 0, 0 }, { 3, 3 }, { 16, 16 }, 0.2f, false, true);

#pragma endregion

#pragma region Siege Tank
	// 탱크 몸체
	CTexture* pTnkBdyTexture = CResourceManager::GetManager()->LoadTexture(L"Tnk", L"Texture\\Multi\\Unit\\TankBody.bmp", RGB(0, 255, 0));
	
	// 탱크 포신
	CTexture* pTnkHdTexture = CResourceManager::GetManager()->LoadTexture(L"TnkBrl", L"Texture\\Multi\\Unit\\TankHead.bmp", RGB(0, 255, 0));

	/*********************************************************************************************************************************************************************/

	// 탱크 몸체 전환
	CTexture* pTnkBdyTransTexture = CResourceManager::GetManager()->LoadTexture(L"TnkBdyTrans", L"Texture\\Multi\\Unit\\TankBodyTrans.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdySgMding", pTnkBdyTransTexture, L"TnkBdySgMding", false, { 0, 5 }, { 0, 0 }, { 128, 128 }, 1.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyTnkMding", pTnkBdyTransTexture, L"TnkBdyTnkMding", false, { 6, 11 }, { 0, 0 }, { 128, 128 }, 1.2f, true, false);

	// 탱크 포신 전환
	CTexture* pTnkHdTransTexture = CResourceManager::GetManager()->LoadTexture(L"TnkBrlTrans", L"Texture\\Multi\\Unit\\TankHeadTrans.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdSgMding", pTnkHdTransTexture, L"TnkHdSgMding", false, { 0, 4 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdTnkMding", pTnkHdTransTexture, L"TnkHdTnkMding", false, { 5, 9 }, { 0, 0 }, { 128, 128 }, 0.8f, true, false);

	/*********************************************************************************************************************************************************************/

	// 탱크 몸체 정지
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopE", pTnkBdyTexture,	L"TnkBdyStopE",	false, { 0, 0 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopNE", pTnkBdyTexture,L"TnkBdyStopNE",false, { 0, 0 }, { 2, 2 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopN", pTnkBdyTexture,	L"TnkBdyStopN",	false, { 0, 0 }, { 4, 4 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopNW", pTnkBdyTexture,L"TnkBdyStopNW",false, { 0, 0 }, { 6, 6 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopW", pTnkBdyTexture,	L"TnkBdyStopW",	false, { 0, 0 }, { 8, 8 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopSW", pTnkBdyTexture,L"TnkBdyStopSW",false, { 0, 0 }, { 10, 10 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopS", pTnkBdyTexture,	L"TnkBdyStopS",	false, { 0, 0 }, { 12, 12 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyStopSE", pTnkBdyTexture,L"TnkBdyStopSE",false, { 0, 0 }, { 14, 14 }, { 128, 128 }, 1.0f, true, false);

	// 탱크 몸체 이동
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveE", pTnkBdyTexture,	L"TnkBdyMoveE",	false, { 0, 2 }, { 0, 0 },		{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveNE", pTnkBdyTexture,L"TnkBdyMoveNE",false, { 0, 2 }, { 2, 2 },		{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveN", pTnkBdyTexture,	L"TnkBdyMoveN",	false, { 0, 2 }, { 4, 4 },		{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveNW", pTnkBdyTexture,L"TnkBdyMoveNW",false, { 0, 2 }, { 6, 6 },		{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveW", pTnkBdyTexture,	L"TnkBdyMoveW",	false, { 0, 2 }, { 8, 8 },		{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveSW", pTnkBdyTexture,L"TnkBdyMoveSW",false, { 0, 2 }, { 10, 10 },	{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveS", pTnkBdyTexture,	L"TnkBdyMoveS",	false, { 0, 2 }, { 12, 12 },	{ 128, 128 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"TnkBdyMoveSE", pTnkBdyTexture,L"TnkBdyMoveSE",false, { 0, 2 }, { 14, 14 },	{ 128, 128 }, 0.2f, false, true);

	// 탱크 포신 정지, 회전
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotE",  pTnkHdTexture, L"TnkHdStopRotE",  false, { 0, 0 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotNE", pTnkHdTexture, L"TnkHdStopRotNE", false, { 0, 0 }, { 2, 2 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotN",  pTnkHdTexture, L"TnkHdStopRotN",  false, { 0, 0 }, { 4, 4 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotNW", pTnkHdTexture, L"TnkHdStopRotNW", false, { 0, 0 }, { 6, 6 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotW",  pTnkHdTexture, L"TnkHdStopRotW",  false, { 0, 0 }, { 8, 8 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotSW", pTnkHdTexture, L"TnkHdStopRotSW", false, { 0, 0 }, { 10, 10 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotS",  pTnkHdTexture, L"TnkHdStopRotS",  false, { 0, 0 }, { 12, 12 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdStopRotSE", pTnkHdTexture, L"TnkHdStopRotSE", false, { 0, 0 }, { 14, 14 }, { 128, 128 }, 1.0f, true, false);

	// 탱크 몸체 사망
	// BangM으로 대체합니다.

	// 탱크 포신 사망
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdDie", pTnkHdTexture, L"TnkHdDie", false, { 3, 3 }, { 5, 5 }, { 128, 128 }, 0.4f, true, false);

	/*********************************************************************************************************************************************************************/

	// 시즈 탱크 몸체 정지
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopE",  pTnkBdyTransTexture, L"SgTnkBdyStopE",  false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopNE", pTnkBdyTransTexture, L"SgTnkBdyStopNE", false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopN",  pTnkBdyTransTexture, L"SgTnkBdyStopN",  false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopNW", pTnkBdyTransTexture, L"SgTnkBdyStopNW", false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopW",  pTnkBdyTransTexture, L"SgTnkBdyStopW",  false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopSW", pTnkBdyTransTexture, L"SgTnkBdyStopSW", false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopS",  pTnkBdyTransTexture, L"SgTnkBdyStopS",  false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkBdyStopSE", pTnkBdyTransTexture, L"SgTnkBdyStopSE", false, { 5, 5 }, { 0, 0 }, { 128, 128 }, 1.0f, true, false);

	// 시즈 탱크 포신 정지, 회전
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotE",  pTnkHdTexture, L"SgTnkHdStpRotE",  false, { 2, 2 }, {  0,  0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotNE", pTnkHdTexture, L"SgTnkHdStpRotNE", false, { 2, 2 }, {  2,  2 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotN",  pTnkHdTexture, L"SgTnkHdStpRotN",  false, { 2, 2 }, {  4,  4 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotNW", pTnkHdTexture, L"SgTnkHdStpRotNW", false, { 2, 2 }, {  6,  6 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotW",  pTnkHdTexture, L"SgTnkHdStpRotW",  false, { 2, 2 }, {  8,  8 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotSW", pTnkHdTexture, L"SgTnkHdStpRotSW", false, { 2, 2 }, { 10, 10 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotS",  pTnkHdTexture, L"SgTnkHdStpRotS",  false, { 2, 2 }, { 12, 12 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdStpRotSE", pTnkHdTexture, L"SgTnkHdStpRotSE", false, { 2, 2 }, { 14, 14 }, { 128, 128 }, 1.0f, true, false);

	/*********************************************************************************************************************************************************************/

	
	// 탱크 포신 공격
	CTexture* pTnkHdHtngTexture = CResourceManager::GetManager()->LoadTexture(L"TnkHdHtng", L"Texture\\Multi\\Effect\\TankFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngN",  pTnkHdHtngTexture, L"TnkHdHtngN",  false, { 0, 1 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngNE", pTnkHdHtngTexture, L"TnkHdHtngNE", false, { 2, 3 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngE",  pTnkHdHtngTexture, L"TnkHdHtngE",  false, { 4, 5 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngSE", pTnkHdHtngTexture, L"TnkHdHtngSE", false, { 6, 7 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngS",  pTnkHdHtngTexture, L"TnkHdHtngS",  false, { 8, 9 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngSW", pTnkHdHtngTexture, L"TnkHdHtngSW", false, { 10, 11 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngW",  pTnkHdHtngTexture, L"TnkHdHtngW",  false, { 12, 13 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHtngNW", pTnkHdHtngTexture, L"TnkHdHtngNW", false, { 14, 15 }, { 0, 0 }, { 128, 128 }, 0.2f, true, false);
	
	// 탱크 포신 피격
	CTexture* pTnkHdHtedTexture = CResourceManager::GetManager()->LoadTexture(L"TnkHdHted", L"Texture\\Multi\\Effect\\TankHitFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"TnkHdHted", pTnkHdHtedTexture, L"TnkHdHted",  false, { 0, 12 }, { 0, 0 }, { 44, 44 }, 0.3f, true, false);
	
	// 시즈 탱크 포신 공격
	CTexture* pSgTnkHdHtngTexture = CResourceManager::GetManager()->LoadTexture(L"SgTnkHdHtng", L"Texture\\Multi\\Effect\\SiegeTankFlame2.bmp", RGB(88, 88, 88));
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngE",  pSgTnkHdHtngTexture, L"SgTnkHdHtngE",  false, { 0, 6 }, {  0,  0 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngNE", pSgTnkHdHtngTexture, L"SgTnkHdHtngNE", false, { 0, 6 }, {  2,  2 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngN",  pSgTnkHdHtngTexture, L"SgTnkHdHtngN",  false, { 0, 6 }, {  5,  5 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngNW", pSgTnkHdHtngTexture, L"SgTnkHdHtngNW", false, { 0, 6 }, {  8,  8 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngW",  pSgTnkHdHtngTexture, L"SgTnkHdHtngW",  false, { 0, 6 }, { 10, 10 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngSW", pSgTnkHdHtngTexture, L"SgTnkHdHtngSW", false, { 0, 6 }, { 13, 13 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngS",  pSgTnkHdHtngTexture, L"SgTnkHdHtngS",  false, { 0, 6 }, { 15, 15 }, { 72, 72 }, 0.8f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHtngSE", pSgTnkHdHtngTexture, L"SgTnkHdHtngSE", false, { 0, 6 }, { 17, 17 }, { 72, 72 }, 0.8f, true, false);

	// 시즈 탱크 포신 피격
	CTexture* pSgTnkHdHtedTexture = CResourceManager::GetManager()->LoadTexture(L"SgTnkHdHted", L"Texture\\Multi\\Effect\\SiegeTankHitFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"SgTnkHdHted", pSgTnkHdHtedTexture, L"SgTnkHdHted", false, { 0, 13 }, { 0, 0 }, { 100, 108 }, 0.6f, true, false);

#pragma endregion

#pragma region Science Vessel
	// 사이언스 배슬 몸체
	CTexture* pScncVslTexture = CResourceManager::GetManager()->LoadTexture(L"ScncVsl", L"Texture\\Multi\\Unit\\ScienceVessel.bmp", RGB(0, 255, 0));

	// 사이언스 배슬 몸체 정지, 이동, 공격
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckE",  pScncVslTexture, L"ScncVslStpMvAtckE",  false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckNE", pScncVslTexture, L"ScncVslStpMvAtckNE", false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckN",  pScncVslTexture, L"ScncVslStpMvAtckN",  false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckNW", pScncVslTexture, L"ScncVslStpMvAtckNW", false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckW",  pScncVslTexture, L"ScncVslStpMvAtckW",  false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckSW", pScncVslTexture, L"ScncVslStpMvAtckSW", false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckS",  pScncVslTexture, L"ScncVslStpMvAtckS",  false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncVslStpMvAtckSE", pScncVslTexture, L"ScncVslStpMvAtckSE", false, { 0, 0 }, { 0, 0 }, { 96, 96 }, 1.0f, true, false);

	// 사이언스 배슬 안테나
	CTexture* pScncVslHdTexture = CResourceManager::GetManager()->LoadTexture(L"ScncVslHd", L"Texture\\Multi\\Unit\\ScienceVesselHead.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdE",  pScncVslHdTexture, 0, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdNE", pScncVslHdTexture, 100, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdN",  pScncVslHdTexture, 200, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdNW", pScncVslHdTexture, 300, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdW",  pScncVslHdTexture, 400, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdSW", pScncVslHdTexture, 500, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdS",  pScncVslHdTexture, 600, 0, 100, 100);
	CResourceManager::GetManager()->CreateSprite(L"ScncVslHdSE", pScncVslHdTexture, 700, 0, 100, 100);
#pragma endregion

#pragma region Battlecruiser
	// 배틀쿠르저
	CTexture* pBtlcrsrTexture = CResourceManager::GetManager()->LoadTexture(L"Btlcrsr", L"Texture\\Multi\\Unit\\Battlecruiser.bmp", RGB(0, 255, 0));

	// 배틀쿠르저 정지, 이동, 공격
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckE",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckE",	false,	{ 0, 0 }, { 0, 0 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckNE", pBtlcrsrTexture, L"BtlcrsrStpMvAtckNE",	false,	{ 0, 0 }, { 4, 4 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckN",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckN",	false,	{ 0, 0 }, { 8, 8 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckNW", pBtlcrsrTexture, L"BtlcrsrStpMvAtckNW",	false,	{ 0, 0 }, { 12, 12 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckW",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckW",	false,	{ 0, 0 }, { 16, 16 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckSW", pBtlcrsrTexture, L"BtlcrsrStpMvAtckSW",	false,	{ 0, 0 }, { 20, 20 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckS",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckS",	false,	{ 0, 0 }, { 24, 24 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrStpMvAtckSE", pBtlcrsrTexture, L"BtlcrsrStpMvAtckSE",	false,	{ 0, 0 }, { 28, 28 }, { 120, 120 }, 1.0f, true, false);

	// 배틀쿠르저 그림자 정지, 이동, 공격
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckE",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckE",	false,	{ 1, 1 }, { 0, 0 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckNE", pBtlcrsrTexture, L"BtlcrsrStpMvAtckNE",	false,	{ 1, 1 }, { 4, 4 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckN",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckN",	false,	{ 1, 1 }, { 8, 8 },   { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckNW", pBtlcrsrTexture, L"BtlcrsrStpMvAtckNW",	false,	{ 1, 1 }, { 12, 12 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckW",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckW",	false,	{ 1, 1 }, { 16, 16 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckSW", pBtlcrsrTexture, L"BtlcrsrStpMvAtckSW",	false,	{ 1, 1 }, { 20, 20 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckS",  pBtlcrsrTexture, L"BtlcrsrStpMvAtckS",	false,	{ 1, 1 }, { 24, 24 }, { 120, 120 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrSdwStpMvAtckSE", pBtlcrsrTexture, L"BtlcrsrStpMvAtckSE",	false,	{ 1, 1 }, { 28, 28 }, { 120, 120 }, 1.0f, true, false);

	// 배틀쿠르저 사망
	// BandL로 대체합니다.

	// 배틀쿠르저 투사체 이동
	CTexture* pBtlcrsrPrjctlTexture = CResourceManager::GetManager()->LoadTexture(L"BtlcrsrPrjctl", L"Texture\\Multi\\Bullet\\BtlcrsrBullet.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlW",  pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlW",  true, { 0, 0 }, {  0,  0 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlSW", pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlSW", true, { 0, 0 }, {  4,  4 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlS",  pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlS",  true, { 0, 0 }, {  8,  8 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlSE", pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlSE", true, { 0, 0 }, { 12, 12 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlE",  pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlE",  true, { 0, 0 }, { 16, 16 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlNE", pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlNE", true, { 0, 0 }, { 20, 20 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlN",  pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlN",  true, { 0, 0 }, { 24, 24 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlNW", pBtlcrsrPrjctlTexture, L"BtlcrsrPrjctlNW", true, { 0, 0 }, { 28, 28 }, { 128, 128 }, 1.0f, true, false);

	// 배틀쿠르저 투사체 정지
	CTexture* pBtlcrsrPrjctlStpTexture = CResourceManager::GetManager()->LoadTexture(L"BtlcrsrPrjctlStp", L"Texture\\Multi\\Effect\\VultureHitFlame.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrPrjctlStp", pBtlcrsrPrjctlStpTexture, L"BtlcrsrPrjctlStp", true, { 0, 0 }, { 0, 9 }, { 40, 40 }, 0.5f, true, false);

	// 배틀쿠르저 야마토포 이동
	CTexture* pBtlcrsrYmtTexture = CResourceManager::GetManager()->LoadTexture(L"BtlcrsrYmt", L"Texture\\Multi\\Bullet\\BtlcrsrYamato.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtE",  pBtlcrsrYmtTexture, L"BtlcrsrYmtE",  true, { 0, 0 }, {  0,  0 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtNE", pBtlcrsrYmtTexture, L"BtlcrsrYmtNE", true, { 0, 0 }, {  4,  4 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtN",  pBtlcrsrYmtTexture, L"BtlcrsrYmtN",  true, { 0, 0 }, {  8,  8 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtNW", pBtlcrsrYmtTexture, L"BtlcrsrYmtNW", true, { 0, 0 }, { 12, 12 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtW",  pBtlcrsrYmtTexture, L"BtlcrsrYmtW",  true, { 0, 0 }, { 16, 16 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtSW", pBtlcrsrYmtTexture, L"BtlcrsrYmtSW", true, { 0, 0 }, { 20, 20 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtS",  pBtlcrsrYmtTexture, L"BtlcrsrYmtS",  true, { 0, 0 }, { 24, 24 }, { 96, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BtlcrsrYmtSE", pBtlcrsrYmtTexture, L"BtlcrsrYmtSE", true, { 0, 0 }, { 28, 28 }, { 96, 96 }, 1.0f, true, false);
#pragma endregion
}

void CTestScene::LoadBuildingTexture()
{
#pragma region Command Center
	// 커맨드 센터
	CTexture* pCmdCntrTexture = CResourceManager::GetManager()->LoadTexture(L"CmdCntr", L"Texture\\Multi\\Building\\CommandCenter.bmp", RGB(0, 255, 0));
	CTexture* pCmdCntrCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"CmdCntrCnstrctn", L"Texture\\Multi\\Building\\CommandCenterConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"CmdCntrCnstrctn", pCmdCntrCnstrctnTexture, L"CmdCntrCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CmdCntrLnd", pCmdCntrTexture, L"CmdCntrLnd", true, { 0, 0 }, { 1, 1 }, { 128, 160 }, 1.0f, true, false);
#pragma endregion

#pragma region Barracks
	// 배럭
	CTexture* pBrrcksTexture = CResourceManager::GetManager()->LoadTexture(L"Brrcks", L"Texture\\Multi\\Building\\Barracks.bmp", RGB(0, 255, 0));
	CTexture* pBrrcksCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"BrrcksCnstrctn", L"Texture\\Multi\\Building\\BarracksConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"BrrcksCnstrctn", pBrrcksCnstrctnTexture, L"BrrcksCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BrrcksPrdc", pBrrcksTexture, L"BrrcksPrdc", true, { 0, 0 }, { 1, 2 }, { 192, 160 }, 0.2f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"BrrcksLnd", pBrrcksTexture, L"BrrcksLnd", true, { 0, 0 }, { 0, 0 }, { 192, 160 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BrrcksLnding", pBrrcksTexture, L"BrrcksLnding", true, { 0, 0 }, { 3, 5 }, { 192, 160 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BrrcksLft", pBrrcksTexture, L"BrrcksLft", true, { 0, 0 }, { 5, 5 }, { 192, 160 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"BrrcksLfting", pBrrcksTexture, L"BrrcksLfting", true, { 0, 0 }, { 6, 8 }, { 192, 160 }, 1.0f, true, false);

#pragma endregion

#pragma region Supply Depot
	// 서플라이 디포
	CTexture* pSplyDptTexture = CResourceManager::GetManager()->LoadTexture(L"SplyDpt", L"Texture\\Multi\\Building\\SupplyDepot.bmp", RGB(0, 255, 0));
	CTexture* pSplyDptCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"SplyDptCnstrctn", L"Texture\\Multi\\Building\\SupplyDepotConstruction.bmp", RGB(0, 255, 0));
	
	CResourceManager::GetManager()->CreateAnimation(L"SplyDptCnstrctn", pSplyDptCnstrctnTexture, L"SplyDptIdle", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"SplyDptIdle", pSplyDptTexture, L"SplyDptIdle", true, { 0, 0 }, { 1, 6 }, { 96, 128 }, 0.6f, false, true);
#pragma endregion

#pragma region Refinery
	// 리파이너리
	CTexture* pRfnryTexture = CResourceManager::GetManager()->LoadTexture(L"Rfnry", L"Texture\\Multi\\Building\\Refinery.bmp", RGB(0, 255, 0));
	CResourceManager::GetManager()->CreateAnimation(L"RfnryCnstrct", pRfnryTexture, L"RfnryCnstrct", true, { 0, 0 }, { 1, 3 }, { 192, 192 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"RfnryIdle", pRfnryTexture, L"RfnryIdle", true, { 0, 0 }, { 4, 4 }, { 192, 192 }, 1.0f, true, false);
#pragma endregion

#pragma region Engineering Bay
	// 엔지니어링 베이
	CTexture* pEngnrByTexture = CResourceManager::GetManager()->LoadTexture(L"EngnrBy", L"Texture\\Multi\\Building\\EngineeringBay.bmp", RGB(255, 0, 255));
	CTexture* pEngnrByCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"EngnrByCnstrctn", L"Texture\\Multi\\Building\\EngineeringBayConstruction.bmp", RGB(255, 0, 0));

	CResourceManager::GetManager()->CreateAnimation(L"EngnrByCnstrctn", pEngnrByCnstrctnTexture, L"EngnrByCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"EngnrByLand", pEngnrByTexture, L"EngnrByLand", true, { 0, 0 }, { 1, 1 }, { 192, 160 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"EngnrByUpgrd", pEngnrByTexture, L"EngnrByUpgrd", true, { 0, 0 }, { 2, 7 }, { 192, 160 }, 1.0f, false, true);
#pragma endregion

#pragma region Academy
	// 아카데미
	CTexture* pAcdmyTexture = CResourceManager::GetManager()->LoadTexture(L"Acdmy", L"Texture\\Multi\\Building\\Academy.bmp", RGB(0, 255, 0));
	CTexture* pAcdmyCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"AcdmyCnstrctn", L"Texture\\Multi\\Building\\AcademyConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"AcdmyCnstrctn", pAcdmyCnstrctnTexture, L"AcdmyCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"AcdmyIdle", pAcdmyTexture, L"AcdmyIdle", true, { 0, 0 }, { 1, 1 }, { 96, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"AcdmyUpgrd", pAcdmyTexture, L"AcdmyUpgrd", true, { 0, 0 }, { 1, 2 }, { 96, 128 }, 0.4f, false, true);
#pragma endregion

#pragma region Factory
	CTexture* pFctryTexture = CResourceManager::GetManager()->LoadTexture(L"Fctry", L"Texture\\Multi\\Building\\Factory.bmp", RGB(0, 255, 0));
	CTexture* pFctryCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"FctryCnstrctn", L"Texture\\Multi\\Building\\FactoryConstruction.bmp", RGB(255, 0, 0));

	CResourceManager::GetManager()->CreateAnimation(L"FctryCnstrctn", pFctryCnstrctnTexture, L"FctryCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FctryLnd", pFctryTexture, L"FctryLnd", true, { 0, 0 }, { 1, 1 }, { 128, 160 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"FctryPrdc", pFctryTexture, L"FctryPrdc", true, { 0, 0 }, { 2, 4 }, { 128, 160 }, 1.0f, false, true);
#pragma endregion

#pragma region Starport
	// 스타포트
	CTexture* pStrprtTexture = CResourceManager::GetManager()->LoadTexture(L"Strprt", L"Texture\\Multi\\Building\\Starport.bmp", RGB(0, 255, 0));
	CTexture* pStrprtCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"StrprtCnstrctn", L"Texture\\Multi\\Building\\StarportConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"StrprtCnstrctn", pStrprtCnstrctnTexture, L"StrprtCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"StrprtPrdc", pStrprtTexture, L"StrprtPrdc", true, { 0, 0 }, { 5, 7 }, { 128, 160 }, 0.3f, false, true);
	CResourceManager::GetManager()->CreateAnimation(L"StrprtLnd", pStrprtTexture, L"StrprtLnd", true, { 0, 0 }, { 1, 1 }, { 128, 160 }, 1.0f, true, false);
#pragma endregion

#pragma region Armory
	// 아머리
	CTexture* pArmryTexture = CResourceManager::GetManager()->LoadTexture(L"Armry", L"Texture\\Multi\\Building\\Armory.bmp", RGB(255, 0, 255));
	CTexture* pArmryCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"ArmryCnstrctn", L"Texture\\Multi\\Building\\ArmoryConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"ArmryCnstrctn", pArmryCnstrctnTexture, L"ArmryCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ArmryIdle", pArmryTexture, L"ArmryIdle", true, { 0, 0 }, { 1, 1 }, { 160, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ArmryUpgrd", pArmryTexture, L"ArmryUpgrd", true, { 0, 0 }, { 2, 4 }, { 160, 128 }, 0.6f, false, true);
#pragma endregion

#pragma region Science Facility
	// 사이언스 퍼실리티
	CTexture* pScncFcltyTexture = CResourceManager::GetManager()->LoadTexture(L"ScncFclty", L"Texture\\Multi\\Building\\ScienceFacility.bmp", RGB(255, 0, 255));
	CTexture* pScncFcltyCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"ScncFcltyCnstrctn", L"Texture\\Multi\\Building\\ScienceFacilityConstruction.bmp", RGB(255, 0, 255));

	CResourceManager::GetManager()->CreateAnimation(L"ScncFcltyCnstrctn", pScncFcltyCnstrctnTexture, L"ScncFcltyCnstrctn", false, { 0, 3 }, { 0, 0 }, { 160, 128 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncFcltyLand", pScncFcltyTexture, L"ScncFcltyLand", false, { 0, 0 }, { 0, 0 }, { 128, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"ScncFcltyUpgrd", pScncFcltyTexture, L"ScncFcltyUpgrd", false, { 0, 1 }, { 0, 0 }, { 128, 96 }, 0.4f, false, true);
#pragma endregion

#pragma region Nuclear Silo
	// 뉴클리어 사일로
	CTexture* pNclrSloTexture = CResourceManager::GetManager()->LoadTexture(L"NclrSlo", L"Texture\\Multi\\Building\\NuclearSilo.bmp", RGB(0, 255, 0));
	CTexture* pNclrSloCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"NclrSloCnstrctn", L"Texture\\Multi\\Building\\NuclearSiloConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"NclrSloCnstrctn", pNclrSloCnstrctnTexture, L"NclrSloCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"NclrSloConnect", pNclrSloTexture, L"NclrSloConnect", true, { 0, 0 }, { 2, 6 }, { 128, 128 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"NclrSloIdle", pNclrSloTexture,  L"NclrSloIdle", true, { 0, 0 }, { 6, 6 }, { 128, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"NclrSloUpgrd", pNclrSloTexture, L"NclrSloUpgrd", true, { 0, 0 }, { 6, 6 }, { 128, 64 }, 1.0f, true, false);
#pragma endregion

#pragma region Machine Shop
	// 머신 샵
	CTexture* pMchnShpTexture = CResourceManager::GetManager()->LoadTexture(L"MchnShp", L"Texture\\Multi\\Building\\MachineShop.bmp", RGB(255, 0, 255));
	CTexture* pMchnShpCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"MchnShpCnstrctn", L"Texture\\Multi\\Building\\MachineShopConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"MchnShpCnstrctn", pMchnShpCnstrctnTexture, L"MchnShpCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MchnShpConnect", pMchnShpTexture, L"MchnShpConnect", true, { 0, 0 }, { 2, 5 }, { 128, 128 }, 0.6f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MchnShpIdle", pMchnShpTexture,  L"MchnShpIdle", true, { 0, 0 }, { 5, 5 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MchnShpUpgrd", pMchnShpTexture, L"MchnShpUpgrd", true, { 0, 0 }, { 6, 8 }, { 128, 128 }, 0.2f, false, true);
#pragma endregion

#pragma region Control Tower
	// 컨트롤 타워
	CTexture* pCntrlTwrTexture = CResourceManager::GetManager()->LoadTexture(L"CntrlTwr", L"Texture\\Multi\\Building\\ControlTower.bmp", RGB(255, 0, 255));
	CTexture* pCntrlTwrCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"CntrlTwrCnstrctn", L"Texture\\Multi\\Building\\ControlTowerConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"CntrlTwrCnstrctn",pCntrlTwrCnstrctnTexture, L"CntrlTwrCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CntrlTwrConnect", pCntrlTwrTexture,	L"CntrlTwrConnect", true, { 0, 0 }, { 2, 6 }, { 128, 64 }, 0.6f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CntrlTwrIdle",	pCntrlTwrTexture,	L"CntrlTwrIdle", true, { 0, 0 }, { 6, 6 }, { 128, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CntrlTwrUpgrd",	pCntrlTwrTexture,	L"CntrlTwrUpgrd", true, { 0, 0 }, { 6, 7 }, { 128, 64 }, 0.2f, false, true);
#pragma endregion

#pragma region Physics Lab
	// 피직스 랩
	CTexture* pPhyscLbTexture = CResourceManager::GetManager()->LoadTexture(L"PhyscLb", L"Texture\\Multi\\Building\\PhysicsLab.bmp", RGB(0, 255, 0));
	CTexture* pPhyscLbCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"PhyscLbCnstrctn", L"Texture\\Multi\\Building\\PhysicsLabConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"PhyscLbCnstrctn", pPhyscLbCnstrctnTexture, L"PhyscLbCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"PhyscLbConnect", pPhyscLbTexture, L"PhyscLbConnect", true, { 0, 0 }, { 1, 5 }, { 128, 64 }, 0.6f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"PhyscLbIdle", pPhyscLbTexture, L"PhyscLbIdle", true, { 0, 0 }, { 5, 5 }, { 128, 64 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"PhyscLbUpgrd", pPhyscLbTexture, L"PhyscLbUpgrd", true, { 0, 0 }, { 5, 6 }, { 128, 64 }, 1.0f, false, true);
#pragma endregion

#pragma region Covert Ops
	// 코버트 옵스
	CTexture* pCvrtOpsTexture = CResourceManager::GetManager()->LoadTexture(L"CvrtOps", L"Texture\\Multi\\Building\\CovertOps.bmp", RGB(0, 255, 0));
	CTexture* pCvrtOpsCnstrctnTexture = CResourceManager::GetManager()->LoadTexture(L"CvrtOpsCnstrctn", L"Texture\\Multi\\Building\\CovertOpsConstruction.bmp", RGB(0, 255, 0));

	CResourceManager::GetManager()->CreateAnimation(L"CvrtOpsCnstrctn", pCvrtOpsCnstrctnTexture, L"CvrtOpsCnstrctn", false, { 0, 3 }, { 0, 0 }, { 96, 96 }, 3.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CvrtOpsConnect", pCvrtOpsTexture, L"CvrtOpsConnect", true, { 0, 0 }, { 1, 6 }, { 128, 128 }, 0.5f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CvrtOpsIdle", pCvrtOpsTexture, L"CvrtOpsIdle", true, { 0, 0 }, { 6, 6 }, { 128, 128 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"CvrtOpsUpgrd", pCvrtOpsTexture, L"CvrtOpsUpgrd", true, { 0, 0 }, { 6, 7 }, { 128, 128 }, 0.4f, false, true);
#pragma endregion
}

void CTestScene::LoadResourceTexture()
{
#pragma region Mineral
	// 미네랄
	CTexture* pMnrlTexture = CResourceManager::GetManager()->LoadTexture(L"Mnrl", L"Texture\\Multi\\Resource\\Mineral.bmp", RGB(0, 255, 0));
	
	// 미네랄 정지
	CResourceManager::GetManager()->CreateAnimation(L"MnrlA0", pMnrlTexture, L"MnrlA0", false, { 0, 0 }, { 0, 0 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlA1", pMnrlTexture, L"MnrlA1", false, { 0, 0 }, { 1, 1 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlA2", pMnrlTexture, L"MnrlA2", false, { 0, 0 }, { 2, 2 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlA3", pMnrlTexture, L"MnrlA3", false, { 0, 0 }, { 3, 3 }, { 64, 96 }, 1.0f, true, false);

	CResourceManager::GetManager()->CreateAnimation(L"MnrlB0", pMnrlTexture, L"MnrlB0", false, { 1, 1 }, { 0, 0 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlB1", pMnrlTexture, L"MnrlB1", false, { 1, 1 }, { 1, 1 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlB2", pMnrlTexture, L"MnrlB2", false, { 1, 1 }, { 2, 2 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlB3", pMnrlTexture, L"MnrlB3", false, { 1, 1 }, { 3, 3 }, { 64, 96 }, 1.0f, true, false);

	CResourceManager::GetManager()->CreateAnimation(L"MnrlC0", pMnrlTexture, L"MnrlC0", false, { 2, 2 }, { 0, 0 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlC1", pMnrlTexture, L"MnrlC1", false, { 2, 2 }, { 1, 1 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlC2", pMnrlTexture, L"MnrlC2", false, { 2, 2 }, { 2, 2 }, { 64, 96 }, 1.0f, true, false);
	CResourceManager::GetManager()->CreateAnimation(L"MnrlC3", pMnrlTexture, L"MnrlC3", false, { 2, 2 }, { 3, 3 }, { 64, 96 }, 1.0f, true, false);

	// 미네랄 오브
	CTexture* pMnrlOrbTexture = CResourceManager::GetManager()->LoadTexture(L"MnrlOrb", L"Texture\\Multi\\Resource\\MineralOrb.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"MnrlOrb", pMnrlOrbTexture, 0, 0, 32, 32);
#pragma endregion

#pragma region Vespene Gas
	// 가스
	CTexture* pVspnGasTexture = CResourceManager::GetManager()->LoadTexture(L"VspnGas", L"Texture\\Multi\\Resource\\Gas.bmp", RGB(0, 255, 0));

	// 가스 정지
	CResourceManager::GetManager()->CreateAnimation(L"VspnGas", pVspnGasTexture, L"VspnGas", false, { 0, 0 }, { 0, 0 }, { 128, 96 }, 1.0f, true, false);

	// 가스 오브
	CTexture* pGasOrbTexture = CResourceManager::GetManager()->LoadTexture(L"GasOrb", L"Texture\\Multi\\Resource\\GasOrb.bmp", RGB(255, 0, 255));
	CResourceManager::GetManager()->CreateSprite(L"GasOrb", pGasOrbTexture, 0, 0, 32, 32);
#pragma endregion
}

void CTestScene::Initialize()
{
	/****************************
		리소스 파일 불러오기 (경고! 키가 중복되는 경우, 스프라이트가 시안색으로 출력됩니다.)
	****************************/
	LoadUITexture();
	LoadUnitTexture();
	LoadBuildingTexture();
	LoadTileTexture();
	LoadEffectTexture();
	LoadResourceTexture();

	/****************************
		오브젝트 배치하기
	****************************/
	
	// 맵을 생성합니다.
	{
		CMapUI* pMapUI = new CMapUI();
		pMapUI->Initialize();
		InsertDynamicUI(pMapUI);
	}
	
	// 플레이어를 생성합니다.
	{
		s_pPlayer = new CPlayer();
		InsertObject(s_pPlayer);
	}
	
	/****************************
		타일맵 배치하기
	****************************/

	// 정적 타일맵을 로드합니다.
	{
		// 정적 타일맵 오브젝트를 생성합니다.
		CStaticTilemapObject* pStaticTilemapObject = new CStaticTilemapObject();
		m_pStaticTilemapObject = pStaticTilemapObject;

		// 정적 타일맵을 생성합니다.
		CTilemap* pStaticTilemap = CResourceManager::GetManager()->CreateTilemap(L"StaticTilemap");
		pStaticTilemap->SetMapSize({ 128, 128 });
		pStaticTilemap->SetTileSize({ 32, 32 });
		CResourceManager::GetManager()->LoadTilemap(L"StaticTilemap", L"Datasheet\\Tilemap\\StaticTilemap.txt");

		// 정적 타일맵을 타일맵 오브젝트에 저장합니다.
		m_pStaticTilemapObject->SetTilemap(pStaticTilemap);
		m_pStaticTilemapObject->SetDebug(false);
		m_pStaticTilemapObject->SetObjectType(EObjectType::TILEMAP);
		InsertObject(pStaticTilemapObject);
	}
	
	// 동적 타일맵을 생성합니다.
	{
		// 동적 타일맵 오브젝트를 생성합니다.
		CDynamicTilemapObject* pDynamicTilemapObject = new CDynamicTilemapObject();
		m_pDynamicTilemapObject = pDynamicTilemapObject;

		// 동적 타일맵을 생성합니다.
		CTilemap* pDynamicTilemap = CResourceManager::GetManager()->CreateTilemap(L"DynamicTilemap");
		pDynamicTilemap->SetMapSize({ 128, 128 });
		pDynamicTilemap->SetTileSize({ 32, 32 });

		// 동적 타일맵을 동적 타일맵 오브젝트에 저장합니다.
		m_pDynamicTilemapObject->SetTilemap(pDynamicTilemap);
		m_pDynamicTilemapObject->SetDebug(false);
		m_pDynamicTilemapObject->SetObjectType(EObjectType::TILEMAP);
		InsertObject(pDynamicTilemapObject);
	}

	/****************************
		오브젝트 배치하기
	****************************/
	
	// 미네랄 아홉 덩이를 생성합니다.
	for (int i = 0; i < 4; ++i)
	{
		CMineral* pMineral = new CMineral();
		pMineral->SetOwnerType(EOwnerType::NEUTRAL);
		pMineral->SetPosition({ 96.0f, 176.0f + 64.0f * i });
		InsertObject(pMineral);
		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 2, 5 + 2 * i }, { 2, 1 }, { ETileType::BUILDING, EOwnerType::NEUTRAL });
	}
	
	for (int i = 0; i < 3; ++i)
	{
		CMineral* pMineral = new CMineral();
		pMineral->SetOwnerType(EOwnerType::NEUTRAL);
		pMineral->SetPosition({ 64.0f, 208.0f + 64.0f * i });
		InsertObject(pMineral);
		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 1, 6 + 2 * i }, { 2, 1 }, { ETileType::BUILDING, EOwnerType::NEUTRAL });
	}
	
	{
		CMineral* pMineral = new CMineral();
		pMineral->SetOwnerType(EOwnerType::NEUTRAL);
		pMineral->SetPosition({ 96.0f, 400.0f });
		InsertObject(pMineral);
		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 2, 12 }, { 2, 1 }, { ETileType::BUILDING, EOwnerType::NEUTRAL });
	}

	{
		CMineral* pMineral = new CMineral();
		pMineral->SetOwnerType(EOwnerType::NEUTRAL);
		pMineral->SetPosition({ 128.0f, 432.0f });
		InsertObject(pMineral);
		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 3, 13 }, { 2, 1 }, { ETileType::BUILDING, EOwnerType::NEUTRAL });
	}

	// 베스핀 가스를 생성합니다.
	{
		CVespeneGas* pGas = new CVespeneGas();
		pGas->SetOwnerType(EOwnerType::NEUTRAL);
		pGas->SetPosition({ 288.0f, 96 });
		InsertObject(pGas);
		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 7, 2 }, { 4, 2 }, { ETileType::BUILDING, EOwnerType::NEUTRAL });
	}

	// 커맨드 센터를 생성합니다.
	{
		CBuildingProperty* pBuildingProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::COMMAND_CENTER);
		CCommandCenter* pCmdCntrObject = new CCommandCenter(*pBuildingProperty);
		pCmdCntrObject->SetObjectType(EObjectType::BUILDING);
		pCmdCntrObject->SetOwnerType(EOwnerType::PLAYER);
		pCmdCntrObject->SetPosition({ 288.0f, 272.0f });

		dynamic_cast<CDynamicTilemapObject*>(m_pDynamicTilemapObject)->InsertDynamicTiles({ 7, 7 }, { 4, 3 }, { ETileType::BUILDING, EOwnerType::PLAYER });

		array<int32, (int32)ETerranBuildingType::ENUM_END>& arrNumBuildings = CGameManager::GetManager()->GetNumBuildings();
		++arrNumBuildings[(int32)ETerranBuildingType::COMMAND_CENTER];
		InsertObject(pCmdCntrObject);
	}

	// SCV를 생성합니다.
	
	for (int i = 0; i < 4; ++i)
	{
		CUnitProperty* pSCVProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SCV);
		CSCV* pSCVObject = new CSCV(*pSCVProperty);
		pSCVObject->SetObjectType(EObjectType::UNIT);
		pSCVObject->SetOwnerType(EOwnerType::PLAYER);
		pSCVObject->SetPosition({ 240.0f + i * 32.0f, 336.0f });
		CGameManager::GetManager()->IncreaseConsumedSupply(1);
		InsertObject(pSCVObject);
	}
	
	/****************************
		위젯 배치하기
	****************************/

	// 사령부 UI를 생성합니다.
	{
		CControlCenter* pCtrlCenterUI = new CControlCenter();
		m_lstStaticUIs.push_back(pCtrlCenterUI);
	}

	// 미니맵 위젯 만들기
	{
		CMiniMapWidget* cMMPWUI = new CMiniMapWidget();
		m_lstStaticUIs.push_back(cMMPWUI);
	}

	// 싱글 위젯을 생성합니다.
	{
		CSUnitProfileWidget* pSPWUI = new CSUnitProfileWidget();
		m_lstStaticUIs.push_back(pSPWUI);
	}

	// 멀티 위젯을 생성합니다.
	{
		CMUnitProfileWidget* pMPWUI = new CMUnitProfileWidget();
		m_lstStaticUIs.push_back(pMPWUI);
	}

	// 명령 위젯 만들기
	{
		CCommandWidget* pCWUI = new CCommandWidget();
		m_lstStaticUIs.push_back(pCWUI);
	}

	// 리소스 위젯을 생성합니다.
	{
		CResourceWidget* pRSWUI = new CResourceWidget();
		m_lstStaticUIs.push_back(pRSWUI);
	}

	// 커서를 생성합니다.
	{
		s_pCursor = new CCursor();
		InsertObject(s_pCursor);
	}

	/****************************
		오브젝트 초기화하기
	****************************/
	CScene::Initialize();
	CSoundManager::GetManager()->PlayBGM(L"TerranBGM.wav", 1.0f);
}

void CTestScene::Update()
{
	CScene::Update();

	if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::CAPS_LOCK))
	{
		// 마린
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::ONE))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
				CMarine* pObject = new CMarine(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 800.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 파이어뱃
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::TWO))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
				CFirebat* pObject = new CFirebat(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 830.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 메딕
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::THREE))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MEDIC);
				CMedic* pObject = new CMedic(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 860.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 벌쳐
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FOUR))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
				CVulture* pObject = new CVulture(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 900.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 탱크
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FIVE))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty0 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
				CUnitProperty* pProperty1 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
				CSiegeTank* pObject = new CSiegeTank(*pProperty0, *pProperty1);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 950.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 배틀쿠르저
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::SIX))
		{
			for (int i = 0; i < 5; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::BATTLE_CRUISER);
				CBattlecruiser* pObject = new CBattlecruiser(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 1000.0f , 1100.0f + 50.0f * i });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}
	}

	if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::LEFT_CTRL))
	{
		// 마린
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::ONE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
				CMarine* pObject = new CMarine(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2100.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 파이어뱃
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::TWO))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
				CFirebat* pObject = new CFirebat(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2150.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 메딕
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::THREE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MEDIC);
				CMedic* pObject = new CMedic(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2200.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 벌쳐
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FOUR))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
				CVulture* pObject = new CVulture(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2250.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 탱크
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FIVE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty0 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
				CUnitProperty* pProperty1 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
				CSiegeTank* pObject = new CSiegeTank(*pProperty0, *pProperty1);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2300.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}

		// 배틀쿠르저
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::SIX))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::BATTLE_CRUISER);
				CBattlecruiser* pObject = new CBattlecruiser(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::COMPUTER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 2500.0f });
				InsertObject(pObject);
				pObject->Initialize();
			}
		}
	}

	if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::SPACE))
	{
		// 마린
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::ONE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
				CMarine* pObject = new CMarine(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1850.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(1);
				pObject->Initialize();
			}
		}

		// 파이어벳
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::TWO))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
				CFirebat* pObject = new CFirebat(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1850.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(1);
				pObject->Initialize();
			}
		}

		// 메딕
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::THREE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MEDIC);
				CMedic* pObject = new CMedic(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1800.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(1);
				pObject->Initialize();
			}
		}

		// 벌쳐
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FOUR))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
				CVulture* pObject = new CVulture(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1750.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(2);
				pObject->Initialize();
			}
		}

		// 탱크
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::FIVE))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty0 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
				CUnitProperty* pProperty1 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
				CSiegeTank* pObject = new CSiegeTank(*pProperty0, *pProperty1);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1700.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(2);
				pObject->Initialize();
			}
		}

		// 사이언스 배슬
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::SIX))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SCIENCE_VESSEL);
				CScienceVessel* pObject = new CScienceVessel(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1600.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(2);
				pObject->Initialize();
			}
		}

		// 배틀쿠르저
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::SEVEN))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::BATTLE_CRUISER);
				CBattlecruiser* pObject = new CBattlecruiser(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1500.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(6);
				pObject->Initialize();
			}
		}

		// 고스트
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::EIGHT))
		{
			for (int i = -2; i < 3; ++i)
			{
				CUnitProperty* pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GHOST);
				CGhost* pObject = new CGhost(*pProperty);
				pObject->SetObjectType(EObjectType::UNIT);
				pObject->SetOwnerType(EOwnerType::PLAYER);// 임시로 소유자를 플레이어로 설정합니다.
				pObject->SetPosition({ 2048.0f + 50.0f * i , 1500.0f });
				InsertObject(pObject);
				CGameManager::GetManager()->IncreaseConsumedSupply(6);
				pObject->Initialize();
			}
		}
	}

	/*
	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::Q))
	{
		CResourceManager::GetManager()->SaveTilemap(L"StaticTilemap", L"Datasheet\\Tilemap\\StaticTilemap.txt");
	}
	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::E))
	{
		CResourceManager::GetManager()->LoadTilemap(L"StaticTilemap", L"Datasheet\\Tilemap\\StaticTilemap.txt");
	}
	*/
}

void CTestScene::LateUpdate()
{
	CScene::LateUpdate();

	// 복사가 아닌 참조로 받아야 메모리에서 해제할 수 있습니다.
	for (auto& lst : m_lstObjects)
	{
		for (auto iter = lst.begin(); iter != lst.end();)
		{
			CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(*iter);

			// 다른 오브젝트는 제외합니다.
			if (pTerranObject == nullptr)
			{
				iter++;
				continue;
			}

			// 유닛이나 건물 오브젝트를 리스트에서 삭제합니다.
			if (pTerranObject->GetReady2Delete())
			{
				(*iter)->Release();
				delete *iter;
				iter = lst.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void CTestScene::Render(HDC _hDC)
{
	CScene::Render(_hDC);
	
	/*
	// 커서 위치를 출력합니다.
	{
		Vector2 tMousePosition = CMouseManager::GetManager()->GetMousePosition();
		wstring strMousePosition = std::format(L"Mouse ({0}, {1})", tMousePosition.m_fX, tMousePosition.m_fY);
		CGeometry::DrawString(_hDC, { 20, 20 }, strMousePosition, RGB(0, 255, 0));
	}

	// 스크롤된 위치를 출력합니다.
	{
		wstring strScrollPosition = std::format(L"Scroll ({0}, {1})", m_tCameraPosition.m_fX, m_tCameraPosition.m_fY);
		CGeometry::DrawString(_hDC, { 20, 40 }, strScrollPosition, RGB(0, 255, 0));
	}

	// 프레임률을 출력합니다.
	{
		uint32 uiFPS = CTimeManager::GetManager()->GetFPS();
		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		wstring strFPS = std::format(L"{0} FPS / {1} Delta Seconds", uiFPS, fDeltaSeconds);
		CGeometry::DrawString(_hDC, { 20, 60 }, strFPS, RGB(0, 255, 0));
	}
	*/
}

void CTestScene::Release()
{
	CScene::Release();
}

