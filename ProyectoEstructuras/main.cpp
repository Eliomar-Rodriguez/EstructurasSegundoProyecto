#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include<string>
#include<sstream>
#include "windows.h"
#include <sstream>
#include<time.h>
#include "fstream"

using namespace std;

#define INF 99             // tamano maximo de vertices
#define nodo pair < int, int >
int tamano=33;
int** matAdy;
int numCiudad = 0;

int tamanoFuente = 38;
sf::RenderWindow window(sf::VideoMode(1408, 970), "Waze - TEC");
int contador = 32;
int pos = 18;
fstream archivo("grafo.saiyajin", ios::in | ios::out |ios::binary | ios::trunc);
struct arco {
    struct vertice *destino;
    struct vertice *origen;
    int distancia;
    string stdestino,storigen;
    struct arco *sigA;
};

struct vertice{
    string ciudad;
    int numeroCiudad;  // cada ciudad tiene un numero de 0 a 32
    int x,y,cantidadArcos;
    struct vertice *sigV;
    struct arco *sigA;
    bool visitadoP1;
    bool visitadoP2;
}*grafo,*ini,*punteroGrafo; // iniGraCarg es el inicio del grafo cargado del archivo

int calculartamano(){
    int cont=0;
    grafo=ini;
    while(grafo!=NULL){
        grafo=grafo->sigV;
        cont++;
    }
        matAdy=new int*[cont];
        for (int x=0;x<cont;x++){
            matAdy[x]=new int[cont];
        }
        tamano=cont;
        contador=cont-1;
};


struct par {
    int valorDistancia;
    int verticeOrigen;
};


struct cmp {
    bool operator() ( const nodo &a , const nodo &b ) {
        return a.first > b.second;
    }
};

priority_queue< nodo , vector<nodo> , cmp > V1; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
priority_queue< nodo , vector<nodo> , cmp > V2;
bool* visitadoV1=new bool[tamano];      //para vértices visitados
bool* visitadoV2=new bool[tamano];
par* distancia1=new par[tamano];
par* distancia2=new par[tamano];

void insertarCiudad(char pciudad[], int x,int y){
    string ciudad = pciudad;
    struct vertice *nnv = new vertice();

    nnv->ciudad = ciudad;
    nnv->visitadoP1 =false;
    nnv->visitadoP2 =false;
    nnv->numeroCiudad = numCiudad;
    numCiudad=numCiudad+1;
    nnv->sigV=NULL;
    nnv->y = y;
    nnv->x = x;

    if (grafo==NULL){
        grafo = nnv;
        ini = nnv;
    }
    else{
        grafo->sigV = nnv;
        grafo = nnv;
    }
    //grafo = nnv;

}
struct vertice* buscar(char pciudad[]){
    struct vertice *tempV = ini;
    while(tempV!=NULL){
        if(tempV->ciudad==pciudad)
            return tempV;
        tempV=tempV->sigV;
    }
    return NULL;
}


void inicializar(){
    for( int i = 0 ; i <= tamano ; ++i ){
        distancia1[ i ].valorDistancia = INF;
        distancia1[ i ].verticeOrigen = INF;
        distancia2[ i ].valorDistancia = INF;
        distancia2[ i ].verticeOrigen = INF;
        visitadoV1[ i ] = false; //inicializamos todos los vértices como no visitados
        visitadoV2[ i ] = false;
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
    nna->stdestino=pdestino;
    nna->storigen=porigen;
    nna->destino=destino;
    nna->origen = origen;

    nna->distancia=pdistancia;
    if (origen->sigA==NULL){
        origen->sigA=nna;
    }
    else{
        arco* aux=origen->sigA;
        while(aux->sigA!=NULL){
            aux=aux->sigA;
        }
        aux->sigA=nna;
    }
    origen->cantidadArcos ++;
}

void cargarMatAdy(){
    struct vertice *tempV = ini;
    struct arco *tempA;

    for(int x = 0; x < tamano; x++){ // tamano por la cantidad de vertices de manera generica
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
char* tochar(string x){
    char* y=new char[100]();
    for (int z=0;z<x.size();z++){
        y[z]=x[z];
    }
    return y;
}
void leerGrafo(){ // como identifico que estoy leyendo?

    struct vertice *tempV;
    struct arco *tempA;
    grafo=NULL;
    ini=NULL;
    archivo.seekg(0,ios::beg);
    tamano=0;
    archivo.read(reinterpret_cast<char *> (&tamano), sizeof(int));
    cout<<tamano<<endl;
    char* charx;
    char* chary;
    for (int z=0;z<tamano;z++){
        archivo.read(reinterpret_cast<char *> (&tempV), sizeof(vertice));
        cout<<tempV->ciudad<<"-"<<tempV->x<<"-"<<tempV->y<<"-"<<tempV->numeroCiudad<<"-"<<tempV->cantidadArcos<<endl;
        charx=tochar(tempV->ciudad);
        insertarCiudad(charx,tempV->x,tempV->y);
    }
    while(!archivo.eof()){
        archivo.read(reinterpret_cast<char *> (&tempA), sizeof(arco));
        cout<<tempA->storigen<<"-"<<tempA->stdestino<<"-"<<tempA->distancia<<endl;
        charx=tochar(tempA->storigen);
        chary=tochar(tempA->stdestino);
        insertarRutas(charx,chary,tempA->distancia);
    }
    calculartamano();
    //archivo.
}

void escribirGrafo(){ // escribe el grafo en el archivo
    // primero inserto el vertice y luego todos los arcos que tenga y asi sucesivamente

    struct vertice *tempV=ini;
    struct arco *tempA;
    if (tempV==NULL){
        cout<<"NULL"<<endl;
    }
    archivo.seekg(0,ios::end);
    archivo.write(reinterpret_cast<char *> (&tamano), sizeof(int));
    char* charx;
    char* chary;
    while(tempV!=NULL){
        cout<<tempV->ciudad<<"-"<<tempV->x<<"-"<<tempV->y<<"-"<<tempV->numeroCiudad<<"-"<<tempV->cantidadArcos<<endl;
        archivo.write(reinterpret_cast<char *> (&tempV), sizeof(vertice));
        tempV = tempV->sigV;
    }
    tempV=ini;
    while(tempV!=NULL){
        tempA=tempV->sigA;
        while(tempA!=NULL){
            cout<<tempA->storigen<<"-"<<tempA->stdestino<<"-"<<tempA->distancia<<endl;
            archivo.write(reinterpret_cast<char *> (&tempA), sizeof(vertice));
            tempA = tempA ->sigA;
        }
        tempV = tempV->sigV;
    }
}

void Dijkstra(int inicioV1){

	inicializar();
	int x = V1.size();
	V1.push( nodo(inicioV1,0)); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia1[ inicioV1 ].valorDistancia = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !V1.empty() ){                   //Mientras cola no este vacia

        actual = V1.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        V1.pop();                           //Sacamos el elemento de la cola
        if( visitadoV1[ actual ] )
			continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola

		visitadoV1[ actual ] = true;         //Marco como visitado el vértice actual

        for( int i = 0 ; i < tamano ; ++i ){ //reviso sus adyacentes del vertice actual
            if(matAdy[actual][i] != INF){
	            peso = matAdy[actual][i]  ;        //peso de la arista que une actual con adyacente ( actual , adyacente )
	            if( !visitadoV1[ i ] ){        //si el vertice adyacente no fue visitado

	            	if( distancia1[ actual ].valorDistancia + peso < distancia1[ i ].valorDistancia ){
				        distancia1[ i ].valorDistancia = distancia1[ actual ].valorDistancia + peso; //relajamos el vertice actualizando la distancia
				        distancia1[ i ].verticeOrigen = actual;
				        V1.push( nodo( i , distancia1[ i ].valorDistancia ) ); //agregamos adyacente a la cola de prioridad
    				}
				}
        	}
        }
    }
}
void imprimirRutaCorta(int destinoF1, int destinoF2){
    int dest1 = destinoF1-1;
    int dest2 = destinoF2-1;
    stack<int> pila;
    stack<int> pila2;
    int dist1=distancia1[dest1].valorDistancia;
    int dist2=distancia2[dest2].valorDistancia;
    while(dest1 != INF)
    {
        pila.push(dest1);
        dest1= distancia1[dest1].verticeOrigen;
    }

    cout <<endl<< "Ruta mas corta para llegar a " << destinoF1 << " desde el vertice inicial es:" << endl;
    while(pila.size()!=0)
    {
        cout << pila.top()+1 ;
        pila.pop();
        if (pila.size() != 0)
            cout << " - ";
    }
    cout << endl;
    cout << "Distancia total de la ruta: " << dist1 << endl;

    while(dest2 != INF)
    {
        pila2.push(dest2);
        dest2= distancia2[dest2].verticeOrigen;
    }

    cout <<endl<< "Ruta mas corta para llegar a " << destinoF2 << " desde el vertice es:" << endl;
    while(pila2.size()!=0)
    {
        cout << pila2.top()+1 ;
        pila2.pop();
        if (pila2.size() != 0)
            cout << " - ";
    }
    cout << endl;
    cout << "Distancia total de la ruta: " << dist2 << endl;
}
string cargarNombre(int pos){
    vertice* aux;
    aux=ini;
    if (pos>tamano){
        return "Invalido";
    }
    for (int x=0;x<pos;x++){
        aux=aux->sigV;
    }
    return aux->ciudad;
}
void imprimirMatAdy(){
    int cont=0;
    string nombres [tamano]={};
    vertice* aux;
    aux=ini;
    while (aux!=NULL){
        nombres[tamano-cont]=aux->ciudad;
        aux=aux->sigV;
        cont++;
    }
    cout<<cont<<endl;
    cont=0;
	for(int i=0; i< tamano; i++){
        cout<<endl<<"Vertice "<<i<<", "<<cargarNombre(i)<<endl;
		for(int j= 0; j < tamano; j++){
            if (matAdy[i][j]!=99){
                cout<<j<<": "<<matAdy[i][j]<<" "<<endl;
                cont++;
            }
		}
	}
	cout<<endl<<cont/2<<" arcos en total, "<<tamano<<" vertices"<<endl;
}
void crearCiudades(){
    // 33 ciudades
    insertarCiudad("San Jose",902,404);
    insertarCiudad("Naranjo",811,344);
    insertarCiudad("Palmares",793,350);
    insertarCiudad("Zarcero",807,305);
    insertarCiudad("Alajuela",861,357);
    insertarCiudad("Sucre",805,275);
    insertarCiudad("Nicoya",500,325);
    insertarCiudad("Ciudad Neily",1263,779);
    insertarCiudad("Perez Zeledon",1034,555);
    insertarCiudad("Limon",1232,382);
    insertarCiudad("Guapiles",1014,310);
    insertarCiudad("Santa Rosa",375,272);
    insertarCiudad("Puerto Viejo",924,246);
    insertarCiudad("Talamanca",1040,525);
    insertarCiudad("Sixaola",1361,516);
    insertarCiudad("Santa Cruz",442,280);
    insertarCiudad("Los Chiles Frontera",720,77);
    insertarCiudad("Cartago",970,419);
    insertarCiudad("Turrialba",1041,393);
    insertarCiudad("Jaco",747,487);
    insertarCiudad("Quepos",888,538);
    insertarCiudad("Golfito",1212,791);
    insertarCiudad("Parrita",837,517);
    insertarCiudad("Paquera",643,427);
    insertarCiudad("Playa Hermosa",408,202);
    insertarCiudad("Liberia",480,183);
    insertarCiudad("Tempisque",473,135);
    insertarCiudad("Cabuya",591,480);
    insertarCiudad("Caño Blanco",1156,328);
    insertarCiudad("Fortuna",739,237);
    insertarCiudad("Manzanillo",569,464);
    calculartamano();
}

void enlazarCiudades(){
    // insercion de los arcos en total son 46

    insertarRutas("San Jose","Naranjo",47);
    insertarRutas("San Jose","Alajuela",19);
    insertarRutas("San Jose","Puerto Viejo",86);
    insertarRutas("San Jose","Cartago",25);

    insertarRutas("Naranjo","Zarcero",19);
    insertarRutas("Naranjo","Palmares",12);
    insertarRutas("Naranjo","Alajuela",19);
    insertarRutas("Naranjo","San Jose",47);

    insertarRutas("Palmares","Manzanillo",93);
    insertarRutas("Palmares","Naranjo",12);
    insertarRutas("Palmares","Jaco",83);

    insertarRutas("Zarcero","Sucre",22);
    insertarRutas("Zarcero","Naranjo",19);

    insertarRutas("Alajuela","Naranjo",19);
    insertarRutas("Alajuela","San Jose",19);
    insertarRutas("Alajuela","Puerto Viejo",80);

    insertarRutas("Sucre","Fortuna",52);
    insertarRutas("Sucre","Zarcero",22);

    insertarRutas("Nicoya","Playa Hermosa",74);
    insertarRutas("Nicoya","Paquera",96);

    insertarRutas("Ciudad Neily","Golfito",31);
    insertarRutas("Ciudad Neily","Perez Zeledon",194);

    insertarRutas("Perez Zeledon","Quepos",87);
    insertarRutas("Perez Zeledon","Golfito",193);
    insertarRutas("Perez Zeledon","Ciudad Neily",194);
    insertarRutas("Perez Zeledon","Cartago",124);

    insertarRutas("Limon","Caño Blanco",94);
    insertarRutas("Limon","Guapiles",95);
    insertarRutas("Limon","Turrialba",119);
    insertarRutas("Limon","Talamanca",239);
    insertarRutas("Limon","Sixaola",92);

    insertarRutas("Guapiles","Caño Blanco",71);
    insertarRutas("Guapiles","Limon",95);

    insertarRutas("Santa Rosa","Los Chiles Frontera",304);
    insertarRutas("Santa Rosa","Liberia",73);

    insertarRutas("Puerto Viejo","Alajuela",80);
    insertarRutas("Puerto Viejo","San Jose",86);

    insertarRutas("Talamanca","Limon",239);
    insertarRutas("Talamanca","Turrialba",155);

    insertarRutas("Sixaola","Limon",92);

    insertarRutas("Santa Cruz","Tempisque",85);
    insertarRutas("Santa Cruz","Liberia",58);
    insertarRutas("Santa Cruz","Fortuna",103);

    insertarRutas("Los Chiles Frontera","Santa Rosa",304);

    insertarRutas("Cartago","San Jose",25);
    insertarRutas("Cartago","Turrialba",66);
    insertarRutas("Cartago","Perez Zeledon",124);

    insertarRutas("Turrialba","Cartago",66);
    insertarRutas("Turrialba","Talamanca",155);
    insertarRutas("Turrialba","Limon",119);

    insertarRutas("Jaco","Palmares",83);
    insertarRutas("Jaco","Parrita",42);

    insertarRutas("Quepos","Parrita",30);
    insertarRutas("Quepos","Perez Zeledon",87);
    insertarRutas("Quepos","Golfito",179);

    insertarRutas("Golfito","Quepos",179);
    insertarRutas("Golfito","Perez Zeledon",193);
    insertarRutas("Golfito","Ciudad Neily",31);

    insertarRutas("Parrita","Jaco",42);
    insertarRutas("Parrita","Quepos",30);

    insertarRutas("Paquera","Nicoya",96);
    insertarRutas("Paquera","Cabuya",47);
    insertarRutas("Paquera","Tempisque",150);
    insertarRutas("Paquera","Manzanillo",105);

    insertarRutas("Playa Hermosa","Nicoya",74);
    insertarRutas("Playa Hermosa","Cabuya",206);

    insertarRutas("Liberia","Santa Rosa",73);
    insertarRutas("Liberia","Santa Cruz",58);
    insertarRutas("Liberia","Tempisque",29);

    insertarRutas("Tempisque","Paquera",150);
    insertarRutas("Tempisque","Liberia",29);
    insertarRutas("Tempisque","Santa Cruz",85);

    insertarRutas("Cabuya","Playa Hermosa",206);
    insertarRutas("Cabuya","Paquera",47);

    insertarRutas("Caño Blanco","Guapiles",71);
    insertarRutas("Caño Blanco","Limon",94);

    insertarRutas("Fortuna","Santa Cruz",103);
    insertarRutas("Fortuna","Sucre",52);

    insertarRutas("Manzanillo","Palmares",93);
    insertarRutas("Manzanillo","Paquera",105);
}
void dibujararcos(){
    grafo=ini;
    while (grafo!=NULL){
        arco* aux=grafo->sigA;
        while(aux!=NULL){
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(aux->origen->x+5, aux->origen->y+5)),
                sf::Vertex(sf::Vector2f(aux->destino->x+5, aux->destino->y+5))
            };
            sf::Color color=sf::Color::Blue;
            line[1].color=color;
            line[0].color=color;
            window.draw(line, 2, sf::Lines);
            aux=aux->sigA;
        }

    grafo=grafo->sigV;
    }
}
void dibujarvertices(){
    int cont=1;
    sf::CircleShape selloVertice(10);
    grafo=ini;
    sf::Font font;
        if (!font.loadFromFile("comic.ttf")) {
        }
    sf::Text texto("", font, 12);
    while(grafo!=NULL){
        selloVertice.setPosition(grafo->x,grafo->y);
        selloVertice.setFillColor(sf::Color::Red);
        window.draw(selloVertice);
        stringstream ss;
        ss << cont;
        texto.setString(ss.str());
        texto.setPosition(grafo->x+5,grafo->y+5); //donde tamano empieza en 18 y al final del ciclo de la ventana le sumo 18
        texto.setFillColor(sf::Color::Black);
        window.draw(texto);
        grafo=grafo->sigV;
        cont++;
    }
    }
int main(int, char const**){
    // crear grafo para luego cargarlo al archivo
    crearCiudades();
    enlazarCiudades();

    // cargar grafo desde archivo

    cargarMatAdy();
    imprimirMatAdy();

    Dijkstra(5);
    //Dijkstra2(7);
    imprimirRutaCorta(1,12);
    Dijkstra(5);
//    imprimirRutaCorta(13);
    struct vertice * tempV = ini;

/*==========================================================================================================*/
/*=====================                         PARTE GRAFICA                          =====================*/
/*==========================================================================================================*/
    // Create the main window
 //   sf::RenderWindow window(sf::VideoMode(1408, 970), "Waze - TEC");//
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
        if (!font.loadFromFile("comic.ttf")) {
            return EXIT_FAILURE;
        }
    sf::Text titulo("Lista de ciudades", font, 25);
    titulo.setPosition(2,0);
    titulo.setFillColor(sf::Color::Black);

    sf::Text ciudad("",font,0);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::RectangleShape toolBar(sf::Vector2f(316,970)); /// tamano del menu donde estan las ciudades
    toolBar.setFillColor(sf::Color(70,187,217));

    /////////////////////////////////////////////////////////////
//Dibuja el primer Grafo (el circulo)
////////////////////////////////////////////////////////////
/*
    sf::CircleShape firstGraph(7); // el 7 es el tamano de los vertices en pantalla
    firstGraph.setFillColor(sf::Color::Blue);
    firstGraph.setPosition(811, 344); // ubicacion en pantalla
*/
    /////////////////////////////////////////////////////////////
//Dibuja el segundo grafo (el circulo)
////////////////////////////////////////////////////////////

    /*sf::CircleShape secondGraph(7);
    secondGraph.setFillColor(sf::Color::Red);
    secondGraph.setPosition(793, 350);*/


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

        string result;
        string hola = "numero";
        std::stringstream sstm;
        sstm << hola << contador;
        result = sstm.str();


        //string hola = "numero",result;
        //result = hola + winstl::int_to_string(contador);
        ////hola = hola + result;
        contador++;
        //cout<<result<<endl;
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

        //ventana.draw(lines);

        // este draw solo se hace una vez

        // Draw the string

        //ventana.draw(titulo);


        // Update the window
        //ventana.display();
        //cont++; // futuro contador para escribir todas las ciudades



        window.draw(titulo);

        struct vertice * tem = ini;

        sf::Text ciudad(tem->ciudad, font, 18);

        //cout<<"fuente";
        while (contador >=1){
            pos += 22;
            string numero;
            //cout<<contador<<" - ";
            std::stringstream sstm;
            sstm << tamano+1-contador << ") " << tem->ciudad; // concatenando
            numero = sstm.str();
            ciudad.setString(numero);
            ciudad.setPosition(18,pos); //donde tamano empieza en 18 y al final del ciclo de la ventana le sumo 18
            ciudad.setFillColor(sf::Color::Black);
            window.draw(ciudad);
            tem = tem ->sigV;
            contador--;
        }
        // Update the window
        dibujararcos();
        dibujarvertices();
        window.display();
        contador = tamano-1; // futuro contador para escribir todas las ciudade
        pos = 18;
    }

    return EXIT_SUCCESS;
}


