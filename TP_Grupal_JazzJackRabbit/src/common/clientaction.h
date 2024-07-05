#ifndef CLIENTACTION_H
#define CLIENTACTION_H

#include <vector>
#include <sstream>
#include <cstdint>

// <u8 size><u8 action>
// if (action == Create) <u16 characterID><u8 namesize><char[namesize] name>
// if (action == Join) <u16 gameID><u16 characterID><u8 namesize><char[namesize] name>
// if (action == Left) <u8 is_fast>
// if (action == Right) <u8 is_fast>

enum class Action : uint8_t
{
  None = '\0',     // guard
  Create = 'C',    // Create(characterID)
  List = 'L',      // List()
  Join = 'J',      // Join(gameID, characterID, string name)
  Quit = 'Q',      // Quit()
  Left = 'A',      // Left(is_fast)
  Right = 'D',     // Right(is_fast)
  Down = 'S',      // Down()
  Up = 'W',        // Up()
  Shoot = 'P',     // Shoot()
  Jump = ' ',      // Jump()
  Combo = 'X',     // Combo()
  SwitchGun = 'E', // switchGun()
  StopMoving = 'd',
  StopShooting = 'a',
  Ammo = 'F' // AmmoFull(gunType)
};

class ClientAction
{
private:
  uint8_t getSize();

public:
  Action action;
  int data;
  int data2;
  std::string name;
  std::string path;
  ClientAction();
  explicit ClientAction(Action action);
  explicit ClientAction(Action action, int data);
  explicit ClientAction(Action action, int data, int data2, std::string name);
  explicit ClientAction(Action action, int data, int data2, std::string name, std::string path);
  explicit ClientAction(Action action, int data, std::string name);
  explicit ClientAction(Action action, int data, std::string name, std::string path);
  static ClientAction deserialize(std::stringstream &from);
  std::vector<char> serialize();
};

using ClientMessage = std::pair<int, ClientAction>;

#endif
