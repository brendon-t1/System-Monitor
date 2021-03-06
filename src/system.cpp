#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return *new Processor(); }

vector<Process>& System::Processes() { 
   vector<int> pids = LinuxParser::Pids(); 
   for(int pid: pids){
       Process process(pid);
       process.CpuUtilization();
       processes_.emplace_back(process);//changed to emplace back from push back
   }
   return processes_;  
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { 
    return LinuxParser::UpTime();
}
