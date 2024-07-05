#include "gamestate.h"

#include <vector>
#include <cstdint>
#include <sstream>
#include <iostream>

GameState::GameState(
    MsgType type,
    uint8_t background,
    uint16_t sec_left,
    uint16_t clientID,
    std::vector<Player> players,
    std::vector<RenderableGameEntity> entities,
    std::vector<AvailableGame> available_games) : type(type), background(background), sec_left(sec_left), clientID(clientID), players(players), entities(entities), available_games(available_games) {}

GameState::GameState() {}
#define FLOAT_ENCODE_FACTOR double(1 << 16)

template <typename T>
static void serializeValue(std::stringstream &into, const T val)
{
  into.write(reinterpret_cast<const char *>(&val), sizeof(T));
}

template <typename T>
static T deserializeValue(std::stringstream &from)
{
  T val;
  from.read(reinterpret_cast<char *>(&val), sizeof(T));
  return val;
}

static void serializeFloat(std::stringstream &into, float f)
{
  int v = f * FLOAT_ENCODE_FACTOR;
  serializeValue<int>(into, htobe32(v));
}

static float deserializeFloat(std::stringstream &from)
{
  int v = deserializeValue<int>(from);
  v = be32toh(v);
  return float(v) / FLOAT_ENCODE_FACTOR;
}

GameState GameState::deserialize(std::stringstream &from)
{
  MsgType type = deserializeValue<MsgType>(from);
  uint8_t background = 0;
  uint16_t sec_left = 0;
  uint16_t clientID = 0;
  std::vector<Player> players;
  std::vector<RenderableGameEntity> entities;
  std::vector<AvailableGame> available_games;
  if (type == MsgType::GameList)
  {
    clientID = be16toh(deserializeValue<uint16_t>(from));
    while (from)
    {
      auto ag = GameState::deserializeAvailableGame(from);
      if (from.fail()) break;
      available_games.push_back(ag);
    }
  }
  if (type == MsgType::GameState)
  {
    background = deserializeValue<uint8_t>(from);
    sec_left = be16toh(deserializeValue<uint16_t>(from));
    auto player_count = deserializeValue<uint8_t>(from);
    for (auto i = 0; i < player_count; i++)
      players.push_back(GameState::deserializePlayer(from));
    while (from)
    {
      auto ent = GameState::deserializeEntity(from);
      if (from.fail()) break;
      entities.push_back(ent);
    }
  }
  GameState gs(type, background, sec_left, clientID, players, entities, available_games);
  return gs;
}

RenderableGameEntity GameState::deserializeEntity(std::stringstream &from)
{
  float x = deserializeFloat(from);
  float y = deserializeFloat(from);
  uint8_t entity = deserializeValue<uint8_t>(from);
  uint8_t animation_state = deserializeValue<uint8_t>(from);
  uint8_t animation_tick = deserializeValue<uint8_t>(from);
  int8_t direction = deserializeValue<int8_t>(from);
  return RenderableGameEntity{
      x,
      y,
      entity,
      animation_state,
      animation_tick,
      direction};
}

std::vector<char> GameState::serialize()
{
  std::stringstream ss;
  if (type == MsgType::GameState)
  {
    uint16_t size = GAMESTATE_SIZE + players.size() * PLAYER_SIZE + entities.size() * RENDERABLE_GAME_ENTITY_SIZE;
    for (auto &player : players)
      size += player.name.size();
    serializeValue<uint16_t>(ss, htobe16(size));
    serializeValue<uint8_t>(ss, (uint8_t)type);
    serializeValue<uint8_t>(ss, this->background);
    serializeValue<uint16_t>(ss, htobe16(sec_left));
    serializeValue<uint8_t>(ss, players.size());
    for (auto &player : players)
      this->serializePlayer(ss, player);
    for (auto &entity : entities)
      this->serializeEntity(ss, entity);
    auto str = ss.str();
    std::vector<char> vec(str.begin(), str.end());
    return vec;
  }
  if (type == MsgType::GameList)
  {
    uint16_t size = GAMELIST_SIZE + available_games.size() * AVAILABLEGAME_SIZE;
    serializeValue<uint16_t>(ss, htobe16(size));
    serializeValue<uint8_t>(ss, (uint8_t)type);
    serializeValue<uint16_t>(ss, htobe16(clientID));
    for (auto &game : available_games)
      this->serializeAvailableGame(ss, game);
    auto str = ss.str();
    std::vector<char> vec(str.begin(), str.end());
    return vec;
  }
  throw std::runtime_error("Attempted to serialize unknown MsgType.");
}

void GameState::serializeEntity(std::stringstream &into, RenderableGameEntity &entity)
{
  serializeFloat(into, entity.x);
  serializeFloat(into, entity.y);
  serializeValue<uint8_t>(into, entity.entity);
  serializeValue<uint8_t>(into, entity.animation_state);
  serializeValue<uint8_t>(into, entity.animation_tick);
  serializeValue<int8_t>(into, entity.direction);
}

AvailableGame GameState::deserializeAvailableGame(std::stringstream &from)
{
  uint16_t id = be16toh(deserializeValue<uint16_t>(from));
  uint8_t players_joined = deserializeValue<uint8_t>(from);
  uint8_t players_needed = deserializeValue<uint8_t>(from);
  return AvailableGame{id, players_joined, players_needed};
}

void GameState::serializeAvailableGame(std::stringstream &into, AvailableGame &game)
{
  serializeValue<uint16_t>(into, htobe16(game.id));
  serializeValue<uint8_t>(into, game.players_joined);
  serializeValue<uint8_t>(into, game.players_needed);
}

GameState GameState::makeGameList(uint16_t clientID, std::vector<AvailableGame> available_games)
{
  std::vector<RenderableGameEntity> el;
  std::vector<Player> pl;
  GameState gs(MsgType::GameList, 0, 0, clientID, pl, el, available_games);
  return gs;
}

GameState GameState::makeGameState(uint8_t background, uint16_t sec_left, std::vector<Player> players, std::vector<RenderableGameEntity> entities)
{
  std::vector<AvailableGame> ag;
  GameState gs(MsgType::GameState, background, sec_left, 0, players, entities, ag);
  return gs;
}

Player GameState::deserializePlayer(std::stringstream &from)
{
  uint16_t id = be16toh(deserializeValue<uint16_t>(from));
  uint8_t health = deserializeValue<uint8_t>(from);
  uint16_t points = be16toh(deserializeValue<uint16_t>(from));
  RenderableGameEntity ent = deserializeEntity(from);
  int size = deserializeValue<uint8_t>(from);
  std::string name;
  while (size--)
    name.push_back(deserializeValue<char>(from));
  uint8_t bulletType = deserializeValue<uint8_t>(from);
  int8_t currentAmmo = deserializeValue<int8_t>(from);
  return Player{id, health, points, ent, name, bulletType, currentAmmo};
}

void GameState::serializePlayer(std::stringstream &into, Player &player)
{
  serializeValue<uint16_t>(into, htobe16(player.id));
  serializeValue<uint8_t>(into, player.health);
  serializeValue<uint16_t>(into, htobe16(player.points));
  serializeEntity(into, player.entity);
  serializeValue<uint8_t>(into, player.name.size());
  for (char c : player.name)
    serializeValue<uint8_t>(into, c);
  serializeValue<uint8_t>(into, player.bulletType);
  serializeValue<int8_t>(into, player.currentAmmo);
}
