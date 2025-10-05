#include "Object.h"
#include "GraphicsEngine.h"
#include <functional>
#include <iostream>
#include <cmath>

// ============================================================================
// PLAYER CLASS IMPLEMENTATION
// ============================================================================

void Player::update() {
    // Player-specific update logic
    // Could include movement, input handling, etc.
}

void Player::draw(GraphicsEngine* graphics) {
    if (!graphics) return;
    
    // Draw player as a blue circle
    SDL_Color playerColor = {0, 100, 255, 255}; // Blue
    graphics->drawCircle(x, y, 0.3f, playerColor);
    
    // Draw a direction indicator (small line showing angle)
    float dirX = x + 0.4f * cos(angle * 3.14159f / 180.0f);
    float dirY = y + 0.4f * sin(angle * 3.14159f / 180.0f);
    SDL_Color lineColor = {255, 255, 255, 255}; // White
    graphics->drawLine(x, y, dirX, dirY, lineColor);
}

std::unique_ptr<Object> Player::create(const tinyxml2::XMLElement* xmlElement) {
    auto player = std::make_unique<Player>();
    
    // Parse the Body element
    auto bodyElement = xmlElement->FirstChildElement("Body");
    if (bodyElement) {
        bodyElement->QueryFloatAttribute("x", &player->x);
        bodyElement->QueryFloatAttribute("y", &player->y);
        bodyElement->QueryFloatAttribute("angle", &player->angle);
    }
    
    std::cout << "Created Player at (" << player->x << ", " << player->y << ") angle=" << player->angle << "\n";
    return player;
}

// ============================================================================
// CRATE CLASS IMPLEMENTATION
// ============================================================================

void Crate::update() {
    // Crate-specific update logic
    // Crates are typically static objects, so minimal update needed
}

void Crate::draw(GraphicsEngine* graphics) {
    if (!graphics) return;
    
    // Draw crate as a brown rectangle
    SDL_Color crateColor = {139, 69, 19, 255}; // Brown
    graphics->drawRect(x, y, 0.6f, 0.6f, crateColor);
    
    // Draw a simple cross pattern on the crate
    SDL_Color crossColor = {160, 82, 45, 255}; // Darker brown
    graphics->drawLine(x - 0.2f, y, x + 0.2f, y, crossColor);
    graphics->drawLine(x, y - 0.2f, x, y + 0.2f, crossColor);
}

std::unique_ptr<Object> Crate::create(const tinyxml2::XMLElement* xmlElement) {
    auto crate = std::make_unique<Crate>();
    
    // Parse the Body element
    auto bodyElement = xmlElement->FirstChildElement("Body");
    if (bodyElement) {
        bodyElement->QueryFloatAttribute("x", &crate->x);
        bodyElement->QueryFloatAttribute("y", &crate->y);
        bodyElement->QueryFloatAttribute("angle", &crate->angle);
    }
    
    std::cout << "Created Crate at (" << crate->x << ", " << crate->y << ") angle=" << crate->angle << "\n";
    return crate;
}

// ============================================================================
// ENEMY CLASS IMPLEMENTATION
// ============================================================================

void Enemy::update() {
    // Enemy-specific update logic
    // Could include AI behavior, pathfinding, etc.
}

void Enemy::draw(GraphicsEngine* graphics) {
    if (!graphics) return;
    
    // Draw enemy as a red triangle-like shape
    SDL_Color enemyColor = {255, 0, 0, 255}; // Red
    graphics->drawCircle(x, y, 0.25f, enemyColor);
    
    // Draw "eyes" - two small white circles
    SDL_Color eyeColor = {255, 255, 255, 255}; // White
    float eyeOffset = 0.1f;
    graphics->drawCircle(x - eyeOffset, y - eyeOffset, 0.05f, eyeColor);
    graphics->drawCircle(x + eyeOffset, y - eyeOffset, 0.05f, eyeColor);
    
    // Draw direction indicator
    float dirX = x + 0.3f * cos(angle * 3.14159f / 180.0f);
    float dirY = y + 0.3f * sin(angle * 3.14159f / 180.0f);
    SDL_Color lineColor = {255, 255, 255, 255}; // White
    graphics->drawLine(x, y, dirX, dirY, lineColor);
}

std::unique_ptr<Object> Enemy::create(const tinyxml2::XMLElement* xmlElement) {
    auto enemy = std::make_unique<Enemy>();
    
    // Parse the Body element
    auto bodyElement = xmlElement->FirstChildElement("Body");
    if (bodyElement) {
        bodyElement->QueryFloatAttribute("x", &enemy->x);
        bodyElement->QueryFloatAttribute("y", &enemy->y);
        bodyElement->QueryFloatAttribute("angle", &enemy->angle);
    }
    
    std::cout << "Created Enemy at (" << enemy->x << ", " << enemy->y << ") angle=" << enemy->angle << "\n";
    return enemy;
}
