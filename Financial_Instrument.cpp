#include"Financial_Instrument.h"

Financial_Instrument::Financial_Instrument(long long curr_timeStamp, std::string symbol, long curr_quant, int curr_price)
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

std::string Financial_Instrument::getSymbol() { return symbol; }
long Financial_Instrument::getVolume() { return volume; }
long long Financial_Instrument::getMax_timeGap() { return max_timeGap; }
int Financial_Instrument::getMax_price() { return max_price; }
int Financial_Instrument::getWieghted_avgPrice() { return weighted_avgPrice; }
void Financial_Instrument::updateVolume() { volume += curr_quant; };
void Financial_Instrument::updateMax_timeGap() {
	if (curr_timeStamp - prev_timeStamp > max_timeGap)
	{
		max_timeGap = curr_timeStamp - prev_timeStamp;
	}

	prev_timeStamp = curr_timeStamp;
};
void Financial_Instrument::updateMax_price() {
	if (curr_price > max_price)
		max_price = curr_price;
};
void Financial_Instrument::updateWeighted_avgPrice() {
	weighted_avgPrice = ((weighted_avgPrice * volume) + (curr_price * curr_quant)) / (volume + curr_quant);
};

void Financial_Instrument::setCurr_quant(long quantity) { curr_quant = quantity; }
void Financial_Instrument::setCurr_price(int price) { curr_price = price; }
void Financial_Instrument::setCurr_timeStamp(long long timestamp) { curr_timeStamp = timestamp; }