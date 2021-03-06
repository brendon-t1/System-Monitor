#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::getline;
using std::string;
using std::to_string;
using std::vector;
using std::getline;
using std::fstream;
using std::istringstream;
using std::replace;

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

float LinuxParser::MemoryUtilization() {
    string line, key, value, size;
  	float total, free, used;                           
    fstream file;
    file.open(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename, std::ios::in);
    if(file.is_open()){
    	while(getline(file, line)){
          replace(line.begin(), line.end(), ':', ' ');
          istringstream stream(line);
        	stream >> key >> value >> size;
          if(key == "MemTotal") {
            if(value == "") {total = 0;}
            else {total = stof(value);}
          }
          if(key == "MemAvailable") {
            if(value == "") {free = 0;}
            else {free = stof(value);}
          }
        }
      file.close();
    }   
    used = (total - free) / total;     
  return used;
}

long LinuxParser::UpTime() {
	  float uptime, idle;
    string line;
  	fstream file;
  	file.open(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename, std::ios::in);
  	if(file.is_open()){
      	getline(file, line);
        istringstream stream(line);
    	  stream >> uptime >> idle; 
        
        file.close();
    }  
    return uptime;
}

long LinuxParser::Jiffies() {
    long active = LinuxParser::ActiveJiffies();
    long idle = LinuxParser::IdleJiffies();
    long jiffies = active + idle;
    return jiffies;
}

long LinuxParser::ActiveJiffies(int pid) {

	string line;
  	int zero, three, four, five, six, seven, eight, ten;
  	int eleven, twelve, target1, target2, target3, target4;
  	long nine;
  	string one;
  	char two;
  	fstream file;
  	file.open(kProcDirectory + to_string(pid) + kStatFilename, std::ios::in);
	    if(file.is_open()){
    	  while(getline(file, line)){
    	    istringstream stream(line);
          stream >> zero >> one >> two >> three >> four >> five >> 
          six >> seven >> eight >> nine >> ten >> eleven >> twelve >>
          target1 >> target2 >> target3 >> target4;
        }
      file.close();
    }
    long active = target1 + target2 + target3 + target4;
	return active;
}


long LinuxParser::ActiveJiffies() {

	string line, cpu;
  	long user, nice, system, idle, iowait, irq;
    int softirq, steal, guest, guest_nice;
  	fstream file;
  	file.open(kProcDirectory + kStatFilename, std::ios::in);
  	if(file.is_open()){
      	getline(file, line);
    	istringstream stream(line);
      	stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
      	file.close();
    }
    long total = user + nice + system + irq + softirq + steal;
  	return total;

}

long LinuxParser::IdleJiffies() {
  
    string line, cpu;
  	long a, b, c, idle, iowait;
  	fstream file;
  	file.open(kProcDirectory + kStatFilename, std::ios::in);
  	  if(file.is_open()){
        getline(file, line);
    	istringstream stream(line);
        stream >> cpu >> a >> b >> c >> idle >> iowait;
      file.close();
      }
  	return idle + iowait;
}

vector<string> LinuxParser::CpuUtilization() {
  	vector<string> total;  
    string line, item;                               
    fstream file;
    file.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename, std::ios::in);
      if(file.is_open()){
    	  getline(file, line);
        istringstream stream(line);
        	while(stream >> item) {
            total.push_back(item);
          }
        file.close();
      }
    return total;
}                            

int LinuxParser::TotalProcesses() {
  int total_processes;
	string line, key, value;
	fstream file;
  file.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename, std::ios::in);
    if(file.is_open()){
      while(getline(file, line)){
        istringstream stream(line);
    	  stream >> key >> value; 
          if(key == "processes"){
            if(value == "") {total_processes = 0;}
            else {total_processes = stoi(value);}
          }  
      }
      file.close();
    }
  return total_processes;
}

int LinuxParser::RunningProcesses() {
  int running_processes;
	string line, key, value;
	fstream file;
  file.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename, std::ios::in);
  if(file.is_open()){
    while(getline(file, line)){
      istringstream stream(line);
    	stream >> key >> value; 
        if(key == "procs_running"){
          if(value == "") {running_processes = 0;}
          else {running_processes = stoi(value);}
        }    
    }
    file.close();
  } 
  return running_processes;
}

std::string LinuxParser::Command(int pid) {
  string cmd;
	fstream file;
  file.open(kProcDirectory + to_string(pid) + kCmdlineFilename, std::ios::in);
  if(file.is_open()){
  		getline(file, cmd);
      file.close();
  }
  return cmd;
}

string LinuxParser::Ram(int pid) {
	string line, key, value, ram;
	fstream file;
  file.open(kProcDirectory + to_string(pid) + kStatusFilename, std::ios::in);
  if (file.is_open()) {
  	while(getline(file, line)){
    	replace(line.begin(), line.end(), ':', ' ');
      istringstream stream(line);
     	stream >> key >> value;
      if(key == "VmSize"){
        ram = value;     
      }
    }
    file.close();
  }
  return ram;
}

string LinuxParser::Uid(int pid) {
  string line, key, value, uid;
  fstream file;
  file.open(kProcDirectory + to_string(pid) + kStatusFilename, std::ios::in);
  if (file.is_open()) {
    while (getline(file, line)) {
      replace(line.begin(), line.end(), ':', ' ');
      istringstream stream(line);
      stream >> key >> value;
        if (key == "Uid") {
          uid = value;
        }
    }
    file.close();
  }
  return uid;
}

string LinuxParser::User(int pid) {
  string line, user, uid2, usern, x, end ;
  string uid = LinuxParser::Uid(pid);
  fstream file;
  file.open(kPasswordPath, std::ios::in);
  if (file.is_open()) {
    while (getline(file, line)) {
	    replace(line.begin(), line.end(), ':', ' ');
      istringstream stream(line);
      stream >> usern >> x >> uid2 >> end;
        if (uid2 == uid) {
          user = usern;
        }
    }
    file.close();
  }
  return user;
}

long LinuxParser::UpTime(int pid) {
    string line, value;
    long time;
    fstream file;
    file.open(kProcDirectory + to_string(pid) + kStatFilename, std::ios::in);
    if (file.is_open()) {
      while (getline(file, line)) {
        istringstream stream(line);
 		    for(int i=0; i<22; i++) {
            stream >> value;
          }
        if(value == ""){time = 0;}
        else{time = std::stol(value);}
      }
      file.close();
    }
  return time;
}
