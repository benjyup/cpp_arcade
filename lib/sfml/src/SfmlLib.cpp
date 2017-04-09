//
// Created by peixot_b on 05/04/17.
//

#include "SfmlLib.hpp"
#include "Object.hpp"
#include "Sprite.hpp"

namespace arcade
{
    SfmlLib::SfmlLib(void *handle) : _win(NULL), _name("SfmlLib"), _observers(),
                                           _handle(handle) { }

    SfmlLib::~SfmlLib()
    {
        freeSharedData();
    }

    /* virtual functions of IGraphicalLib */

    void                                    SfmlLib::reloadObject(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject> > > & objs) {
        std::shared_ptr<arcade::IObject> tmp;
        std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> newObjs(
                new std::vector<std::shared_ptr<arcade::IObject> >);

        for (auto &obj : (*objs)) {
            if (obj->getString() != "") {
                tmp = initLabel(obj->getName(), obj->getTextureFile());
                tmp->setString(obj->getString());

            } else
                tmp = initObject(obj->getName(), obj->getTextureFile());
            tmp->setSpeed(obj->getSpeed());
            tmp->setPosition(obj->getPosition());
            tmp->setScale(obj->getScale());
            tmp->setDirection(obj->getDirection());
            obj = tmp;
        }
    }

    std::shared_ptr<arcade::IWindows> &SfmlLib::initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>>> &objs,
                                                               uint64_t,
                                                               uint64_t)
    {
        if (objs->size() > 0 && !std::dynamic_pointer_cast<arcade::Object>((*objs)[0]))
            reloadObject(objs);
        _win.reset();
        _win = std::make_shared<arcade::Window>(objs);
        return (_win);
    }

    std::shared_ptr<IObject> SfmlLib::initObject(const std::string &name, const std::string &filename)
    {
        std::shared_ptr<arcade::Sprite>   tmp(new arcade::Sprite(name, filename, getTexture(filename)));
        return (tmp);
    }

    std::shared_ptr<arcade::IObject>    SfmlLib::initLabel(const std::string &name, const std::string &filename)
    {
        std::shared_ptr<Label>    tmp(new Label(name, filename, getFont(filename)));
        return (tmp);
    }

    std::shared_ptr<arcade::IWindows>   &SfmlLib::getWindows()
    {
        return (_win);
    }

    void                                SfmlLib::setVisual(std::shared_ptr<arcade::IObject> &obj, std::string const & filename) {
        std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(obj);

        obj->setTextureFile(filename);
        if (!sprite) {
            std::shared_ptr<Label> label = std::dynamic_pointer_cast<Label>(obj);
            if (label)
                label->setVisual(getFont(filename));
        } else
            sprite->setVisual(getTexture(filename));
    }

    /* !(virtual functions of IGraphicalLib) */

    /* virtual functions of IObserved */

    std::shared_ptr<IEvenement> SfmlLib::getEvent() {
        return (std::shared_ptr<IEvenement>());
    }

    void SfmlLib::notify(const IEvenement &evenement) {
        for (auto &it : _observers)
            it->getNotified(evenement);
    }

    void SfmlLib::registerObserver(arcade::IObserver *observer) {
        if (_win)
            _win->registerObserver(observer);
    }

    void SfmlLib::removeObserver(arcade::IObserver *observer) {
        if (_win)
            _win->removeObserver(observer);
    }

    /* !(virtual functions of IObserved) */

    /* virtual functions of ILibrairy */

    void* SfmlLib::getHandle() const {
        return ((void *) (_handle));
    }

    std::string const& SfmlLib::getName() const {
        return (_name);
    }

    ILibrairy::LibType SfmlLib::getType() const {
        return (ILibrairy::LibType::Graphical);
    }

    void SfmlLib::freeSharedData(void)
    {
        for (auto *it : _observers)
            removeObserver(it);
        if (_objects)
            _objects->clear();
        _objects.reset();
        _win.reset();
        _textureDump.clear();
        _fontDump.clear();
    }

    std::shared_ptr<sf::Texture>            &SfmlLib::getTexture(std::string const &fileName) {
        auto tmp = std::make_shared<sf::Texture>();

        if (_textureDump.find(fileName) == _textureDump.end()) {
            _textureDump.emplace(fileName, tmp);
            _textureDump[fileName]->setSmooth(true);
            if (!(_textureDump[fileName]->loadFromFile(fileName + ".png")))
                throw std::runtime_error("Failed to load a texture");
        }
        return (_textureDump[fileName]);
    }

    std::shared_ptr<sf::Font>               &SfmlLib::getFont(std::string const &fileName) {
        auto tmp = std::make_shared<sf::Font>();

        if (_fontDump.find(fileName) == _fontDump.end()) {
            _fontDump.emplace(fileName, tmp);
            if (!(_fontDump[fileName]->loadFromFile(fileName + ".ttf")))
                throw std::runtime_error("Failed to load a font");
        }
        return (_fontDump[fileName]);
    }

    ILibrairy *getNewLib(void *handle) {
        return (new SfmlLib(handle));
    }
}