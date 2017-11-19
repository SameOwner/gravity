#include"src/Game/MyGame.h"
#include"src/Define.h"
#pragma comment(linker,"/entry:mainCRTStartup")


int main() {
	MyGame(Vector2{ (float)WINDOW_WIDTH,(float)WINDOW_HEIGHT }, sizeRate).run();
	//return Game(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}