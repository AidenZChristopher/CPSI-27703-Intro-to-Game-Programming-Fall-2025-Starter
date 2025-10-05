#include "Engine.h"
#include "GraphicsEngine.h"
#include <tinyxml2.h>
#include <iostream>
#include <SDL.h>
#include <chrono>
#include <thread>

Engine::Engine() {
    std::cout << "Engine created\n";
}

Engine::Engine(const std::string& levelPath) {
    std::cout << "Engine created with level path: " << levelPath << "\n";
    loadLevel(levelPath);
}

void Engine::loadLevel(const std::string& levelPath) {
    std::cout << "Loading level: " << levelPath << "\n";
    
    // Clear existing objects
    objects.clear();
    
    // Load XML document
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(levelPath.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load level file: " << levelPath << "\n";
        return;
    }
    
    // Get root element
    auto* root = doc.RootElement();
    if (!root) {
        std::cerr << "No root element found in level file\n";
        return;
    }
    
    // Iterate through Object elements
    auto* objectElement = root->FirstChildElement("Object");
    while (objectElement) {
        // Get object type
        const char* type = objectElement->Attribute("type");
        if (!type) {
            std::cerr << "Object missing 'type' attribute\n";
            objectElement = objectElement->NextSiblingElement("Object");
            continue;
        }
        
        // Find factory function for this type
        auto it = objectLibrary.map.find(type);
        if (it == objectLibrary.map.end()) {
            std::cerr << "Unknown object type: " << type << "\n";
            objectElement = objectElement->NextSiblingElement("Object");
            continue;
        }
        
        // Create object using factory function
        try {
            auto obj = it->second(objectElement);
            if (obj) {
                objects.push_back(std::move(obj));
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating object of type " << type << ": " << e.what() << "\n";
        }
        
        objectElement = objectElement->NextSiblingElement("Object");
    }
    
    std::cout << "Loaded " << objects.size() << " objects from level file\n";
}

void Engine::update() {
    // Update all objects
    for (auto& obj : objects) {
        if (obj) {
            obj->update();
        }
    }
}

void Engine::draw(GraphicsEngine* graphics) {
    if (!graphics) return;
    
    // Draw all objects
    for (auto& obj : objects) {
        if (obj) {
            obj->draw(graphics);
        }
    }
}

bool Engine::run(GraphicsEngine* graphics) {
    if (!graphics || !graphics->isInitialized()) {
        return false;
    }
    
    bool running = true;
    SDL_Event event;
    
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        // Update game logic
        update();
        
        // Render frame
        graphics->beginFrame();
        draw(graphics);
        graphics->endFrame();
        
        // Small delay to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    
    return true;
}
