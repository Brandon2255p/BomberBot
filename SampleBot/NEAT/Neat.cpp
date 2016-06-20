#include "Neat.h"
#include "../json/json.h"
#include <fstream>

NeuralNetwork::NeuralNetwork() {	
	
	//runNeuralNetwork();
}

void NeuralNetwork::runNeuralNetwork() {	
	initializePool();
	
	while (true) {		
		double timeoutBonus;
		double fitness;

		shared_ptr<Species> species = pool->getSpecies()[pool->getCurrentSpecies()];
		shared_ptr<Genome> genome = species->getGenome()[pool->getCurrentGenome()];

		if (pool->getCurrentFrame() == 1) {
			clearDisplay();
			displayGenome(genome);
			updateLabels();
			/**///playerForm->updateDisplay();
		}
		
		// change to %5 ?
		if (pool->getCurrentFrame() % 1 == 0) {
			evaluateCurrent();
		}

		// if changed to %5, the keyboard in evaluateCurrent() must be set again here

		if (getCharacterX() > rightmost) {
			rightmost = getCharacterX();
			timeout = GlobalVariables::TimeoutConstant;
		}

		timeout = timeout - 1;
		timeoutBonus = pool->getCurrentFrame() / 4;
		/**TODO::UNCOMMENT
		if (timeout + timeoutBonus <= 0 || playerForm->getGameRunning() == false) {
			// change here to adjust fitness importance of distance and speed
			fitness = rightmost - pool->getCurrentFrame() * 0.5;
			if (rightmost > 962)
				fitness = fitness + 1000;
			else if (fitness == 0)
				fitness = -1;
			genome->setFitness(fitness);			

			if (fitness > pool->getCurrentMaxFitness()) {
				pool->setCurrentMaxFitness(fitness);
				pool->setMaxFitnessSpecies(pool->getCurrentSpecies());
				pool->setMaxFitnessGenome(pool->getCurrentGenome());
			}

			if (fitness > pool->getMaxFitness()) {
				pool->setMaxFitness(fitness);
				pool->setMaxFitnessSpecies(pool->getCurrentSpecies());
				pool->setMaxFitnessGenome(pool->getCurrentGenome());
				pool->setSaveGenome(true);
			}

			System::Diagnostics::Debug::WriteLine("Generation " + pool->getGeneration() + " species " + pool->getCurrentSpecies() + " genome " + pool->getCurrentGenome() + " fitness: " + fitness);
			pool->setCurrentGenome(1);
			pool->setCurrentSpecies(1);
			while (fitnessAlreadyMeasured())
				nextGenome();
			initializeRun();
		}
		*/
		pool->setCurrentFrame(pool->getCurrentFrame() + 1);
		/**TODO::UNCOMMENTplayerForm->updateGame();*/
	}
}

void NeuralNetwork::runGenome(string filename) {
	double fitness;
	double timeoutBonus;
	int currentFrame = 0;
	bool running = true;
		
	createLabels();
	shared_ptr<Genome> genome = loadGenome(filename);
	genome->setParentPool(pool);
	genome->generateNetwork();	
	displayGenome(genome);
	/**TODO::UNCOMMENT
	while (running && playerForm->getGameRunning()) {
		evaluateGenome(genome);

		if (getCharacterX() > rightmost) {
			rightmost = getCharacterX();
			timeout = GlobalVariables::TimeoutConstant;
		}
			
		fitness = rightmost - currentFrame * 0.5;
		if (rightmost > 962) 
			fitness = fitness + 1000;
		
		playerForm->getLabelValues()[4] = fitness;

		timeout = timeout - 1;
		timeoutBonus = currentFrame / 4;

		if (timeout + timeoutBonus <= 0) 
			running = false;
		
		updateCellValues(genome);
		playerForm->updateDisplay();
		playerForm->updateGame();	

		currentFrame++;
		playerForm->getThread()->Sleep(10);			
	}	
	*/
}

void NeuralNetwork::initializePool() {
	pool = make_shared<Pool>();
	
	for (int i = 0; i < GlobalVariables::Population; i++) {
		shared_ptr<Genome> basicGenome = createBasicGenome();
		pool->addToSpecies(basicGenome);
	}	
	
	initializeRun();
}

void NeuralNetwork::initializeRun() {
	shared_ptr<Species> species;
	shared_ptr<Genome> genome;

	//playerForm->restartGame();
	rightmost = 0;
	pool->setCurrentFrame(0);
	timeout = GlobalVariables::TimeoutConstant;
	// may have to set all keyboard inputs to 0?

	species = pool->getSpecies()[pool->getCurrentSpecies()];
	genome = species->getGenome()[pool->getCurrentGenome()];

	genome->generateNetwork();
	evaluateCurrent();
}

shared_ptr<Genome> NeuralNetwork::createBasicGenome() {
	shared_ptr<Genome> genome = make_shared<Genome>();
	// int innovation = 1; ?

	genome->setParentPool(pool);
	genome->setMaxNeuron(GlobalVariables::NumInputs);
	genome->createBasicGenes();
	genome->mutate();

	return genome;
}

void NeuralNetwork::evaluateCurrent() {
	shared_ptr<Species> species = pool->getSpecies()[pool->getCurrentSpecies()];
	shared_ptr<Genome> genome = species->getGenome()[pool->getCurrentGenome()];

	vector<double> inputs;
	inputs.push_back(NULL);
	inputs.push_back(getCharacterX() / 962.0);
	inputs.push_back(getCharacterY() / 586.0);
	inputs.push_back((getEnemy1() - 422) / (149.0 - 18));
	inputs.push_back((getEnemy2() - 766) / (110.0 - 18));
	inputs.push_back(1.0);

	// keyboard[0] = space, keyboard[1] = left, keyboard[2] = right
	vector<bool> keyboard = genome->evaluateNetwork(inputs);

	if (keyboard[1] == true && keyboard[2] == true) {
		keyboard[1] = false;
		keyboard[2] = false;
	}

	//playerForm->setControls(keyboard);
}

void NeuralNetwork::evaluateGenome(shared_ptr<Genome> genome) {
	vector<double> inputs;
	inputs.push_back(NULL);
	inputs.push_back(getCharacterX() / 962.0);
	inputs.push_back(getCharacterY() / 586.0);
	inputs.push_back((getEnemy1() - 422) / (149.0 - 18));
	inputs.push_back((getEnemy2() - 766) / (110.0 - 18));
	inputs.push_back(1.0);

	// keyboard[0] = Left, keyboard[1] = Right, keyboard[2] = Up, keyboard[3] = Down, keyboard[4] = Plant Bomb, keyboard[5] = Trigger Bomb
	vector<bool> keyboard = genome->evaluateNetwork(inputs);

	//playerForm->setControls(keyboard);
}

// character x position (PlayerForm->Size = (962, 586))
double NeuralNetwork::getCharacterX() {
	//return playerForm->getCharacter()->Location.X / 962.0;
	//return playerForm->getCharacter()->Location.X;
	return 1;
}

// character y position
double NeuralNetwork::getCharacterY() {
	//return playerForm->getCharacter()->Location.Y / 586.0;
	//return playerForm->getCharacter()->Location.Y;
	return 1;
}

// enemy1 x position (platform5->Size.Width = 149, platform5->Location.X = 422, character->Size.Width = 19)
double NeuralNetwork::getEnemy1() {
	//return (playerForm->getEnemy1()->Location.X - 422) / (149.0 - 18);
	//return playerForm->getEnemy1()->Location.X;
	return 1;
}

// enemy2 x position (platform8->Size.Width = 110, platform8->Location.X = 766)
double NeuralNetwork::getEnemy2() {
	//return (playerForm->getEnemy2()->Location.X - 766) / (110.0 - 18);
	//return playerForm->getEnemy2()->Location.X;
	return 1;
}

bool NeuralNetwork::fitnessAlreadyMeasured() {
	shared_ptr<Species> species = pool->getSpecies()[pool->getCurrentSpecies()];
	shared_ptr<Genome> genome = species->getGenome()[pool->getCurrentGenome()];

	return (genome->getFitness() != 0);
}

void NeuralNetwork::nextGenome() {
	pool->setCurrentGenome(pool->getCurrentGenome() + 1);
	if (pool->getCurrentGenome() >= pool->getSpecies()[pool->getCurrentSpecies()]->getGenome().size()) {
		pool->setCurrentGenome(1);
		pool->setCurrentSpecies(pool->getCurrentSpecies() + 1);
		if (pool->getCurrentSpecies() >= pool->getSpecies().size()) {
			saveGenome();
			pool->setCurrentMaxFitness(0);
			pool->setSaveGenome(false);
			pool->newGeneration();
			pool->setCurrentSpecies(1);
		}
	}
	return;
}

void NeuralNetwork::saveGenome() {
	// remove if statement to save genomes for every generation
	if (pool->getSaveGenome() == true) {
		shared_ptr<Genome> genome = pool->getSpecies()[pool->getMaxFitnessSpecies()]->getGenome()[pool->getMaxFitnessGenome()];

		string filename = "generation" + to_string(pool->getGeneration()) + ".json";
		Json::Value jsonSettings;
		// write genome information
		jsonSettings["genome"]["info"]["generation"] = pool->getGeneration();
		jsonSettings["genome"]["info"]["species"] = pool->getMaxFitnessSpecies();
		jsonSettings["genome"]["info"]["genome"] = pool->getMaxFitnessGenome();
		// write genome object
		jsonSettings["genome"]["object"]["fitness"] = genome->getFitness();
		jsonSettings["genome"]["object"]["maxneuron"] = genome->getMaxNeuron();
		jsonSettings["genome"]["object"]["globalrank"] = genome->getGlobalRank();
		jsonSettings["genome"]["object"]["connectionsmr"] = genome->getConnectionsMR();
		jsonSettings["genome"]["object"]["linkmr"] = genome->getLinkMR();
		jsonSettings["genome"]["object"]["biasmr"] = genome->getBiasMR();
		jsonSettings["genome"]["object"]["nodemr"] = genome->getNodeMR();
		jsonSettings["genome"]["object"]["enablemr"] = genome->getEnableMR();
		jsonSettings["genome"]["object"]["disablemr"] = genome->getDisableMR();
		jsonSettings["genome"]["object"]["stepmr"] = genome->getStepMR();
		// genes
		for (int i = 1; i < genome->getGenes().size(); i++) {
			jsonSettings["genome"]["object"]["genes"][i]["innode"] = genome->getGenes()[i]->getInNode();
			jsonSettings["genome"]["object"]["genes"][i]["outnode"] = genome->getGenes()[i]->getOutNode();
			jsonSettings["genome"]["object"]["genes"][i]["weight"] = genome->getGenes()[i]->getWeight();
			jsonSettings["genome"]["object"]["genes"][i]["isenabled"] = genome->getGenes()[i]->getEnabled();
			jsonSettings["genome"]["object"]["genes"][i]["innovationnum"] = genome->getGenes()[i]->getInnovNum();
		}
		ofstream outfile(filename + "");
		if (outfile.is_open())
			outfile << jsonSettings << endl;
		outfile.close();
	}
	return;
}

shared_ptr<Genome> NeuralNetwork::loadGenome(string filename) {
	cout << "File to genome: " << filename << endl;
	shared_ptr<Genome> genome = make_shared< Genome>();	
	ifstream myfile(filename);

	//if (myfile.is_open())
	{
		// Read the file into json object
		Json::Value jsonSettings;
		myfile >> jsonSettings;

		// read genome information
		//jsonSettings["genome"]["info"]["generation"] = pool->getGeneration();
		//jsonSettings["genome"]["info"]["species"] = pool->getMaxFitnessSpecies();
		//jsonSettings["genome"]["info"]["genome"] = pool->getMaxFitnessGenome();
		// write genome object
		const Json::Value GenomeObject = jsonSettings["genome"]["object"];
		genome->setFitness(GenomeObject["fitness"].asDouble());
		genome->setMaxNeuron(GenomeObject["maxneuron"].asInt());
		genome->setGlobalRank(GenomeObject["globalrank"].asInt());
		genome->setConnectionsMR(GenomeObject["connectionsmr"].asDouble());
		genome->setLinkMR(GenomeObject["linkmr"].asDouble());
		genome->setBiasMR(GenomeObject["biasmr"].asDouble());
		genome->setNodeMR(GenomeObject["nodemr"].asDouble());
		genome->setEnableMR(GenomeObject["enablemr"].asDouble());
		genome->setDisableMR(GenomeObject["disablemr"].asDouble());
		genome->setStepMR(GenomeObject["stepmr"].asDouble());
		// genes
		for (auto iter : GenomeObject["genes"]) {
			shared_ptr<Gene> tempGene = make_shared<Gene>();
			tempGene->setInNode(iter["innode"].asInt());
			tempGene->setOutNode(iter["outnode"].asInt());
			tempGene->setWeight(iter["weight"].asDouble());
			tempGene->setEnabled(iter["isenabled"].asBool());
			tempGene->setInnovNum(iter["innovationnum"].asInt());
			cout << tempGene->getInnovNum() << endl;
			genome->getGenes().push_back(tempGene);
		}
		//playerForm->getLabelValues()[1] = Convert::ToDouble(root->SelectSingleNode("info")->SelectSingleNode("generation")->InnerText);
		//playerForm->getLabelValues()[2] = Convert::ToDouble(root->SelectSingleNode("info")->SelectSingleNode("species")->InnerText);
		//playerForm->getLabelValues()[3] = Convert::ToDouble(root->SelectSingleNode("info")->SelectSingleNode("genome")->InnerText);
		myfile.close();
	}
	return genome;
}

void NeuralNetwork::displayGenome(shared_ptr<Genome> genome) {
	vector<int> neurons;
	bool exists;
	int tempNeuron;
	double xSpacing;

	//for (int i = 0; i <= GlobalVariables::MaxNodes + GlobalVariables::NumOutputs; i++) {
	//	playerForm->getCellX().push_back(0);
	//	playerForm->getCellY().push_back(0);
	//	playerForm->getCellValue().push_back(0);
	//}

	// hidden nodes
	for (int i = 1; i < genome->getGenes().size(); i++) {
		shared_ptr<Gene> gene = genome->getGenes()[i];
		if (gene->getInNode() > GlobalVariables::NumInputs && gene->getInNode() <= GlobalVariables::MaxNodes) {
			exists = false;
			for (int j = 0; j < neurons.size(); j++)
				if (neurons[j] == gene->getInNode())
					exists = true;
			if (exists == false)
				neurons.push_back(gene->getInNode());
		}
		if (gene->getOutNode() > GlobalVariables::NumInputs && gene->getOutNode() <= GlobalVariables::MaxNodes) {
			exists = false;
			for (int j = 0; j < neurons.size(); j++)
				if (neurons[j] == gene->getOutNode())
					exists = true;
			if (exists == false)
				neurons.push_back(gene->getOutNode());
		}
	}
	/**TODO::UNCOMMENT
	for (int i = 1; i < genome->getGenes().size(); i++) {
		shared_ptr<Gene> gene = genome->getGenes()[i];
		if (gene->getInNode() > GlobalVariables::NumInputs && gene->getInNode() <= GlobalVariables::MaxNodes && gene->getOutNode() > GlobalVariables::NumInputs && gene->getOutNode() <= GlobalVariables::MaxNodes) {
			if (neurons->IndexOf(gene->getInNode()) > neurons->IndexOf(gene->getOutNode())) {
				tempNeuron = neurons[neurons->IndexOf(gene->getInNode())];
				neurons[neurons->IndexOf(gene->getInNode())] = neurons[neurons->IndexOf(gene->getOutNode())];
				neurons[neurons->IndexOf(gene->getOutNode())] = tempNeuron;
			}
		}
	}
	
	xSpacing = (315.0 - 51.0) / (neurons.size() + 1);
	
	for (int i = 0; i < neurons.size(); i++) {
		playerForm->getCellX()[neurons[i]] = xSpacing*(i + 1) + 51;
		playerForm->getCellY()[neurons[i]] = rand() % (152 - 19) + 19;
	}

	// inputs
	for (int i = 0; i < 4; i++) {
		playerForm->getCellX()[i+1] = 42;
		playerForm->getCellY()[i+1] = 10 + (25 * i) + (i * 9);
	}
	playerForm->getCellX()[5] = 42;
	playerForm->getCellY()[5] = 161;
	
	// outputs
	playerForm->getCellX()[GlobalVariables::MaxNodes + 1] = 324;
	playerForm->getCellY()[GlobalVariables::MaxNodes + 1] = 25;
	playerForm->getCellX()[GlobalVariables::MaxNodes + 2] = 324;
	playerForm->getCellY()[GlobalVariables::MaxNodes + 2] = 83;
	playerForm->getCellX()[GlobalVariables::MaxNodes + 3] = 324;
	playerForm->getCellY()[GlobalVariables::MaxNodes + 3] = 148;

	// genes
	for (int i = 1; i < genome->getGenes().size(); i++) {		
		playerForm->getInCell().push_back(genome->getGenes()[i]->getInNode());
		playerForm->getOutCell().push_back(genome->getGenes()[i]->getOutNode());		
		if (genome->getGenes()[i]->getEnabled() == false)
			playerForm->getGeneWeight().push_back(0);
		else
			playerForm->getGeneWeight().push_back(genome->getGenes()[i]->getWeight());
	}*/
}

void NeuralNetwork::updateCellValues(shared_ptr<Genome> genome) {
	/**TODO::UNCOMMENT
	for (int i = 1; i < genome->getNetwork()->getNeurons().size(); i++) {
		if (genome->getNetwork()->getNeurons()[i] != nullptr)
			playerForm->getCellValue()[i] = genome->getNetwork()->getNeurons()[i]->getValue();
	}*/
}

void NeuralNetwork::clearDisplay() {
	//playerForm->getCellX()->RemoveRange(0, playerForm->getCellX().size());
	//playerForm->getCellY()->RemoveRange(0, playerForm->getCellY().size());
	//playerForm->getCellValue()->RemoveRange(0, playerForm->getCellValue().size());
	//playerForm->getInCell()->RemoveRange(0, playerForm->getInCell().size());
	//playerForm->getOutCell()->RemoveRange(0, playerForm->getOutCell().size());
	//playerForm->getGeneWeight()->RemoveRange(0, playerForm->getGeneWeight().size());
}

void NeuralNetwork::updateLabels() {
	/**TODO::UNCOMMENT
	if (playerForm->getLabelValues().size() == 0)
		for (int i = 0; i < 6; i++)
			playerForm->getLabelValues().push_back(0);

	playerForm->getLabelValues()[0] = GlobalVariables::Population;
	playerForm->getLabelValues()[1] = pool->getGeneration();
	playerForm->getLabelValues()[2] = pool->getCurrentSpecies();
	playerForm->getLabelValues()[3] = pool->getCurrentGenome();
	playerForm->getLabelValues()[4] = 0;
	playerForm->getLabelValues()[5] = pool->getMaxFitness();
	*/
}

void NeuralNetwork::createLabels() {
	/**TODO::UNCOMMENT
	if (playerForm->getLabelValues().size() == 0)
		for (int i = 0; i < 6; i++)
			playerForm->getLabelValues().push_back(0);
			*/
}

////////////////////////////// Pool //////////////////////////////

Pool::Pool():
species()
{
	shared_ptr<Species> temp;
	temp.reset();
	species.push_back(temp);
	generation = 0;
	//innovation = GlobalVariables::NumOutputs; 
	innovation = 15;
	currentSpecies = 1; 
	currentGenome = 1; 
	maxFitness = 0;
	currentMaxFitness = 0;
	currentFrame = 0;
	maxFitnessSpecies = 0;
	maxFitnessGenome = 0;
	saveGenome = false;
}

vector<shared_ptr<Species>> Pool::getSpecies() {
	return species;
}

int Pool::getCurrentSpecies() {
	return currentSpecies;
}

void Pool::setCurrentSpecies(int num) {
	currentSpecies = num;
	return;
}

int Pool::getCurrentGenome() {
	return currentGenome;
}

void Pool::setCurrentGenome(int num) {
	currentGenome = num;
	return;
}

void Pool::addToSpecies(shared_ptr<Genome> genome) {
	for (int i = 1; i < species.size(); i++) {
		if (isSameSpecies(genome, species[i]->getGenome()[1])) {
			species[i]->getGenome().push_back(genome);
			return;
		}
	}

	shared_ptr<Species> newSpecies = make_shared<Species>();
	newSpecies->getGenome().push_back(genome);
	species.push_back(newSpecies);
	return;
}

bool Pool::isSameSpecies(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	int maxGenes = std::max(genome1->getGenes().size() - 1, genome2->getGenes().size() - 1);
	//double numDisjoint = numDisjointGenes(genome1, genome2);
	//double numExcess = numExcessGenes(genome1, genome2);
	double numDisjointExcess = numDisjointExcessGenes(genome1, genome2);
	double weight = weightDifferences(genome1, genome2);
	
	double compatibility = ((GlobalVariables::C1*numDisjointExcess) / maxGenes) + (GlobalVariables::C3*weight);
	
	if (compatibility < GlobalVariables::CompatibilityThreshold)
		return true;
	else
		return false;
}

int Pool::numDisjointExcessGenes(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	vector<bool> innovation1;
	vector<bool> innovation2;
	int numDisjoint = 0;

	int maxInnov = 0;
	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (genome1->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome1->getGenes()[i]->getInnovNum();
	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (genome2->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome2->getGenes()[i]->getInnovNum();

	for (int i = 0; i <= maxInnov; i++) {
		innovation1.push_back(false);
		innovation2.push_back(false);
	}

	for (int i = 1; i < genome1->getGenes().size(); i++)
		innovation1[genome1->getGenes()[i]->getInnovNum()] = true;
	for (int i = 1; i < genome2->getGenes().size(); i++)
		innovation1[genome2->getGenes()[i]->getInnovNum()] = true;

	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (innovation2[genome1->getGenes()[i]->getInnovNum()] == false)
			numDisjoint++;

	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (innovation1[genome2->getGenes()[i]->getInnovNum()] == false)
			numDisjoint++;

	return numDisjoint;
}

// needs to be fixed
int Pool::numDisjointGenes(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	vector<bool> innovation1;
	vector<bool> innovation2;
	int numDisjoint = 0;
	int bigGenomeMaxInnov = std::max(genome1->getGenes()[genome1->getGenes().size() - 1]->getInnovNum(), genome2->getGenes()[genome2->getGenes().size() - 1]->getInnovNum());
	int smallGenomeMaxInnov = std::min(genome1->getGenes()[genome1->getGenes().size() - 1]->getInnovNum(), genome2->getGenes()[genome2->getGenes().size() - 1]->getInnovNum());

	for (int i = 0; i <= bigGenomeMaxInnov; i++) {
		innovation1.push_back(false);
		innovation2.push_back(false);
	}

	for (int i = 1; i < genome1->getGenes().size(); i++)
		innovation1[genome1->getGenes()[i]->getInnovNum()] = true;
	for (int i = 1; i < genome2->getGenes().size(); i++)
		innovation1[genome2->getGenes()[i]->getInnovNum()] = true;

	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (innovation2[genome1->getGenes()[i]->getInnovNum()] == false && genome1->getGenes()[i]->getInnovNum() <= smallGenomeMaxInnov)
			numDisjoint++;

	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (innovation1[genome2->getGenes()[i]->getInnovNum()] == false && genome2->getGenes()[i]->getInnovNum() <= smallGenomeMaxInnov)
			numDisjoint++;

	return numDisjoint;
}

// needs to be fixed
int Pool::numExcessGenes(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	vector<bool> innovation1;
	vector<bool> innovation2;
	int numExcess = 0;
	int bigGenomeMaxInnov = std::max(genome1->getGenes()[genome1->getGenes().size() - 1]->getInnovNum(), genome2->getGenes()[genome2->getGenes().size() - 1]->getInnovNum());
	int smallGenomeMaxInnov = std::min(genome1->getGenes()[genome1->getGenes().size() - 1]->getInnovNum(), genome2->getGenes()[genome2->getGenes().size() - 1]->getInnovNum());

	for (int i = 0; i <= bigGenomeMaxInnov; i++) {
		innovation1.push_back(false);
		innovation2.push_back(false);
	}

	for (int i = 1; i < genome1->getGenes().size(); i++)
		innovation1[genome1->getGenes()[i]->getInnovNum()] = true;
	for (int i = 1; i < genome2->getGenes().size(); i++)
		innovation1[genome2->getGenes()[i]->getInnovNum()] = true;

	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (innovation2[genome1->getGenes()[i]->getInnovNum()] == false && genome1->getGenes()[i]->getInnovNum() > smallGenomeMaxInnov)
			numExcess++;

	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (innovation1[genome2->getGenes()[i]->getInnovNum()] == false && genome2->getGenes()[i]->getInnovNum() > smallGenomeMaxInnov)
			numExcess++;

	return numExcess;
}

double Pool::weightDifferences(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	vector<shared_ptr<Gene>> genes1;
	double totalWeight = 0;
	int numMatching = 0;

	int maxInnov = 0;
	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (genome1->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome1->getGenes()[i]->getInnovNum();
	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (genome2->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome2->getGenes()[i]->getInnovNum();

	for (int i = 0; i <= maxInnov; i++)
	{
		shared_ptr<Gene> temp;
		temp.reset();
		genes1.push_back(temp);
	}

	for (int i = 1; i < genome1->getGenes().size(); i++)
		genes1[genome1->getGenes()[i]->getInnovNum()] = genome1->getGenes()[i];

	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (genes1[genome2->getGenes()[i]->getInnovNum()] != nullptr) {
			totalWeight = totalWeight + abs(genes1[genome2->getGenes()[i]->getInnovNum()]->getWeight() - genome2->getGenes()[i]->getWeight());
			numMatching++;
		}

	if (totalWeight == 0)
		return 0;
	else
		return (totalWeight / numMatching);
}


int Pool::newInnovation() {
	innovation++;
	return innovation;
}

int Pool::getCurrentFrame() {
	return currentFrame;
}

void Pool::setCurrentFrame(int num) {
	currentFrame = num;
	return;
}

double Pool::getMaxFitness() {
	return maxFitness;
}

void Pool::setMaxFitness(double num) {
	maxFitness = num;
	return;
}

double Pool::getCurrentMaxFitness() {
	return currentMaxFitness;
}

void Pool::setCurrentMaxFitness(double num) {
	currentMaxFitness = num;
	return;
}

int Pool::getGeneration() {
	return generation;
}

int Pool::getMaxFitnessSpecies() {
	return maxFitnessSpecies;
}

void Pool::setMaxFitnessSpecies(int num) {
	maxFitnessSpecies = num;
	return;
}

int Pool::getMaxFitnessGenome() {
	return maxFitnessGenome;
}

void Pool::setMaxFitnessGenome(int num) {
	maxFitnessGenome = num;
	return;
}

bool Pool::getSaveGenome() {
	return saveGenome;
}

void Pool::setSaveGenome(bool willBeSaved) {
	saveGenome = willBeSaved;
	return;
}

void Pool::newGeneration() {	
	
	double sum;
	int breed;
	vector<shared_ptr<Genome>> offspring;
	
	cullWeakGenomes();
	cullSpecies(false);

	for (int i = 1; i < species.size(); i++) 
		species[i]->calculateAdjustedFitness();		
			
	removeWeakSpecies2();
	
	sum = totalAdjustedFitness();	
	for (int i = 1; i < species.size(); i++) {
		breed = floor((species[i]->getTotalAdjustedFitness() / (double)sum) * GlobalVariables::Population);
		for (int j = 0; j < breed; j++)
			offspring.push_back(species[i]->breedChild());  
	}
	while (offspring.size() + species.size() - 1 < GlobalVariables::Population)
		offspring.push_back(species[(rand() % (species.size() - 1)) + 1]->breedChild());
	
	cullSpecies(true);		
			
	for (int i = 0; i < offspring.size(); i++)
		addToSpecies(offspring[i]);

	generation = generation + 1;
	return;
	
	/*
	double sum;
	int breed;
	vector<shared_ptr<Genome>>^ offspring = gcnew vector<shared_ptr<Genome>>();

	cullSpecies(false);
	rankGlobally();
	removeStaleSpecies();
	rankGlobally();
	
	for (int i = 1; i < species.size(); i++)
		species[i]->calculateAverageFitness();

	removeWeakSpecies();

	sum = totalAverageFitness();
	for (int i = 1; i < species.size(); i++) {
		breed = floor((species[i]->getAverageFitness() / (double)sum) * GlobalVariables::Population) - 1;
		for (int j = 0; j < breed; j++)
			offspring.push_back(species[i]->breedChild());
	}

	cullSpecies(true);

	while (offspring.size() + species.size() - 1 < GlobalVariables::Population)
		offspring.push_back(species[(rand() % (species.size() - 1)) + 1]->breedChild());

	for (int i = 0; i < offspring.size(); i++)
		addToSpecies(offspring[i]);

	generation++;
	return;
	*/
}

// if cullAllButOne = false then cull bottom 80%, if cullAllButOne = true then cull all but the top member
void Pool::cullSpecies(bool cullAllButOne) {
	int remaining;
	for (int i = 1; i < species.size(); i++) {

		species[i]->sortGenomesDescending(1, species[i]->getGenome().size() - 1);
		
		if (cullAllButOne == true)
			remaining = 1 + 1;
		else
			remaining = ceil((species[i]->getGenome().size() - 1) * GlobalVariables::SurvivalThreshold) + 1;
		
		while (species[i]->getGenome().size() > remaining)
			species[i]->getGenome().erase(species[i]->getGenome().begin() +species[i]->getGenome().size() - 1);
	}
	return;
}

void Pool::cullWeakGenomes() {	
	vector<int> speciesIndex;

	for (int i = 1; i < species.size(); i++) {
		vector<int> genomeIndex;

		for (int j = 1; j < species[i]->getGenome().size(); j++)
			if (species[i]->getGenome()[j]->getFitness() < 0)
				genomeIndex.push_back(j);

		reverse(genomeIndex.begin(), genomeIndex.end());//genomeIndex->Reverse();

		for (int j = 0; j < genomeIndex.size(); j++)
				species[i]->getGenome().erase(species[i]->getGenome().begin() + genomeIndex[j]);

		if (species[i]->getGenome().size() < 2)
			speciesIndex.push_back(i);
	}
	reverse(speciesIndex.begin(), speciesIndex.end());//speciesIndex->Reverse();

	for (int i = 0; i < speciesIndex.size(); i++)
		species.erase(species.begin() + speciesIndex[i]);

	return;
}

double Pool::totalAdjustedFitness() {
	double total = 0;
	for (int i = 1; i < species.size(); i++)
		total = total + species[i]->getTotalAdjustedFitness();
	return total;
}

void Pool::rankGlobally() {
	shared_ptr<Genome> temp;
	temp.reset();
	int count = 1;
	shared_ptr<Species> globalSpecies = make_shared<Species>();

	for (int i = 1; i < species.size(); i++)
		for (int j = 1; j < species[i]->getGenome().size(); j++) 
			globalSpecies->getGenome().push_back(temp);

	for (int i = 1; i < species.size(); i++)
		for (int j = 1; j < species[i]->getGenome().size(); j++) {
			globalSpecies->getGenome()[count] = species[i]->getGenome()[j];
			count++;
		}
		
	globalSpecies->sortGenomesAscending(1, globalSpecies->getGenome().size() - 1);

	for (int i = 1; i < globalSpecies->getGenome().size(); i++)
		globalSpecies->getGenome()[i]->setGlobalRank(i);

	return;
}

void Pool::removeStaleSpecies() {
	shared_ptr<Species> temp;
	temp.reset();
	vector<shared_ptr<Species>> survived;
	survived.push_back(temp);
	for (int i = 1; i < species.size(); i++) {
		species[i]->sortGenomesDescending(1, species[i]->getGenome().size() - 1);
		if (species[i]->getGenome()[1]->getFitness() > species[i]->getTopFitness()) {
			species[i]->setTopFitness(species[i]->getGenome()[1]->getFitness());
			species[i]->setStaleness(0);
		}
		else {
			species[i]->setStaleness(species[i]->getStaleness() + 1);
		}
		if (species[i]->getStaleness() < GlobalVariables::StaleSpecies || species[i]->getTopFitness() >= maxFitness)
			survived.push_back(species[i]);
	}
	species = survived;
	return;
}

void Pool::removeWeakSpecies() {
	shared_ptr<Species> temp;
	temp.reset();
	int breed;
	vector<shared_ptr<Species>> survived;
	survived.push_back(temp);
	for (int i = 1; i < species.size(); i++) {
		breed = floor(species[i]->getAverageFitness() / totalAverageFitness() * GlobalVariables::Population);
		if (breed >= 1)
			survived.push_back(species[i]);
	}
	species = survived;
	return;
}

void Pool::removeWeakSpecies2() {
	vector<int> speciesIndex;

	double sum = totalAdjustedFitness();
	for (int i = 1; i < species.size(); i++)
		if (floor((species[i]->getTotalAdjustedFitness() / (double)sum) * GlobalVariables::Population) < 1)
			speciesIndex.push_back(i);

	reverse(speciesIndex.begin(), speciesIndex.end()); //speciesIndex->Reverse();

	for (int i = 0; i < speciesIndex.size(); i++)
		species.erase(species.begin()+speciesIndex[i]);

	return;
}

double Pool::totalAverageFitness() {
	double total = 0;
	for (int i = 1; i < species.size(); i++)
		total = total + species[i]->getAverageFitness();
	return total;
}

////////////////////////////// Species //////////////////////////////

Species::Species() :
genomes()
{
	shared_ptr<Genome> temp;
	temp.reset();
	genomes.push_back(temp);//hold place 0 so counting starts from 1
	topFitness = 0;
	staleness = 0;
	totalAdjustedFitness = 0;
	averageFitness = 0;
}

vector<shared_ptr<Genome>> &Species::getGenome() {
	return genomes;
}

double Species::getTotalAdjustedFitness() {
	return totalAdjustedFitness;
}

double Species::getTopFitness() {
	return topFitness;
}

void Species::setTopFitness(double num) {
	topFitness = num;
	return;
}

int Species::getStaleness() {
	return staleness;
}

void Species::setStaleness(int num) {
	staleness = num;
	return;
}

double Species::getAverageFitness() {
	return averageFitness;
}

void Species::sortGenomesDescending(int first, int last) {
	if (last - first > 0) {		
		// generate random pivot
		double pivot = genomes[rand() % (last - first + 1) + first]->getFitness();
		int left = first;
		int right = last;
		shared_ptr<Genome> tempGenome;
		// exit loop when both pointers point to pivot (this occurs when they are equal)
		while (left <= right) {			
			// find left element that is less than or equal to pivot
			while (genomes[left]->getFitness() > pivot)
				left++;
			// find right element that is greater than or equal to pivot
			while (genomes[right]->getFitness() < pivot)
				right--;
			// swap left and right elements
			if (left <= right) {
				tempGenome = genomes[left];
				genomes[left] = genomes[right];
				genomes[right] = tempGenome;
				left++;
				right--;
			}
		}
		// call function recursively to continue sorting 
		sortGenomesDescending(first, right);
		sortGenomesDescending(left, last);
	}
	return;
}

void Species::sortGenomesAscending(int first, int last) {
	if (last - first > 0) {
		// generate random pivot
		double pivot = genomes[rand() % (last - first + 1) + first]->getFitness();
		int left = first;
		int right = last;
		shared_ptr<Genome> tempGenome;
		// exit loop when both pointers point to pivot (this occurs when they are equal)
		while (left <= right) {
			// find left element that is greater than or equal to pivot
			while (genomes[left]->getFitness() < pivot)
				left++;
			// find right element that is less than or equal to pivot
			while (genomes[right]->getFitness() > pivot)
				right--;
			// swap left and right elements
			if (left <= right) {
				tempGenome = genomes[left];
				genomes[left] = genomes[right];
				genomes[right] = tempGenome;
				left++;
				right--;
			}
		}
		// call function recursively to continue sorting 
		sortGenomesDescending(first, right);
		sortGenomesDescending(left, last);
	}
	return;
}

void Species::calculateAdjustedFitness() {
	double total = 0;
	for (int i = 1; i < genomes.size(); i++) {		
		genomes[i]->setAdjustedFitness(genomes[i]->getFitness() / (genomes.size() - 1));
		total = total + genomes[i]->getAdjustedFitness();
	}
	totalAdjustedFitness = total;
	return;
}

void Species::calculateAverageFitness() {
	int total = 0;
	for (int i = 1; i < genomes.size(); i++)
		total = total + genomes[i]->getGlobalRank();
	averageFitness = (double)total / genomes.size();
	return;
}

shared_ptr<Genome> Species::breedChild() {
	shared_ptr<Genome> child;
	shared_ptr<Genome> genome1 = genomes[(rand() % (genomes.size() - 1)) + 1];
	shared_ptr<Genome> genome2 = genomes[(rand() % (genomes.size() - 1)) + 1];
			
	if (((double)rand() / (RAND_MAX)) < GlobalVariables::CrossoverChance)
		child = crossover(genome1, genome2);
	else
		child = genome1->copyGenome();

	child->mutate();

	return child;
}

shared_ptr<Genome> Species::crossover(shared_ptr<Genome> genome1, shared_ptr<Genome> genome2) {
	shared_ptr<Genome> tempGenome;
	vector<shared_ptr<Gene>> innovation2;
	shared_ptr<Genome> child = make_shared<Genome>();
	
	int maxInnov = 0;
	for (int i = 1; i < genome1->getGenes().size(); i++)
		if (genome1->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome1->getGenes()[i]->getInnovNum();
	for (int i = 1; i < genome2->getGenes().size(); i++)
		if (genome2->getGenes()[i]->getInnovNum() > maxInnov)
			maxInnov = genome2->getGenes()[i]->getInnovNum();


	// make sure genome1 has the higher fitness
	if (genome2->getFitness() > genome2->getFitness()) {
		tempGenome = genome1;
		genome1 = genome2;
		genome2 = tempGenome;
	}

	for (int i = 0; i <= maxInnov; i++)
	{
		shared_ptr<Gene> temp;
		temp.reset();
		innovation2.push_back(temp);
	}

	for (int i = 1; i < genome2->getGenes().size(); i++)
		innovation2[genome2->getGenes()[i]->getInnovNum()] = genome2->getGenes()[i];

	for (int i = 1; i < genome1->getGenes().size(); i++) {
		// if it is a matching gene, and genome2->gene is enabled, and 50% chance
		if (innovation2[genome1->getGenes()[i]->getInnovNum()] != nullptr && rand() % 2 == 0 && innovation2[genome1->getGenes()[i]->getInnovNum()]->getEnabled() == true)
			child->getGenes().push_back(innovation2[genome1->getGenes()[i]->getInnovNum()]->copyGene());
		else
			child->getGenes().push_back(genome1->getGenes()[i]);
	}

	child->setParentPool(genome1->getParentPool());
	child->setMaxNeuron(std::max(genome1->getMaxNeuron(), genome2->getMaxNeuron()));

	child->setConnectionsMR(genome1->getConnectionsMR());
	child->setLinkMR(genome1->getLinkMR());
	child->setBiasMR(genome1->getBiasMR());
	child->setNodeMR(genome1->getNodeMR());
	child->setEnableMR(genome1->getEnableMR());
	child->setDisableMR(genome1->getDisableMR());
	child->setStepMR(genome1->getStepMR());

	return child;
}

////////////////////////////// Genome //////////////////////////////

Genome::Genome():
genes()
{
	shared_ptr<Gene> temp;
	temp.reset();
	genes.push_back(temp);
	network = make_shared<Network>();
	fitness = 0;
	adjustedFitness = 0;
	maxNeuron = 0;
	globalRank = 0;
	connectionsMR = GlobalVariables::MutateConnectionsChance;
	linkMR = GlobalVariables::LinkMutationChance;
	biasMR = GlobalVariables::BiasMutationChance;
	nodeMR = GlobalVariables::NodeMutationChance;
	enableMR = GlobalVariables::EnableMutationChance;
	disableMR = GlobalVariables::DisableMutationChance;
	stepMR = GlobalVariables::StepSize;
}

int Genome::getMaxNeuron() {
	return maxNeuron;
}

void Genome::setMaxNeuron(int num) {
	maxNeuron = num;
	return;
}

vector<shared_ptr<Gene>> &Genome::getGenes() {
	return genes;
}

shared_ptr<Pool> Genome::getParentPool() {
	return parentPool;
}

void Genome::setParentPool(shared_ptr<Pool> pool) {
	parentPool = pool;
	return;
}

double Genome::getFitness() {
	return fitness;
}

void Genome::setFitness(double num) {
	fitness = num;
	return;
}

double Genome::getAdjustedFitness() {
	return adjustedFitness;
}

void Genome::setAdjustedFitness(double num) {
	adjustedFitness = num;
	return;
}

int Genome::getGlobalRank() {
	return globalRank;
}

void Genome::setGlobalRank(int num) {
	globalRank = num;
	return;
}

shared_ptr<Network> Genome::getNetwork() {
	return network;
}

double Genome::getConnectionsMR() {
	return connectionsMR;
}

void Genome::setConnectionsMR(double num) {
	connectionsMR = num;
	return;
}

double Genome::getLinkMR() {
	return linkMR;
}

void Genome::setLinkMR(double num) {
	linkMR = num;
	return;
}

double Genome::getBiasMR() {
	return biasMR;
}

void Genome::setBiasMR(double num) {
	biasMR = num;
	return;
}

double Genome::getNodeMR() {
	return nodeMR;
}

void Genome::setNodeMR(double num) {
	nodeMR = num;
	return;
}

double Genome::getEnableMR() {
	return enableMR;
}

void Genome::setEnableMR(double num) {
	enableMR = num;
	return;
}

double Genome::getDisableMR() {
	return disableMR;
}

void Genome::setDisableMR(double num) {
	disableMR = num;
	return;
}

double Genome::getStepMR() {
	return stepMR;
}

void Genome::setStepMR(double num) {
	stepMR = num;
	return;
}

void Genome::createBasicGenes() {
	for (int i = 1; i <= GlobalVariables::NumInputs; i++) {
		for (int j = 1; j <= GlobalVariables::NumOutputs; j++) {
			shared_ptr<Gene> gene = make_shared<Gene>();
			gene->setInNode(i);
			gene->setOutNode(GlobalVariables::MaxNodes + j);
			gene->setEnabled(true);
			gene->setInnovNum(3*(i-1) + j);
			gene->setWeight(((double)rand() / (RAND_MAX)) * 4 - 2);
			genes.push_back(gene);
		}
	}
	return;
}

void Genome::mutate() {
	double p;

	randomizeRates();

	if (((double)rand() / (RAND_MAX)) < connectionsMR)
		pointMutate();

	p = linkMR;
	while (p > 0) {
		if (((double)rand() / (RAND_MAX)) < p) 
			linkMutate(false);
		p = p - 1;
	}

	p = biasMR;
	while (p > 0) {
		if (((double)rand() / (RAND_MAX)) < p)
			linkMutate(true);
		p = p - 1;
	}
		
	p = nodeMR;
	while (p > 0) {
		if (((double)rand() / (RAND_MAX)) < p)
			nodeMutate();
		p = p - 1;
	}

	p = enableMR;
	while (p > 0) {
		if (((double)rand() / (RAND_MAX)) < p)
			enableDisableMutate(true);
		p = p - 1;
	}

	p = disableMR;
	while (p > 0) {
		if (((double)rand() / (RAND_MAX)) < p)
			enableDisableMutate(false);
		p = p - 1;
	}
}

void Genome::randomizeRates() {
	if (rand() % 2 == 0)
		connectionsMR = connectionsMR * 0.95;
	else
		connectionsMR = connectionsMR * 1.05263;

	if (rand() % 2 == 0)
		linkMR = linkMR * 0.95;
	else
		linkMR = linkMR * 1.05263;

	if (rand() % 2 == 0)
		biasMR = biasMR * 0.95;
	else
		biasMR = biasMR * 1.05263;

	if (rand() % 2 == 0)
		nodeMR = nodeMR * 0.95;
	else
		nodeMR = nodeMR * 1.05263;

	if (rand() % 2 == 0)
		enableMR = enableMR * 0.95;
	else
		enableMR = enableMR * 1.05263;

	if (rand() % 2 == 0)
		disableMR = disableMR * 0.95;
	else
		disableMR = disableMR * 1.05263;

	if (rand() % 2 == 0)
		stepMR = stepMR * 0.95;
	else
		stepMR = stepMR * 1.05263;
}

void Genome::pointMutate() {
	for (auto geneIter : genes)
		if (((double)rand() / (RAND_MAX)) < GlobalVariables::PerturbChance)
			geneIter->setWeight(geneIter->getWeight() + ((double)rand() / (RAND_MAX)) * stepMR * 2 - stepMR);
		else
			geneIter->setWeight(((double)rand() / (RAND_MAX)) * 4 - 2);
}

void Genome::linkMutate(bool forceBias) {
	int neuron1 = randomNeuron(false);
	int neuron2 = randomNeuron(true);
	int temp;
	
	shared_ptr<Gene> newLink = make_shared<Gene>();

	if (neuron1 <= GlobalVariables::NumInputs && neuron2 <= GlobalVariables::NumInputs) // both are input nodes
		return;

	if (neuron2 <= GlobalVariables::NumInputs) {
		temp = neuron1;
		neuron1 = neuron2;
		neuron2 = temp;
	}

	newLink->setInNode(neuron1);
	newLink->setOutNode(neuron2);
	if (forceBias == true)
		newLink->setInNode(GlobalVariables::NumInputs);

	if (containsLink(newLink) == true)
		return;

	newLink->setInnovNum(parentPool->newInnovation());
	newLink->setWeight(((double)rand() / (RAND_MAX)) * 4 - 2);
	
	genes.push_back(newLink);
	return;
}

void Genome::nodeMutate() {
	shared_ptr<Gene> gene;
	shared_ptr<Gene> gene1;
	shared_ptr<Gene> gene2;

	if (genes.size() == 0)
		return;

	maxNeuron = maxNeuron + 1;

	gene = genes[(rand() % (genes.size()-1)) + 1];
	if (gene->getEnabled() == false)
		return;
	gene->setEnabled(false);

	gene1 = gene->copyGene();
	gene1->setOutNode(maxNeuron);
	gene1->setWeight(1.0);
	gene1->setInnovNum(parentPool->newInnovation());
	gene1->setEnabled(true);
	genes.push_back(gene1);

	gene2 = gene->copyGene();
	gene2->setInNode(maxNeuron);
	gene2->setInnovNum(parentPool->newInnovation());
	gene2->setEnabled(true);
	genes.push_back(gene2);

	return;
}

void Genome::enableDisableMutate(bool enable) {
	vector<shared_ptr<Gene>> candidates;

	for (int i = 1; i < genes.size(); i++)
		if (genes[i]->getEnabled() != enable)
			candidates.push_back(genes[i]);

	if (candidates.size() == 0)
		return;
	else {
		candidates[rand() % candidates.size()]->setEnabled(!enable);
		return;
	}
}

int Genome::randomNeuron(bool nonInput) {
	vector<bool> neurons;
	int count = 0;
	int n;

	for (int i = 0; i <= GlobalVariables::MaxNodes + GlobalVariables::NumOutputs; i++)
		neurons.push_back(false);

	if (nonInput == false)
		for (int i = 1; i <= GlobalVariables::NumInputs; i++) 
			neurons[i] = true;
			
	for (int i = 1; i <= GlobalVariables::NumOutputs; i++) 
		neurons[GlobalVariables::MaxNodes + i] = true;
		
	for (int i = 1; i < genes.size(); i++) {
		if (nonInput == false || genes[i]->getInNode() > GlobalVariables::NumInputs) 
			neurons[genes[i]->getInNode()] = true;			
		if (nonInput == false || genes[i]->getOutNode() > GlobalVariables::NumInputs) 
			neurons[genes[i]->getOutNode()] = true;
	}

	for (int i = 0; i < neurons.size(); i++)
		if (neurons[i] == true)
			count++;

	n = rand() % count + 1;
			
	for (int i = 1; i <= GlobalVariables::MaxNodes + GlobalVariables::NumOutputs; i++) {
		if (neurons[i] == true) 
			n = n - 1;
		if (n == 0) 
			return i;
	}
	
	return 0; 
}

bool Genome::containsLink(shared_ptr<Gene> link) { 
	for (int i = 1; i < genes.size(); i++) 
		if (genes[i]->getInNode() == link->getInNode() && genes[i]->getOutNode() == link->getOutNode())
			return true;
	return false;
}

void Genome::generateNetwork() {
	shared_ptr<Neuron> temp;
	temp.reset();
	for (int i = 1; i <= GlobalVariables::MaxNodes + GlobalVariables::NumOutputs; i++)
		network->getNeurons().push_back(temp);
	
	for (int i = 1; i <= GlobalVariables::NumInputs; i++)
		network->getNeurons()[i] = make_shared<Neuron>();
	
	for (int i = 1; i <= GlobalVariables::NumOutputs; i++)
		network->getNeurons()[GlobalVariables::MaxNodes + i] = make_shared<Neuron>();
	
	sortGenes(1, genes.size() - 1);

	for (int i = 1; i < genes.size(); i++)
		if (genes[i]->getEnabled() == true) {
			if (network->getNeurons()[genes[i]->getOutNode()] == nullptr)
				network->getNeurons()[genes[i]->getOutNode()] = make_shared<Neuron>();
			network->getNeurons()[genes[i]->getOutNode()]->getIncomingGenes().push_back(genes[i]);
			if (network->getNeurons()[genes[i]->getInNode()] == nullptr)
				network->getNeurons()[genes[i]->getInNode()] = make_shared<Neuron>();
		}
}

void Genome::sortGenes(int first, int last) {
	if (last - first > 0) {
		// generate random pivot
		int pivot = genes[rand() % (last - first + 1) + first]->getOutNode();
		int left = first;
		int right = last;
		shared_ptr<Gene> tempGene;
		// exit loop when both pointers point to pivot (this occurs when they are equal)
		while (left <= right) {
			// find left element that is greater than or equal to pivot
			while (genes[left]->getOutNode() < pivot)
				left++;
			// find right element that is less than or equal to pivot
			while (genes[right]->getOutNode() > pivot)
				right--;
			// swap left and right elements
			if (left <= right) {
				tempGene = genes[left];
				genes[left] = genes[right];
				genes[right] = tempGene;
				left++;
				right--;
			}
		}
		// call function recursively to continue sorting 
		sortGenes(first, right);
		sortGenes(left, last);
	}
	return;
}

vector<bool> Genome::evaluateNetwork(vector<double> inputs) {
	double sum;
	shared_ptr<Gene> incomingGene;
	shared_ptr<Neuron> incomingNeuron;
	
	for (int i = 1; i <= GlobalVariables::NumInputs; i++)
		network->getNeurons()[i]->setValue(inputs[i]);
		
	for (int i = 1; i < network->getNeurons().size(); i++) {
		sum = 0;			
		if (network->getNeurons()[i] != nullptr) {
			for (int j = 1; j < network->getNeurons()[i]->getIncomingGenes().size(); j++) {
				incomingGene = network->getNeurons()[i]->getIncomingGenes()[j];
				incomingNeuron = network->getNeurons()[incomingGene->getInNode()];
				sum = sum + incomingGene->getWeight() * incomingNeuron->getValue();
			}
			if (network->getNeurons()[i]->getIncomingGenes().size() > 1)
				network->getNeurons()[i]->setValue(sigmoid(sum));
		}
	}
	double MaxOutout = 0;
	vector<bool> outputs;
	for (int i = 1; i <= GlobalVariables::NumOutputs; i++) {
		if (network->getNeurons()[GlobalVariables::MaxNodes + i]->getValue() > 0)
			outputs.push_back(true);
		else
			outputs.push_back(false);
	}

	return outputs;
}

double Genome::sigmoid(double x) {
	//return (1 / (1 + exp(-x - GlobalVariables::SigmoidBias)));
	return (2 / (1 + exp(-4.9 * x)) - 1);
}

shared_ptr<Genome> Genome::copyGenome() {
	shared_ptr<Genome> newGenome = make_shared<Genome>();

	for (int i = 1; i < genes.size(); i++)
		newGenome->getGenes().push_back(genes[i]->copyGene());

	newGenome->setParentPool(parentPool);
	newGenome->setMaxNeuron(maxNeuron);
	newGenome->setConnectionsMR(connectionsMR);
	newGenome->setLinkMR(linkMR);
	newGenome->setBiasMR(biasMR);
	newGenome->setNodeMR(nodeMR);
	newGenome->setEnableMR(enableMR);
	newGenome->setDisableMR(disableMR);
	newGenome->setStepMR(stepMR);

	return newGenome;
}

////////////////////////////// Network //////////////////////////////

Network::Network():
neurons()
{
	shared_ptr<Neuron> temp;
	temp.reset();
	neurons.push_back(temp);
}

vector<shared_ptr<Neuron>> &Network::getNeurons() {
	return neurons;
}

////////////////////////////// Gene //////////////////////////////

Gene::Gene() {
	inNode = 0;
	outNode = 0;
	weight = 0;
	isEnabled = true;
	innovationNum = 0;
}

int Gene::getInnovNum() {
	return innovationNum;
}

void Gene::setInnovNum(int num) {
	innovationNum = num;
	return;
}

double Gene::getWeight() {
	return weight;
}

void Gene::setWeight(double num) {
	weight = num;
	return;
}

bool Gene::getEnabled() {
	return isEnabled;
}

void Gene::setEnabled(bool enable) {
	isEnabled = enable;
	return;
}

int Gene::getInNode() {
	return inNode;
}

void Gene::setInNode(int num) {
	inNode = num;
	return;
}

int Gene::getOutNode() {
	return outNode;
}
void Gene::setOutNode(int num) {
	outNode = num;
	return;
}

shared_ptr<Gene> Gene::copyGene() {
	shared_ptr<Gene> newGene = make_shared<Gene>();
	newGene->setInNode(inNode);
	newGene->setOutNode(outNode);
	newGene->setWeight(weight);
	newGene->setEnabled(isEnabled);
	newGene->setInnovNum(innovationNum);
	return newGene;
}

////////////////////////////// Neuron //////////////////////////////

Neuron::Neuron():
incomingGenes()
{
	shared_ptr<Gene> temp;
	temp.reset();
	incomingGenes.push_back(temp);
	value = 0.0;
}

vector<shared_ptr<Gene>> &Neuron::getIncomingGenes() {
	return incomingGenes;
}

double Neuron::getValue() {
	return value;
}

void Neuron::setValue(double num) {
	value = num;
	return;
}
