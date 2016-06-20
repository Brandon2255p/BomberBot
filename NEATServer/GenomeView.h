#pragma once

#include <cmath>
#include "../SampleBot/NEAT/Neat.h"

namespace NEATServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class GenomeView : public System::Windows::Forms::Form
	{
	public:
		GenomeView();

		System::Void formClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void drawGenome(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

		void startGame();
		void gameClock();
		void updateGame();
		bool getGameRunning();

		delegate void CharacterDelegate();
		delegate PictureBox^ CharacterDelegatePB(int);
		delegate void EnemyDelegate();
		delegate void LabelDelegate();
		delegate void GenomeDelegate();

		System::Threading::Thread^ getThread();
		void setThread(System::Threading::Thread^);
		void setControls(Generic::List<bool>^);
		List<int>^ getCellX();
		List<int>^ getCellY();
		List<double>^ getCellValue();
		List<int>^ getInCell();
		List<int>^ getOutCell();
		List<double>^ getGeneWeight();
		void updateDisplay();
		List<double>^ getLabelValues();

	protected:
		~GenomeView();

	private:
		System::ComponentModel::Container ^components;


		System::Windows::Forms::PictureBox^  leftBoundary;
		System::Windows::Forms::PictureBox^  genome;
		System::Windows::Forms::Label^  playerX;
		System::Windows::Forms::Label^  playerY;
		System::Windows::Forms::Label^  enemy1X;
		System::Windows::Forms::Label^  npc2X;
		System::Windows::Forms::Label^  bias;
		System::Windows::Forms::Label^  space;
		System::Windows::Forms::Label^  left;
		System::Windows::Forms::Label^  right;
		System::Windows::Forms::Label^  population;
		System::Windows::Forms::Label^  species;
		System::Windows::Forms::Label^  genomeLabel;
		System::Windows::Forms::Label^  maxFitness;
	private: System::Windows::Forms::Label^  generation;
	private: System::Windows::Forms::Label^  fitness;
			
			 bool gameRunning;

			 List<int>^ cellX;
			 List<int>^ cellY;
			 List<double>^ cellValue;
			 List<int>^ inCell;
			 List<int>^ outCell;
			 List<double>^ geneWeight;
			 List<double>^ labelValues;

			 System::Threading::Thread^ thread;

#pragma region Windows Form Designer generated code
			 void InitializeComponent(void)
			 {
				 this->leftBoundary = (gcnew System::Windows::Forms::PictureBox());
				 this->genome = (gcnew System::Windows::Forms::PictureBox());
				 this->playerX = (gcnew System::Windows::Forms::Label());
				 this->playerY = (gcnew System::Windows::Forms::Label());
				 this->enemy1X = (gcnew System::Windows::Forms::Label());
				 this->npc2X = (gcnew System::Windows::Forms::Label());
				 this->bias = (gcnew System::Windows::Forms::Label());
				 this->space = (gcnew System::Windows::Forms::Label());
				 this->left = (gcnew System::Windows::Forms::Label());
				 this->right = (gcnew System::Windows::Forms::Label());
				 this->population = (gcnew System::Windows::Forms::Label());
				 this->species = (gcnew System::Windows::Forms::Label());
				 this->genomeLabel = (gcnew System::Windows::Forms::Label());
				 this->maxFitness = (gcnew System::Windows::Forms::Label());
				 this->generation = (gcnew System::Windows::Forms::Label());
				 this->fitness = (gcnew System::Windows::Forms::Label());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->leftBoundary))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->genome))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // leftBoundary
				 // 
				 this->leftBoundary->Location = System::Drawing::Point(-1, 0);
				 this->leftBoundary->Margin = System::Windows::Forms::Padding(2);
				 this->leftBoundary->Name = L"leftBoundary";
				 this->leftBoundary->Size = System::Drawing::Size(1, 1);
				 this->leftBoundary->TabIndex = 4;
				 this->leftBoundary->TabStop = false;
				 // 
				 // genome
				 // 
				 this->genome->BackColor = System::Drawing::Color::White;
				 this->genome->Location = System::Drawing::Point(7, 7);
				 this->genome->Margin = System::Windows::Forms::Padding(2);
				 this->genome->Name = L"genome";
				 this->genome->Size = System::Drawing::Size(371, 181);
				 this->genome->TabIndex = 19;
				 this->genome->TabStop = false;
				 this->genome->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GenomeView::drawGenome);
				 // 
				 // playerX
				 // 
				 this->playerX->BackColor = System::Drawing::Color::White;
				 this->playerX->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->playerX->Location = System::Drawing::Point(7, 15);
				 this->playerX->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->playerX->Name = L"playerX";
				 this->playerX->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->playerX->Size = System::Drawing::Size(42, 13);
				 this->playerX->TabIndex = 20;
				 this->playerX->Text = L"playerX";
				 this->playerX->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // playerY
				 // 
				 this->playerY->BackColor = System::Drawing::Color::White;
				 this->playerY->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->playerY->Location = System::Drawing::Point(7, 49);
				 this->playerY->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->playerY->Name = L"playerY";
				 this->playerY->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->playerY->Size = System::Drawing::Size(42, 13);
				 this->playerY->TabIndex = 21;
				 this->playerY->Text = L"playerY";
				 this->playerY->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // enemy1X
				 // 
				 this->enemy1X->BackColor = System::Drawing::Color::White;
				 this->enemy1X->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->enemy1X->Location = System::Drawing::Point(7, 83);
				 this->enemy1X->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->enemy1X->Name = L"enemy1X";
				 this->enemy1X->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->enemy1X->Size = System::Drawing::Size(42, 13);
				 this->enemy1X->TabIndex = 22;
				 this->enemy1X->Text = L"npc1X";
				 this->enemy1X->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // npc2X
				 // 
				 this->npc2X->BackColor = System::Drawing::Color::White;
				 this->npc2X->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->npc2X->Location = System::Drawing::Point(7, 117);
				 this->npc2X->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->npc2X->Name = L"npc2X";
				 this->npc2X->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->npc2X->Size = System::Drawing::Size(42, 13);
				 this->npc2X->TabIndex = 23;
				 this->npc2X->Text = L"npc2X";
				 this->npc2X->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // bias
				 // 
				 this->bias->BackColor = System::Drawing::Color::White;
				 this->bias->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->bias->Location = System::Drawing::Point(7, 164);
				 this->bias->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->bias->Name = L"bias";
				 this->bias->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->bias->Size = System::Drawing::Size(42, 13);
				 this->bias->TabIndex = 24;
				 this->bias->Text = L"bias";
				 this->bias->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // space
				 // 
				 this->space->BackColor = System::Drawing::Color::White;
				 this->space->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->space->Location = System::Drawing::Point(341, 30);
				 this->space->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->space->Name = L"space";
				 this->space->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->space->Size = System::Drawing::Size(37, 13);
				 this->space->TabIndex = 25;
				 this->space->Text = L"Space";
				 // 
				 // left
				 // 
				 this->left->BackColor = System::Drawing::Color::White;
				 this->left->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->left->Location = System::Drawing::Point(341, 88);
				 this->left->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->left->Name = L"left";
				 this->left->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->left->Size = System::Drawing::Size(37, 13);
				 this->left->TabIndex = 26;
				 this->left->Text = L"Left";
				 // 
				 // right
				 // 
				 this->right->BackColor = System::Drawing::Color::White;
				 this->right->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->right->Location = System::Drawing::Point(341, 153);
				 this->right->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->right->Name = L"right";
				 this->right->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->right->Size = System::Drawing::Size(37, 13);
				 this->right->TabIndex = 27;
				 this->right->Text = L"Right";
				 // 
				 // population
				 // 
				 this->population->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->population->ForeColor = System::Drawing::Color::White;
				 this->population->Location = System::Drawing::Point(383, 7);
				 this->population->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->population->Name = L"population";
				 this->population->Size = System::Drawing::Size(300, 16);
				 this->population->TabIndex = 28;
				 this->population->Text = L"Population: ";
				 // 
				 // species
				 // 
				 this->species->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->species->ForeColor = System::Drawing::Color::White;
				 this->species->Location = System::Drawing::Point(384, 56);
				 this->species->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->species->Name = L"species";
				 this->species->Size = System::Drawing::Size(300, 16);
				 this->species->TabIndex = 30;
				 this->species->Text = L"Species: ";
				 // 
				 // genomeLabel
				 // 
				 this->genomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->genomeLabel->ForeColor = System::Drawing::Color::White;
				 this->genomeLabel->Location = System::Drawing::Point(384, 72);
				 this->genomeLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->genomeLabel->Name = L"genomeLabel";
				 this->genomeLabel->Size = System::Drawing::Size(300, 16);
				 this->genomeLabel->TabIndex = 31;
				 this->genomeLabel->Text = L"Genome: ";
				 // 
				 // maxFitness
				 // 
				 this->maxFitness->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->maxFitness->ForeColor = System::Drawing::Color::White;
				 this->maxFitness->Location = System::Drawing::Point(384, 121);
				 this->maxFitness->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->maxFitness->Name = L"maxFitness";
				 this->maxFitness->Size = System::Drawing::Size(300, 16);
				 this->maxFitness->TabIndex = 33;
				 this->maxFitness->Text = L"Max Fitness: ";
				 // 
				 // generation
				 // 
				 this->generation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->generation->ForeColor = System::Drawing::Color::White;
				 this->generation->Location = System::Drawing::Point(384, 40);
				 this->generation->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->generation->Name = L"generation";
				 this->generation->Size = System::Drawing::Size(300, 16);
				 this->generation->TabIndex = 34;
				 this->generation->Text = L"Generation: ";
				 // 
				 // fitness
				 // 
				 this->fitness->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->fitness->ForeColor = System::Drawing::Color::White;
				 this->fitness->Location = System::Drawing::Point(384, 105);
				 this->fitness->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->fitness->Name = L"fitness";
				 this->fitness->Size = System::Drawing::Size(300, 16);
				 this->fitness->TabIndex = 35;
				 this->fitness->Text = L"Fitness: ";
				 // 
				 // GenomeView
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::Color::Black;
				 this->ClientSize = System::Drawing::Size(778, 206);
				 this->Controls->Add(this->fitness);
				 this->Controls->Add(this->generation);
				 this->Controls->Add(this->maxFitness);
				 this->Controls->Add(this->genomeLabel);
				 this->Controls->Add(this->species);
				 this->Controls->Add(this->population);
				 this->Controls->Add(this->right);
				 this->Controls->Add(this->left);
				 this->Controls->Add(this->space);
				 this->Controls->Add(this->bias);
				 this->Controls->Add(this->npc2X);
				 this->Controls->Add(this->enemy1X);
				 this->Controls->Add(this->playerY);
				 this->Controls->Add(this->playerX);
				 this->Controls->Add(this->genome);
				 this->Controls->Add(this->leftBoundary);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Margin = System::Windows::Forms::Padding(2);
				 this->MaximizeBox = false;
				 this->Name = L"GenomeView";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"NEAT";
				 this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &GenomeView::formClosing);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->leftBoundary))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->genome))->EndInit();
				 this->ResumeLayout(false);

			 }
#pragma endregion

	};
}
