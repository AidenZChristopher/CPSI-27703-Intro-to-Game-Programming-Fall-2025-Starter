#include "Engine.h"
#include "GraphicsEngine.h"
#include <iostream>

int main() {
    std::string path = "assets/level.xml";
    
    // Create graphics engine
    GraphicsEngine graphics;
    if (!graphics.init("Object Factory Demo")) {
        std::cerr << "Failed to initialize graphics\n";
        return 1;
    }
    
    // Create engine and load level
    Engine engine(path); // STACK allocation

    // Print object details
    for (int i = 0; i < engine.objects.size(); ++i) {
        std::cout << "[Main] obj#" << i
                  << " pos=(" << engine.objects[i]->x
                  << ", " << engine.objects[i]->y << ")"
                  << " angle=" << engine.objects[i]->angle << "\n";
    }

    std::cout << "\nStarting graphics demo...\n";
    std::cout << "Close the window to exit.\n";
    
    // Run the graphics demo
    engine.run(&graphics);

    std::cout << "\nObject factory system demonstration complete!\n";
    return 0;
}
