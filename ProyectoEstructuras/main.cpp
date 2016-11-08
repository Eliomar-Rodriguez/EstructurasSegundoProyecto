#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;
#define INF 99
struct arco {
    //char destino[];
    struct vertice *destino;
    int distancia;
    struct arco *sigA;
};

struct vertice{
    string ciudad;
    struct vertice *sigV;
    struct arco *sigA;
    bool visitado;
}*grafo;

void insertarCiudad(char pciudad[]){

    struct vertice *nnv = new vertice();string ciudad = pciudad;
    nnv->ciudad = ciudad;
    //strcpy(nnv->ciudad,ciudad);
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
void cargarMatAdy(){
    int matAdy [33][33];
    for(int x = 0; x < 33; x++){
        for(int y = 0; y < 33; y++){
            matAdy[x][y]=INF;
        }
    }
    // el x es la ciudad de inicio y la y es el destino y el numero es la distancia entre ciudades
    matAdy[17][11]=304; // los chiles F - santa rosa

    matAdy[11][17]=304; // santa rosa - los chiles F
    matAdy[11][27]=73;  // santa rosa - liberia
    matAdy[11][26]=9;   // santa rosa - tamarindo

    matAdy[26][11]=9;   // tamarindo - santa rosa
    matAdy[26][27]=78;  // tamarindo - liberia
    matAdy[26][25]=72;  // tamarindo - plata hermosa

    matAdy[27][26]=78;  // liberia - tamarindo
    matAdy[27][11]=73;  // liberia - santa rosa
    matAdy[27][16]=58;  // liberia santa cruz
    matAdy[27][28]=29;  // liberia tempisque

    matAdy[25][6]=74;   // playa hermosa - nicoya
    matAdy[25][29]=206; // playa hermosa - cabuya
    matAdy[25][26]=72;  // playa hermosa - tamarindo

    matAdy[6][25]=74;   // nicoya - playa hermosa
    matAdy[6][24]=96;   // nicoya - paquera

    matAdy[29][25]=206; // cabuya - playa hermosa
    matAdy[29][24]=47;  // cabuya - paquera

    matAdy[24][6]=96;   // paquera - nicoya
    matAdy[24][29]=47;  // paquera - cabuya
    matAdy[24][28]=150; // paquera - tempisque
    matAdy[24][32]=105; // paquera - manzanillo

    matAdy[28][24]=150; // tempisque - paquera
    matAdy[28][27]=29;  // tempisque - liberia
    matAdy[28][16]=85;  // tempisque - santa cruz

    matAdy[16][28]=85;  // santa cruz - tempisque
    matAdy[16][27]=58;  // santa cruz - liberia
    matAdy[16][31]=103; // santa cruz - fortuna

    matAdy[31][16]=103; // fortuna - santa cruz
    matAdy[31][5]=52;   // fortuna - sucre

    matAdy[32][2]=93;   // manzanillo - palmares
    matAdy[32][24]=105; // manzanillo - paquera

    matAdy[5][31]=52;   // sucre - fortuna
    matAdy[5][3]=22;    // sucre - zarcero

    matAdy[3][5]=22;    // zarcero - sucre
    matAdy[3][1]=19;    // zarcero - naranjo

    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
    matAdy[][]=;
}
void cargarDatos(){
    // 33 ciudades
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

    // insercion de los arcos en total son 46
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
    // falta de aqui hasta abajo
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
    insertarRutas("Parrita","Quepos",30);

    insertarRutas("Quepos","Parrita",30);
    insertarRutas("Quepos","Perez Zeledon",87);
    insertarRutas("Quepos","Golfito",179);

    insertarRutas("Golfito","Quepos",179);
    insertarRutas("Golfito","Perez Zeledon",193);
    insertarRutas("Golfito","Ciudad Neilly",31);

    insertarRutas("Alajuela","Naranjo",19);
    insertarRutas("Alajuela","San Jose",19);
    insertarRutas("Alajuela","Heredia",41);
    insertarRutas("Alajuela","Sarapiqui",85);

    insertarRutas("San Jose","Naranjo",47);
    insertarRutas("San Jose","Alajuela",19);
    insertarRutas("San Jose","Heredia",13);
    insertarRutas("San Jose","Cartago",25);

    insertarRutas("Cartago","San Jose",25);
    insertarRutas("Cartago","Turrialba",66);
    insertarRutas("Cartago","Perez Zeledon",124);

    insertarRutas("Heredia","Alajuela",41);
    insertarRutas("Heredia","San Jose",13);
    insertarRutas("Heredia","Sarapiqui",85);

    insertarRutas("Sarapiqui","Heredia",85);
    insertarRutas("Sarapiqui","Alajuela",85);
    insertarRutas("Sarapiqui","Guapiles",49);

    insertarRutas("Perez Zeledon","Quepos",87);
    insertarRutas("Perez Zeledon","Golfito",193);
    insertarRutas("Perez Zeledon","Ciudad Neilly",194);
    insertarRutas("Perez Zeledon","Cartago",124);

    insertarRutas("Ciudad Neilly","Golfito",31);
    insertarRutas("Ciudad Neilly","Perez Zeledon",194);

    insertarRutas("Turrialba","Cartago",66);
    insertarRutas("Turrialba","Talamanca",155);
    insertarRutas("Turrialba","Limon",119);

    insertarRutas("Guapiles","Caño Blanco",71);
    insertarRutas("Guapiles","Limon",95);
    insertarRutas("Guapiles","Sarapiqui",49);

    insertarRutas("Caño Blanco","Guapiles",71);
    insertarRutas("Caño Blanco","Limon",94);

    insertarRutas("Limon","Caño Blanco",94);
    insertarRutas("Limon","Guapiles",95);
    insertarRutas("Limon","Turrialba",119);
    insertarRutas("Limon","Talamanca",239);
    insertarRutas("Limon","Sixaola",92);

    insertarRutas("Sixaola","Limon",92);

    insertarRutas("Talamanca","Limon",239);
    insertarRutas("Talamanca","Turrialba",155);
}

int main()
{
    cargarDatos();

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
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
