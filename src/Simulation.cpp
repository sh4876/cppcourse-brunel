#include "Simulation.hpp"

#include "Neuron.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

/**Constructor
 * @param total Number of neurone (NB_Neurones as default value)
 */
Simulation::Simulation( double weight_connection_ratio,  double Eta, unsigned int NbNeurons, unsigned int EndSimulation):
	 weight_connection_ratio_(weight_connection_ratio), Eta_(Eta), NbNeurons_(NbNeurons), EndSimulation_(EndSimulation/h)
{
	NbExcitatory_ = NbNeurons_*(1-NEURON_RATIO);
	assert(NbExcitatory_>0);
	NbInhibitory_ = NbNeurons_*NEURON_RATIO;
	assert(NbInhibitory_>0);
	
	Ce_ = NbExcitatory_*CONNECTION_RATIO; //!< CONNECTIONS_FROM_EXCITATORY
	assert(Ce_>0);
	Ci_ = NbInhibitory_*CONNECTION_RATIO; //!< CONNECTIONS_FROM_INHIBITORY
	assert(Ci_>0);
	
    CreateExcitatory();
    CreateInhibitory();
}


Simulation::~Simulation(){
	 for (size_t i(0); i < Neurone.size() ; ++i ) {
		delete Neurone[i];
	 }
	 Neurone.clear();
}      

 /**RunSimulation
  * makes the connections between the neurones of the network
  * updates until the end of the simulation
  * @see main
  */
void Simulation::RunSimulation() {
	ConnectNetwork();
	UpdateSimulation();
}



/**UpdateSimulation
 * 1)check if the table of neurone is not empty
 * 2)updates every neuron until the time of the simulation reaches its limit.
 * 3)time of simulation incremented once each neuron has been updated once
 * @param step time at wich the simulation must end
 * @see RunSimulation
 */
void Simulation::UpdateSimulation () {
    assert(! (Neurone.empty())); 
    
    unsigned int globalClock(0);
    while (globalClock < EndSimulation_) {
		
		for( size_t i(0); i<Neurone.size(); ++i) {
				 
			if (Neurone[i] == nullptr) {cerr << "pointeur nul" << flush;}
               
			Neurone[i]->update();
        } ++globalClock; 
   }
}


/**CreateConnection
 * neuron of index2 becomes a target of neuron of index1
 * @param indexes of two neurones in the table
 * @see ConnectNetwork
 */
void Simulation::CreateConnection(const size_t& index1, const size_t& index2) {
    assert(index1<Neurone.size());
    assert(index2<Neurone.size());
    Neurone[index1]->addTarget(Neurone[index2]);
 }

/**ConnectNetwork
 * generates the random connection between the neurons of the table
 * @see RunSimulation
 */
 void Simulation::ConnectNetwork() {

         default_random_engine sv;
         mt19937 random_list (sv());
         uniform_int_distribution<int> excitatory(0, NbExcitatory_-1);
         uniform_int_distribution<int> inhibitory(NbExcitatory_, NbNeurons_-1);
         for (size_t target(0); target < NbNeurons_; ++target) {
			
                for (size_t i(0); i < Ce_; ++i) {
					CreateConnection(excitatory(random_list),target);
                }
                for (size_t i(0); i < Ci_; ++i) {
					CreateConnection(inhibitory(random_list), target);
                }
        }
}


/**CreateExcitatory
 * generates a certain amount of excitatory neurones with external current
 * @param number of excitatory numbers whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateExcitatory () {
    for (unsigned int i(0); i < NbExcitatory_ ; ++i) {
        Neurone.push_back(new Neuron(false, Eta_, weight_connection_ratio_ ));
    }
}

/**CreateInhibitory
 * generates a certain amount of inhibitory neurones
 * @param number of inhibitory neurones whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateInhibitory () {
    for (unsigned int i(0); i < NbInhibitory_ ; ++i) {
        Neurone.push_back(new Neuron(true, Eta_, weight_connection_ratio_ ));
    }
}

                ///methods used in unittests

/**Connected
 * @param indexes of two neurones in the table
 * @see used in unittests
 * @return if neuron of index2 is a target of neuron of index1
 */
bool Simulation::Connected (const size_t& index1, const size_t& index2) const {
	assert(index1<Neurone.size());
    assert(index2<Neurone.size());
    for (const auto& target : Neurone[index1]->getTargets() ) {
        if (Neurone[index2] == target) {return true;}
    }
    return false;
}

/**get_NbNeurones
 * @see used in unittests
 * @return number of neurones in the table
 */
unsigned int Simulation::get_NbNeurones () const {
    return Neurone.size();
}

/**getNeuronePotential
 * @param index of the neurone of which we want to know the potential
 * @see used in unittests
 * @return potential of given neuron
 */
double Simulation::getNeuronePotential (const size_t& index) const {
    return Neurone[index]->getPotential(); 
}

/**write the time (in ms) at wich each neuron had a spike in an external file
 * @param the external file 
 * @see in the main to plot the graphs 
 */
void Simulation::writeSpikeInFile( const string& file) {
	ofstream out(file);
	
	if (out.fail()) {
		cerr << "impossible to write in file" << file << flush;
	
	} else {
		for ( size_t i(0); i< Neurone.size(); ++i) {
			//assert((Neurone[i]-> getTimeSpike()).size() > 0 ); //can t be written beacause of case D.
			for ( const auto& spike : Neurone[i]->getTimeSpike()) {
				out << spike*h << '\t' << i << '\n'; 
				}
		}
	}
	out.close();
}

/**allows to silence the background noise the neuron additionally receive at each update
 * @see unused in the current version
 */
void Simulation::shutExternalNoise() {	
	for ( auto& n : Neurone ) {
		n->setExternalNoise( false);
	}
}

/**gets the number of incoming connection (that should be equal for each neuron)
 * @param index of the neuron of which we want to know the nb of incomming connections 
 * @see only used in unittests
 */
unsigned int Simulation::IncomingConnections(const size_t& index) const {	
	unsigned int targeted(0);
	assert (index< NbNeurons_);
	for (size_t i(0); i < NbNeurons_ ; ++i ) {
			for (const auto& target : Neurone[i]->getTargets()) {
			if (Neurone[index] == target) {++targeted;} }
		}
	return targeted; 
}
