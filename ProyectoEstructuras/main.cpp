#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;


struct arco {
    //char destino[];
    struct vertice *destino;
    int distancia;
    struct arco *sigA;
};

struct vertice{
    char ciudad[];
    struct vertice *sigV;
    struct arco *sigA;
    bool visitado;
}*grafo;

void insertarCiudad(char pciudad[]){

    struct vertice *nnv = new vertice();
    strcpy(nnv->ciudad,pciudad);
    //nnv->ciudad=pciudad;
    nnv->visitado =false;

    nnv->sigV=grafo;
    grafo =nnv;
}
struct vertice* buscar(char pciudad[]){

    struct vertice *tempV = grafo;
    while(tempV!=NULL){

        if(tempV->ciudad==pciudad)
            return tempV;

        tempV=tempV->sigV;

    }
    return NULL;
}
void insertarRutas(char porigen[],char pdestino[], int pdistancia){

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

void cargarDatos(){
    // 32 ciudades
    insertarCiudad("San Jose");
    insertarCiudad("Naranjo");
    insertarCiudad("Palmares");
    insertarCiudad("Zarcero");
    insertarCiudad("Alajuela");
    insertarCiudad("Sucre");
    insertarCiudad("Nicoya");
    insertarCiudad("Ciudad Neilly");
    insertarCiudad("Perez Zeledon");
    insertarCiudad("Limon");
    insertarCiudad("Guapiles");
    insertarCiudad("Santa Rosa");
    insertarCiudad("Heredia");
    insertarCiudad("Sarapiqui");
    insertarCiudad("Talamanca");
    insertarCiudad("Sixaola");
    insertarCiudad("Santa Cruz");
    insertarCiudad("Los Chiles Frontera");
    insertarCiudad("Cartago");
    insertarCiudad("Turrialba");
    insertarCiudad("Jaco");
    insertarCiudad("Quepos");
    insertarCiudad("Golfito");
    insertarCiudad("Parrita");
    insertarCiudad("Paquera");
    insertarCiudad("Playa Hermosa");
    insertarCiudad("Tamarindo");
    insertarCiudad("Liberia");
    insertarCiudad("Tempisque");
    insertarCiudad("Cabuya");
    insertarCiudad("Caño Blanco");
    insertarCiudad("Fortuna");
    insertarCiudad("Manzanillo");


    insertarRutas("Los Chiles Frontera","Santa Rosa",304);

    insertarRutas("Santa Rosa","Los Chiles Frontera",304);
    insertarRutas("Santa Rosa","Liberia",73);
    insertarRutas("Santa Rosa","Tamarindo",9);

    insertarRutas("Tamarindo","Santa Rosa",9);
    insertarRutas("Tamarindo","Liberia",78);
    insertarRutas("Tamarindo","Playa Hermosa",72);

    insertarRutas("Liberia","Tamarindo",78);
    insertarRutas("Liberia","Santa Rosa",73);
    insertarRutas("Liberia","Santa Cruz",58);
    insertarRutas("Liberia","Tempisque",29);

    insertarRutas("Playa Hermosa","Nicoya",74);
    insertarRutas("Playa Hermosa","Cabuya",206);
    insertarRutas("Playa Hermosa","Tamarindo",72);

    insertarRutas("Nicoya","Playa Hermosa",74);
    insertarRutas("Nicoya","Paquera",96);

    insertarRutas("Cabuya","Playa Hermosa",206);
    insertarRutas("Cabuya","Paquera",47);

    insertarRutas("Paquera","Nicoya",96);
    insertarRutas("Paquera","Cabuya",47);
    insertarRutas("Paquera","Tempisque",150);
    insertarRutas("Paquera","Manzanillo",105);

    insertarRutas("Tempisque","Paquera",150);
    insertarRutas("Tempisque","Liberia",29);
    insertarRutas("Tempisque","Santa Cruz",85);

    insertarRutas("Santa Cruz","Tempisque",85);
    insertarRutas("Santa Cruz","Liberia",58);
    insertarRutas("Santa Cruz","Fortuna",103);

    insertarRutas("Fortuna","Santa Cruz",103);
    insertarRutas("Fortuna","Sucre",52);

    insertarRutas("Manzanillo","Palmares",93);
    insertarRutas("Manzanillo","Paquera",105);

    insertarRutas("Sucre","Fortuna",52);
    insertarRutas("Sucre","Zarcero",22);

    insertarRutas("Zarcero","Sucre",22);
    insertarRutas("Zarcero","Naranjo",19);

    insertarRutas("Naranjo","Zarcero",19);
    insertarRutas("Naranjo","Palmares",12);
    insertarRutas("Naranjo","Alajuela",19);
    insertarRutas("Naranjo","San Jose",47);

    insertarRutas("Palmares","Manzanillo",93);
    insertarRutas("Palmares","Naranjo",12);
    insertarRutas("Palmares","Jaco",83);

    insertarRutas("Jaco","Palmares",83);
    insertarRutas("Jaco","Parrita",42);

    insertarRutas("Parrita","Jaco",42);
    insertarRutas("Parrita","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
    insertarRutas("","",0);
}

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
