#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>

#include"Financial_Instrument_Manger.h"
#include"Financial_Instrument.h"

void Financial_Instrument_Manager::processTradeStream() {
	readTradeStream();
	writeTradeResult();
}

void Financial_Instrument_Manager::readTradeStream()
{
	std::ifstream input_file(input_fileName);
	std::string rowStr;
	std::string str;


	if (input_file)
	{
		std::cout << ">>Opening input file and Processing trade streams...\n";
		while (std::getline(input_file, rowStr))
		{
			std::stringstream row(rowStr);
			std::vector <std::string> trade_row;

			while (std::getline(row, str, ','))
			{
				trade_row.push_back(str);
			}

			//check if symbol is already in manager
			itr = Financial_Instr_List.find(trade_row[1]);
			if (itr == Financial_Instr_List.end())
			{
				//and create an object of that symbol

				auto newInstrument = std::make_shared< Financial_Instrument>(
					std::stoll(trade_row[0]),
					trade_row[1],
					std::stol(trade_row[2]),
					std::stoi(trade_row[3]));

				Financial_Instr_List.insert(std::make_pair(trade_row[1], newInstrument));
			}
			else
			{
				//calculate new:volume, maxtimeGAP, max price, weightedAvgPrice

				//set current time stamp
				itr->second->setCurr_timeStamp(std::stoll(trade_row[0]));

				//set current quantity
				itr->second->setCurr_quant(std::stol(trade_row[2]));

				//set current price
				itr->second->setCurr_price(std::stol(trade_row[3]));

				//update weighted average price
				itr->second->updateWeighted_avgPrice();

				//update volume
				itr->second->updateVolume();

				//update max price
				itr->second->updateMax_price();

				//update max time gap
				itr->second->updateMax_timeGap();
			}
		}
		std::cout << ">>Trade stream processing complete!\n";
	}
	else
	{
		std::cout << ">>unable to open file\n";
	}
}


void Financial_Instrument_Manager::writeTradeResult()
{
	std::ofstream outFile(output_fileName);

	if (!outFile.bad())
	{
		std::cout << ">>Creating output file...\n";

		//add header
		outFile << "symbol," << "MaxTimeGap," << "Volume," << "WeightedAveragePrice," << "MaxPrice\n";

		//loop through map of financial instrument list
		for (itr = Financial_Instr_List.begin(); itr != Financial_Instr_List.end(); ++itr) {
			outFile << itr->first << ",";							//symbol
			outFile << itr->second->getMax_timeGap() << ",";			//max time gap
			outFile << itr->second->getVolume() << ",";				//volume
			outFile << itr->second->getWieghted_avgPrice() << ",";	//weighted average price
			outFile << itr->second->getMax_price() << "\n";			//Max Price
		}

		std::cout << ">>data successfully written to file\n";
		outFile.close();
	}
	else
	{
		std::cout << ">>unable to write file\n";
	}
}