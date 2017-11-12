#include "network.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <cassert>

using namespace std;

	//////////////////////////////
	//                          //
	// constructor & destructor //
	//                          //
	//////////////////////////////
	
Network::Network()
		:neurons_(), 
		 connectionMap_(N, vector<int>()),
		 netClock_(0)
{	
	/*!
	 * by default ou network consist in a number N of neurons stocked in the constant file 
	 * 
	 * we fill vector of neurons the following way:
	 * 
	 * the 4N/5 first elements are excitatory neurons
	 * the N/5 left are inhibitory neurons
	 */
	
	//adding the exitatory neuron		
	for(int i(0); i<Ne ; ++i)
	{
		neurons_.push_back(Neuron(E));
	}
	//adding the inhibitory neurons
	for(int i(0); i<Ni; ++i)
	{
		neurons_.push_back(Neuron(I));
	}
 
    /*!
     * we fill our connection map the following way :
     * 
     * each neuron should recieve a certain number of connection from
     * excitatory(Ce) and inhibitory(Ci) neurons.
     * Our map telling us for a neuron which are its POST synaptic
     * neurons we have to place randomly each neuron in a way that it 
     * occure the right amount of time in our map
     */
    for (size_t i(0); i<N; ++i)
    {
		/*!
		 * selection of the exitatory connection:
		 * 
		 * we assign it randomly to Ce excitatory neurons (other than 
		 * himself)
		 */
		for (int E(0); E < Ce; ++E) 
		{
			unsigned int r(0);
	
			static random_device rd; 
			static mt19937 gen(rd());
			static uniform_int_distribution<> dis(0,Ne-1);

			do
			{
				r = dis(gen);
			}while(r == i);
			
			connectionMap_[r].push_back(i);
		}
		/*!
		 * selection of the inhibitory connection:
		 * 
		 * we assign it randomly to Ci inhibitory neurons (other than 
		 * himself)
		 */
		for (int I(0); I < Ci; ++I) 
		{
			unsigned int r(0);
	
			static random_device rd; 
			static mt19937 gen(rd());
			static uniform_int_distribution<> dis(Ne,N-1);

			do
			{
				r = dis(gen);
			}while(r == i);
			
			connectionMap_[r].push_back(i);
		}	
	}
}

Network::~Network()
{
	neurons_.clear();
	connectionMap_.clear();
}

	//////////////////////////////
	//                          //
	//			Getters			//
	//                          //
	//////////////////////////////
	
vector<Neuron> Network::getNeurons()
{
	return neurons_;
}	

vector< vector<int> > Network::getConnectionMap()
{
	return connectionMap_;
}

	//////////////////////////////
	//                          //
	//			Setters			//
	//                          //
	//////////////////////////////
	
void Network::setManualConnection (unsigned int pre, unsigned int post)
{
	if((pre>=N) or (post>=N))
	{
		cerr << "ERROR: manual connection out of range" << endl;
		assert(pre>=N);
		assert(post>=N);
	}
	else
	{
		connectionMap_[pre].push_back(post);
		
	}
}

	//////////////////////////////
	//                          //
	//			Display			//
	//                          //
	//////////////////////////////

void Network::displayNeurons()
{
	cout << "---Neurons---" << endl << endl;
	
	for (size_t i(0); i<N; ++i)
	{
		cout << "N" << i << endl;
	}
		
	cout << endl << endl;
}

void Network::displayConnectionMap()
{
	cout << "---Connection Map---" << endl << endl;
	cout << "   =========================================" << endl;
	for (size_t i(0); i<N; ++i)
	{
		cout << "N" << i << "	";
		for (size_t j(0); j<connectionMap_[i].size(); ++j)
		{
			cout << connectionMap_[i][j] << " ";
		}
		cout << endl;
		cout << "   -----------------------------------------" << endl;
	}
	cout << "   =========================================" << endl;
	cout << endl << endl;
}

void Network::displaySpikeTimes()
{
	cout << endl << endl << "---spikes---" << endl << endl;
	
	for (size_t i(0); i<N; ++i)
	{
		if(neurons_[i].getNumberOfSpike() != 0)
		{
			cout << endl << "---N"<< i <<"---" << endl << neurons_[i].getNumberOfSpike() << " spikes occured at times: " << endl;
			for(size_t j = 0; j < neurons_[i].getSpikeTimes().size(); ++j)
			{
				cout << "t = " << (neurons_[i].getSpikeTimes()[j])/10 << "ms" << endl;
			}
			cout << endl << endl;
		}
	}
}

void Network::displaySimulation()
{
	displayNeurons();
	displayConnectionMap();
	displaySpikeTimes();
}

	//////////////////////////////
	//                          //
	//			Print			//
	//                          //
	//////////////////////////////
	
void Network::printSpikeTimes()
{
	ofstream data;
	data.open("data_neuro.txt");
	
	if(data.fail())
	{
		cerr << "Error while opening the file" << endl;
		assert(data.fail());
	}
	else
	{
		for(int i(0); i<N; ++i)
		{
			for(size_t j(0); j<neurons_[i].getSpikeTimes().size(); ++j)
			{
				data << (neurons_[i].getSpikeTimes()[j])/100 << "\t" << i << "\n";
			}
		}
	}
}	

	//////////////////////////////
	//                          //
	//		  Simulation		//
	//                          //
	//////////////////////////////

void Network::runSimulation(unsigned int t_stop)
{		
		while(netClock_ < t_stop)
		{
			
			update();
		
			++netClock_;
		}
}

void Network::update()
{
	for (size_t i(0); i<N; ++i)
	{
		//check for each neuron if it spiked during this update
		if(neurons_[i].update(0.0, true))
		{
			/*
			 * if yes we transmit the corresponding electrical imput
			 * (Je = 0.1 if the neuron is excitatory, Ji =-0.5 if it is
			 * inhibitory) to all its post synaptic neurons
			 */
			for(size_t j(0); j<connectionMap_[i].size(); ++j)
			{
				int post = connectionMap_[i][j]; 

				if(neurons_[i].isExcitatory())
				{
					/*
					 * the electrical imput is written in the buffer of
					 * the post synaptic neuron with a delay D=15ms
					 */
					neurons_[post].setBufferAt(netClock_+D, Je);
				}
				else
				{
					neurons_[post].setBufferAt(netClock_+D, Ji);
				}
			}
		}
	}
}







