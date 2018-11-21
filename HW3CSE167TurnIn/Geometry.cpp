//
//  Geometry.cpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#include "Geometry.hpp"
#include <stdio.h>
#include <iostream>

Geometry::Geometry(glm::mat4 mat, const char*  filename){
    this->M = mat;
    OBJObject * model;
    model = new OBJObject(filename);
};

//void Geometry::init(std::string filename) {
//    model = new OBJObject(filename);
//}

void Geometry::draw(glm::mat4 C) {
    model -> draw(0,C);
}

void Geometry::update(glm::vec3 rotAxis){
    this->M = glm::rotate(M,(GLfloat)glfwGetTime()*1.5f, rotAxis);
};
