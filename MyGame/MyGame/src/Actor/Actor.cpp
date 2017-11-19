#include "Actor.h"
#include<algorithm>
#include"../Field/FieldBase.h"
#include"Body/Base/HitInfo.h"

Actor::Actor():world_(nullptr),name_("Null"),position_(Vector3::Zero),body_(std::make_shared<DummyBody>())
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	world_(world),name_(name),position_(position),body_(body)
{
}

void Actor::rootInitialize()
{
	initialize();
	eachChildren([&](Actor& actor) {actor.rootInitialize(); });
}

void Actor::rootUpdate(float deltaTime)
{
	prevPosition_ = position_;
	prevRotation_ = rotation_;

	update(deltaTime);
	eachChildren([&](Actor& actor) {actor.rootUpdate(deltaTime); });
}

void Actor::rootDraw() const
{
	draw();
	eachChildren([&](const Actor& actor) {actor.rootDraw(); });

}

void Actor::initialize()
{
	isDead_ = false;
}

void Actor::update(float deltaTime)
{
}

void Actor::draw() const
{
}

void Actor::end()
{
}

bool Actor::isCollide(const Actor & other)
{
	HitInfo info;
	return body_->isCollide(*other.getBody().get(),info);
}

void Actor::onCollide(Actor & other)
{
}
void Actor::receiveMessage(EventMessage message, void * param)
{
}
void Actor::collide(Actor& other) {
	//���g�Ɠ������Ă���
	if (isCollide(other)) {
		//���݂��ɒʒm����
		onCollide(other);
		other.onCollide(*this);
	}
	//�q���ɂ������蔻�肳����
	eachChildren([&](Actor& child) { child.collide(other); });
}

// �t�B�[���h�Ƃ̏Փ˔���
bool Actor::field(Vector3& result) {
	Vector3 hitcenter;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&hitcenter))
	{
		result = hitcenter;

		return true;
	}
	return false;
}

void Actor::addChild(ActorPtr child)
{
	children_.push_back(child);
}

void Actor::setNumber(int cn)
{
	characterNumber_ = cn;
}

int Actor::getNumber() const
{
	return characterNumber_;
}

std::string Actor::getName() const
{
	return name_;
}

IBodyPtr Actor::getBody() const
{
	return body_;
}

Vector3 Actor::getPosition() const
{
	return position_;
}

bool Actor::isDead() const
{
	return isDead_;
}

void Actor::dead()
{
	isDead_ = true;
}

void Actor::clearChildren() {
	children_.clear();
}

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// �q�̌���
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	//�������ɍ������q���������炻�������Ă���
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	//�q�����X�Ɏq���������Ă����ꍇ�A���̒�������{��
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	//�Ώۂ����Ȃ�������null��Ԃ�
	return nullptr;
}
void Actor::findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	//�q�̒����疼�O�������Ă鑊������X�g�ɒǉ����Ă���
	eachChildren([&](Actor& actor) {
		if (actor.getName() == name) {
			//���g��shared_ptr��weak_ptr�̃��X�g�ɓ����
			actorList.push_back(actor.shared_from_this());
		}
	});
}

// �q������
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q������ (const�Łj
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q�̏Փ˔���
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// �q���폜
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// �q���폜
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

void Actor::handleMessage(EventMessage message, void * param)
{
	//�S���Ƀ��b�Z�[�W�𑗂�
	eachChildren([&](Actor& actor) {
		receiveMessage(message, param);
	});
}
