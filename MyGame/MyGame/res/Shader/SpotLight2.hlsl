#include"DxLibShaderCommon.hlsli"
struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//テクスチャ座標
	float3 WTangent:TEXCOORD1;//接線
	float3 WBinormal : TEXCOORD2;//従法線
	float3 WNormal:TEXCOORD3;//ワールド法線
	float4 WPosition:TEXCOORD4;//ワールド座標
	float4 Position:SV_POSITION;//正規化デバイス頂点座標
};

cbuffer PixelShaderCB:register(b4) {
	//それぞれfloat4にしているのは、パディングを回避するため

	float4 g_WorldViewPosition;//視点の位置
	float4 g_WorldLightPosition;//ライトの位置
	float4 g_LightAmbientColor;;//環境光のライトの色
	float4 g_LightDiffuseColor;//拡散反射光のライトの色
	float4 g_LightSpecularColor;//鏡面反射光のライトの色
	float4 g_LightDirection;//ライトの方向
	float g_LightRange;//ライトの距離
	float g_LightCosOuterAngle;//スポットライトの外側角度のコサイン値
	float g_LightCosInnerAngle;//スポットライトの内側角度のコサイン値
	float padding;//パディング
}
//ディフューズマップテクスチャ
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);
//法線マップテクスチャ
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);
//スペキュラマップテクスチャ
SamplerState g_SpecularMapSampler:register(s2);
Texture2D g_SpecularMapTexture:register(t2);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//ライト方向のベクトル
	float3 lLightDir = g_WorldLightPosition.xyz - PSInput.WPosition.xyz;
	//法線ベクトル
	float3x3 matTBN = float3x3(normalize(PSInput.WTangent), normalize(PSInput.WBinormal), normalize(PSInput.WNormal));
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoord.xy).xyz*2.0 - 1.0), matTBN);
	//視点方向ベクトル
	float3 V = normalize(g_WorldViewPosition.xyz - PSInput.WPosition.xyz);
	//ライト方向ベクトル
	float3 L= normalize(lLightDir);
	//ハーフベクトル
	float3 H = normalize(L + V);

	//ライトまでの距離を求める
	float lLightDistance = length(lLightDir);
	//距離による減衰の計算
	float lRangeAttenuation = smoothstep(g_LightRange, 0.0, lLightDistance);
	//ライトのベクトルとライトの方向ベクトルの内積を計算
	float CosDir = dot(-L, normalize(g_LightDirection.xyz));
	//スポットライトの効果を計算
	float SpotEffect = smoothstep(g_LightCosOuterAngle, g_LightCosInnerAngle, CosDir);
	//距離による減衰と合成
	float Attenuation = lRangeAttenuation*SpotEffect;

	//テクスチャカラーの取得
	float4 TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);
	float4 TextureSpecularColor = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoord.xy);

	//環境光の計算
	float3 AmbientColor = g_LightAmbientColor.rgb*TextureDiffuseColor.rgb;
	//拡散反射光の計算
	float Diffuse = max(dot(L, N), 0.0);
	float3 DiffuseColor = g_LightDiffuseColor.rgb*TextureDiffuseColor.rgb*g_Common.Material.Diffuse.rgb*Diffuse;
	//鏡面反射光の計算
	float Specular = pow(max(dot(N, H), 0.0), g_Common.Material.Power);
	float3 SpecularColor = g_LightSpecularColor.rgb * TextureSpecularColor.rgb*g_Common.Material.Specular.rgb*Specular;
	//自己照明の計算
	float3 EmissiveColor = TextureDiffuseColor.rgb*g_Common.Material.Ambient_Emissive.rgb;

	//出力カラーの計算
	float4 OutputColor;
	OutputColor.rgb = (AmbientColor + DiffuseColor + SpecularColor)*Attenuation + EmissiveColor;
	OutputColor.a = TextureDiffuseColor.a;
	return OutputColor;


}