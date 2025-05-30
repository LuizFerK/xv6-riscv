## Project Setup
1. Ensure you have the correct environment setup to run the project. You can follow the xv6 installation guide for the RISC-V architecture emulated on QEMU via [MIT's 6.S081 Tools Page](https://pdos.csail.mit.edu/6.S081/2021/tools.html).

2. In the root folder, build the project using `make qemu`.

3. Once the shell initializes, you can run the scheduler test script using the `schedtest` command.

4. The results will be printed to stdout, demonstrating that the process priority classes are supported by the scheduler implementation.

## Fork Changes
This project is a fork of the xv6-riscv repository to test the implementation of a scheduler based on priority class queues with a round-robin strategy. The main code modifications include:

1. `kernel/proc.h:95` - Added `priority_class` to the process struct
2. `kernel/proc.c:16` - Added the process priority queues
3. `kernel/proc.c:36` - Function to get the priority queue based on a ticket
4. `kernel/proc.c:52` - Function to get the priority queue based on the class
5. `kernel/proc.c:68` - Function to enqueue processes in their respective queues
6. `kernel/proc.c:84` - Function to dequeue the first process from the queue
7. `kernel/proc.c:356` - Refactored the `fork` function to accept the process priority class as a parameter
8. `kernel/proc.c:517` - Function to generate a random integer from 0 to max (exclusive)
9. `kernel/proc.c:356` - Refactored the `scheduler` function to draw a random class based on a random ticket and select the first process from the priority queue of the selected class to run
10. `kernel/proc.c:329/401/610/682/704` - Modified so any process that changes state to "RUNNABLE" gets added to the end of its respective queue
11. `Makefile:68` - Added flag to remove built-in fork implementation
12. `user/schedtest.c` - Test script to verify the scheduler algorithm with class drawing and the round-robin strategy
13. All other xv6 user tests were removed

## xv6 base README

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".
