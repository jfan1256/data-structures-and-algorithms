# HW 0: Hello, Jack!

## CPSC 223, Fall 2023

## Alan Weide and Ozan Erat

### Introduction

Welcome to CPSC 223!

In this introductory assignment, you will practice the basics of setting up a Unix environment for C programming, writing a basic C program, and submitting an assignment for grading.
The assignment will tackle the following topics:
1. Connecting to the Zoo via SSH
   * Directly through your terminal
   * Using an extension for an IDE (in this case, Visual Studio Code)
2. Creating a project directory for an assignment
3. Writing your first C programs
   * "Hello, World"
   * "Helo, Jack"
4. Compiling and running a C program
   * GCC directly via command line
   * Makefiles
5. Submitting assignments to Gradescope

You are *required* to complete this assignment on the Zoo.
You may accomplish this by using one of the Zoo workstations in AKW or by connecting via SSH either directly or with the Visual Studio Code Remote-SSH Extension.
One of the submission package requirements for this assignment is a screenshot of your program running on the Zoo.
**You will receive no credit for this assignment if you do not run your program on the Zoo.**

#### Reading this file

This file (and every assignment README in this course) is a [Markdown](https://www.markdownguide.org/) file.
You can open it as you would any text file, but it may be awkward to read by default because it contains format directives that render nicely only when viewed in a Markdown viewer.
Fortunately, most modern text editors (most importantly, Visual Studio Code, which we recommend for this course) ship with a Markdown viewer bundled with them.

To access the Markdown viewer in Visual Studio Code, select the button in the top right of your tab group that looks like a two-column layout and a magnifying glass.
This is the **Preview** view, and it renders Markdown nicely for your viewing pleasure.

This README is structured as a tutorial to cover some of the basic concepts and tools you'll use in completing the assignemts for this course.
The steps you're asked to take are marked in this document with "**TODO:**".
Some of them may not be obvious, so make sure to read the document in its entirety and carefully.

### 1. Connecting to the Zoo

**TODO:** To start this assignment, you will connect to the Zoo via SSH in two ways.
First, directly via the SSH command from your computer's Terminal application, and second by using an extension for Visual Studio Code (VS Code) that will provide you with a consistent development environment whether you work locally or on the Zoo.

#### A. Using SSH Directly

* Using Linux or a Mac
    1. MacOS and most Linux distributions come with an SSH client installed by default. To use it, open a Terminal window and type the following command (with no brackets surrounding your NetID):
    ```
    $ ssh [your-netid]@node.zoo.cs.yale.edu
    ```
    > **Note**: For verbatim commands that you are asked to run, the line will always start with a `$` character, to indicate that it should be entered at a command prompt.
    > Any fields within the command you are expected to fill in with your own value are enclosed in `[]`.
    > The `$` is not part of the command, and any field you are expected to fill in should not have `[]` around it.
    > In fact, we'll use `[]` more broadly to denote parts of text that should be replaced by something else.

    2. Enter your NetID password when prompted, and complete any necessary authentication steps.
* Using Windows with WSL (**strongly recommended** if on Windows)
    1. Install WSL by following the instructions [here](https://learn.microsoft.com/en-us/windows/wsl/install)
    2. Install a Linux distibution of your choice (if you're unsure, we recommend a recent version of Ubuntu, at least 18.04 LTS).
    3. Open a WSL terminal window and follow the instructions above for connecting to the Zoo using Linux.
* Using Windows without WSL (not recommended)
    1. Install an SSH client, such as [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/)
    2. Open your SSH client (the rest of these instructions refer to PuTTY). Enter "`node.zoo.cs.yale.edu`" for the host name. You can leave the port as is, but make sure "SSH" is the selected connection type.
    3. Click "Open", and enter your NetID and password. Complete all other authentication steps.

You'll know you have successfully connected to the Zoo when you have a terminal window with a prompt that looks something like the following (your NetID should appear in place of `adw58` and an arbitrary animal from [this list](https://zoo.cs.yale.edu/newzoo/) of available nodes in place of "`lion`"):
```
[adw58@lion:~]
$
```

From here, you can execute commands and interact with the Zoo just as you would your personal machine through your local terminal.
Type the command "`exit`" to end the SSH session and return to your local machine.

If you would like to connect to a particular Zoo node (for example, if you have a particular affinity for giraffes), you can replace "`node`" in the host name with the name of your favorite animal, such as "`giraffe`".
You can find a list of all available animals at https://zoo.cs.yale.edu/newzoo/.

#### B. Using the Remote-SSH Visual Studio Code Extension

**TODO:** Follow the instructions in [this Google Document](https://docs.google.com/document/d/1UsbTyCDCX7DRpt4arLpV0ybR2OZU0imFt9Ori9o1Fn4/edit?usp=sharing) to set up VS Code for an SSH connection to the Zoo.

### 2. Creating a Project Directory for this Assignment

This section will also serve as a Unix command primer/refresher.
The general structure of a command is:
```
command argument1 argument2 argument3 ...
```

Although the command line is technically bounded, there is no *practical* limit to the number or length of command-line arguments.
The arguments could be anything, including file names, specific values, or option flags.
Conventionally, option flags begin with a hyphen ('`-`') to visually distinguish them from literal values.
By default, command arguments are delimited by whitespace: if you need whitespace *within* an argument, you must delimit that argument with either single or double quotes (`'argument goes here'` or `"argument goes here"`).

In this exercise, you'll create a new directory, navigate to it, and create a file that will become your first C program.

> **Note**: We'll use the terms "folder" and "directory" interchangably in this document.
> Generally speaking, "folder" is the preferred nomenclature when you're using a GUI (graphical user interface) to navigate a file system, while "directory" is preferred when using a command-line interface.

**TODO:** Complete the following steps.

1. Decide what kind of file structure you'd like to use for this course. We recommend keeping all of your course materials together in one "umbrella" directory, and then use a subdirectory for each programming assignment, lecture demo, *etc.* For this exercise, we'll use the name `FA23-223` as the "umbrella" directory, and it will&mdash;again, for the purposes of this exercise&mdash;live in our home directory.
2. Navigate to your **Home Directory**, which is named "`~`". To navigate through the file system on the Zoo (and any Unix-based operating system), you use the `cd` (**c**hange **d**irectory) command. For example, to navigate to your home directory, you would use the following command:
    ```
    $ cd ~
    ```
    > **Note**: For verbatim commands we're asking you to run, their line in the README will always start with a `$` character, to indicate that it should be entered at a command prompt.
    > The `$` is not part of the command.

    > **Note**: To navigate to your Home directory, you can also use the `cd` command without *any* arguments.
3. Create your umbrella directory with the `mkdir` ("**m**a**k**e **dir**ectory) command:
    ```
    $ mkdir FA23-223
    ```
4. Confirm it got created and it has the correct name, using the `ls` (**l**i**s**t) command:
    ```
    $ ls .
    ```
    > **Note**: '`.`' is a special directory name that refers to "the current directory".
    > By default, without any arguments, the `ls` command lists the contents of the current directory.
    > The command "`ls ~`" would also accomplish the same task, since we're currently in our home directory (`~`).
5. Move to your new directory:
    ```
    $ cd FA23-223
    ```
6. Create a directory for this assignment (we'll call it `hw0`), and enter it:
    ```
    $ mkdir hw0
    $ cd hw0
    ```
7. Create a file called `hello_1.c`:
    ```
    $ touch hello_1.c
    ```
    > **Note**: The `touch` command creates an empty file with the given name but does not open it.
    > To open it, you have several options:
    > 1. If you are using the VS Code Remote-SSH extension, run the command `code hello_1.c` from the integrated terminal, or navigate to the file in the explorer sidebar of VS Code and double-click it to open.
    > 2. If you are connected to the Zoo over SSH directly, open the file in one of the available text editors on the Zoo, such as `emacs` or `vi`. The command to do so is the name of the editor followed by the file name you wish to open.
8. Verify the file was created successfully and is empty:
    ```
    $ ls -l
    ```
    > **Note**: The `-l` (lowercase ell) option for the `ls` command stands for "**l**ong format".
    > The output of `ls -l` is much more detailed than the output of bare `ls`.
    > If the `-l` option is given, the following information is displayed for each file: file mode, number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-month file was last modified, hour file last modified, minute file last modified, and the pathname.
    > The line for `hello_1.c` should look similar to the following:
    > ```
    > -rw-rw-r--  1 adw58 adw58         0 Aug 14 09:57 hello_1.c
    > ```

Congratulations! Now you know a little bit about navigating the file system from the command line.
There is, of course, much more about the command line to learn, most of which you'll be able to pick up as you go.
Of course, we'll do our best to explain all new commands we introduce in class and assignments.

Every command on the Zoo (and other Unix systems) has an associated "manpage" (short for "manual page") with its documentation.
**TODO:** For example, to access the manual for `ls`, execute the following command:
```
$ man ls
```

### 3. Writing and Running Your First C Program: Hello, World!

**TODO:** Open your `hello_1.c` file using the `code`, `emacs`, or `vi` command or the VS Code sidebar.
Now it's time to get coding!

**TODO:** Write a program, contained entirely in the file `hello_1.c`, that, when run, prints the string, "`Hello, world!`" followed by a new line to the console and then exits.

**TODO:** Compile your program using GCC (**G**NU **C**ompiler **C**ollection) as shown in class.
Name your executable `HelloWorld`.

**TODO:** Execute your new program.
Here is an example of what you should see when you compile and run it, assuming there are no errors or warnings (**if there are any errors or warnings, you must fix those before submission to earn full credit**):
```
$ gcc -o HelloWorld hello_1.c
$ ./HelloWorld
Hello, world!
```

To execute a program, you issue a command with the name of the executable.
However, your operating system searches on its **PATH** (a sequence of directories) for that executable, and it's highly likely that your current directory is not on that path.
Therefore, you must specify the **complete path** for your executable, which is accomplished in this case by prepending "`./`" to the executable name: remember, "`.`" refers to "the current directory".

### 4. Your Second C Program: Hello, Jack!

Hello, World is a fine program, but it's not very exciting.
Let's add some pizzazz to it by enabling user interaction and directing the computer to respond in a particular way to user input.

**TODO:** Create a new file called `hello_2.c` and open it for editing.

**TODO:** Write a program that greets the user with their name.
It must satisfy the following requirements:
* On startup, the program prompts the user for their name by displaying the phrase, "`Enter your name:`" followed by a space. The program then waits for the user to enter their name via `stdin`, interpreting the user's entry up to but excluding the first newline character as the user's name.
* Once the program has the user's name, it greets the user by printing the following greeting on its own line (remember, `[]` just indicate a field to replace with some other text; they should not be displayed):
    ```
    Hello, [users-name]!
    ```

Here is a sample interaction showing the compilation and execution of a correct implementation of this program:
```
$ gcc -o HelloJack hello_2.c
$ ./HelloJack
Enter your name: Ozan Erat
Hello, Ozan Erat!
```

For this assignment, you **may not** use any pointers.
You may, however, assume that the user will enter no more than 126 characters as their name.

**TODO:** Finally, remove the two executables you've generated using the `rm` (**r**e**m**ove) command:

```
$ rm HelloJack HelloWorld
```

> **Note**: to remove many files at once, you might wish to take advantage of the Unix **wildcard** character, '`*`'.
> The wildcard character matches any number of any characters.
> For example, to perform the `rm` command above, we might have written "`rm Hello*`" instead.
> Since the only two file names in our folder that begin with "Hello" (note the capital 'H'!) are `HelloJack` and `HelloWorld`, those are the files that would be removed.
> You should be careful with the wildcard character, however&mdash;you can probably imagine how easy it is to accidentally delete some necessary files if you are not paying attention.

Don't worry! We'll regenerate them in a more felxible manner in the next section.

### 5. Creating a Makefile

We hope it's obvious that not all of your programs will consist of a single file that you can compile with such a short command to invoke GCC.
The final part of this assignment will guide you in the creation of an extensible [makefile](https://www.gnu.org/software/make/) that you'll be able to adapt to your needs in future assignments and even in your programming projects outside of this course!

There are a few key pieces in a makefile:
1. Variables
2. Targets
3. Dependencies
4. Recipes

(Targets, Dependencies and Recipes together make up the makefile's **Rules**.)

**TODO:** To start, create a new file called `makefile`.
This is one of two conventional names for a file containing variables and rules for the GNU Make tool.
(You could also call it `Makefile` (with a capital 'M').)

The Make tool figures out automaticaly which files it needs to update, based on which source files have changed.
It also automatically determines the proper order for updating files, in case one non-source file depends upon anouther non-source file.
The biggest benefit that Make affords you as a developer is that if you change only a few source files and then run Make, it does not need to recompile all of your program&mdash;it updates only those non-source files that depend directly or indirectly on the source files that you have changed.

At its core, each Make recipe is a sequence of commands to be executed.
As a side effect of this generality, Make is not limited to compiling a program.
You can also use Make to control installing or deinstalling a package or really anything else you want to do often enough to make it worthwhile to write down how to do it (such as running a test suite).

At the top of every makefile is a list of variables with one per line in the format "`VARIABLE = value`" (conventionally, make variables are named with all capital letters).
Following that is a sequence of targets.
When you invoke the Make tool with the command `$ make some-target`, Make will find the target with name `some-target` and check its dependencies.
If the target is newer than all of its dependences, then it does not need to be regenerated (so Make will do nothing).
Otherwise, each newer dependency is generated (perhaps according to a different rule in the makefile) before it is used in regenerating `some-target`.

The basic syntax of a Make rule is as follows:
```
target: dependencies...
    commands
    ...
```

We'll start with the variables we will use in our makefile, which in this case will be used to compile C programs into executables using the GCC C compiler.
There are two conventional variables we should define when we want to use Make to build C programs: `CC`, and `CFLAGS`.
`CC` stands for "**C** **C**ompiler", and for this course should have the value `gcc`.
**TODO:** To set this in your makefile, include the following line at the top of the file:
```
CC = gcc
```

**TODO:** The `CFLAGS` variable should contain all flags that are *common* among all targets in your makefile.
We'll keep this boilerplate for now (if you're interested in what these flags mean, we encourage you to look it up, though we'll discuss it in class eventually):
```
CFLAGS = -std=c17 -Wall -Werror -pedantic -g
```

Now that you've defined the relevant variables, it's time to get writing our first rule, which we'll name the conventional "`all`".
The first target in a makefile should always be named "all" to adhere to convention, and it should compile the entire program and produce an exectuable (or executables).
The `all` target should appear first because invoking the `make` command without any target name will trigger the first target in the makefile.
This assignment asks you to create two executables: `HelloWorld` and `HelloJack`, so that's what our `all` target will do.
**TODO:** We specify this to make by designating `HelloWorld` and `HelloJack` as *dependencies* of the `all` target as follows:
```
all: HelloWorld HelloJack
```

If we run `make` or `make all` at this point, we'll get the following message (or something very similar):
```
$ make
make: *** No rule to make target `HelloWorld', needed by `all'.  Stop.
```

We hope you can deduce what this message is warning you about, but if not, here's a hint: how does Make know what HelloWorld is and how to create it?
**TODO:** Define another two targets, with recipes containing commands that Make can run to generate our executables named `HelloWorld` and `HelloJack`!

Here's a possible rule for `HelloWorld`, which directs Make to run exactly the command we did above to compile our first program:
```
HelloWorld: hello_1.c
    gcc -o HelloWorld hello_1.c
```

**TODO:** Write an analogous rule to create the `HelloJack` executable.
Test that your rules create the appropriate executables by running `$ make` or `$ make all`, and then executing those programs as you did above.

Notice that in your current makefile, there is no reference to the `CC` or `CFLAGS` variables, which we worked so hard to define.
To get the value of a variable within a makefile, use the syntax `$(VARIABLENAME)` within a recipe command.
Doing so performs a textual substitution of the variable's value at that point in the script.
For example, you might rewrite the `HelloWorld` rule as follows:
```
HelloWorld: hello_1.c
    $(CC) $(CFLAGS) -o HelloWorld hello_1.c
```

**TODO:** Replace both rules with versions that make use of both the `CC` and `CFLAGS` variables and run `make` again.

If you didn't remove the previous versions of the executables, you'll see a message such as "``make: Nothing to be done for `all'.``".
**TODO:** If you see this message, remove your executables now and re-run Make.

Did you encounter any surprises?
It's possible that received a warning on this compilation run that you did not on the previous one.
If so, it's likely the result of the `-Wall` flag, which means "turn on **all** **w**arnings".
By default, some warnings are considered so rarely of concern that the default configuration of GCC does not report them.
However, since one purpose of this course is to build your coding discipline, we *do* want those warnings reported so that we can build software that's as robust as possible.

**TODO:** Fix any errors or warnings generated by compilation, ensuring that the output of `make` looks as follows:
```
$ make
gcc -std=c17 -g -pedantic -Wall -o HelloWorld hello_1.c
gcc -std=c17 -g -pedantic -Wall -o HelloJack hello_2.c
```

It might get tiring having to remember to remove your executables every time you update the makefile.
Fortunately, we can use Make to automate that process, too!
A standard target you should include in all of your makefiles is named `clean`, which should delete files generated by program compilation&mdash;normally, all files generated either directly or indirectly by the `all` target.

**TODO:** Write a rule for the `clean` target that removes every file generated by the `all` target but&mdash;crucially&mdash;**not** any of your source files.

> **Hint**: `make all` creates more than just the `HelloWorld` and `HelloJack` executables!
> Check the contents of your project directory with `ls -l -a` to see precisely what is generated (the `-a` option means "list **a**ll files", which includes some hidden files not normally listed by `ls`).

> **Hint**: If you need to remove a directory, use the `-r` (**r**ecursive)option for the `rm` command, and to prevent the command from failing if the file doesn't exist, use the `-f` (**f**orce) option.

**TODO:** Test that `$ make clean` performs as intended by checking the contents of your folder before and after calling it, and by regenerating your executables and symbol directories with `$ make all`.

Now there's just one more thing to note in your makefile: the rules for `HelloWorld` and `HelloJack` both have repeated file names.
We'll see throughout this course that repetition anywhere should be a signal to us that we can do something differently.
In this case, we can take advantage of some of Make's [automatic variables](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html): `$@` (the name of the target of the rule) and `$^` (a space-separated list of all dependencies of this target).

**TODO:** Rewrite the rules for `HelloWorld` and `HelloJack` to use automatic variables, and test that they work as intented.

**TODO:** Before moving on to the final section, run `$ make clean`.

### 6. Submission

This assignment is due at **11:59 PM NHT (New Haven Time) on Friday, September 8, 2023**.

Due to the nature of this assignment and its timeline with respect to the shopping period at the start of the semester, for **this assignment only**, no late penalties will be assessed until the deadline of the next assignment (Friday September 22).
You can find details about the late submission policy in this course in the Syllabus.

If you've followed all instructions, your project folder should contain two C source files: `hello_1.c` and `hello_2.c` as well as a file called `makefile` containing rules for 4 targets: `all`, `HelloWorld`, `HelloJack`, and `clean`.
Since you just ran `make clean`, there should be no executable or `.dSYM` folders in the directory.

Now it's time to submit your assignment to Gradescope!

**TODO:** To do so, you'll upload all files required by the assignment to Gradescope.
For this assignment, you should submit (only) the following files (the screenshots may all be in the same image):
1. `makefile`
2. `hello_1.c`
3. `hello_2.c`
4. A screenshot of the terminal, connected via SSH to the Zoo, showing the output of `make all` in a clean project directory (it must compile two executables without errors or warnings, using the required compilation commands)
5. A screenshot of the terminal, connected via SSH to the Zoo, showing the output of executing `HelloWorld` (it must print "Hello, World!")
6. A screenshot of the terminal, connected via SSH to the Zoo, showing the output of executing `HelloJack` (it must propmt the user for their name and then greet the user)

To get the files for this assignment from the Zoo to your local machine, you have a few options.
* If you are using the Zoo via the VS Code Remote-SSH extension, select all files you wish to include in your submission, then right-click on one of them and select "Download". Choose a location on your local machine to store the files.
* If you are using the Zoo via SSH directly, you can get your files by exiting your SSH session and using [SCP](https://man7.org/linux/man-pages/man1/scp.1.html) to copy files from the Zoo to your machine. Since we don't expect many of you to use this mode of connection, we'll leave it at that and suggest that you speak to one of us or a ULA directly for further assistance.
* If you are comfortable using Git or another version control system, you can sync your files on the Zoo with a copy of the repository on your local machine via a Git repository host such as Github. (If you are comfortable with Git, we encourage you to use it for your assignments in this course, although we will not cover it in class. If you're unfamiliar with Git, we encourage you to read the [Git tutorial](https://git-scm.com/docs/gittutorial) and try it out.)

**TODO:** Once you have your files on your local machine, upload them to the Gradescope page for [Homework 0](https://www.gradescope.com/courses/597738).

### Some Notes

This assignment is designed as a tutorial to get you up and running on the Zoo using the tools available there.
The remaining assignments' README documents will be less tutorial-like and will consist primarily or entirely of the requirements that your program must satisfy to earn full credit for the assignment.
That said, as the course progresses and we introduce more tools to your repertoire, we may include mini-tutorials either as part of an assignment README or via supplemental sessions and documents.

This is the only assignment in which you are *required* to use the Zoo, but we **strongly encourage** you to use the Zoo to develop your remaining assignments for two main reasons:
1. Your submissions will be executed on the Zoo for grading, and different operating systems sometimes exhibit inconsistent behavior for certain C programs. Therefore, you should always test your programs on the Zoo, anyway, so you might as well develop on the Zoo. **"It works on my machine!" is not an excuse for incorrect submissions.**
2. If you've set up your environment appropriately, working on the Zoo via SSH is not so different from working on your local machine, so there's no logistical reason not to use the Zoo.

<hr/>
&copy;2023 Alan Weide and Ozan Erat, Yale University Department of Computer Science
