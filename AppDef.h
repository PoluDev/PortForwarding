#ifndef __APP_DEF_H__
#define __APP_DEF_H__

#include <string>

struct ApplicationParameter
{
    std::string application_path_;
    std::string dest_;
    unsigned short bind_port_;
    unsigned short dest_port_;
};


#endif // __APP_DEF_H__
