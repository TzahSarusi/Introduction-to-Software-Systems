#include <iostream>
#include <stddef.h>
#include <cstring>
#include <ctype.h>
#include "string.h"
#define SPLIT_ERROR -1



String::String() {
	this->length = 0;
	this->data = NULL;
}
String::String(const String& str) {
	//construct string from string

	//check for valid input
	if (str.data == NULL || str.length == 0) {
		this->length = 0;
		this->data = NULL;
	}
	else {
		//copy contents of string	
		this->length = str.length;
		this->data = new char[this->length + 1]; //
		strncpy(this->data, str.data, this->length + 1);
	}
}

String::String(const char* str) {
	//construct string from char*

	//check for valid inputs
	if (str == NULL) {
		this->length = 0;
		this->data = NULL;
	}
	//copy contents
	else {
		this->length = strlen(str);
		this->data = new char[this->length + 1];
		strncpy(this->data, str, this->length + 1);
	}
}

String::~String() {
	if (this->data != NULL) {
		delete[] data;
	}
}

String& String:: operator=(const String& rhs) {
	//check for equality in multiple cases;
	//same address, empty data,
	//and 0 length
	if (this == &rhs) {
		return *this;
	}
	if (this->data != NULL) {
		delete[] data;
	}
	if (rhs.length == 0) {
		this->length = 0;
		this->data = NULL;
	}
	//else: copy contents
	else {
		this->length = rhs.length;
		this->data = new char[this->length + 1];
		strncpy(this->data, rhs.data, this->length + 1);
	}
	return *this;
}

String& String:: operator=(const char* str) {
	//perfectly analogous to previous operator
	if (this->data != NULL) {
		delete[] data;
	}
	int str_len = strlen(str);
	if ((str == NULL) || (str_len == 0)) {
		this->data = NULL;
		this->length = 0;
		return *this;
	}
	else {
		this->data = new char[str_len + 1];
		this->length = str_len;
		strncpy(this->data, str, str_len + 1);
		return *this;
	}
}

bool String::equals(const char* rhs) const {
	size_t str_len = strlen(rhs);
	//check for equality in edge cases
	//of empty strings
	if ((rhs == NULL) && (this->data == NULL)) {
		return true;
	}
	else if (this->length != str_len) {
		return false;
	}
	//else, strncmp
	else {
		return (!strncmp(rhs, this->data, this->length - 1));
	}
}


bool String::equals(const String& rhs) const {
	//analogous to prev operator
	if ((rhs.data == NULL && this->data == NULL)) {
		return true;
	}
	else if (this->length != rhs.length) {
		return false;
	}

	else {
		return (!strncmp(rhs.data, this->data, this->length));
	}
}

void String::split(const char* delimiters,
	String** output, size_t* size) const {
	//if string is empty - error
	if (this->data == NULL) {
		*size = SPLIT_ERROR;
		return;
	}

	//substring indexing; count num
	//of substrings
	int substr_num = 1;
	for (int i = 0; i < (int)(this->length); i++) {
		for (int j = 0; j < (int)(strlen(delimiters)); j++) {
			if (delimiters[j] == (this->data)[i]) {
				substr_num += 1;
				break; //to avoid delimeter double counting
			}
		}
	}
	//update size
	*size = substr_num;

	if (output == NULL) {
		return;
	}
	//initialize required vars
	int substr_idx = 0;
	int start_idx = 0;
	*output = new String[substr_num];
	std::string fnl_str;
	std::string data_str(this->data);

	//going over string again to find delimiters
	//of course could be done with an array during prev
	//for loop, but led to bugs
	for (int i = 0; i < (int)(this->length); i++) {
		for (int j = 0; j < (int)(strlen(delimiters)); j++) {
			if (delimiters[j] == (this->data)[i]) {
				if (i == start_idx) {
					start_idx = i + 1;
					*size = (*size) - 1;
					break;
				}
				//string conversion and substr
				fnl_str = data_str.substr(start_idx, i - start_idx);
				char* char_str = new char[fnl_str.length() + 1];
				strcpy(char_str, fnl_str.c_str());

				(*output)[substr_idx] = String(char_str);
				start_idx = i + 1;
				substr_idx += 1;
				delete[] char_str;
			}
		}
	}

	//last substring is parsed seperately
	//to prevent edge cases
	if ((int)(this->length) == start_idx) {
		*size = (*size) - 1;
	}
	else {
		fnl_str = data_str.substr(start_idx, (int)(this->length) - start_idx);
		char* char_str = new char[fnl_str.length() + 1];
		strcpy(char_str, fnl_str.c_str());
		(*output)[substr_idx] = String(char_str);
		delete[] char_str;
	}
}

int String::to_integer() const {
	//check that string is valid (unsure if
	//required). if itis, atoi
	for (int i = 0; i < (int)(this->length); i++) {
		if (isdigit((this->data)[i]) == 0) {
			return 0;
		}
	}
	return std::atoi(this->data);
}

String String::trim() const {

	if (this->data == NULL) {
		return String();
	}
	//initialize required vars
	int start_idx = 0;
	int end_idx = (this->length) - 1;
	//find string edges
	while (this->data[start_idx] == ' ') {
		start_idx++;
	}
	while ((this->data[end_idx] == ' ') && (start_idx != end_idx)) {
		end_idx--;
	}
	//checks whether string is empty
	if (data[end_idx] == ' ') {
		return String();
	}
	end_idx++;


	//setting the output
	std::string trim;
	std::string original(this->data);
	trim = original.substr(start_idx, end_idx - start_idx);
	char* tmp_str = new char[trim.length() + 1];
	strcpy(tmp_str, trim.c_str());
	String output = String(tmp_str);
	delete[] tmp_str;
	return output;
}
