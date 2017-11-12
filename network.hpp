#ifndef network_HPP
#define network_HPP

#include "neuron.hpp"

#include <iostream>
#include <vector>

using namespace std;

/*!
 * @brief network class
 * 
 * this class simulates the network created by the connection of multiple
 * neurons. It is in charge of creating the connection between the neurons
 * in a random fashion and to deliver the information from one to another
 * following those connections.
 */
class Network
{
	private:
		
		//!list of all the neurons in the network
		vector <Neuron> neurons_;
		
		//!matrix that map the connections for each neurons
		//!lines : neuron
		//!column : post-synaptic neurons 
		vector< vector<int> > connectionMap_;
		
		//!local clock of the network
		unsigned int netClock_;
		
		
	public:
	
	//////////////////////////////
	//                          //
	// constructor & destructor //
	//                          //
	//////////////////////////////
	
		/*!
		 * @brief initialise a network with a number N of neuron given by the
		 * 		  constant file, a matrix mapping all the connection between
		 * 		  these neurons and an internal clock at t=0
		 */	
		Network();
		
		/*!
		 * @brief destructor
		 */	
		~Network();
		
	//////////////////////////////
	//                          //
	//			Getters			//
	//                          //
	//////////////////////////////
	
		/*!
		 * @brief get the list of the neurons in the network
		 * 
		 * @return vector<Neuron> neurons_
		 */
		vector<Neuron> getNeurons();
		
		/*!
		 * @brief get the connection map of the network
		 * 
		 * @return vector< vector<int> > connectionMap_
		 */
		vector< vector<int> > getConnectionMap();
		
	//////////////////////////////
	//                          //
	//			Display			//
	//                          //
	//////////////////////////////
	/*
	 * those are mainly usefull when working with small networks for
	 * debugging purpose
	 */
	 
		/*!
		 * @brief display the list of neurons in the terminal
		 */
			void displayNeurons();
			
		/*!
		 * @brief display the connection map in the terminal
		 */
			void displayConnectionMap();
			
		/*!
		 * @brief display the spikes of each neuron in the terminal
		 */	
			void displaySpikeTimes();
			
		/*!
		 * @brief display all the aspect of a simulation listed above
		 */
			void displaySimulation();

	//////////////////////////////
	//                          //
	//			Setters			//
	//                          //
	//////////////////////////////
	
	/*!
	 * @brief set manually a connection between two choosen neurons
	 * 
	 * @param int pre index of the pre-synaptic neuron
	 * @param int post index of the post-synaptic neuron
	 * 
	 * used for test purpose in a previous version
	 */
	void setManualConnection (unsigned int pre, unsigned int post);
			
	//////////////////////////////
	//                          //
	//			Print			//
	//                          //
	//////////////////////////////
		
		/*!
		 * @brief print the spikes of each neuron in an external text file
		 * 		  name neuron_data.txt located in the build folder
		 */	
		void printSpikeTimes();	
			
	//////////////////////////////
	//                          //
	//		  Simulation		//
	//                          //
	//////////////////////////////	
	
		/*!
		 * @brief run the simulation of a network from t=0 to t=t_stop
		 * 
		 * @param unsigned int t_stop end time of the simulatioin
		 */	
			void runSimulation(unsigned int t_stop);
			
		/*!
		 * @brief update the state of the network for each time step h
		 * 
		 * @param double I the external electric current applied on each
		 * 		  neurons of the network
		 * @param bool randomSpike if each neuron of the network recieve
		 * 		  an external random noise or not
		 */
			void update();

};

#endif
