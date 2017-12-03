#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	//各種リソースのロードを行う
	LoadSprite();
	LoadModel();
	LoadEffect();
	LoadFont();
	LoadBGM();
	LoadSE();
	LoadEtcetera();

	isEnd_ = true;
}

void LoadingScene::update(float deltaTime) {

}

void LoadingScene::draw() const {

}

void LoadingScene::end() {

}

void LoadingScene::LoadSprite()
{
	std::string defaultPath = "res/Sprite/";//全リソース共通パス

}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//全リソース共通パス

	Model::GetInstance().Load(defaultPath + "alicia/model.mv1", MODEL_ID::MODEL_PLAYER);

	std::list<std::string> anims{
		defaultPath + "alicia/idle.mv1",
		defaultPath + "alicia/run.mv1",
		defaultPath + "alicia/jump_up.mv1",
		defaultPath + "alicia/float.mv1",
		defaultPath + "alicia/jump_down.mv1",
		defaultPath + "alicia/slide.mv1",
		defaultPath + "alicia/fly.mv1"
	};
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_PLAYER, anims);
}

void LoadingScene::LoadEffect()
{
	//Modelクラスを利用したエフェクト
	std::string defaultPath = "res/Sprite/Effect/";//全リソース共通パス

	//Effekseerを利用したエフェクト
	defaultPath = "res/Effekseer/";
}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//全リソース共通パス
	//FontManager::GetInstance().AddFont(FONT_ID::JAPANESE_FONT, defaultPath + "HGRGY.TTC", "HG行書体", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//全リソース共通パス
	//Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::TITLE_BGM);

}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//全リソース共通パス
	//Sound::GetInstance().LoadSE(defaultPath + "check.mp3", SE_ID::CHECK_SE);
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "Field/Skybox/skydome.mv1", MODEL_ID::MODEL_SKYBOX);
	Model::GetInstance().Load(defaultPath + "Field/Stage/stage.mv1", MODEL_ID::MODEL_STAGE);

}
