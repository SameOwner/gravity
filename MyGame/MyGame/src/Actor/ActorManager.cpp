#include "ActorManager.h"
#include"Actor.h"
#include"../ID/EnumIDs.h"

ActorManager::ActorManager()
{
	initialize();
}

void ActorManager::initialize()
{
	countList_ = 0;//���ʔԍ����X�g��������
	actors_.clear();

	actors_[ActorGroup::PLAYER_ACTOR] = std::make_shared<Actor>();
	root_->clearChildren();
	root_->addChild(actors_[ActorGroup::PLAYER_ACTOR]);

}

void ActorManager::update(float deltaTime)
{
	root_->rootUpdate(deltaTime);

	collide();

	//���񂾃L�����͍폜����
	root_->removeChildren();
}

void ActorManager::draw() const
{
	root_->rootDraw();
}

void ActorManager::addActor(ActorGroup group, const ActorPtr & actor)
{
	actor->initialize();
	//���ʔԍ�������U��
	actor->setNumber(countList_);
	countList_++;
	//�A�N�^�[�ɒǉ�
	actors_[group]->addChild(actor);
}

ActorPtr ActorManager::findActor(const std::string & name)
{
	return root_->findCildren(name);
}

void ActorManager::findActor(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	root_->findCildren(name,actorList);
}

void ActorManager::handleMessage(EventMessage message, void * param)
{
	root_->handleMessage(message, param);
}

void ActorManager::collide()
{
	//actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);

}
