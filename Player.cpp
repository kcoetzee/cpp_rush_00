#include "Player.hpp"
#include <iostream>
#include <ncurses.h>
#include "Game.hpp"
#include "Projectile.hpp"


void Player::update(Game *world, int time)
{
    GameEntity::update(world,time);
    // std::cout << "Player: " << m_x << ":" << m_y << std::endl;
}

void Player::resolvecollision(Game *world)
{
    std::cout << "SADAS" << std::endl;
}

void Player::processInput(Game *world, int input)
{
    if (input == 27)
    {
        world->stopRunning();
    }

    switch(input)
    {
        case (KEY_DOWN): moveDown(world); break;
        case (KEY_UP): moveUp(world); break;
        case (KEY_RIGHT): moveRight(world); break;
        case (KEY_LEFT): moveLeft(world); break;
        case (32): shootRight(world);
    }

}

void Player::takeDamage(Game *world)
{
    world->setLives(world->getLives() - 1);
}

void Player::shootRight(Game *world)
{
    Projectile *bullet = new Projectile('*', PROJECTILE);
    bullet->setDirection(1);

    world->addEntity(bullet, m_x + 1, m_y);
}

Player::Player(char sprite, ENTITY_TYPE type)
:GameEntity(sprite, type)
{
    init_pair(PLAYER_PAIR, COLOR_WHITE, COLOR_BLUE);
    m_colorPair = PLAYER_PAIR;
}