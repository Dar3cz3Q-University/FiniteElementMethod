#include "pch.h"

#include "gtest/gtest.h"

#include "Simulation.h"

static const double EPSILON = 1e-1;

static double globalPVectorFixture_1_4_4[16] = {
    12000.0,
    12000.0,
    12000.0,
    12000.0,
    12000.0,
    0.0,
    0.0,
    12000.0,
    12000.0,
    0.0,
    0.0,
    12000.0,
    11999.9,
    12000.0,
    12000.0,
    12000.0,
};

static double globalPVectorFixture_2_4_4[16] = {
    16310.9,
    13922.3,
    9844.53,
    8155.47,
    13922.3,
    0,
    0,
    9844.53,
    9844.53,
    0,
    0,
    13922.3,
    8155.47,
    9844.53,
    13922.3,
    16310.9
};

TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test1_4_4)
{
    // Given
    Simulation simulation(FileTypeEnum::TEXT, "../../../Input/Grids/Test1_4_4.txt");

    // When
    simulation.Run();

    // Then
    for (int i = 0; i < 16; i++)
        EXPECT_NEAR(globalPVectorFixture_1_4_4[i], simulation.m_Grid.m_GlobalPVector.GetElement(i, 0), EPSILON);
}

TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test2_4_4)
{
    // Given
    Simulation simulation(FileTypeEnum::TEXT, "../../../Input/Grids/Test2_4_4_MixGrid.txt");

    // When
    simulation.Run();

    // Then
    for (int i = 0; i < 16; i++)
        EXPECT_NEAR(globalPVectorFixture_2_4_4[i], simulation.m_Grid.m_GlobalPVector.GetElement(i, 0), EPSILON);
}
