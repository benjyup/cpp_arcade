//
// Created by vincent on 03/04/17.
//

#include <fstream>
#include <map>
#include <unistd.h>
#include "Snake.hpp"

const std::string			        		arcade::Snake::S_MAP_PATH 	= "./resc/snake/map";
const std::string						arcade::Snake::S_HEAD_RESOURCES = "./gfx/snake/snake_head";
const std::string						arcade::Snake::S_TAIL_RESOURCES = "./gfx/snake/snake_tail";
const std::string						arcade::Snake::S_WALL_RESOURCES = "./gfx/snake/wall";
const std::string						arcade::Snake::S_GROUND_RESOURCES = "./gfx/snake/ground";
const std::string						arcade::Snake::S_POWERUP_RESOURCES = "./gfx/snake/apple";
const std::string						arcade::Snake::S_SNAKE_RESOURCES = "./gfx/snake/snake";

const std::map<arcade::TileType,
	std::string>			    			arcade::Snake::S_TILE_RESOURCES = {
	{arcade::TileType::EMPTY, S_GROUND_RESOURCES},
	{arcade::TileType::BLOCK, S_WALL_RESOURCES},
	{arcade::TileType::POWERUP, S_POWERUP_RESOURCES},
	{arcade::TileType::EVIL_DUDE, S_SNAKE_RESOURCES},
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
	: _objects(), _lib(NULL), _win(NULL), _map(), _score(0), _snake(), _map_size({0, 0}), _handle(handle),
	  _lib_name("lib_arcade_snake"), _gen(getpid()), _dis_width(0, 0), _dis_height(0, 0)
{
  _snake.ct = arcade::CommandType::PLAY;

  _checkMove = {
	  {arcade::TileType::BLOCK, [&]() -> void { _dead(); }},
	  {arcade::TileType::EVIL_DUDE, [&]() -> void { _dead(); }},
	  {arcade::TileType::EMPTY, [&]() -> void { _move(); }},
	  {arcade::TileType::POWERUP, [&]() -> void { _powerUp(); }}
  };

  _actions = {
	  {arcade::CommandType::PLAY, [&]() -> void {}},
	  {arcade::CommandType::GO_UP, [&]() -> void {_snake.body[S_SNAKE_HEAD].y -= 1; }},
	  {arcade::CommandType::GO_DOWN, [&]() -> void {_snake.body[S_SNAKE_HEAD].y += 1; }},
	  {arcade::CommandType::GO_LEFT, [&]() -> void {_snake.body[S_SNAKE_HEAD].x -= 1; }},
	  {arcade::CommandType::GO_RIGHT, [&]() -> void {_snake.body[S_SNAKE_HEAD].x += 1; }},
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

void arcade::Snake::initGame(arcade::IGraphicalLib *lib, arcade::IObserver *,
			     std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > > &objects)
{
/*    if (lib == NULL)
        throw std::runtime_error("Not able to init the game with a null graphical library.");*/
  _lib = lib;
  if (!(_win = _lib->getWindows().get()))
    throw std::runtime_error("Not able to init the game until the window is not.");
  _objects = objects;
  createMap();
}

uint64_t 		arcade::Snake::getScore() const
{
  return (_score);
}

void 			arcade::Snake::gameTurn()
{
  /*arcade::Vector3d tmp(0, 0);

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

  (_actions[_snake.ct])();

  if (_snake.ct != arcade::CommandType::PLAY)
    (_checkMove[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
  if (_snake.body[S_SNAKE_HEAD].y >= _map_size.getY() || _snake.body[S_SNAKE_HEAD].x >= _map_size.getX())
    {
      _map[_snake.body[S_SNAKE_HEAD].y % _map_size.getY()][_snake.body[S_SNAKE_HEAD].x % _map_size.getX()] = TileType::EVIL_DUDE;
      _refreshObjects();
      _win->refresh();
      sleep(1);
      throw std::runtime_error("Game Over !");
    }
  _refreshObjects();*/
}

// private

void 			arcade::Snake::createMap()
{
  int32_t		x = 0, y = 0;
  arcade::Vector3d	v{0, 0, 0};

  while (y < S_HEIGHT)
    {
      x = 0;
      while (x < S_WIDTH)
	{
	  v.setX(x);
	  v.setY(y);
	  v.setZ(0);
	  if (y == 0 || y == S_HEIGHT - 1 || x == 0 || x == S_WIDTH - 1)
	    {
	      _createObject("ground" + std::to_string(y) + std::to_string(x), S_WALL_RESOURCES, v);
	      _map[y][x] = arcade::TileType::BLOCK;
	    }
	  else
	    {
	      _createObject("wall" + std::to_string(y) + std::to_string(x), S_GROUND_RESOURCES, v);
	      _map[y][x] = arcade::TileType::EMPTY;
	    }
	  x += 1;
	}
      y += 1;
    }
  std::cout << "y = " << _objects->size() << std::endl;
/*  _initPowerUp();
  _initPowerUp();
  _initPowerUp();
  _initSnake();*/
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
  try
    {
      if (event.getAction() == IEvenement::Action::KeyPressDown	 && kc != IEvenement::KeyCode::Key_Undefined
	  && S_FORBIDEN_COMMAND.at(_snake.ct)!=
	     S_BINDING.at(kc))
	{
	  _snake.ct = S_BINDING.at(kc);
	}
    } catch (const std::exception &)
    {
      try {
	  _snake.ct = S_BINDING.at(kc);
	} catch (std::exception e) {
	  throw std::runtime_error("ICI");
	}}
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
      if (v.getX() == _snake.body[S_SNAKE_HEAD].x && v.getY() == _snake.body[S_SNAKE_HEAD].y)
	{
	  _lib->setVisual(it, S_HEAD_RESOURCES);
	  it->setName("snake_head");
	}
      else if(v.getX() == _snake.body[_snake.body.size() - 1].x && v.getY() == _snake.body[_snake.body.size() - 1].y)
	  {
	    _lib->setVisual(it, S_TAIL_RESOURCES);
	    it->setName("snake_tail");
	  }
	else
	  {
	    _lib->setVisual(it, S_TILE_RESOURCES.at(_map[v.getY()][v.getX()]));
	  }
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

std::shared_ptr<arcade::IObject> arcade::Snake::_createObject(const std::string &name, const std::string &filename,
							      const arcade::Vector3d &pos)
{
  std::shared_ptr<arcade::IObject> obj;

  obj.reset();
  if (_lib)
    {
      obj = _lib->initObject(name, filename);
      obj->setPosition(pos);
      obj->setSpeed(pos.getZ());
      _win->addObject(obj, pos);
    }
  return (obj);
}