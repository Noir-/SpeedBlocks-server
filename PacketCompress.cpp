#include "PacketCompress.h"
#include "network.h"

void PacketCompress::extract(PlayfieldHistory& history) {
	tmpcount=0;
	bitcount=0;
	sf::Uint8 counter=0;
	sf::Uint8 endy=0;
	sf::Uint8 temp=0;
	int y;
	getBits(endy, 5);
	for (int c=0; c<endy; c++) {
		for (int x=0; x<10; x++)
			history.square[21-c][x]=8;
		getBits(temp, 4);
		history.square[21-c][temp]=0;
	}
	for (int x=0; x<10; x++) {
		counter=0;
		getBits(counter, 5);
		for (y=0; y<counter; y++)
			history.square[y][x]=0;
		for (; y<22-endy; y++)
			getBits(history.square[y][x], 3);
	}
}

void PacketCompress::getBits(sf::Uint8& byte, sf::Uint8 bits) {
	sf::Uint8 temp=0;
	temp = tmp[tmpcount]>>bitcount | temp;
	bitcount+=bits;
	if (bitcount>7) {
		bitcount-=8;
		tmpcount++;
		if (bitcount>0)
			temp = tmp[tmpcount]<<(bits-bitcount) | temp;
	}
	temp = temp<<(8-bits);
	temp = temp>>(8-bits);
	byte=temp;
}