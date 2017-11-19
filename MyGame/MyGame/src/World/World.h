#pragma once
#include"IWorld.h"
#include"../Field/FieldPtr.h"
#include"../Actor/ActorManager.h"
#include"../UI/UIManager.h"

// ���[���h���ۃC���^�[�t�F�[�X
class World:public IWorld {
public:
	World();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw()const;
	//���b�Z�[�W��M
	void handleMessage(EventMessage message, void* param);
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor)override;

	void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name)override;
	// �A�N�^�[�̕�������
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList)override;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField()override;
	//�t�B�[���h�̐ݒ�
	virtual void setField(FieldPtr field)override;

	virtual std::weak_ptr<CameraActor> getCamera()const override;
private:
	FieldPtr field_;
	ActorManager actors_;
	UIManager uiManager_;

	std::weak_ptr<CameraActor> camera_;

};
