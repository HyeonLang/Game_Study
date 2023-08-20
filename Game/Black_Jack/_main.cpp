#include "utility.h"
#include "BlackJack.h"

int main() {
	BlackJack b;
	b.Init();

	while (1) {
		b.Update();
		b.Render();
		if (b.GetIsGameOver()) break;
	}

	b.Destroy();


}