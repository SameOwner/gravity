#include "ActorManager.h"
#include"Actor.h"
#include"../ID/EnumIDs.h"

ActorManager::ActorManager()
{
	initialize();
}

void ActorManager::initialize()
{
	countList_ = 0;//識別番号リストを初期化
	actors_.clear();

	root_ = std::make_shared<Actor>();

	actors_[ActorGroup::PLAYER_ACTOR] = std::make_shared<Actor>();
	actors_[ActorGroup::ENEMY_ACTOR] = std::make_shared<Actor>();
	actors_[ActorGroup::ETCETERA_ACTOR] = std::make_shared<Actor>();
	actors_[ActorGroup::CAR_ACTOR] = std::make_shared<Actor>();
	actors_[ActorGroup::CITIZEN_ACTOR] = std::make_shared<Actor>();
	actors_[ActorGroup::POINT_ACTOR] = std::make_shared<Actor>();
	
	root_->clearChildren();
	root_->addChild(actors_[ActorGroup::PLAYER_ACTOR]);
	root_->addChild(actors_[ActorGroup::ENEMY_ACTOR]);
	root_->addChild(actors_[ActorGroup::ETCETERA_ACTOR]);
	root_->addChild(actors_[ActorGroup::CAR_ACTOR]);
	root_->addChild(actors_[ActorGroup::CITIZEN_ACTOR]);
	root_->addChild(actors_[ActorGroup::POINT_ACTOR]);

}

void ActorManager::update(float deltaTime)
{
	root_->rootUpdate(deltaTime);

	collide();

	//死んだキャラは削除する
	root_->removeChildren();
}

void ActorManager::draw() const
{
	root_->rootDraw();
}

void ActorManager::addActor(ActorGroup group, const ActorPtr & actor)
{
	actor->initialize();
	//識別番号を割り振る
	actor->setNumber(countList_);
	countList_++;

	//種類を設定する
	actor->setGroup(group);
	
	//アクターに追加
	actors_[group]->addChild(actor);
}

ActorPtr ActorManager::findActor(const std::string & name)
{
	return root_->findCildren(name);
}

void ActorManager::findActor(ActorGroup group,const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	actors_[group]->findCildren(name,actorList);
}

void ActorManager::handleMessage(EventMessage message, void * param)
{
	root_->handleMessage(message, param);
}

unsigned int ActorManager::getSize(ActorGroup group) const
{
	return actors_.at(group)->getChildCount();
}

void ActorManager::collide()
{
	actors_[ActorGroup::PLAYER_ACTOR]->collideChildren(*actors_[ActorGroup::POINT_ACTOR]);
	actors_[ActorGroup::PLAYER_ACTOR]->collideChildren(*actors_[ActorGroup::ENEMY_ACTOR]);
	actors_[ActorGroup::PLAYER_ACTOR]->collideChildren(*actors_[ActorGroup::CITIZEN_ACTOR]);
	actors_[ActorGroup::PLAYER_ACTOR]->collideChildren(*actors_[ActorGroup::CAR_ACTOR]);
	

}
