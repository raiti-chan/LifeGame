// lifegame_c8x8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lifegame_c8x8.h"

int main() {
	std::random_device rd;
	mt = new std::mt19937_64(rd());

	ulong bord = randULong();
	bord = 0b1111111110000001101111011010010110100101101111011000000111111111ULL;
	std::cout << bord << std::endl;
	getchar();

	outBord(bord);

	while (getchar() != 'e') {
		bord = nextGeneration(bord);
		outBord(bord);
	}

	getchar();
	delete mt;
	return 0;
}


ulong nextGeneration(ulong bord) {

	ulong shift[8];//ずらしたビットボードを格納する配列

	shift[0] = (bord & 0xFEFEFEFEFEFEFE00ULL) >> 9;//左上にずらしたビットボード
	shift[1] = (bord & 0xFFFFFFFFFFFFFF00ULL) >> 8;//上にずらしたビットボード
	shift[2] = (bord & 0x7F7F7F7F7F7F7F00ULL) >> 7;//右上にずらしたビットボード

	shift[3] = (bord & 0xFEFEFEFEFEFEFEFEULL) >> 1;//左にずらしたビットボード
	shift[4] = (bord & 0x7F7F7F7F7F7F7F7FULL) << 1;//右にずらしたビットボード

	shift[5] = (bord & 0x00FEFEFEFEFEFEFEULL) << 7;//左下にずらしたビットボード
	shift[6] = (bord & 0x00FFFFFFFFFFFFFFULL) << 8;//下にずらしたビットボード
	shift[7] = (bord & 0x007F7F7F7F7F7F7FULL) << 9;//右下にずらしたビットボード

	ulong count[9];//位置の数を格納するボード

	//周りの数に対応するビットを立てる
	//左上、上を合わせ0,1,2を求める
	count[0] = ~(shift[0] | shift[1]);
	count[1] = shift[0] ^ shift[1];
	count[2] = shift[0] & shift[1];

	//前回の結果に右上を合わせ3までを求める
	count[3] = shift[2] & count[2];
	count[2] = (count[2] & ~shift[2]) | (count[1] & shift[2]);
	count[1] = (count[1] & ~shift[2]) | (count[0] & shift[2]);
	count[0] = count[0] & ~shift[2];

	//前回の結果に左を合わせ4までを求める
	count[4] = shift[3] & count[3];
	count[3] = (count[3] & ~shift[3]) | (count[2] & shift[3]);
	count[2] = (count[2] & ~shift[3]) | (count[1] & shift[3]);
	count[1] = (count[1] & ~shift[3]) | (count[0] & shift[3]);
	count[0] = count[0] & ~shift[3];

	//前回の結果に右を合わせて5までを求める
	count[5] = shift[4] & count[4];
	count[4] = (count[4] & ~shift[4]) | (count[3] & shift[4]);
	count[3] = (count[3] & ~shift[4]) | (count[2] & shift[4]);
	count[2] = (count[2] & ~shift[4]) | (count[1] & shift[4]);
	count[1] = (count[1] & ~shift[4]) | (count[0] & shift[4]);
	count[0] = count[0] & ~shift[4];

	//前回の結果に左下を合わせて6までを求める
	count[6] = shift[5] & count[5];
	count[5] = (count[5] & ~shift[5]) | (count[4] & shift[5]);
	count[4] = (count[4] & ~shift[5]) | (count[3] & shift[5]);
	count[3] = (count[3] & ~shift[5]) | (count[2] & shift[5]);
	count[2] = (count[2] & ~shift[5]) | (count[1] & shift[5]);
	count[1] = (count[1] & ~shift[5]) | (count[0] & shift[5]);
	count[0] = count[0] & ~shift[5];

	//前回の結果に下を合わせて7までを求める
	count[7] = shift[6] & count[6];
	count[6] = (count[6] & ~shift[6]) | (count[5] & shift[6]);
	count[5] = (count[5] & ~shift[6]) | (count[4] & shift[6]);
	count[4] = (count[4] & ~shift[6]) | (count[3] & shift[6]);
	count[3] = (count[3] & ~shift[6]) | (count[2] & shift[6]);
	count[2] = (count[2] & ~shift[6]) | (count[1] & shift[6]);
	count[1] = (count[1] & ~shift[6]) | (count[0] & shift[6]);
	count[0] = count[0] & ~shift[6];

	//前回の結果に右下を合わせて8までを求める
	count[8] = shift[7] & count[7];
	count[7] = (count[7] & ~shift[7]) | (count[6] & shift[7]);
	count[5] = (count[5] & ~shift[7]) | (count[4] & shift[7]);
	count[4] = (count[4] & ~shift[7]) | (count[3] & shift[7]);
	count[3] = (count[3] & ~shift[7]) | (count[2] & shift[7]);
	count[2] = (count[2] & ~shift[7]) | (count[1] & shift[7]);
	count[1] = (count[1] & ~shift[7]) | (count[0] & shift[7]);
	count[0] = count[0] & ~shift[7];

	return (~bord & count[3]) | (bord & (count[2] | count[3]));
}

ulong nextGenerationV2(ulong bord) {
	ulong shift[8];//ずらしたビットボードを格納する配列

	ulong top = bord & 0xFF00000000000000ULL,
		bottom = bord & 0x00000000000000FFULL,
		left = bord & 0x8080808080808080ULL,
		right = bord & 0x0101010101010101ULL;


	shift[0] = (bord & 0xFEFEFEFEFEFEFE00ULL) >> 9;//左上にずらしたビットボード
	shift[1] = (bord & 0xFFFFFFFFFFFFFF00ULL) >> 8;//上にずらしたビットボード
	shift[2] = (bord & 0x7F7F7F7F7F7F7F00ULL) >> 7;//右上にずらしたビットボード

	shift[3] = (bord & 0xFEFEFEFEFEFEFEFEULL) >> 1;//左にずらしたビットボード
	shift[4] = (bord & 0x7F7F7F7F7F7F7F7FULL) << 1;//右にずらしたビットボード

	shift[5] = (bord & 0x00FEFEFEFEFEFEFEULL) << 7;//左下にずらしたビットボード
	shift[6] = (bord & 0x00FFFFFFFFFFFFFFULL) << 8;//下にずらしたビットボード
	shift[7] = (bord & 0x007F7F7F7F7F7F7FULL) << 9;//右下にずらしたビットボード

	ulong count[9];//位置の数を格納するボード

				   //周りの数に対応するビットを立てる
				   //左上、上を合わせ0,1,2を求める
	count[0] = ~(shift[0] | shift[1]);
	count[1] = shift[0] ^ shift[1];
	count[2] = shift[0] & shift[1];

	//前回の結果に右上を合わせ3までを求める
	count[3] = shift[2] & count[2];
	count[2] = (count[2] & ~shift[2]) | (count[1] & shift[2]);
	count[1] = (count[1] & ~shift[2]) | (count[0] & shift[2]);
	count[0] = count[0] & ~shift[2];

	//前回の結果に左を合わせ4までを求める
	count[4] = shift[3] & count[3];
	count[3] = (count[3] & ~shift[3]) | (count[2] & shift[3]);
	count[2] = (count[2] & ~shift[3]) | (count[1] & shift[3]);
	count[1] = (count[1] & ~shift[3]) | (count[0] & shift[3]);
	count[0] = count[0] & ~shift[3];

	//前回の結果に右を合わせて5までを求める
	count[5] = shift[4] & count[4];
	count[4] = (count[4] & ~shift[4]) | (count[3] & shift[4]);
	count[3] = (count[3] & ~shift[4]) | (count[2] & shift[4]);
	count[2] = (count[2] & ~shift[4]) | (count[1] & shift[4]);
	count[1] = (count[1] & ~shift[4]) | (count[0] & shift[4]);
	count[0] = count[0] & ~shift[4];

	//前回の結果に左下を合わせて6までを求める
	count[6] = shift[5] & count[5];
	count[5] = (count[5] & ~shift[5]) | (count[4] & shift[5]);
	count[4] = (count[4] & ~shift[5]) | (count[3] & shift[5]);
	count[3] = (count[3] & ~shift[5]) | (count[2] & shift[5]);
	count[2] = (count[2] & ~shift[5]) | (count[1] & shift[5]);
	count[1] = (count[1] & ~shift[5]) | (count[0] & shift[5]);
	count[0] = count[0] & ~shift[5];

	//前回の結果に下を合わせて7までを求める
	count[7] = shift[6] & count[6];
	count[6] = (count[6] & ~shift[6]) | (count[5] & shift[6]);
	count[5] = (count[5] & ~shift[6]) | (count[4] & shift[6]);
	count[4] = (count[4] & ~shift[6]) | (count[3] & shift[6]);
	count[3] = (count[3] & ~shift[6]) | (count[2] & shift[6]);
	count[2] = (count[2] & ~shift[6]) | (count[1] & shift[6]);
	count[1] = (count[1] & ~shift[6]) | (count[0] & shift[6]);
	count[0] = count[0] & ~shift[6];

	//前回の結果に右下を合わせて8までを求める
	count[8] = shift[7] & count[7];
	count[7] = (count[7] & ~shift[7]) | (count[6] & shift[7]);
	count[5] = (count[5] & ~shift[7]) | (count[4] & shift[7]);
	count[4] = (count[4] & ~shift[7]) | (count[3] & shift[7]);
	count[3] = (count[3] & ~shift[7]) | (count[2] & shift[7]);
	count[2] = (count[2] & ~shift[7]) | (count[1] & shift[7]);
	count[1] = (count[1] & ~shift[7]) | (count[0] & shift[7]);
	count[0] = count[0] & ~shift[7];

	return (~bord & count[3]) | (bord & (count[2] | count[3]));
}

ulong randULong() {
	return (*mt)();
}

void outBord(ulong bord) {
	std::stringstream ss;
	ss << static_cast<std::bitset<64>> (bord);
	std::string bordtxt = ss.str();
	std::cout << bordtxt << std::endl;
	//getchar();
	std::cout << std::endl;

	char chars[64] = {};
	bordtxt._Copy_s(chars, 64, 64, 0);
	int count = 0;
	for (int i = 0; i < 64; i++) {
		std::cout << (chars[i] == '1' ?"■" : "□");
		count++;
		if (count == 8) {
			std::cout << std::endl;
			count = 0;
		}
	}
}