#include <SFML/Graphics.hpp>
#include <cmath>

// Lorentz system parameters
const float sigma = 10.0f;
const float rho = 28.0f;
const float beta = 8.0f / 3.0f;

// Particle structure
struct Particle {
    sf::Vector3f position;
    sf::Color color;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lorentz Butterfly Simulation");

    // Create particles
    const int numParticles = 1000;
    std::vector<Particle> particles(numParticles);

    for (auto& particle : particles) {
        particle.position = sf::Vector3f(rand() % 800, rand() % 600, rand() % 600);
        particle.color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update particle positions using Lorentz equations
        for (auto& particle : particles) {
            float x = particle.position.x;
            float y = particle.position.y;
            float z = particle.position.z;

            float dx = sigma * (y - x);
            float dy = x * (rho - z) - y;
            float dz = x * y - beta * z;

            particle.position.x += dx * 0.005;
            particle.position.y += dy * 0.005;
            particle.position.z += dz * 0.005;
        }

        // Draw particles with rotation around the center
        window.clear();

        for (const auto& particle : particles) {
            sf::CircleShape circle(2);

            // Calculate rotated position around the center of the screen
            float rotatedX = particle.position.x + window.getSize().x / 2;
            float rotatedY = particle.position.y + window.getSize().y / 2;

            circle.setPosition(rotatedX, rotatedY);
            circle.setFillColor(particle.color);
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}
