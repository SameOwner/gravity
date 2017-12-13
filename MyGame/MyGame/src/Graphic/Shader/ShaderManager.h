#pragma once
#include<map>

//�V�F�[�_�[ID
enum class ShaderID {
	TEST_SHADER,
	SKYBOX_SHADER,//�X�J�C�{�b�N�X�p�V�F�[�_�[


};

//�V�F�[�_�[���Ǘ�����N���X
class ShaderManager {
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager& getInstance() {
		static ShaderManager manager;
		return manager;
	}
	//������
	void initialize();
	//�V�F�[�_�[�̓ǂݍ���
	void LoadShader(ShaderID id,const std::string& vertexShader, const std::string& pixelShader);
	//�V�F�[�_�[�̗L����
	void begin(ShaderID id);
	//�V�F�[�_�[�̖�����
	void end();
private:

	std::map<ShaderID, std::pair<int,int>> shaderHandleMap_;//�n���h���ꗗ

};