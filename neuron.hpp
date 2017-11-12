#ifndef neuron_HPP
#define neuron_HPP

#include "constant.hpp"

#include <vector>

using namespace std;

/*!
 * @brief Neuron class
 * 
 * this class simulate the unit of a single neuron and the way it react
 * to extarnal electrical imput, wheter it is a spike comming from an 
 * other neuron or an constant electrical current
 */
class Neuron
{		
	private:
	
		//!membrane potential
		double V_;
		
		//!collection of the times when the spikes occured
		vector<double> spikeTimes_;
		
		//!tells if the neuron is refractory or not
		bool refractory_;
		
		//!global clock of the neuron !in steps h!
		double neuroClock_;
		
		//!buffer: memory of the spikes recieved at a time t by the neuron
		vector<double> buffer_;

		//!tells which type the neuron is (E:exitatory, I:inhibitory)
		neuron_type type_;
		
		
	public:

	//////////////////////////////
	//                          //
	// constructor & destructor //
	//                          //
	//////////////////////////////
	
		/*!
		 * @brief default constructor
		 * 		  initialise a neuron with a null membrane potential, in a
		 * 		  non repository state, with an internal clock at t=0, with 
		 * 		  an empty buffer and in a non spiking state
		 * 
		 * @param neuron_type type the type of the neuron
		 * 	
		 */
		Neuron(neuron_type type);
		
		/*!
		 * @brief destructor
		 */	
		~Neuron();
		
	//////////////////////////////
	//                          //
	//			Getters			//
	//                          //
	//////////////////////////////

		/*!
		 * @brief get the membrane potential of the neuron
		 * 
		 * @return double V_
		 */
		double getMembranePotential() const;
		
		
		/*!
		 * @brief get the number of spikes the neuron has done during a simulation 
		 * 
		 * @return size_t spikeTimes.size()
		 */
		size_t getNumberOfSpike() const;
	
		/*!
		 * @brief get all the times a spike occured in the neuron
		 * 
		 * @return vector<double> spikeTimes_
		 */
		vector<double> getSpikeTimes() const;
	
		/*!
		 * @brief tells which position of the buffer correspond to a time t
		 * 
		 * @param double t the time
		 * 
		 * @return int i the position corresponding
		 */	
		int getBufferPos (int t) const;
		
		/*!
		 * @brief tells wheter the neuron is excitatory or not (inhibitory)
		 * 
		 * @return true if type_==E
		 * 		   false if type_==I
		 */	
		bool isExcitatory();
		
	//////////////////////////////
	//                          //
	//			Setters			//
	//                          //
	//////////////////////////////
	
		/*!
		 * @brief set the membrane potential to given number
		 * 
		 * @param double newPot new membrane potential
		 */
		void setMembranePotential(double newV);
	
	//////////////////////////////
	//                          //
	//		  Simulation		//
	//                          //
	//////////////////////////////
		
		/*!
		 * @brief update the state of a neuron at each time steps h during a
		 * 		  simulation
		 * 
		 * @param double I the external electric current applied on the neuron
		 * @param bool randomSpike if the neuron recieve random external
		 * 		  noise or not
		 * 
		 * @return true if the neuron spike during this update
		 * 		   false otherwise
		 */
		bool update (double Iext, bool randomSpike);
		
		/*!
		 * @brief compute the embrane potential at time t+h
		 * 
		 * @param double h the time step
		 * @param double I the external electric current applied on the neuron
		 */ 
		void depolarisation (double Iext, double J);
		
		/*!
		 * @brief add the electrical input recieved by the neuron in the buffer
		 * 		  at the corresponding time t
		 * 
		 * @param int t the time corresponding to the buffer's place
		 * @param double input to write into the buffer
		 */
		void setBufferAt (int t, double input);
};

#endif
