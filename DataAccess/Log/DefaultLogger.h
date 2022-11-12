#ifndef DEFAULTLOGGER_H
#define DEFAULTLOGGER_H

#include <fstream>
#include <memory>
#include <string>

class DefaultLogger
{
public:
  DefaultLogger(std::string file_path);

  bool log(std::string log);
  bool log(std::string file_path, std::string log);

private:
  std::string file_path_;
  std::shared_ptr<std::ofstream> file_handler_;
};

#endif // DEFAULTLOGGER_H
