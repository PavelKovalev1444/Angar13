#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include "player.h"

class logger{
    std::ofstream logFile;
    std::string fileName;
public:
    logger();
    ~logger ();
    void update(player* p);
};

#endif // LOGGER_H
