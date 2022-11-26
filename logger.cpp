#include "logger.h"

//#define LOG Output(...) ;
#define LOG {Output(X, ...)};

Logger::Logger()
{

}

void Output() {
    std::cout<<std::endl;
}

template<typename First, typename ... othersType>
void Output(First arg, othersType... rest) {
    count ++;
    std::cout<<"\nLine Number : "<<__LINE__;
    std::cout<<"\nFunction Name : "<<__func__;
    std::cout<<"\nFile Name : "<<__FILE__;

    Output(rest...);
}


