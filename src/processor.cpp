#include "processor.h"
#include <fstream>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
 
  float active = LinuxParser::ActiveJiffies();
  float total = LinuxParser::Jiffies();
  float util = active / total;
  return util; 
}