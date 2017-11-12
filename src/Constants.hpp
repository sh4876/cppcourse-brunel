#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <cmath>
using namespace std;

const int NB_NEURONS(12500); 			//!<  number of neurons 				(DEFAULT)
const double END_SIMULATION(1000); 		//!< End time of simulation in ms 		(DEFAULT)

const int WEIGHT_CONNECTION_RATIO(5);	//!< inhibitory over excitatory  		(DEFAULT)
const int ETA(2) ; 						//!<  external firing rate over rate to reach threshold   (DEFAULT)

const double NEURON_RATIO(0.2); 		//!<  Inhibitory over Excitatory 	(UNCHANGED)
const double CONNECTION_RATIO(0.1);		//!< connection ratio 				(UNCHANGED)

const double C_ext_ (NB_NEURONS*CONNECTION_RATIO);
/// values that can t be changed inside of the simulation :

const double h(0.1); 					//!< time interval in ms 			(UNCHANGED)

const double tau(20); 					//!<  membrane time constant of an excitatory neurone in ms (UNCHANGED)
const double Vr(0.0); 					//!<  reset potential in mV 		(UNCHANGED)
const double tau_rp(2); 				//!< refractory period in ms 		(UNCHANGED)
const double threshold(20); 			//!<  threshold potential in mV 	(UNCHANGED)
const double R(20); 					//!<  resistance in GOh 			(UNCHANGED)
const double DELAY(1.5); 					//!<  the delay in ms 				(UNCHANGED)


const double Je(0.1); 					//!< transmitted value of excitatory spike (weight)  (UNCHANGED)
const double C1(exp(-h/tau));			//!< (UNCHANGED)
const double C2(R*(1-C1));				//!< (UNCHANGED)

/// conversion in timesteps;

const unsigned int STEP_END_SIMULATION(END_SIMULATION/h);
const int STEP_tau=tau/h;				//!< tau in steps 					(UNCHANGED)
const int STEP_tau_rp=tau_rp/h;			//!< refractory period in steps 	(UNCHANGED)
const int STEP_D=DELAY/h;					//!< delay in steps 				(UNCHANGED)
const int Buffersize(STEP_D+1);			//!<  size of ring buffer 			(UNCHANGED)


#endif


