#include"DxLibPixelShader.hlsli"

struct PS_INPUT {
	float4 TexCoords0_1 : TEXCOORD0;
	float3 VPosition    : TEXCOORD1;
	float3 VNormal      : TEXCOORD2;
	float3 VLight       : TEXCOORD3;
	float3 VTangent     : TEXCOORD4;
	float3 VBinormal    : TEXCOORD5;
	float4 Position     : SV_POSITION;
};

SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);

SamplerState g_SpecularMapSampler:register(s2);
Texture2D g_SpecularMapTexture:register(t2);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//カメラから見た、対象からライトに向かうベクトル(Lightのパラメータは既にカメラ基準に変換されている)
	float3 lLightDir = g_Common.Light[0].Position - PSInput.VPosition.xyz;

	float3x3 matTBN = float3x3(normalize(PSInput.VTangent), normalize(PSInput.VBinormal), normalize(PSInput.VNormal));
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoords0_1.xy).xyz*2.0 - 1.0), matTBN);
	float3 V = normalize(-PSInput.VPosition);
	float3 L = normalize(lLightDir);
	float3 H = normalize(L + V);//ライト方向と視点方向の真ん中
	
	//距離の2乗
	float lLightDistancePow2 = dot(lLightDir, lLightDir);

	//減衰率の計算  lLightGen=1/(減衰値0+減衰値1*距離+減衰値2*(距離*距離))
	float lLightAttenuation =
		1.0 / (g_Common.Light[0].Attenuation0//一定減衰
			+ g_Common.Light[0].Attenuation1*sqrt(lLightDistancePow2)//距離
			+ g_Common.Light[0].Attenuation2*lLightDistancePow2);//距離の二乗

	//有効範囲外だったら減衰率を0にする=ライトの限界値 RangePow2がルートを外さない値なため、こっちを基準にする float step(float y,float x){return (x>=y)? 1.0f:0.0f};
	//stepは左辺が大きければ1,右辺が大きければ0を返す
	float lRangeAttenuation = step(lLightDistancePow2, g_Common.Light[0].RangePow2);
	//ライト方向ベクトルとライト位置から頂点位置へのベクトルの内積(=Cos a)を計算
	float lLightDirectionCosA = dot(normalize(-lLightDir), g_Common.Light[0].Direction.xyz);
	//スポットライト減衰計算 pow(((Cos a-Cos f)/(Cos q-Cos f)),falloff) SpotLightParamはそれぞれ(Cos a-Cos f)と1/(Cos q-Cos f)の計算結果が入っている
	float lLightSpotEffect =
		saturate(pow(abs(max(lLightDirectionCosA - g_Common.Light[0].SpotParam0, 0.0f)//saturateはClampする関数
			*g_Common.Light[0].SpotParam1), g_Common.Light[0].FallOff));

	float Attenuation = lLightAttenuation *lRangeAttenuation *lLightSpotEffect;


	//テクスチャカラーの取得
	float4 TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoords0_1.xy);
	float4 TextureSpecularColor = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoords0_1.xy);

	//環境光
	float3 AmbientColor = g_Common.Light[0].Ambient.rgb*TextureDiffuseColor.rgb;

	//拡散反射光
	float Diffuse = max(dot(L, N), 0.0);
	float3 DiffuseColor = g_Common.Light[0].Diffuse.rgb*TextureDiffuseColor.rgb*g_Common.Material.Diffuse.rgb*Diffuse;

	//鏡面反射光
	float Specular = pow(max(dot(N, H), 0.0), g_Common.Material.Power);
	float3 SpecularColor = g_Common.Light[0].Specular.rgb*TextureSpecularColor.rgb*g_Common.Material.Specular.rgb*Specular;

	//自己照明
	float3 EmissiveColor = TextureDiffuseColor.rgb*g_Common.Material.Ambient_Emissive.rgb;

	float4 OutputColor;
	OutputColor.rgb = (AmbientColor + DiffuseColor + SpecularColor)*Attenuation + EmissiveColor;//Attenuationがライト強度、減衰の計算は最終的には描画割合0～1(1を超えて過剰に色を付ける事も可能?)を表現する
	OutputColor.a = TextureDiffuseColor.a;
	return OutputColor;

}