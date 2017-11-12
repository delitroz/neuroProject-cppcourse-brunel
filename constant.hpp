#ifndef constant_HPP
#define constant_HPP

//////////////////////////////
//                          //
//		Time constants		//
//                          //
//////////////////////////////

	/*
	 *timstep
	 *choosen to be 1 to simplify the calculations, its physical value
	 *is however 0.1ms so every constant in the differential equation of 
	 *the membranne potential have to be modified accordingly
	 */
	static const double h(1);
		
	//time constant (20 ms)
	static const double tau(200);

	//refractory period (20 ms)
	static const double tau_rp(20);

	//transmission delay (15 ms)
	static const int D(15);

//////////////////////////////
//                          //
//	  Potential constants	//
//                          //
//////////////////////////////

	//treshold memrane electrical potential of the neurone [mvolt]
	static const double V_tresh(20);

	//standard memrane electrical potential of the neurone [mvolt]
	static const double V_reset(0);

	/*
	 *electrical capacitance [farad]
	 *modified to have the same value of tau/C with a tau=200 
	 */
	static const double C(10);

	//electric resistance of the membrane (=tau/C) 
	static const double R (20) ;

	//amplitude transmitted after a spike from an excitatory neuron
	static const double Je(0.1);

	//amplitude transmitted after a spike from an inhibitory neuron
	static const double Ji(-0.5);

	//ratio Ji/Je
	static const int g(5);

//////////////////////////////
//                          //
//		Neuron constants	//
//                          //
//////////////////////////////
	
	/*
	 *total number of neurons in a network
	 *standard N=12500
	 *minimal configuration N=50
	 */ 
	static const int N(12500);

	//number of excitatory neurons in a network
	static const int Ne = 0.8*N;

	//number of inhibitory neurons in a network
	static const int Ni = 0.2*N;

//////////////////////////////
//                          //
//	 Connection constants	//
//                          //
//////////////////////////////
	
	//total number of connection for each neuron
	static const int Ctot = 0.1*N;

	//number of connection with a excitatory neuron for each neuron
	static const int Ce = 0.1*Ne;

	//number of connection with a inhibitory neuron for each neuron
	static const int Ci = 0.1*Ni;

//////////////////////////////
//                          //
//		Random constants	//
//                          //
//////////////////////////////

	//rate of random spiking from external connections
	static const double V_ext = 0.2;

//////////////////////////////
//                          //
//		Neuron types		//
//                          //
//////////////////////////////
	
	//tells which type the neuron is (E:exitatory I:inhibitory)
	enum neuron_type{E,I};

#endif
