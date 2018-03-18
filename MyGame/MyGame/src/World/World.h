#pragma once
#include"IWorld.h"
#include"../Field/FieldPtr.h"
#include"../Actor/ActorManager.h"
#include"../UI/UIManager.h"
#include"../Field/CityMap.h"
#include"../Field/WalkGraph.h"
#include"../Fade/FadeSprite.h"

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
	virtual void addUI(const UIPtr& ui)override;
	//�ԓ��̓ǂݍ���
	void loadMap(const std::string& filename, const std::string& mapfilename);
	//�����̒ǉ�
	void addWalkPoint(const std::string& pointfilename, const std::string& mapfilename);
	void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name)override;
	// �A�N�^�[�̕�������
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList)override;
	//�A�N�^�[�̐����擾
	virtual int getActorCount(ActorGroup group)const override;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField()override;
	//�t�B�[���h�̐ݒ�
	virtual void setField(FieldPtr field)override;
	virtual CityMap& getCityMap()override;
	virtual WalkGraph& getWalkMap()override;
	virtual FadeSprite& getFade()override;
	virtual std::weak_ptr<CameraActor> getCamera()const override;
private:
	FieldPtr field_{};
	ActorManager actors_{};
	UIManager uiManager_{};
	CityMap map_{};//���H�}�b�v
	WalkGraph walkMap_{};//�����}�b�v���X�g
	std::weak_ptr<CameraActor> camera_{};

	FadeSprite fade_{};
};
