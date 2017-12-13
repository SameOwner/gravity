#include "ShaderManager.h"
#include<DxLib.h>

ShaderManager::ShaderManager() {

}

ShaderManager::~ShaderManager() {}

void ShaderManager::initialize() {
	InitShader();
	shaderHandleMap_.clear();

}

void ShaderManager::LoadShader(ShaderID id,const std::string & vertexShader, const std::string & pixelShader)
{
	int vertex = LoadVertexShader(vertexShader.c_str());
	int pixel = LoadPixelShader(pixelShader.c_str());

	shaderHandleMap_[id] = std::make_pair(vertex, pixel);
}

void ShaderManager::begin(ShaderID id) {
	MV1SetUseOrigShader(TRUE);
	SetUseVertexShader(shaderHandleMap_.at(id).first);
	SetUsePixelShader(shaderHandleMap_.at(id).second);

}

void ShaderManager::end() {
	MV1SetUseOrigShader(FALSE);

}
