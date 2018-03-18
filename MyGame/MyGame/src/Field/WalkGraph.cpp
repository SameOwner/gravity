#include "WalkGraph.h"
#include<assert.h>
#include"../Resource/CsvReader.h"

#define SHEET_OUT_OF_LENGTH assert(sheet < currentSheet_)

void WalkGraph::initialize() {
	nodes_.clear();
	currentSheet_ = 0;
}

 void WalkGraph::load(const std::string & pointfilename, const std::string & pathfilename) {
	currentSheet_++;//シートのカウントを追加
	CsvReader reader(pointfilename);//ポイントの読み込み

	nodes_.emplace_back();//新しいシートの作成
	int nodeSize = reader.rows();//ノード数の確認

	nodes_.back().resize(nodeSize);//ノード数分配列サイズを確保


	for (int i = 0; i < nodeSize; i++) {
		//ポイント位置の設定
		nodes_.back()[i].position.x = reader.getf(i, 0);
		nodes_.back()[i].position.y = reader.getf(i, 1);
		nodes_.back()[i].position.z = reader.getf(i, 2);
	}

	reader.load(pathfilename);//エッジの読み込み
	int edgeSize = reader.rows();//エッジ数の確認

								 //エッジデータの読み込み
	for (int i = 0; i < edgeSize; i++) {
		//始点終点のノード番号を読み込む
		int start = reader.geti(i, 0);
		int end = reader.geti(i, 1);
		float cost = Vector3::Distance(nodes_.back()[start].position, nodes_.back()[end].position);//距離をエッジのコストとする
																								   //相互に相手を行き先として設定する
		nodes_.back()[start].edges.push_back({ end,cost });
		nodes_.back()[end].edges.push_back({ start,cost });
	}
}

//ノードを取得

 const WalkGraph::Node & WalkGraph::getNode(int sheet, int index) const {
	 SHEET_OUT_OF_LENGTH;
	 return nodes_.at(sheet)[index];
}

//ノード数を取得

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
