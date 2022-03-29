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
using std::stoi;
using std::vector;
using std::fstream;
using std::istringstream;

int Process::Pid() {return pid;}

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
    float cpu_usage = ((total_time / ticks) / seconds);//removed the 100 here
    return cpu_usage;
    
}

string Process::Command() { return  LinuxParser::Command(Process::Pid()); }

string Process::Ram() {
	string ram =LinuxParser::Ram(Process::Pid());
	int mb;
    if(ram == ""){mb = 0;}
    else{mb = stoi(ram);}
  	mb /= 1024;
  	string ram_mb = to_string(mb);
  	return ram_mb;
}

string Process::User() { return LinuxParser::User(Process::Pid());}

long int Process::UpTime() {
    long total = 0;
    long process_uptime = LinuxParser::UpTime(Process::Pid()); 
    process_uptime /= sysconf(_SC_CLK_TCK);
    long total_uptime = LinuxParser::UpTime();
    total = total_uptime - process_uptime;
    return total;
}

bool Process::operator<(Process const& a) const {
	return a.cpu < cpu;	
}