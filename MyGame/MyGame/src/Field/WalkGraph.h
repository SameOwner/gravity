#pragma once
#pragma once
#include<vector>
#include<string>
#include"../Math/Vector3.h"

class WalkGraph {
public:
	struct Edge {
		int node;//�ڑ���m�[�h�ԍ�
		float cost;//�ړ��R�X�g
	};
	struct Node {
		Vector3 position;
		std::vector<Edge> edges;//�G�b�W
	};
	WalkGraph() = default;

	void initialize();
	void load(const std::string& pointfilename, const std::string& pathfilename);
	//�m�[�h���擾
	const Node& getNode(int sheet, int index)const;
	//�m�[�h�����擾
	std::size_t node_count(int sheet)const;
	//�ŋ߃m�[�h�̃L�[���擾
	int getNearestNode(int sheet, const Vector3& position)const;
private:
	int currentSheet_{ 0 };
	std::vector<std::vector<Node>> nodes_;
};