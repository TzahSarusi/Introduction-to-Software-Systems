#include <iostream>
#include "ip.h"
#include "port.h"
#include "field.h"
#define MASK_SIZE 2
#define MIN_IP 0
#define MAX_IP 0xFFFFFFFF
#define IP_SIZE 4
#define MASK_SIZE 2
#define SHIFT 24
#define FOURBYTES 32
#define BYTE 8


IP::IP(String pattern) :Field(pattern) {

}

IP::~IP() {
}

bool IP::match_value(String packet) const {

	//initialize relevant vars
	//and check for valid input
	String *ip;
	size_t ip_size=0;
	int shift_factor=SHIFT;
	unsigned int tmp_ip=0, int_ip=0;
	packet.split(".", &ip, &ip_size);
	if (ip==NULL || (int)(ip_size)!=(int)(IP_SIZE)) {
		delete[] ip;
		return false;
	}
	
	//convert IP to int
	//according to rules explained in assignment
	for (int i=0; i<(int)(IP_SIZE); i++) {
		ip[i]=ip[i].trim();
		tmp_ip = ((ip[i]).to_integer())<<shift_factor;
		shift_factor =shift_factor - BYTE;
		int_ip = int_ip | tmp_ip;
	}
	delete[] ip;
	//check if given ip is in valid range
	return ((int_ip>=min_ip) && (int_ip<=max_ip));
}

bool IP::set_value(String val) {
	//initialize required vars
	String *mask;
    	String *ip;
	size_t mask_size=0;
	size_t ip_size=0;
	int int_mask = 0;

	val.split("/", &mask, &mask_size);
   	//mask[0] is actually the IP address

	//check for valid input
	if ((int)(mask_size)!=(int)(MASK_SIZE) || mask==NULL) {
		delete[] mask;
		delete[] ip;
		return false;
	}

	mask[0]=mask[0].trim();
	mask[1]=mask[1].trim();
	int_mask = (mask[1]).to_integer();
	
	//mask validity checks
	if (int_mask<0||int_mask>FOURBYTES) {
		delete[] mask;
		delete[] ip;
		return false;
	}


	if (int_mask==0) {
		delete[] mask;
		min_ip = 0;
		max_ip = MAX_IP;
		return true;
	}

	//since not all IPs are permitted, begin min/max calc
	//check whether IP is valid
	(mask[0]).split(".", &ip, &ip_size);
	if (ip==NULL || (int)(ip_size)!=(int)(IP_SIZE)) {
		delete[] ip;
		delete[] mask;
		return false;
	}

	//convert IP to int by shifting
	int bit_shift=SHIFT;
	unsigned int tmp_ip_int=0, ip_int=0;
	for (int i=0; i<IP_SIZE; i++) {
		ip[i]=ip[i].trim();
		tmp_ip_int = ((ip[i]).to_integer())<<bit_shift;
		// str_to_int=(ip[i]).to_integer();
		// tmp_ip=str_to_int<<bit_shift;
		bit_shift =bit_shift - BYTE;
		ip_int = ip_int | tmp_ip_int;
	}

	//if mask is maximal size -> ip_range = one value
	if (int_mask == FOURBYTES) {
		min_ip=ip_int;
		max_ip=ip_int;
		delete[] mask;
		delete[] ip;
		return true;
	}

	//apply mask
	ip_int = ip_int >> (FOURBYTES-int_mask);
	ip_int = ip_int << (FOURBYTES-int_mask);

	min_ip = ip_int;
	max_ip = (MAX_IP >> int_mask);
	max_ip = max_ip|ip_int;

	delete[] mask;
	delete[] ip;
	return true;
}
