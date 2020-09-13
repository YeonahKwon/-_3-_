#include <bangtal.h>
using namespace bangtal;

int main()
{
	//1. 장면 생성
	ScenePtr scene1 = Scene::create("룸1", "images/배경-1.png");
	ScenePtr scene2 = Scene::create("룸2", "images/배경-2.png");


	//3. 문을 생성한다
	auto open1 = false;
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);

	//4. 문을 클릭하면 이동  //lambda funtion
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open1 == true) { //열린상태
			scene2->enter();
			showMessage("나가는 문이 어디있지...");
		}
		else { //닫힌상태
			door1->setImage("images/문-오른쪽-열림.png");
			open1 = true;
		}
		return true;
		});

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false, locked3 = true;
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 940, 280);
	door3->setScale(0.3f);

	auto flowerpot_moved = false; //화분생성
	auto flowerpot = Object::create("images/화분.png", scene2, 850, 170);
	flowerpot->setScale(1.5f);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene2, 700, 170);
				flowerpot_moved = true;
				showMessage("문을 찾았다!");
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene2, 1000, 170);
				flowerpot_moved = true;
				showMessage("문을 찾았다!");
			}
		}
		return true;
		});

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open3 == true) { //열린상태
			endGame();
		}
		else {                //닫힌상태
			door3->setImage("images/문-오른쪽-열림.png");
			open3 = true;
			showMessage("이제 나갈 수 있다.");
		}
		return true;
		});

	//게임 시작
	startGame(scene1);

	return 0;
}