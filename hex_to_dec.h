#ifndef HEX_TO_DEC_H // Checks if `HEX_TO_DEC_H` issn`t defined
#define HEX_TO_DEC_H // Defines `HEX_TO_DEC_H`

#include <string> // Default C++ library

inline int HexToDec(const std::string& hexNumber) { // Takes as a parametr
	return std::stoi(hexNumber, 0, 16);  // Is used to convert the hexadecimal string to an integer in decimal format
}                                       // The `stoi` function is a part of C++ Standard Library and converts strings to integers
					// Second argument (`0`) must be presented as a hexadecimal number
					// Third argument (`16`) the third argument (16) indicates the base of the conversion (hexadecimal)
#endif                                  // Closes the include guard, marking the end of the header file



