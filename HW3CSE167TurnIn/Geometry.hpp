//
//  Geometry.hpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "Node.hpp"
#include "OBJObject.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include <list>



#endif /* Geometry_hpp */

class Geometry : public Node
{
    public:
    Geometry(glm::mat4 mat,const char*  filename);
    glm::mat4 M;
    OBJObject *model=NULL;
    static void init(const char*  filename);
    void draw(glm::mat4 C);
    void update(glm::vec3 rotAxis);
    };
