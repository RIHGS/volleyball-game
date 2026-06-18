
#pragma once

#include <cmath>
#include "Ball.hpp"

// ball ra kunai rectangle beech collision check garcha
// collision bhayo bhane ball lai push out garcha ra velocity reflect garcha
bool circleRect(Ball& ball, sf::FloatRect rect, bool& scoreLeft, bool& scoreRight) {
    float bx = ball.shape.getPosition().x;
    float by = ball.shape.getPosition().y;
    float r = BALL_RADIUS;

    // rectangle ma ball ko sabai najik ko point khojdaichau
    float nearX = std::max(rect.position.x, std::min(bx, rect.position.x + rect.size.x));
    float nearY = std::max(rect.position.y, std::min(by, rect.position.y + rect.size.y));

    float dx = bx - nearX;
    float dy = by - nearY;

    // collision chaina bhane early exit
    if (dx * dx + dy * dy > r * r) return false;

    // ball lai rectangle bata baahira push gardaichau
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist == 0) dist = 0.01f;  // divide by zero rokcha

    float nx = dx / dist;
    float ny = dy / dist;

    ball.shape.setPosition({ bx + nx * (r - dist), by + ny * (r - dist) });

    // velocity reflect gardaichau - standard bounce formula
    float dot = ball.vel.x * nx + ball.vel.y * ny;
    ball.vel.x -= 2 * dot * nx;
    ball.vel.y -= 2 * dot * ny;


    return true;
}
