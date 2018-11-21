//
//  sceneGraph.cpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#include "sceneGraph.hpp"

#define Node_hpp

//sceneGraph::sceneGraph {
//    sGraph = new sceneGraph;
//    sGraph.addChild(bunny);
//    sGraph.
//};

void sceneGraph::Geometry {
    antenna = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167/Hw3CSE167/robotParts/antenna_s.obj");
    body = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167/Hw3CSE167/robotParts/body_s.obj");
    eyeball = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167/Hw3CSE167/robotParts/eyeball_s.obj");
    head = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167/Hw3CSE167/robotParts/head_s.obj");
    limb = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167/Hw3CSE167/robotParts/limb_s.obj");
}


void sceneGraph::Transform::addChild(Node* n){
    children.push_back ( n );
    n -> parent = this ;
};

