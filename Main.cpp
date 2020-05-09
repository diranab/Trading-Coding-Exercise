#include <iostream>

#include"Financial_Instrument_Manger.h"
#include"Financial_Instrument.h"





int main()
{
	std::unique_ptr<Financial_Instrument_Manager> tradeManager(new Financial_Instrument_Manager("QuantLab_codingExercise\\input.csv","output.csv"));
	tradeManager->processTradeStream();


	return 0;
}