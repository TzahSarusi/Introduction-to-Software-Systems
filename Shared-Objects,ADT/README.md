In this exercise we will build a system for managing student grades. For the purpose of building the system, we will use the Shared Library of
Linked-List of type ADT in this exercise.

Part I - System requirements:
You are given a program called prog.exe that has already been written and compiled by us.
With the help of this software, the faculty secretaries can enter details of students, add the same courses to each student
He/she did, and print information to the screen. The program reads commands from the user, according to the following format, and executes them one by one
(Interpreter). Below are the supported commands:

Command: add-student NAME ID
Description: Adds a new student with NAME and ID to the system.

Command: add-grade STUDENT-ID COURSE-NAME GRADE
Description: Adds a new course COURSE-NAME with GRADE (integer) to the student with id ID.

Command: calc-avg STUDENT-ID
Description: Calculates the average of a student with id ID.

Command: print-student STUDENT-ID
Description: Prints the student's information. See comments in "grades.h" for the print format.

Command: print-all
Description: Prints information of all students. Same format as in "print-student".

Command: echo DATA [DATA...]
Description: Similar to Bash's echo, echoes the input text to the screen.

Input can be inserted into prog.exe using Redirection.

The program executes all the above commands by calling functions from the library libgrades.so - which you will have to implement
and to compile. Pay attention to the grades.h interface file - there is a list of all the functions that must be supported. Pay special attention to the case
edge and desired return values. The code you will implement should be written in a file called grades.c.
For building libgrades.so, you can use the list.so-liblibked library given to you, in which a linked list is implemented
in the form of ADT. Think about which lists you will need, and which members are in each list.

Part B - liblinked-list.so:

You are given a library with a linked list implementation. Go through the functions in the interface file linked-list.h and pay attention to the details
the following :
1. What are the user functions of the ADT? What is their structure, and what should be done with them? Remember,
User functions are defined as types for function pointers that the user must provide to the ADT at creation time
A new object.
2. What functions are supported by liblinked-list? In particular, where is the fact that it is an ADT reflected?
3. How do we create a linked list? How were organs added to her? How do we go through the members in the list?
4. In the ADT interface, an opaque data-structure named Iterator is declared. As users, we do not have
No information about the internal structure of this data structure, and we have to work with pointers only (similar to the data structure).
FILE.

Iterators - an accepted abstraction for accessing members within a data structure:

• We do not know what an iterator consists of: in particular, it is possible that its internal structure is different when it comes to an iterator of
A list versus a tree iterator.
• We do know that there are wrapper functions that can be used to perform operations on the iterator.
• In our case, we can:
◦ Initialize an iterator to the beginning or end of the list (list_begin, list_end.)
◦ move an iterator forward and backward (list_next, list_prev.)
◦ Add elements in the middle of the list using an iterator (list_insert.)
◦ Access the object to which the iterator points: for example, in a linked list containing Integers , you can access
Integer to which the iterator points using the list_get operation

Part C - MakeFile construction:
You must create a Makefile that compiles grades.c to grades.o, and links the Object to a dynamic library called
libgrades.so. pay attention :
1. You must declare during linking about the use of the liblinked-list.so library (see how to do this in practice).
2. You must compile the object with special flags (see practice how to do this).
3. Note that when calling prog.exe it is possible that the Loader will not recognize liblinked-list.so and libgrades.so (since
The libraries are not installed in the system. See Workshop 5 on how to overcome this difficulty (note that this should not affect
Your Makefile, it is the user's responsibility to perform these steps (.
4. Put a clean flag as we learned in practice 4. Note that you clean only the files created in the process
The compilation, and not other files (hint: do not clean EXE files.)

Part D - Debugging and measuring will be effective:
1. Make sure that the program runs properly, that there are no memory leaks, and that there are no problems whatsoever. If there are, you can find them
As we learned with the help of GDB (Workshop 4.)
2. Note that at the end of the run the program emits to stderr the total running time of the program in milliseconds. The right submission
And the most effective will earn its owner 0.5 bonus points for the final score. ) Our method of measurement: the running of your parrot
10 times on the same input and average performance.
