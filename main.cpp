#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


bool checkAABBColision(sf::RectangleShape &rect1Shape, sf::RectangleShape &rect2Shape)
{
    sf::FloatRect rect1 = rect1Shape.getGlobalBounds();
    sf::FloatRect rect2 = rect2Shape.getGlobalBounds();

    bool overlapX = rect1.left + rect1.width > rect2.left && rect1.left < rect2.left + rect2.width;
    bool overlapY = rect1.top + rect1.height > rect2.top && rect1.top < rect2.top + rect2.height;

    return overlapX && overlapY;
}

int main()
{
    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "AABB Collision");

    sf::RectangleShape rectShape1;
    rectShape1.setFillColor(sf::Color::Red);
    rectShape1.setSize(sf::Vector2f(150, 150));
    rectShape1.setOrigin (rectShape1.getSize().x / 2, rectShape1.getSize().y / 2);
    rectShape1.setPosition(vm.getDesktopMode().width / 2, vm.getDesktopMode().height / 2);


    sf::Vector2f shapePos(vm.getDesktopMode().width / 3, vm.getDesktopMode().height / 3);
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Yellow);
    shape.setSize(sf::Vector2f(150, 150));
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(shapePos);

    sf::Font font;
    if (!font.loadFromFile("fonts/ComicMono.ttf")) {
        std::cerr << "font not found\n";
        return -1;
    }

    sf::Text debugText;
    debugText.setCharacterSize(50);
    debugText.setFillColor(sf::Color::Red);
    debugText.setFont(font);


    sf::Clock clock;
    const int SPEED = 700;
    // Window
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Key handle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        sf::Vector2f prevPos = shapePos;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            shapePos.y -= SPEED * dt.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shapePos.y += SPEED * dt.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            shapePos.x -= SPEED * dt.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            shapePos.x += SPEED * dt.asSeconds();
        }

        shape.setPosition(shapePos);

        // Collision handle
        // if (shape.getGlobalBounds().intersects(rectShape1.getGlobalBounds())) {
        //     shapePos = prevPos;
        //     shape.setPosition(shapePos);
        // }

        if (checkAABBColision(shape, rectShape1)) {
            shapePos = prevPos;
            shape.setPosition(shapePos);
        }

        std::stringstream ss;
        ss << "YELLOW SHAPE\nleft: " << shape.getGlobalBounds().left << "\ntop: "
            << shape.getGlobalBounds().top << "\nheight: "
            << shape.getGlobalBounds().height << "\nwidth: "
            << shape.getGlobalBounds().width << "\n\n\n"

            << "RED SHAPE\nleft: " << rectShape1.getGlobalBounds().left << "\ntop: "
            << rectShape1.getGlobalBounds().top << "\nheight: "
            << rectShape1.getGlobalBounds().height << "\nwidth: "
            << rectShape1.getGlobalBounds().width << "\n";

        debugText.setString(ss.str());

        window.clear();
        window.draw(rectShape1);
        window.draw(shape);
        window.draw(debugText);
        window.display();
    }

    return 0;
}
