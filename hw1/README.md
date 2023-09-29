# CPSC 223 SPRING 2023 PSET 1: Game of Life

## Due Friday, September 22 at 11:59pm

## Submission checklist 

Your final submission must have (at least) the following files:

* `life.c`
* `life.h`
* `main.c`
* `helpers.c`
* `helpers.c`
* `makefile` (or `Makefile`)
* `LOG.md` (see the section about your [Log File](#log-file) below)

When you submit these files, submit them indvidually to Gradescope.

## Background

Please read this entire document carefully before you begin writing any code!

In this assignment, you will design and write a C program to simulate a one-dimensional version of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
The basic idea of the Game of Life is that cells in a grid are used to simulate biological cells.
Each cell is either alive or dead.
At each step of the simulation, each cell’s current status and its number of living neighbors are used to determine the status of the cell for the next step of the simulation.  

Typically, the Game of Life is set up as a two-dimensional grid.
In this assignment you will build a one-dimensional version that has $N$ cells numbered $0$ through $N-1$.
Your "grid" will be stored in a **statically-allocated array**.
Each cell $i$ is adjacent to cells $i - 1$ and $i + 1$, with two exceptions: cell $0$ is adjacent only to cell $1$, and cell $N-1$ is adjacent only to cell $N-2$.
A live cell has value $1$ and a dead cell has value $0$.
At each step of the simulation, the cell values at that step determine what changes will occur at the next timestep as follows:

* If a live cell $i$ has two live neighbors, then cell $i$ will die
* If a live cell $i$ does not have two live neighbors, then any dead neighbors of cell $i$ will become alive

> **Note**: for all interior cells, two neighbors need to be examined.
> For the first and last cell, there is only one neighbor to examine, and the rules above still apply (this has the effect that once alive, edge cells can never die).

Consider the state with 10 cells:

```
0111010101
```

* Cell 0 is dead; it stays dead. 
* Cell 1 is alive; it has a dead neighbor in cell 0, so cell 0 becomes alive in the next timestep.
    It does nothing to cell 2 (which is already alive).  
* Cell 2 is alive; it has two alive neighbors, so cell 2 dies in the next timestep.
* Cell 3 is alive; it has a dead neighbor in cell 4, so cell 4 becomes alive.
    (It treats cell 2 as still "alive", since that was the cell’s state when this timestep started, and does not do anything to it!) 
* Cell 4 is dead; it stays dead (again, based on the current timestep!)
* Cell 5 is alive; it has two dead neighbors, so both cell 4 and cell 6 become alive.
* Cell 6 is dead; it stays dead.
* Cell 7 is alive; it has two dead neighbors, so both cell 6 and cell 8 become alive.
* Cell 8 is dead; it stays dead.
* Cell 9 is alive; it has a dead neighbor in cell 8, so cell 8 becomes alive.

So at the next step of the simulation, the state would be:

```
1101111111
```

After another simulation step, then the state would be:

```
1111000001
```

Work through this example by hand to make sure you understand the rules for cell modification.
 
## The Assignment 

You will submit `main.c` (which we'll call the "driver"), `life.h` ("interface"), `life.c` ("implementation"), `makefile`, and `LOG.md` files for this assignment (and a pair of helper files).

The point of this assignment is to build your understanding of statically-alocated memory, so **you may not use dynamic memory allocation anywhere in your program: that means you may not use `malloc` or `calloc`!**

### Requirements for `life.h`

`life.h` must contain prototypes for at least the following two functions:

* ```C
  bool isAlive(int field[], size_t i, size_t size);
  ```
    The `isAlive` function takes as arguments an array of `int`s called `field`, an index `i`, and the size of the array (`size`).
    It returns `true` if the cell at position `i` is alive, otherwise returns `false`.
    Note that unlike in many languages, `bool`, `true` and `false` are not keywords in C, so you must `#include <stdbool.h>` to use them.
* ```C
  bool shouldDie(int field[], size_t i, size_t size);
  ```
    The `shouldDie` function takes as arguments an array of `int`s called `field`, an index `i`, and the size of the array (`size`).
    It returns `true` if cell `i` has two live neighbors; otherwise it returns `false`.
    > **Hint**: Checking for neighbors that don’t exist (*e.g.*, things at index `-1` or at an index equal to `size`) will cause an error.
    > Check your indexes before using them! 

> **Note**: The starter code for this assignment includes a ready-to-go `life.h` header file.
> You may add to that file, but **do not change anything that is already there**.

### Requirements for `life.c`

`life.c` must contain an *implementation* for each function prototype in `life.h`.

### Requirements for `main.c`

You should start with the provided `main.c` scaffolding file to ensure your macro definition and general program structure are appropriate.
You **may not** remove anything outside of the `main` function (but you may add to it).

At the top of the file, you must define a single compile-time constant named `SIZE`, which should have value `10`:

```C
#define SIZE 10
```

In the provided `main.c` scaffolding file, this macro is already defined, and it is surrounded by a guard that permits us to override its definition at the command line during compilation, which makes it relatively easy to change its value and test differing field widths.
We will do this during grading, by compiling `main.c` with the following command (we will vary `N`):

```
$ gcc -DSIZE=N -std=c17 -Wall -pedantic -g -c -o main.o main.c
```

For example, if `N` is `30`, your program should accept and simulate Game of Life for a field of width `30`.

> **Note**: **Do not change** the code surrounding the definition of `SIZE` in this file, and ensure the value of `SIZE` in your submitted `main.c` is `10`.

`main.c` must contain a single function with the following signature:

```C
int main(int argc, char* argv[])
```

The `main` function should accept two command-line arguments, which will appear in the following order:

* `time_steps`: a positive integer describing how many "generations" the simulation will run for.

    > **Hint**: Use a low value *e.g.*, 1 or 2 as you write and test your code, and increase it after you confirm expected outputs for the lower values.
    > As part of grading your submission, we will test your program on arbitrarily large values of `time_steps` (within the range of type `int`).
* `init`: a string consisting of the characters `'0'` and `'1'`, of length `SIZE`, representing the initial state for this run of Game of Life.

Thereafter, your `main` function must create a new **statically-allocated array** of length `SIZE` (that is, you may *not* use `malloc` or `calloc`).
Using this array: 

* Print the initial values held in the array (they must match what was entered as the final command-line argument)
* Run the game `time_steps` times, printing the array at the end of each step (so it looks like the examples in the [sample runs](#sample-runs) below)

### Requirements for `makefile` (or `Makefile`)

`makefile` must have a rule to generate an executable called `Life`, which when executed runs the `main` function implemented in `main.c`.
The name of the target must be "`Life`".

## Output format

The first line of ouptut must begin with the string `"Initial values"`, which must be followed by a space-separated list of the initial cell values enclosed by `"[ "` and `" ]"` (note the spaces) that begins at column 17.
Thereafter, each line of output must begin with the string `"Step `_`N`_`"` (for some value `N`, starting at $1$), which must be followed by a space-separated list of the cell values at that timestep enclosed in `'['` and `']'`, beginning on column 17.

> **Note**: You may use the provided functions in `helpers.h` and `helpers.c` to aid in output formatting.
> We encourage you to study the implementations of the helper functions, because scaffolding will decrease as the semester goes on and precise format specification adherence will remain important.

### Sample Runs 

To aid your testing, multiple sample runs are shown below.
Before you begin to write any code, it is crucial that you can replicate these by hand (given the initial values, carry out the next 2, 3, or more timesteps).

#### Example A:

```
$ ./Life 2 1000000001
Initial Values  [ 1 0 0 0 0 0 0 0 0 1 ]
Step 1          [ 1 1 0 0 0 0 0 0 1 1 ]
Step 2          [ 1 1 1 0 0 0 0 1 1 1 ]
```

#### Example B

```
$ ./Life 5 0000110000
Initial Values  [ 0 0 0 0 1 1 0 0 0 0 ]
Step 1          [ 0 0 0 1 1 1 1 0 0 0 ]
Step 2          [ 0 0 1 1 0 0 1 1 0 0 ]
Step 3          [ 0 1 1 1 1 1 1 1 1 0 ]
Step 4          [ 1 1 0 0 0 0 0 0 1 1 ]
Step 5          [ 1 1 1 0 0 0 0 1 1 1 ]
```

#### Example C

```
$ ./Life 3 0111010101
Initial Values  [ 0 1 1 1 0 1 0 1 0 1 ]
Step 1          [ 1 1 0 1 1 1 1 1 1 1 ]
Step 2          [ 1 1 1 1 0 0 0 0 0 1 ]
Step 3          [ 1 0 0 1 1 0 0 0 1 1 ]
```

#### Example D

```
$ ./Life 10 1010011111
Initial Values  [ 1 0 1 0 0 1 1 1 1 1 ]
Step 1          [ 1 1 1 1 1 1 0 0 0 1 ]
Step 2          [ 1 0 0 0 0 1 1 0 1 1 ]
Step 3          [ 1 1 0 0 1 1 1 1 1 1 ]
Step 4          [ 1 1 1 1 1 0 0 0 0 1 ]
Step 5          [ 1 0 0 0 1 1 0 0 1 1 ]
Step 6          [ 1 1 0 1 1 1 1 1 1 1 ]
Step 7          [ 1 1 1 1 0 0 0 0 0 1 ]
Step 8          [ 1 0 0 1 1 0 0 0 1 1 ]
Step 9          [ 1 1 1 1 1 1 0 1 1 1 ]
Step 10         [ 1 0 0 0 0 1 1 1 0 1 ]
```

## Assumptions You May Make

You may assume that we will test your program "in good faith".
In particular, you may assume:

* There are exactly three command-line arguments including the name of the executable (that is, the value of `argc` is `3`)
* The first command-line argument (`argv[1]`) is convertible to an `int` using the `atoi` function from the C standard library
* The first command-line argument, when converted to an `int`, is positive
* The second command-line argument (`argv[2]`) contains exactly `SIZE` characters, each of which is either `'0'` or `'1'`

In all runs of your program that adhere to these assumptions, your program must produce correct output, not encounter any runtime errors, and exit with status code `0`.

In future assignments we will not be so kind with our testing!
To help you prepare, consider what changes you would need to make to your solution for *this* assignment to accomodate the removal of any or all of the above assumptions.
Ask yourself the following questions:

* What if there are fewer or more than 3 command-line arguments?
* What if the first command-line argument is not convertible to an `int` (*e.g.* it is a negative number)? What if it is not a number at all? What if it is `0`?
* What if the second command-line argument does not contain the appropriate number of `'0'`s or `'1'`s? Too few? Too many?
* What if the second command-line argument contains characters other than `'0'` or `'1'`?

We encourage you to make changes to account for such cases and submit them to receive feedback on your implementation in this relatively low-stakes environment, in which you will not be penalized for ignoring ill-formed input.

### Requirements for Your Log file

Your `LOG.md` file should be a [markdown](https://www.markdownguide.org/) file of the general form (that below is mostly fictitious):

```markdown
# Author
Alan Weide 
adw58

# Estimate of time to complete assignment
10 hours

# Actual time to complete assignment
| Date  | Time Started | Time Spent | Work completed                                                                                                        |
| :---: | -----------: | ---------: | :-------------------------------------------------------------------------------------------------------------------- |
| 8/01  |      10:15pm |       0:45 | read assignment and played several games to help me understand the rules.                                             |
| 8/02  |       9:00am |       2:20 | wrote functions for determining whether a roll is three of a kind, four of a kind, and all the other lower categories |
| 8/04  |       4:45pm |       1:15 | wrote code to create the graph for the components                                                                     |
| 8/05  |       7:05pm |       2:00 | discovered and corrected two logical errors; code now passes all tests except where choice is Yahtzee                 |
| 8/07  |      11:00am |       1:35 | finished debugging; program passes all public tests                                                                   |
|       |              |            |                                                                                                                       |
|       |              |       7:55 | total time spent                                                                                                      |

# Collaboration
I discussed my solution with: Petey Salovey, Biddy Martin, and Biff Linnane (and watched four episodes of Futurama).

# Discussion
Debugging the graph construction was difficult because the size of the graph made it impossible to check by hand.
Using asserts helped tremendously, as did counting the incoming and outgoing edges for each vertex.
The other major problem was my use of two different variables in the same function called _score and score.
The last bug ended up being using one in place of the other; I now realize the danger of having two variables with names varying only in punctuation -- since they both sound the same when reading the code back in my head it was not obvious when I was using the wrong one.
```

Specifically, your log file must contain...

* Your full name and netID, each on their own line in a section with header "`# Author`"
* Your estimate of the time required (*made prior to writing any code*) in a section with header "`# Estimate of time to complete assignment`"
* The total time you actually spent on the assignment, formatted as you see fit[^1], but must contain each "shift" during which you worked on the assignment and a brief description of the work completed in each shift, in a section with header "`# Actual time to complete assignment`"
* The names of all others (but not members of the teaching staff) with whom you discussed the assignment for more than 10 minutes, in a section with header "`# Collaboration`", and
* A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some), in a section with header "`# Discussion`", which must be the last section

[^1]: In the example, it is formatted as a table.

## Comments and Coding Style 

Make sure all your code is well-commented and readable.
In particular, make sure to have: 

* good variable names 
* high level comments that explain what the program is doing or what it is implementing 
* lower level comments that explain how particular elements of the program are implemented *if the implementation is not obvious*
* please look at the style guide for further style suggestions and expectations, which has been shared via Canvas

# Hints and Advice 

Before you do any coding, complete a design planning exercise by carrying out the following steps: 

1. Reread the gameplay instructions and consult the [sample runs](#sample-runs) until you understand exactly what will change from one time step to the next
2. Determine what data is involved, based on the problem description 
3. Write out a high level program outline 
4. Write more refined pseudocode within the outline, sketching out each function in pseudocode 
5. Write more refined pseudocode for the main function 
6. Then (and only then!) start turning your pseudocode into real code.
    Compile and test your program often, maybe as frequently as after each line of code!  
7. As you test your code, unexpected things will occur!
    Add print statements to inspect variable values to help understand what your program is doing or&mdash;better&mdash;use [GDB](https://www.sourceware.org/gdb/) (if you're on the Zoo or another Linux machine, including WSL on Windows) or [LLDB](https://lldb.llvm.org/) (if you're on a Mac).

If you feel that adding more functions in addition to the ones outlined in this overview would help your program, you are welcome to do so.
If these extra functions are called from `main`, they should be declared in `life.h` or `helpers.h` and implemented in the corresponding source file (either `life.c` or `helpers.c`, as appropriate).
If these extra functions were useful only in the implementations of your other `life.h` functions, they *should not* be declared in `life.h` and instead *only* exist in `life.c` (you may find it useful to separate their *declaration* from their *implementation*, even within the same file, but you are not required to do so).
Be sure to note any additional functions you have implemented in your `LOG.md` file, and ensure they are well-commented (*i.e.*, there must be an English-language description of their behavior adjacent to their prototype or definition; complicated functions should have comments in their body, too).

> For example, Alan's solution to this assignment included two additional functions in `life.h`:
>
> * `void activate_cell(int field[], size_t i, size_t size)`, which "activates" the cell in `field` at index `i`
> * `void kill_cell(int field[], size_t i, size_t size)`, which "kills" the cell in `field` at index `i`
>
> Even though the implementation of each of these functions is trivial in Alan's code, their presence helps keep his `main` function easy to read&mdash;and, therefore, to understand!

By itself, the C programming language does not provide many functions you can call.
Several useful functions for this assignment are in `stdlib.h`, which you should `#include` in `main.c` and maybe also in `life.h` or `life.c`, depending on how you have structured your program.
One such function, `int atoi(const char* s)` returns the `int` that is represented by the (ASCII) string `s` interpreted as a decimal integer.

### Submission

This assignment is due at **11:59 PM NHT (New Haven Time) on Friday, September 22, 2023**.

Per the Syllabus, late submissions with no Dean's Extension will incur a 5-point penalty for each 12-hour period after the end of the grace period.
Absent a Dean's Extension, no work will be accepted more than 120 hours (5 days) after the due date or after the end of the Reading Period, whichever comes earlier.
Every programming assignment and late period deadline except for the end of the Reading Period and the 120-hour hard limit on late submissions has an automatic 2-hour grace period.
The grace period accounts for last-minute problems like laptop batteries dying, slowdowns on the Zoo, or frogs raining from the sky.
It is strict.

To submit this assignment to Gradescope, you'll upload your source code, your makefile, and any other files required by the assignment.
For this assignment, you should submit (only) the following files:

1. `main.c`
2. `life.c`
3. `life.h`
4. `helpers.c` (*even if you did not use the provided functions*)
5. `helpers.h` (*even if you did not use the provided functions*)
6. `makefile` (or `Makefile`)
7. `LOG.md` (see the section about your [Log File](#log-file) above)
8. Any other source or header files (except system header files) required by your program

Your submission **should not** contain any executable files or object files, not should it contain this README file.

Upload your files to [this Gradescope assignment](https://www.gradescope.com/courses/597738/assignments/3302068) before the deadline.
