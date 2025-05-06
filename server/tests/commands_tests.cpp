// #include "Command.h"
// #include "Color.h"
// #include "gtest/gtest.h"
// #include <chrono>
// #include <thread>

// class CommandsTest : public ::testing::Test
// {
// protected:
//     const size_t height = 800;
//     const size_t width = 800;
//     const size_t x = 82;
//     const size_t y = 52;
//     const std::string color = "#f0f0f0";

//     std::shared_ptr<Session> session;
//     std::shared_ptr<PixelGrid> pg;
//     std::shared_ptr<const std::vector<std::vector<Color>>> grid;
//     std::shared_ptr<const std::string> sessionId;
//     std::shared_ptr<CommandgetGrid> commandgetGrid;
//     std::shared_ptr<CommandsetPixel> commandsetPixel;
//     std::shared_ptr<CommandNewGame> commandNewGame;
//     std::string connectionId; 
//     void SetUp() override
//     {
//         sessionId = SessionHolder::CreateSession(width, height);
//         session = SessionHolder::FindSession(*sessionId);
//         pg = session->getPixelGrid();
//         grid = pg->getGrid();
//         connectionId = "id";

//         commandgetGrid = std::make_shared<CommandgetGrid>(*sessionId, connectionId);
//         commandsetPixel = std::make_shared<CommandsetPixel>(*sessionId, connectionId, x, y, color);
//         commandNewGame = std::make_shared<CommandNewGame>(connectionId, width, height);
//     }

//     void TearDown() override
//     {
//     }
// };

// TEST_F(CommandsTest, CommandgetGrid_Constructor_FieldsNotEmpty) {
//     EXPECT_EQ(commandgetGrid->getConnectionID(), connectionId);
//     EXPECT_EQ(commandgetGrid->getSessionID(), sessionId);
// }

// TEST_F(CommandsTest, CommandsetPixel_Constructor_FieldsNotEmpty)
// {
//     EXPECT_EQ(commandsetPixel->getConnectionID(), connectionId);
//     EXPECT_EQ(commandsetPixel->getSessionID(), sessionId);
//     EXPECT_EQ(commandsetPixel->getColor(), color);
//     EXPECT_EQ(commandsetPixel->getX(), x);
//     EXPECT_EQ(commandsetPixel->getY(), y);
// }