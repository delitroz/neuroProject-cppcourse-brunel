#include "gtest/gtest.h"
#include "neuron.hpp"
#include "network.hpp"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

	//////////////////////
	//					//
	//	Neurons Tests	//
	//					//
	//////////////////////

	/*
	 * test if the membrane pototial compute well during an update
	 */
	TEST (NeuronTest, SingleUpdate)
	{
		Neuron n(E);

		double Iext(1.0);

		n.update(Iext, false);
		EXPECT_EQ(20.0*(1-exp(-0.1/20.0)), n.getMembranePotential());
	}

	/*
	 * test if the membrane potential behave correctly after numerous
	 * update
	 * 
	 * with an external current value of 1 the membranne potential
	 * should tend to the treshold potential(=20) withoud reaching it
	 */
	TEST (NeuronTest, MultipleUpdate)
	{
		Neuron n(E);
		
		double Iext(1.0);
		
		for (int i(0); i<2000; ++i)
		{
			n.update(Iext, false);
		}
		EXPECT_LT(n.getMembranePotential(), V_tresh);
	}

	/*
	 * test if the membrane potential decrease as predicted to 0 in
	 * abscence of external current
	 */
	TEST (NeuronTest, PotentialRegression)
	{	
		Neuron n(E);
		
		n.setMembranePotential(10.0);
		
		double Iext(0.0);
			
		for (int i(0); i<2000; ++i)
		{
			n.update(Iext, false);
		}
		//! value close to 0
		EXPECT_LT(n.getMembranePotential(), 0.001);
		//! but not 0
		EXPECT_GT(n.getMembranePotential(), 0);
	}

	/*!
	 * @brief test if in the has the good amount of spikes at the good times
	 * 
	 * with an external current equal to 1.01 we should observe five spikes at
	 * t= 92.4ms 186.9ms 281.4ms 375.9ms and 470.4ms
	 * 
	 */
	TEST (NeuronTest, Spike)
	{		 
		Neuron n(E);
			
		double Iext(1.01);

		for (int i(0); i<5000; ++i)
		{
			n.update(Iext, false);
		}
		EXPECT_EQ(n.getNumberOfSpike(), 5);
		EXPECT_EQ(n.getSpikeTimes()[0]/10, 92.4);
		EXPECT_EQ(n.getSpikeTimes()[1]/10, 186.9);
		EXPECT_EQ(n.getSpikeTimes()[2]/10, 281.4);
		EXPECT_EQ(n.getSpikeTimes()[3]/10, 375.9);
		EXPECT_EQ(n.getSpikeTimes()[4]/10, 470.4);
	}

	//////////////////////
	//					//
	//	Network Tests	//
	//					//
	//////////////////////
	/*
	 * to have results with an axceptable run-time the best is to work
	 * with a minimal configuration by changing the value of N in the 
	 * constant file
	 * the test however run with larger numbers
	 * 
	 * with a number of neuron N=50 we will have:
	 * Ne=40 excitatory neurons
	 * Ni=10 inhibitory neurons
	 * Ctot=5 total connection for each neurons
	 * Ce=4 excitatory connection for each neurons
	 * C1=1 inhibitory connection for each neurons
	 */

	/*
	 * test the actual total number of neuron and the number of 
	 * each type of neurons after the network initialisation
	 */
	TEST (NetworkTest, neuronsNumber)
	{
		Network net;
		
		vector<Neuron> list = net.getNeurons();
		int E(0),
			I(0);
		
		for (size_t i(0); i<list.size(); ++i)
		{
			if(list[i].isExcitatory())
			{
				++E;
			}
			else
			{
				++I;
			}
		}
		
		EXPECT_EQ(list.size(), N);
		EXPECT_EQ(E, Ne);
		EXPECT_EQ(I, Ni);
		
	}

	/*
	 * test the actual total number of connection and the number of
	 * each type of connection for each neurons 
	 */
	TEST (NetworkTest, connectionNumber)
	{	
			
		 
		Network net;
		
		vector<Neuron> list = net.getNeurons();
		vector< vector<int> > map = net.getConnectionMap();
		
		for (int n(0); n<N; ++n)
		{
			int tot(0),
				E(0),
				I(0);
				
			for (int i(0); i<N; ++i)
			{
				for (size_t j(0); j<map[i].size(); ++j)
				{
					if (map[i][j]==n)
					{
						++tot;
						
						if (list[i].isExcitatory())
						{
							++E;
						}
						else
						{
							++I;
						}
					}
				}
			}
		
			EXPECT_EQ(tot ,Ctot);
			EXPECT_EQ(E ,Ce);
			EXPECT_EQ(I ,Ci);
		}
	}

