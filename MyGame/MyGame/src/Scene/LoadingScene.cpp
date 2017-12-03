#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	//�e�탊�\�[�X�̃��[�h���s��
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
	std::string defaultPath = "res/Sprite/";//�S���\�[�X���ʃp�X

}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//�S���\�[�X���ʃp�X

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
	//Model�N���X�𗘗p�����G�t�F�N�g
	std::string defaultPath = "res/Sprite/Effect/";//�S���\�[�X���ʃp�X

	//Effekseer�𗘗p�����G�t�F�N�g
	defaultPath = "res/Effekseer/";
}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//�S���\�[�X���ʃp�X
	//FontManager::GetInstance().AddFont(FONT_ID::JAPANESE_FONT, defaultPath + "HGRGY.TTC", "HG�s����", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//�S���\�[�X���ʃp�X
	//Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::TITLE_BGM);

}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//�S���\�[�X���ʃp�X
	//Sound::GetInstance().LoadSE(defaultPath + "check.mp3", SE_ID::CHECK_SE);
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//�S���\�[�X���ʃp�X
	Model::GetInstance().Load(defaultPath + "Field/Skybox/skydome.mv1", MODEL_ID::MODEL_SKYBOX);
	Model::GetInstance().Load(defaultPath + "Field/Stage/stage.mv1", MODEL_ID::MODEL_STAGE);

}
