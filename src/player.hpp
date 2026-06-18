#pragma once
// Player.hpp
// Player struct yaha cha - player ko sabai data ra functions yahi define bhayeka chhan
#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

struct Player {
    sf::RectangleShape shape;  // screen ma dekhiney rectangle
    sf::Vector2f vel;         // velocity - left/right/up/down speed //cordinatess
    bool onGround = false;   // jump garna milcha ki milaina
    int  score = 0;         // yo player ko score
    float minX, maxX;      // LEFT RIGHT BOUNDS

    // ── constructor - player object banaudako bela run huncha ──
    Player(float x, float y, sf::Color col, float mn, float mx)//it can take 4 input values
        : vel(0, 0), minX(mn), maxX(mx)
    {
        shape.setSize({ P_W, P_H });
        shape.setOrigin({ P_W / 2, P_H / 2 });
        shape.setPosition({ x, y });
        shape.setFillColor(col);
    }

    // ── harek frame ma call huncha - gravity, movement, bounds check garcha ──
    void update() {
        vel.y += GRAVITY;      // gravity t
        shape.move(vel);       // velocity anusaar shape move 

        // ground check - player ground bhanda tala gayo bhane snap back
        if (shape.getPosition().y + P_H / 2 >= GROUND_Y) {//limiting our players from falling to ground y-axis
            shape.setPosition({ shape.getPosition().x, GROUND_Y - P_H / 2 });
            vel.y = 0;
            onGround = true;
        }

        // horizontal bounds check 

        float px = shape.getPosition().x;
        if (px - P_W / 2 < minX) { //limiting our players from falling to ground tara this time from x-axis
            shape.setPosition({ minX + P_W / 2, shape.getPosition().y });
            vel.x = 0;//left
        }
        if (px + P_W / 2 > maxX) {
            shape.setPosition({ maxX - P_W / 2, shape.getPosition().y });
            vel.x = 0;//right
        }
    }
};

