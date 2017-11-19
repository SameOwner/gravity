#include "World.h"
#include"../ID/EnumIDs.h"
#include"../Actor/Actor.h"
#include"../Field/FieldBase.h"

World::World():field_(nullptr)
{
}

void World::initialize()
{
	actors_.initialize();
	uiManager_.initialize();

}

void World::update(float deltaTime)
{
	actors_.update(deltaTime);
	uiManager_.update(deltaTime);

}

void World::draw() const
{
	//field‚ª‚¢‚½‚ç•`‰æ
	if(field_!=nullptr)field_->draw();

	actors_.draw();
	uiManager_.draw();
}

void World::handleMessage(EventMessage message, void * param)
{
}

void World::addActor(ActorGroup group, const ActorPtr & actor)
{
	actors_.addActor(group, actor);
}

ActorPtr World::findActor(const std::string & name)
{
	return actors_.findActor(name);
}

void World::findActors(const std::string & name, std::list<ActorPtr>& actorList)
{

}

void World::sendMessage(EventMessage message, void * param)
{
	actors_.handleMessage(message, param);
}

FieldPtr World::getField()
{
	return field_;
}

void World::setField(FieldPtr field)
{
	field_ = field;
}
