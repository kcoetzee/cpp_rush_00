#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Game.hpp"
#include <iostream>

void Enemy::update(Game *world, int time)
{
    if (time >= 10){
        GameEntity::update(world, time);
        // std::cout << m_x << ":" << m_y << std::endl;
        moveLeft(world);
    }

    if (m_shootTimer.elapsed() >= 3)
    {
        bool canShoot = false;
        // only shoot if it's clear
        for (int i = 0; i < m_x; i++)
        {
            if (world->board[i][m_y].getEntity() != 0 && world->board[i][m_y].getEntity()->getType() != ENEMY){
                canShoot = true;
            }
        }

        if (canShoot)
        {
            shootLeft(world);
            m_shootTimer.reset();
        }
    }


}

Enemy::Enemy(char sprite, ENTITY_TYPE type)
:GameEntity(sprite, type)
{
    m_shootTimer.reset();
}

void Enemy::resolveCollision(Game *world, GameEntity *other)
{
    if (other->getType() == PLAYER)
    {
        Player* p = dynamic_cast<Player*>(other);
        p->takeDamage(world);
    }
    die();
}

void Enemy::shootLeft(Game *world)
{
    Projectile *bullet = new Projectile('=', PROJECTILE);
    bullet->setDirection(-1);

    world->addEntity(bullet, m_x - 1, m_y);   
}