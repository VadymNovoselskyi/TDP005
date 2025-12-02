#include <SFML/Graphics.hpp>

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
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(100, 100);

    sf::Texture player_texture{};
    player_texture.loadFromFile("lab1/fighter.png");
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
        window.draw(player);
        update(window, player);

        sf::Time delta{UPDATE_TIME - clock.getElapsedTime()};
        sf::sleep(delta);
    }

    return 0;
}