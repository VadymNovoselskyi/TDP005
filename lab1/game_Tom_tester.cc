#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

double const SPEED{5};
int const FPS{60};
auto const UPDATE_TIME{sf::milliseconds(1000.0 / FPS)};


struct Point
{
    float x;
    float y;
};

void processMovementP(sf::Sprite &figure)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        figure.move(0, -SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        figure.move(-SPEED, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        figure.move(0, SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        figure.move(SPEED, 0);
    }
}
void processMovementPE(sf::Sprite &figure1, sf::CircleShape &figure2)
{
    Point new_direction{0,0};
    //Point player {figure1.getPosition()};
    //Point enemy  {figure2.getPosition()};
    
    float rikting_x = figure1.getPosition().x - figure2.getPosition().x;
    float rikting_y = figure1.getPosition().y - figure2.getPosition().y;


    float len = std::sqrt(rikting_x * rikting_x + rikting_y * rikting_y);

 
    //normalize
    if(len != 0)
    {
        new_direction.x = (rikting_x / len);
        new_direction.y = (rikting_y / len);
    }
    figure2.move(sf::Vector2f(new_direction.x * SPEED, new_direction.y * SPEED));

}

void update(sf::RenderWindow &window, sf::Drawable const &figure)
{
    window.clear(sf::Color::Blue);

    window.draw(figure);
    window.display();
}

int main()
{
    sf::RenderWindow window{sf::VideoMode(1024, 768), "Hello world"};
    sf::Clock clock;

    bool closed{false};

    int const r{50};
    sf::CircleShape circle{r};
    circle.setOrigin(r, r);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(100, 100);

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
        //processMovement(player);
        window.clear(sf::Color::Blue);
        processMovementP(player);
        processMovementPE(player, circle);
        window.draw(player);
        window.draw(circle);

        window.display();

        sf::Time delta{UPDATE_TIME - clock.getElapsedTime()};
        sf::sleep(delta);
    }

    return 0;
}
