#include "logger.h"

logger::logger(){

    time_t seconds = time(nullptr);
    tm* timeinfo = localtime(&seconds);
    char s[30];
    strftime(s, 30, "playerLog_%F_%T.txt",timeinfo);
    fileName = s;
    logFile.open(fileName, std::ios_base::app);
}

logger::~logger (){
    logFile.close();
}

void logger::update(player* p){
    time_t seconds = time(nullptr);
    tm* timeinfo = localtime(&seconds);
    char s[30];
    strftime(s, 30, "playerLog_%F_%T.txt",timeinfo);
    logFile << s << *p;
}
