#pragma once

class CUnitProperty;
class CBuildingProperty;
class CUpgradeProperty;

class CPropertyManager final
{
private:
	CPropertyManager() = default;

public:
	~CPropertyManager() = default;
	CPropertyManager(const CPropertyManager& rhs) = delete;
	CPropertyManager(CPropertyManager&& rhs) = delete;
	CPropertyManager& operator=(const CPropertyManager& rhs) = delete;
	CPropertyManager& operator=(CPropertyManager&& rhs) = delete;

public:
	static CPropertyManager* GetManager() {
		if (s_pPropertyManager == nullptr)
		{
			s_pPropertyManager = new CPropertyManager();
		}
		return s_pPropertyManager;
	}

public:
	void Initialize();
	void Release();

public:
	CUnitProperty* GetUnitProperty(ETerranUnitType _eTerranUnitType) { return m_arrUnitProperties[(int32)_eTerranUnitType]; }
	CBuildingProperty* GetBuildingProperty(ETerranBuildingType _eTerranBuildingType) { return m_arrBuildingProperties[(int32)_eTerranBuildingType]; }
	CUpgradeProperty* GetUpgradeProperty(ETerranUpgradeType _eTerranUpgradeType) { return m_arrUpgradeProperties[(int32)_eTerranUpgradeType]; }

/***************
	µ•¿Ã≈Õ ∏‚πˆ
***************/
public:
	static CPropertyManager* s_pPropertyManager;

private:
	std::array<CUnitProperty*, (int32)ETerranUnitType::ENUM_END> m_arrUnitProperties{ nullptr };
	std::array<CBuildingProperty*, (int32)ETerranBuildingType::ENUM_END> m_arrBuildingProperties{ nullptr };
	std::array<CUpgradeProperty*, (int32)ETerranUpgradeType::ENUM_END> m_arrUpgradeProperties{ nullptr };
};

