#include "config_loader.h"

ConfigLoader::ConfigLoader() {
    std::ifstream config_file("../config.json");
    if (!config_file.is_open()){
        std::cerr << "Config JSON File could not be loaded" << std::endl;
    }


    config_file >> this->json_file; //Asocio el archivo con la librería

    sv_port = std::getenv("PORT")?
            std::getenv("PORT"): this->json_file["sv_port"];

}

ConfigLoader &ConfigLoader::get_init_configs() {
    static ConfigLoader instance;
    return instance;
}
