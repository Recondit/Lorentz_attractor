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
    sf::Vector3f Constant;
};

sf::Color randColor(float x , float y , float z){
    float dist = (x*x + y*y + z*z)/(3*(70*70));
    sf::Vector3f color1 = sf::Vector3f(255 , 0 , 0);
    sf::Vector3f color2 = sf::Vector3f(0 , 255 , 255);

    sf::Vector3f color = color1 + dist*(color2 - color1);
    return sf::Color(color.x , color.y , color.z);
}

void SimpleLorentzAttractor(){
    // Create a window
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lorentz Attractor");

    // Create particles
    const int numParticles = 100; // Adjust the number of particles as needed
    std::vector<Particle> particles(numParticles);
    const int remove = 60; // Higher value means longer paths

    // Initialize particles with different initial positions and create their paths
    for (int i = 0; i < numParticles; ++i) {
        particles[i].position.x = static_cast<float>(rand() % 75 - 5);
        particles[i].position.y = static_cast<float>(rand() % 75 - 5);
        particles[i].position.z = static_cast<float>(rand() % 75 - 5);

        particles[i].color = randColor(particles[i].position.x , particles[i].position.y , particles[i].position.z);

        float randomFactorx = (rand() % 141 - 70) / 100.0f;
        float randomFactory = (rand() % 141 - 70) / 100.0f;
        float randomFactorz = (rand() % 141 - 70) / 100.0f;
        particles[i].Constant = sf::Vector3f(sigma * (1.0f+randomFactorx) , rho * (1.0f + randomFactory) , beta * (1.0f + randomFactorz));

        printf("%f\n", particles[i].Constant.x);

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

        for (int i = 0; i < numParticles; ++i) {
            int r = rand() % 5;

            if (particles[i].path.getVertexCount() > 2*remove){
            sf::VertexArray copy(sf::LineStrip, particles[i].path.getVertexCount() - r);
            for (int j = r; j < particles[i].path.getVertexCount(); ++j) {
                        copy[j-r] = particles[i].path[j];
            }
            particles[i].path = copy;
            }

            


            particles[i].path.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + particles[i].position.x * 18, windowHeight / 2 - particles[i].position.y * 18), particles[i].color));
        }
        window.display();
    }
}




void LorentzAttractor(){
    // Create a window
    const int windowWidth = 1600;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lorentz Attractor");

    // Create particles
    const int numParticles = 1000; // Adjust the number of particles as needed
    std::vector<Particle> particles(numParticles);
    const int remove = 60; // Higher value means longer paths

    // Initialize particles with different initial positions and create their paths
    for (int i = 0; i < numParticles; ++i) {
        particles[i].position.x = static_cast<float>(rand() % 75 - 5);
        particles[i].position.y = static_cast<float>(rand() % 75 - 5);
        particles[i].position.z = static_cast<float>(rand() % 75 - 5);

        particles[i].color = randColor(particles[i].position.x , particles[i].position.y , particles[i].position.z);

        float randomFactorx = (rand() % 141 - 70) / 100.0f;
        float randomFactory = (rand() % 141 - 70) / 100.0f;
        float randomFactorz = (rand() % 141 - 70) / 100.0f;
        particles[i].Constant = sf::Vector3f(sigma * (1.0f+randomFactorx) , rho * (1.0f + randomFactory) , beta * (1.0f + randomFactorz));

        printf("%f\n", particles[i].Constant.x);

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

            float dx = particles[i].Constant.x  * (y - x);
            float dy = x * (particles[i].Constant.y - z) - y;
            float dz = x * y - particles[i].Constant.z * z;

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

        for (int i = 0; i < numParticles; ++i) {
            int r = rand() % 5;

            if (particles[i].path.getVertexCount() > 2*remove){
            sf::VertexArray copy(sf::LineStrip, particles[i].path.getVertexCount() - r);
            for (int j = r; j < particles[i].path.getVertexCount(); ++j) {
                        copy[j-r] = particles[i].path[j];
            }
            particles[i].path = copy;
            }

            


            particles[i].path.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + particles[i].position.x * 18, windowHeight / 2 - particles[i].position.y * 18), particles[i].color));
        }
        window.display();
    }
}


// Constants
const double g = 9.81;  // acceleration due to gravity

// Function to update the state of the double pendulum using the Runge-Kutta method
void update(double& theta1, double& theta2, double& omega1, double& omega2, double dt, double l1, double l2, double m1, double m2) {
    // Runge-Kutta method
    double k11, k12, k21, k22, k31, k32, k41, k42;
    
    k11 = dt * omega1;
    k21 = dt * omega2;
    
    k12 = dt * (-g * (2 * m1 + m2) * std::sin(theta1) - m2 * g * std::sin(theta1 - 2 * theta2) -
                2 * std::sin(theta1 - theta2) * m2 * (std::pow(omega2, 2) * l2 + std::pow(omega1, 2) * l1 * std::cos(theta1 - theta2))) /
               (l1 * (2 * m1 + m2 - m2 * std::cos(2 * (theta1 - theta2))));
    
    k22 = dt * (2 * std::sin(theta1 - theta2) * (std::pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * std::cos(theta1) +
                                                  std::pow(omega2, 2) * l2 * m2 * std::cos(theta1 - theta2))) /
               (l2 * (2 * m1 + m2 - m2 * std::cos(2 * (theta1 - theta2))));
    
    k31 = dt * (omega1 + 0.5 * k12);
    k41 = dt * (omega2 + 0.5 * k22);
    
    k32 = dt * (-g * (2 * m1 + m2) * std::sin(theta1 + 0.5 * k11) -
                m2 * g * std::sin((theta1 + 0.5 * k11) - 2 * (theta2 + 0.5 * k21)) -
                2 * std::sin((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)) * m2 *
                    (std::pow((omega2 + 0.5 * k22), 2) * l2 + std::pow((omega1 + 0.5 * k12), 2) * l1 * std::cos((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)))) /
               (l1 * (2 * m1 + m2 - m2 * std::cos(2 * ((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)))));
    
    k42 = dt * (2 * std::sin((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)) *
                    (std::pow((omega1 + 0.5 * k12), 2) * l1 * (m1 + m2) +
                     g * (m1 + m2) * std::cos((theta1 + 0.5 * k11)) +
                     std::pow((omega2 + 0.5 * k22), 2) * l2 * m2 * std::cos((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)))) /
               (l2 * (2 * m1 + m2 - m2 * std::cos(2 * ((theta1 + 0.5 * k11) - (theta2 + 0.5 * k21)))));
    
    theta1 += k31;
    theta2 += k41;
    omega1 += k32;
    omega2 += k42;
}





void DoublePendulum() {
    // Create a window
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Double Pendulum");

    // Pendulum parameters
    double theta1 = 3.14 / 2.0;  // initial angle of the first pendulum
    double theta2 = 3.14 / 2.0;  // initial angle of the second pendulum
    double omega1 = 0.0;         // initial angular velocity of the first pendulum
    double omega2 = 0.0;         // initial angular velocity of the second pendulum
    double l1 = 150.0;           // length of the first pendulum arm
    double l2 = 150.0;           // length of the second pendulum arm
    double m1 = 10.0;            // mass of the first bob
    double m2 = 10.0;            // mass of the second bob

    // Create a vertex array for the pendulum path
    sf::VertexArray path1(sf::LineStrip);
    sf::VertexArray string1(sf::LineStrip);
    sf::VertexArray path2(sf::LineStrip);
    sf::VertexArray string2(sf::LineStrip);

    // Define two points for the line
    sf::Vector2f center(windowWidth/2.0f, windowHeight/2.0f);


    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::VertexArray line1(sf::Lines, 2);
        sf::VertexArray line2(sf::Lines, 2);
        line1[0].position = center;
    

        // Update pendulum state
        update(theta1, theta2, omega1, omega2, 0.01, l1, l2, m1, m2);

        // Append the current position to the paths
        path1.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + l1 * std::sin(theta1), windowHeight / 2 + l1 * std::cos(theta1)), sf::Color::Red));
        path2.append(sf::Vertex(sf::Vector2f(windowWidth / 2 + l1 * std::sin(theta1) + l2 * std::sin(theta2), windowHeight / 2 + l1 * std::cos(theta1) + l2 * std::cos(theta2)), sf::Color::Green));

        line1[1].position = sf::Vector2f(windowWidth / 2 + l1 * std::sin(theta1), windowHeight / 2 + l1 * std::cos(theta1));

        line2[0].position = sf::Vector2f(windowWidth / 2 + l1 * std::sin(theta1), windowHeight / 2 + l1 * std::cos(theta1));
        line2[1].position = sf::Vector2f(windowWidth / 2 + l1 * std::sin(theta1) + l2 * std::sin(theta2), windowHeight / 2 + l1 * std::cos(theta1) + l2 * std::cos(theta2));

        // Draw
        window.clear();


        // Draw the paths
        window.draw(path1);
        window.draw(line1);
        window.draw(line2);
        window.draw(path2);

        // Draw the pendulum bobs
        sf::CircleShape bob1(m1);
        bob1.setPosition(windowWidth / 2 + l1 * std::sin(theta1) - m1, windowHeight / 2 + l1 * std::cos(theta1) - m1);
        bob1.setFillColor(sf::Color::Red);
        window.draw(bob1);

        sf::CircleShape bob2(m2);
        bob2.setPosition(windowWidth / 2 + l1 * std::sin(theta1) + l2 * std::sin(theta2) - m2, windowHeight / 2 + l1 * std::cos(theta1) + l2 * std::cos(theta2) - m2);
        bob2.setFillColor(sf::Color::Green);
        window.draw(bob2);

        window.display();
    }

}

int main() {
    DoublePendulum();
    // LorentzAttractor(); 
    // SimpleLorentzAttractor();
    return 0;
}


