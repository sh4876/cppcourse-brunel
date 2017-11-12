#include "Neuron.hpp"
#include <iostream>
#include <random>

#include "Constants.hpp"

/**Constructor
 * @param Nature of the neurone (inhibitoty or excitatory), external current, 
 * external firing rate over rate to reach threshold, weight of inhibitory input over excitatory
 * 
 * external noise is set to true as default but can be change by a setter (usefull in unittests)
 * initialise all the cases of the buffer with the value of zero
 */
Neuron::Neuron(bool Inhib, double Eta , double weight_connection_ratio, double Iexterne) : isInhibitory_(Inhib ), Eta_(Eta) , 
weight_connection_ratio_ (weight_connection_ratio), I_ext_(Iexterne) 
{     
		potential_ = 0.0; 
        local_clock_=0;
		external_noise_=true;
		V_ext_ =Eta* threshold/(Je*tau)*h;
        for (size_t i(0); i < Buffersize; ++i) {buffer_.push_back(0.0);}
}

/**destructor
 * @see in the destructor of Simulation
 */
Neuron::~Neuron(){}
	
/**update of one steptime
 * 1) if the neurone isn t refractory, it will update its potential.
 * 2) if we allow the neurone to receive background noise from the rest of
 * the brain, then an additionnal potential must be taken into account.
 * 3) if the neuron spikes, the time of the spike is saved and the potential 
 * is reset to Vr as defined in the constants file. The if the neuron has targets 
 * (e.g. it is part of a Network) then it sends current to all of them 
 * 4) erasing the content of the corresponding case of the ring buffer
 * 5) incrementating the local clock at the end of update 
 * @see in Simulation.update
 * @return true if neuron had a spike
 */
bool Neuron::update ( ) {

	   bool hadSpike(false);

       if (!isRefractory(local_clock_)) {
		
			potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%(Buffersize)] + noise()  ; //! C1 and C2 defined in Constants.hpp
		
			if (potential_ >= threshold) {
				timeSpike_.push_back(local_clock_);
				potential_ = Vr;  //! Vr (the reset potential) is defined in Constants.hpp
				hadSpike = true;
				
				if (targets.size() >=1 ) {
	
						for (auto& t : targets) {
						
								t-> writeinBuffer(local_clock_, isInhibitory_);
						}
				}
			}
				
				
		} 
		
		buffer_[(local_clock_)%(Buffersize)] = 0; 
        ++local_clock_;
      
        return hadSpike;
} 
		

/**calculates the background noise coming from the rest of the brain if we allow background noise
 * the value of the noise corresponds to the result of the poisson distribution multiply by the weight of excitatory spikes   
 * @see in Neuron.update
 * @return value of the noise generated
 */
double Neuron::noise () const {
	double noisyPotential(0);
       if (external_noise_) { 
            static random_device rd;
            static mt19937 generator(rd());
            static poisson_distribution<int> pois(V_ext_);
  
            noisyPotential = Je*pois(generator); //! Je defined in Constants.hpp
            }
    return noisyPotential; 
}

/**writeinBuffer
 * adds current at a certain index in the ring buffer for it to be
 * added/substracted to the potential later in the simulation.
 * if the neuron sending the input is inhib the current will be substracted 
 * @param time at wich the neuron sending the input had a spike, if the neuron sending the signal is inhibitory
 * @see in update
 */
void Neuron::writeinBuffer(const int& time, bool inhib){
        size_t index (0);
        index = (time + buffer_.size()-1)%buffer_.size();
        if (inhib) {buffer_[index] -= Je*WEIGHT_CONNECTION_RATIO;
			} else { buffer_[index] += Je; }
}

/**isRefractory
 * if the delay since the last spike hasnt expired the neuron cant update its potential
 * @param given time (corresponding to localclock)
 * @see update
 * @return if neurone is indeed refractory
 */
bool Neuron::isRefractory(const int& time) const {
	
        if (timeSpike_.size() < 1 )  {
			
				return false;   
		}else { 
		
			return (timeSpike_.back()+STEP_tau_rp > time);
		}
}

/**addTarget, adds a target to the vector of targets, when neuron spikes, it will send currents to its targets 
 * @param pointer of the target neuron
 * @see in CreateConnection in Simulation
 */
void Neuron::addTarget (Neuron* n){
	targets.push_back(n);
}	

	//// -------------------getters-------------------//// 

/**return true if neuron is inhibitory
 * @see in writeinBuffer
 * @return if inhibitory
 */
bool Neuron::isInhib() const {
        return isInhibitory_;
}


/**getPotential
 * @see in method storePotential and in unitests
 * @return value of the potential
 */
double Neuron::getPotential() const {
        return potential_;
}

/**getTimeSpike
 * @see in method storePotential, in method isRefractory
 * @return time of last spike
 */
vector <int> Neuron::getTimeSpike() const {
        return timeSpike_;
}
        
/**getTargets()
 * @param true if we want the neuron to receive random inputs from rest of the brain
 * @see in updateSimulation (to send current to the targets when the neuron is spiking)
 * @see used in unittests and was very usefull to know if the neurons had the right number of incomming connection
 */
vector<Neuron*> Neuron::getTargets() const {
	return targets;
}

	//// -------------------setters-------------------//// 
	
/**set_Iext
 * @param external current
 * @see used in unittests
 */
void Neuron::set_Iext(const double& Iext) {
        I_ext_ = Iext;
}

/**setExternalNoise
 * @param true if we want the neuron to receive random inputs from rest of the brain
 * @see used in unitests (to have predictable results)
 * @see in Simulation.shutExternalNoise() for the same reason
 */
void Neuron::setExternalNoise(const bool& YesOrNo) {
     external_noise_= YesOrNo;
}


