#include "WalkGraph.h"
#include<assert.h>
#include"../Resource/CsvReader.h"

#define SHEET_OUT_OF_LENGTH assert(sheet < currentSheet_)

void WalkGraph::initialize() {
	nodes_.clear();
	currentSheet_ = 0;
}

 void WalkGraph::load(const std::string & pointfilename, const std::string & pathfilename) {
	currentSheet_++;//�V�[�g�̃J�E���g��ǉ�
	CsvReader reader(pointfilename);//�|�C���g�̓ǂݍ���

	nodes_.emplace_back();//�V�����V�[�g�̍쐬
	int nodeSize = reader.rows();//�m�[�h���̊m�F

	nodes_.back().resize(nodeSize);//�m�[�h�����z��T�C�Y���m��


	for (int i = 0; i < nodeSize; i++) {
		//�|�C���g�ʒu�̐ݒ�
		nodes_.back()[i].position.x = reader.getf(i, 0);
		nodes_.back()[i].position.y = reader.getf(i, 1);
		nodes_.back()[i].position.z = reader.getf(i, 2);
	}

	reader.load(pathfilename);//�G�b�W�̓ǂݍ���
	int edgeSize = reader.rows();//�G�b�W���̊m�F

								 //�G�b�W�f�[�^�̓ǂݍ���
	for (int i = 0; i < edgeSize; i++) {
		//�n�_�I�_�̃m�[�h�ԍ���ǂݍ���
		int start = reader.geti(i, 0);
		int end = reader.geti(i, 1);
		float cost = Vector3::Distance(nodes_.back()[start].position, nodes_.back()[end].position);//�������G�b�W�̃R�X�g�Ƃ���
																								   //���݂ɑ�����s����Ƃ��Đݒ肷��
		nodes_.back()[start].edges.push_back({ end,cost });
		nodes_.back()[end].edges.push_back({ start,cost });
	}
}

//�m�[�h���擾

 const WalkGraph::Node & WalkGraph::getNode(int sheet, int index) const {
	 SHEET_OUT_OF_LENGTH;
	 return nodes_.at(sheet)[index];
}

//�m�[�h�����擾

 std::size_t WalkGraph::node_count(int sheet) const {
	 SHEET_OUT_OF_LENGTH;
	return nodes_.at(sheet).size();
}

 int WalkGraph::getNearestNode(int sheet,const Vector3& position) const
 {
	 SHEET_OUT_OF_LENGTH;
	 int result = 0;
	 float nearlength = Vector3::Distance(position, nodes_.at(sheet).front().position);

	 float length;
	 for (int i = 0; i < nodes_.at(sheet).size(); i++) {
		 length = Vector3::Distance(position, nodes_.at(sheet).at(i).position);
		 if (length < nearlength) {
			 nearlength = length;
			 result = i;
		 }
	 }
	 return result;
 }
