#pragma once
#include"IWorld.h"
#include"../Field/FieldPtr.h"
#include"../Actor/ActorManager.h"
#include"../UI/UIManager.h"
#include"../Field/CityMap.h"
#include"../Field/WalkGraph.h"
#include"../Fade/FadeSprite.h"

// ワールド抽象インターフェース
class World:public IWorld {
public:
	World();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw()const;
	//メッセージ受信
	void handleMessage(EventMessage message, void* param);
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor)override;
	virtual void addUI(const UIPtr& ui)override;
	//車道の読み込み
	void loadMap(const std::string& filename, const std::string& mapfilename);
	//歩道の追加
	void addWalkPoint(const std::string& pointfilename, const std::string& mapfilename);
	void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name)override;
	// アクターの複数検索
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList)override;
	//アクターの数を取得
	virtual int getActorCount(ActorGroup group)const override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)override;
	// フィールドの取得
	virtual FieldPtr getField()override;
	//フィールドの設定
	virtual void setField(FieldPtr field)override;
	virtual CityMap& getCityMap()override;
	virtual WalkGraph& getWalkMap()override;
	virtual FadeSprite& getFade()override;
	virtual std::weak_ptr<CameraActor> getCamera()const override;
private:
	FieldPtr field_{};
	ActorManager actors_{};
	UIManager uiManager_{};
	CityMap map_{};//道路マップ
	WalkGraph walkMap_{};//歩道マップリスト
	std::weak_ptr<CameraActor> camera_{};

	FadeSprite fade_{};
};
