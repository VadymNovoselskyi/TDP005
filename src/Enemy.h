#ifndef Enemy_H
#define Enemy_H

#include "Character.h"

class Enemy
{
    public:
        Enemy(int attackRange, int attackSpeed, int XP_DROP, int damage, int score,/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction)
        :attackRange{attackRange}, attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score}, Charactar::Charactar(double maxHP, double currentHp, int movementSpeed, Point positon, Point direction) {}
        virtual void attack() = 0;

    protected:
    
        void tryAttack();
        void calcPath();
        int attackRange;
        int attackSpeed;
        int XP_DROP;
        double damage;
        int score; // inte en privat för olika enyme är vär olika score
}


class Enemy_1 :public Enemy
{
    public:
    void attack() override;
        
}

class Kaboom:public Enemy
{
    public:
    void attack() override;

    private:
        bool isInRange();
        void increaseSpeed(int);
        void explode();
        double explodeRange{15};
        double explodeDamage{20};
}

class Enemy_3:public Enemy
{
    public:
    void attack() override;
    
    protected:
        struct Projectles:
        {

        };    
    private:
        void shoot();
}

#endif 