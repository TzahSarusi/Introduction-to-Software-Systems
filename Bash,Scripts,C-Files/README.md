A malfunction occurred in the Technion's 𝑔𝑟𝑎𝑑𝑒𝑠 system during the most important period of the semester - exam period!
Due to the malfunction, the system is unable to produce score histograms and statistics for the various tests.
The students in the introductory course to software systems in electrical engineering decided to take responsibility and help repair the system.
In this question we will implement a program that will read text files with data about each course and the grades in it and generate a histogram and statistics
needed by the 𝑔𝑟𝑎𝑑𝑒𝑠 system.

Part 1 - Bash script to manage the task:

Name of the script: course_stat.sh
Arguments: Course Number xxxxxx (for example: 044101)

The script should do the following:
1. Checking that the number of arguments received for the script is correct - if not, the following error message will be printed
To STDERR: "𝑊𝑟𝑜𝑛𝑔 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑎𝑟𝑔𝑢𝑚𝑒𝑛𝑡𝑠" and an orderly exit from the script will be performed.
2. Checking that there is a file of the format 𝑥𝑥𝑥𝑥𝑥𝑥.𝑡𝑥𝑡 in the folder - if such a file does not exist, the error message will be printed
Next to STDERR: "𝐶𝑜𝑢𝑟𝑠𝑒 𝑛𝑜𝑡 𝑓𝑜𝑢𝑛𝑑" and an orderly exit from the script will take place.
3. Creating a new folder for the program results in the following format 𝑥𝑥𝑥𝑥𝑥𝑥_𝑠𝑡𝑎𝑡, if such a folder already exists
delete it and its contents and create a new empty one.
4. Reading only the grades column from the grades file 𝑥𝑥𝑥𝑥𝑥𝑥.𝑡𝑥𝑡 and writing them to a new file called 𝑔𝑟𝑎𝑑𝑒𝑠.𝑡𝑥𝑡 under
The folder created in section 3. Detail of the structure of the grade files later in the exercise.
5. Compiling and running the program 𝑐𝑎𝑙𝑐_ 𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑖𝑐𝑠.𝑐, instructions on how to compile can be found in the appendices at the end of the exercise.
6. At the end of the program run, print the statistics file 𝑐𝑜𝑢𝑟𝑠𝑒_𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑖𝑐𝑠.𝑡𝑥𝑡 created by the program
𝑐𝑎𝑙𝑐_ 𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑡𝑖𝑐𝑠.𝑐

Part 2 - a C## program to calculate the statistics:

The name of the program – 𝑐𝑎𝑙𝑐_ 𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑖𝑐𝑠.𝑐
All the files created by the program should be created under the folder 𝑥𝑥𝑥𝑥𝑥𝑥_𝑠𝑡𝑎𝑡 created by the script.

The program must perform the following actions:
1. Opening a new file for writing named 𝑐𝑜𝑢𝑟𝑠𝑒_𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑖𝑐𝑠.𝑡𝑥𝑡 .
2. Opening the file 𝑔𝑟𝑎𝑑𝑒𝑠.𝑡𝑥𝑡 for reading.
3. Performing the following analysis:
• Calculation of the number of students in the course.
• Calculation of the average of the course - accuracy of 3 digits after the period.
• Calculation of the median of the course - for clarification, if there are 𝑁 students in the course
the median will be calculated according to the formula - median = (N+1)/2
• Calculation of the maximum and minimum score.
• Calculation of the percentage passing the course - accuracy of 2 digits after the period.
4. Writing the calculations and the histogram to the file 𝑐𝑜𝑢𝑟𝑠𝑒_𝑠𝑡𝑎𝑡𝑖𝑠𝑡𝑖𝑐𝑠.𝑡𝑥𝑡 in the format that will be described later in the exercise.
5. Closing the files.

Input format:

The input files will be of the following form:
- First line description of the columns
- The rest of the lines - tab separated data
(TAB.)
- It can be assumed that the grades are normal [1,100]
Note that a score of 0 is not considered correct in the exercise
- It can be assumed that the scores are in the second column
of the file.
- It can be assumed that the input files will be in the folder
It is where your script and program are powered.

