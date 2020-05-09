#ifndef FINANCIAL_INSTRUMENT_H
#define FINANCIAL_INSTRUMENT_H

#include<string>
#include"Financial_Instrument_Manger.h"

class Financial_Instrument
{
friend class Financial_Instrument_Manager;
private:
	std::string symbol;
	long long curr_timeStamp;
	long curr_quant;
	int curr_price;

private:
	long volume;
	long long prev_timeStamp;
	long long max_timeGap;
	int max_price;
	int weighted_avgPrice;


public:
	//constructor for new symbol
	Financial_Instrument(long long curr_timeStamp, std::string symbol, long curr_quant, int curr_price);


private:
	//setters for current, quantity and price
	void setCurr_quant(long quantity);
	void setCurr_price(int price);
	void setCurr_timeStamp(long long timestamp);

private:
	//update functions
	void updateVolume();
	void updateMax_timeGap();
	void updateMax_price();
	void updateWeighted_avgPrice();

private:
	//getter functions
	long getVolume();
	long long getMax_timeGap();
	int getMax_price();
	int getWieghted_avgPrice();
	std::string getSymbol();
};

#endif // !FINANCIAL_INSTRUMENT_H
