#ifndef Enemy_H
#define Enemy_H
#include <string>
#include "Character.h"
#include "GameState.h"
#include "StateMachine.h"
#include "Player.h"


class Enemy : public Character
{
    public:
        Enemy(/*Charactar*/  double maxHP, double currentHP, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player);
        virtual ~Enemy();

        virtual void attack() = 0;
        std::string getTag();

        void draw(sf::RenderWindow *window)const override;
        
        //void move() override;
        void die() override;
        void onCollision(std::string const &othe) override;

    protected:

        void tryAttack(sf::Vector2f);
        //void calcPath(sf::Vector2f);
        int attackRange;
        int attackSpeed;
        int XP_DROP;
        double damage;
        int score; // inte en privat för olika enyme är vär olika score
        Player* player;
    private:
        std::string tag{"enemy"};
};


class Footman :public Enemy
{
    public:
        Footman(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player);
        void attack() override;
        void move() override;

    private:
        sf::Texture const *texture;
        
};

class Kaboom:public Enemy
{
    public:
        Kaboom(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player,
        double explodeDamage, double explodeRange);
        void attack() override;
        void move() override;

    private:
        bool isInRange(sf::Vector2f ,float len);
        void explode(sf::Vector2f);
        double explodeRange;
        double explodeDamage;
        sf::Texture const *texture;
};

class Archer:public Enemy
{
    public:
        Archer(/*Charactar*/ double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
           /*Enemy*/ int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player);
    void attack() override;
    void move() override;
    
    protected:
        struct Projectles
        {

        };    
    private:
        void shoot();
        sf::Texture const *texture;
};




#endif 