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
const unsigned int						arcade::Snake::S_POWERUP_NBR_DEFAULT = 3;

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
	  _lib_name("lib_arcade_snake"), _gen(getpid()), _dis_width(0, S_WIDTH - 1), _dis_height(0, S_HEIGHT - 1)
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
	  {arcade::CommandType::GO_UP, [&]() -> void {_goUp(); }},
	  {arcade::CommandType::GO_DOWN, [&]() -> void {_goDown(); }},
	  {arcade::CommandType::GO_LEFT, [&]() -> void {_goLeft(); }},
	  {arcade::CommandType::GO_RIGHT, [&]() -> void {_goRight(); }},
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
  (_actions[_snake.ct])();
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
	      _createObject("ground", S_WALL_RESOURCES, v, 0);
	      _map[y][x] = arcade::TileType::BLOCK;
	    }
	  else
	    {
	      _createObject("wall", S_GROUND_RESOURCES, v, 0);
	      _map[y][x] = arcade::TileType::EMPTY;
	    }
	  x += 1;
	}
      y += 1;
    }
  std::cout << "y = " << _objects->size() << std::endl;
  for (unsigned int i = 0 ; i < S_POWERUP_NBR_DEFAULT ; i += 1)
      _initPowerUp();
  _initSnake();
}

void arcade::Snake::_initSnake()
{
  unsigned int i = 0;
  Position p;

  p.x = S_WIDTH / 2;
  p.y = S_HEIGHT / 2;
  while (i < S_DEFAULT_SNAKE_LENGTH)
    {
      _snake.body.push_back(p);
      if (i == 0)
	_createObject("snake", S_HEAD_RESOURCES, {(int32_t)p.x, (int32_t)p.y}, 0.25);
      else
	_createObject("snake", S_SNAKE_RESOURCES, {(int32_t)p.x, (int32_t)p.y}, 0.25);
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
	  && S_FORBIDEN_COMMAND.at(_snake.ct) != S_BINDING.at(kc))
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
  _createObject("powerup", S_POWERUP_RESOURCES, {p.x, p.y}, 0);
}

void arcade::Snake::_dead()
{
  _win->refresh();
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

  p.x = _snake.body[S_SNAKE_HEAD].x;
  p.y = _snake.body[S_SNAKE_HEAD].y;

  std::cout << "x = " << p.x << " y = " << p.y << std::endl;
  for (auto &it : _snake.objsPowerUp)
    if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y)
      {
	_win->destroyObject(it);
	std::cout << "Destroy" << std::endl;
      }
    else
      std::cout << "pas Destroy -> x = " << it->getPosition().getX() << " y = "<< it->getPosition().getY() << std::endl;

  p.x = _snake.body[_snake.body.size() - 1].x;
  p.y = _snake.body[_snake.body.size() - 1].y;
  if (p.x - 1 >= 0 && _map[p.y][p.x - 1] == arcade::TileType::EMPTY)
    {
      _snake.body.push_back({static_cast<uint16_t >(p.x - 1), p.y});
      _createObject("snake", S_SNAKE_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
    }
  else if (p.y - 1 >= 0 && _map[p.y - 1][p.x] == arcade::TileType::EMPTY)
      {
	_snake.body.push_back({p.x, static_cast<uint16_t >(p.y - 1)});
	_createObject("snake", S_SNAKE_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
      }
    else if (p.y + 1 < _map_size.getY() && _map[p.y + 1][p.x] == arcade::TileType::EMPTY)
	{
	  _snake.body.push_back({p.x, static_cast<uint16_t >(p.y + 1)});
	  _createObject("snake", S_SNAKE_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
	}
  _initPowerUp();
}

std::shared_ptr<arcade::IObject> arcade::Snake::_createObject(const std::string &name, const std::string &filename,
							      const arcade::Vector3d &pos, float speed)
{
  std::shared_ptr<arcade::IObject> obj;

  obj.reset();
  if (_lib)
    {
      obj = _lib->initObject(name, filename);
      obj->setScale(2);
      obj->setPosition(pos);
      obj->setSpeed(speed);
      _win->addObject(obj, pos);
      if (name == "snake")
	_snake.objs.push_back(obj);
      else if (name == "powerup")
	  _snake.objsPowerUp.push_back(obj);
    }
  return (obj);
}

void arcade::Snake::_goUp()
{
  if (!_snake.objs[0]->isMoving())
    {
      _followHead();
      _snake.body[S_SNAKE_HEAD].y -= 1;
      _win->moveObject(_snake.objs[0], {_snake.body[S_SNAKE_HEAD].x , _snake.body[S_SNAKE_HEAD].y});
      (_snake.objs[0])->setDirection({0, -1, 0});
      (_checkMove[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
      _map[_snake.body[0].y][_snake.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Snake::_goDown()
{
  if (!_snake.objs[0]->isMoving())
    {
      _followHead();
      _snake.body[S_SNAKE_HEAD].y += 1;
      _win->moveObject(_snake.objs[0], {_snake.body[S_SNAKE_HEAD].x , _snake.body[S_SNAKE_HEAD].y});
      (_snake.objs[0])->setDirection({0, 1, 0});
      (_checkMove[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
      _map[_snake.body[0].y][_snake.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Snake::_goLeft()
{
  if (!_snake.objs[0]->isMoving())
    {
      _followHead();
      _snake.body[S_SNAKE_HEAD].x -= 1;
      _win->moveObject(_snake.objs[0], {_snake.body[S_SNAKE_HEAD].x , _snake.body[S_SNAKE_HEAD].y});
      (_snake.objs[0])->setDirection({-1, 0, 0});
      (_checkMove[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
      _map[_snake.body[0].y][_snake.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Snake::_goRight()
{
  if (!_snake.objs[0]->isMoving())
    {
      _followHead();
      _snake.body[S_SNAKE_HEAD].x += 1;
      _win->moveObject(_snake.objs[0], {_snake.body[S_SNAKE_HEAD].x , _snake.body[S_SNAKE_HEAD].y});
      (_snake.objs[0])->setDirection({1, 0, 0});
      (_checkMove[_map[_snake.body[S_SNAKE_HEAD].y][_snake.body[S_SNAKE_HEAD].x]])();
      _map[_snake.body[0].y][_snake.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Snake::_followHead()
{
  arcade::Vector3d tmp(0, 0);

  tmp.setX(_snake.body[_snake.body.size() - 1].x);
  tmp.setY(_snake.body[_snake.body.size() - 1].y);
  if (_snake.ct != CommandType::PLAY)
    {
      for (unsigned long i = _snake.body.size() - 1; i != 0; i--)
	{
	  _snake.objs[i]->setPosition({_snake.body[i - 1].x, _snake.body[i - 1].y});
	  _snake.objs[i]->setDirection(_snake.objs[i - 1]->getDirection());
	  _snake.body[i].x = _snake.body[i - 1].x;
	  _snake.body[i].y = _snake.body[i - 1].y;
	  _map[_snake.body[i].y][_snake.body[i].x] = TileType::EVIL_DUDE;
	}
      _map[tmp.getY()][tmp.getX()] = TileType::EMPTY;
    }
}
