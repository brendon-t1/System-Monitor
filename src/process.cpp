#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process()

// TODO: Return this process's ID
int Process::Pid() {return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { LinuxParser::Ram(pid);  }

// TODO: Return the user (name) that generated this process
string Process::User() { LinuxParser::User(pid);}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {LinuxParser::UpTime(pid);}//need to convert to seconds?

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
	return a.cpu < cpu;	
}