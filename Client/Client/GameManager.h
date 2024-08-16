#pragma once

class CTerranObject;

class CGameManager final {
/***************
	메서드
***************/
private:
	CGameManager() = default;

public:
	~CGameManager() = default;

public:
	static CGameManager* GetManager()
	{
		if (s_pGameManager == nullptr)
		{
			s_pGameManager = new CGameManager();
		}
		return s_pGameManager;
	}

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Release();

public:
	int32 GetProducedMineral() const { return m_iProducedMineral; }
	void SetProducedMineral(int32 _iProducedMineral) { m_iProducedMineral = _iProducedMineral; }
	
	int32 GetProducedGas() const { return m_iProducedGas; }
	void SetProducedGas(int32 _iProducedGas) { m_iProducedGas = _iProducedGas; }
	
	int32 GetProducedSupply() const { return m_iProducedSupply; }
	void SetProducedSupply(int32 _iProducedSupply) { m_iProducedSupply = _iProducedSupply; }
	
	int32 GetConsumedSupply() const { return m_iConsumedSupply; }
	void SetConsumedSupply(int32 _iConsumedSupply) { m_iConsumedSupply = _iConsumedSupply; }
	
	std::vector<CTerranObject*>& GetSelectedObjects() { return m_vecSelectedObjects; }
	void SetSelectedObjects(std::vector<CTerranObject*> _vecSelectedObject) { m_vecSelectedObjects = _vecSelectedObject; }

	std::array<int32, (int32)ETerranBuildingType::ENUM_END>& GetNumBuildings() { return m_arrNumBuildings; }

	std::array<int32, (int32)ETerranUnitType::ENUM_END>& GetNumUnits() { return m_arrNumUnits; }

	std::array<bool, (int32)ETerranUpgradeType::ENUM_END>& GetUpgrades() { return m_arrUpgrades; }
	void SetUpgrade(ETerranUpgradeType _eTerranUpgradeType, bool _bUpgrade) { m_arrUpgrades[(int32)_eTerranUpgradeType] = _bUpgrade; }

public:
	void IncreaseProducedMineral(int32 _iProducedMineral) { m_iProducedMineral += _iProducedMineral; }
	
	void IncreaseProducedGas(int32 _iProducedGas) { m_iProducedGas += _iProducedGas; }
	
	void IncreaseProducedSupply(int32 _iProducedSupply) { m_iProducedSupply += _iProducedSupply; }
	
	void IncreaseConsumedSupply(int32 _iConsumedSupply) { m_iConsumedSupply += _iConsumedSupply; }
	
	void IncreaseNumBuilding(ETerranBuildingType _eTerranBuildingType, int32 _iValue) { m_arrNumBuildings[(int32)_eTerranBuildingType] += _iValue; }
	
	bool IsThereBuilding(ETerranBuildingType _eBuildingType) { return m_arrNumBuildings[(int32)_eBuildingType] > 0; }
	
	bool IsThereUpgrade(ETerranUpgradeType _eUpgradeType) { return m_arrUpgrades[(int32)_eUpgradeType]; }
	
public:
	void ClearSelectedObject();

	void InsertSelectedObject(CTerranObject* _pTerranObject) { m_vecSelectedObjects.push_back(_pTerranObject); }

	size_t SizeSelectedObject() { return m_vecSelectedObjects.size(); }

	CTerranObject* FrontSelectedObject() { return m_vecSelectedObjects.front(); }

public:
	void SendCommand(ECommandType _eCommandType);

	void SendCommand(ECommandType _eCommandType, CTerranObject* _pTargetObject);

	void SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition);

	void SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTargetObject);

/***************
	데이터 멤버
***************/
public:
	static CGameManager* s_pGameManager;

private:
	// 생산한 미네랄
	int32 m_iProducedMineral = 100'50;

	// 생산한 가스
	int32 m_iProducedGas = 10'000;

	// 생산한 보급품
	int32 m_iProducedSupply = 0;

	// 소비한 보급품
	int32 m_iConsumedSupply = 0;

	// 건물의 수
	std::array<int32, (int32)ETerranBuildingType::ENUM_END> m_arrNumBuildings{ 0 };

	// 유닛의 수
	std::array<int32, (int32)ETerranUnitType::ENUM_END> m_arrNumUnits{ 0 };

	// 업그레이드 여부
	std::array<bool, (int32)ETerranUpgradeType::ENUM_END> m_arrUpgrades{ false };

	// 선택된 유닛/건물
	std::vector<CTerranObject*> m_vecSelectedObjects;

private:
	// 건물이 건설된 타일 위치
	std::vector<Vector2Int> m_vecAddOnTilePosition[(int32)ETerranAddOnType::ENUM_END];

	// 커맨드 센터가 건설된 타일 위치
	std::vector<Vector2Int> m_vecCmdCntrTilePosition;

	// 베스핀 가스가 있는 타일 위치
	std::vector<Vector2Int> m_vecVspnGasTilePosition;

public:
	void InsertAddOnTilePosition(ETerranAddOnType _eTerranAddOnType, Vector2Int _tTilePosition) { m_vecAddOnTilePosition[(int32)_eTerranAddOnType].push_back(_tTilePosition); }

	std::vector<Vector2Int>& GetAddOnTilePosition(ETerranAddOnType _eTerranAddOnType) { return m_vecAddOnTilePosition[(int32)_eTerranAddOnType]; }

	void InsertCmdCntrTilePosition(Vector2Int _tTilePosition) { m_vecCmdCntrTilePosition.push_back(_tTilePosition); }

	std::vector<Vector2Int>& GetCmdCntrTilePosition() { return m_vecCmdCntrTilePosition; }

	void InsertVspnGasTilePosition(Vector2Int _tTilePosition) { m_vecVspnGasTilePosition.push_back(_tTilePosition); }

	std::vector<Vector2Int>& GetVspnGasTilePosition() { return m_vecVspnGasTilePosition; }
};

