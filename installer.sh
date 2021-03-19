function initialMessage () {
    clear
    echo "==================================================================="
    echo "                  WOLFENSTEIN  3D  ONLINE              "
    echo "                    +------------------+               "                                
    echo "                    |       ___        |               "                                
    echo "                    |   _  (,~ |   _   |               "
    echo "                    |  (____/  |____)  |               "                                
    echo "                    |  |||||    |||||  |               "
    echo "                    |  |||||    |||||  |               "
    echo "                    |  |||||\  /|||||  |               "            
    echo "                    |  |||  /\/\  |||  |               "                                
    echo "                    |  |' m' /\ 'm '|  |               "                                
    echo "                    |       /||\       |               "                                
    echo "                     \________________/                "                              
    echo ""
    echo "Welcome to the Wolfenstein 3D oline installer. 

The following work is a final project for the subject Taller de Programación I (FUIBA). For more information visit https://github.com/JulianBiancardi/Wolfenstein-Taller1.
"
}

function helpMessage() {
    echo "The available commands are as follows"
    echo "  d: install only dependencies"
    echo "  i: install only the game"
    echo "  a: install all"
    echo "  u: unistall the game"
    echo "  h: show helps"
    echo "  q: close"
    echo ""
}

function unknownInput() {
    echo -e "\x1b[1m\x1b[31mOrder not found. Please enter 'h' for help. \x1b[0m\n"
}


function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function installDependencies() {
    echo -e "\x1b[1m\x1b[36mInstalling 'cmake'...\x1b[0m\n"
    sudo apt-get install cmake
    echo -e "\x1b[1m\x1b[36mInstalling 'libsdl2-dev'...\x1b[0m\n"
    sudo apt-get install libsdl2-dev
    echo -e "\x1b[1m\x1b[36mInstalling 'libsdl2-image-dev'...\x1b[0m\n"
    sudo apt-get install libsdl2-image-dev
    echo -e "\x1b[1m\x1b[36mInstalling 'libsdl2-ttf-dev'...\x1b[0m\n"
    sudo apt-get install libsdl2-ttf-dev
    echo -e "\x1b[1m\x1b[36mInstalling 'libsdl2-mixer-dev'...\x1b[0m\n"
    sudo apt-get install libsdl2-mixer-dev
    echo -e "\x1b[1m\x1b[36mInstalling 'libyaml-cpp-dev'...\x1b[0m\n"
    sudo apt install libyaml-cpp-dev
    echo -e "\x1b[1m\x1b[36mInstalling 'qt5'...\x1b[0m\n"
    sudo apt-get install qtcreator
    sudo apt-get install qt5-default
    echo -e "\x1b[1m\x1b[36mInstalling 'lua5.3'...\x1b[0m\n"
    sudo apt-get install lua5.3 liblua5.3-dev
    echo -e "\x1b[1m\x1b[32mInstall dependencies complete\x1b[0m\n"
}

function installGame() {
    build
    sudo make install -j4
    echo -e "\x1b[1m\x1b[32mInstall game complete\x1b[0m\n"
}

function uninstall() {
    sudo rm -rf build
    sudo rm -rf /usr/lib/libcommon.so
    sudo rm -rf /usr/bin/wolfenstein3D
    sudo rm -rf /usr/bin/server
    sudo rm -rf /var/wolfenstein3D
    sudo rm -rf /etc/wolfenstein3D
    echo -e "\x1b[1m\x1b[32mUninstall the game complete\x1b[0m\n"
}


# exit when any command fails
set -e

initialMessage
helpMessage

while :
do
    read OPTION
    case $OPTION in
        d)  
            echo ""
            installDependencies
        ;;
        i)
            echo ""
            installGame
        ;;
        a)
            echo ""
            installDependencies
            installGame
        ;;
        u)
            echo ""
            uninstall
        ;;
        h)  
            echo ""
            clear
            helpMessage
        ;;
        q)  
            echo ""
            exit 0
        ;;
        *)  
            echo ""
            unknownInput
        ;;
    esac
done