#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::getline;
using std::string;
using std::to_string;
using std::vector;
using std::getline;
using std::fstream;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    std::string key, value;
  	float total = 0;
    std::string line;                               
    std::fstream file;
    file.open(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename, std::ios::in);
    if(file.is_open()){
    	while(getline(file, line)){
          	std::istringstream stream(line);
        	stream >> key >> value;
          	
        }
      file.close();
    }   
    total = stoi(value);                         
  return total;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
	long uptime;
  	long unneeded =0;
    string line;
  	std::fstream file;
  	file.open(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename, std::ios::in);
  	if(file.is_open()){
      	while(std::getline(file, line)){
        std::istringstream stream(line);
    	stream >> uptime >> unneeded; 
        }
      file.close();
    }  
    return uptime;
}

// TODO: Read and return the number of jiffies for the system
//sys is system frequency which is the number of ticks per second
long LinuxParser::Jiffies() {

	long total;
  	long time = LinuxParser::UpTime();//removed linux designation as compiler was saying Uptime() is not a member of LinuxParser
  	long sys = sysconf(_SC_CLK_TCK);
  	total = time * sys;
  	return total;
}

// TODO: Read and return the number of active jiffies for a PID
//are elements 13-16 the correct ones from /proc/pid/stat for active jiffies
long LinuxParser::ActiveJiffies(int pid) {

	string line;
  	int zero, three, four, five, six, seven, eight, ten;
  	int eleven, twelve, target1, target2, target3, target4;
  	long nine;
  	std::string one;
  	char two;
  	fstream file;
  	file.open(kProcDirectory + to_string(pid) + kStatFilename, std::ios::in);
	if(file.is_open()){
    	while(getline(file, line)){
    	std::istringstream stream(line);
        stream >> zero >> one >> two >> three >> four >> five >> 
          six >> seven >> eight >> nine >> ten >> eleven >> twelve >>
          target1 >> target2 >> target3 >> target4;
        }
      file.close();
    }
	return target1 + target2 + target3 + target4;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {

	string line;
  	string cpu;
  	long a, b, c, d, e, f;
    int g, h, i ,j;
  	fstream file;
  	file.open(kProcDirectory + kStatFilename, std::ios::in);
  	if(file.is_open()){
      	while(getline(file, line)){
    	std::istringstream stream(line);
        stream >> cpu >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
        }
      file.close();
    }
  
  	return a+b+c+d+e+f+g+h+i+j;

}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {

	string line;
  	string cpu;
  	int a, b, c, idle, iowait;
  	fstream file;
  	file.open(kProcDirectory + kStatFilename, std::ios::in);
  	if(file.is_open()){
      	while(getline(file, line)){
    	std::istringstream stream(line);
        stream >> cpu >> a >> b >> c >> idle >>iowait;
        }
      file.close();
    }
  
  	return idle + iowait;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
	
  	vector<string> total;  
    std::string line;                               
    std::fstream file;
  	string item;
    file.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename, std::ios::in);
    if(file.is_open()){
    	getline(file, line);//remove while loop so that it only reads one line
          	std::istringstream stream(line);
        	while(stream >> item) {
            	total.push_back(item);
            }
      file.close();
        }
    return total;
}                            


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  	int total_processes;
	string line;
  	string key, value;
	std::fstream file;
  	file.open(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename, std::ios::in);
  	if(file.is_open()){
    	while(std::getline(file, line)){
        std::istringstream stream(line);
    	stream >> key >> value; 
          if(key == "processes"){
            total_processes = stoi(value);
        }  
      file.close();
    }
  	return total_processes;
  }
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {

  	int running_processes;
	string line;
  	string key, value;
	std::fstream file;
  	file.open(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename, std::ios::in);
  	if(file.is_open()){
    	while(std::getline(file, line)){
        std::istringstream stream(line);
    	stream >> key >> value; 
          if(key == "procs_running"){
            running_processes = stoi(value);
        }  
      file.close();
    }
  	return running_processes;

}
}

// TODO: Read and return the command associated with a process

std::string LinuxParser::Command(int pid) {
  string line;
	string cmd;
	fstream file;
  	file.open(kProcDirectory + to_string(pid) + kCmdlineFilename, std::ios::in);
    if(file.is_open()){
  		getline(file, line);
          	std::istringstream stream(line);
    		stream >> cmd; 
    	
      file.close();
    }
  	return cmd;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {

	string ram, Vm;
  	string line;
	fstream file;
  	file.open(kProcDirectory + to_string(pid) + kStatusFilename, std::ios::in);
  if (file.is_open()) {
  	while(getline(file, line)){
    	std::istringstream stream(line);
      	std::replace(line.begin(), line.end(), ':', ' ');
     	while(stream >> Vm >> ram) {
      	if(Vm == "Vmsize"){
           return ram;//should I return this here or save seperately and close the file after
           }
        }
    }
    file.close();
    }
  
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  
  string line;
  string key;
  string value;
  fstream file;
  file.open(kProcDirectory + to_string(pid) + kStatusFilename, std::ios::in);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream stream(line);
      std::replace(line.begin(), line.end(), ':', ' ');
      while (stream >> key >> value) {
        if (key == "Uid") {//or should it be Uid or Uid:
          return value;
        }
      }
    }
    file.close();
  }
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {

  
  string line;
  string user, uid2;
  string uid = LinuxParser::Uid(pid);
  fstream file;
  file.open(kPasswordPath, std::ios::in);
  if (file.is_open()) {
    while (getline(file, line)) {
	  std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stream(line);
      while(stream >> uid2 >> user) {
        if (uid2 == uid) {
          return user;
        }
      }
    
    }
    file.close();
  }
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {

  string line;
  long value;
  fstream file;
  file.open(kProcDirectory + to_string(pid) + kStatFilename, std::ios::in);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream stream(line);
      //loop through the stream to find value 22
 		for(int i=0; i<22; i++){
          stream >> value;
        }
         file.close();
      }
   return (value / sysconf(_SC_CLK_TCK));
  }

}
