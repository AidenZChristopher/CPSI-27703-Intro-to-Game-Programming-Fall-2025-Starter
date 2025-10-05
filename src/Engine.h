#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Library.h"
#include "Object.h"

class GraphicsEngine;

struct Engine {
    Library objectLibrary; // Owned by value, not unique_ptr
    std::vector<std::unique_ptr<Object>> objects;
    
    // Constructors
    Engine();
    Engine(const std::string& levelPath);
    
    // Methods
    void loadLevel(const std::string& levelPath);
    void update();
    void draw(GraphicsEngine* graphics);
    
    // Game loop
    bool run(GraphicsEngine* graphics);
};
