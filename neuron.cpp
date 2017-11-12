#include "neuron.hpp"

#include <iostream>
#include <cmath>
#include <random>
//#include <assert>

using namespace std;

	//////////////////////////////
	//                          //
	// constructor & destructor //
	//                          //
	//////////////////////////////
	
Neuron::Neuron(neuron_type type) 
	  :V_(V_reset),
	   refractory_(false),
	   neuroClock_(0),
	   buffer_(D+1, 0.0),
	   type_(type)
{}

Neuron::~Neuron()
{
	buffer_.clear();
	spikeTimes_.clear();
}

	//////////////////////////////
	//                          //
	//			Getters			//
	//                          //
	//////////////////////////////
	
double Neuron::getMembranePotential() const
{
	return V_;
}

size_t Neuron::getNumberOfSpike() const
{
	return spikeTimes_.size();
}

vector<double> Neuron::getSpikeTimes() const
{
	return spikeTimes_;
}

int Neuron::getBufferPos (int t) const
{
	int i = t % (D+1);
	return i;
}

bool Neuron::isExcitatory()
{
	if(type_ == E)
	{
		return true;
	}
	else
	{
		return false;
	}
}

	//////////////////////////////
	//                          //
	//			Setters			//
	//                          //
	//////////////////////////////
	
void Neuron::setMembranePotential(double newV)
{
	V_ = newV;
}

	//////////////////////////////
	//                          //
	//		  Simulation		//
	//                          //
	//////////////////////////////

bool Neuron::update(double Iext, bool randomSpike) 
{		
	if(refractory_)
	{
		/*
		 * during this refractory period the neuron is unable to modify
		 * its membranne potential: it stays at 0 during 2ms
		 */
		
		//assert(!spikeTimes_.empty());
		
		if (!spikeTimes_.empty() and neuroClock_>= spikeTimes_.back()+tau_rp)
		{
			refractory_ = false;
		}
	}
	else if(!refractory_ and V_ < V_tresh)
	{
		/*
		 * we create a variable J that contain the information comming 
		 * from the buffer plus the random noise created with poisson
		 * distribution (if enabled)
		 */
		double J(0.0);
		if(randomSpike)
		{
			double lambda = V_ext*Ce;
			
			static random_device rd;
			static mt19937 gen(rd());
			static poisson_distribution<int> d(lambda);
	
			J = d(gen)*Je + buffer_[getBufferPos(neuroClock_)];
		}
		else
		{
			J = buffer_[getBufferPos(neuroClock_)];
		}
		
		depolarisation(Iext, J);
	}
	else if(!refractory_ and V_ >= V_tresh)
	{
		spikeTimes_.push_back(neuroClock_);
	
		V_ = V_reset;
		
		/*
		 * after spiking the neuron enter refractory mode
		 */
		refractory_ = true;	 
		
		/*
		 * the neuron gives a signal telling that he spiked
		 */
		return true;
	}
	/*
	 * the buffer is cleaned directly after its use
	 */
	buffer_[getBufferPos(neuroClock_)] = 0;
	
	++neuroClock_;
	
	return false;
}

void Neuron::depolarisation (double Iext, double J)
{
	double c = exp(-h/tau);
	V_ = V_*c + Iext*R*(1-c) + J; 
}

void Neuron::setBufferAt(int t, double input)
{	
	int i = getBufferPos(t);
	buffer_[i] += input;
}


