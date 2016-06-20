#pragma once
#include "../../NEATServer/GenomeView.h"

#include <functional>
#include <algorithm>
#include <stdlib.h>   
#include <time.h> 
#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

 class NeuralNetwork;
 class Pool;
 class Species;
 class Genome;
 class Network;
 class Gene;
 class Neuron;

namespace GlobalVariables {
	static int Population = 300;

	static int NumInputs = 4 + 1;
	static int NumOutputs = 3;
	static int MaxNodes = 1000;

	static double MutateConnectionsChance = 0.25;
	static double PerturbChance = 0.90;
	static double CrossoverChance = 0.75; // set to 1 if you want all new organisms in new generation to be bred, rather than some to be cloned
	static double LinkMutationChance = 2.0;
	static double BiasMutationChance = 0.4;
	static double NodeMutationChance = 0.5;
	static double EnableMutationChance = 0.2;
	static double DisableMutationChance = 0.4;
	static double StepSize = 0.1;

	static double SurvivalThreshold = 0.2;

	static int StaleSpecies = 15;
	static int TimeoutConstant = 20;

	static double CompatibilityThreshold = 3.0;
	static double C1 = 2.0;
	static double C2 = 2.0;
	static double C3 = 1.0;

	//static double SigmoidBias = 0;
};

class NeuralNetwork {
public:
	NeuralNetwork();
	void runPlayerForm();
	void runNeuralNetwork();
	void runGenome(string);
	void initializePool();
	void initializeRun();
	shared_ptr<Genome> createBasicGenome();
	void evaluateCurrent();
	void evaluateGenome(shared_ptr<Genome>);
	bool fitnessAlreadyMeasured();
	void nextGenome();
	void saveGenome();
	shared_ptr<Genome> loadGenome(string);
	void displayGenome(shared_ptr<Genome>);
	void updateCellValues(shared_ptr<Genome>);
	void clearDisplay();
	void updateLabels();
	void createLabels();
				
	double getCharacterX(); // character x position
	double getCharacterY(); // character y position
	double getEnemy1(); // enemy1 x position
	double getEnemy2(); // enemy2 x position
private:

	shared_ptr <Pool> pool;

	int rightmost;
	int timeout;
};

class Pool {
public:
	Pool();
	vector<shared_ptr<Species>> getSpecies();
	int getCurrentSpecies();
	void setCurrentSpecies(int);
	int getCurrentGenome();
	void setCurrentGenome(int);
	int getCurrentFrame();
	void setCurrentFrame(int);
	double getMaxFitness();
	void setMaxFitness(double);
	double getCurrentMaxFitness();
	void setCurrentMaxFitness(double);
	int getGeneration();
	int getMaxFitnessSpecies();
	void setMaxFitnessSpecies(int);
	int getMaxFitnessGenome();
	void setMaxFitnessGenome(int);
	bool getSaveGenome();
	void setSaveGenome(bool);

	void addToSpecies(shared_ptr<Genome>);
	bool isSameSpecies(shared_ptr<Genome>, shared_ptr<Genome>);
	int numExcessGenes(shared_ptr<Genome>, shared_ptr<Genome>);
	int numDisjointGenes(shared_ptr<Genome>, shared_ptr<Genome>);
	int numDisjointExcessGenes(shared_ptr<Genome>, shared_ptr<Genome>);
	double weightDifferences(shared_ptr<Genome>, shared_ptr<Genome>);
	int newInnovation();
	void newGeneration();
	void cullSpecies(bool);
	void cullWeakGenomes();
	void rankGlobally();
	void removeStaleSpecies();
	void removeWeakSpecies();
	void removeWeakSpecies2();
	double totalAdjustedFitness();
	double totalAverageFitness();

private:
	vector<shared_ptr<Species>> species;
	int generation;
	int innovation;
	int currentSpecies;
	int currentGenome;
	int currentFrame; 
	double maxFitness;
	double currentMaxFitness;
	int maxFitnessSpecies;
	int maxFitnessGenome;
	bool saveGenome;
};

class Species {
public:
	Species();
	vector<shared_ptr<Genome>> &getGenome();
	double getTotalAdjustedFitness();
	double getTopFitness();
	void setTopFitness(double);
	int getStaleness();
	void setStaleness(int);
	double getAverageFitness();

	void sortGenomesAscending(int, int);
	void sortGenomesDescending(int, int);
	void calculateAdjustedFitness();	
	void calculateAverageFitness();
	shared_ptr<Genome> breedChild();
	shared_ptr<Genome> crossover(shared_ptr<Genome>, shared_ptr<Genome>);
private:
	vector<shared_ptr<Genome>> genomes;

	double topFitness;
	int staleness;
	double totalAdjustedFitness;	
	double averageFitness;
};

class Genome {
public:
	Genome();
	int getMaxNeuron();
	void setMaxNeuron(int);
	vector<shared_ptr<Gene>> &getGenes();
	shared_ptr<Pool> getParentPool();
	void setParentPool(shared_ptr<Pool>);
	double getFitness();
	void setFitness(double);
	double getAdjustedFitness();
	void setAdjustedFitness(double);
	int getGlobalRank();
	void setGlobalRank(int);
	shared_ptr<Network> getNetwork();

	double getConnectionsMR();
	void setConnectionsMR(double);
	double getLinkMR();
	void setLinkMR(double);
	double getBiasMR();
	void setBiasMR(double);
	double getNodeMR();
	void setNodeMR(double);
	double getEnableMR();
	void setEnableMR(double);
	double getDisableMR();
	void setDisableMR(double);
	double getStepMR();
	void setStepMR(double);

	void createBasicGenes();
	void mutate();
	void randomizeRates();
	void pointMutate();
	void linkMutate(bool);
	void nodeMutate();
	void enableDisableMutate(bool);
	int randomNeuron(bool);
	bool containsLink(shared_ptr<Gene>);
	void generateNetwork();
	void sortGenes(int, int);
	vector<bool> evaluateNetwork(vector<double>);
	double sigmoid(double);
	shared_ptr<Genome> copyGenome();
private:
	vector<shared_ptr<Gene>> genes;

	shared_ptr<Network> network;
	shared_ptr<Pool> parentPool;

	double fitness;
	double adjustedFitness;
	int maxNeuron;
	int globalRank;

	// mutation rates
	double connectionsMR;
	double linkMR;
	double biasMR;
	double nodeMR;
	double enableMR;
	double disableMR;
	double stepMR;
};

class Network {
public:
	Network();
	vector<shared_ptr<Neuron>> &getNeurons();
private:
	vector<shared_ptr<Neuron>> neurons;
};

class Neuron { // node gene
public:
	Neuron();
	vector<shared_ptr<Gene>> &getIncomingGenes();
	double getValue();
	void setValue(double);
private:
	vector<shared_ptr<Gene>> incomingGenes;
	double value;
};

class Gene { // connection gene
public:
	Gene();
	int getInnovNum();
	void setInnovNum(int);
	double getWeight();
	void setWeight(double);
	bool getEnabled();
	void setEnabled(bool);
	int getInNode();
	void setInNode(int);
	int getOutNode();
	void setOutNode(int);

	shared_ptr<Gene> copyGene();
private:
	int inNode;
	int outNode;
	double weight;
	bool isEnabled;
	int innovationNum;
};
