#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANIO 15
#define CANT 10
#define ALIAS 5
#define LARGOC 8

typedef struct{//fecha
    int dia;
    int mes;
    int anio;
}fecha;

typedef struct{//alias
    char largoAlias[ALIAS];
    int tamanioAlias;
}cadenaAlias;

typedef struct{//datos partida
    cadenaAlias player1;//cambiar a ALIAS
    cadenaAlias player2;//cambiar
    fecha fechaPartidas;
    int resultadoP1;
    int resultadoP2;
}partida;

typedef struct{//partidas
    partida partidas[10];//cambiar
    int pos;
}listaPartidas;

typedef struct{//nombre
    char largoNombre[TAMANIO];
    int tamanioNombre;
}cadenaNombre;

typedef struct{//apellido
    char largoApellido[TAMANIO];
    int tamanioApellido;
}cadenaApellido;

typedef struct{//ci
    int numero[LARGOC]; //contiene la cantidad de dígitos de la ci.
    int largodigito; //cantidad de dígitos de la ci.
}digito; // defino estructura digito para ser utilizada en la cedula del paciente

typedef struct{//datos
    digito cedula;
    fecha fechaNacimiento;
    cadenaNombre nombre;
    cadenaApellido apellido;
    cadenaAlias alias;
}datos;

typedef struct{//jugador
    datos data;
    int activo;
}jugador;

typedef struct{//datos jugador
    jugador players[CANT];
}listaDeJugador;

void saludo();//saludo de bienvenida
void menu();//menú principal
int opcionMenu();//selección de opción de menú
listaDeJugador gestionUsuario(listaDeJugador jugadores,int *pos);//menú gestión usuario
listaDeJugador altaJugador(listaDeJugador jugadores,int *pos);//alta de jugador
digito ci_ingreso();//ingreso ci
fecha fechaNacimiento();//ingreso fecha de nacimiento
cadenaAlias ingresoAlias();//ingreso fecha alias
cadenaNombre ingresoNombre();//ingreso nombre
cadenaApellido ingresoApellido();//ingreso apellido
listaDeJugador bajaJugador(listaDeJugador jugadores,int *pos);//baja de jugador
int buscoJugador(listaDeJugador jugadores,int pos,cadenaAlias apodo);//función para buscar un jugador
int comparoAlias(cadenaAlias a1,cadenaAlias a2);//función que compra alias
void muestroAlias(listaDeJugador jugadores,int pos);//muestro alias
void muestroNombre(listaDeJugador jugadores,int pos);//muestro nombre
void muestroApellido(listaDeJugador jugadores,int pos);//muestro apellido
void muestroCedula(listaDeJugador jugadores,int pos);//muestro ci
void muestroFechanacimiento(listaDeJugador jugadores,int pos);//muestro fecha de nacimiento
char confirmaSN();//función para confirmar
listaDeJugador modificarJugador(listaDeJugador jugadores,int *pos);//modificación de jugador
void consultas(listaDeJugador jugadores,int *pos,listaPartidas partidas);//menú consultas
void listadoJugadores(listaDeJugador jugadores,int pos);//listado de jugadores
void listadoPartidas(listaDeJugador jugadores,listaPartidas partidas);//listado de todas las partidas
void partidasJugador(listaDeJugador jugadores,listaPartidas partidas,int *pos);//listado de partidas por jugador
void partidasFecha(listaDeJugador jugadores,listaPartidas partidas);//listado de partidas por fecha
void jugar(listaDeJugador jugador,int *pos,listaPartidas *partidas);//menú principal del juego
void reglas();//Función de reglas y formas de jugar (Texto)
void menuJogo(listaPartidas *listadoPartidas,char *jugadordeturno,listaDeJugador jugadores,int *pos,int *salir);//menú opciones del juego
void seleccionPartida(int *tamanio,int *salir);//Función para seleccionar el tablero
void crearTablero(int tamanio,int *jugador1,int *jugador2,char *tablero[]);//función para crear el tablero
void movimiento(char jugadordeturno,int tamanio,char jugadorActual,int jugador1,int jugador2,char *tablero[],int puntos[],int *salir);//Función para los movimientos / disparos de los jugadores
void ganador(char jugadordeturno,int puntos[],listaPartidas *listadoPartidas);//Función que indica el ganador
void despedida();//Función de despedida al usuario (Texto)
void salirTodo();//función salir

int main(){
    int op;
    int pos=0;
    digito cedula;
    listaDeJugador jugadores;
    listaPartidas partidas;
    saludo();
    while(op!=4){
        menu();
        op=opcionMenu();
        switch (op){
            case 1:
                jugadores=gestionUsuario(jugadores,&pos);
                break;
            case 2:
                system("clear");
                consultas(jugadores,&pos,partidas);
                break;
            case 3:
                jugar(jugadores,&pos,&partidas);
                system("clear");
                break;
            case 4:
                salirTodo();
                break;
        }
    }
    return 0;
}

void saludo(){ // Función de bienvenida al usuario (Texto)
    printf("\n\t\t   > > > Bienvenido a nuestro juego < < <\n");
    printf("\n\t\t Creadores: Juan Martín Pilón && Melanie Frade\n\n\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * *   \tA R Q U E R O S\t   * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * *     E N \t E L     * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * *    \t B O S Q U E \t   * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\n\n");
}

void menu(){//menú principal
    printf("# # # # # # # # M E N U # # # # # # # #\n");
    printf("\t1- Gestionar usuario.\n");
    printf("\t2- Consultas.\n");
    printf("\t3- Jugar.\n");
    printf("\t4- Salir.\n");
}

int opcionMenu(){//selección de opción de menú
    int op;
    printf("Ingrese opción [1-4]: ");
    scanf("%d",&op);
    getchar();
    return op;
}

listaDeJugador gestionUsuario(listaDeJugador jugadores,int *pos){//menú gestión usuario
    int sel;
    system ("clear");
    printf("1- Gestionar usuario.\n");
    printf("\t1- Alta de Jugador:\n");
    printf("\t2- Baja de Jugador:\n");
    printf("\t3- Modificación de Jugador:\n");
    printf("\t4- Volver al menú principal:\n");
    printf("Ingrese opción [1-4]: ");
    scanf("%d", &sel);
    system ("clear");

    switch (sel){
        case 1:
            jugadores=altaJugador(jugadores,&*pos);
            getchar();
            system ("clear");
            break;
        case 2:
            jugadores=bajaJugador(jugadores,&*pos);
            getchar();
            system ("clear");
            break;
        case 3:
            jugadores=modificarJugador(jugadores,&*pos);
            getchar();
            system ("clear");
            break;
        case 4:
            break;
    }
    return jugadores;
}

listaDeJugador altaJugador(listaDeJugador jugadores, int *pos){//alta jugador
    system ("clear");
    printf("\t1- Alta de Jugador.\n");
    datos data;
    cadenaAlias auxAlias;//variable auxiliar que guarda el alias
    cadenaNombre auxNombre;
    cadenaApellido auxApellido;
    data.cedula=ci_ingreso();
    printf("Fecha de nacimiento:\n");
    data.fechaNacimiento=fechaNacimiento();
    getchar();
    printf("El alias a ingresar admite como máximo 5 caracteres.\n");
    auxAlias=ingresoAlias();
    auxNombre=ingresoNombre();
    auxApellido=ingresoApellido();
    jugadores.players[*pos].activo=1;
    if(buscoJugador(jugadores,*pos,auxAlias)==-1){//devuelve -1 no encontrado
        jugadores.players[*pos].data.alias=auxAlias;
        jugadores.players[*pos].data.nombre=auxNombre;
        jugadores.players[*pos].data.apellido=auxApellido;
        jugadores.players[*pos].data.cedula=data.cedula;
        jugadores.players[*pos].data.fechaNacimiento=data.fechaNacimiento;
        *pos=*pos+1;
        printf("Presione 'ENTER' para continuar.\n");
    }
    else{
        printf("Jugador ya existe.\n");
        jugadores.players[*pos].activo=0;
    }
    return jugadores;
}

digito ci_ingreso(){//ingreso ci
    digito res;
    int i=0,suma,modulo,valor,valido;
    printf("Ingrese Cédula: ");
    do{//validar ci
        i=0;
        while((res.numero[i]=getchar())!='\n' && i<LARGOC){
            res.numero[i]=res.numero[i]-48;
            i++;
        }
        res.largodigito=i;
        suma=(2*res.numero[0])+(9*res.numero[1])+(8*res.numero[2])+(7*res.numero[3])+(6*res.numero[4])+(3*res.numero[5])+(4*res.numero[6]);//validar
        modulo=suma%10;
        valor=(10-modulo);
        valido=valor;

        if(valido==res.numero[7]){
            printf("Correcto!\n");
        }
    }
    while(valido!=res.numero[7]);
    return res;
}

fecha fechaNacimiento(){//ingreso fecha nacimiento
    fecha res;//respuesta
    printf("\tDía: ");
    scanf("%d",&res.dia);
    printf("\tMes: ");
    scanf("%d",&res.mes);
    printf("\tAño: ");
    scanf("%d",&res.anio);
//validar fecha
    while(((res.anio<1900)||(res.anio>2020))||(res.mes>12)){
        printf("Fecha no válida, repita su ingreso.\n");
        printf("Fecha:\n");
        printf("\tDía: ");
        scanf("%d",&res.dia);
        printf("\tMes: ");
        scanf("%d",&res.mes);
        printf("\tAño: ");
        scanf("%d",&res.anio);
    }
    switch(res.mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            while(res.dia>32 || res.dia<=0){
                printf("Fecha no válida\n");
                printf("Ingrese día correcto: ");
                scanf("%d", &res.dia);
            }
            break;
        case 2:
            while(res.dia>28 || res.dia<=0){
                printf("Fecha no válida\n");
                printf("Ingrese día correcto: ");
                scanf("%d", &res.dia);
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            while(res.dia>31 || res.dia<=0){
                printf("Fecha no válida\n");
                printf("Ingrese día correcto: ");
                scanf("%d", &res.dia);
            }
            break;
    }
    return res;
}

cadenaAlias ingresoAlias(){//ingreso alias
    cadenaAlias alia;
    int x=0;
    printf("Alias: ");
    while(((alia.largoAlias[x]=getchar())!='\n') && x<ALIAS){
        x++;
    }
    alia.tamanioAlias=x;
    return alia;
}

cadenaNombre ingresoNombre(){//ingreso nombre
    cadenaNombre name;
    int x=0;
    printf("Nombre: ");   //ingresar
    while(((name.largoNombre[x]=getchar())!='\n')&&x<TAMANIO){
        x++;
    }
    name.tamanioNombre=x;
    return name;
}

cadenaApellido ingresoApellido(){//ingreso apellido
    cadenaApellido surname;
    int x=0;
    printf("Apellido: ");   //ingresar
    while(((surname.largoApellido[x]=getchar())!='\n')&&x<TAMANIO){
        x++;
    }
    surname.tamanioApellido=x;
    return surname;
}

listaDeJugador bajaJugador(listaDeJugador jugadores,int *pos){//baja jugador
    int i;
    char confirma;
    cadenaAlias auxAlias;
    printf("\t2- Baja de Jugador:\n");
    getchar();
    auxAlias=ingresoAlias();
    i=buscoJugador(jugadores,*pos,auxAlias);
    if(i!=-1){//!=-1 si existe el paciente
        if(jugadores.players[i].activo==1){
            printf("\tAlias: ");
            muestroAlias(jugadores,i);
            printf("\n\tNombre: ");
            muestroNombre(jugadores,i);
            printf("\n\tApellido: ");
            muestroApellido(jugadores,i);
            printf("\n\tCI: ");
            muestroCedula(jugadores,i);
            printf("\n\tFecha Nacimiento: ");
            muestroFechanacimiento(jugadores,i);
            printf("\nDesea eliminar el Jugador? [S/N]\n");
            printf("\n");
            confirma=confirmaSN();
            if(confirma=='S'||confirma=='s'){
                jugadores.players[i].activo=0;
            }
        }
        else{
            printf("Jugador Inactivo.\n");
        }
    }
    else{
        printf("Jugador NO existe.\n");
        getchar();
    }
    printf("Presione 'ENTER' para continuar.\n");
    getchar();
    return jugadores;
}

int buscoJugador(listaDeJugador jugadores,int pos,cadenaAlias apodo){//función para buscar un jugador
    //devuelve la posición dentro del array jugadores donde se encuentra el alias
    //caso contrario, si NO encuentra el alias, devuelve -1
    int i;
    int j=comparoAlias(jugadores.players[0].data.alias,apodo);
    for(i=0;i<pos;i++){//pos indica cuantos jugadores hay en ese momento
        if(comparoAlias(jugadores.players[i].data.alias,apodo)==0){
            return i;//posición donde se encontró el alias
        }
    }
    return -1;//no se encontró
}

int comparoAlias(cadenaAlias a1,cadenaAlias a2){//función que compra alias
    int iguales,i,contador;
    contador=0;

    if(a1.tamanioAlias!=a2.tamanioAlias){
        iguales=1;
    }//distintos por tener distinto largo
    else{//los largos son iguales
        for(i=0;i<a1.tamanioAlias;i++){
            if(a1.largoAlias[i]==a2.largoAlias[i]){//comparo posición por posición
                contador++;
            }
        }
        if(contador==a1.tamanioAlias){
            iguales=0;//los alias son iguales
        }
        else{
            iguales=1;
        }
    }
    return iguales;
}

void muestroAlias(listaDeJugador jugadores,int pos){//mostrar alias
    int x;
    for(x=0;x<jugadores.players[pos].data.alias.tamanioAlias;x++){
        printf("%c",jugadores.players[pos].data.alias.largoAlias[x]);
    }
}

void muestroNombre(listaDeJugador jugadores,int pos){//mostrar nombre
    int x;
    for(x=0;x<jugadores.players[pos].data.nombre.tamanioNombre;x++){
        printf("%c",jugadores.players[pos].data.nombre.largoNombre[x]);
    }
}

void muestroApellido(listaDeJugador jugadores,int pos){//mostrar apellido
    int x;
    for(x=0;x<jugadores.players[pos].data.apellido.tamanioApellido;x++){
        printf("%c",jugadores.players[pos].data.apellido.largoApellido[x]);
    }
}

void muestroCedula(listaDeJugador jugadores,int pos){//mostrar ci
    int x;
    for(x=0;x<jugadores.players[pos].data.cedula.largodigito;x++){
        printf("%d",jugadores.players[pos].data.cedula.numero[x]);
    }
}

void muestroFechanacimiento(listaDeJugador jugadores,int pos){//mostrar fecha nacimiento
    printf("%d/%d/%d",jugadores.players[pos].data.fechaNacimiento.dia,jugadores.players[pos].data.fechaNacimiento.mes,jugadores.players[pos].data.fechaNacimiento.anio);
}

char confirmaSN(){//función para confirmar
    char confirma =' ';
    do{
        scanf(" %c",&confirma);
    }
    while(confirma!='S' && confirma!='N' && confirma!='s' && confirma!='n');
    return confirma;
}

listaDeJugador modificarJugador(listaDeJugador jugadores, int *pos){//modificación de jugador
    int i;
    char confirma;
    cadenaAlias auxAlias;
    cadenaNombre auxNombre;
    cadenaApellido auxApellido;
    fecha auxFecha;
    digito auxCi;
    system("clear");
    printf("\t3- Modificación de Jugador:\n");
    getchar();
    auxAlias=ingresoAlias();
    i=buscoJugador(jugadores,*pos,auxAlias);
    if(i!=-1){
        if(jugadores.players[i].activo==1){
            printf("\tAlias: ");
            muestroAlias(jugadores,i);
            printf("\n\tNombre: ");
            muestroNombre(jugadores,i);
            printf("\n\tApellido: ");
            muestroApellido(jugadores,i);
            printf("\n\tCI: ");
            muestroCedula(jugadores,i);
            printf("\n\tFecha Nacimiento: ");
            muestroFechanacimiento(jugadores,i);
            printf("\nDesea Modificar el Jugador? [S/N]\n");
            confirma=confirmaSN();
            if(confirma=='S'||confirma=='s'){//sobre-escribe los datos del jugador
                getchar();
                auxNombre=ingresoNombre();
                auxApellido=ingresoApellido();
                auxCi=ci_ingreso();
                printf("Fecha de nacimiento:\n");
                auxFecha=fechaNacimiento();
                printf("Desea confirmar [S / N]: ");
                confirma=confirmaSN();
                if(confirma=='S'||confirma=='s'){
                    jugadores.players[i].data.alias=auxAlias;
                    jugadores.players[i].data.nombre=auxNombre;
                    jugadores.players[i].data.apellido=auxApellido;
                    jugadores.players[i].data.cedula=auxCi;
                    jugadores.players[i].data.fechaNacimiento=auxFecha;
                }//si no se confirma, no hago nada
            }//si no se confirma, no hago nada, no modifico nada
        }
        else{
            printf("Jugador Inactivo.\n");
            getchar();
        }
        printf("Presione 'ENTER' para continuar.\n");
        getchar();
    }
    else{
        printf("Jugador NO existe.\n");
        getchar();
    }
    return jugadores;
}

void consultas(listaDeJugador jugadores,int *pos,listaPartidas partidas){//menú consultas
    int sel;
    system ("clear");
    printf("2- CONSULTAS:\n");
    printf("\t1- Listado de Jugadores.\n");
    printf("\t2- Listado  de todas las Partidas.\n");
    printf("\t3- Listado de partidas por Jugador.\n");
    printf("\t4- Listado de partidas por fecha.\n");
    printf("\t5- Volver al menú principal:\n");
    printf("Ingrese opción [1-5]: ");
    scanf("%d", &sel);
    system ("clear");

    switch (sel){
        case 1:
            listadoJugadores(jugadores,*pos);
            getchar();
            getchar();
            system ("clear");
            break;
        case 2:
            listadoPartidas(jugadores,partidas);
            getchar();
            getchar();
            break;
        case 3:
            partidasJugador(jugadores,partidas,&*pos);
            getchar();
            getchar();
            break;
        case 4:
            partidasFecha(jugadores,partidas);
            getchar();
            getchar();
            break;
        case 5:
            break;
    }
}

void listadoJugadores(listaDeJugador jugadores,int pos){//listado de jugadores
    int i;
    printf("1- Listado de Jugadores.\n");
    getchar();
    for(i=0;i<pos;i++){
        if(jugadores.players[i].activo==1){
            printf("\tAlias: ");
            muestroAlias(jugadores,i);
            printf("\n\tNombre: ");
            muestroNombre(jugadores,i);
            printf("\n\tApellido: ");
            muestroApellido(jugadores,i);
            printf("\n\tCI: ");
            muestroCedula(jugadores,i);
            printf("\n\tFecha de Nacimiento: ");
            muestroFechanacimiento(jugadores,i);
            printf("\n\n");
        }
    }
    printf("Presione 'ENTER' para continuar.\n");
}

void listadoPartidas(listaDeJugador jugadores,listaPartidas partidas){//listado de todas las partidas
    int x,i;
    getchar();
    printf("\t2- Listado  de todas las Partidas.\n");
    for(x=0;x<partidas.pos;x++){
        printf("Partida %d: ",x+1);
        printf("\n\tFecha: %d/%d/%d",partidas.partidas[x].fechaPartidas.dia,partidas.partidas[x].fechaPartidas.mes,partidas.partidas[x].fechaPartidas.anio);
        printf("\n\tAlias Jugador 1: ");
        for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
            printf("%c",partidas.partidas[x].player1.largoAlias[i]);
        }
        //muestro alias
        printf("\n\tAlias Jugador 2: ");
        for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
            printf("%c",partidas.partidas[x].player2.largoAlias[i]);
        }
        if(partidas.partidas[x].resultadoP1>partidas.partidas[x].resultadoP2){
            printf("\n\tGanador: ");
            for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
                printf("%c",partidas.partidas[x].player1.largoAlias[i]);
            }
            printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP1,partidas.partidas[x].resultadoP2);
        }
        else{
            printf("\n\tGanador: ");
            for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
                printf("%c",partidas.partidas[x].player2.largoAlias[i]);
            }
            printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP2,partidas.partidas[x].resultadoP1);
        }
        printf("\n");
    }
    printf("Presione 'ENTER' para continuar.\n");
}

void partidasJugador(listaDeJugador jugadores,listaPartidas partidas,int *pos){//listado partidas por jugador
    printf("\t3- Listado de partidas por Jugador.\n");
    int x,i;
    getchar();
    cadenaAlias auxAlias;
    auxAlias=ingresoAlias();
    getchar();
    i=buscoJugador(jugadores,*pos,auxAlias);
    if(i!=-1){
        if(jugadores.players[i].activo==1){
            for(x=0;x<partidas.pos;x++){
                if((comparoAlias(auxAlias,partidas.partidas[x].player1)==1)||(comparoAlias(auxAlias,partidas.partidas[x].player2)==1)){
                    printf("Partida %d: ",x+1);
                    printf("\n\tFecha: %d/%d/%d",partidas.partidas[x].fechaPartidas.dia,partidas.partidas[x].fechaPartidas.mes,partidas.partidas[x].fechaPartidas.anio);
                    printf("\n\tAlias Jugador 1: ");
                    for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
                        printf("%c",partidas.partidas[x].player1.largoAlias[i]);
                    }
                    //muestro alias
                    printf("\n\tAlias Jugador 2: ");
                    for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
                        printf("%c",partidas.partidas[x].player2.largoAlias[i]);
                    }
                    if(partidas.partidas[x].resultadoP1>partidas.partidas[x].resultadoP2){
                        printf("\n\tGanador: ");
                        for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
                            printf("%c",partidas.partidas[x].player1.largoAlias[i]);
                        }
                        printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP1,partidas.partidas[x].resultadoP2);
                    }
                    else{
                        printf("\n\tGanador: ");
                        for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
                            printf("%c",partidas.partidas[x].player2.largoAlias[i]);
                        }
                        printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP2,partidas.partidas[x].resultadoP1);
                    }
                }
                printf("\n");
            }
        }
        else{
            printf("Jugador Inactivo.\n");
        }
    }
    else{
        printf("Jugador no Existe.\n");
    }
    printf("\nPresione 'ENTER' para continuar.\n");
}

void partidasFecha(listaDeJugador jugadores,listaPartidas partidas){//listado de partidas por fecha
    printf("\t4- Listado de partidas por fecha.\n");
    int x,i;
    getchar();
    fecha auxFecha;
    printf("Ingrese Fecha a Consultar:\n");
    auxFecha=fechaNacimiento();

    for(x=0;x<partidas.pos;x++){
        if(partidas.partidas[x].fechaPartidas.dia==auxFecha.dia && partidas.partidas[x].fechaPartidas.mes==auxFecha.mes && partidas.partidas[x].fechaPartidas.anio==auxFecha.anio){
            printf("Partida %d: ",x+1);
            printf("\n\tFecha: %d/%d/%d",partidas.partidas[x].fechaPartidas.dia,partidas.partidas[x].fechaPartidas.mes,partidas.partidas[x].fechaPartidas.anio);
            printf("\n\tAlias Jugador 1: ");
            for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
                printf("%c",partidas.partidas[x].player1.largoAlias[i]);
            }
            //muestro alias
            printf("\n\tAlias Jugador 2: ");
            for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
                printf("%c",partidas.partidas[x].player2.largoAlias[i]);
            }
            if(partidas.partidas[x].resultadoP1>partidas.partidas[x].resultadoP2){
                printf("\n\tGanador: ");
                for(i=0;i<partidas.partidas[x].player1.tamanioAlias;i++){
                    printf("%c",partidas.partidas[x].player1.largoAlias[i]);
                }
                printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP1,partidas.partidas[x].resultadoP2);
            }
            else{
                printf("\n\tGanador: ");
                for(i=0;i<partidas.partidas[x].player2.tamanioAlias;i++){
                    printf("%c",partidas.partidas[x].player2.largoAlias[i]);
                }
                printf("\n\tResultado de la Partida: %d - %d ",partidas.partidas[x].resultadoP2,partidas.partidas[x].resultadoP1);
            }
        }
        else{
            printf("La fecha ingresada no corresponde.\n");
        }
        printf("\n");
    }
    printf("\nPresione 'ENTER' para continuar.\n");
}

void jugar(listaDeJugador jugadores,int *pos,listaPartidas *listadoPartidas){//menú principal del juego
    system("clear");
    int *tamanio;
    char jugadordeturno;
    char jugadorActual;
    int jugador1,jugador2;
    int salir=0;
    char *tablero[81];
    int puntos[2]={0,0};
    listadoPartidas->pos=0;
    char letra;
    do{
        srand(time(NULL));
        reglas();
        menuJogo(listadoPartidas,&jugadordeturno,jugadores,&*pos,&salir);
        if(salir==0){
            getchar();
            seleccionPartida(&tamanio,&salir);
            while(puntos[0]<2 && puntos[1]<2 && salir==0){//p0 = J1 p1= J2
                crearTablero(tamanio,&jugador1,&jugador2,&tablero);
                movimiento(jugadordeturno,tamanio,jugadorActual,jugador1,jugador2,&tablero,puntos,&salir);
            }
            if(salir==0) {
                ganador(jugadordeturno,puntos,listadoPartidas);
                printf("Para volver a jugar presione: V \n");
                printf("Para volver a Menú presione X \n");
                scanf(" %c", &letra);
                puntos[0]=0;//reinicia los contadores
                puntos[1]=0;
            }
        }
    }
    while(letra=='V' && salir==0);
}

void reglas(){//Función de reglas y formas de jugar (Texto)
    printf("\n\nOBJETIVO DEL JUEGO:\n");
    printf("\n   - El objetivo del juego es eliminar a tu oponente.\n");
    printf("\n\nREGLAS DEL JUEGO:\n");
    printf("  1- Cada partida se compone de 3 rounds, el jugador que gane 2 de ellas, gana  la partida.\n");
    printf("  2- El jugador que reciba un flechazo, pierde el round.\n");
    printf("  3- Cada arquero puede moverse solo UN lugar a la vez, tanto en sentido \nVERTICAL como HORIOZNTAL.\n");
    printf("  4- Moverse en DIAGONAL no está permitido.\n");
    printf("  5- Los flechazos solo se pueden realizar en línea recta [Vertical/Horizontal],con una distancia máxima de 5 metros [1 cuadrado = 1 metro]\n");
    printf("  6- Las X representan los árboles que conforman el bosque.\n");
    printf("  7- Un arquero no puede moverse fuera del tablero, ni a una celda donde haya unárbol.\n");
    printf("  8- Las flechas no pueden traspasar los árboles.\n");
    printf("\n\t* * * I M P O R T A N T E ! ! ! * * *\n\n");
    printf("  - BOLQ MAYUS debe permanecer ACTIVADO en todo momento, de lo contrario, el \njuego no funcionará.\n");
    printf("  - Los Movimientos se realizan con las teclas:\n\tA: Derecha\n\tD: Izquierda\n\tW: Arriba\n\tS: Abajo\n");
    printf("  - Los Disparos se realizan con las teclas:\n\tL: Derecha\n\tJ: Izquierda\n\tI: Arriba\n\tK: Abajo\n");
    printf("  - Presione X para SALIR.\n");
    printf("  - Presione F para RENDIRSE.");
}

void menuJogo(listaPartidas *listadoPartidas,char *jugadordeturno,listaDeJugador jugadores,int *pos,int *salir){//menú opciones del juego
    char menu;
    int x=0;
    char j1[ALIAS];
    char j2[ALIAS];
    int a1=-1,a2=-1;
    printf("\n\n\n\tPresione 'P' para JUGAR, presione cualquier otra tecla para SALIR:\n\n\t");
    scanf(" %c", &menu);
    if(menu=='P'){
       while(a1==-1 || a2==-1){
            if(a1==-1){//para que no pida dos veces
                getchar();
                printf("\nIngrese 1er ");
                listadoPartidas->partidas[listadoPartidas->pos].player1=ingresoAlias();
                a1=buscoJugador(jugadores,*pos,listadoPartidas->partidas[listadoPartidas->pos].player1);
            }
            if(a2==-1){
                printf("\nIngrese 2do ");
                listadoPartidas->partidas[listadoPartidas->pos].player2=ingresoAlias();
                a2=buscoJugador(jugadores,*pos,listadoPartidas->partidas[listadoPartidas->pos].player2);
            }
            if(comparoAlias(listadoPartidas->partidas[listadoPartidas->pos].player1,listadoPartidas->partidas[listadoPartidas->pos].player2)==0){
                printf("Alias 2 debe ser diferente de Alias 1.\n");
                a2=-1;
            }
        }
        printf("Ingrese fecha:\n");
        listadoPartidas->partidas[listadoPartidas->pos].fechaPartidas=fechaNacimiento();

        printf("\n\tSeleccione que jugador va a comenzar [Alias 1 = 1 / Alias 2 = 2]:\n\n\t");
        scanf("%c", jugadordeturno);
        while(*jugadordeturno!='1' && *jugadordeturno!='2'){//selección de jugador
            printf("Indique su elección [1 o 2]:\n\n\t");
            scanf("%c", jugadordeturno);
        }
        printf("\nSeleccionó ALIAS %c\n", *jugadordeturno);
    }
    else{
        if(menu=='X'){
            *salir=1;
//            despedida();
            salirTodo();
        }
    }
}

void seleccionPartida(int *tamanio,int *salir){//Función para seleccionar el tablero
    char opcionTablero;
    printf("\n\tElige el tipo de partida que quieres jugar:\n\n\t\tA - Partida Rápida\n\t\tB - Partida Normal\n\t\tC - Partida Larga\n\t\tPresione cualquier otra tecla para salir del juego\n\n\t");
    scanf(" %c", &opcionTablero);
    switch(opcionTablero){//Selección de tablero/partida
        case 'A':
            system("clear");
            printf("\nSeleccionó partida Rápida.\n");
            *tamanio=5;
            break;
        case 'B':
            system("clear");
            printf ("\nSeleccionó partida Normal.\n");
            *tamanio=7;
            break;
        case 'C':
            system("clear");
            printf("\nSeleccionó partida Larga.\n");
            *tamanio=9;
            break;
        default:
            *salir=1;
        }
}

void crearTablero(int tamanio,int *jugador1,int *jugador2,char *tablero[]){//función para crear el tablero
    int x=0,y=0,forest=0;
    for(x=0;x<tamanio;x++){//inicializar tablero
        for(y=0;y<tamanio;y++){
            tablero[tamanio*x+y]=' ';
        }
    }
    tablero[tamanio-1]='2'; //poner jugador 1
    *jugador2=tamanio-1;
    tablero[tamanio*(tamanio-1)]='1'; //poner jugador 2
    *jugador1=tamanio*(tamanio-1);
    while(forest<tamanio){
        srand(time(NULL));
        x=rand()%(tamanio*tamanio);
        if(tablero[x]==' '){
            tablero[x]='X'; //poner arboles
            forest++;
        }
    }
}

void movimiento(char jugadordeturno,int tamanio,char jugadorActual,int jugador1,int jugador2,char *tablero[],int puntos[],int *salir){//Función para los movimientos / disparos de los jugadores
    char mover;
    int x=0;//movimientos
    int y=0;
    int i;
    int fallo;
    int invalido=0;
    jugadorActual=jugadordeturno;
    int hit=0;
    while(hit==0 && *salir==0){
        i=1;
        fallo=0;
        printf("\n\tTurno de Alias %c\n\n", jugadordeturno);
        printf("Puntos Alias 1: %d\n", puntos[0]);
        printf("Puntos Alias 2: %d\n\n", puntos[1]);

        printf("  "); //imprimir tablero
        for(x=0;x<tamanio;x++){
            printf("| %c ", 65+x);//convertir a letra
        }
        printf("|\n");
        for(x=0;x<tamanio;x++){
            printf("%d ", x+1);
            for(y=0;y<tamanio;y++){
                printf("| %c ",tablero[x*tamanio+y]);
            }
            printf("|\n");
        }
        scanf(" %c",&mover);
//Movimientos y Disparos
        while((mover!='W')&&(mover!='S')&&(mover!='A')&&(mover!='D')&&(mover!='J')&&(mover!='K')&&(mover!='L')&&(mover!='I')&&(mover!='X')&&(invalido==1)&&(mover!='F')){
            printf("Ingrese otra letra.\n");
            scanf(" %c", &mover);
            invalido=0;
        }

        int posicion;
        if(jugadordeturno=='1'){
            posicion=jugador1;
            jugadorActual='1';
        }
        else{
            if(jugadordeturno=='2'){
                posicion=jugador2;
                jugadorActual='2';
            }
        }

        switch(mover){
            case 'W':
                if((posicion-tamanio>=0)&&(tablero[posicion-tamanio]==' ')){//que esté dentro del tablero && que sea un lugar vacío
                    tablero[posicion]=' ';
                    tablero[posicion-tamanio]=jugadorActual;
                    if(jugadorActual=='1'){
                        jugador1-=tamanio;
                    }
                    else{
                        if(jugadorActual=='2'){
                            jugador2-=tamanio;
                        }
                    }
                    system("clear");
                    invalido=0;
                    printf("Se movió para arriba\n");
                }
                else{
                    printf("Movimiento inválido, intente nuevamente\n");
                    getchar();
                    invalido=1;
                }
                break;
            case 'S':
                if((posicion+tamanio<tamanio*tamanio)&&(tablero[posicion+tamanio]==' ')){
                    tablero[posicion]=' ';
                    tablero[posicion+tamanio]=jugadorActual;
                    if(jugadorActual=='1'){
                        jugador1+=tamanio;
                    }
                    else{
                        if(jugadorActual=='2'){
                            jugador2+=tamanio;
                        }
                    }
                    system("clear");
                    invalido=0;
                    printf("Se movió para abajo\n");
                }
                else{
                    printf("Movimiento inválido, intente nuevamente\n");
                    invalido=1;
                }
                break;
            case 'A':
                if((posicion%tamanio!=0)&&(tablero[posicion-1]==' ')){
                    tablero[posicion]=' ';
                    tablero[posicion-1]=jugadorActual;
                    if(jugadorActual=='1'){
                        jugador1--;
                    }
                    else{
                        if(jugadorActual=='2'){
                            jugador2--;
                        }
                    }
                    system("clear");
                    invalido=0;
                    printf("Se movió para la izquierda\n");
                }
                else{
                    printf("Movimiento inválido, intente nuevamente\n");
                    invalido=1;
                }
                break;
            case 'D':
                if(((posicion+1)%tamanio!=0)&&(tablero[posicion+1]==' ')){
                    tablero[posicion]=' ';
                    tablero[posicion+1]=jugadorActual;
                    if(jugadorActual=='1'){
                        jugador1++;
                    }
                    else{
                        if(jugadorActual=='2'){
                            jugador2++;
                        }
                    }
                    system("clear");
                    invalido=0;
                    printf("Se movió hacia la derecha\n");
                }
                else{
                    printf("Movimiento inválido, intente nuevamente\n");
                    invalido=1;
                }
                break;
            case 'X'://salir
                *salir=1;
                despedida();
                salirTodo();
                break;
            case 'F'://rendirse
                if(jugadordeturno=='1'){
                    puntos[1]++;
                    printf("\n\tFELICIDADES Alias 2 ganaste el ROUND!!\n");
                    hit=1;
                }
                else{
                    puntos[0]++;
                    printf("\n\tFELICIDADES Alias 1 ganaste el ROUND!!\n");
                    hit=1;
                }
                break;
            case 'I':
                printf("Disparó hacia arriba\n");
                while (i<6 && fallo==0){
                    if(posicion-((i+1)*tamanio)>=0&&tablero[posicion-((i+1)*tamanio)]==' '){
                        i++;
                    }
                    else{
                        if(posicion-((i+1)*tamanio)>=0&&(tablero[posicion-((i+1)*tamanio)]=='X')){
                            fallo=1;
                            printf ("Le disparaste a un árbol\n");
                        }
                        else{
                            if(posicion-((i+1)*tamanio)>=0&&(tablero[posicion-((i+1)*tamanio)]=='1'||tablero[posicion-((i+1)*tamanio)]=='2')){
                                fallo=3;
                                hit=1;
                                if(jugadordeturno=='1'){
                                    puntos[0]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                                else{
                                    puntos[1]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                            }
                            else{
                                fallo=1;
                            }
                        }
                    }
                }
                break;
            case 'K':
                printf("Disparó hacia abajo\n");
                while(i<6 && fallo==0){
                    if(posicion+((i+1)*tamanio)<tamanio*tamanio && tablero[posicion+((i+1)*tamanio)]==' '){
                        i++;
                    }
                    else{
                        if(posicion+((i+1)*tamanio)<tamanio*tamanio&&(tablero[posicion+((i+1)*tamanio)]=='X')){
                            fallo=1;
                            printf ("Le disparaste a un árbol\n");
                        }
                        else{
                            if(posicion+((i+1)*tamanio)<tamanio*tamanio&&(tablero[posicion+((i+1)*tamanio)]=='1'||tablero[posicion+((i+1)*tamanio)]=='2')){
                                fallo=3;
                                hit=1;
                                if(jugadordeturno=='1') {
                                    puntos[0]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                                else{
                                    puntos[1]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                            }
                            else{
                                fallo=1;
                            }
                        }
                    }
                }
                break;
            case 'J':
                printf("Disparó hacia la izquierda\n");
                while (i<6 && fallo==0){
                    if(((posicion-i)%tamanio!=0)&&(tablero[posicion-i]==' ')){
                        i++;
                    }
                    else{
                        if(((posicion-i)%tamanio!=0)&&(tablero[posicion-i]=='X')){
                            fallo=1;
                            printf ("Le disparaste a un árbol\n");
                        }
                        else{
                            if(((posicion-i)%tamanio!=0)&&(tablero[posicion-i]=='1'||tablero[posicion-i]=='2')){
                                fallo=3;
                                hit=1;
                                if(jugadordeturno=='1'){
                                    puntos[0]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                                else{
                                    puntos[1]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                            }
                            else{
                                fallo=1;
                            }
                        }
                    }
                }
                break;
            case 'L':
                printf("Disparó hacia la derecha\n");
                while (i<6 && fallo==0){
                    if(((posicion+i)%tamanio!=0)&&(tablero[posicion+i]==' ')){
                        i++;
                    }
                    else{
                        if(((posicion+i)%tamanio!=0)&&(tablero[posicion+i]=='X')){
                            fallo=1;
                            printf ("Le disparaste a un árbol\n");
                        }
                        else{
                            if(((posicion+i)%tamanio!=0)&&(tablero[posicion+i]=='1'||tablero[posicion+i]=='2')){
                                fallo=3;
                                hit=1;
                                if(jugadordeturno=='1'){
                                    puntos[0]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);
                                }
                                else{
                                    puntos[1]++;
                                    printf("\n\tFELICIDADES Alias %c ganaste el ROUND!!\n",jugadordeturno);

                                }
                            }
                            else{
                                fallo=1;
                            }
                        }
                    }
                }
                break;
        }
        if(invalido==0){
            if(jugadordeturno=='1'){
                jugadordeturno='2';
            }
            else{
                if(jugadordeturno=='2'){
                    jugadordeturno='1';
                }
            }
        }
    }
}

void ganador(char jugadordeturno,int puntos[],listaPartidas *listadoPartidas){//Función que indica el ganador
    if((puntos[0]<2)){//jugador 1, gana jugador 2
        printf("\nGANASTE la partida ALIAS %c !!\n\n",jugadordeturno+1);
    }
    else{
        if(puntos[1]<2){//jugador 2, gana jugador 1
            printf("\nGANASTE la partida ALIAS %c !!\n\n", jugadordeturno);
        }
    }
    listadoPartidas->partidas[listadoPartidas->pos].resultadoP1=puntos[0];
    listadoPartidas->partidas[listadoPartidas->pos].resultadoP2=puntos[1];
    listadoPartidas->pos=listadoPartidas->pos+1;
    despedida();
}

void despedida(){//Función de despedida al usuario (Texto)
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * \t  J U E G O \t  * * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * *    F I N A L I Z A D O    * * * * * * * * * * * * * *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
}

void salirTodo(){//función salir
    system("clear");
    printf("\n\n\t\tGracias por utilizar nuestro Programa!!\n");
    printf("Ante cualquier problema o sugerencia, no dude en contactar con sus creadores.\n\n");
}
