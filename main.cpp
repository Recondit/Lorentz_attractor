#include <SFML/Graphics.hpp>
#include <vector>

float sigma = 10.0;
float rho = 28.0;
float beta = 8.0 / 3.0;


struct Pendulum {
    float length;
    float angle;
    float angularVelocity;
    float damping;
};

struct Particle {
    sf::Vector3f position;
    sf::Color color;
    sf::VertexArray path;
};

void LorentzAttractor(){
    // Create a window
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lorentz Attractor");

    // Create particles
    const int numParticles = 100; // Adjust the number of particles as needed
    std::vector<Particle> particles(numParticles);

    // Initialize particles with different initial positions and create their paths
    for (int i = 0; i < numParticles; ++i) {
        particles[i].position.x = static_cast<float>(rand() % 75 - 5);
        particles[i].position.y = static_cast<float>(rand() % 75 - 5);
        particles[i].position.z = static_cast<float>(rand() % 75 - 5);

        particles[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255);

        particles[i].path.setPrimitiveType(sf::LineStrip);
        particles[i].path.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + particles[i].position.x * 18, windowHeight / 2 - particles[i].position.y * 18), particles[i].color));
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update particles
        for (int i = 0; i < numParticles; ++i) {
            float x = particles[i].position.x;
            float y = particles[i].position.y;
            float z = particles[i].position.z;

            float dx = sigma * (y - x);
            float dy = x * (rho - z) - y;
            float dz = x * y - beta * z;

            // Update 
            particles[i].position.x += dx * 0.001f;
            particles[i].position.y += dy * 0.001f;
            particles[i].position.z += dz * 0.001f;

            // Append the current position to the path
            particles[i].path.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + particles[i].position.x * 18, windowHeight / 2 - particles[i].position.y * 18), particles[i].color));
        }

        // Draw
        window.clear();

        // Draw the paths
        for (int i = 0; i < numParticles; ++i) {
            window.draw(particles[i].path);
        }

        // Draw the current positions
        for (int i = 0; i < numParticles; ++i) {
            sf::CircleShape circle(1.0f);
            circle.setPosition(windowWidth / 2 + particles[i].position.x * 18, windowHeight / 2 - particles[i].position.y * 18);
            circle.setFillColor(particles[i].color);
            window.draw(circle);
        }

        window.display();
    }
}


void DoublePendulum() {
     // Create a window
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lorentz Attractor");
    // Create bob
    Pendulum bob = {150.0f, 2.0f, 0.0f , 0.01f};

   

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        // Update
        bob.angularVelocity += (-9.8 / bob.length * std::sin(bob.angle) - bob.damping * bob.angularVelocity) * 0.01f;
        bob.angle += bob.angularVelocity * 0.01f;
        printf("%f\n", bob.angle);
        printf("%f\n", bob.angularVelocity);







        // Draw
        window.clear();
        sf::Vector2f bobPosition = sf::Vector2f(bob.length * std::sin(bob.angle) , bob.length * std::cos(bob.angle));
        sf::CircleShape ball(20.0f);
        ball.setPosition(windowWidth/2 + bobPosition.x, windowHeight/2 + bobPosition.y);
        ball.setFillColor(sf::Color::Red);
        window.draw(ball);
        window.display();
    }


}

int main() {
    DoublePendulum();
    // LorentzAttractor();
    return 0;
}


