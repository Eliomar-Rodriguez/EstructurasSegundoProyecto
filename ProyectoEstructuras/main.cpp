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

void insertarCiudad(char pciudad){

struct vertice *nnv = new vertice();
nnv->ciudad=pciudad;
nnv->visitado =false;

nnv->sigV=grafo;
grafo =nnv;
}

void insertarRutas(char porigen,char pdestino, int pdistancia){

    struct vertice *origen =buscar (porigen);
    struct vertice *destino =buscar (pdestino);
    if((origen ==NULL )||(destino ==NULL)){
        cout << "Datos inconsistentes\n";
        return;
    }

    struct arco *nna = new arco();
    nna->destino=destino;
    nna->distancia=pdistancia;

    nna->sigA =origen->sigA;
    origen->sigA=nna;
}

int main()
{
    insertarCiudad('H');
    insertarCiudad('F');
    insertarCiudad('E');
    insertarCiudad('D');
    insertarCiudad('C');
    insertarCiudad('B');
    insertarCiudad('A');
    insertarRutas('A','C',7);
    insertarRutas('A','D',2);
    insertarRutas('E','F',3);
    insertarRutas('D','E',4);
    insertarRutas('C','D',5);
    insertarRutas('B','C',6);
    insertarRutas('A','B',7);
    insertarRutas('D','H',8);
    insertarRutas('F','H',1);


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
