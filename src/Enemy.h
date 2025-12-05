#ifndef Enemy_H
#define Enemy_H
#include <string>
#include "Character.h"

class Enemy : public Character
{
    public:
        Enemy(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score);
        virtual ~Enemy();

        virtual void attack() = 0;
        std::string getTag();
        
        void move() override;
        void die() override;

    protected:

        void tryAttack(Point);
        void calcPath(Point);
        int attackRange;
        int attackSpeed;
        int XP_DROP;
        double damage;
        int score; // inte en privat för olika enyme är vär olika score
    private:
        std::string tag{"enemy"};
};


class Footman :public Enemy
{
    public:
        Footman(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score);
        void attack() override;
        
};

class Kaboom:public Enemy
{
    public:
        Kaboom(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score,
        double explodeDamage, double explodeRange);
        void attack() override;

    private:
        bool isInRange(Point);
        void increaseSpeed(int);
        void explode(Point);
        double explodeRange;
        double explodeDamage;
};

class Archer:public Enemy
{
    public:
        Archer(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
            int attackRange, int attackSpeed, int XP_DROP, double damage, int score);
    void attack() override;
    
    protected:
        struct Projectles
        {

        };    
    private:
        void shoot();
};




#endif 