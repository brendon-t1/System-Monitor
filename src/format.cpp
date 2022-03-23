#include <string>
#include <iomanip>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
		string time;
        int hours;
  		int minutes;
  		int local_seconds;
  		minutes = seconds / 60;
  		hours = minutes / 60;
  		minutes -= (hours * 60);
  		local_seconds = seconds - (hours * 60 * 60) - minutes * 60;
  		if(hours < 10){
          time += "0";
          time += to_string(hours);}
        else{time += to_string(hours);}
  		time +=":";
  		if(minutes < 10){
          time += "0";
          time += to_string(minutes);}
        else{time += to_string(minutes);}
    	time +=":";
  		if(local_seconds < 10){
          time += "0";
          time += to_string(local_seconds);}
        else{time += to_string(local_seconds);}

	return time;
}