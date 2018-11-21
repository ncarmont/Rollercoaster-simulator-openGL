//
//  Transform.cpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#include "Transform.hpp"

Transform::Transform(glm::mat4 mat){
    this->M = mat;
};

void Transform::addChild(Node* n){
    children.push_back ( n );
};

void Transform::draw(glm::mat4 C){
    
    for (int i =0; i<children.size();i++){
        glm::mat4 transform = M * C;
        children[i]->draw(M*C);
    };
};

void Transform::update(glm::vec3 rotAxis){
    
};


