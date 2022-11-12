#include "DefaultLogger.h"

DefaultLogger::DefaultLogger(std::string file_path):file_path_(file_path)
{
  file_handler_ = std::make_shared<std::ofstream>(file_path_.c_str(), std::ios::out | std::ios::app | std::ios::binary);
  if(file_handler_->is_open())
  {
  }
}

bool DefaultLogger::log(std::string log)
{
  std::string newlog = log +"\r\n";
  if(!file_handler_->is_open())
  {
    return false;
  }
  file_handler_->write(newlog.c_str(), newlog.size());
  file_handler_->flush();

  printf("%s", newlog.c_str());
  return true;
}

bool DefaultLogger::log(std::string file_path, std::string log)
{
  std::shared_ptr<std::ofstream> f_h_ = std::make_shared<std::ofstream>(file_path.c_str(), std::ios::out | std::ios::app | std::ios::binary);
  if(f_h_->is_open())
  {
    f_h_->write(log.c_str(), log.size());
    f_h_->close();
    return  true;
  }
  else
  {
    return false;
  }
}
