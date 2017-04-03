//
// Created by vincent on 03/04/17.
//

#include "Snake.hpp"

const std::string			MAP_PATH = "../resc/snake/map.ncurses";
static const std::unordered_map<arcade::TileType,
	std::string>			TILE_RESOURCES = {
	{arcade::TileType::EMPTY, "../gfx/ground"},
	{arcade::TileType::BLOCK, "../gfx/wall"},
	{arcade::TileType::POWERUP, "../gfx/apple"},
	{arcade::TileType::EVIL_DUDE, "../gfx/snake"},
};

arcade::Snake::Snake() : _objects(), _lib(NULL), _map()
{

}

arcade::Snake::~Snake() { }

void 			arcade::Snake::initGame(arcade::IGraphicalLib *lib,
						    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> & objects)
{
  if (lib == NULL)
    throw std::runtime_error("Not able to init the game with a null graphical library.");
  _lib = lib;
  _objects = objects;
}

uint64_t 		arcade::Snake::getScore() const
{
  return (_score);
}

void 			arcade::Snake::gameTurn()
{

}

void 			arcade::Snake::createMap()
{

}

void arcade::Snake::initGraphicalLib(arcade::IGraphicalLib *)
{

}

void arcade::Snake::getNotified(IEvenement const &)
{

}