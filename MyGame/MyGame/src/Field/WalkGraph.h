#pragma once
#pragma once
#include<vector>
#include<string>
#include"../Math/Vector3.h"

class WalkGraph {
public:
	struct Edge {
		int node;//接続先ノード番号
		float cost;//移動コスト
	};
	struct Node {
		Vector3 position;
		std::vector<Edge> edges;//エッジ
	};
	WalkGraph() = default;

	void initialize();
	void load(const std::string& pointfilename, const std::string& pathfilename);
	//ノードを取得
	const Node& getNode(int sheet, int index)const;
	//ノード数を取得
	std::size_t node_count(int sheet)const;
	//最近ノードのキーを取得
	int getNearestNode(int sheet, const Vector3& position)const;
private:
	int currentSheet_{ 0 };
	std::vector<std::vector<Node>> nodes_;
};