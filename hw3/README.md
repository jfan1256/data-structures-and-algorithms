# Pset3: Ahoy Matey! Part B

### Due Sunday, Oct 15 2023

Ahoy, matey!
Let's extend our Hookbook from the last assignment.
In this assignment, you will be practicing **file I/O operations**, **structs**, **dynamic memory allocation**, **linked lists**, **sorting**, **function pointers**, and **software engineering** in C.

## The Assignment
In the last assignment, you created an application that reads in a list of pirate names and sorts them before printing out their names as a list. 

This time, your swashbuckling clientele has finally concluded their market research and now they have full profiles for the pirates in their HookBook.
The information they need you to store includes:
* Their current vessel of employ
* Their current captain (who is another pirate!)
* The number of treasures they've found
* Their favorite port of call
* All of the pirating skills they posess

As in the previous assignment, your job will be to display each pirate's profile in sorted order, this time with the full complement of profile information.

There are two additional requirements for this assignment, however.
First, you will be given *two* input files: one as formatted before, with a list of pirate profiles, and another containing pirate/captain pairs, the specification of which can be found below.
Second, the sort order won't be predefined for you.
Instead, you must accept a command-line argument to define the sorting order.
Precisely how you must handle this is described below.

### To summarize
Your program must:
1. Load a list of pirate profiles from a file whose name is given to you as a command-line argument
2. Load a list of pirate/captain pairs from a file whose name is given to you as a command-line argument
3. Accept a *third* command-line argument, which is the sorting order for your output
4. Add those pirates into a list, and sort that list in the specified order
5. Display the profiles of the pirates, sorted according to the argument

## Files you are given
* `skills_list.h` (Interface), with the following type definition.
    **You may not change anything in this file**, however you may add functions or other definitions to it if you like.
    This interface is your chance to flex your interface-designing creativity.
    Consider what you need to do with a list of skills, and define and implement functions that enable you to accomplish those tasks.
    There may by 5-10 function prototypes in this file.
    As you design the interface, consider whether you need to...

    * access a particular skill by name?
    * access a skill at a particular index?
    * remove a skill from the list?
    * handle several skills with the same name?
    * implement a custom type to track additional data about a skill in the list, or will a built-in type suffice?
    * put the skills in a particular order
    * print the list of skills?

    We suggest you use the various list-like interfaces we have seen in class so far for inspiration.
    ```C
    /**
     * Type of a list of pirate skills, implemented as a linked list.
     */
    typedef struct skills_list_instance_t skills_list;
    ```
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
    pirate* pirate_create(void);

    /**
     * Reads a pirate profile from input. If the file cursor is not at the
     *  beginning of a pirate profile, this function returns NULL.
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
     * Returns the vessel of the pirate.
     */
    const char *pirate_vessel(const pirate *p);

    /**
     * Sets the vessel of a pirate.
    */
    void pirate_set_vessel(pirate *p, const char* vessel);

    /**
     * Returns the favorite port of call of the pirate.
     */
    const char *pirate_port(const pirate *p);

    /**
     * Sets the favorite port of call of a pirate.
    */
    void pirate_set_port(pirate *p, const char* port);

    /**
     * Returns the rank of the pirate.
     */
    const char *pirate_rank(const pirate *p);

    /**
     * Sets the rank of a pirate.
    */
    void pirate_set_rank(pirate *p, const char* rank);

    /**
     * Returns the treasure of the pirate.
     */
    unsigned int pirate_treasure(const pirate *p);

    /**
     * Sets the treasure of a pirate.
    */
    void pirate_set_treasure(pirate *p, unsigned int treasure);

    /**
     * Returns a pointer to the profile of the pirate's captain.
     */
    const pirate *pirate_captain(const pirate *p);

    /**
     * Sets the captain of a pirate.
     */
    void pirate_set_captain(pirate * p, const pirate *cpt);

    /**
     * Returns a pointer to the list of skills of the pirate.
     */
    skills_list *pirate_skills(const pirate *p);

    /**
     * Frees all memory associated with this pirate. This function claims ownership
     *  of p.
     */
    void pirate_destroy(pirate *p);

    ```

    > **Note**: This header file contains "getters" and "setters" for most of the fields of a pirate profile you need access to; but only a "getter" for the skills list.
    > *This is intentional*.
    > Consider why you do not need a "setter" for the skills list, yet you do need a setter for, e.g., the treasure.
    > Are the any other setters that you could do without?

    > **Note**: This header file eliminates the `pirate_compare` function you were asked to implement in the last assignment.
    > A pointer to a comparison function is now a parameter to `list_create` in `pirate_list.h`.
    > Consider what necessitated this change and how to adapt your program to handle it.
    > Hint: review the lecture(s) on function pointers and study the demo code carefully.

* `pirate_list.h` (Interface), with the following declarations.
    **You may not change anything in this file**, however you may add functions or other definitions to it if you like.

    ```C
    /**
    * Type of a list of pirates, as an opaque struct.
    */
    typedef struct pirate_list_instance_t pirate_list;

    /**
    * Allocate memory for a new pirate_list and return a pointer to it.
    *
    * The comparison function returns a negative number, zero, or a positive number
    *  as the first argument "comes before", is the same as, or "comes after" the
    *  second.
    */
    pirate_list *list_create(int (*comp)(const void*, const void*));

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
    * Assumes 0 <= idx <= [the length of the list] (otherwise its behavior is
    *  undefined).
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
    * Sort the list of pirates according to the order defined when this list was
    * created.
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

    > **Note**: The biggest change in this file from the version given to you in the previous assignment is that `list_create` takes an argument, which is the **comparison function** to use for list sorting.
    > As the function specification says, the comparison function returns a negative number, zero, or a positive number as the first argument "comes before", is the same as, or "comes after" the second.

    > **Note**: Also note that your implementation of `list_insert` may assume that the index is valid.
    > If you completed the previous assignment without that assumption, your implementation is still correct!
    > The specification for this function states that the behavior is undefined in the case of an invalid index, which means whatever you did to handle that case last time is a-OK.

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

* `hookbookb.c` (Driver)
    * This will be the file where your `main` function is going to be.
        Your `main` function must:
        1. Take three command-line arguments: the path to a file containing the pirates' profiles, the path to a file containing pirate/captain pairs, and the sort order.
        2. Open the profiles file and read from it the list of pirate profiles, appearing as sepcified [below](#input-format), storing them in a `pirate_list*`
        3. Open the captains file and read from it the list of pirate/captain pairs, appearing as specified [below](#input-format)
        4. Sort the list in the order defined by the third command-line argument
        5. Print the sorted list to `stdout`, conforming to the format described below in [Output Format](#output-format)
        6. Release all resources (files, memory, _etc._)
* `skills_list.c` (Implementation), containing a definition for every declaration or prototype in `skills_list.h`.
    **You are required to implement the list of skills as a singly-linked list.**
    * A linked list is arguably not the best tool for this job. We encourage you to think about what would be a better option. (But you are still required to implement a linked list.)
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
  * A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some), in a section with header "`# Discussion`", which must be the last section. Your discussion must also address the following: 
    * Suppose we asked you to allow a user to enter a pirate's name and see information about them. What might be a better data structure than an array list to help you accomplish this task? Why?

    > **Important**: There is a specific prompt you must address in your `LOG.md` file's discussion: Suppose we asked you to allow a user to enter a pirate's name and see information about them. What might be a better data structure than an array list to help you accomplish this task? Why?

## Other requirements

* The implementation of `skills_list` must be as a singly-linked list.
* Each header and source file must use `#include` directives to include things that are _directly_ used by that file&mdash;**no more, no less**. Points will be deducted for clearly extraneous `#include` directives or directives that rely on transitive inclusions.
* You may not use the standard library's `qsort` function to sort anything, nor any other pre-implemented sorting function. You **must** implement every sorting algorithm that you use on your own
    * Sorting a list of pirates must take $O(n \log n)$ time and $O(\log n)$ additional memory (including stack frames) regardless of the command-line sort flag
    * There is no required bound on sorting a list of skills

    > **Hint**: take advantage of this relaxed efficiency requirement for `skills_list` as an opportunity to write code that is particularly easy to understand and reason about, and think about ways in which you can avoid a separate `sort` function altogether&mdash;perhaps by maintaining a sorted order as you insert each skill or by selecting the skills in order from an unsorted list when it comes time to print them.

* You must create _at most one_ pirate for each name in the input file&mdash;you may not create copies of pirates (copies of _pointers_ to pirates is OK).
* It is possible that you will not use every function you implemented...but you still must implement every function identified in this README! We will run **unit tests** on your program, meaning we will test&mdash;in isolation&mdash;each of the functions identified in this document. For example, you can efficiently implement a solution to this assignment without using the `list_remove` function, although we will run test cases that call `list_remove` on contrived input values and check that your implementation of that function conforms to its specification.

    > Here is a possible unit test for `list_remove` (note: this test case *does not* test `pirate_destroy` or `list_destroy`, as the the assertions are made before those functions are called):
    > ```C
    > void test_remove_1()
    > {
    >     pirate_list* p = list_create();
    >     pirate* r = pirate_create();
    >     pirate_set_name(r, "Foo");
    >     list_insert(p, r, 0);
    >     pirate* r2 = list_remove(p, r);
    >     if (list_length(p) == 0 && strcmp(pirate_name(r2), "Foo") == 0)
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

* Start this assignment by copying your implementation of `pirate_list`, `pirate`, and `libhookbook` from your solution for the previous assignment.
  * You will, of course, have to make some changes to your solution for the previous assignment (otherwise, this would not be a very good assignment!) but at least some of it should be straightforward to reuse.
* Factor out the functionality of `main` into several well-named, easily-understood functions that you define in `libhookbook`.
* To help manage `#include` directives, draw a "map" of your project's files, with arrows marking *direct* dependencies, and use that to write your include directives
* `NULL` is a special pointer value that means "points to nothing". Attempting to dereference `NULL` will more than likely result in a segmentation fault, which your program must avoid.
* If you find yourself struggling to accomplish a task in the course of your development, break that task down into smaller steps&mdash;chances are you'll know how to do some of the smaller steps!&mdash;and keep breaking it down into smaller and smaller steps that you know how to tackle. Then, compose those smaller steps into a function that solves your original problem.

## Input Format

The input to the program is three command-line arguments, which represent&mdash;in no particualr order&mdash;the name of the profiles file, the name of the captains file, and a flag indicating the method by which to sort the output.
The order of the command-line arguments is only partially defined:

* The sort method flag may appear anywhere in the command-line arguments, or not appear at all.
* The two non-sort-flag arguments are to be interpreted in order: the first-appearing one is the list of pirate profiles and the second-appearing one is the list of pirates and their captains.

If present, the sort flag argument should be one of "`-n`", "`-v`", or "`-t`".
Their meaning is as follows:
* `-n`: sort the output in **ascending** order by the pirates' names
* `-v`: sort the output in **ascending** order by the pirates' vessels
* `-t`: sort the output in **descending** order by the pirates' treasures

If there is no sort flag present, the output should be sorted in **ascending** order by the pirates' names (as if the `-n` sort flag was provided).
Your sorting algorithm must break ties by sorting tied pirates in ascending order of their names.

The profiles file is the organized as described in the previous assignment:

* The first line of the file is the name of a pirate
* The following consecutive non-empty lines hold pirate information, each of which is labeled with the kind of information it provides. Each line is one of the following:
  * "`rank:[rank-name]`", where `[rank-name]` is the name of this pirate's rank on their vessel, such as "captain", "first mate", or "sailor"
  * "`vessel:[vessel-name]`", where `[vessel-name]` is the name of this pirate's current vessel of employ
  * "`port:[port-name]`", where `[port-name]` is the name of this pirate's favorite port of call
  * "`treasure:[treasure-amount]`", where `[treasure-amount]` is a nonnegative integer that counts the number of treasure pieces this pirate owns
  * "`skill:[skill-name]`" where `[skill-name]` is a skill that a pirate might posess, such as "swashbuckling", "treasure hunting", or "navigating"
* Each pirate profile in the input is followed by exactly one empty line

The captains file contains pirate/captain pairs, with one name per line, organized as follows:

```
underling-name-1
captain-name-1
underling-name-2
captain-name-2
pirate-name-3
captain-name-3
...
```

There are some features of the input files that are important:

* The name of either file does not begin with a hyphen (`'-'`)
* The last line of each file is a blank line.
* No pirate name begins or ends with whitespace.
* In the profiles file, the pirate's name will be on the first line of their profile, but the rest of the profile information can appear in any order, or may not be present at all
* There may be several pirates with the same name. In this case, only the *first* pirate with a given name should be persisted. Put another way, *in the generated `pirate_list`, every pirate should have a unique name*.
* There may be lines with repeated labels. Except in the case of repeated skills, only the *last* occurrence of a label should be persisted. (Repeated skills should *all* be persisted, with duplicate skills interpreted as increased proficiency by the pirate.)
* Not every pirate profile will contain a line for every piece of information; your method of storing pirate information must account for this possibility.
  * If a pirate does not have a line for the piece of information by which the user has requested the program to sort, then that pirate should appear **at the end** of the sorted list and multiple such pirates should be sorted in ascending order by name (just as if they were tied acording to the initial sort parameter).
* In the captains file, every name is also a name of a pirate with a profile from the profiles file.
* Beyond their mere existence, you may make no assumptions about the nature of a pirate and their captain:
  * It may be the case that one pirate's captain has a captain that is another pirate
  * It may be the case that one pirate's captain has as a captain the first pirate
  * It may be the case that a pirate is their own captain
  * A pirate and their captain need not be sailors on the same vessel
  * The "rank" of a captain need not be "captain"
  * Not every pirate with a profile will appear in the captains file

## Output Format

The output from your program must be a list of pirate profiles, sorted in the order defined by the user at the command line.
Each profile must begin with the pirate's name, which must be followed for a line identifying each additional piece of information you have available for this pirate, but *no* lines for pieces of information for which there was nothing in the profile.

The order in which the fields must be displayed is:
* "Captain"
* "Rank"
* "Vessel"
* "Port"
* "Treasure"
* "Skills"

The lines for these additional pieces of information must appear each on their own line, indented by **4** spaces and beginning with the kind of information displayed ("Captain", "Rank", "Vessel", *etc.*) followed by a colon and a space (`": "`).
In the case of a pirate with multiple skills, the label "Skills" should appear only once, with each *unique* skill on its own line, indented by **12** spaces (the first skill must appear on the same line as the "Skills" label).
Skills must be sorted in ascending lexicographic order of their name, and skills in which a pirate is proficient must be followed on their line by a number of asterisks (`'*'`) equal to that skill's "rating" for the pirate (*i.e.*, the number of times that skill appeared in the pirate's profile in the input) minus 1.
([See example 1](#examples) below for further clarification.)

If a pirate has a captain, is must be displayed in the output as follows:

```
    Captain: <captain-name> (<captain-vessel>)
```

### Examples

Here are several example runs of the program showing the output both to `stdout` and to `stderr`.

1. File with three pirates
    > File: `A_list.txt`
    > ```text
    > jack sparrow
    > rank:captain
    > vessel:the black pearl
    > port:tortuga
    > treasure:12
    >
    > william turner
    > port:port royal
    > skill:smithing
    > skill:smithing
    > skill:fencing
    > skill:fencing
    > skill:fencing
    > skill:fencing
    > 
    > elizabeth swan
    > rank:queen
    > treasure:367
    > vessel:the flying dutchman
    > port:port royal
    > skill:leadership
    > skill:subterfuge
    >
    > ```

    > File: `A_captains.txt`
    > ```text
    > william turner
    > jack sparrow
    > jack sparrow
    > elizabeth swan
    >
    > ```

    > Command and output:
    > ```text
    > $ ./HookBook A_list.txt A_captains.txt -v
    > jack sparrow
    >     Captain: elizabeth swan (the flying dutchman)
    >     Rank: captain
    >     Vessel: the black pearl
    >     Port: tortuga
    >     Treasure: 12
    > elizabeth swan
    >     Rank: queen
    >     Vessel: the flying dutchman
    >     Port: port royal
    >     Treasure: 367
    >     Skills: leadership
    >             subterfuge
    > william turner
    >     Captain: jack sparrow (the black pearl)
    >     Port: port royal
    >     Skills: smithing *
    >             fencing ***
    > ```

2. File with 30 pirates, names only, and no captains
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

    > File `B_captains.txt` is empty.

    > Command and output (note the line reading, "Expand to 50"!):
    > ```text
    > $ ./HookBook B_list.txt B_captains.txt -n
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
    In all cases where the command-line arguments are not as specified in the [Input Format](#input-format), your program must print a descriptive error message to `stderr` and exit with status code `1`.

To give you a better sense of the kinds of things you must handle, here are some *valid* commands for running your program, which must be handled correctly:

* `$ ./Hookbook profiles.txt captains.txt -n`
* `$ ./Hookbook profiles.txt -t captains.txt`
* `$ ./Hookbook -v profiles.txt captains.txt`
* `$ ./Hookbook profiles.txt captains.txt`

Here are some invalid ones, which your program must handle by printing a descriptive error message to `stderr` and exiting with status code `1`:

* `$ ./Hookbook` (not enough arguments)
* `$ ./Hookbook profiles.txt` (not enough arguments)
* `$ ./Hookbook -n -t profiles.txt captains.txt` (too many arguments)
* `$ ./Hookbook profiles.txt captains.txt -x` (invlaid sort flag: `-x`)
* `$ ./Hookbook profiles.txt captains.txt foo.txt` (too many filenames)
* `$ ./Hookbook not-a-file.txt not-a-file-again.txt -n` (file doesn't exist)

You may assume the following about the file referred to by the first non-sort-flag command-line argument, if you can open it for reading:

* Its name does not begin with a hyphen (`'-'`)
* It is a text file. That is, we will not try to open a binary file, _e.g._, an image
* It conforms to the [input specification](#input-format) above for the profiles file
* No line in the file will be longer than 127 characters
* No line in the file will contain any non-ASCII characters

You may assume the following about the file referred to by the second non-sort-flag command-line argument, if you can open it for reading:

* Its name does not begin with a hyphen (`'-'`)
* It is a text file.
* It conforms to the [input specification](#input-format) above for the captains file
* The contents of every non-empty line is the name of a pirate with a profile in the profiles file

> **Note**: We will not test your submission with files that you *can* open that do not conform to the specified format, but we may test your program with files that you *cannot* open.

## Submission

Submit your project to Gradescope by uploading all files needed to run your program.
It is due **11:59 PM NHT on Sunday, October 15, 2023**.

You must submit the following files:

* `makefile` (or `Makefile`)
* `hookbookb.c`
* `pirate.h`
* `pirate.c`
* `pirate_list.h`
* `pirate_list.c`
* `libhookbook.h`
* `libhookbook.c`
* `skills_list.h`
* `skills_list.c`
* `LOG.md`
* Any other files needed to compile and run your program.

Refer to the Syllabus for information on collaboration and late-assignment policy.

## Optional Additional Activities

Completing these additional activities is at your discretion and for your learning benefit, but they do not count toward your grade on this assignment or in the course.

1. Check that the input files are actually valid
   * Check that the first command-line argument that's a file name conforms to the profiles file input format
   * Check that the second one conforms to the captains file input format
2. Implement `skills_list` such that one of the following is true:
   * Adding a skill to the list of skills takes $O(1)$ time and printing the list takes $O(n \log n)$ time (and sorts the list just before printing), or
   * Adding a skill to the list of skills takes $O(\log n)$ time (and maintains that the skills are always sorted) and printing the list of skills takes $O(n)$ time

    > **Note**: A linked list cannot conform to these complexity bounds, so if you complete this second additional activity, make a clear note of it in your `LOG.md` file, so that your grader knows why `skills_list` is not implemented as a linked list.
