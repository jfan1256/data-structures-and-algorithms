# Author
Jonathan Fan
jsf63

# Estimate of time to complete assignment
5 hours

# Actual time to complete assignment
| Date  | Time Started | Time Spent | Work completed                                                                                                        |
| :---: | -----------: | ---------: | :-------------------------------------------------------------------------------------------------------------------- |
| 9/26  |       7:45pm |       0:30 | read assignment and understand everything                                                                             |
| 9/26  |       8:15pm |       2:00 | started creating functionality for makefile, hookbook.c, and pirate.c out                                             |
| 9/27  |       3:00pm |       2:00 | finished pircate.c and coded pirate_list (except for sorting algorithm).c                                             |
| 9/27  |       5:00pm |       0:30 | fixing segmentation fault error (its j-- not j++ in the forloop!!!!!!)                                                |
| 9/27  |       9:30pm |       1:00 | coded merge sort conquering algorithm                                                                                 |
| 9/28  |       8:00pm |       0:30 | restart sorting algorithm, switched to in-place merge sort                                                            |
| 9/28  |       8:30pm |       0:30 | coded functionality for libhookbook.c                                                                                 |
| 9/28  |       9:00pm |       1:00 | begin debugging (was outputting question marks and segmentation fault)                                                |
| 9/28  |      10:00pm |       0:30 | tried all cases and fixed memory leaks using valgrind                                                                 |
|       |              |            |                                                                                                                       |
|       |              |       8:00 | total time spent                                                                                                      |


# Collaboration
None.

# Discussion
Building the pirate.c was pretty straightforward. Reviewed the slides a lot to understand struct and opaque structs more. Devising the pirate_list was
more tedious. I had to debug two different segmentation fault errors (both SUPER ANNOYING). The first one was due to an infinite loop of j++ not j--. The second one was related
to inserting and trying to append pirates in the libhookbook. I ended up just creating my own function due to the list_insert same name constraint. Inplace merge sort was interesting, I coded that before in a python project, so I was mostly trying to translate that into C. I also had to fix memory leaks (when I read in a input file
and changed the name of the struct, I did not free the placeholder strdup("N/A")).