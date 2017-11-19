#pragma once
#include"ActorPtr.h"
#include<map>
#include<list>

enum class ActorGroup;
enum class EventMessage;
class ActorManager {
public:
	ActorManager();

	// ������
	void initialize();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �A�N�^�[�̒ǉ�
	void addActor(ActorGroup group, const ActorPtr& actor);
	// �A�N�^�[�̌���
	ActorPtr findActor(const std::string& name);
	// �A�N�^�[�̈ꊇ����
	void findActor(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// �Փ˔���
	void collide();
private:
	//�L�����N�^�[�Ɏ��ʔԍ���ݒ肷��
	int countList_{ 0 };
private:
	//�A�N�^�[�ꗗ
	std::map<ActorGroup,ActorPtr> actors_;

	ActorPtr root_;
};