#include "processor.h"
#include <fstream>

#include "linux_parser.h"

float Processor::Utilization() {
 
  float active = LinuxParser::ActiveJiffies();
  float total = LinuxParser::Jiffies();
  float util = active / total;
  return util; 
}