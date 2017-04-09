//
// Created by peixot_b on 09/04/17.
//

#include <fstream>
#include <map>
#include <unistd.h>
#include "Solar_Fox.hpp"
#include "../../../lib/interfaces/Protocol.hpp"
#include "../../../lib/interfaces/IObserve.hpp"
#include "../../../lib/interfaces/IGraphicalLib.hpp"

const std::string			            arcade::Solar_Fox::S_MAP_PATH 	= "./resc/Solar_Fox/map";
const std::string						arcade::Solar_Fox::S_HEAD_RESOURCES = "./gfx/Solar_Fox/vaisseau";
const std::string						arcade::Solar_Fox::S_WALL_RESOURCES = "./gfx/Solar_Fox/space";
const std::string						arcade::Solar_Fox::S_GROUND_RESOURCES = "./gfx/Solar_Fox/space";
const std::string						arcade::Solar_Fox::S_POWERUP_RESOURCES = "./gfx/Solar_Fox/fuel";
const std::string						arcade::Solar_Fox::S_Solar_Fox_RESOURCES = "./gfx/Solar_Fox/projectile";
const std::string						arcade::Solar_Fox::S_Solar_Fox_RESOURCES2 = "./gfx/Solar_Fox/shot";
const std::string						arcade::Solar_Fox::S_TTF_RESOURCES = "./gfx/Solar_Fox/Roboto-Regular";
const unsigned int						arcade::Solar_Fox::S_POWERUP_NBR_DEFAULT = 32;

const unsigned long							arcade::Solar_Fox::S_Solar_Fox_HEAD = 0;

const uint64_t								arcade::Solar_Fox::S_SCORE_INC = 42;

const std::map<arcade::TileType,
        std::string>			    			arcade::Solar_Fox::S_TILE_RESOURCES = {
        {arcade::TileType::EMPTY, S_GROUND_RESOURCES},
        {arcade::TileType::BLOCK, S_WALL_RESOURCES},
        {arcade::TileType::POWERUP, S_POWERUP_RESOURCES},
        {arcade::TileType::EVIL_SHOOT, S_Solar_Fox_RESOURCES},
        {arcade::TileType::MY_SHOOT, S_Solar_Fox_RESOURCES2},
};

const std::map<char, arcade::TileType>				arcade::Solar_Fox::S_STRING_TO_TILE = {
        {'1', TileType::BLOCK},
        {'0', TileType::EMPTY},
        {'2', TileType::POWERUP},
};

const std::map<arcade::CommandType,
        arcade::CommandType>					arcade::Solar_Fox::S_FORBIDEN_COMMAND = {
        {arcade::CommandType::GO_UP, arcade::CommandType::GO_DOWN},
        {arcade::CommandType::GO_DOWN, arcade::CommandType::GO_UP},
        {arcade::CommandType::GO_RIGHT, arcade::CommandType::GO_LEFT},
        {arcade::CommandType::GO_LEFT, arcade::CommandType::GO_RIGHT}
};

const std::map<arcade::IEvenement::KeyCode , arcade::CommandType>			arcade::Solar_Fox::S_BINDING = {
        {arcade::IEvenement::KeyCode::Key_Z, arcade::CommandType::GO_UP},
        {arcade::IEvenement::KeyCode::Key_S, arcade::CommandType::GO_DOWN},
        {arcade::IEvenement::KeyCode::Key_D, arcade::CommandType::GO_RIGHT},
        {arcade::IEvenement::KeyCode::Key_Q, arcade::CommandType::GO_LEFT},
        {arcade::IEvenement::KeyCode::Key_A, arcade::CommandType::SHOOT}
};

arcade::Solar_Fox::Solar_Fox(void *handle)
        : _shot(false), _objects(), _lib(NULL), _win(NULL), _map(), _score(0), _Solar_Fox(), _map_size({0, 0}), _handle(handle),
          _lib_name("lib_arcade_Solar_Fox"), _gen(getpid()), _dis_width(0, S_WIDTH - 1), _dis_height(0, S_HEIGHT - 1)
{
    _Solar_Fox.ct = arcade::CommandType::GO_RIGHT;
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
            {arcade::CommandType::SHOOT, [&]() -> void {_shoot(); }},
    };
}

arcade::Solar_Fox::~Solar_Fox()
{
    freeSharedData();
}

void* arcade::Solar_Fox::getHandle() const { return (_handle);}

std::string const& arcade::Solar_Fox::getName() const { return (_lib_name);}

void arcade::Solar_Fox::freeSharedData()
{
    if (_objects)
        _objects->clear();
    _objects.reset();
}

void arcade::Solar_Fox::initGame(arcade::IGraphicalLib *lib, arcade::IObserver *,
                             std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > > &objects) {
    initGraphicalLib(lib);
    _objects = objects;
    createMap();
    score = _createLabel("Score: 0", S_TTF_RESOURCES, {0, 0, 0});
}

uint64_t 		arcade::Solar_Fox::getScore() const
{
    return (_score);
}

void 			arcade::Solar_Fox::gameTurn()
{
    (_actions[_Solar_Fox.ct])();
}

void                              arcade::Solar_Fox::setCt(arcade::CommandType ct){
    _Solar_Fox.ct = ct;
}

void 			arcade::Solar_Fox::createMap()
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
                _createObject("space", S_WALL_RESOURCES, v, 0);
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
    _initSolar_Fox();
    for (unsigned int i = 0 ; i < S_POWERUP_NBR_DEFAULT ; i += 1)
        _initPowerUp();
}

void arcade::Solar_Fox::_initSolar_Fox()
{
    Position p;

    p.x = S_WIDTH / 2;
    p.y = S_HEIGHT / 2;
    _Solar_Fox.body.push_back(p);
    _createObject("Solar_Fox", S_HEAD_RESOURCES, {(int32_t) p.x, (int32_t) p.y}, 0.25);
}

void arcade::Solar_Fox::initGraphicalLib(arcade::IGraphicalLib *lib)
{
    _lib = lib;
    if (_lib) {
        if (!(_win = _lib->getWindows().get())) {
            throw std::runtime_error("Not able to init the game until the window is not.");
        }
        _win->setMapSize(S_HEIGHT);
    }
}

void arcade::Solar_Fox::getNotified(IEvenement const &event) {
    IEvenement::KeyCode kc = event.getKeyCode();
    try {
        if (event.getAction() == IEvenement::Action::KeyPressDown && kc != IEvenement::KeyCode::Key_Undefined
            && S_FORBIDEN_COMMAND.at(_Solar_Fox.ct) != S_BINDING.at(kc)) {
            _Solar_Fox.ct = S_BINDING.at(kc);
        }
    } catch (const std::exception &) {
        try {
            _Solar_Fox.ct = S_BINDING.at(kc);
        } catch (std::exception e) {
        }
    }
}

arcade::ILibrairy *arcade::getNewLib(void *handle)
{
    return (new arcade::Solar_Fox(handle));
}

void arcade::Solar_Fox::_initPowerUp()
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

void arcade::Solar_Fox::_dead()
{
    _win->refresh();
    sleep(1);
    throw std::runtime_error("Game Over !");
}

void arcade::Solar_Fox::_move() {
    //_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x] = TileType::EVIL_DUDE;
}

void arcade::Solar_Fox::_powerUp() {
    arcade::Position p;

    p.x = _Solar_Fox.body[S_Solar_Fox_HEAD].x;
    p.y = _Solar_Fox.body[S_Solar_Fox_HEAD].y;
    _move();
    for (auto &it : _Solar_Fox.objsPowerUp)
        if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y) {
            _win->destroyObject(it);
            _score += 100;
            score->setString("Score :" + std::to_string(_score));
        }
    p.x = _Solar_Fox.body[_Solar_Fox.body.size() - 1].x;
    p.y = _Solar_Fox.body[_Solar_Fox.body.size() - 1].y;

    //if (p.x - 1 >= 0 && _map[p.y][p.x - 1] == arcade::TileType::EMPTY) {
        //_Solar_Fox.body.push_back({static_cast<uint16_t >(p.x - 1), p.y});
    //_createObject("Solar_Fox", S_Solar_Fox_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
    //} else if (p.y - 1 >= 0 && _map[p.y - 1][p.x] == arcade::TileType::EMPTY) {
     //   _Solar_Fox.body.push_back({p.x, static_cast<uint16_t >(p.y - 1)});
     //   _createObject("Solar_Fox", S_Solar_Fox_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
    //} else if (p.y + 1 < _map_size.getY() && _map[p.y + 1][p.x] == arcade::TileType::EMPTY) {
    //    _Solar_Fox.body.push_back({p.x, static_cast<uint16_t >(p.y + 1)});
     //   _createObject("Solar_Fox", S_Solar_Fox_RESOURCES, {static_cast<uint16_t >(p.x - 1), p.y}, 0.25);
    //}
}

std::shared_ptr<arcade::IObject> arcade::Solar_Fox::_createObject(const std::string &name, const std::string &filename,
                                                              const arcade::Vector3d &pos, float speed)
{
    std::shared_ptr<arcade::IObject> obj;

    obj.reset();
    if (_lib)
    {
        obj = _lib->initObject(name, filename);
        obj->setScale(1);
        obj->setPosition(pos);
        obj->setSpeed(speed);
        _win->addObject(obj, pos);
        if (name == "Solar_Fox")
            _Solar_Fox.objs.push_back(obj);
        else if (name == "powerup")
            _Solar_Fox.objsPowerUp.push_back(obj);
        else if (name == "shoot")
            _Solar_Fox.objsShoot.push_back(obj);
    }
    return (obj);
}

std::shared_ptr<arcade::IObject> arcade::Solar_Fox::_createLabel(const std::string &name, const std::string &filename,
                                                             const arcade::Vector3d &pos)
{
    std::shared_ptr<arcade::IObject> obj;

    obj.reset();
    if (_lib)
    {
        obj = _lib->initLabel(name, filename);
        obj->setScale(1);
        obj->setPosition(pos);
        obj->setString(name);
        _win->addObject(obj, pos);
    }
    return (obj);
}

void arcade::Solar_Fox::_goUp() {
    arcade::Position p;

    p.x = _Solar_Fox.body[S_Solar_Fox_HEAD].x;
    p.y = _Solar_Fox.body[S_Solar_Fox_HEAD].y;
    if (_shot == true) {
        _createObject("shoot", S_Solar_Fox_RESOURCES2, {static_cast<uint16_t >(p.x), (p.y - 1)}, 1);
        _shot = false;

        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y - 1) {
                _win->moveObject(it, {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y - 2});
            }
        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y - 1) {
                _win->destroyObject(it);
            }
    }
    if (_lib) {
        if (!_Solar_Fox.objs[0]->isMoving()) {
            _Solar_Fox.body[S_Solar_Fox_HEAD].y -= 1;
            _win->moveObject(_Solar_Fox.objs[0], {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            (_Solar_Fox.objs[0])->setDirection({0, 1, 0});
            (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
            //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
        }
    }
    else {
        _Solar_Fox.body[S_Solar_Fox_HEAD].y -= 1;
        (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
        //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Solar_Fox::_goDown()
{
    arcade::Position p;

    p.x = _Solar_Fox.body[S_Solar_Fox_HEAD].x;
    p.y = _Solar_Fox.body[S_Solar_Fox_HEAD].y;
    if (_shot == true) {
        _createObject("shoot", S_Solar_Fox_RESOURCES2, {static_cast<uint16_t >(p.x), (p.y + 1)}, 1);
        _shot = false;

        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y + 1) {
                _win->moveObject(it, {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y + 2});
            }
        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x && it->getPosition().getY() == p.y + 1) {
                _win->destroyObject(it);
            }
    }
    if (_lib) {
        if (!_Solar_Fox.objs[0]->isMoving()) {
            _Solar_Fox.body[S_Solar_Fox_HEAD].y += 1;
            _win->moveObject(_Solar_Fox.objs[0], {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            (_Solar_Fox.objs[0])->setDirection({0, -1, 0});
            (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
            //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
        }
    }
    else {
        _Solar_Fox.body[S_Solar_Fox_HEAD].y += 1;
        (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
        //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Solar_Fox::_goLeft() {
    arcade::Position p;

    p.x = _Solar_Fox.body[S_Solar_Fox_HEAD].x;
    p.y = _Solar_Fox.body[S_Solar_Fox_HEAD].y;
    if (_shot == true)
    {
        _createObject("shoot", S_Solar_Fox_RESOURCES2, {static_cast<uint16_t >(p.x - 1), p.y}, 1);
        _shot = false;

        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x - 1 && it->getPosition().getY() == p.y) {
                _win->moveObject(it, {_Solar_Fox.body[S_Solar_Fox_HEAD].x - 2, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            }
        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x - 1 && it->getPosition().getY() == p.y) {
                _win->destroyObject(it);
            }
    }
    if (_lib) {
        if (!_Solar_Fox.objs[0]->isMoving()) {
            _Solar_Fox.body[S_Solar_Fox_HEAD].x -= 1;
            _win->moveObject(_Solar_Fox.objs[0], {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            (_Solar_Fox.objs[0])->setDirection({1, 0, 0});
            (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
            //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
        }
    }
    else {
        _Solar_Fox.body[S_Solar_Fox_HEAD].x -= 1;
        (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
        //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
    }
}

void arcade::Solar_Fox::_goRight() {
    arcade::Position p;

    p.x = _Solar_Fox.body[S_Solar_Fox_HEAD].x;
    p.y = _Solar_Fox.body[S_Solar_Fox_HEAD].y;
    if (_shot == true)
    {
        _createObject("shoot", S_Solar_Fox_RESOURCES2, {static_cast<uint16_t >(p.x + 1), p.y}, 1);
        _shot = false;
        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x + 1 && it->getPosition().getY() == p.y) {
                _win->moveObject(it, {_Solar_Fox.body[S_Solar_Fox_HEAD].x + 2, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            }
        for (auto &it : _Solar_Fox.objsShoot)
            if (it->getPosition().getX() == p.x + 1 && it->getPosition().getY() == p.y) {
                _win->destroyObject(it);
            }
    }
    if (_lib) {
        if (!_Solar_Fox.objs[0]->isMoving()) {
            _Solar_Fox.body[S_Solar_Fox_HEAD].x += 1;
            _win->moveObject(_Solar_Fox.objs[0], {_Solar_Fox.body[S_Solar_Fox_HEAD].x, _Solar_Fox.body[S_Solar_Fox_HEAD].y});
            (_Solar_Fox.objs[0])->setDirection({-1, 0, 0});
            (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
            //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;

        }
    }
    else
    {
        _Solar_Fox.body[S_Solar_Fox_HEAD].x += 1;
        (_checkMove[_map[_Solar_Fox.body[S_Solar_Fox_HEAD].y][_Solar_Fox.body[S_Solar_Fox_HEAD].x]])();
        //_map[_Solar_Fox.body[0].y][_Solar_Fox.body[0].x] = TileType::EVIL_DUDE;
    }
}

void    arcade::Solar_Fox::_shoot()
{
    _shot = true;
}

void             arcade::Solar_Fox::where_Am_I(void){
    struct WhereAmI         wai;
    Position *p = new Position[_Solar_Fox.body.size()];
    int                         count = 0;

    wai.type = arcade::CommandType::WHERE_AM_I;
    wai.lenght = _Solar_Fox.body.size();
    for (auto i : _Solar_Fox.body)
    {
        p[count].x = i.x;
        p[count].y = i.y;
        count++;
    }
    write(1, &wai, sizeof(wai));
    write(1, p, sizeof(*p) * _Solar_Fox.body.size());
    delete p;
}

void            arcade::Solar_Fox::get_map(void) {
    struct GetMap getMap;
    arcade::TileType *tile = new TileType[S_HEIGHT * S_WIDTH];
    int i = -1;
    int j;

    getMap.type = arcade::CommandType::GET_MAP;
    getMap.height = S_HEIGHT;
    getMap.width = S_WIDTH;
    while (++i < S_HEIGHT) {
        j = -1;
        while (++j < S_WIDTH) {
            tile[i * S_WIDTH + j] = _map[i][j];
        }
    }
    write(1, &getMap, sizeof(getMap));
    write(1, tile, sizeof(*tile) * S_HEIGHT * S_WIDTH);
    delete tile;
}

extern "C"
{
void Play(void) {
    arcade::CommandType cmd;
    arcade::Solar_Fox game(NULL);
    std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > > objs(
            new std::vector<std::shared_ptr<arcade::IObject> >);
    std::ifstream in("/dev/stdin");

    game.initGame(NULL, NULL, objs);
    while (in.read((char *)(&cmd), sizeof(cmd))) {
        switch (cmd) {
            case arcade::CommandType::WHERE_AM_I:
                game.where_Am_I();
                break;
            case arcade::CommandType::GET_MAP:
                game.get_map();
                break;
            case arcade::CommandType::GO_UP:
                game.setCt(arcade::CommandType::GO_UP);
                break;
            case arcade::CommandType::GO_DOWN:
                game.setCt(arcade::CommandType::GO_DOWN);
                break;
            case arcade::CommandType::GO_LEFT:
                game.setCt(arcade::CommandType::GO_LEFT);
                break;
            case arcade::CommandType::GO_RIGHT:
                game.setCt(arcade::CommandType::GO_RIGHT);
                break;
            case arcade::CommandType::SHOOT:
                game.setCt(arcade::CommandType::SHOOT);
                break;
            case arcade::CommandType::PLAY:
                game.gameTurn();
                break;
            default:
                break;
        }
    }
}
}