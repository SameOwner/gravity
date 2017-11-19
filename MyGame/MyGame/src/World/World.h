#pragma once
#include"IWorld.h"
#include"../Field/FieldPtr.h"
#include"../Actor/ActorManager.h"
#include"../UI/UIManager.h"

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

	void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name)override;
	// アクターの複数検索
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList)override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)override;
	// フィールドの取得
	virtual FieldPtr getField()override;
	//フィールドの設定
	virtual void setField(FieldPtr field)override;

	virtual std::weak_ptr<CameraActor> getCamera()const override;
private:
	FieldPtr field_;
	ActorManager actors_;
	UIManager uiManager_;

	std::weak_ptr<CameraActor> camera_;

};
