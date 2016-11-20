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
int tamano=33,rutaTotal=0;
int** matAdy;
int numCiudad = 0;

int tamanoFuente = 38;
sf::RenderWindow window(sf::VideoMode(1408, 970), "Waze - TEC");
int contador = 32;
int pos = 18;
sf::Font font;

struct arco {
    struct vertice *destino;
    struct vertice *origen;
    int distancia;
    char stdestino[30],storigen[30];
    struct arco *sigA;
};

struct vertice{
    char ciudad[30];
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

priority_queue< nodo , vector<nodo> , cmp > V1;
priority_queue< nodo , vector<nodo> , cmp > V2;

void insertarCiudad(char pciudad[], int x,int y){
    string ciudad = pciudad;
    struct vertice *nnv = new vertice();

    strcpy(nnv->ciudad,pciudad);
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
}

struct vertice* buscar(string pciudad){
    struct vertice *tempV = ini;
    while(tempV!=NULL){
        string comp1=tempV->ciudad;
        string comp2=pciudad;
        if(comp1==comp2)
            return tempV;
        tempV=tempV->sigV;
    }
    return NULL;
}

struct vertice* buscar(int indice){
    grafo =ini;
    for(int x=0;x<indice;x++){
        grafo=grafo->sigV;
    }
    return grafo;
};

int buscar(vertice* x){
    grafo=ini;
    for(int y=0;y<tamano;y++){
        if (grafo->ciudad==x->ciudad){
            return y;
        }
        grafo=grafo->sigV;
    }
}

void insertarRutas(char porigen[30],char pdestino[30], int pdistancia){

    struct vertice *origen =buscar (porigen);
    struct vertice *destino =buscar (pdestino);
    if((origen ==NULL )||(destino ==NULL)){
        cout << "Datos inconsistentes\n";
        return;
    }

    struct arco *nna = new arco();
    strcpy(nna->stdestino,pdestino);
    strcpy(nna->storigen,porigen);
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

char* toChar(string x){
    char* y=new char[100]();
    for (int z=0;z<x.size();z++){
        y[z]=x[z];
    }
    return y;
}
bool leerGrafo(char nombre[30]){
    std::ifstream existe(nombre);
    if (!existe)
    {
        std::cout << "Fichero no encontrado" << std::endl;
        return false;
    }
    fstream archivo(nombre, ios::in | ios::out |ios::binary);
    struct vertice tempV;
    struct arco tempA;
    grafo=NULL;
    ini=NULL;
    archivo.seekg(0);
    archivo.read(reinterpret_cast<char *> (&tamano), sizeof(int));
    cout<<"\nEl grafo cargado tiene "<<tamano<<"vertices"<<endl;
    char* charx;
    char* chary;
    for (int z=0;z<tamano;z++){
        archivo.read(reinterpret_cast<char *> (&tempV), sizeof(vertice));
        insertarCiudad(tempV.ciudad,tempV.x,tempV.y);
    }
    while(!archivo.eof()){
        archivo.read(reinterpret_cast<char *> (&tempA), sizeof(arco));
        insertarRutas(tempA.storigen,tempA.stdestino,tempA.distancia);
    }
    calculartamano();
    return true;
}

void escribirGrafo(){ // escribe el grafo en el archivo
    // primero inserto el vertice y luego todos los arcos que tenga y asi sucesivamente
    fstream archivo("grafo31V.txt", ios::in | ios::out |ios::binary | ios::trunc);
    struct vertice *tempV=ini;
    struct arco *tempA;
    if (tempV==NULL){
        cout<<"NULL"<<endl;
    }
    archivo.seekg(0);
    tamano;
    archivo.write(reinterpret_cast<char *> (&tamano), sizeof(int));
    while(tempV!=NULL){
        archivo.seekg(0, ios::end);
        archivo.write(reinterpret_cast<char *> (tempV), sizeof(vertice));
        tempV = tempV->sigV;
    }
    tempV=ini;
    while(tempV!=NULL){
        tempA=tempV->sigA;
        while(tempA!=NULL){
            archivo.seekg(0,ios::end);
            archivo.write(reinterpret_cast<char *> (tempA), sizeof(arco));
            tempA = tempA ->sigA;
        }
        tempV = tempV->sigV;
    }
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

stack<int> Dijkstra(int origen,int destino,stack<int> baneados){
    cout<<"\nDesde la ciudad #"<<origen+1<<" hasta la ciudad #"<<destino+1<<" hay: ";
    int actual=origen;
    stack<int> camino;
    int** tabla=new int*[tamano];
    for (int x=0;x<tamano;x++){
        tabla[x]=new int[3];
        tabla[x][0]=INF;
        tabla[x][1]=INF;
        tabla[x][2]=0;
    }
    tabla[origen][0]=0;
    tabla[origen][1]=origen;
    tabla[origen][2]=1;
    vertice* tempV=buscar(actual);
    arco* tempA=tempV->sigA;
    while(!baneados.empty()){
        tabla[baneados.top()][2]=1;
        baneados.pop();
    }
    for (int x=0;x<tamano;x++){
        tempV=buscar(actual);
        tempA=tempV->sigA;
        while(tempA!=NULL){
            if (tabla[buscar(tempA->destino)][0]==INF || tabla[buscar(tempA->destino)][0]>tabla[actual][0]+tempA->distancia){
                tabla[buscar(tempA->destino)][0]=tabla[actual][0]+tempA->distancia;
                tabla[buscar(tempA->destino)][1]=actual;

            }
            tempA=tempA->sigA;
        }
        for(int y=0;y<tamano;y++){
            if (tabla[y][0]!=INF&&tabla[y][2]!=1){
                if (tabla[y][0]<tabla[actual][0]||tabla[actual][2]==1){
                    actual=y;
                }
            }
        }
        tabla[actual][2]=1;
    }/*
    for (int a=0;a<tamano;a++){
        if(tabla[a][1]!=INF){
            cout<<a+1<<": "<<tabla[a][0]<<" - "<<tabla[a][1]+1<<" * "<<tabla[a][2]<<endl;
        }
        else{
            cout<<a+1<<": "<<tabla[a][0]<<" - "<<"INF"<<" * "<<tabla[a][2]<<endl;
        }
    }*/
    rutaTotal = tabla[destino][0];
    cout<<rutaTotal<<" KM"<<endl;
    actual=destino;
    camino.push(actual);
    while(actual!=origen){
        actual=tabla[actual][1];
        if (actual==99){
            cout<<"Ya no hay rutas hacia la ciudad # "<<destino<<""<<endl;
            stack<int> negativo;
            return negativo;
        }
        camino.push(actual);
    }
    cout<<endl;
    return camino;
}

void crearCiudades(){
    insertarCiudad("San Jose",902,404);
    insertarCiudad("Naranjo",811,344);
    insertarCiudad("Palmares",730,350);
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
    insertarCiudad("Canio Blanco",1156,328);
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

    insertarRutas("Limon","Canio Blanco",94);
    insertarRutas("Limon","Guapiles",95);
    insertarRutas("Limon","Turrialba",119);
    insertarRutas("Limon","Talamanca",239);
    insertarRutas("Limon","Sixaola",92);

    insertarRutas("Guapiles","Canio Blanco",71);
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

    insertarRutas("Canio Blanco","Guapiles",71);
    insertarRutas("Canio Blanco","Limon",94);

    insertarRutas("Fortuna","Santa Cruz",103);
    insertarRutas("Fortuna","Sucre",52);

    insertarRutas("Manzanillo","Palmares",93);
    insertarRutas("Manzanillo","Paquera",105);
}

void dibujarRuta(stack<int> pila,sf::Color color,int desp){
    while(pila.size()>1)
    {
        int origen=pila.top();
        pila.pop();
        int destino=pila.top();
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(buscar(origen)->x+10+desp, buscar(origen)->y+10+desp)),
            sf::Vertex(sf::Vector2f(buscar(destino)->x+10+desp, buscar(destino)->y+10+desp))
        };
        line[1].color=color;
        line[0].color=color;
        window.draw(line, 2, sf::Lines);
    }
}

void dibujarPesos(){
    grafo=ini;
    while (grafo!=NULL){
        arco* aux=grafo->sigA;
        while(aux!=NULL){
            stringstream ss;
            ss << aux->distancia;
            sf::Text label(ss.str(), font, 10);
            label.setPosition(((aux->origen->x+aux->destino->x+10)/2),((aux->origen->y+aux->destino->y+10)/2));
            label.setColor(sf::Color::Magenta);
            window.draw(label);
            aux=aux->sigA;
        }
    grafo=grafo->sigV;
    }
}

void dibujarArcos(){
    grafo=ini;
    while (grafo!=NULL){
        arco* aux=grafo->sigA;
        while(aux!=NULL){
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(aux->origen->x+10, aux->origen->y+10)),
                sf::Vertex(sf::Vector2f(aux->destino->x+10, aux->destino->y+10))
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

void dibujarVertices(){
    int cont=1;
    sf::CircleShape selloVertice(10);
    grafo=ini;
    sf::Text texto("", font, 12);
    while(grafo!=NULL){
        selloVertice.setPosition(grafo->x,grafo->y);
        selloVertice.setFillColor(sf::Color::Green);
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

void dibujarNombres(){
    stack<int> baneado,pila;
    contador=tamano;
    pos = 18;
    struct vertice * tem = ini;
    sf::Text ciudad(tem->ciudad, font, 18);
    while (contador >=1){
        pos += 22;
        string numero;
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
}

int main(int, char const**){
    stack<int> baneado,baneado2,pila,pila2;
    font.loadFromFile("comic.ttf");
    // crear grafo para luego cargarlo al archivo
    bool y=true;
    bool jugadores;
    cout<<" ========================================="<<endl;
    cout<<"|               WAZE - TEC                |"<<endl;
    cout<<" ========================================="<<endl;
    cout<<"Modo de busqueda"<<endl<<"\t1. Un jugador"<<endl<<"\t2. Dos jugadores"<<endl<<"\t";
    while(true){
        string op;
        try{
            cin>>op;
            if(op=="1"){
                jugadores=false;
                break;
            }
            else if(op=="2"){
                jugadores=true;
                break;
            }
            else{
                cout<<"Ingrese la opcion 1 o 2"<<endl;
            }
        }
        catch(int x){
            cout<<"Ingrese la opcion 1 o 2"<<endl;
        }
    }
    while(y){
        cout<<endl<<"Como desea trabajar?"<<endl<<"\t1. Cargando grafo desde un archivo"<<endl<<"\t2. Con un grafo creado a pie \"quemado\""<<endl<<"\t";
        string x;
        cin>>x;
        if(x=="2"){
            crearCiudades();
            enlazarCiudades();
            escribirGrafo();
            y=false;
        }
        else if(x=="1"){
            cout<<"Escriba el nombre del archivo que contiene el grafo a trabajar: ";
            char dir[30];
            cin>>dir;
            y=!leerGrafo(dir);
        }
        else{
            cout<<"Debe de ingresar la opcion 1 o 2"<<endl;
        }
    }
    // cargar grafo desde archivo

    //cargarMatAdy();
    //imprimirMatAdy();
    struct vertice * tempV = ini;

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

    sf::Font font;
        if (!font.loadFromFile("comic.ttf")) {
            return EXIT_FAILURE;
        }
    sf::Text titulo("Lista de ciudades", font, 25);
    titulo.setPosition(2,0);
    titulo.setFillColor(sf::Color::Black);

    sf::Text ciudad("",font,0);

    sf::RectangleShape toolBar(sf::Vector2f(316,970)); /// tamano del menu donde estan las ciudades
    toolBar.setFillColor(sf::Color(70,187,217));


    sf::VertexArray lines(sf::LinesStrip,2);
    lines[0].position = sf::Vector2f(799,356);
    lines[1].position = sf::Vector2f(817,350);
    lines[0].color = sf::Color::Black;
    lines[1].color = sf::Color::Black;
    window.draw(sprite);
    window.draw(toolBar);

    dibujarNombres();

    window.draw(titulo);

    dibujarArcos();

    dibujarPesos();

    dibujarVertices();

    window.display();
    grafo=ini;
    cout<< " ================================" <<endl;
    cout<< "|        Lista de ciudades       |" <<endl;
    cout<< " ================================" <<endl;
    for(int x=1;x<tamano+1;x++){
        cout<<x<<". "<<grafo->ciudad<<endl;
        grafo=grafo->sigV;
    }
    int origen,destino,origen2,destino2;
    while(true){
        try{
            cout<<endl<<"Jugador 1: Ingresa la ciudad de partida ";
            cin>>origen;
            while(origen>tamano||origen<=0){
                cout<<endl<<"El indice del origen se encuentra fuera del dominio del grafo ";
                cout<<endl<<"\nJugador 1: Vuelva a ingresa la ciudad de origen ";
                cin>>origen;
            }
            cout<<endl<<"Jugador 1: Ingresa la ciudad de destino ";
            cin>>destino;
            while(destino>tamano||destino<=0){
                cout<<endl<<"El indice del destino se encuentra fuera del dominio del grafo ";
                cout<<endl<<"\nJugador 1: Vuelva a ingresa la ciudad de destino ";
                cin>>destino;
            }
            if(origen!=destino){
                    destino--;
                    origen--;
                break;
            }
            else{
                cout<<endl<<"Jugador 1: El origen y el destino son iguales!!"<<endl;
            }
        }
        catch(int tamano){
            cout<<"Jugador 1: Debe insertar numeros"<<endl;
        }
    }
    if(jugadores){
        while(true){
            try{
                cout<<endl<<"Jugador 2: Ingresa la ciudad de partida ";
                cin>>origen2;
                while(origen2>tamano||origen2<=0){
                    cout<<endl<<"El indice del origen se encuentra fuera del dominio del grafo ";
                    cout<<endl<<"\nJugador 2: Vuelva a ingresa la ciudad de origen ";
                    cin>>origen2;
                    }
                    cout<<endl<<"Jugador 2: Ingresa la ciudad de destino";
                    cin>>destino2;
                    while(destino2>tamano||destino2<=0){
                        cout<<endl<<"El indice del destino se encuentra fuera del dominio del grafo ";
                        cout<<endl<<"\nJugador 2: Vuelva a ingresa la ciudad de destino ";
                        cin>>destino2;
                    }
                    if(origen2!=destino2){
                            destino2--;
                            origen2--;
                        break;
                    }
                    else{
                        cout<<endl<<"Jugador 2: La ciudad de partida y la ciudad de destino son iguales!!"<<endl;
                    }
                }
            catch(int tamano){
                cout<<"Jugador 2: Debe insertar numeros"<<endl;
            }
        }
    }
    // Start the game loop
    while (window.isOpen())
    {
        contador++;
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
        dibujarNombres();
        window.draw(titulo);

        pila=Dijkstra(origen,destino,baneado);
        dibujarPesos();
        dibujarVertices();
        dibujarArcos();
        dibujarRuta(pila,sf::Color::Red,0);
        if (jugadores){
            pila2=Dijkstra(origen2,destino2,baneado2);
            dibujarRuta(pila2,sf::Color::Green,4);
        }
        window.display();
        if(pila.size()==0){
            cout<<"Jugador 1: Se eliminara el ultimo nodo baneado"<<endl;
            baneado.pop();
        }
        else{
            contador = tamano-1;
            if (origen!=destino){
                int x=pila.top();
                pila.pop();
                cout<<"\nJugador 1: La siguiente ciudad es la #"<<pila.top()+1<<", desea continuar por esta ruta? s/n"<<endl;
                pila.push(x);
                string opcion;
                while(true){
                    cin>>opcion;
                    if (opcion=="s"){
                        pila.pop();
                        origen=pila.top();
                        break;
                    }
                    else if (opcion=="n"){
                        pila.pop();
                        baneado.push(pila.top());
                        pila.push(origen);
                        break;
                    }
                    else{
                        cout<<"Debe de ingresar la opcion 1 o 2"<<endl;
                    }
                }
            }
            else{
                cout<<"Jugador 1 ha llegado a su destino"<<endl;
                string ok;
                cin>>ok;
            }
        }
        if(jugadores){
            if(pila2.size()==0){
                cout<<"Jugador 2: Se eliminará el ultimo nodo baneado"<<endl;
                baneado2.pop();
            }
            else{
                if(origen2!=destino2){
                    int x=pila2.top();
                    pila2.pop();
                    cout<<"\nJugador 2: La siguiente ciudad es la #"<<pila2.top()+1<<" desea continuar por esta ruta? s/n"<<endl;
                    pila2.push(x);
                    string opcion;
                    while(true){
                        cin>>opcion;
                        if (opcion=="s"){
                            pila2.pop();
                            origen2=pila2.top();
                            break;
                        }
                        else if(opcion=="n"){
                            pila2.pop();
                            baneado2.push(pila2.top());
                            pila2.push(origen2);
                            break;
                        }
                        else{
                            cout<<"Debe de ingresar la opcion 1 o 2"<<endl;
                        }
                    }
                }
                else{
                    cout<<"Jugador 2 ha llegado a su destino"<<endl;
                    string ok;
                    cin>>ok;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

