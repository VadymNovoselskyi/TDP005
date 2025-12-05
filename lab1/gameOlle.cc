#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

double const SPEED{5};
int const FPS{60};
auto const UPDATE_TIME{sf::milliseconds(1000.0 / FPS)};
struct Point
{
    float x;
    float y;
};
Point operator+=(Point lhs, Point rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
Point operator-=(Point lhs, Point rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

Point operator*=(Point p, float d)
{
    p.x *= d;
    p.y *= d;
    return p;
}
void processMovement(sf::Sprite &figure)
{
    Point direction{0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // figure.move(0, -SPEED);
        direction.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // figure.move(-SPEED, 0);
        direction.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // figure.move(0, SPEED);
        direction.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // figure.move(SPEED, 0);
        direction.x = 1;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);
    }

    figure.move(sf::Vector2f(direction.x * SPEED, direction.y * SPEED));
}
void takeDamage(int x,sf::RectangleShape &CurrentHp)
{
    float newSize = 150 - x;
    CurrentHp.setSize(sf::Vector2f(newSize, 50.f));
    // HP -= x;
    // int HPtextSave = 100;
    // hPText.setString(std::to_string(HPtextSave));
}
int main()
{
    sf::RenderWindow window{sf::VideoMode(1024, 768), "Hello world"};
    sf::Clock clock;

    bool closed{false};

    int const r{50};
    sf::CircleShape circle{r};
    circle.setOrigin(r, r);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(100, 100);

    // Hp box background + outline
    sf::RectangleShape HpBox(sf::Vector2(150.f, 50.f));
    HpBox.setSize(sf::Vector2f(150.f, 50.f));
    HpBox.setFillColor(sf::Color(128, 0, 0));
    HpBox.setPosition(10, 10);

    // current hp
    sf::RectangleShape CurrentHp(sf::Vector2(150.f, 50.f));
    CurrentHp.setSize(sf::Vector2f(150.f, 50.f));
    CurrentHp.setFillColor(sf::Color(204, 0, 0));
    CurrentHp.setPosition(10, 10);

    // hp text
    // sf::Font defaultFont{};
    // defaultFont.loadFromFile("Orbitron-Bold.ttf");
    // sf::Text hpText{};
    // double HP = 100;
    // hpText.setFont(defaultFont);
    // hpText.setString(std::to_string(HP));
    // hpText.setFillColor(sf::Color::Black);
    // hpText.setStyle(sf::Text::Bold);
    // hpText.setCharacterSize(20);
    // hpText.setPosition(50, 28);
    // player
    sf::Texture player_texture{};
    player_texture.loadFromFile("../imgs/fighter.png");
    auto player_size{player_texture.getSize()};

    sf::Sprite player{player_texture};
    player.setPosition(512, 384);
    player.setOrigin(player_size.x / 2, player_size.y);

    while (!closed)
    {
        clock.restart();
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                closed = true;
            }
        }
        processMovement(player);
        window.clear(sf::Color::Blue);

        window.draw(player);
        window.draw(HpBox);
        window.draw(CurrentHp);
        //window.draw(hpText);
        window.display();
        takeDamage(25, CurrentHp);

        sf::Time delta{UPDATE_TIME - clock.getElapsedTime()};
        sf::sleep(delta);
    }

    return 0;
}