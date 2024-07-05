#ifndef BACKGROUNDS_LOADER_H
#define BACKGROUNDS_LOADER_H

#include <iostream>
#include <vector>
#include "../common/enums.h"

// Cargar manualmente frames porque estos no son de width constante.
#include <map>
#include <string>

const std::map<enum Background, std::string> backgrounds{
    {INIT_SCREEN, "/Pantalla_inicial.png"},
    {MAIN_SCREEN, "/Fondo_seleccionar_caracter.png"},
    {BLACK_SCREEN, "/black_image.jpg"},
    {GENERAL_SCREEN, "/fondo_general.png"},
};
#endif
