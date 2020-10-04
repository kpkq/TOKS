#include "Package.h"

string Package::encodeMsg(string msg)
{
	string encodedMsg;
	for (int i = 0; i < msg.size(); i++) encodedMsg.append(bitset<8>((int)msg[i]).to_string());
	return encodedMsg;
}

string Package::decodeMsg(string encodedMsg)
{
	string decodedMsg;
	for (int i = 0; i < encodedMsg.size() / 8; i++)
	{
		int num = strtol(encodedMsg.substr(i * 8, 8).c_str(), NULL, 2);
		decodedMsg += (char)num;
	}
	return decodedMsg;
}

void Package::showPckg(string msg)
{
	for (int i = 0; i <= msg.size() / 8; i++)
	{
		string tmp = msg.substr(i * 8, 8);
		if (tmp == this->beginFlag)
			cout << tmp << "|";
		else cout << tmp << "|";
	}
}

string Package::pack(string encodedMsg)
{
	string packedMsg(encodedMsg);
	while (1)
	{
		int poz = packedMsg.find(this->beginFlag);
		if (poz != -1)
			packedMsg.insert(poz + 1, "1");
		else break;
	}
	int ones = 0;
	for (auto digit : packedMsg) if (digit == '1') ones++;
	packedMsg.append(to_string(ones % 2));
	return packedMsg.insert(0, this->beginFlag);
}

string Package::unpack(string rawData)
{
	bool parityBit = rawData[rawData.size()];
	int poz = rawData.find(this->beginFlag);
	if (poz == -1) return "";
	else rawData.erase(0, 8);
	int ones = 0;
	for (auto digit : rawData) if (digit == '1') ones++;
	if (ones % 2 != (int)parityBit) return "";
	else rawData.pop_back();
	while (1)
	{
		int poz = rawData.find(this->bitStuffed);
		if (poz != -1)
			rawData.erase(poz + 7, 1);
		else break;
	}
	return rawData;
}

Package::Package()
{
}


