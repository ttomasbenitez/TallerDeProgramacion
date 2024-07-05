#include "clientaction.h"

ClientAction::ClientAction() : action(Action::None) {}
ClientAction::ClientAction(Action action) : action(action), data(0), data2(0) {}
ClientAction::ClientAction(Action action, int data) : action(action), data(data), data2(0) {}
ClientAction::ClientAction(Action action, int data, int data2, std::string name) : action(action), data(data), data2(data2), name(name) {}
ClientAction::ClientAction(Action action, int data, int data2, std::string name, std::string path) : action(action), data(data), data2(data2), name(name), path(path) {}
ClientAction::ClientAction(Action action, int data, std::string name) : action(action), data(data), name(name) {}
ClientAction::ClientAction(Action action, int data, std::string name, std::string path) : action(action), data(data), name(name), path(path) {}

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

ClientAction ClientAction::deserialize(std::stringstream &from)
{
  Action action = (Action)deserializeValue<uint8_t>(from);
  int data = 0, data2 = 0;
  std::string name;
  std::string path;
  switch (action)
  {
  case Action::Create:
  { // b clientaction.cpp:34
    data = be16toh(deserializeValue<uint16_t>(from));
    int size = deserializeValue<uint8_t>(from);
    while (size--)
      name.push_back(deserializeValue<uint8_t>(from));
    size = deserializeValue<uint8_t>(from);
    while (size--)
      path.push_back(deserializeValue<uint8_t>(from));
    break;
  }
  case Action::Join:
  {
    data = be16toh(deserializeValue<uint16_t>(from));
    data2 = be16toh(deserializeValue<uint16_t>(from));
    int size = deserializeValue<uint8_t>(from);
    while (size--)
      name.push_back(deserializeValue<uint8_t>(from));
    break;
  }
  case Action::Left:
  {
    data = deserializeValue<uint8_t>(from);
    break;
  }
  case Action::Right:
  {
    data = deserializeValue<uint8_t>(from);
    break;
  }
  default:
    break;
  }
  ClientAction ca(action, data, data2, name, path);
  return ca;
}

std::vector<char> ClientAction::serialize()
{
  std::stringstream ss;
  serializeValue<uint8_t>(ss, this->getSize());
  serializeValue<uint8_t>(ss, (uint8_t)this->action);
  switch (this->action)
  {
  case Action::Create:
  {
    serializeValue<uint16_t>(ss, (uint16_t)htobe16(this->data));
    serializeValue<uint8_t>(ss, name.size());
    for (char c : name)
      serializeValue<uint8_t>(ss, c);
    serializeValue<uint8_t>(ss, path.size());
    for (char c : path)
      serializeValue<uint8_t>(ss, c);
    break;
  }
  case Action::Join:
  {
    serializeValue<uint16_t>(ss, (uint16_t)htobe16(this->data));
    serializeValue<uint16_t>(ss, (uint16_t)htobe16(this->data2));
    serializeValue<uint8_t>(ss, name.size());
    for (char c : name)
      serializeValue<uint8_t>(ss, c);
    break;
  }
  case Action::Left:
  {
    serializeValue<uint8_t>(ss, (uint8_t)this->data);
    break;
  }
  case Action::Right:
  {
    serializeValue<uint8_t>(ss, (uint8_t)this->data);
    break;
  }
  default:
    break;
  }
  auto str = ss.str();
  std::vector<char> vec(str.begin(), str.end());
  return vec;
}

uint8_t ClientAction::getSize()
{
  uint8_t size = 1; // type
  switch (this->action)
  {
  case Action::Create:
  {
    size += 2 + 1 + name.size() + path.size() + 1;
    break;
  }
  case Action::Join:
  {
    size += 2 + 2 + 1 + name.size();
    break;
  }
  case Action::Left:
  {
    size += 1;
    break;
  }
  case Action::Right:
  {
    size += 1;
    break;
  }
  default:
    break;
  }
  return size;
}
