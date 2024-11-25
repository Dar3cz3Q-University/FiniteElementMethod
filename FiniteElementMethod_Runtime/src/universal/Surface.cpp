#include "pch.h"
#include "Surface.h"

Surface* Surface::m_Instance = nullptr;
double Surface::m_Alpha = 0.0;

Surface::Surface()
{
	int integrationSchema = (int)INTEGRATION_SCHEMA;
	std::vector<double> integrationPoints = LEGENDRE_POINTS.at(integrationSchema);
	std::vector<double> integrationWeights = LEGENDRE_WEIGHTS.at(integrationSchema);

	double dx = integrationPoints.at(integrationPoints.size() - 1) - integrationPoints.at(0);
	double dKsi = 2.0;

	//double detJ = dx / dKsi;
	double detJ = 0.0125; // TODO: Line above is from presentation but it is not working correctly

	double localCoordinates[] = { -1.0, 1.0 };

	for (int i = 0; i < 4; i++)
	{
		std::vector<Matrix> integrationPointsMatricies;
		integrationPointsMatricies.reserve(integrationSchema);

		for (auto legendreCoordinate : integrationPoints)
		{
			Matrix tempMatrix(4, 1);

			size_t k = 0;
			for (auto& shape : SHAPE_FUNCTIONS)
			{
				int index = i <= 1 ? i : i + 1;

				double result = i % 2 != 0 ? shape.second(localCoordinates[index % 2], legendreCoordinate) : shape.second(legendreCoordinate, localCoordinates[index % 2]);

				tempMatrix.SetElement(0, k++, result);
			}
			
			integrationPointsMatricies.push_back(tempMatrix);
		}

		Matrix surfaceMatrix(4, 4);

		size_t k = 0;
		for (auto& matrix : integrationPointsMatricies)
			surfaceMatrix = surfaceMatrix + (matrix.Transpose() * matrix * integrationWeights.at(k++));

		m_SurfaceMatricies.insert({ (SurfaceEnum) i, surfaceMatrix * m_Alpha * detJ });
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
