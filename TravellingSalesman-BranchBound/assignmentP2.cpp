// assignmentP2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InputFileDecoder.h"
#include "OutputPrinter.h"

int main(int argc, char *argv[])
{
	if (argc != 3) // argc should be 3 for correct execution
				   // We print argv[0] assuming it is the program name
		cout << "usage: " << argv[0] << " <file path>/<input file name> <output file name> \n";
	else
	{
		ifstream inputFile(argv[1]);
		if (!inputFile)
		{
			cout << "Unable to open " << argv[1] << " for reading.\n";
			return(1);
		}
		ofstream outputFile(argv[2]);
		if (!outputFile)
		{
			cout << "Unable to open " << argv[1] << " for writing.\n";
			return(1);
		}
	}

	InputFileDecoder *pFileDecoder = new InputFileDecoder(argv[1]);
	OutputPrinter	*pOutputPrinter = new OutputPrinter(argv[2]);

	if (pFileDecoder && pOutputPrinter)
	{
		Tour *pTour = NULL;
		while (pFileDecoder->GetTour(pTour))
		{
			if (pTour)
			{
				pTour->ComputeBestPath();
				pOutputPrinter->Print(pTour);
			}
		}
	}

	delete pFileDecoder; pFileDecoder = NULL;
	delete pOutputPrinter; pOutputPrinter = NULL;
    return 0;
}

