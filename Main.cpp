#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <utility>
#include <stdlib.h>
#include <stdio.h>



class Financial_Instrument
{
private:
	long long curr_timeStamp;
	long long prev_timeStamp;
	long curr_quant;
	int curr_price;
	
private:
	std::string symbol;
	long volume;
	long long max_timeGap;
	int max_price;
	int weighted_avgPrice;
	friend class Financial_Instrument_Manager;

public:
	//constructor for new symbol
	Financial_Instrument(long long curr_timeStamp, std::string symbol, long curr_quant, int curr_price)
		: symbol(symbol),
		curr_timeStamp(curr_timeStamp),
		curr_quant(curr_quant),
		curr_price(curr_price),
		max_timeGap(0),
		max_price(curr_price),
		volume(curr_quant),
		weighted_avgPrice(curr_price),
		prev_timeStamp(curr_timeStamp)
	{}

private: 
	//setters for current quantity and price
	void setCurr_quant(long quantity) {
		curr_quant = quantity;
	}

	void setCurr_price(int price) {
		curr_price = price;
	}

	void setCurr_timeStamp(long long timestamp) {
		curr_timeStamp = timestamp;
	}

public:
	std::string getSymbol();

	void updateVolume() { volume += curr_quant; };
	long getVolume();

	void updateMax_timeGap() {
		if (curr_timeStamp - prev_timeStamp > max_timeGap)
		{
			max_timeGap = curr_timeStamp - prev_timeStamp;
		}

		prev_timeStamp = curr_timeStamp;
	};
	
	long long getMax_timeGap();

	void updateMax_price() {
		if (curr_price > max_price)
			max_price = curr_price;
	};

	int getMax_price();

	void updateWeighted_avgPrice() {
		weighted_avgPrice = ((weighted_avgPrice * volume) + (curr_price * curr_quant)) / (volume + curr_quant);
	};

	int getWieghted_avgPrice();
};

std::string Financial_Instrument::getSymbol() { return symbol; }
long Financial_Instrument::getVolume() {return volume;}
long long Financial_Instrument::getMax_timeGap() { return max_timeGap; }
int Financial_Instrument::getMax_price() { return max_price; }
int Financial_Instrument::getWieghted_avgPrice() { return weighted_avgPrice; }




class Financial_Instrument_Manager
{
private:
	std::map < std::string, std::shared_ptr<Financial_Instrument>> Financial_Instr_List;
	std::map<std::string, std::shared_ptr<Financial_Instrument>>::iterator itr;
	std::string input_fileName;
	std::string output_fileName;
	//input file(path)
	//output file(path)


public:
	Financial_Instrument_Manager(std::string input_file, std::string output_file) 
		: input_fileName(input_file),
		output_fileName(output_file)
	{}

	void readTradeStream();
	void writeTradeResult();

};

void Financial_Instrument_Manager::readTradeStream()
{
	std::ifstream input_file(input_fileName);
	std::string rowStr;
	std::string str;


	if (input_file)
	{
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
			else				//calculate new:volume, maxtimeGAP, max price, weightedAvgPrice
			{
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
	}
	else
	{
		std::cout << "unable to open file\n";
	}
}

void Financial_Instrument_Manager::writeTradeResult()
{
	std::ofstream outFile("QuantLab_codingExercise\\output.csv");

	if (!outFile.bad())
	{
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

		std::cout << "data successfully written to file\n";
		outFile.close();
	}
	else
	{
		std::cout << "unable to write file\n";
	}
}



int main()
{
	std::unique_ptr<Financial_Instrument_Manager> tradeManager(new Financial_Instrument_Manager("QuantLab_codingExercise\\input.csv","output.csv"));
	tradeManager->readTradeStream();
	tradeManager->writeTradeResult();

	return 0;
}