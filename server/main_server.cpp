#include <iostream>
#include "config_loader.h"
int main(int argc, char const *argv[]){
    try{
       /*
        if (argc != 3) {
            std::cerr<< "Error: argumentos invalidos.";
            return 1;
        }
        */
        std::string char_read;
        bool server_enabled = true;
        const std::string file = argv[2];
//        AcceptorTh acceptor(repository, file, argv[1]);
 //       acceptor.start();




        std::cout << ConfigLoader::get_init_configs().sv_port;

        while (server_enabled){
            std::cin >> char_read;
            if (char_read == "q"){
                server_enabled = false;
//             acceptor.stopAccepting();
            }
        }
//        acceptor.join();
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }catch (...) {
        std::cerr << "Error inesperado en el hilo main" << std::endl;
        return 1;
    }
    return 0;
}
