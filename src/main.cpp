#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Neuron.hpp"
#include "Constants.hpp"
#include "Simulation.hpp"


using namespace std;


bool Sim();
void createGraph();

int main (){

if (Sim()) {
	createGraph(); }
	
	
 return 0;
}



bool Sim() {
	cout << "Simulation of the Brunel network. The simulation is considered over a period of 1000ms and the network contains 12500 neurons " << endl;
	cout << " Wich simulation would you like to run ? You can choose between A, B, C or D with respective parameters : " ;
	cout << " (3,2), (6,4), (5,2) and (4.5, 0.9)  for the connection ratio and eta (in that order)" << endl; 
	char answer;
	cin >> answer ;
	bool retour(true);
	
	switch (answer) {
		case 'A' : 
			{Simulation simA(3,2);
			simA.RunSimulation();
			simA.writeSpikeInFile("spikes.txt");}
			break;
		case 'B' :
			{Simulation simB(6,4);
			simB.RunSimulation();
			simB.writeSpikeInFile("spikes.txt");}
			break; 
		case 'C' : 
			{Simulation simC(5,2);
			simC.RunSimulation();
			simC.writeSpikeInFile("spikes.txt");}
			break;
		case 'D' : 
			{Simulation simD(4.5,0.9);
			simD.RunSimulation();
			simD.writeSpikeInFile("spikes.txt"); }
			break;
		default : 
			cout << "wrong entry :( " << endl;
			retour = false;
	
		}
	
		return retour; 
}

void createGraph() {
	cout << "Graph is beeing created " << endl; 
	system ("python ../src/pyscript.py");
}
	
	
	
	
