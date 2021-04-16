# Wolfenstein-Taller1

<img src="readme/Banner.png" alt="drawing" width="800" height="350"/>

## Integrantes

| Nombre                                                        | Padrón |
| ------------------------------------------------------------- | ------ |
| [BIANCARDI, Julian](https://github.com/JulianBiancardi)       | 103945 |
| [CZOP, Santiago](https://github.com/Santiago-Czop)            | 104057 |
| [GIARDINA, Fernando](https://github.com/FerGiardina)          | 103732 |
| [STENGHELE, Juan Francisco](https://github.com/JuanStenghele) | 104000 |
     
Corrector: **[DI PAOLA, Martin](https://github.com/eldipa)**

# Indice   
1. [Introducción](#id1)
2. [Requisitos](#id2)
3. [Instalación](#id3)
4. [Ejecución](#id4)
5. [Juego](#id5)
6. [Imagenes](#id7)

## 1. Introducción<a name="id1"></a>

Este juego, inspirado en el original Wolfenstein3d, es parte del trabajo final y grupal realizado para la materia de Taller de Programación I dictada en la Facultad de Ingeniería de la Universidad de Buenos Aires (FIUBA) durante el segundo cuatrimestre del 2020.


## 2. Requisitos<a name="id2"></a>

* SDL, SDL_image, SDL_ttf, SDL_mixer
* QT5
* Lua
* Sistema operativo: Linux

## 3. Instalación<a name="id3"></a>

Abrir una consola en la raiz del proyecto (Ctrl + Alt + T) y ejecutar el siguiente comando:

        $ bash installer.sh
        
El instalador contiene los siguientes comandos que usted puede utilizar:

 - a: instala todo el juego más las dependencias necesarias
 - i: instala solo las dependencias necesarias
 - u: desistala el juego
 - h: muestra los comandos disponibles
 - q: salir del instalador

(Se aconseja utilizar el comando **a** para garantizar el correcto funcionamiento de los aplicativos.)

## 4. Ejecución<a name="id4"></a>

Una vez instalado el juego completo más las dependecias necesarias, se generarán tres archivos ejecutables:

 * server
 * wolfenstein3D
 * editor

Estos archivos se encuentran dentro de la carpeta build generada por el instalador. 

El archivo **server** representa el servidor del juego. El mismo se corre con el siguiente comando:

        $ ./server

El archivo **wolfenstein3D** representa a un cliente. El mismo se corre con el siguiente comando:

        $ ./wolfenstein3D

El archivo **editor** representa el editor de mapas. El mismo se corre con el siguiente comando:

        $ ./editor

(Ver la guía de usuario [EditorManual.pdf](https://github.com/JulianBiancardi/Wolfenstein-Taller1/blob/main/EditorManual.pdf).)


## 5. Juego<a name="id5"></a>

Para poder empezar a jugar primero debemos correr el servidor que se encargara del manejo y correcto funcionamiento de las partidas creadas por los distintos clientes.

La siguiente salida por consola indica que el servidor se a abierto correctamente:

        foo@pc:~/Wolfenstein-Taller1/build$ ./server
        Running server on 8080 ...
        Successful opening the server on the port 8080

Con el comando **q** cerraremos el servidor. Una vez que tengamos abierto nuestro servidor ya podremos inciar los clientes.

Al iniciar un nuevo cliente veremos la siguiente interfaz grafica que representa las partidas creadas por otros usuarios, donde *status* nos indica si la partida ha comenzado o no.

<img src="readme/Launcher.png" alt="drawing"/>

Para unirse simplemente seleccione la partida a la que quiera jugar y presionado al boton *JOIN* se unira a la misma (si la partida ya ha comenzado o el limite de jugadores es exedido no se podrá unir).

Para comnezar la partida, el creador de la misma es decir el host debera presionar la tecla **Enter** de su teclado.

Para crear una nueva partida presione el boton *NEW* y podrá elegir el mapa. Los mapas son creados por el editor de niveles que tambien se le provee en este proyecto.

## 6. Imagenes<a name="id7"></a>

 - Imagenes del juego
  
<img src="readme/game1.png" alt="drawing" />
<img src="readme/game2.png" alt="drawing" />
<img src="readme/multiple_screen_sizes.png" alt="drawing"/>

 - Imagenes del editor

<img src="readme/editor1.png" alt="drawing"/>
<img src="readme/editor2.png" alt="drawing" />
<img src="readme/editor3.png" alt="drawing" />
<img src="readme/editor4.png" alt="drawing" />
<img src="readme/editor5.png" alt="drawing" />
