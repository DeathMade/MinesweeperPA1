# MinesweeperPA1

One of university assignments using C. Translated description for the program is as follows: 

The task is to create a program that will calculate the look of the minesweeper.

The input of the program is the board of this game. The board is entered as a rectangular field filled with asterisk (mina) and a dot (free field). The field is entered by row, each row of input contains one row of the playing field. Entering the playing field is finished when the input ends (EOF is active).

The output of the program is a playing field filled with the calculated number of mines that are located around the square.

The program must handle the correctness of the input. If the input is not valid, the program detects this situation and displays an error message. The error message format is again shown in the samples below. An error is considered if the input is:

1) the playing field contains characters other than the asterisk dot,
2) the playing field is not rectangular in shape and
3) the playing field is not at least 1x1.

Your program will run in a limited test environment. It is limited by runtime and the amount of available memory is also limited. The task is not computationally demanding, but it is necessary to work with memory reasonably. Small and huge playing areas are entered at the entrance. If you allocate the board statically, either you will not be able to process large inputs, or you will not pass the basic test memory limit (which enters small inputs, thus significantly reducing the amount of available memory). The test environment uses a memory debugger to check that the memory is working properly. Take care to allocate and free memory.

Demonstration of program work:
Enter the board:
..... * ....
.. * .. * ....
..... * .. *.
.. * .......
Filled playing area: 
.1112 * 2 ... 
.1 * 13 * 3111 
.2222 * 21 * 1 
.1 * 1111111
