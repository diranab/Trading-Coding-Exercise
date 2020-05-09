#ifndef FINANCIAL_INSTRUMENT_MANAGER_H
#define FINANCIAL_INSTRUMENT_MANAGER_H

#include<map>
#include<memory>


class Financial_Instrument;

class Financial_Instrument_Manager
{
private:
	std::map < std::string, std::shared_ptr<Financial_Instrument>> Financial_Instr_List;
	std::map<std::string, std::shared_ptr<Financial_Instrument>>::iterator itr;
	std::string input_fileName;
	std::string output_fileName;

private:
	void readTradeStream();
	void writeTradeResult();

public:
	Financial_Instrument_Manager()
		: input_fileName("input.csv"),
		output_fileName("output.csv")
	{}

	//read trade stream and write result in output file
	void processTradeStream();
};

#endif // !FINANCIAL_INSTRUMENT_MANAGER_H

