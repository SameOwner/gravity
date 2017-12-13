#include"DxLibVertexShader.hlsli"

struct VS_INPUT {

	float4 Position :POSITION;//ローカル座標
};

struct VS_OUTPUT {
	float3 TexCoord:TEXCOORD0;//テクスチャ座標(6面座標のため、Vector3として渡す)
	float4 Position:SV_POSITION;//座標(プロジェクション座標系へ変換済のもの)


};

//スカイボックス用のシェーダー、カメラに近づく事が無い=カメラによる平行移動を行わないようにする
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;
	float4 lViewPosition;

	//視点座標系に変換、カメラの位置は考慮しないようにする(カメラに近づく事がないようにする)
	lViewPosition.x = dot(VSInput.Position.xyz, g_Base.ViewMatrix[0].xyz);
	lViewPosition.y = dot(VSInput.Position.xyz, g_Base.ViewMatrix[1].xyz);
	lViewPosition.z = dot(VSInput.Position.xyz, g_Base.ViewMatrix[2].xyz);
	lViewPosition.w = 1.0;

	//Projection(正規化デバイス座標系)への変換を行う
	VSOutput.Position.x = dot(lViewPosition, g_Base.ProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, g_Base.ProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, g_Base.ProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, g_Base.ProjectionMatrix[3]);
	//モデルのローカル座標をそのままテクスチャ座標に入れる事で、
	VSOutput.TexCoord.xyz = VSInput.Position.xyz;

	return VSOutput;
}