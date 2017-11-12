#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "Constants.hpp"
#include <string>

using namespace std;

class Neuron; 


class Simulation {

        private:

double weight_connection_ratio_;			//!< inhibitory over excitatory;
double Eta_;								//!<  external firing rate over rate to reach threshold

unsigned int NbNeurons_; 						//!< total number of neurons 
unsigned int NbExcitatory_;						//!< total number of excitatory neurons 
unsigned int NbInhibitory_;						//!< total number of inhibitory neurons 

unsigned int EndSimulation_; 					//!< time of simulation end in ms


unsigned int Ce_;								//!< number of connections received from excitatory neurons (and for each neuron)
unsigned int Ci_;								//!< number of connections received from inhibitory neurons (and for each neuron)

vector<Neuron*> Neurone;                		//!< saves all the neuron involved in the simulation

void CreateExcitatory () ;						//!< creates all excitatory neurons 
void CreateInhibitory () ;						//!< creates all excitatory neurons


        public :
Simulation(double weight_connection_ratio, double Eta_, unsigned int NbNeurons = NB_NEURONS,  
	unsigned int EndSimulation= END_SIMULATION );          //!< constuctor
	
 ~Simulation();      							//!<  destructor
void RunSimulation();                           //!< runs the simulation
void UpdateSimulation ();       				//!< updates simulation from globalClock until Endsimulation is reached 
void CreateConnection(const size_t& index1, const size_t& index2); //!< creates connections between two neurones
void ConnectNetwork() ; 						//!< randomly connects the whole network
bool Connected (const size_t& index1, const size_t& index2) const; //!< attest if index2 is a target of index1 
unsigned int get_NbNeurones () const ; 			//!< gets the number of neuron in the simulation
double getNeuronePotential(const size_t& index) const; //!< gets the potential of a neuron
void writeSpikeInFile( const string& file);		//!< writes the spike at wich the spikes occur in an external file 
void shutExternalNoise(); 						//!< sets the backgroud noise off for each neuron 
unsigned int IncomingConnections(const size_t& index) const ; //!< only used in unittests     
};

#endif
