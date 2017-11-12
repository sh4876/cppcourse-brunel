Aim: reproduce the figures of the Brunel network. This Network  

How I structured my files : 

-> Neuron.hpp
-> Neuron.cpp
This class takes care of the "life" of one neuron. It doesn t need to be integrated in a network altough the case where it is connected to other neurons is taken into account.
We consider two different kinds of neuron: inhibitory and excitatory ones. Since the comportment between the two is quite similar, spliting this class in two is more constraining than it is helpful. 

-> Simulation.hpp
-> Simulation.cpp
This class plays the role of both a simulation and a network. In fact the class has an attribut were the neurons (making the network) are stored. The class simulation takes care of initialising all the neurons, connecting them and updating them all.

-> Constants.hpp
Contains values used both in the class Neuron and Simulation.
All the values present in this file are defined as const.
The majority of them don't need to be changed to plot the figures of the brunel network. The only values that could be usefull to change are the values corresponding to the number of neuron, the lenght of the simulation, the weight connection ratio and the external firing rate over rate to reach threshold. These are default values used in the simulation but they can be redefined by the user when initializing a simulation. 
   

-> main.cpp
where Simulations or neurons can be created.

Unittests.cpp tests parts of the program (detailed description below).

Parameters that can/must be set by the user:
in the main.cpp the user can change the folowing parameters of the class simulation: 

1) weight_connection_ratio 	//<! ratio of the weight of the input sent by the neurons (inhibitory over excitatory)
2) Eta_  			//!< external firing rate over rate to reach threshold

3) NbNeurons   		//!< number of neurons 
4) EndSimulation 	//!< time lenght of the simulation
5) ExternalCurrent	//!< external current given to the neurons

Important : 
1) and 2) must be defined !
3), 4) and 5) have default values as defined in the constants
5) coul d have be left out of the constructor in simulation since the neurons each have a default value (= 0.0) in their constructor but i prefered to overwright this default value to avoid having unknown values in the simulation. 

Running the Simulation: 
commad lines must be copied in a terminal in the build repository containing the executables in the following order :
Cmake ../ 
make 
./neurone


Running the tests:

instead of the command line " ./neurone " written above, you should enter ./neurone_unittest 

There are 10 tests in total, the descriptions are listed below:
Note: for the results of the simulation to be predicatable, the background noise is shut of. 

1) TEST(OneNeurone, OneUpdate)
Checks if the potential is correctly updated after one step when external current is provided.

2) TEST(OneNeurone, Nocurrent)
Checks if the potential equals zero after 3 steps of time (the number 3 was chosen arbitrary) when no external current is provided. 

3) TEST(OneNeurone, TwoUpdates)
Checks if the potential is correctly updated after two steps when external current is provided.

4) TEST(SimulationwithTwoNeurones, numberOfNeurones)
Checks if the simulation initialises the wright number of neurons.
Since the total number of neurons is the sum of the Excitatory and inhibitory neurons, and these are calculated with the ratio (4:1) it could be that the number of Excitatory and Inhibitory resulting is not an integer hence we would have lost neurons in the process.

5) TEST(SimulationwithTwoNeurones, ConnectionToAnother)
Checks if the method create connection works well. Note that neurons can be connected to each other more than once but that this test doesn t take the number of connections into account.

6) TEST(OneNeurones, ResetPotential)
Cheks if the potential is reset to zero after spiking

7) TEST(OneNeuron, FirstSpikeTime)
Cheks if one neuron isolated receiving external current spikes at the right time

8) TEST(TwoNeurones, ExcitatorySpikeTransmission)
Check if a spiking excitatory neuron writes at the right time in the buffer of a target neuron and if the target reads the buffer correctly (receives the potential of spiking neuron after a delay ).

9) TEST(TwoNeurones, InhibitorySpikeTransmission)
Same as above except the spiking neuron is inhibitory thus the currents it sends to its target is negative.

10) TEST(SimulationwithlotsofNeurons, numberOfIncomingConnections)
Checks if the number of incoming connections each neuron receives is the one expected. (Each neuron should have the same predictable number of incoming connection but not necessarily the same number of target since these are randomly distributed). 



