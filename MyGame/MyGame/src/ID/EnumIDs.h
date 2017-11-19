#pragma once

//モデルID
enum class MODEL_ID {
	MODEL_PLAYER
};
enum class SPRITE_ID {

};
enum class BGM_ID {

};
enum class SE_ID {

};
enum class FONT_ID {

};
//Effekseerを利用したエフェクト用ID
enum class EFFECT_ID {

};
//ゲーム中で利用するシーンを列挙する
enum class SceneType {
	SCENE_TITLE,
	SCENE_LOADING,
	SCENE_GAMEPLAY,
	SCENE_GAMEOVER,
	SCENE_CLEAR,
	SCENE_CREDIT,
	SCENE_EXIT,//ダミーシーン

};

//メッセージによるActor間の操作
enum class EventMessage {

};

//Actorのグループ分け
enum class ActorGroup {
	PLAYER_ACTOR,
};