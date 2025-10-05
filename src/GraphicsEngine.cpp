#include "GraphicsEngine.h"
#include <iostream>
#include <cmath>

GraphicsEngine::GraphicsEngine() {
    std::cout << "GraphicsEngine created\n";
}

GraphicsEngine::~GraphicsEngine() {
    shutdown();
}

bool GraphicsEngine::init(const std::string& title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
        return false;
    }
    
    window_ = SDL_CreateWindow(title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window_) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }
    
    renderer_ = SDL_CreateRenderer(window_, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window_);
        SDL_Quit();
        return false;
    }
    
    initialized_ = true;
    std::cout << "GraphicsEngine initialized successfully\n";
    return true;
}

void GraphicsEngine::shutdown() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    if (initialized_) {
        SDL_Quit();
        initialized_ = false;
    }
}

void GraphicsEngine::beginFrame() {
    if (!renderer_) return;
    clear();
}

void GraphicsEngine::endFrame() {
    if (!renderer_) return;
    SDL_RenderPresent(renderer_);
}

void GraphicsEngine::clear() {
    if (!renderer_) return;
    SDL_SetRenderDrawColor(renderer_, 20, 20, 30, 255); // Dark blue background
    SDL_RenderClear(renderer_);
}

void GraphicsEngine::drawRect(float x, float y, float width, float height, SDL_Color color) {
    if (!renderer_) return;
    
    auto screenPos = worldToScreen(x, y);
    int screenWidth = static_cast<int>(width * PIXELS_PER_METER);
    int screenHeight = static_cast<int>(height * PIXELS_PER_METER);
    
    SDL_Rect rect = {
        screenPos.x - screenWidth / 2,
        screenPos.y - screenHeight / 2,
        screenWidth,
        screenHeight
    };
    
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer_, &rect);
}

void GraphicsEngine::drawCircle(float x, float y, float radius, SDL_Color color) {
    if (!renderer_) return;
    
    auto center = worldToScreen(x, y);
    int screenRadius = static_cast<int>(radius * PIXELS_PER_METER);
    
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    
    // Simple circle drawing algorithm
    for (int dx = -screenRadius; dx <= screenRadius; dx++) {
        for (int dy = -screenRadius; dy <= screenRadius; dy++) {
            if (dx * dx + dy * dy <= screenRadius * screenRadius) {
                SDL_RenderDrawPoint(renderer_, center.x + dx, center.y + dy);
            }
        }
    }
}

void GraphicsEngine::drawLine(float x1, float y1, float x2, float y2, SDL_Color color) {
    if (!renderer_) return;
    
    auto start = worldToScreen(x1, y1);
    auto end = worldToScreen(x2, y2);
    
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer_, start.x, start.y, end.x, end.y);
}

GraphicsEngine::ScreenPoint GraphicsEngine::worldToScreen(float worldX, float worldY) const {
    ScreenPoint screenPos;
    screenPos.x = static_cast<int>(SCREEN_WIDTH / 2 + worldX * PIXELS_PER_METER);
    screenPos.y = static_cast<int>(SCREEN_HEIGHT / 2 - worldY * PIXELS_PER_METER); // Flip Y axis
    return screenPos;
}

