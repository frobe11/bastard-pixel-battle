// #include "Session.h"
// #include "gtest/gtest.h"
// #include <chrono>
// #include <thread>

// class SessionTest : public ::testing::Test
// {
// protected:
//     const size_t height = 800;
//     const size_t width = 800;

//     std::shared_ptr<Session> session;
//     std::shared_ptr<PixelGrid> pg;
//     std::shared_ptr<const std::vector<std::vector<Color>>> grid;
//     void SetUp() override
//     {
//         session = std::make_shared<Session>(width,height);
//         pg = session->getPixelGrid();
//         grid = pg->getGrid();
//     }

//     void TearDown() override
//     {
//     }
// };

// TEST_F(SessionTest, Session_Constructor_FieldsNotEmpty)
// {
//     EXPECT_NE(*(session->getSessionID()), "");
//     EXPECT_NE(session->getSessionID().get(), nullptr);

// }

// TEST_F(SessionTest, PixelGrid_setPixelBlack_PixelIsBlack)
// {
//     const auto color = "#000000";
//     const size_t x = 16;
//     const size_t y = 90;
//     EXPECT_EQ((*grid)[y][x], "#ffffff");
//     pg->setPixel(x, y, color);
//     EXPECT_EQ((*grid)[y][x], "#000000");
// }

// TEST_F(SessionTest, PixelGrid_HeightWidth_AsAsigned)
// {

//     EXPECT_EQ(pg->getHeight(), height);
//     EXPECT_EQ(pg->getWidth(), width);
//     EXPECT_EQ((*grid)[0][0], "#ffffff");
// }