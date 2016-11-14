#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define INF 99
#define tamano 33               // tamano maximo de vertices
#define nodo pair < pair<int,int> , pair<int,int> >

string todasCiudades[40];
int matAdy [tamano][tamano];
int numCiudad = 0;

struct arco {
    struct vertice *destino;
    int distancia;
    struct arco *sigA;
};

struct vertice{
    string ciudad;
    int numeroCiudad;  // cada ciudad tiene un numero de 0 a 32
    int x,y;
    struct vertice *sigV;
    struct arco *sigA;
    bool visitado;
}*grafo;


struct par {
    int valorDistancia;
    int verticeOrigen;
};


struct cmp {
    bool operator() ( const nodo &a , const nodo &b ) {
        return a.second > b.second;
    }
};

priority_queue< nodo , vector<nodo> , cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
bool visitado[tamano];      //para vértices visitados
par distancia[tamano];

void insertarCiudad(char pciudad[]){
    string ciudad = pciudad;
    struct vertice *nnv = new vertice();

    nnv->ciudad = ciudad;
    nnv->visitado =false;
    nnv->numeroCiudad = numCiudad;
    numCiudad=numCiudad+1;
    nnv->sigV=grafo;
//    nnv->x = x;
    //nnv->y = y;
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


void inicializar(){
    for( int i = 0 ; i <= tamano ; ++i ){
        distancia[ i ].valorDistancia = INF;
        distancia[ i ].verticeOrigen = INF;
        visitado[ i ] = false; //inicializamos todos los vértices como no visitados
    }
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
    struct vertice *tempV = grafo;
    struct arco *tempA;

    for(int x = 0; x < tamano; x++){
        for(int y = 0; y < tamano; y++){
            matAdy[x][y]=INF;
        }
    }

    // cargar la matriz con datos del grafo
    while (tempV!=NULL){
        tempA=tempV->sigA;
        while(tempA!=NULL){
            matAdy[tempV -> numeroCiudad][tempA -> destino -> numeroCiudad] = tempA -> distancia; // relaciona respecto a las posiciones de la matriz las ciudades ya que cada ciudad tiene un numero
            tempA = tempA -> sigA;
        }
        tempV=tempV->sigV;
    }
}

void Dijkstra(int inicio){
	inicializar();
	int x = Q.size();
	Q.push( nodo( make_pair(inicio,0),make_pair(inicio, 0))); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicio ].valorDistancia = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty() ){                   //Mientras cola no este vacia
        actual = Q.top().first.first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] )
			continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola

		visitado[ actual ] = true;         //Marco como visitado el vértice actual

        for( int i = 0 ; i < tamano ; ++i ){ //reviso sus adyacentes del vertice actual
            if(matAdy[actual][i] != INF){
	            peso = matAdy[actual][i]  ;        //peso de la arista que une actual con adyacente ( actual , adyacente )
	            if( !visitado[ i ] ){        //si el vertice adyacente no fue visitado

	            	if( distancia[ actual ].valorDistancia + peso < distancia[ i ].valorDistancia ){
				        distancia[ i ].valorDistancia = distancia[ actual ].valorDistancia + peso; //relajamos el vertice actualizando la distancia
				        distancia[ i ].verticeOrigen = actual;
				        Q.push( nodo( i , distancia[ i ].valorDistancia ) ); //agregamos adyacente a la cola de prioridad
    				}
				}
        	}
        }
    }
}

void imprimirMatAdy(){

	//int i,j;
	for(int i=0; i< tamano; i++){
		for(int j= 0; j < tamano; j++)
			cout<<matAdy[i][j]<<"    ";
		cout<<endl;

	}
}
void crearCiudades(){
    // 33 ciudades
    insertarCiudad("San Jose");
    insertarCiudad("Naranjo");
    insertarCiudad("Palmares");
    insertarCiudad("Zarcero");
    insertarCiudad("Alajuela");
    insertarCiudad("Sucre");
    insertarCiudad("Nicoya");
    insertarCiudad("Ciudad Neily");
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
}
void enlazarCiudades()
{
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
    insertarRutas("Golfito","Ciudad Neily",31);

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
    insertarRutas("Perez Zeledon","Ciudad Neily",194);
    insertarRutas("Perez Zeledon","Cartago",124);

    insertarRutas("Ciudad Neily","Golfito",31);
    insertarRutas("Ciudad Neily","Perez Zeledon",194);

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

int main(int, char const**)
{
    crearCiudades();
    enlazarCiudades();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1410, 970), "Waze - TEC");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("fondo1.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(322,5);      // image position

    // Create a graphical text to display
    sf::Font font;

    if (!font.loadFromFile("pala.ttf")) {
        return EXIT_FAILURE;
    }
    /*--------------------------------------------------------------------------------------------------*/

    //int cont=0;
    /*dentro del ciclo de la ventana lo que hay que hacer es un
    if (cont <=listaCiudades.size()) entonces
    sf::Text ciudad(cont.toString()+listaciudades.get(cont), font, 18);
    ciudad.setPosition(6,tamano); donde tamano empieza en 18 y al final del ciclo de la ventana le sumo 18
    ciudad.setFillColor(sf::Color::Black);

    y se pone un solo write al final de ciudad  */

    /*--------------------------------------------------------------------------------------------------*/

    sf::Text text1("Lista de ciudades", font, 25);
    text1.setPosition(2,0);
    text1.setFillColor(sf::Color::Black);

    sf::Text text("0 - Los Chiles Frontera", font, 18);
    text.setPosition(9,38);
    text.setFillColor(sf::Color::Black);

    sf::Text text2("1 - San Jose", font, 18); // 18 tamano fuente
    text2.setPosition(9,58);
    text2.setFillColor(sf::Color::Black);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::RectangleShape toolBar(sf::Vector2f(316,970)); /// tamano del menu donde estan las ciudades
    toolBar.setFillColor(sf::Color(70,187,217));

    /////////////////////////////////////////////////////////////
//Dibuja el primer Grafo (el circulo)
////////////////////////////////////////////////////////////

    sf::CircleShape firstGraph(7); // el 7 es el tamano de los vertices en pantalla
    firstGraph.setFillColor(sf::Color::Blue);
    firstGraph.setPosition(811, 344); // ubicacion en pantalla

    /////////////////////////////////////////////////////////////
//Dibuja el segundo grafo (el circulo)
////////////////////////////////////////////////////////////

    sf::CircleShape secondGraph(7);
    secondGraph.setFillColor(sf::Color::Red);
    secondGraph.setPosition(793, 350);


/////////////////////////////////////////////////////////////
//Dibuja la linea entre un grafo y otro.
////////////////////////////////////////////////////////////

    sf::VertexArray lines(sf::LinesStrip,2);
    lines[0].position = sf::Vector2f(799,356);
    lines[1].position = sf::Vector2f(817,350);
    lines[0].color = sf::Color::Black;
    lines[1].color = sf::Color::Black;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color(153,217,234));

        // Draw the sprite
        window.draw(sprite);

        window.draw(toolBar);

        window.draw(firstGraph);
        window.draw(secondGraph);

        window.draw(lines);

        // este draw solo se hace una vez

        // Draw the string
        window.draw(text);
        window.draw(text1);
        window.draw(text2);

        // Update the window
        window.display();
        //cont++; // futuro contador para escribir todas las ciudades
    }

    return EXIT_SUCCESS;
}
