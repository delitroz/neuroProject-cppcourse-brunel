#include "network.hpp"

#include <iostream>

/*
 * main programm
 * 
 * Run the global simulation with a network consisting of 12500 neurons
 * during a period a time interval of 1s (10000 steps). Then write all the data into
 * an external texte file neuro_data.txt located in the build folder that
 * can be used to plot the results in the provided web script
 * 
 * this version however presents some problems:
 * 	
 * 	1: the time required to run the simulation in its standard size is 
 *	   way to big, it should indeed take roughly 10minutes to run it, which
 * 	   is way under the standard required.
 * 
 *  2: the simulation produce way to much spikes in its standard size, the
 * 	   plot becoms unreadable.
 * 	   However ,playing a bit with the time- and number-of-neurons parameters
 * 	   I could recreate a figure getting close to Brunell's one
 * 
 */
int main()
{
	Network net;

	net.runSimulation(10000);
	
	net.printSpikeTimes();

	return 0;
}

