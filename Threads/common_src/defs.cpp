#include "defs.h"

std::string get_event_message(const int& alive_enemies, const int& dead_enemies,
                              const uint8_t& event_type) {
    std::ostringstream response;

    if (event_type == DEAD_ENEMY) {
        response << "Un enemigo ha muerto. ";
    } else if (event_type == REVIVED_ENEMY) {
        response << "Un enemigo ha revivido. ";
    }

    response << alive_enemies << " vivo(s) y " << dead_enemies << " muerto(s).";

    return response.str();
}
