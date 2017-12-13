#pragma once

//モデルID
enum class MODEL_ID {
	MODEL_PLAYER,
	MODEL_SKYBOX,
	MODEL_STAGE,
};
enum class SPRITE_ID {
	SPRITE_FLOATGAUGE,//浮遊ゲージスプライト
	SPRITE_WINDEFFECT//風エフェクトスプライト
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
	ETCETERA_ACTOR,//ゲームに関与しないアクター
	PLAYER_ACTOR,//プレイヤー
	POINT_ACTOR,//チェックポイント
};