#include <SFML/Graphics.hpp>
#include <iostream>

double const SPEED{5};
int const FPS{60};
auto const UPDATE_TIME{sf::milliseconds(1000.0 / FPS)};

void processMovement(sf::Sprite &figure)
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

int main()
{
    sf::RenderWindow *window{new sf::RenderWindow{sf::VideoMode(1024, 768), "Hello world"}};
    sf::View *view{new sf::View{{1024 / 2, 768 / 2}, {1024, 768}}};
    window->setView(*view);

    sf::Clock clock;

    bool closed{false};

    int const r{50};
    sf::CircleShape circle1{r};
    circle1.setOrigin(r, r);
    circle1.setFillColor(sf::Color::Red);
    sf::CircleShape circle2{r};
    circle2.setOrigin(r, r);
    circle2.setFillColor(sf::Color::Green);
    sf::CircleShape circle3{r};
    circle3.setOrigin(r, r);
    circle3.setFillColor(sf::Color::Blue);

    circle1.setPosition(500, 100);
    circle2.setPosition(1000, 100);
    circle3.setPosition(1500, 100);

    sf::Texture player_texture{};
    player_texture.loadFromFile("fighter.png");
    auto player_size{player_texture.getSize()};

    sf::Sprite player{player_texture};
    player.setPosition(512, 384);
    player.setOrigin(player_size.x / 2, player_size.y);

    while (!closed)
    {
        clock.restart();
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                closed = true;
            }
        }
        processMovement(player);
        view->setCenter(player.getPosition());
        std::cout << player.getPosition().x << std::endl;
        
        std::cout << window->getView().getCenter().x << std::endl;
        window->clear();
        window->setView(*view);
        window->draw(player);
        window->draw(circle1);
        window->draw(circle2);
        window->draw(circle3);

        window->display();

        sf::Time delta{UPDATE_TIME - clock.getElapsedTime()};
        sf::sleep(delta);
    }

    return 0;
}