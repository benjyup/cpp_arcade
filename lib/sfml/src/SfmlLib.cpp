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
        //_objects.reset();
    }

    /* virtual functions of IGraphicalLib */

    std::shared_ptr<arcade::IWindows> &SfmlLib::initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> >&objs,
                                                               uint64_t height,
                                                               uint64_t width)
    {
        try
        {
            _objects = objs;
            _win = std::shared_ptr<IWindows>(new Window(objs, height, width));
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("Not able to open the window : " + std::string(e.what()));
        }
        return (_win);
    }

    std::shared_ptr<IObject> SfmlLib::initObject(const std::string &name, const std::string &filename)
    {
        std::shared_ptr<arcade::Sprite>   tmp(new arcade::Sprite(name, getTexture(filename)));
        tmp->setTextureFile(filename);
        return (tmp);
    }

    std::shared_ptr<arcade::IObject> SfmlLib::initLabel(const std::string &name, const std::string &filename)
    {
        std::shared_ptr<Label>    tmp(new Label(name, this->getFont(filename)));
        tmp->setTextureFile(filename);
        return (tmp);
    }

    std::shared_ptr<arcade::IWindows>& SfmlLib::getWindows()
    {
        return (_win);
    }

    void SfmlLib::setVisual(std::shared_ptr<arcade::IObject> &obj, std::string const & filename)
    {
        std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(obj);

        if (sprite)
        {
            sprite->setVisual(this->getTexture(filename));
            sprite->setTextureFile(filename);
        }
        else
        {
            std::shared_ptr<Label> label = std::dynamic_pointer_cast<Label>(obj);
            if (label)
            {
                label->setVisual(this->getFont(filename));
                label->setTextureFile(filename);
            }
        }

    }

    /* !(virtual functions of IGraphicalLib) */

    /* virtual functions of IObserved */

    std::shared_ptr<IEvenement> SfmlLib::getEvent()
    {return(std::shared_ptr<IEvenement>());}

    void SfmlLib::notify(const IEvenement &evenement)
    {
        for (auto &it : _observers)
            it->getNotified(evenement);
    }

    void SfmlLib::registerObserver(arcade::IObserver *observer)
    {
        if (this->_win)
            this->_win->registerObserver(observer);
    }

    void SfmlLib::removeObserver(arcade::IObserver *observer)
    {
        if (observer == NULL)
            return ;
        auto it = _observers.begin();

        while (it != _observers.end())
        {
            if (*it == observer)
            {
                _observers.erase(it);
                return ;
            }
            ++it;
        }
    }

    /* !(virtual functions of IObserved) */

    /* virtual functions of ILibrairy */

    void* SfmlLib::getHandle() const { return ((void *) (_handle)); }

    std::string const& SfmlLib::getName() const { return (_name); }

    ILibrairy::LibType SfmlLib::getType() const {return (ILibrairy::LibType ::Graphical);}

    void SfmlLib::freeSharedData(void) { }

    std::shared_ptr<sf::Texture>            &SfmlLib::getTexture(std::string const &fileName)
    {
        if (this->_textureDump.find(fileName) == this->_textureDump.end())
        {
            auto tmp = std::make_shared<sf::Texture>();
            this->_textureDump.emplace(fileName, tmp);
            this->_textureDump[fileName]->setSmooth(true);
            if (!(this->_textureDump[fileName]->loadFromFile(fileName + ".png")))
                throw std::string("Failed to load a texture");
        }
        return (this->_textureDump[fileName]);
    }

    std::shared_ptr<sf::Font>               &SfmlLib::getFont(std::string const &fileName)
    {
        if (this->_fontDump.find(fileName) == this->_fontDump.end())
        {
            auto tmp = std::make_shared<sf::Font>();
            this->_fontDump.emplace(fileName, tmp);
            if (!(this->_fontDump[fileName]->loadFromFile(fileName + ".ttf")))
                throw std::string("Failed to load a font");
        }
        return (this->_fontDump[fileName]);
    }

    ILibrairy *getNewLib(void *handle)
    {
        return (new SfmlLib(handle));
    }

}