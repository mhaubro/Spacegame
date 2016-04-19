#pragma once

class Player
{
protected:
    float x,y;
    float angle;
    
public:
    Player(float x, float y);
    
    void update(float t);
    void render();
    
  
};
