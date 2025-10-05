#include "Library.h"
#include "Object.h"  // Now includes Player, Crate, Enemy
#include <iostream>

Library::Library() {
    // Register all object types with their factory functions
    map["Player"] = Player::create;
    map["Crate"] = Crate::create;
    map["Enemy"] = Enemy::create;
    
    std::cout << "Library initialized with " << map.size() << " object types\n";
}
