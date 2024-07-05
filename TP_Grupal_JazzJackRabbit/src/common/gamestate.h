#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <sstream>
#include <cstdint>

/*
  Wire format:
  GameState: <u16 total_size><u8 type>
    if(type == 0) <u16 client_id><AvailableGame[] available_games>
    if(type == 1) <u8 background><u16 sec_left><u8 player_count><Player[player_count]><RenderableGameEntity[] entities>
  RenderableGameEntity: <u32 x><u32 y><u8 entity><u8 animation_state><u8 animation_tick><i8 direction>
  Player: <u16 id><u8 health><u16 points><RenderableGameEntity entity><u8 namesize><char[namesize] name>
  AvailableGame: <u16 id><u8 players_joined><u8 players_needed>
  Where x and y are fixed-point (16/16) representations of the coordinates
*/

struct RenderableGameEntity {
  float x;
  float y;
  uint8_t entity; // which entity?
  uint8_t animation_state; // doing which animation?
  uint8_t animation_tick; // how far into the animation?
  int8_t direction; // -1 = left; 1 = right
};

struct Player {
  uint16_t id;
  uint8_t health;
  uint16_t points;
  RenderableGameEntity entity;
  std::string name;
  uint8_t bulletType;
  int8_t currentAmmo;
};

struct AvailableGame {
  uint16_t id;
  uint8_t players_joined;
  uint8_t players_needed;
};

enum class MsgType: uint8_t {
  GameList,
  GameState
};

class GameState {
  private:
    static RenderableGameEntity deserializeEntity(std::stringstream& from);
    static void serializeEntity(std::stringstream& into, RenderableGameEntity& entity);
    static AvailableGame deserializeAvailableGame(std::stringstream& from);
    static void serializeAvailableGame(std::stringstream& into, AvailableGame& game);
    static Player deserializePlayer(std::stringstream& from);
    static void serializePlayer(std::stringstream& into, Player& player);
    explicit GameState(
      MsgType type,
      uint8_t background,
      uint16_t sec_left,
      uint16_t clientID,
      std::vector<Player> players,
      std::vector<RenderableGameEntity> entities,
      std::vector<AvailableGame> available_games
    );
  public:
    GameState();
    MsgType type;
    uint8_t background;
    uint16_t sec_left;
    uint16_t clientID;
    std::vector<Player> players;
    std::vector<RenderableGameEntity> entities;
    std::vector<AvailableGame> available_games;
    static GameState deserialize(std::stringstream& from);
    static GameState makeGameList(uint16_t clientID, std::vector<AvailableGame> available_games);
    static GameState makeGameState(uint8_t background, uint16_t sec_left, std::vector<Player> players, std::vector<RenderableGameEntity> entities);
    std::vector<char> serialize();
};

#define HEADER_SIZE 1
#define GAMELIST_SIZE (HEADER_SIZE + 2)
#define GAMESTATE_SIZE (HEADER_SIZE + 1 + 2 + 1)
#define RENDERABLE_GAME_ENTITY_SIZE (4 + 4 + 1 + 1 + 1 + 1)
#define PLAYER_SIZE (2 + 1 + 2 + RENDERABLE_GAME_ENTITY_SIZE + 1 + 1+ 1) // + name.size()
#define AVAILABLEGAME_SIZE (2 + 1 + 1)

#endif
