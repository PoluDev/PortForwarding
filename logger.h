#ifndef LOGGER_H
#define LOGGER_H
#include <QCoreApplication>
#include <string>
#include <iostream>
int count = 0;

class Logger
{
public:
    Logger();
    void Output();
    template<typename First, typename ... othersType>
    void Output(First arg, othersType... rest);
};

#endif // LOGGER_H
