//
// Created by vincent on 03/04/17.
//

#include <fstream>
#include <map>
#include <unistd.h>
#include "Snake.hpp"

const std::string			        		arcade::Snake::S_MAP_PATH = "./resc/snake/map";
const std::map<arcade::TileType,
	std::string>			    			arcade::Snake::S_TILE_RESOURCES = {
	{arcade::TileType::EMPTY, "./gfx/snake/ground"},
	{arcade::TileType::BLOCK, "./gfx/snake/wall"},
	{arcade::TileType::POWERUP, "./gfx/snake/apple"},
	{arcade::TileType::EVIL_DUDE, "./gfx/snake/snake"},
};

const std::map<char, arcade::TileType>				arcade::Snake::S_STRING_TO_TILE = {
	{'1', TileType::BLOCK},
	{'0', TileType::EMPTY},
};

const std::map<arcade::CommandType,
	arcade::CommandType>					arcade::Snake::S_FORBIDEN_COMMAND = {
	{arcade::CommandType::GO_UP, arcade::CommandType::GO_DOWN},
	{arcade::CommandType::GO_DOWN, arcade::CommandType::GO_UP},
	{arcade::CommandType::GO_RIGHT, arcade::CommandType::GO_LEFT},
	{arcade::CommandType::GO_LEFT, arcade::CommandType::GO_RIGHT}
};

const std::map<arcade::IEvenement::KeyCode , arcade::CommandType>			arcade::Snake::S_BINDING = {
	{arcade::IEvenement::KeyCode::Key_Z, arcade::CommandType::GO_UP},
	{arcade::IEvenement::KeyCode::Key_S, arcade::CommandType::GO_DOWN},
	{arcade::IEvenement::KeyCode::Key_D, arcade::CommandType::GO_RIGHT},
	{arcade::IEvenement::KeyCode::Key_Q, arcade::CommandType::GO_LEFT}
};

const unsigned long						arcade::Snake::S_SNAKE_HEAD = 0;
const unsigned long						arcade::Snake::S_DEFAULT_SNAKE_LENGTH = 4;

arcade::Snake::Snake(void *handle)
	: _objects(), _lib(NULL), _map(), _score(0), _snake(), _map_size({0, 0}), _handle(handle),
	  _lib_name("lib_arcade_snake"), _gen(getpid()), _dis_width(0, 0), _dis_height(0, 0)
{
  _snake.ct = arcade::CommandType::PLAY;
  _snake.length = 0;
  _snake.direction = Direction::UNKNOWN;

  _actions = {
	  {arcade::TileType::BLOCK, [&]() -> void { _dead(); }},
	  {arcade::TileType::EVIL_DUDE, [&]() -> void { _dead(); }},
	  {arcade::TileType::EMPTY, [&]() -> void { _move(); }},
	  {arcade::TileType::POWERUP, [&]() -> void { _powerUp(); }}
  };
}

arcade::Snake::~Snake()
{
  freeSharedData();
}

void* arcade::Snake::getHandle() const { return (_handle);}

std::string const& arcade::Snake::getName() const { return (_lib_name);}

void arcade::Snake::freeSharedData()
{
  if (_objects)
    _objects->clear();
  _objects.reset();
}

void 			arcade::Snake::initGame(arcade::IGraphicalLib *lib,
						    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> & objects)
{
/*    if (lib == NULL)
        throw std::runtime_error("Not able to init the game with a null graphical library.");*/
  _lib = lib;
  if (!(_win = _lib->getWindows().get()))
    throw std::runtime_error("You have to init the window before init the game.");
  _objects = objects;
  createMap();
}

uint64_t 		arcade::Snake::getScore() const
{
  return (_score);
}

void 			arcade::Snake::gameTurn()
{
  _refreshObjects();
}

// private

void 			arcade::Snake::createMap()
{
  std::ifstream 	fs;
  std::string         	str;

  fs.open(S_MAP_PATH);
  if (!(fs.is_open()))
    throw std::runtime_error("Not able to create the map.");

  std::getline(fs, str);
  if (fs.eof() || !std::all_of(str.begin(), str.end(), [](char c){return std::isdigit(c);}))
    throw std::runtime_error("The map's width is invalid.");
  _map_size.setX(std::stoi(str));

  std::getline(fs, str);
  if (fs.eof() || !std::all_of(str.begin(), str.end(), [](char c){return std::isdigit(c);}))
    throw std::runtime_error("The map's height is invalid.");
  _map_size.setY(std::stoi(str));

  if (_map_size.getX() < 10 || _map_size.getX() > 100 || _map_size.getY() < 10 || _map_size.getY() > 100)
    throw std::runtime_error("Invalid map's size.");

  _dis_width = std::uniform_int_distribution<int>(0, _map_size.getX() - 1);
  _dis_height = std::uniform_int_distribution<int>(0, _map_size.getY() - 1);

  getline(fs, str);
  arcade::TileType tt;
  int32_t x, y = 0;
  arcade::Vector3d v(0, 0);
  while (!fs.eof())
    {
      _map.push_back(std::vector<arcade::TileType>());
      x = 0;
      for (const auto &it : str)
	{
	  try {
	      tt = S_STRING_TO_TILE.at(it);
	      std::shared_ptr<arcade::IObject> obj = _lib->initObject(((tt == arcade::TileType::BLOCK) ? ("wall") : ("ground")),
								      S_TILE_RESOURCES.at(tt));
	      v.setX(x);
	      v.setY(y);
	      obj->setPosition(v);
	      _objects->push_back(obj);
	      _map[_map.size() - 1].push_back(tt);
	    } catch (const std::exception &e) {
	      throw std::runtime_error("Invalid map. " + std::to_string(it) + " " + std::string(e.what()));
	    }
	  x += 1;
	}
      if ((int)_map[_map.size() - 1].size() != _map_size.getX())
	throw std::runtime_error("Invalid map.");
      getline(fs, str);
      y += 1;
    }
  if ((int)_map.size() != _map_size.getY())
    throw std::runtime_error("Invalid map.");
  fs.close();
  _initPowerUp();
  _initPowerUp();
  _initPowerUp();
  _initSnake();
}

void arcade::Snake::_initSnake()
{
  unsigned int i = 0;
  Position p;

  p.x = _map_size.getX() / 2;
  p.y = _map_size.getY() / 2;
  while (i < S_DEFAULT_SNAKE_LENGTH)
    {
      _snake.body.push_back(p);
      _map[p.y][p.x] = TileType::EVIL_DUDE;
      i += 1;
      p.x -= 1;
    }
}

void arcade::Snake::initGraphicalLib(arcade::IGraphicalLib *)
{

}

void arcade::Snake::getNotified(IEvenement const &event)
{
  IEvenement::KeyCode kc = event.getKeyCode();
  arcade::Vector3d tmp(0, 0);

  try
    {
      if (kc != IEvenement::KeyCode::Key_Undefined && S_BINDING.at(kc) != S_FORBIDEN_COMMAND.at(_snake.ct))
	{
	  _snake.ct = S_BINDING.at(kc);
	}
    } catch (const std::exception &)
    { _snake.ct = S_BINDING.at(kc); }

  tmp.setX(_snake.body[_snake.body.size() - 1].x);
  tmp.setY(_snake.body[_snake.body.size() - 1].y);
  if (_snake.ct != CommandType::PLAY)
    {
      for (unsigned int i = _snake.body.size() - 1; i != 0; i--)
	{
	  _snake.body[i].x = _snake.body[i - 1].x;
	  _snake.body[i].y = _snake.body[i - 1].y;
	  _map[_snake.body[i].y][_snake.body[i].x] = TileType::EVIL_DUDE;
	}
      _map[tmp.getY()][tmp.getX()] = TileType::EMPTY;
    }
  if (_snake.ct == arcade::CommandType::GO_UP)
    _snake.body[S_SNAKE_HEAD].y -= 1;
  else if (_snake.ct == arcade::CommandType::GO_DOWN)
      _snake.body[S_SNAKE_HEAD].y += 1;
    else if (_snake.ct == arcade::CommandType::GO_LEFT)
	_snake.body[S_SNAKE_HEAD].x -= 1;
      else if (_snake.ct == arcade::CommandType::GO_RIGHT)
	  _snake.body[S_SNAKE_HEAD].x += 1;
  if (_snake.ct != arcade::CommandType::PLAY)
  	(_actions[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
  if (_snake.body[S_SNAKE_HEAD].y >= _map_size.getY() || _snake.body[S_SNAKE_HEAD].x >= _map_size.getX())
    {
      _map[_snake.body[S_SNAKE_HEAD].y % _map_size.getY()][_snake.body[S_SNAKE_HEAD].x % _map_size.getX()] = TileType::EVIL_DUDE;
      _refreshObjects();
      _win->refresh();
      sleep(1);
      throw std::runtime_error("Game Over !");
    }
}

arcade::ILibrairy *arcade::getNewLib(void *handle)
{
  return (new arcade::Snake(handle));
}

void arcade::Snake::_initPowerUp()
{
  arcade::Position p;
  p.x = static_cast<uint16_t>(_dis_width(_gen));
  p.y = static_cast<uint16_t>(_dis_height(_gen));
  while (_map[p.y][p.x] != arcade::TileType::EMPTY)
    {
      p.x = static_cast<uint16_t>(_dis_width(_gen));
      p.y = static_cast<uint16_t>(_dis_height(_gen));
    }
  _map[p.y][p.x] = arcade::TileType::POWERUP;
}

void arcade::Snake::_refreshObjects()
{
  arcade::Vector3d v(0,0);

  for (auto &it : *_objects)
    {
      v = it->getPosition();
      it->setVisual(S_TILE_RESOURCES.at(_map[v.getY()][v.getX()]));
    }
}

void arcade::Snake::_dead()
{
  _map[_snake.body[S_SNAKE_HEAD].y % _map_size.getY()][_snake.body[S_SNAKE_HEAD].x % _map_size.getX()] = TileType::EVIL_DUDE;
  _refreshObjects();
  _lib->getWindows()->refresh();
  sleep(1);
  throw std::runtime_error("Game Over !");
}

void arcade::Snake::_move()
{
  _map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x] = TileType::EVIL_DUDE;
}

void arcade::Snake::_powerUp()
{
  arcade::Position p;

  p.x = _snake.body[_snake.body.size() - 1].x;
  p.y = _snake.body[_snake.body.size() - 1].y;

  if (p.x - 1 >= 0 && _map[p.y][p.x - 1] == arcade::TileType::EMPTY)
      _snake.body.push_back({static_cast<uint16_t >(p.x - 1), p.y});
  else if (p.y - 1 >= 0 && _map[p.y - 1][p.x] == arcade::TileType::EMPTY)
      _snake.body.push_back({p.x, static_cast<uint16_t >(p.y - 1)});
    else if (p.y + 1 < _map_size.getY() && _map[p.y + 1][p.x] == arcade::TileType::EMPTY)
	_snake.body.push_back({p.x, static_cast<uint16_t >(p.y + 1)});
  _initPowerUp();
}