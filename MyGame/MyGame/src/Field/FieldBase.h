#pragma once
#include"../Math/Collision/CollisionMesh.h"

// �t�B�[���h�N���X
class FieldBase {
public:
	// �R���X�g���N�^
	FieldBase(int field=-1, int skybox=-1);
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �t�B�[���h�̃n���h���擾
	int modelHandle();
	CollisionMesh& getMesh();
	// �R�s�[�֎~
	FieldBase(const FieldBase& other) = delete;
	FieldBase& operator = (const FieldBase& other) = delete;
private:
	int field_;
	int skyBox_;
	CollisionMesh mesh_;
};
