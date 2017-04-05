//
// Created by vincent on 03/04/17.
//

#include <fstream>
#include <map>
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
const unsigned long						arcade::Snake::S_SNAKE_HEAD = 0;

arcade::Snake::Snake(void *handle)
	: _objects(), _lib(NULL), _map(), _score(0), _snake(), _map_size({0, 0}), _handle(handle),
	  _lib_name("lib_arcade_snake")
{
  _snake.ct = arcade::CommandType::PLAY;
  _snake.body.push_back({2,1});
  _snake.body.push_back({1,1});
  _snake.length = 0;
  _snake.direction = Direction::UNKNOWN;
}

arcade::Snake::~Snake()
{
  _objects.reset();
}

void* arcade::Snake::getHandle() const { return (_handle);}

std::string const& arcade::Snake::getName() const { return (_lib_name);}

void arcade::Snake::freeSharedData() {}

void 			arcade::Snake::initGame(arcade::IGraphicalLib *lib,
						    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> & objects)
{
/*    if (lib == NULL)
        throw std::runtime_error("Not able to init the game with a null graphical library.");*/
  _lib = lib;
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
  if (_map_size.getX() <= 0 || _map_size.getX() > 100 || _map_size.getY() <= 0 || _map_size.getY() > 100)
    throw std::runtime_error("Invalid map's size.");
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
	      throw std::runtime_error("Invalid map1. " + std::to_string(it) + " " + std::string(e.what()));
	    }
	  x += 1;
	}
      if ((int)_map[_map.size() - 1].size() != _map_size.getX())
	throw std::runtime_error("Invalid map2.");
      getline(fs, str);
      y += 1;
    }
  if ((int)_map.size() != _map_size.getY())
    throw std::runtime_error("Invalid map3.");
  fs.close();
  _map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x] = TileType::EVIL_DUDE;
  _map[_snake.body[1].y][_snake.body[1].x] = TileType::EVIL_DUDE;
}

void arcade::Snake::initGraphicalLib(arcade::IGraphicalLib *)
{

}

void arcade::Snake::getNotified(IEvenement const &event)
{
  IEvenement::KeyCode kc = event.getKeyCode();
  arcade::Vector3d tmp(_snake.body[S_SNAKE_HEAD].x, _snake.body[S_SNAKE_HEAD].y);

  if (kc != IEvenement::KeyCode::Key_Undefined)
    _kc = kc;
  for (unsigned int i = 1 ; i < _snake.body.size() ; i++)
    {
      tmp.setX(_snake.body[i].x);
      tmp.setY(_snake.body[i].y);
      _snake.body[i].x = _snake.body[i - 1].x;
      _snake.body[i].y = _snake.body[i - 1].y;
      _map[_snake.body[i].y][_snake.body[i].x] = TileType::EVIL_DUDE;
    }
  _map[tmp.getY()][tmp.getX()] = TileType::EMPTY;
  if (_kc == IEvenement::KeyCode::Key_Z)
    _snake.body[S_SNAKE_HEAD].y -= 1;
  else if (_kc == IEvenement::KeyCode::Key_S)
      _snake.body[S_SNAKE_HEAD].y += 1;
    else if (_kc == IEvenement::KeyCode::Key_Q)
	_snake.body[S_SNAKE_HEAD].x -= 1;
      else if (_kc == IEvenement::KeyCode::Key_D)
	  _snake.body[S_SNAKE_HEAD].x += 1;
  _map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x] = TileType::EVIL_DUDE;
}

arcade::ILibrairy *arcade::getNewLib(void *handle)
{
  return (new arcade::Snake(handle));
}

void arcade::Snake::_fillTheMap()
{

}

void arcade::Snake::_refreshObjects()
{
  arcade::Vector3d v(0,0);

  for (auto &it : *_objects)
    {
      v = it->getPosition();
      _lib->setVisual(it, S_TILE_RESOURCES.at(_map[v.getY()][v.getX()]));
    }
}