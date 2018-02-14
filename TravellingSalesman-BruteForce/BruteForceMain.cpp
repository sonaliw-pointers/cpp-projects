
#include"Trip.h"
#include"Printer.h"
#include"Decoder.h"

int main()
{
	Decoder inputDecoder;
	Printer outputPrinter;

	Trip *pTrip = NULL;
	while (inputDecoder.GetTrip(pTrip))
	{
		if (pTrip)
		{
			pTrip->ComputeBestPath();
			outputPrinter.Print(pTrip);
		}		
	}
	return 0;
}