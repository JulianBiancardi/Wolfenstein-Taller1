#!/bin/bash

#----------------------------------MESSAGES------------------------------------------

function waitingInputMessage() {
    printf "> Ingrese una opción: "
}

function initialMessage () {
    clear
    echo "======================================================"
    echo "=               WOLFENSTEIN 3D ONLINE                ="
    echo "======================================================"
    echo ""
}

function helpMessage() {
    echo "Opciones de instalación:"
    echo "  d: instala dependencias necesarias."
    echo "  i: instala el juego (no se instalan dependencias)."
    echo "  a: instala todo (dependencias y juego)."
    echo ""
    echo "Opciones de desinstalación:"
    echo "  u: desinstala el juego."
    echo ""
    echo "Otras opciones:"
    echo "  h: muestra este mensaje."
    echo "  q: cerrar."
    echo ""
}

function unknownInput() {
    echo "Opción desconocida (ingrese 'h' para ayuda, 'q' para salir)." 
    echo ""
}


#-------------------------------------BUILD AND EXECUTION------------------------------------
function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function installDependencies() {
    echo "=== INSTALACIÓN DE DEPENDENCIAS ==="
    echo ""
    echo ">> Instalando 'cmake'..."
    sudo apt-get install cmake
    echo ""
    echo ">> Instalando 'libsdl2-dev'..."
    sudo apt-get install libsdl2-dev
    echo ""
    echo ">> Instalando 'libsdl2-image-dev'..."
    sudo apt-get install libsdl2-image-dev
    echo ""
    echo ">> Instalando 'libsdl2-ttf-dev'..."
    sudo apt-get install libsdl2-ttf-dev
    echo ""
    echo ">> Instalando 'libsdl2-mixer-dev'..."
    sudo apt-get install libsdl2-mixer-dev
    echo ""
    echo ">> Instalando 'libyaml-cpp-dev'..."
    sudo apt install libyaml-cpp-dev
    echo ""
    echo ">> Instalando 'qt5'..."
    sudo apt-get install qtcreator
    sudo apt-get install qt5-default
    echo ""
    echo "Instalación de dependencias finalizada."
    echo ""
}

function installGame() {
    echo "=== INSTALACIÓN DEL JUEGO ==="
    build
    sudo make install -j4
    echo ""
    echo "Instalación del juego finalizada."
    echo ""
}

function all() {
    installDependencies
    installGame
}

function uninstall() {
    echo "=== DESINSTALADOR ==="
    sudo rm -rf build
    sudo rm -rf /usr/lib/libcommon.so
    sudo rm -rf /usr/bin/wolfenstein3D
    sudo rm -rf /usr/bin/server
    sudo rm -rf /var/wolfenstein
    echo ""
    echo "Se ha desinstalado el juego con éxito."
    echo ""
}

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Loop ppal

# exit when any command fails
set -e

initialMessage
helpMessage
waitingInputMessage

while :
do
    read OPTION
    case $OPTION in
        d)  
            echo ""
            installDependencies
            waitingInputMessage
        ;;
        i)
            echo ""
            installGame
            waitingInputMessage
        ;;
        a)
            echo ""
            installDependencies
            installGame
            waitingInputMessage
        ;;
        u)
            echo ""
            uninstall
            waitingInputMessage
        ;;
        h)  
            echo ""
            clear
            helpMessage
            waitingInputMessage
        ;;
        q)  
            echo ""
            exit 0
        ;;
        *)  
            echo ""
            unknownInput
            waitingInputMessage
        ;;
    esac
done

#------------------------------------------------------------------------------