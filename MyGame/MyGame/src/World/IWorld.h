#pragma once

#include"../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include <string>
#include<list>

enum class ActorGroup;
enum class EventMessage;
// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �A�N�^�[�̕�������
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() = 0;
	virtual void setField(FieldPtr field) = 0;

};
