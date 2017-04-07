//
// Created by florian on 4/4/17.
//

#include "openglLib.hpp"

namespace arcade {

    OpenGlLib::OpenGlLib(void *handle) : _handle(handle) {

    }

    OpenGlLib::~OpenGlLib() {

    }

    std::shared_ptr<arcade::IWindows> &OpenGlLib::initWindows(std::shared_ptr<std::vector<std::shared_ptr<arcade::IObject>> >&objs,
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

    std::shared_ptr<IObject>		OpenGlLib::initObject(std::string const &name, std::string const &filename){
        return (std::shared_ptr<IObject>(new Object(name, filename)));
    }

    std::shared_ptr<IObject>		OpenGlLib::initLabel(std::string const &name, std::string const &filename){
        return (std::shared_ptr<IObject>(new Label(name, filename)));
    }

    std::shared_ptr<arcade::IWindows> &OpenGlLib::getWindows(void) {
        return (_win);
    }

    void OpenGlLib::setVisual(std::shared_ptr<arcade::IObject> &obj, std::string const & filename)
    {
        Object *o = static_cast<Object*>(obj.get());
        if (o->getType() == Object::ObjectType::Label)
        {
            Label *label = static_cast<Label*>(obj.get());
            label->setProperties(filename);
        }
        else
            o->setProperties();
    }

    void* OpenGlLib::getHandle() const { return ((void *) (_handle)); }

    std::string const& OpenGlLib::getName() const { return (_name); }

    ILibrairy::LibType OpenGlLib::getType() const {return (ILibrairy::LibType ::Graphical);}

    ILibrairy *getNewLib(void *handle) {
        return (new OpenGlLib(handle));
    }

    void OpenGlLib::freeSharedData(void)
    {
        for (auto *it : _observers)
            removeObserver(it);
        if (_objects)
            _objects->clear();
        _objects.reset();
    }

    void OpenGlLib::registerObserver(arcade::IObserver *observer)
    {
        if (_win != NULL)
            _win->registerObserver(observer);
        _observers.push_back(observer);
    }

    void OpenGlLib::removeObserver(arcade::IObserver *observer)
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

    std::shared_ptr<IEvenement> OpenGlLib::getEvent() //demander a timot
        {return (std::shared_ptr<IEvenement>());}

    void OpenGlLib::notify(const IEvenement &evenement)
    {
        for (auto &it : _observers)
            it->getNotified(evenement);
    }
}