#pragma once

#include"../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include <string>
#include<list>

enum class ActorGroup;
enum class EventMessage;
// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// アクターの複数検索
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	// フィールドの取得
	virtual FieldPtr getField() = 0;
	virtual void setField(FieldPtr field) = 0;

};
