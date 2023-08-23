#ifndef GET_DATA_H  // Checks if `GET_DATA_H` isn`t defined
#define GET_DATA_H  // Defines `GET_DATA_H`

#include "constants.h"
#include <iostream>
#include <cstdlib>   // Provides functions for performing various operations related to C-style strings and memory management (popen.pclose)
#include <algorithm> // Provides a wide range of generic algorithms for working with containers like arrays, vectors, and other standard containers


inline std::string get_data(const std::string mac){                          // This is the function definition,it takes parametr `mac` which is used to identify BLE sensor
    std::string cmd = gatt_tool_command + mac + " " + char_read_command; // This command read characteristic with the addres `0x006e`
    FILE* const fp = popen(cmd.c_str(), "r");                                // Opens a pipe to the specified command and returns `FILE` pointer allowing the program to read 
                                                                       // the output of the command

    if (fp == nullptr) {                                        // The code checks if the `fp` (file pointer) is valid If it's not, an error message is printed
        std::cout << "Failed to execute command." << std::endl; // and the function returns the string "F"
        return "F"; 
    }   

    char response[response_size];
    std::string data0 = "";

    while (fgets(response, response_size, fp) != nullptr) { // The function reads the output of the command line by line using `fgets`
        data0 += response;                                     // appends each line to the `data0` string
    }

    pclose(fp);                               // Closing the file pointer
    size_t pos = data0.find(':');             // The code searches for the position of the colon `:` character in the `data0` string.
    std::string data = "";
    try {
        if (pos == std::string::npos) {
            throw std::runtime_error("Colon ':' character not found in data.");
        }

        data = data0.substr(pos + 1);
        data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
    } catch (const std::exception& error) {
        std::cout << "Exception: " << error.what() << std::endl;
        return "F"; 
    }

	return data; // The cleaned data is returned as a `string`

}

#endif // Closes the include guard, marking the end of the header file

// The `popen` and `pclose` functions are used for opening and closing a pipe to a command. These functions are used for dynamic memory allocation and management
// The `stoi` function is used for converting strings to integers


// The `remove` function from the `algorithm` library is used to remove specific characters from a string


/*An inline function in C++ is a function declaration that suggests to the compiler that it should attempt to replace the function call with the actual function code at the point where the function is called. In other words, it's a hint to the compiler to perform "inline expansion" of the function.
 */
