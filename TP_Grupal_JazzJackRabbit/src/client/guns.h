#ifndef GUNS_LOADER_H
#define GUNS_LOADER_H

#include "../common/enums.h"

#include <map>
#include <string>

const std::map<enum Background, std::string> backgrounds{
    {INIT_SCREEN, "/Pantalla_inicial.png"},
    {MAIN_SCREEN, "/Fondo_seleccionar_caracter.png"},
    {BLACK_SCREEN, "/black_image.jpg"},
    {GENERAL_SCREEN, "/fondo_general.png"},
};
#endif
