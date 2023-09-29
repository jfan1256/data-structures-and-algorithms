# Pset3: Ahoy Matey!

### Due Friday, Oct 6 2023

Ahoy, matey!
This exercise will get you started programming Hookbook.
In this assignment, you will be practicing **file I/O operations**, **structs**, **dynamic memory allocation**, **array lists**, **sorting**, and **software engineering** in C.

## The Assignment
HookBook is a hot new social media platform built for pirates, by pirates (bulldogs are kind of piratey, right?).
To create HookBook, you'll load a list of pirates from a file and add them to a list that you've created.
For this assignment, the only information about each pirate that you will be given is their name. 

However, your swashbuckling clientele is in the process of creating profiles for themselves that they will give you at a later date.
This means that your Hookbook program must easily transform to accept a list of pirates that includes all kinds of additional information about them, including:
* Their current vessel of employ
* Their current captain (who is another pirate!)
* The number of treasures they've found
* Their favorite port of call
* Maybe other things

After the list of pirates is loaded by your program, your job will be to display each pirate's profile in sorted order, with some placeholders for information you don't have yet.

### To summarize
Your program must:
1. Load a list of pirate names from a file whose name is given to you as a command-line argument
1. Add those pirates into a list, and sort that list in lexicographical order
1. Display the profiles of the pirates, sorted lexicographically
1. All of the above steps must be taken with the fact in mind that future requirements will increase the information you will hold about each pirate.

## Files you are given
* `pirate.h` (Interface), with the following (partial) type definition.
    You must complete the task marked by `TODO`.
    **You may not change anything in this file**, however you may add functions or other definitions to it if you like.
    ```C
    /** 
     * Type of a pirate
     */
    typedef /* TODO: complete this typedef */ pirate;

    /**
     * Allocates enough memory for a pirate, and returns a pointer to the newly-
     *  allocated memory.
     */
    pirate* pirate_create();

    /**
     * Reads a pirate profile from input. Assumes that the input cursor is at the
     *  beginning of a pirate profile (otherwise, its behavior is undefined).
     *
     * Returns a pointer to a pirate created from the profile in input.
     *
     * This function consumes a blank line after the end of the current profile
     *  before returning, meaning that after this function is done, the input
     *  cursor is either at the end of the input file or at the beginning of the
     *  next pirate profile.
     */
    pirate *pirate_read(FILE *restrict input);

    /**
     * Prints a pirate's profile to output in conformance with the output
     *  specification in the README.
     */
    void pirate_print(const pirate *p, FILE *restrict output);

    /**
     * Returns the name of the pirate.
     */
    const char *pirate_name(const pirate *p);

    /**
     * Sets the name of a pirate.
    */
    void pirate_set_name(pirate *p, const char* name);

    /**
     * Compares two pirates, returning a negative number, zero, or a positive
     *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
     */
    int pirate_compare(pirate *a, pirate *b);

    /**
     * Frees all memory associated with this pirate. This function claims ownership
     *  of p.
     */
    void pirate_destroy(pirate *p);

    ```

    > **Note**: Although there is not much information to store or to display about each pirate right now (just their name), the next assignment will ask you to track more information about the pirate.
    > The functions defined in `pirate.h` (which you must implement in `pirate.c`) encapsulate some important functionality such as reading and printing a pirate's profile, accessing individual properties of a pirate, and comparing two pirates.

* `pirate_list.h` (Interface), with the following declarations.
    **You may not change anything in this file**, however you may add functions or other definitions to it if you like.

    ```C
    /**
    * Type of a list of pirates, as an opaque struct.
    */
    typedef struct pirate_list_instance_t pirate_list;

    /**
    * Allocate memory for a new pirate_list and return a pointer to it.
    */
    pirate_list *list_create();

    /**
    * Return the index of the pirate with the same name as p, or a value greater
    *  than or equal to the length of the list if the pirate is not in the list.
    *
    * Ownership of p is not changed.
    */
    size_t list_index_of(pirate_list *pirates, pirate *p);

    /**
    * Only if there is no pirate in the list with the same name as p, insert
    *  pirate p into the list at index idx by copying the pointer, shifting the
    *  latter part of the list one "slot" to the right.
    *
    * If there is a pirate in the list with the same name as p, do nothing, and
    *  return p (the pirate that was not inserted).
    *
    * If the pirate was inserted into the list, return NULL.
    *
    * If p is added to the list, the list claims ownership of the pirate pointed
    *  to by p; otherwise ownership remains with p.
    */
    pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

    /**
    * Remove the pirate from the list with the same name as p, and return a
    *  pointer to it.
    * If there is no pirate in the list with the same name as p, return NULL.
    *
    * The caller of this function is responsible for freeing the returned pirate
    *   if it is not NULL.
    */
    pirate *list_remove(pirate_list *pirates, pirate *p);

    /**
    * Return a pointer to the pirate pointed to by index idx in the list, or NULL
    *  if idx is not a valid index (i.e., it is >= the length of the list).
    *
    * Ownership of the pirate remains with the list.
    */
    pirate *list_access(pirate_list *pirates, size_t idx);

    /**
    * Sort the list of pirates in lexicographical order by name.
    */
    void list_sort(pirate_list *pirates);

    /**
    * Return the number of pirates in the list.
    */
    size_t list_length(pirate_list *pirates);

    /**
    * Free all memory associated with the list, including the pirates in the list.
    */
    void list_destroy(pirate_list *pirates);
    ```

* `libhookbook.h` (Interface) and `libhookbook.c` (Implementation), which are empty except for a defintion guard in the header file.
  * You may use `libhookbook` as you see fit; any functionality required by your `main` function or that might be generally useful should appear in these files.
  * **Importantly, even if you do not add any functionality to `libhookbook`, you must submit both a header file and source file with these names.**
* `makefile` (Incomplete)
    * The provided makefile defines two variables, `CC` and `CFLAGS`.
        You must submit a makefile having identical values for those two variables:
        ```
        CC = gcc
        CFLAGS = -std=c17 -Wall -Werror -pedantic -g
        ```
    * The first target, `HookBook`, is incomplete and you must complete it, however, you must not change its name, and it must generate an executable file named "`HookBook`".
    * The rest of `makefile` is up to you.

## Files you must create

* `hookbook.c` (Driver)
    * This will be the file where your `main` function is going to be.
        Your `main` function must:
        1. Take as the only command-line argument the path to a file containing the pirates' names who will be placed into our HookBook.
        2. Open that file and read from it the list of pirate names, appearing one on each line, storing them in a `pirate_list*`
        3. Sort the list in [lexicographic](https://en.wikipedia.org/wiki/Lexicographic_order) order by pirate name
        4. Print the sorted list to `stdout`, conforming to the format described below in [Output Format](#output-format)
        5. Release all resources (files, memory, _etc._)
* `pirate.c` (Implementation), containing a definition for every declaration or prototype in `pirate.h`
* `pirate_list.c` (Implementation), containing a body for every function prototype in `pirate_list.h`, and a definition for `struct pirate_list_instance_t`
    * `pirate_list` must be implemented as an **array list**, _a.k.a._ **resizing array**
    * The initial capacity of the list must be defined as a constant named `INITIAL_CAPACITY`, having value `25`
    * When the array capacity changes, it must change by a *factor* of `2`, which must be the value of a constant named `RESIZE_FACTOR`
    * Your array list implementation must avoid the oscillation problem discussed in class
    * In addition to functions declared in `pirate_list.h`, `pirate_list.c` must contain a declaration and implementation for each of the following two "helper" functions that are not declared in the header file:
        ```C
        /**
         * Check if the actual number of pirates in the array is "too large"; if it is,
         *  increase the capacity of the array by a factor of RESIZE_FACTOR.
         *
         * If the array capacity was changed, print to stderr the string "Expand to ",
         *  followed by the new capacity of the list and a newline. Here is a possible
         *  print statement:
         *
         *     fprintf(stderr, "Expand to %zu\n", new_capacity);
         *
         * If the capacity was not changed, do nothing.
         */
        void list_expand_if_necessary(pirate_list *pirates);

        /**
         * Check if the actual number of pirates in the array is "too small"; if it is,
         *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
         *
         * If the array capacity was changed, print to stderr the string "Contract to "
         *  followed by the new capacity of the list. Here is a possible print
         *  statement:
         *
         *     fprintf(stderr, Contract to %zu\n, new_capacity);
         *
         * If the capacity was not changed, do nothing.
         *
         * The capacity of the array must never fall below INITIAL_CAPACITY!
         */
        void list_contract_if_necessary(pirate_list *pirates);
        ```
    
* `LOG.md` (Log file), which must include:
  * Your full name and netID, each on their own line in a section with header "`# Author`"
  * Your estimate of the time required (*made prior to writing any code*) in a section with header "`# Estimate of time to complete assignment`"
  * The total time you actually spent on the assignment, formatted as you see fit, but must contain each "shift" during which you worked on the assignment and a brief description of the work completed in each shift, in a section with header "`# Actual time to complete assignment`"
  * The names of all others (but not members of the teaching staff) with whom you discussed the assignment for more than 10 minutes, in a section with header "`# Collaboration`", and
  * A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some), in a section with header "`# Discussion`", which must be the last section

## Other requirements
* You may add to `pirate.h` as you wish but there _must_ remain a declaration of a type named `pirate` and definitions for `pirate_create`, `pirate_read`, `pirate_print`, `pirate_name`, `pirate_compare`, and `pirate_destory`.
    This includes declaring additional functions in that file or making the `struct` an **opaque struct**.
* Each header and source file must use `#include` directives to include things that are _directly_ used by that file&mdash;**no more, no less**. Points will be deducted for clearly extraneous `#include` directives or directives that rely on transitive inclusions.
* You may not use the standard library's `qsort` function to sort the list, nor any other pre-implemented sorting function. You **must** implement a sorting algorithm on your own, and it must run on average in $O(n \log(n))$ time and use $O(1)$ additional memory, where $n$ is the number of pirates in the list.

    > **Note**: Think back to the sorting algorithms we discussed in class recently&mdash;which of them conform to these requirements? Which of them do not?

* You must create _exactly one_ pirate for each name in the input file&mdash;you may not create copies of pirates (copies of _pointers_ to pirates is OK).
* It is possible that you will not use every function you implemented...but you still must implement every function identified in this README! We will run **unit tests** on your program, meaning we will test&mdash;in isolation&mdash;each of the functions identified in this document. For example, you can efficiently implement a solution to this assignment without using the `list_remove` function, although we will run test cases that call `list_remove` on contrived input values and check that your implementation of that function conforms to its specification.

    > Here is a possible unit test for `list_remove`:
    > ```C
    > void test_remove_1()
    > {
    >     pirate_list* p = list_create();
    >     pirate* r = pirate_create();
    >     pirate_set_name(r, "Foo");
    >     list_insert(p, r, 0);
    >     pirate* r2 = list_remove(p, r);
    >     if (list_length(p) == 0)
    >     {
    >         printf("test_remove_1 passed!\n");
    >     }
    >     else
    >     {
    >         printf("test_remove_1 failed!\n");
    >     }
    >     pirate_destroy(r2);
    >     list_destroy(p);
    > }
    > ```
    >
    > It could be called by a `main` function that does nothing but calls a bunch of similar unit test functions.

### Memory Management

Now that you're managing memory yourself, we will test your submission with `valgrind`, a tool to help identify memory leaks.
When run on valid input, **for full credit, your submission must produce a valgrind report with no memory leaks, no errors, and no warnings**.

> **Note**: Valgrind is not available for the most recent several generations of Apple computers, and its support level for modern Windows computers is iffy.
> It is however available, stable, and configured for use on the Zoo.
> This is yet another reason it is important to run your programs on the Zoo before submitting them (an easy way to make sure you do this is to develop them entirely on the Zoo).

## Suggestions and Notes

* In class, we implemented a naive array list to which you could append and remove `int`s from just one end. Use that to jump start your implementation of `pirate_list`.
* Factor out the functionality of `main` into several well-named, easily-understood functions.
* Do not use a raw `char*` for the type of `pirate`&mdash;remember, your program must easily adapt to store additional information about each pirate later on!
* To help manage `#include` directives, draw a "map" of your project's files, with arrows marking *direct* dependencies, and use that to write your include directives
* `NULL` is a special pointer value that means "points to nothing". Attempting to dereference `NULL` will more than likely result in a segmentation fault, which your program must avoid.
* If you find yourself struggling to accomplish a task in the course of your development, break that task down into smaller steps&mdash;chances are you'll know how to do some of the smaller steps!&mdash;and keep breaking it down into smaller and smaller steps that you know how to tackle. Then, compose those smaller steps into a function that solves your original problem.

## Input Format

You will receive pirate information in the form of a regular text file organized as follows (which is the same between this assignment and the next).

> **Note**: For this assignment (only), pirate profiles will not have any additional information associated with them; that is, the input for this assignment will contain only pirate names, each separated from one another by an empty line.
> The next assignment will have a significantly reduced turnaround time (only 1 week vs. 2 weeks), so we encourage you to read, understand, and even implement functionality for handling general pirate profile input as part of this assignment to give you a head start on the next one.

* The first line of the file is the name of a pirate
* The following consecutive non-empty lines hold pirate information, each of which is labeled with the kind of information it provides. Each line is one of the following:
  * "`rank:[rank-name]`", where `[rank-name]` is the name of this pirate's rank on their vessel, such as "captain", "first mate", or "sailor"
  * "`vessel:[vessel-name]`", where `[vessel-name]` is the name of this pirate's current vessel of employ
  * "`port:[port-name]`", where `[port-name]` is the name of this pirate's favorite port of call
  * "`treasure:[treasure-amount]`", where `[treasure-amount]` is a nonnegative integer that counts the number of treasure pieces this pirate owns
  * "`skill:[skill-name]`" where `[skill-name]` is a skill that a pirate might posess, such as "swashbuckling", "treasure hunting", or "navigating"
* Each pirate profile in the input is followed by exactly one empty line

There are some features of the input that are important:

* The pirate's name will be on the first line of their profile, but the rest of the profile information can appear in any order, or may not be present at all
* There may be several pirates with the same name. In this case, only the *first* pirate with a given name should be persisted. Put another way, *in the generated `pirate_list`, every pirate should have a unique name*.
* There may be lines with repeated labels. Except in the case of repeated skills, only the *last* occurrence of a label should be persisted. Repeated skills should *all* be persisted, with duplicate skills interpreted as increased proficiency by the pirate.
* Not every pirate profile will contain a line for every piece of information; your method of storing pirate information must account for this possibility.

## Output Format

The output from your program must be a list of pirate names, sorted in increasing lexicographic order.
Each profile must begin with the pirate's name, which must be followed for a line identifying each additional piece of information you have available for this pirate.

> **Note**: To reiterate, in this assignment, you will have no additional information, so the output will just be a list of names.

Additional pieces of information must appear each on their own line, indented with 4 spaces and beginning with the kind of information displayed ("Captain", "Rank", "Vessel", *etc.*).
In the case of a pirate with multiple skills, the label "Skills" should appear only once, with each *unique* skill on its own line, indented by 13 spaces.
Skills in which a pirate is proficient must be followed on their line by a number of asterisks (`'*'`) equal to that skill's "rating" for the pirate (*i.e.*, the number of times that skill appeared in the pirate's profile in the input).

### Examples

Here are several example runs of the program showing the output both to `stdout` and to `stderr`.

1. File with three pirates
    > File: `A_list.txt`
    > ```text
    > jack sparrow
    >
    > william turner
    >     
    > elizabeth swan
    >
    > ```

    > Command and output:
    > ```text
    > $ ./HookBook A_list.txt
    > elizabeth swan
    > jack sparrow
    > william turner
    > ```

2. File with 30 pirates
    > File: `B_list.txt`
    > ```text
    > captain mansel alcantra
    >
    > john alexander
    >
    > algerine pirates
    >
    > ali basha
    >
    > captain alleston
    >
    > alwilda
    >
    > alexander ammand
    >
    > ibrahim ameer
    >
    > captain cornelius anderson
    >
    > captain androeas
    >
    > sultan of timor angora
    >
    > angria
    >
    > captain thomas anstis
    >
    > antonio
    >
    > john rose archer
    >
    > james austin
    >
    > captain john avery
    >
    > captain bridgeman
    >
    > captain aylett
    >
    > job baily
    >
    > captain baker
    >
    > roger ball
    >
    > john ballet
    >
    > captain baltizar
    >
    > captain bannister
    >
    > barbarosa
    >
    > redbeard
    >
    > captain nicholas barbe
    >
    > captain barnard
    >
    > captain barnes
    >
    > ```
    

    > Command and output (note the line reading, "Expand to 50"!):
    > ```text
    > $ ./HookBook B_list.txt
    > Expand to 50
    > alexander ammand
    > algerine pirates
    > ali basha
    > alwilda
    > angria
    > antonio
    > barbarosa
    > captain alleston
    > captain androeas
    > captain aylett
    > captain baker
    > captain baltizar
    > captain bannister
    > captain barnard
    > captain barnes
    > captain bridgeman
    > captain cornelius anderson
    > captain john avery
    > captain mansel alcantra
    > captain nicholas barbe
    > captain thomas anstis
    > ibrahim ameer
    > james austin
    > job baily
    > john alexander
    > john ballet
    > john rose archer
    > redbeard
    > roger ball
    > sultan of timor angora
    > ```

## Assumptions

You may assume the following about the command-line arguments to the program:

* **Nothing!** 
    We will run your program with no command-line arguments, many command-line arguments, and a single command-line argument that is the name of a file that does not exist.
    In all cases where the first command-line argument is *not* the name of file from which you can read, your program must exit with status code `1` and not cause any errors such as segmentation faults.
    If there are many command-line arguments provided, your program should attempt to interpret the first one as the name of the input file.

You may assume the following about the file referred to by the command-line argument, if you can open it for reading:

* It is a text file. That is, we will not try to open a binary file, _e.g._, an image
* It conforms to the [input specification](#input-format) above
* No line in the file will be longer than 127 characters
* No line in the file will contain any non-ASCII characters
* No pirate profile information will be provided in the input file besides pirate names

## Submission

Submit your project to Gradescope by uploading all files needed to run your program.
It is due **11:59 PM NHT on Friday, October 6, 2023**.

You must submit the following files:

* `makefile` (or `Makefile`)
* `hookbook.c`
* `pirate.h`
* `pirate.c`
* `pirate_list.h`
* `pirate_list.c`
* `libhookbook.h`
* `libhookbook.c`
* `LOG.md`
* Any other files needed to compile and run your program.

Refer to the Syllabus for information on collaboration and late-assignment policy.
