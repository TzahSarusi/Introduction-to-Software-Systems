#include <iostream>
#include "ip.h"
#include "port.h"

extern void parse_input(Field&);
extern int check_args(int, char**);

int main(int argc, char** argv) {

	if (check_args(argc, argv) != 0) {
		return 1;
	}
	//initialize rules string from input
	//and rules array
	String rules(argv[1]);
	String* rules_arr;
	size_t rules_arr_size = 0;
	rules.split("=", &rules_arr, &rules_arr_size);

	if (rules_arr == NULL) {
		delete[] rules_arr;
		return 0;
	}

	(rules_arr[0]) = (rules_arr[0]).trim();
	(rules_arr[1]) = (rules_arr[1]).trim();


	//parse port rule
	if ((rules_arr[0]).equals("dst-port") ||
		(rules_arr[0]).equals("src-port")) {
		Port port_rule(rules_arr[0]);
		port_rule.set_value(rules_arr[1]);
		parse_input(port_rule);
	}
	//parse ip rule
	if ((rules_arr[0]).equals("dst-ip") ||
		(rules_arr[0]).equals("src-ip")) {
		IP ip_rule(rules_arr[0]);
		ip_rule.set_value(rules_arr[1]);
		parse_input(ip_rule);
	}

	delete[] rules_arr;

}

