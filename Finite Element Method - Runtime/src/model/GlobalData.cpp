#include "pch.h"

#include "GlobalData.h"

GlobalData::GlobalData()
{

}

std::ostream& operator<<(std::ostream& os, const GlobalData& globalData)
{
	//os << globalData.m_Grid << "\n";
	return os;
}
