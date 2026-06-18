
#include <SFML/Graphics.hpp>  
#include <SFML/Window.hpp>    // keyboard input ra window events ko lagi
#include <cmath>              
#include <string>             


#include "constants.hpp"  
#include "player.hpp"     
#include "ball.hpp"       
#include "collision.hpp"  

int main() {

    
    sf::RenderWindow window(sf::VideoMode({ (unsigned)W, (unsigned)H }), "Volleyball");


    window.setFramerateLimit(60);

    // GROUND 
    // RectangleShape = SFML ko flat rectangle - width=800, height=20 pixels
    sf::RectangleShape ground({ (float)W, 20.f });
    ground.setPosition({ 0.f, GROUND_Y });          // GROUND_Y=550
    ground.setFillColor(sf::Color(200, 180, 100));  

    // NET
    // width=20px, height = screen bottom - NET_TOP
    sf::RectangleShape net({ 20.f, H - NET_TOP });
    net.setPosition({ NET_X, NET_TOP });           // NET_X=390, NET_TOP=400
    net.setFillColor(sf::Color(220, 220, 220));   

    //PLAYER
    // Player(x, y, color, leftLimit, rightLimit) 
    
    Player p1(200.f, GROUND_Y - P_H / 2, sf::Color(220, 60, 60), 0.f, NET_X);
    // p2: right side, blue color, NET_X+20 dekhi W(800) samma jaan sakcha
    Player p2(600.f, GROUND_Y - P_H / 2, sf::Color(60, 60, 220), NET_X + 20.f, (float)W);


    //BALL
    Ball ball;  // Ball() constructor call , position {200,300}, vel {3,-5}

   
    sf::Font font;
 
    bool hasFont = font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");

    sf::Text scoreText(font);              // score display text object
    scoreText.setCharacterSize(36);        // font size = 36px
    scoreText.setFillColor(sf::Color::White); // white text
    scoreText.setPosition({ W / 2.f - 40.f, 10.f }); // screen ko top-center ma rakhcha

    // ── GAME STATE variables ──
    bool scoreLeft = false; // P1 le score garyo ki gardaina track gardaichau
    bool scoreRight = false; // P2 le score garyo ki gardaina track gardaichau
    int  resetTimer = 0;     // score bhayepachi pause counter - 0 bhayo bhane game active cha

//GAME LOOP


    while (window.isOpen()) {  

        // ── STEP 1: EVENTS - window close button check ──
     
        while (auto event = window.pollEvent()) {
            // X button click garyo bhane window CLOSE
            if (event->is<sf::Event::Closed>()) window.close();
        }


        if (!resetTimer) {

        
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                p1.vel.x = -P_SPEED;      // LEFT
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                p1.vel.x = P_SPEED;       // RIGHT
            else
                p1.vel.x = 0;             // STATIONARY

           
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && p1.onGround) {
                p1.vel.y = P_JUMP;     // P_JUMP = -12
                p1.onGround = false;      // double-jumP PREVENTION
            }

            // P2 controls: Left arrow=left, Right arrow=right, Up arrow=jump
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                p2.vel.x = -P_SPEED;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                p2.vel.x = P_SPEED;
            else
                p2.vel.x = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && p2.onGround) {
                p2.vel.y = P_JUMP;
                p2.onGround = false;
            }
        }


        // UPDATE 

        p1.onGround = false;
        p2.onGround = false;

        p1.update();    
        p2.update();    //  movement, boundary check
        ball.update();  


        // COLLISION

        // BALL NET
        circleRect(ball, net.getGlobalBounds(), scoreLeft, scoreRight);

        // BALL P1
        circleRect(ball, p1.shape.getGlobalBounds(), scoreLeft, scoreRight);

      //BALL P2
        circleRect(ball, p2.shape.getGlobalBounds(), scoreLeft, scoreRight);


     // BALL GROUND
        if (!resetTimer && ball.shape.getPosition().y + BALL_RADIUS >= GROUND_Y) {

            if (ball.shape.getPosition().x < NET_X) {
                
                p2.score++;
                scoreRight = true;  //SERVE TRACK
            }
            else {
               
                p1.score++;
                scoreLeft = true; // P1 le score garyo
            }

            resetTimer = 90; //60 FPS DOIND THE MATH
        }

        // RESET COUNTDOwn
        if (resetTimer > 0) {
            resetTimer--;           // harek frame ma 1 ghataudaichau

            if (resetTimer == 0) {  // countdown sakkiyo - ab ball reset garne
                // ball reset AGADI scoreRight read gardaichau serve position ko lagi
                ball.reset(scoreRight ? 200.f : 600.f);
              
                scoreLeft = false; // score flags reset gardaichau next round ko lagi
                scoreRight = false;
            }
        }


        // SCORE TEXT UPDATe
        if (hasFont)
            //  "0  :  0" format ma dekhauchha
            scoreText.setString(std::to_string(p1.score) + "  :  " + std::to_string(p2.score));


       

        // new frame
        window.clear(sf::Color(30, 144, 200)); // sky blue background color

       
        window.draw(ground);     
        window.draw(net);        
        window.draw(p1.shape);  
        window.draw(p2.shape);
        window.draw(ball.shape);

        if (hasFont)
            window.draw(scoreText); 

        window.display();


    } 
} 