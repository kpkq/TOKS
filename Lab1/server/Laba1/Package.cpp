#include "Package.h"
#define PACKET_SIZE 64
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

vector<string> Package::pack(string encodedMsg)
{
	vector<string> packs;
	for (int i = 0; i <= encodedMsg.size() / PACKET_SIZE; i++)
	{
		packs.push_back("");
		string packedMsg(encodedMsg.substr(i*PACKET_SIZE, PACKET_SIZE));
		while (1)
		{
			int poz = packedMsg.find(this->beginFlag);
			if (poz != -1)
				packedMsg.insert(poz + 1, "1");
			else break;
		}
		while (packedMsg.size() != PACKET_SIZE + 8) packedMsg.push_back('0');
		int ones = 0;
		for (auto digit : packedMsg) if (digit == '1') ones++;
		packedMsg.insert(0, this->beginFlag);
		packs[i] = Package::decodeMsg(packedMsg);
		packs[i].insert(1, to_string(ones % 2));
	}
	return packs;
}

string Package::unpack(string rawData)
{
	int parityBit = (int)Package::decodeMsg(rawData.substr(8, 8))[0] - 48;
	rawData.erase(8, 8);
	int poz = rawData.find(this->beginFlag);
	if (poz == -1) return "";
	else rawData.erase(0, 8);
	int ones = 0;
	for (auto digit : rawData) if (digit == '1') ones++;
	if (ones % 2 != parityBit) return "";
	while (1)
	{
		int poz = rawData.find(this->bitStuffed);
		if (poz != -1)
		{
			rawData.erase(poz + 7, 1);
			rawData.push_back('0');
		}
		else break;
	}
	return rawData;
}

Package::Package()
{
}


