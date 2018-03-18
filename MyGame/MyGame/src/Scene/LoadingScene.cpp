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
	LoadShader();
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
	Sprite::GetInstance().Load(defaultPath + "gauge.png", SPRITE_ID::SPRITE_FLOATGAUGE);
	Sprite::GetInstance().Load(defaultPath + "gaugeframe_black.png", SPRITE_ID::SPRITE_FLOATGAUGE_FRAME);
	
	Sprite::GetInstance().Load(defaultPath + "wind.png", SPRITE_ID::SPRITE_WINDEFFECT);
	Sprite::GetInstance().Load(defaultPath + "map.png", SPRITE_ID::SPRITE_FIELDMAP);
	Sprite::GetInstance().Load(defaultPath + "title.png", SPRITE_ID::SPRITE_TITLEBACK);
	Sprite::GetInstance().Load(defaultPath + "title_logo.png", SPRITE_ID::SPRITE_TITLELOGO);
	Sprite::GetInstance().Load(defaultPath + "title_presskey.png", SPRITE_ID::SPRITE_TITLEBUTTON);
	Sprite::GetInstance().Load(defaultPath + "gameclear.png", SPRITE_ID::SPRITE_GAMECLEAR);
	Sprite::GetInstance().Load(defaultPath + "fade.png", SPRITE_ID::FADE_SPRITE);
	
}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//全リソース共通パス

	Model::GetInstance().Load(defaultPath + "alicia/alicia.mv1", MODEL_ID::MODEL_PLAYER);
	
	//Model::GetInstance().Load(defaultPath + "alicia/model.mv1", MODEL_ID::MODEL_PLAYER);
	//std::list<std::string> anims{
	//	defaultPath + "alicia/idle.mv1",
	//	defaultPath + "alicia/run.mv1",
	//	defaultPath + "alicia/jump_up.mv1",
	//	defaultPath + "alicia/float.mv1",
	//	defaultPath + "alicia/jump_down.mv1",
	//	defaultPath + "alicia/slide.mv1",
	//	defaultPath + "alicia/fly.mv1",
	//	defaultPath + "alicia/blow.mv1",
	//	defaultPath + "alicia/down.mv1",
	//	defaultPath + "alicia/getup.mv1"
	//};
	//AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_PLAYER, anims);

	Model::GetInstance().Load(defaultPath + "models/car/car1/model.mv1", MODEL_ID::MODEL_CAR);
	Model::GetInstance().Load(defaultPath + "bird/bird.pmx", MODEL_ID::MODEL_ENEMY);
	Model::GetInstance().Load(defaultPath + "models/usausa/usausa.pmd", MODEL_ID::MODEL_CITIZEN_USAUSA);
}


void LoadingScene::LoadEffect()
{
	//Modelクラスを利用したエフェクト
	std::string defaultPath = "res/Effekseer";//全リソース共通パス

}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//全リソース共通パス
	FontManager::GetInstance().AddFont(FONT_ID::FONT_COUNT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//全リソース共通パス
	Sound::GetInstance().LoadBGM(defaultPath + "title.mp3", BGM_ID::SOUND_TITLE);
	Sound::GetInstance().LoadBGM(defaultPath + "game.mp3", BGM_ID::SOUND_GAME);
	Sound::GetInstance().LoadBGM(defaultPath + "clear.mp3", BGM_ID::SOUND_CLEAR);
	
}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//全リソース共通パス
	Sound::GetInstance().LoadSE(defaultPath + "select.mp3", SE_ID::SELECT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "run.mp3", SE_ID::RUN_SE);
	Sound::GetInstance().LoadSE(defaultPath + "wind.mp3", SE_ID::WIND_SE);
	Sound::GetInstance().LoadSE(defaultPath + "jump.mp3", SE_ID::JUMP_SE);
	Sound::GetInstance().LoadSE(defaultPath + "land.mp3", SE_ID::LAND_SE);
	Sound::GetInstance().LoadSE(defaultPath + "hit.mp3", SE_ID::HIT_SE);

}

void LoadingScene::LoadShader()
{
	std::string defaultPath = "res/Shader/";//全リソース共通パス
	ShaderManager::getInstance().LoadShader(ShaderID::SKYBOX_SHADER, defaultPath + "SkyBoxVertexShader.cso", defaultPath + "SkyBoxPixelShader.cso");
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//全リソース共通パス
	Model::GetInstance().Load(defaultPath + "Field/Skybox/skydome.mv1", MODEL_ID::MODEL_SKYBOX);
	Model::GetInstance().Load(defaultPath + "Field/Stage/stage.mv1", MODEL_ID::MODEL_STAGE);

}
