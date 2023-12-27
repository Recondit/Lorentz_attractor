#include <SFML/Graphics.hpp>
#include <deque>

class LorenzAttractor {
public:
    float x, y, z;
    float sigma, rho, beta;

    LorenzAttractor() : x(1.0), y(0.0), z(0.0), sigma(10.0), rho(28.0), beta(8.0 / 3.0) {}

    void update(float dt) {
        float dx = sigma * (y - x);
        float dy = x * (rho - z) - y;
        float dz = x * y - beta * z;

        x += dx * dt;
        y += dy * dt;
        z += dz * dt;
    }
};

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const float trailInterval = 0.05f; // Add a point to the trail every 0.1 seconds

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lorentz Attractor");
    window.setFramerateLimit(60);

    sf::CircleShape particle(2.0f);
    particle.setFillColor(sf::Color::Red);

    LorenzAttractor attractor;

    std::deque<sf::Vector2f> trail; // Trail to store particle positions

    sf::Clock clock; // SFML clock to measure elapsed time
    float elapsedTime = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds(); // Restart the clock and get the elapsed time

        attractor.update(dt);

        particle.setPosition(
            windowWidth / 2 + attractor.x * 9,
            windowHeight / 2 - attractor.y * 9
        );

        elapsedTime += dt;

        if (elapsedTime >= trailInterval) {
            trail.push_front(particle.getPosition());
            elapsedTime = 0.0f; // Reset the elapsed time
        }

        window.clear();

        // Draw the trail
        for (const auto& point : trail) {
            particle.setPosition(point);
            window.draw(particle);
        }

        window.display();
    }

    return 0;
}
