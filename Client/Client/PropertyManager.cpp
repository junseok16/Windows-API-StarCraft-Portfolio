#include "pch.h"
#include "PropertyManager.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"

CPropertyManager* CPropertyManager::s_pPropertyManager = nullptr;

void CPropertyManager::Initialize()
{
	/*
		std::wstring _strName,
		ERaceType _eRaceType,
		Vector2Int _tileSize,
		std::wstring _strRank,// 유닛만 있습니다.
		int32 _iMaxHP,
		int32 _iMaxMP,
		int32 _iMaxShield,
		int32 _iAttackPoint,
		int32 _iDefensePoint,
		float _fSpeed,
		float _fAttackDeltaSeconds,
		int32 _iSight,
		int32 _iRange,
		int32 _iMineral,
		int32 _iGas,
		int32 _iSeconds,
		int32 _iConsumeSupply);
	*/
	/*
		CBuildingProperty(
        std::wstring _strName,
        ERaceType _eRaceType,
		Vector2Int _tileSize,
        int32 _iMaxHP,
        int32 _iMaxMP,
        int32 _iMaxShield,
        int32 _iAttackPoint,
        int32 _iDefensePoint,
        float _fSpeed,
        float _fAttackDeltaSeconds,
        int32 _iSight,
        int32 _iRange,
        int32 _iMineral,
        int32 _iGas,
        int32 _iSeconds,
        int32 _iProduceSupply);
	*/
	/*
		CUpgradeProperty(
		std::wstring _strName,
		ERaceType _eRaceType,
		Vector2Int _tTileSize,
		std::wstring _strRank,
		int32 _iRank,
		int32 _iMaxHP,
		int32 _iMaxMP,
		int32 _iMaxShield,
		int32 _iAttackPoint,
		int32 _iDefensePoint,
		float _fSpeed,
		float _fAttackDeltaSeconds,
		int32 _iSight,
		int32 _iRange,
		int32 _iMineral,
		int32 _iGas,
		int32 _iSeconds,
		int32 _iConsumeSupply);
	*/

	// 유닛 프로퍼티 rank																														hp		mp		shld	atk		def		spd			delta		sight	range	mi		gas		time	supply
	{
		CUnitProperty* pSCVPrprty			= new CUnitProperty(L"Terran SCV",				ERaceType::TERRAN, { 1, 1 }, L"Pirate",			 0, 60,		0,		0,		5,		0,		125.0f,		0.625f,		224,	32,		50,		0,		1,		1);
		CUnitProperty* pMrnPrprty			= new CUnitProperty(L"Terran Marine",			ERaceType::TERRAN, { 1, 1 }, L"Pirate",			 1, 40,		0,		0,		6,		0,		100.0f,		0.625f,		224,	128,	50,		0,		1,		1);
		CUnitProperty* pMdcnPrprty			= new CUnitProperty(L"Terran Medic",			ERaceType::TERRAN, { 1, 1 }, L"1st Lieutenant",	 2, 60,		200,	0,		6,		1,		100.0f,		0.3f,		288,	48,		50,		25,		1,		1);
		CUnitProperty* pFrbtPrprty			= new CUnitProperty(L"Terran Firebat",			ERaceType::TERRAN, { 1, 1 }, L"Corporal",		 3, 50,		0,		0,		4,		1,		100.0f,		0.916f,		224,	48,		50,		25,		1,		1);
		CUnitProperty* pGhstPrprty			= new CUnitProperty(L"Terran Ghost",			ERaceType::TERRAN, { 1, 1 }, L"Specialist",		 4, 45,		200,	0,		4,		1,		100.0f,		0.916f,		320,	224,	50,		25,		1,		1);

		CUnitProperty* pVltrPrprty			= new CUnitProperty(L"Terran Vulture",			ERaceType::TERRAN, { 1, 1 }, L"Sergeant",		 5, 80,		0,		0,		15,		0,		130.0f,		1.25f,		256,	160,	75,		0,		1,		2);
		CUnitProperty* pGlthPrprty			= new CUnitProperty(L"Terran Goliath",			ERaceType::TERRAN, { 1, 1 }, L"First Sergeant",	 6, 125,	0,		0,		12,		1,		110.0f,		0.916f,		256,	192,	100,	50,		1,		2);
		CUnitProperty* pTnkPrprty			= new CUnitProperty(L"Terran Siege Tank",		ERaceType::TERRAN, { 1, 1 }, L"Master Sergeant", 7, 150,	0,		0,		15,		1,		100.0f,		1.541f,		320,	224,	150,	100,	1,		2);
		CUnitProperty* pSgTnkPrprty			= new CUnitProperty(L"Terran Siege Tank",		ERaceType::TERRAN, { 1, 1 }, L"Master Sergeant", 8, 150,	0,		0,		35,		1,		0.0f,		3.125f,		320,	384,	150,	100,	1,		2);
		CUnitProperty* pScncVsslSgTnkPrprty = new CUnitProperty(L"Terran Science Vessel",	ERaceType::TERRAN, { 1, 1 }, L"Major",			11, 200,	200,	0,		0,		1,		110.0f,		0.0f,		320,	0,		100,	225,	1,		2);
		CUnitProperty* pBtlcrsrPrprty		= new CUnitProperty(L"Terran Battlecruiser",	ERaceType::TERRAN, { 1, 1 }, L"Commodore",		13, 500,	200,	0,		25,		1,		70.0f,		1.25f,		352,	192,	400,	300,	1,		6);

		/*
		CUnitProperty* pDrpShpPrprty		= new CUnitProperty(L"Terran Dropship",			ERaceType::TERRAN, { 2, 2 }, L"Warrant Officer", 9,	150,	0,		0,		0,		1,		60.0f,		0.0f,		256,	0,		100,	100,	1,		2);
		CUnitProperty* pWrthPrprty			= new CUnitProperty(L"Terran Wraith",			ERaceType::TERRAN, { 2, 2 }, L"Captain",		10,	150,	100,	0,		70,		1,		60.0f,		3.125f,		260,	384,	150,	100,	1,		2);
		CUnitProperty* pVlkyrPrprty			= new CUnitProperty(L"Terran Valkyrie",			ERaceType::TERRAN, { 2, 2 }, L"Lt Commander",	12,	150,	0,		0,		70,		1,		60.0f,		3.125f,		260,	384,	150,	100,	1,		2);
		*/
		
		m_arrUnitProperties[(int32)ETerranUnitType::SCV] = pSCVPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::MARINE] = pMrnPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::FIREBAT] = pFrbtPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::MEDIC] = pMdcnPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::GHOST] = pGhstPrprty;

		m_arrUnitProperties[(int32)ETerranUnitType::VULTURE] = pVltrPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::TANK] = pTnkPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::SIEGE_TANK] = pSgTnkPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::GOLIATH] = pGlthPrprty;

		m_arrUnitProperties[(int32)ETerranUnitType::SCIENCE_VESSEL] = pScncVsslSgTnkPrprty;
		m_arrUnitProperties[(int32)ETerranUnitType::BATTLE_CRUISER] = pBtlcrsrPrprty;
	}
		
	// 빌딩 프로퍼티
	{
		CBuildingProperty* pCmndCntrPrprty = new CBuildingProperty(L"Terran Command Center", ERaceType::TERRAN, { 4, 3 }, 1500, 0, 0, 0, 1, 1.0f, 0, 10, 0, 400, 0, 1, 10);
		CBuildingProperty* pSpplyDptsPrprty = new CBuildingProperty(L"Terran Supply Depots", ERaceType::TERRAN, { 3, 2 }, 500, 0, 0, 0, 1, 0.0f, 0, 8, 0, 100, 0, 1, 8);
		CBuildingProperty* pRfnryPrprty = new CBuildingProperty(L"Terran Refinery", ERaceType::TERRAN, { 4, 2 }, 750, 0, 0, 0, 1, 0.0f, 0, 8, 0, 100, 0, 1, 0);
		CBuildingProperty* pBrrcksPrprty = new CBuildingProperty(L"Terran Barracks", ERaceType::TERRAN, { 4, 3 }, 1000, 0, 0, 0, 1, 1.0f, 0, 8, 0, 150, 0, 1, 0);
		CBuildingProperty* pEngnrByPrprty = new CBuildingProperty(L"Terran Engineering Bay", ERaceType::TERRAN, { 4, 3 }, 850, 0, 0, 0, 1, 1.0f, 0, 8, 0, 125, 0, 1, 0);
		CBuildingProperty* pAcdmyPrprty = new CBuildingProperty(L"Terran Academy", ERaceType::TERRAN, { 3, 2 }, 600, 0, 0, 0, 1, 0.0f, 0, 8, 0, 150, 0, 1, 0);

		CBuildingProperty* pFctryPrprty = new CBuildingProperty(L"Terran Factory", ERaceType::TERRAN, { 4, 3 }, 1250, 0, 0, 0, 1, 1.0f, 0, 8, 0, 200, 100, 1, 0);
		CBuildingProperty* pStrprtPrprty = new CBuildingProperty(L"Terran Starport", ERaceType::TERRAN, { 4, 3 }, 1300, 0, 0, 0, 1, 1.0f, 0, 10, 0, 150, 100, 1, 0);
		CBuildingProperty* pScncFcltyPrprty = new CBuildingProperty(L"Terran Science Facility", ERaceType::TERRAN, { 4, 3 }, 850, 0, 0, 0, 1, 1.0f, 0, 10, 0, 100, 150, 1, 0);
		CBuildingProperty* pArmryPrprty = new CBuildingProperty(L"Terran Armory", ERaceType::TERRAN, { 3, 2 }, 750, 0, 0, 0, 1, 0.0f, 0, 8, 0, 100, 50, 1, 0);

		CBuildingProperty* pCmstStnPrprty = new CBuildingProperty(L"Terran Comsat Station", ERaceType::TERRAN, { 2, 2 }, 500, 200, 0, 0, 1, 0.0f, 0, 10, 0, 50, 50, 1, 0);
		CBuildingProperty* pNclrSloPrprty = new CBuildingProperty(L"Terran Nuclear Silo", ERaceType::TERRAN, { 2, 2 }, 600, 0, 0, 0, 1, 0.0f, 0, 8, 0, 100, 100, 1, 0);
		CBuildingProperty* pMchnShpPrprty = new CBuildingProperty(L"Terran Machine Shop", ERaceType::TERRAN, { 2, 2 }, 750, 0, 0, 0, 1, 0.0f, 0, 8, 0, 50, 50, 1, 0);
		
		CBuildingProperty* pCntrlTwrPrprty = new CBuildingProperty(L"Terran Control Tower", ERaceType::TERRAN, { 2, 2 }, 500, 0, 0, 0, 1, 0.0f, 0, 8, 0, 50, 50, 1, 0);
		CBuildingProperty* pPhyscLbPrprty = new CBuildingProperty(L"Terran Physics Lab",	ERaceType::TERRAN, { 2, 2 }, 600, 0, 0, 0, 1, 0.0f, 0, 8, 0, 50, 50, 1, 0);
		CBuildingProperty* pCvrtOpsPrprty = new CBuildingProperty(L"Terran Covert Ops",		ERaceType::TERRAN, { 2, 2 }, 750, 0, 0, 0, 1, 0.0f, 0, 8, 0, 50, 50, 1, 0);
		

		m_arrBuildingProperties[(int32)ETerranBuildingType::COMMAND_CENTER] = pCmndCntrPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::SUPPLY_DEPOT] = pSpplyDptsPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::REFINERY] = pRfnryPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::BARRACKS] = pBrrcksPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::ENGINEERING_BAY] = pEngnrByPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::ACADEMY] = pAcdmyPrprty;

		m_arrBuildingProperties[(int32)ETerranBuildingType::FACTORY] = pFctryPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::STARPORT] = pStrprtPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::SCIENCE_FACILITY] = pScncFcltyPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::ARMORY] = pArmryPrprty;

		m_arrBuildingProperties[(int32)ETerranBuildingType::COMSAT_STATION] = pCmstStnPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::NUCLEAR_SILO] = pNclrSloPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::MACHINE_SHOP] = pMchnShpPrprty;

		m_arrBuildingProperties[(int32)ETerranBuildingType::CONTROL_TOWER] = pCntrlTwrPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::PHYSICS_LAB] = pPhyscLbPrprty;
		m_arrBuildingProperties[(int32)ETerranBuildingType::COVERT_OPS] = pCvrtOpsPrprty;
	}
	
	// 업그레이드 프로퍼티
	{
		// 엔지니어링 베이
		CUpgradeProperty* pInfWpn1Prprty	= new CUpgradeProperty(L"Upgrade Infantry Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pInfWpn2Prprty	= new CUpgradeProperty(L"Upgrade Infantry Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 175, 175, 3, 0);
		CUpgradeProperty* pInfWpn3Prprty	= new CUpgradeProperty(L"Upgrade Infantry Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 250, 250, 3, 0);

		CUpgradeProperty* pInfArmr1Prprty	= new CUpgradeProperty(L"Upgrade Infantry Armor",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pInfArmr2Prprty	= new CUpgradeProperty(L"Upgrade Infantry Armor",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 175, 175, 3, 0);
		CUpgradeProperty* pInfArmr3Prprty	= new CUpgradeProperty(L"Upgrade Infantry Armor",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 250, 250, 3, 0);

		// 아카데미
		CUpgradeProperty* pU238ShllPrprty	= new CUpgradeProperty(L"Research U-238 Shells",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 150, 150, 3, 0);
		CUpgradeProperty* pStmpckTchPrprty	= new CUpgradeProperty(L"Research Stimpack Tech",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);

		// 머신 샵
		CUpgradeProperty* pIonThrstrPrprty	= new CUpgradeProperty(L"Research Ion Thrusters",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pSgMdPrprty		= new CUpgradeProperty(L"Research Siege Tech",		ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 150, 150, 3, 0);

		// 아머리
		CUpgradeProperty* pVhclWpn1Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pVhclWpn2Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 175, 175, 3, 0);
		CUpgradeProperty* pVhclWpn3Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Weapons", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 250, 250, 3, 0);

		CUpgradeProperty* pVhclPltng1Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Plating", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pVhclPltng2Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Plating", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 175, 175, 3, 0);
		CUpgradeProperty* pVhclPltng3Prprty	= new CUpgradeProperty(L"Upgrade Vehicle Plating", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 250, 250, 3, 0);

		// 사이언스 퍼실리티
		CUpgradeProperty* pIrdtPrprty		= new CUpgradeProperty(L"Research Irradiate",		ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 200, 200, 3, 0);
		CUpgradeProperty* pTtnRctrPrprty	= new CUpgradeProperty(L"Upgrade Titan Reactor",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 150, 150, 3, 0);

		// 피직스 랩
		CUpgradeProperty* pYmtCnnPrprty		= new CUpgradeProperty(L"Research Yamato Cannon",	ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 0);
		CUpgradeProperty* pClssRctrPrprty	= new CUpgradeProperty(L"Upgrade Colossus Reactor", ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 150, 150, 3, 0);

		// 코버트 옵스

		// 뉴클리어 사일로
		CUpgradeProperty* pArmNclrSloPrprty = new CUpgradeProperty(L"Arm Nuclear Silo",			ERaceType::TERRAN, { 0, 0 }, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 100, 100, 3, 8);

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_WEAPONS_1] = pInfWpn1Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_WEAPONS_2] = pInfWpn2Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_WEAPONS_3] = pInfWpn3Prprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_ARMOR_1] = pInfArmr1Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_ARMOR_2] = pInfArmr2Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::INFANTRY_ARMOR_3] = pInfArmr3Prprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::U238_SHELLS]		= pU238ShllPrprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::STIMPACK_TECH]	= pStmpckTchPrprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::ION_THRUSTERS]	= pIonThrstrPrprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::SIEGE_TECH]		= pSgMdPrprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_WEAPONS_1] = pVhclWpn1Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_WEAPONS_2] = pVhclWpn2Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_WEAPONS_3] = pVhclWpn3Prprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_PLATING_1] = pVhclPltng1Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_PLATING_2] = pVhclPltng2Prprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::VIHICLE_PLATING_3] = pVhclPltng3Prprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::IRRADIATE]		= pIrdtPrprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::TITAN_REACTOR]	= pTtnRctrPrprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::YAMATO_CANNON]	= pYmtCnnPrprty;
		m_arrUpgradeProperties[(int32)ETerranUpgradeType::COLOSSUS_REACTOR] = pClssRctrPrprty;

		m_arrUpgradeProperties[(int32)ETerranUpgradeType::ARM_NUCLEAR_SILO] = pArmNclrSloPrprty;
	}
}

void CPropertyManager::Release()
{
	for_each(m_arrUnitProperties.begin(), m_arrUnitProperties.end(), SAFE_DELETE_FUNCTOR());
	for_each(m_arrBuildingProperties.begin(), m_arrBuildingProperties.end(), SAFE_DELETE_FUNCTOR());
	for_each(m_arrUpgradeProperties.begin(), m_arrUpgradeProperties.end(), SAFE_DELETE_FUNCTOR());

	VERIFY_NULLPTR(s_pPropertyManager);
	SAFE_DELETE(s_pPropertyManager);
}
