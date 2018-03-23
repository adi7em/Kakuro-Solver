# Kakuro-Solver
# @author- Aditya Ranjan

This is the Kakuro Solver project using the CSP(Constraints Satisfaction Problem) in C++.
The executable is named as "myfile", which can be used to solve the problem. The input format to the code can be seen in sample inputs in the file "inputFiles".

Input Format: 1) First two lines indicates number of rows and columns respectively.
2) The horizontal and vertical represents one by one filling of respective cells in the row or column format of the board.
3) '#' represents black cells that do not have to be filled.
4) Empty cells in the puzzle that need to be filled with a number are represented as '0'.

Output Format: Output of the code will be written in the specified output file which will be exactly in the same format expcept that all the '0' cells would have been filled with numbers 1-9 satistying the constraints.

How to Run(in Linux): 1) Place the input file in the same directory as executable and go to the directory.
2) type $ ./myfile inputfile outputfile

How to make Changes: For making the changes in the you have to go to .cpp and .h files. After changes are made, Recompile the code using following command-
$ make

Now a new executable will be created with name "myfile". Now this can be used to run the code as before.
