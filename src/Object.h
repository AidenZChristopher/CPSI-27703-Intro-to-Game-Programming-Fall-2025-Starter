#pragma once
#include <memory>
#include <functional>
#include <tinyxml2.h>
#include <SDL.h>

// Forward declarations
namespace tinyxml2 {
    class XMLElement;
}
class GraphicsEngine;

// Abstract base class for all game objects
class Object {
public:
    // Position and rotation
    float x{}, y{}, angle{};
    
    // Virtual destructor
    virtual ~Object() = default;
    
    // Pure virtual methods that must be implemented by derived classes
    virtual void update() = 0;
    virtual void draw(GraphicsEngine* graphics) = 0;
    
    // Factory function type
    using FactoryFunction = std::function<std::unique_ptr<Object>(const tinyxml2::XMLElement*)>;
    
protected:
    // Protected constructor to prevent direct instantiation
    Object() = default;
};

// ============================================================================
// CONCRETE GAME OBJECT CLASSES
// ============================================================================

// Player class
class Player : public Object {
public:
    // Constructor
    Player() = default;
    
    // Virtual method implementations
    void update() override;
    void draw(GraphicsEngine* graphics) override;
    
    // Factory function
    static std::unique_ptr<Object> create(const tinyxml2::XMLElement* xmlElement);
};

// Crate class
class Crate : public Object {
public:
    // Constructor
    Crate() = default;
    
    // Virtual method implementations
    void update() override;
    void draw(GraphicsEngine* graphics) override;
    
    // Factory function
    static std::unique_ptr<Object> create(const tinyxml2::XMLElement* xmlElement);
};

// Enemy class
class Enemy : public Object {
public:
    // Constructor
    Enemy() = default;
    
    // Virtual method implementations
    void update() override;
    void draw(GraphicsEngine* graphics) override;
    
    // Factory function
    static std::unique_ptr<Object> create(const tinyxml2::XMLElement* xmlElement);
};
