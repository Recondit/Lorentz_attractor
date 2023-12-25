#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Create a circle shape
    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(375.0f, 275.0f); // Center the circle

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Draw the circle
        window.clear();
        window.draw(circle);
        window.display();
    }
    printf("Hello World!\n");
    return 0;
}