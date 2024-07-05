#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "clientaction.h"
#include "gamestate.h"

TEST(SerdeTest, ClientActionNoParams) {
  ClientAction act(Action::Up);
  auto buf = act.serialize();
  int size = buf[0];
  std::string msg(buf.data() + 1, size);
  std::stringstream ss(msg);
  auto act2 = ClientAction::deserialize(ss);
  EXPECT_EQ(act.action, act2.action);
}

TEST(SerdeTest, ClientActionOneParam) {
  ClientAction act(Action::Right, true);
  auto buf = act.serialize();
  int size = buf[0];
  std::string msg(buf.data() + 1, size);
  std::stringstream ss(msg);
  auto act2 = ClientAction::deserialize(ss);
  EXPECT_EQ(act.action, act2.action);
  EXPECT_EQ(act.data, act2.data);
}

TEST(SerdeTest, ClientActionCreate) {
  ClientAction act(Action::Create, 1, "thename");
  auto buf = act.serialize();
  int size = buf[0];
  std::string msg(buf.data() + 1, size);
  std::stringstream ss(msg);
  auto act2 = ClientAction::deserialize(ss);
  EXPECT_EQ(act.action, act2.action);
  EXPECT_EQ(act.data, act2.data);
  EXPECT_EQ(act.name, act2.name);
}

TEST(SerdeTest, ClientActionJoin) {
  ClientAction act(Action::Join, 1, 2, "thename");
  auto buf = act.serialize();
  int size = buf[0];
  std::string msg(buf.data() + 1, size);
  std::stringstream ss(msg);
  auto act2 = ClientAction::deserialize(ss);
  EXPECT_EQ(act.action, act2.action);
  EXPECT_EQ(act.data, act2.data);
  EXPECT_EQ(act.data2, act2.data2);
  EXPECT_EQ(act.name, act2.name);
}

TEST(SerdeTest, GameStateGameList) {
  auto gl = GameState::makeGameList(10, {
    AvailableGame { 1, 2, 3 },
    AvailableGame { 4, 5, 6 }
  });
  auto vec = gl.serialize();
  uint16_t size = be16toh(*(uint16_t*)vec.data());
  EXPECT_EQ(size, vec.size() - 2);
  std::string s(vec.data() + 2, size);
  std::stringstream ss(s);
  GameState dl = GameState::deserialize(ss);
  EXPECT_EQ(gl.type, dl.type);
  EXPECT_EQ(gl.clientID, dl.clientID);
  EXPECT_EQ(gl.available_games.size(), dl.available_games.size());
}

TEST(SerdeTest, GameStateGameState) {
  auto gl = GameState::makeGameState(15, 200, {
    Player { 1, 2, 13, RenderableGameEntity { 100, 500, 1, 4, 9, 0 }, "myname"},
    Player { 3, 1, 11, RenderableGameEntity { 200, 400, 2, 8, 8, 1 }, "othername"}
  }, {
    RenderableGameEntity { 4.3, 2.7, 10, 12, 5,  -1 },
    RenderableGameEntity { 0.2, 1.4,  0,  1, 12, +1 }
  });
  auto vec = gl.serialize();
  uint16_t size = be16toh(*(uint16_t*)vec.data());
  EXPECT_EQ(size, vec.size() - 2);
  std::string s(vec.data() + 2, size);
  std::stringstream info(s);
  GameState dl = GameState::deserialize(info);
  EXPECT_EQ(gl.type, dl.type);
  EXPECT_EQ(gl.background, dl.background);
  EXPECT_EQ(gl.sec_left, dl.sec_left);
  EXPECT_EQ(gl.players.size(), dl.players.size());
  EXPECT_EQ(gl.entities.size(), dl.entities.size());
  EXPECT_EQ(gl.players[0].name, dl.players[0].name);
  EXPECT_EQ(gl.players[1].name, dl.players[1].name);
  EXPECT_EQ(gl.players[1].health, dl.players[1].health);
  EXPECT_EQ(gl.players[1].entity.y, dl.players[1].entity.y);
}
