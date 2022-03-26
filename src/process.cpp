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

// TODO: Return this process's ID
int Process::Pid() {return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization(int pid) {
    string line, one;
    int zero, three, four, five, six, seven, nine, eleven, twelve;
    int thirteen, utime, stime, cutime, cstime;
    int eighteen, nineteen, twenty, twenty_one;
    long eight, ten, starttime;
    char two;
    fstream file;
    file.open(kProcDirectory + to_string(pid) + kStatFilename, std::ios::in);
        if(file.is_open()){
            getline(file, line);
            istringstream stream(line);
            stream >> zero >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >>
            ten >> eleven >> twelve >> thirteen >> utime >> stime >> cutime >> cstime >>
            eighteen >> nineteen >> twenty >> twenty_one >> starttime;
            file.close();
        }
    long total_time = utime + stime ;//#14 utime + #15 stime also add #16 cutime and #17 cstime if we want to include the time from the childrens processes
    long seconds = LinuxParser::UpTime(pid) - ( starttime / sysconf(_SC_CLK_TCK));//uptime - (#22 starttime / Hertz)
    //Hertz is sysconf(_SC_CLK_TCK)
    float cpu_usage = 100 * ((total_time / Hertz) / seconds);
    return cpu_usage;
    
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::Pid());  }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid());}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()); }//need to convert to seconds?

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
	return a.cpu < cpu;	
}