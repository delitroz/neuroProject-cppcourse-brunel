# neuroProject

### Description  ###
The purpose of this programm is to simulate a neural network.

The main programm create a network, run a simulation covering a time range of 1s and write all the data in an external file name named data_neuro.txt which can be used to plot the results.

To change the size of the network which could be useful in certain context (see comments below). Change the constant N present in the file constant.hpp

### Use ###
to create all the files used to compile the program, in the directory neuroProject-cppcourse-brunel use the command
$ mkdir build; cd build; cmake ..

to compile the program then use in the same repertory
$ make

to generate the doxygen documentation use
$ make doc

finally you can run the executables files by using
for the main programm:
$ ./main

for the tests
$ ./unittest

### Comments ###

this version presents some problems:
	1: the time required to run the simulation in its standard size is far to big, it should indeed take roughly 10minutes to run it, 		   which is way under the standard required.
	   This create some issues with the unittest to: to get it to run in an acceptable time, it's better to run it with the minimal  	    viable configuration of 50 neurons
 
	2: the simulation produce way to much spikes in its standard size, the plot becomes unreadable. However, playing a bit with the 	   time- and number-of-neurons parameters I could recreate a figure getting close to Brunell's one



