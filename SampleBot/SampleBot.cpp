// SampleBot.cpp : Defines the entry point for the console application.
//

#include <random>
#include <iostream>

///Local Includes
#include "Logger.h"
#include "json\json.h"
#include "json\json-forwards.h"

#include "PlayerState.h"
#include "Block.h"
#include "Map.h"

using namespace std;

void readStateFile(string filePath);
void writeMoveFile(string filePath);

//Instantiate the Log File
Logger Log("C:\\Users\\brand\\Downloads\\Bomberman\\Sample Bots\\C++\\MoveLog");

cMapState currentMap;
vector<PlayerState> vPlayerState;

int main(int argc, char* argv[])
{
	string filePath = "";

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	if (argc == 3)
	{
		string Path (argv[2]);
		filePath = Path;
		cout << "File Path: " << filePath << std::endl;
	}
	Log.WriteToLog("Parsed args");


	readStateFile(filePath);
	writeMoveFile(filePath);
	return 0;
}

void readStateFile(string filePath)
{
	cout << "Reading state file " << filePath + "\\" + "state.json" << std::endl;
	string fileContent;
	string line;
	ifstream myfile(filePath + "\\" + "state.json");

	Json::Value Root;
	if (myfile.is_open())
	{
		myfile >> Root;
		const Json::Value RegisteredPlayerEntities = Root["RegisteredPlayerEntities"];
		const Json::Value CurrentRound = Root["CurrentRound"];
		const Json::Value PlayerBounty = Root["PlayerBounty"];
		const Json::Value MapHeight = Root["MapHeight"];
		const Json::Value MapWidth = Root["MapWidth"];
		const Json::Value MapSeed = Root["MapSeed"];
		const Json::Value GameBlocksRows = Root["GameBlocks"];

		
		for (int index = 0; index < RegisteredPlayerEntities.size(); ++index)
		{
			const Json::Value Name = RegisteredPlayerEntities[index]["Name"];
			const Json::Value Key = RegisteredPlayerEntities[index]["Key"];
			const Json::Value Points = RegisteredPlayerEntities[index]["Points"];
			const Json::Value Killed = RegisteredPlayerEntities[index]["Killed"];
			const Json::Value BombBag = RegisteredPlayerEntities[index]["BombBag"];
			const Json::Value BombRadius = RegisteredPlayerEntities[index]["BombRadius"];
			const Json::Value Location = RegisteredPlayerEntities[index]["Location"];
			PlayerState Player(Name, Key, Points, Killed, BombBag, BombRadius, Location);
			cout << Player.ToString() << endl;
			vPlayerState.push_back(Player);
		}
		cout << CurrentRound.asString() << endl;
		cout << PlayerBounty.asString() << endl;
		cout << MapHeight.asString() << endl;
		cout << MapWidth.asString() << endl;
		cout << MapSeed.asString() << endl;

		// Iterate over the sequence elements.
		for (int index = 0; index < GameBlocksRows.size(); ++index)
		{
			for (int Blockindex = 0; Blockindex < GameBlocksRows[index].size(); ++Blockindex)
			{
				const Json::Value Block = GameBlocksRows[index][Blockindex];

				const Json::Value EntityType = Block["Entity"];
				const Json::Value Bomb = Block["Bomb"];
				const Json::Value PowerUp = Block["PowerUp"];
				const Json::Value Exploding = Block["Exploding"];
				const Json::Value Location = Block["Location"];
				cBlock CurrentBlock(EntityType, Bomb, PowerUp, Exploding, Location);
				currentMap.m_vMap.push_back(CurrentBlock);
				Log.WriteToLog(CurrentBlock.ToString());
			}
		}
		myfile.close();
	}
}

void writeMoveFile(string filePath)
{
	currentMap.ClosestPowerUp(vPlayerState[3].GetLocation());
	currentMap.ClosestBomb(vPlayerState[3].GetLocation());
	cout << "Writing move file " << filePath + "\\" + "move.txt" << std::endl;
	ofstream outfile(filePath + "\\" + "move.txt");
	Json::Value jsonSettings;
	jsonSettings["genome"]["object"]["genes"] = "thisisagene";

	for (int i = 1; i < 5; i++) {
		jsonSettings["genome"]["object"]["list"][i]["one"] = "ten";
		jsonSettings["genome"]["object"]["list"][i]["two"] = Json::Value::Int(i);
	}
	
	outfile << jsonSettings << endl;
	if (outfile.is_open())
	{
		random_device rd; 
		mt19937 rng(rd());
		uniform_int_distribution<int> uni(1, 4);
		int out = uni(rng);
		outfile << out << std::endl;
		outfile.close();
		Log.WriteToLog("MOVE=" + to_string(out));
	}

}
