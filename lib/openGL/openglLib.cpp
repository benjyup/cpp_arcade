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
//            _win = std::shared_ptr<IWindows>(new Window(objs, height, width));
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("Not able to open the window : " + std::string(e.what()));
        }
        return (_win);
    }



    ILibrairy *getNewLib(void *handle) {
        return (new OpenGlLib(handle));
    }

}