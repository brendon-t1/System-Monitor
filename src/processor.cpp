#include "processor.h"
#include <fstream>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
 
  	int a, b, c, d, e, f, g, h, i, j
    string cpu;
    std::string line;                               
    std::fstream file;
    file.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename, std::ios::in);
    if(file.is_open()){
    	getline(file, line))
          	std::istringstream stream(line);
        	stream >> cpu >> a >> b >> c >> d >> e
              >> f >> g >> h >> i >> j;
    file.close();    
    }                            
  return a + b + c + d + e + f + g + h + i + j;
    // long total;
    // vector<string> v = LinuxParser::CpuUtilization();
    // for(string i: v) {
    //     total += stoi(v[i]);
    // }
    // return total;
    //iterate through the vector and add all of them together


}