#pragma once

//モデルID
enum class MODEL_ID {
	MODEL_PLAYER,
	MODEL_SKYBOX,
	MODEL_STAGE,
	MODEL_CAR,
	MODEL_ENEMY,
	MODEL_CITIZEN_USAUSA,

};
enum class SPRITE_ID {
	SPRITE_FLOATGAUGE,//浮遊ゲージスプライト
	SPRITE_FLOATGAUGE_FRAME,//浮遊ゲージ枠スプライト
	SPRITE_WINDEFFECT,//風エフェクトスプライト
	SPRITE_FIELDMAP,//フィールドマップスプライト
	SPRITE_TITLEBACK,//タイトルバックスプライト
	SPRITE_TITLELOGO,//タイトルロゴスプライト
	SPRITE_TITLEBUTTON,//タイトルボタンスプライト
	SPRITE_GAMECLEAR,//ゲームクリアスプライト
	FADE_SPRITE,//フェードスプライト
};
enum class BGM_ID {
	SOUND_TITLE,
	SOUND_GAME,
	SOUND_CLEAR
};
enum class SE_ID {
	SELECT_SE,//選択
	RUN_SE,//足音
	WIND_SE,//移動時風音
	JUMP_SE,//ジャンプ
	LAND_SE,//着地
	HIT_SE,//接触
};
enum class FONT_ID {
	FONT_COUNT,//カウント用フォント
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
	Hit_Car,
	Hit_Bullet,
};

//Actorのグループ分け
enum class ActorGroup {
	ETCETERA_ACTOR,//ゲームに関与しないアクター
	PLAYER_ACTOR,//プレイヤー
	CAR_ACTOR,//車アクター
	POINT_ACTOR,//チェックポイント
	ENEMY_ACTOR,//敵
	CITIZEN_ACTOR,//住民
};