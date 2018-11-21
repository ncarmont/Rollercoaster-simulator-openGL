//
//  Node.hpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include "OBJObject.h"
#include <list>



class Node
{
    public:
    virtual void draw(glm::mat4 C)=0;
    virtual void update(glm::vec3 rotAxis)=0;
    Node * parent ;
    std::vector <Node*> children;
};
#endif /* Node_hpp */
