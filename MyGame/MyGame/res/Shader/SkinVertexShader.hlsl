#include "DxLibVertexShader.hlsli"

struct VS_INPUT {
	float4 Position   : POSITION;
	float3 Normal     : NORMAL0;
	float4 Diffuse    : COLOR0;
	float4 Specular   : COLOR1;
	float4 TexCoords0 : TEXCOORD0;
	float4 TexCoords1 : TEXCOORD1;
	float3 Tangent    : TANGENT0;
	float3 Binormal   : BINORMAL0;
	int4   BlendIndices0 : BLENDINDICES0;
	float4 BlendWeight0  : BLENDWEIGHT0;
};

struct VS_OUTPUT {
	float4 TexCoords0_1 : TEXCOORD0;
	float3 VPosition    : TEXCOORD1;
	float3 VNoraml      : TEXCOORD2;
	float3 VLight       : TEXCOORD3;
	float3 VTangent     : TEXCOORD4;
	float3 VBinormal    : TEXCOORD5;
	float4 Position     : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT VSInput) {
	VS_OUTPUT VSOutput;
	// スキンメッシュ用のブレンド行列の作成
	int4 lBoneFloatIndex;
	lBoneFloatIndex = VSInput.BlendIndices0;
	float4 lLocalWorldMatrix[3];
	lLocalWorldMatrix[0] =  g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 0] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[1] =  g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 1] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[2] =  g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 2] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 0] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 1] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 2] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 0] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 1] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 2] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 0] * VSInput.BlendWeight0.w;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 1] * VSInput.BlendWeight0.w;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 2] * VSInput.BlendWeight0.w;

	// ワールド変換
	float4 lWorldPosition;
	lWorldPosition.x = dot(VSInput.Position, lLocalWorldMatrix[0]);
	lWorldPosition.y = dot(VSInput.Position, lLocalWorldMatrix[1]);
	lWorldPosition.z = dot(VSInput.Position, lLocalWorldMatrix[2]);
	lWorldPosition.w = 1.0f;
	// ビュー変換
	float4 lViewPosition;
	lViewPosition.x = dot(lWorldPosition, g_Base.ViewMatrix[0]);
	lViewPosition.y = dot(lWorldPosition, g_Base.ViewMatrix[1]);
	lViewPosition.z = dot(lWorldPosition, g_Base.ViewMatrix[2]);
	lViewPosition.w = 1.0f;
	// 透視変換
	float4 lProjPosition;
	lProjPosition.x = dot(lViewPosition, g_Base.ProjectionMatrix[0]);
	lProjPosition.y = dot(lViewPosition, g_Base.ProjectionMatrix[1]);
	lProjPosition.z = dot(lViewPosition, g_Base.ProjectionMatrix[2]);
	lProjPosition.w = dot(lViewPosition, g_Base.ProjectionMatrix[3]);

	// 法線ベクトルのワールド変換
	float3 lWorldNormal;
	lWorldNormal.x = dot(VSInput.Normal, lLocalWorldMatrix[0].xyz);
	lWorldNormal.y = dot(VSInput.Normal, lLocalWorldMatrix[1].xyz);
	lWorldNormal.z = dot(VSInput.Normal, lLocalWorldMatrix[2].xyz);
	float3 lViewNormal;
	lViewNormal.x = dot(lWorldNormal, g_Base.ViewMatrix[0].xyz);
	lViewNormal.y = dot(lWorldNormal, g_Base.ViewMatrix[1].xyz);
	lViewNormal.z = dot(lWorldNormal, g_Base.ViewMatrix[2].xyz);
	// 接ベクトルのワールド変換
	float3 lWorldTangent;
	lWorldTangent.x = dot(VSInput.Tangent, lLocalWorldMatrix[0].xyz);
	lWorldTangent.y = dot(VSInput.Tangent, lLocalWorldMatrix[1].xyz);
	lWorldTangent.z = dot(VSInput.Tangent, lLocalWorldMatrix[2].xyz);
	// 接ベクトルの視野変換
	float3 lViewTangent;
	lViewTangent.x = dot(lWorldTangent, g_Base.ViewMatrix[0].xyz);
	lViewTangent.y = dot(lWorldTangent, g_Base.ViewMatrix[1].xyz);
	lViewTangent.z = dot(lWorldTangent, g_Base.ViewMatrix[2].xyz);
	// 従法線ベクトルのワールド変換
	float3 lWorldBinormal;
	lWorldBinormal.x = dot(VSInput.Binormal, lLocalWorldMatrix[0].xyz);
	lWorldBinormal.y = dot(VSInput.Binormal, lLocalWorldMatrix[1].xyz);
	lWorldBinormal.z = dot(VSInput.Binormal, lLocalWorldMatrix[2].xyz);
	float3 lViewBinormal;
	lViewBinormal.x = dot(lWorldBinormal, g_Base.ViewMatrix[0].xyz);
	lViewBinormal.y = dot(lWorldBinormal, g_Base.ViewMatrix[1].xyz);
	lViewBinormal.z = dot(lWorldBinormal, g_Base.ViewMatrix[2].xyz);

	// ライト方向のベクトルを視野座標系に変換
	float3 lViewLight;
	lViewLight.x = dot(g_Common.Light[0].Direction, g_Base.ViewMatrix[0].xyz);
	lViewLight.y = dot(g_Common.Light[0].Direction, g_Base.ViewMatrix[1].xyz);
	lViewLight.z = dot(g_Common.Light[0].Direction, g_Base.ViewMatrix[2].xyz);

	// 計算結果を出力
	VSOutput.TexCoords0_1 = VSInput.TexCoords0;
	VSOutput.VPosition    = lViewPosition.xyz;
	VSOutput.VNoraml      = lViewNormal;
	VSOutput.VLight       = lViewLight;
	VSOutput.VTangent     = lViewTangent;
	VSOutput.VBinormal    = lViewBinormal;
	VSOutput.Position     = lProjPosition;
	return VSOutput;
}