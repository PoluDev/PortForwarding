#ifndef APPDEF_H
#define APPDEF_H

#include <string>

struct ApplicationParameter
{
    std::string application_path_;
    std::string dest_;
    unsigned short bind_port_;
    unsigned short dest_port_;
};


#endif // APPDEF_H
