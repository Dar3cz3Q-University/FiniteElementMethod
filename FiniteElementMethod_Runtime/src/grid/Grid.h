#pragma once

#include "Element.h"
#include "numerical_methods/NumericalMethods.h"
#include "multithreading/ThreadPool.h"

#include "gtest/gtest.h"

class Grid 
{
public:
	Grid() = default;

public:
	void Calculate(const GlobalData& data);

public:
	size_t GetNumberOfNodes() const { return m_Nodes.size(); }
	size_t GetNumberOfElements() const { return m_Elements.size(); }

	Node GetNode(int index) const { return m_Nodes.at(index); }

	Matrix GetH() const { return m_Matrix_H; }
	Matrix GetC() const { return m_Matrix_C; }
	Matrix GetP() const { return m_Vector_P; }

	inline void AddElement(int index, Element element) { m_Elements.insert({ index, element }); }
	inline void AddNode(int index, Node node) { m_Nodes.insert({ index, node }); }
	inline void SetNodeAsBoundaryCondition(int index) { m_Nodes.at(index).IsBoundaryCondition = true; }
	inline void SetParametersForElement(int index, Parameters parameters) { m_Elements.at(index).SetParameters(parameters); };

private:
	std::map<int, Element> m_Elements;
	std::map<int, Node> m_Nodes;
	Matrix m_Matrix_H;
	Matrix m_Matrix_C;
	Matrix m_Vector_P;

private:
	void CalculateGlobalData();

public:
	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
	friend class VTKFileWriter;

public:
	FRIEND_TEST(Global_H_MatrixTest, GeneratesValidMatrixFor_Test1_4_4);
	FRIEND_TEST(Global_H_MatrixTest, GeneratesValidMatrixFor_Test2_4_4);

	FRIEND_TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test1_4_4);
	FRIEND_TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test2_4_4);
};

std::ostream& operator<<(std::ostream& os, const Grid& grid);
