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
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return *new Processor(); }

// TODO: Return a container composed of the system's processes
//the vector is holding Process class objects
vector<Process>& System::Processes() { 
    //make a vector of all of the pids in the system
   vector<int> pids = LinuxParser::Pids(); 
   //loop through all of them
   for(int pid: pids){
       Process process(pid);
       //for every pid in pids make a Process class object
       process.CpuUtilization();
       //get the cpu utilization
       processes_.push_back(process);
       //add every process to the processes_ vector
   }
    
    
   return processes_;  
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
    // long time = LinuxParser::UpTime(); 
    // string military_time = Format::ElapsedTime(time);
    // return military_time; 
}
