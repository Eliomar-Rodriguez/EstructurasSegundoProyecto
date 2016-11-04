#include <SFML/Graphics.hpp>


struct arco {
    //char destino;
    struct vertice *destino;
    int distancia;
    struct arco *sigA;
};

struct vertice{
    char ciudad;
    struct vertice *sigV;
    struct arco *sigA;
    bool visitado;
}*grafo;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(200.f);

    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
