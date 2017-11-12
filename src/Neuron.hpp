#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"
#include <random>

using namespace std;
typedef vector<double> Buffer;


class Neuron {

        private :
		
	bool isInhibitory_;								//!< true if the neurone is inhibitory, false if excitatory
	double Eta_;									//!< external firing rate over rate to reach threshold
	double weight_connection_ratio_;				//!< inhibitory over excitatory;
	double I_ext_;                                  //!< external current
	
	double potential_;                              //!< membrane potential
	vector<int > timeSpike_;                    	//!< time of each spike
	int local_clock_;                               //!< neuron's local clock
	bool external_noise_;							//!< true if we allowed the neuron to get random inputs from the rest of the brain 
											
	double V_ext_;									//!< external firing rate
	bool isRefractory(const int&) const;			//!< State of neuron (refractory or not)
       
	Buffer buffer_; 								//!< saves inputs of spiking neuron of wich "this" is a target
	vector <Neuron*> targets; 						//!< neurones that get an input in their buffer when the neurones spikes 
	double noise() const ;							//!< calculates the background noise using poisson distribution
	
        public :

	Neuron( bool Inhib, double Eta=ETA, double weight_connection_ratio = WEIGHT_CONNECTION_RATIO,  double I_ext= 0); //!< constructor
	~Neuron();      								//!<  destructor
             
	bool update() ; 								//!< updates the neuron of one step
	void writeinBuffer(const int& time, bool inhib)  ; 		//!< neuron spiking at time (localclock ) sends a signal to every neuron it s connected to
	void addTarget(Neuron* n); 						//!< adds a target to wich the neuron will send current if it s spiking
	
	void set_Iext(const double&) ; 					//!< setter of external current	
	void setExternalNoise(const bool& YesOrNo); 	//!< set to true if we allow the neuron to get random inputs from the rest of the brain 
	
	bool isInhib() const; 							//!< true if the neuron is inhibitory
	double getPotential() const; 					//!< gets the potential of the membrane
	vector <int> getTimeSpike() const;       		//!< saves the time of the spikes 
	vector<Neuron*> getTargets() const;				//!< return the vector containing pointers to all the neurons it should send current to in case of spike
};


#endif
