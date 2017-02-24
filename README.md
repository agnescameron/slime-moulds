# slime-moulds
Code for cellular automata model of slime mould Physarum Polycephalum

This code has been developed as part of a dissertation project that seeks to explore and develop the Gunji et al cellular automaton model of the slime mould physarum polycephalum (https://en.wikipedia.org/wiki/Physarum_polycephalum). It creates a visual output on a 50x100 grid in the Terminal window.

The program consists of two phases: a growth phase, in which the plasmoid is initialised, and a migration phase, where either amoebic or chemotactic motion is observed. The slime 'migrates' by softening its cell wall, accepting an empty cell and pushing this cell through itself. In chemotactic motion, the slime preferentially absorbs empty cells from areas closest to the food source, which creates a net motion towards this (a mechanism more easily observed by enabling bubble printing). See Gunji paper for full explanation and algorithm.

To use the code, compile and run the file slime.cpp in c++0x. The program invites the user to declare variables, which will alter the outcome of the simulation. In order, these are:

GROWTH:
Initial seed size: the number of cells that form the initial seed of the slime (spread randonly around an initial point)

Number of food sources: how many randomly-distributed food sources are distributed. By typing zero, the slime will perform amoebic, rather than chemotactic motion.

Steps for initial growth phase: expands the slime around the initial seed

MIGRATION
s: This is the number of empty cells that must surround a bubble that has entered the slime (NSEW, there are no diagonal cells), for that bubble to be considered 'on the edge' of the slime, and therefore expelled

Number of Cells a Bubble Can Move: limits bubble flow after a set number of steps. The smaller this is, the more fragmented the plasmodium becomes.

Limit for cycles: Number of iterations of 'accepting a bubble'. This can be extended after the program has run.

Print the bubble: Useful for getting a feel for the mechanism of how the algorithm works, but makes code distinctly slower.
