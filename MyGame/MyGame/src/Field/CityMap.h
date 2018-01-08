#pragma once
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"

class IWorld;//�e�X�g�p
class CityMap {
public:
	CityMap();
	~CityMap();
	void initialize();
	//csv�t�@�C���̓ǂݍ���
	void load(const std::string& filename, const std::string& mapfilename);
	//�ړI�n�ɂ��ǂ蒅�����߂̎��̒n�_����������
	int getNextCarPoint(int current,int goal);
	//�n�_�̍��W���擾����
	Vector3 getPosition(int point);
	void getWorld(IWorld* wrd);//�e�X�g
	int getSize()const;
	int getNearestPoint(const Vector3& position);

	void draw()const;//�f�o�b�O�\��
private:
	TwoDimensionalArray<int> carPointMap_;//�Ԃ��ړI�n�ɓ��B���邽�߂̌o�H��ۑ�����}�b�v
	std::vector<Vector3> carPoints_;//���H�|�C���g���X�g

	IWorld* world;//�e�X�g�p���[���h
};