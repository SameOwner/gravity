#pragma once
#include<map>

//シェーダーID
enum class ShaderID {
	TEST_SHADER,
	SKYBOX_SHADER,//スカイボックス用シェーダー


};

//シェーダーを管理するクラス
class ShaderManager {
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager& getInstance() {
		static ShaderManager manager;
		return manager;
	}
	//初期化
	void initialize();
	//シェーダーの読み込み
	void LoadShader(ShaderID id,const std::string& vertexShader, const std::string& pixelShader);
	//シェーダーの有効化
	void begin(ShaderID id);
	//シェーダーの無効化
	void end();
private:

	std::map<ShaderID, std::pair<int,int>> shaderHandleMap_;//ハンドル一覧

};