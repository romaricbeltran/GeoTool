#include <gtest/gtest.h>
#include <glm/glm.hpp>

TEST(Vec3Test, Addition) {
    glm::vec3 a(1, 2, 3);
    glm::vec3 b(4, 5, 6);
    glm::vec3 result = a + b;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
