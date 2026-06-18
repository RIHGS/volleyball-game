// Ball.hpp
// Ball struct yaha cha - ball ko sabai data ra functions yahi define bhayeka chhan
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Constants.hpp"

struct Ball {
    sf::CircleShape shape;  
    sf::Vector2f vel;       

    // BALL OBJECT , VEL PARAMETERS
    Ball() : vel(3.f, -5.f) {
        shape.setRadius(BALL_RADIUS);
        shape.setOrigin({ BALL_RADIUS, BALL_RADIUS });
        shape.setPosition({ 200.f, 300.f });
        shape.setFillColor(sf::Color::White);
    }

    // ── point score bhayepachi ball reset garna call huncha ──
    void reset(float x) {
        shape.setPosition({ x, 250.f });
        vel = { (x < 400 ? 3.f : -3.f), -6.f };  // serve direction decide gardaichau
    }

    // ── harek frame ma call huncha - gravity ra wall bounce handle garcha ──
    void update() {
        vel.y += GRAVITY * 0.6f;  // ball player bhanda halka khascha
        shape.move(vel);

        float bx = shape.getPosition().x;
        float by = shape.getPosition().y;

        // left wall bounce
        if (bx - BALL_RADIUS < 0) {
            shape.setPosition({ BALL_RADIUS, by });
            vel.x = std::abs(vel.x); // absolute//just trying  reversing at left
        }
        // right wall bounce
        if (bx + BALL_RADIUS > W) {
            shape.setPosition({ W - BALL_RADIUS, by });
            vel.x = -std::abs(vel.x); // absolute//just trying  reversing at right
        }
        // ceiling bounce
        if (by - BALL_RADIUS < 0) {
            shape.setPosition({ bx, BALL_RADIUS });
            vel.y = std::abs(vel.y);//bychance ceiling thokyo bhane
        }
    }
};

