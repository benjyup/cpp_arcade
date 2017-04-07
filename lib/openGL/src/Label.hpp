//
// Created by florian on 4/6/17.
//

#ifndef CPP_ARCADE_LABEL_HPP
#define CPP_ARCADE_LABEL_HPP

#include <vector>
#include "Object.hpp"

namespace arcade
{
    class Label : public Object
    {
    public:
        Label(const std::string &name, const std::string &filename);
        virtual ~Label();

        virtual bool 			setProperties(const std::string &pahtname);
        virtual Object::ObjectType 		getType(void) const;
    private:
        TTF_Font *font;
    };
}


#endif //CPP_ARCADE_LABEL_HPP
