In this exercise, we will build a firewall software that filters information according to a predetermined set of rules. In order to implement the
Firewall We will use Cpp to build a simple program, and Bash for the benefit of pressing the rules and entering them into the program we built.
In this exercise we will emphasize three things:
1. Correctness - do you filter the information as required.
2. No memory leaks - you will see that with Cpp it is much simpler to manage memory than in C.
3. Efficiency - we will measure the amount of running time your program takes.


Part A - Communication Network:
In this exercise we will focus on 4 fields that appear in most of the Internet packages that we send and receive:
1. Source IP Address
2. Source Port
3. Destination IP Address
4. Destination Port
Basic concepts
IP address: This is an Integer (4 bytes) that indicates which computer sent the package. For simplicity, let's assume that this address is
to the computer When we write an IP address, we do it in the following format: each byte in Integer is represented in decimal form (0-255,)
And between every two bytes there is a dot e. For example, this IP address: 4.52.133.12 represents this Integer:
int ip = (4<<24) | (52<<16) | (133<<8) | (12);

Mask: A group of several IP addresses can be represented by specifying the number of bits (from left to right) that must be referenced,
While all the other beats are Don't Care. Specifying the number of bits is done by adding a slash (/) after the IP address, and writing
The number (between 0 and 32). For example, the following mask: 255.63.1.1/15 indicates that the leftmost 15 bits should be considered
(MSB) in the IP address, and for the rest of the 17 as Don't care.
The binary representation of 255.63.1.1/15 is (* stands for don’t care):
11111111 0011111* ******** ********

Port: This is a short (2 bytes) that indicates an application number inside the computer. We will not go into the meaning beyond that, we will just say
A port is represented in standard decimal form.
A port range can be represented by writing two numbers separated by a dash, for example 0-65535 represents the entire possible port range.

Packet: We will represent a packet as a string with a collection of 4 fields (as defined above), in the following format:
src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT


Part B - Our Firewall:
The firewall built in the exercise is software that receives as input a list of packets (as defined above), and a law
any defined on only one of the four fields. The rule defines which values of the field are valid. The program will print to
stdout all the packets that comply with the law.

Example 1 - IP address law:
cat pacetks.txt | ./firewall.exe “src-ip=122.0.0.0/8”
This command line will run our firewall so that it prints to stdout all packets in packets.txt whose source address
which contain 122 as the first byte.

Example 2 - Law on port:
cat pacetks.txt | ./firewall.exe “dst-port=22-22”
This command line will run our firewall so that it prints to stdout all the packets in packets.txt specified by the destination
Theirs is exactly 22.


Part C - Implementation of the program Firewall.exe - Strings:
As you must have noticed, you will need to compress a large number of strings in order to work properly with Firewall. For this purpose, we will build
A class called String which will be able to support the basic operations while independently managing the memory it keeps. in particular,
We would like to support the following actions:
• Constructors:
◦ missing parameters: Initializes an empty string
◦ Copy: Initializes a string from another string
◦ with a single parameter * const char : initializes a string from the variable, while performing Clone .
• Distractor: release all the memory stored in String
• operator = :
◦ with parameter * const char : overwrites the current string content, while executing Clone .
◦ With a String parameter: overwrites the current string content, while performing a Clone to the string content.
equals:
◦ With parameter * const char: returns true if the content of the string in this is the same as the parameter.
◦ With a String parameter: returns true if the content of the string in this is the same as the cycle in the parameter.
• split: receives a list of characters according to which the string should be split (Delimiters), destination address for saving the strings
(Output), and a destination address for saving the number of split strings (Size.)
• to_integer: turns the string into a number (or otherwise returns 0 - search Google for the atoi method.)
• trim: returns a new string without spaces at the beginning or end of the string.


Part D - Implementation of the program Firewall.exe - Fields:
In order to compress different IP and Port type fields, first an abstract parent class representing a field, called Field, will be built.
This department will support:
• A constructor that receives a string: this parameter will define the string that we expect to receive at the beginning of the field (for example src-ip or dst-port), and will save it inside the class.
• Distractor: will release all memory of the class.
• set_value : a pure virtual method that will define the set of valid values for that field (for example,
120.0.0.0/8 (. Returns True if there were no problems processing the input.
• match_value : a pure virtual method that returns True only if the value received in the parameter matches the set
The values hatched by set_value (for example, following the previous example, for 120.4.5.6).
• match: a method that accepts strings of a packet (see part 1) and returns True if the packet matches the law
Defined by the field. Please note - when implementing this method it is recommended to call match_value.
Now, we will build two daughter classes - Ip and Port which will inherit from Field and will support a different and specific implementation of each of the methods
set_value and match_value.


Part E - Implementation of the program Firewall.exe - the main file:
In this part you will have to write the main function of the program. This function reads the standard input and the argument
the first of the program, interprets them, and prints to the standard output all the packets that comply with the law entered as an argument (see
An example of how to read the program in part B).
Note: you don't have to write everything from scratch. In your implementation, you must use functions from the library libinput.so that we
we wrote In particular, these are the methods:
• check_args: accepts as parameters the arguments of the main method, and checks that they are correct. If not, printed
Error messages to the screen, and a value other than 0 is returned. The program must be exited with an error status if the function fails.
• parse_input: receives a reference to an object of type Field, and prints to stdout all the packets received in stdin
that comply with the rules hatched in Field (by running the match method defined in Field's interface.)
Please note: the code must be written in a file called main.cpp


Part F - Building a MakeFile
You must create a Makefile which compiles all the cpp files, and links according to the following instructions:

• The String, Field, Ip, Port classes must be linked into a dynamic library called libfirewall.so. this part
Critical, since the library libinput.so uses Field and String, therefore it uses the library
libfirewall.so .
• The main.cpp file must be compiled into a program called firewall.exe. Pay attention to declare that you use
In the dynamic libraries libinput.so and libfirewall.so (because you use them...)


Part G - Scoring and efficiency measurement:
1. Make sure that the program runs properly, that there are no memory leaks, and that there are no problems whatsoever. If there are, you can find them
As we learned with the help of GDB. Below is an example of a command line in GDB for running a program with receiving parameters
Input from stdin :
run “src-ip=3.3.3.3/32” < gdb-test-pkts.in
2. For your use, you are given a simple test called gdb-test with which you can check the correctness of your program.
3. Note that at the end of the run the program emits to stderr the total running time of the program in milliseconds. The right submission
And the most effective will earn its owner 0.5 bonus points for the final score. ) Our method of measurement: running your parrot 10
times on the same input, and average execution on the net time (. Note that we will ignore solutions whose running time is long
More than a second, since the runtime should take milliseconds.


Part H - writing a firewall.sh script:
In fact, our firewall will not filter packets by only one field (as in the firewall.exe program), but will support a large number of
fields (AND operation) and a large number of rules (OR operation). We would like to write a script that receives the packets in stdin,
and as an argument the name of a file containing a large number of rules, and emits to stdout all the packets that matched at least one
from the laws.
Rule structure: a collection of 4 fields between which an AND operation takes place. for example:
src-ip=253.145.84.201/32,dst-ip=189.112.138.228/32,src-port=53-53,dst-port=0-6
This rule will forward packets that have both the relevant source address, both the relevant destination address, and the port numbers
(source and destination) are relevant. Please note: there can be spaces between the equal characters (=) and the comma (). Also, the fields can be
mixed up.
Rules file structure: The rules file contains a number of rules between which an OR operation takes place. Each rule is on a new line. also,
There can be empty lines in the file, as well as comments (starting with #) at the end of a rule line or a normal line. For example:
src-ip= 253.145.84.201/32, dst-ip=189.112.138.228/32, src-port= 53-53,dst-port=0-6
# Comment, yep.
Src-ip=253.145.84.201/31, dst-ip=189.112.138.228/31,src-port=53-53, dst-port=0-6 # Comment in here
src-ip=253.145.84.201/31 , dst-ip=189.112.138.228/24,src-port = 53-700,dst-port=0-60

The script must parse the rules file (hint: it is recommended to use sed, awk and other CLI tools), execute a pilot
using firewall.exe, and output to the standard output all the packets that meet at least one of the rules.
The packets must be sorted using sort (CLI tool).
