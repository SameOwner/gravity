#include "SceneManager.h"
#include"Scenes.h"

//ローディングシーンから開始
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING) {
	//利用するシーンを作成し、シーンリストに追加する
	scenes_[SceneType::SCENE_LOADING] = std::make_shared<LoadingScene>();
	scenes_[SceneType::SCENE_TITLE] = std::make_shared<TitleScene>();
	scenes_[SceneType::SCENE_GAMEPLAY] = std::make_shared<GamePlayScene>();
	scenes_[SceneType::SCENE_CLEAR] = std::make_shared<GameClearScene>();
	scenes_[SceneType::SCENE_GAMEOVER] = std::make_shared<GameOverScene>();
}

void SceneManager::start() {
	scenes_[currentScene_]->start();
}

void SceneManager::update(float deltaTime) {
	scenes_[currentScene_]->update(deltaTime);

}

void SceneManager::draw() {
	scenes_[currentScene_]->draw();
}

//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next();

}

//次のシーンへ遷移する

void SceneManager::next() {
	//シーンを終了して
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//次のシーンを開始する
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
