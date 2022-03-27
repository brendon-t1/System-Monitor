#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"
#include "linux_parser.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;
using std::fstream;
using std::istringstream;

// TODO: Return this process's ID
int Process::Pid() {return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    string line, one;
    int zero, three, four, five, six, seven, nine, eleven, twelve;
    int thirteen, utime, stime, cutime, cstime;
    int eighteen, nineteen, twenty, twenty_one;
    long eight, ten, starttime;
    char two;
    fstream file;
    file.open(LinuxParser::kProcDirectory + to_string(Process::Pid()) + LinuxParser::kStatFilename, std::ios::in);
        if(file.is_open()){
            getline(file, line);
            istringstream stream(line);
            stream >> zero >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >>
            ten >> eleven >> twelve >> thirteen >> utime >> stime >> cutime >> cstime >>
            eighteen >> nineteen >> twenty >> twenty_one >> starttime;
            file.close();
        }
  	float ticks = sysconf(_SC_CLK_TCK);
  	float uptime = LinuxParser::UpTime();
  	float start_time = LinuxParser::UpTime(pid);
    float total_time = utime + stime;
    float seconds = uptime - ( start_time / ticks);
    float cpu_usage = 100 * ((total_time / ticks) / seconds);
    return cpu_usage;
    
}

// TODO: Return the command that generated this process
string Process::Command() { return  LinuxParser::Command(Process::Pid()); }

//  DO: Return this process's memory utilization
string Process::Ram() {
	string ram =LinuxParser::Ram(Process::Pid());
	int mb = stoi(ram);
  	mb /= 1024;
  	string ram_mb = to_string(mb);
  	return ram_mb;
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid());}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()); }//need to convert to seconds?

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
	return a.cpu < cpu;	
}