#pragma once
#include <SDL.h>
#include <memory>
#include <string>

class GraphicsEngine {
public:
    // Constructor/Destructor
    GraphicsEngine();
    ~GraphicsEngine();
    
    // Initialization
    bool init(const std::string& title = "Object Factory Demo");
    void shutdown();
    
    // Rendering
    void beginFrame();
    void endFrame();
    void clear();
    
    // Drawing primitives
    void drawRect(float x, float y, float width, float height, SDL_Color color);
    void drawCircle(float x, float y, float radius, SDL_Color color);
    void drawLine(float x1, float y1, float x2, float y2, SDL_Color color);
    
    // Coordinate conversion
    struct ScreenPoint {
        int x, y;
    };
    ScreenPoint worldToScreen(float worldX, float worldY) const;
    
    // Getters
    SDL_Renderer* getRenderer() const { return renderer_; }
    bool isInitialized() const { return renderer_ != nullptr; }
    
    // Constants
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;
    static constexpr float PIXELS_PER_METER = 50.0f;
    
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    bool initialized_ = false;
};

