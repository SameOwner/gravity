#include"src/Game/MyGame.h"
#include"src/Define.h"
#pragma comment(linker,"/entry:mainCRTStartup")
#include"src/Method/MethodExecutor.h"
#include"src/Method/FunctionExecutor.h"


int main() {
	//MethodExecutor<void(int, int)> c;
	//std::function<void(int, int)> b = [](int a, int b) {OutputDebugString((std::to_string(a + b).c_str())); };
	//c += b;

	//c.execute(1, 3);

	//FunctionExecutor<void,int,float,std::string> a;
	////a = MethodExecutor<int, float, std::string>();
	//std::function<void(int, float, std::string)> s= [](int x, float y, std::string z) {OutputDebugString(z.c_str()); };
	//a += s;
	//
	//a -= s;

	////a.add([](int x, float y, std::string z) {OutputDebugString(z.c_str()); });
	////a.add([](int x,float y,std::string z) {OutputDebugString((z+"momomomo").c_str()); });
	//a.execute(2, 3.0f, "‚±‚à");

	return MyGame(Vector2{ (float)WINDOW_WIDTH,(float)WINDOW_HEIGHT }, sizeRate).run();
	//return Game(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}
