#pragma once

#include"../Actor/ActorPtr.h"
#include"../UI/UIPtr.h"

#include"../Field/FieldPtr.h"
#include <string>
#include<list>

enum class ActorGroup;
enum class EventMessage;
class CameraActor;
class CityMap;
class WalkGraph;
class FadeSprite;

// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	//UIの追加
	virtual void addUI(const UIPtr& ui) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// アクターの複数検索
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) = 0;
	//アクターの数を取得
	virtual int getActorCount(ActorGroup group)const = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	// フィールドの取得
	virtual FieldPtr getField() = 0;
	virtual void setField(FieldPtr field) = 0;
	virtual std::weak_ptr<CameraActor> getCamera()const = 0;
	virtual CityMap& getCityMap() = 0;
	virtual WalkGraph& getWalkMap() = 0;
	virtual FadeSprite& getFade() = 0;
};
