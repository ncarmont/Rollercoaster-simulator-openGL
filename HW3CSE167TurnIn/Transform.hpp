//
//  Transform.hpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include "Node.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include <list>


#endif /* Transform_hpp */

class Transform : public Node
{
    public:
    Transform(glm::mat4 mat);
    void draw(glm::mat4 C);
    void update(glm::vec3 rotAxis);
    glm::mat4 M;
    std::vector<Node*> nodes;
    static void draw();
    void addChild(Node* n);
    };
