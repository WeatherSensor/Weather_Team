#ifndef GET_DATA_H  // Checks if GET_DATA_H isn`t defined
#define GET_DATA_H  // Defines GET_DATA_H

#include "constants.h"
#include <iostream>
#include <cstdlib>   // Provides functions for performing various operations related to C-style strings and memory management (popen.pclose)
#include <algorithm> // Provides a wide range of generic algorithms for working with containers like arrays, vectors, and other standard containers


inline std::string get_data(const std::string mac){                          // This is the function definition,it takes parametr mac which is used to identify BLE sensor
	std::string cmd = gatt_tool_command + mac + " " + char_read_command; // This command read characteristic with the addres 0x006e
	FILE* const fp = popen(cmd.c_str(), "r");                                // Opens a pipe to the specified command and returns FILE pointer allowing the program to read 
	// the output of the command

	if (fp == nullptr) {                                        // The code checks if the fp (file pointer) is valid If it's not, an error message is printed
		std::cerr << "Failed to execute command." << std::endl; // and the function returns the string "F"
		return "F"; 
	}   

	char response[response_size];
	std::string data0 = "";

	while (fgets(response, response_size, fp) != nullptr) { // The function reads the output of the command line by line using fgets
		data0 += response;                                     // appends each line to the data0 string
	}
	size_t pos = data0.find(':');             // The code searches for the position of the colon : character in the data0 string.
	std::string data = "";

	if (pos == std::string::npos) {
		std::cerr << "The Program Failed To Connect To The Sensor" << std::endl;
		return "F";
	}

	data = data0.substr(pos + 1);
	data.erase(std::remove(data.begin(), data.end(), ' '), data.end());


	int status = pclose(fp);                               // Closing the file pointer
	if (status != 0) {
		std::cerr << "Failed to close pipe or command failed." << std::endl;
		return "F";
	}


	return data; // The cleaned data is returned as a string

}

#endif // Closes the include guard, marking the end of the header file
