#include "pch.h"
#include "UniversalElement.h"

UniversalElement* UniversalElement::m_Instance = nullptr;

UniversalElement::UniversalElement()
{
	LOG_TRACE("Calculating universal elements");

	int integrationSchema = (int)INTEGRATION_SCHEMA + 1;
	std::vector<double> legendreValues = LEGENDRE_POINTS.at(integrationSchema);
	std::vector<double> legendreWeights = LEGENDRE_WEIGHTS.at(integrationSchema);

	double localCoordinates[] = { -1.0, 1.0 };

	//
	// Calculate H matricies and P vectors
	//

	LOG_TRACE("Calculating universal H matricies and P vectors");

	for (int i = 0; i < 4; i++)
	{
		std::vector<Matrix> integrationPointsMatricies;
		integrationPointsMatricies.reserve(INTEGRATION_POINTS_COUNT);

		for (auto legendreValue : legendreValues)
		{
			Matrix tempMatrix(1, 4);

			size_t k = 0;
			for (auto& [_, shape] : SHAPE_FUNCTIONS)
			{
				int index = i <= 1 ? i : i + 1;

				double result = i % 2 != 0 ? shape(localCoordinates[index % 2], legendreValue) : shape(legendreValue, localCoordinates[index % 2]);

				tempMatrix.SetElement(0, k++, result);
			}
			
			integrationPointsMatricies.push_back(tempMatrix);
		}

		LOG_TRACE("Calculating universal H matrix for {} surface", i);

		Matrix surfaceMatrix(4);

		size_t k = 0;
		for (auto& matrix : integrationPointsMatricies)
			surfaceMatrix = surfaceMatrix + (matrix.Transpose() * matrix * legendreWeights.at(k++));

#ifdef ENABLE_DEBUG_PRINT
		LOG_TRACE("Displaying universal H matrix for {} surface", i);
		std::cout << surfaceMatrix << "\n";
#endif

		m_SurfaceMatricies.insert({ (SurfaceEnum) i, surfaceMatrix });

		LOG_TRACE("Displaying universal P vector for {} surface", i);

		Matrix pVector(4, 1);

		k = 0;
		for (auto& matrix : integrationPointsMatricies)
			pVector = (matrix.Transpose() * legendreWeights.at(k++)) + pVector;

#ifdef ENABLE_DEBUG_PRINT
		LOG_TRACE("Displaying universal P vector for {} surface", i);
		std::cout << pVector << "\n";
#endif

		m_PVectors.insert({ (SurfaceEnum)i, pVector });
	}

	//
	// Calculate C Matricies
	//

	LOG_TRACE("Calculating universal C matricies");

	std::vector<Node> legendrePoints = IntegrationPointDerivatives::GetInstance()->GetIntegrationPoints();

	size_t i = 0;
	for (auto& point : legendrePoints)
	{
		LOG_TRACE("Calculating universal C matricies in {} integration point", i);

		Matrix tempMatrix(1, 4);

		size_t k = 0;
		for (auto& [_, shape] : SHAPE_FUNCTIONS)
		{
			double result = shape(point.ksi, point.eta);
			tempMatrix.SetElement(0, k++, result);
		}

		Matrix cMatrix(4);
		cMatrix = tempMatrix.Transpose() * tempMatrix;

#ifdef ENABLE_DEBUG_PRINT
		LOG_TRACE("Displaying universal C matricies in {} integration point", i++);
		std::cout << cMatrix << "\n";
#endif

		m_CMatricies.push_back(cMatrix);
	}
}

UniversalElement::~UniversalElement()
{
	if (!m_Instance)
		delete m_Instance;
}

UniversalElement* UniversalElement::GetInstance()
{
	if (!m_Instance)
		m_Instance = new UniversalElement();

	return m_Instance;
}
