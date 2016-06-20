#include "GenomeView.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace NEATServer;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	NEATServer::GenomeView form;
	Application::Run(%form);
}


GenomeView::GenomeView() {
	InitializeComponent();

	cellX = gcnew List<int>();
	cellY = gcnew List<int>();
	cellValue = gcnew List<double>();
	inCell = gcnew List<int>();
	outCell = gcnew List<int>();
	geneWeight = gcnew List<double>();
	labelValues = gcnew List<double>();

	startGame();
}

GenomeView::~GenomeView() {
	if (components)
		delete components;
}


void GenomeView::setControls(Generic::List<bool>^ controls) {
	
	return;
}

void GenomeView::startGame() {
	gameRunning = true;
}

void GenomeView::gameClock() {
	while (gameRunning) {
		updateGame();
		thread->Sleep(10);
	}
}

void GenomeView::updateGame() {
	if (gameRunning) {
		
	}
}

System::Void GenomeView::formClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	thread->Abort();
}

System::Threading::Thread^ GenomeView::getThread() {
	return thread;
}

void GenomeView::setThread(System::Threading::Thread^ t) {
	thread = t;
	return;
}

bool GenomeView::getGameRunning() {
	return gameRunning;
}

List<int>^ GenomeView::getCellX() {
	return cellX;
}

List<int>^ GenomeView::getCellY() {
	return cellY;
}

List<double>^ GenomeView::getCellValue() {
	return cellValue;
}

List<int>^ GenomeView::getInCell() {
	return inCell;
}

List<int>^ GenomeView::getOutCell() {
	return outCell;
}

List<double>^ GenomeView::getGeneWeight() {
	return geneWeight;
}

List<double>^ GenomeView::getLabelValues() {
	return labelValues;
}

// top left = (0,0) / bottom right = (370,180)
System::Void GenomeView::drawGenome(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	int width = 9;
	int height = 9;

	Pen^ blackPen = gcnew Pen(Color::Black, 1);
	Pen^ greenPen = gcnew Pen(Color::Green, 1);
	Pen^ redPen = gcnew Pen(Color::Red, 1);
	Pen^ greyPen = gcnew Pen(Color::LightGray, 1);
	SolidBrush^ whiteBrush = gcnew SolidBrush(System::Drawing::Color::White);
	SolidBrush^ blackBrush = gcnew SolidBrush(System::Drawing::Color::Black);

	for (int i = 0; i < inCell->Count; i++) {
		Point point1 = Point(cellX[inCell[i]] + 9, cellY[inCell[i]] + 4);
		Point point2 = Point(cellX[outCell[i]], cellY[outCell[i]] + 4);
		if (geneWeight[i] == 0)
			e->Graphics->DrawLine(greyPen, point1, point2);
	}

	for (int i = 0; i < inCell->Count; i++) {
		Point point1 = Point(cellX[inCell[i]] + 9, cellY[inCell[i]] + 4);
		Point point2 = Point(cellX[outCell[i]], cellY[outCell[i]] + 4);
		if (geneWeight[i] > 0)
			e->Graphics->DrawLine(greenPen, point1, point2);
		else if (geneWeight[i] < 0)
			e->Graphics->DrawLine(redPen, point1, point2);
	}


	for (int i = 0; i < cellX->Count; i++) {
		if (cellX[i] > 0) {
			if (cellValue[i] > 0)
				e->Graphics->FillRectangle(blackBrush, cellX[i], cellY[i], width, height);
			else
				e->Graphics->FillRectangle(whiteBrush, cellX[i], cellY[i], width, height);
			e->Graphics->DrawRectangle(blackPen, cellX[i], cellY[i], width, height);
		}
	}
}

void GenomeView::updateDisplay() {
	if (genome->InvokeRequired) {
		GenomeDelegate^ d = gcnew GenomeDelegate(this, &GenomeView::updateDisplay);
		this->Invoke(d);
	}
	else {
		genome->Invalidate();

		if (labelValues[0] == 0)
			population->Text = "Population: N/A";
		else
			population->Text = "Population: " + Convert::ToString(labelValues[0]);

		generation->Text = "Generation: " + Convert::ToString(labelValues[1]);
		species->Text = "Species: " + Convert::ToString(labelValues[2]);
		genomeLabel->Text = "Genome: " + Convert::ToString(labelValues[3]);

		if (labelValues[4] == 0)
			fitness->Text = "Fitness: N/A";
		else
			fitness->Text = "Fitness: " + Convert::ToString(labelValues[4]);

		if (labelValues[5] == 0)
			maxFitness->Text = "Max Fitness: N/A";
		else
			maxFitness->Text = "Max Fitness: " + Convert::ToString(labelValues[5]);
	}
}
