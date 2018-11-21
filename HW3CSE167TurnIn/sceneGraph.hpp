//
//  sceneGraph.hpp
//  Hw3CSE167
//
//  Created by Computer Science on 09/11/2018.
//  Copyright © 2018 Nicolas Carmont. All rights reserved.
//

#ifndef sceneGraph_hpp
#define sceneGraph_hpp

#include <stdio.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include <list>

#endif /* sceneGraph_hpp */


    class Node
    {
        public:
        virtual void draw(glm::mat4 C)=0;
        virtual void update()=0;
        Node * parent ;
        std::list <Node*> children;
    };
    
    class Transform : Node
    {
        public:
        glm::mat4 transf;
        std::list<Node*> nodes;
        void addChild(Node* n);
        protected:
    };
    
    class Geometry : Node
    {
        public:
        static void init(std::string filename);
        
        
    };
