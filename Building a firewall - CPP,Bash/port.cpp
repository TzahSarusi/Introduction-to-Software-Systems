#include <iostream>
#include "string.h"
#include "field.h"
#include "port.h"

#define maximumPortNumber 65535
#define PORT_SIZE 2

Port::Port(String patternValue) :Field(patternValue) {

}

Port::~Port() {}

bool Port::match_value(String port) const {
	//trim, convert, and check if port is in valid
	//range
	port = port.trim();
	int packetNumber = port.to_integer();
	bool match = (packetNumber <= maximumPortNumber) && (packetNumber >= minimumPortNumber);
	return (match);
}

bool Port::set_value(String port_val) {
	//initialize required vars
	String* port_arr;
	size_t port_arr_size = 0;
	port_val.split("-", &port_arr, &port_arr_size);
	//port_arr[0] is the given minimal port, port_arr[1] is the 
	//given maximal port
	port_arr[0] = port_arr[0].trim();
	port_arr[1] = port_arr[1].trim();
	int minimumPortNumber_tmp = (port_arr[0]).to_integer();
	int maximumPortNumber_tmp = (port_arr[1]).to_integer();

	if (port_arr == NULL || (int)(port_arr_size) != (int)(PORT_SIZE)) {
		delete[] port_arr;
		return false;
	}

	//check if port range is valid
	if (minimumPortNumber_tmp<0 || maximumPortNumber_tmp<0 || minimumPortNumber_tmp>maximumPortNumber_tmp ||
		minimumPortNumber_tmp>(int)(maximumPortNumber) || maximumPortNumber_tmp > (int)(maximumPortNumber)) {
		delete[] port_arr;
		return false;
	}
	minimumPortNumber = minimumPortNumber_tmp;
	maximumPortNumber = maximumPortNumber_tmp;
	delete[] port_arr;
	return true;
}

