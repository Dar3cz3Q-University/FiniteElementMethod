#include "pch.h"
#include "Surface.h"

Surface* Surface::m_Instance = nullptr;

Surface::Surface()
{
	int integrationSchema = (int)INTEGRATION_SCHEMA;

	auto& integrationPoints = IntegrationPointDerivatives::GetInstance()->GetIntegrationPoints();

	for (const auto& x : integrationPoints)
	{
		std::cout << x << "\n";
	}
}

Surface::~Surface()
{
	if (!m_Instance)
		delete m_Instance;
}

Surface* Surface::GetInstance()
{
	if (!m_Instance)
		m_Instance = new Surface();

	return m_Instance;
}
