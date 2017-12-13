struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//テクスチャ座標
	float3 WTangent:TEXCOORD1;//接線
	float3 WBinormal : TEXCOORD2;//従法線
	float3 WNormal:TEXCOORD3;//ワールド法線
	float4 WPosition:TEXCOORD4;//ワールド座標
	float4 Position:SV_POSITION;//正規化デバイス頂点座標

};
//法線マップテクスチャ
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);

//キューブマップテクスチャ
SamplerState g_CubemapSampler:register(s11);
TextureCube g_CubemapTexture:register(t11);

cbuffer PixelShaderCB:register(b4) {
	float4 g_WorldViewPosition;
}

//リフレクションの計算をするために、World座標系を基準としている
float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//法線マップの変換行列を作成
	float3x3 matTBN = float3x3(normalize(PSInput.WTangent),normalize(PSInput.WBinormal),normalize(PSInput.WNormal));
	//法線マップから値を取ってくる(TBNマトリクスでワールド座標系に行く)
	float N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoord.xy).xyz*2.0 - 1.0), matTBN);
	//法線ベクトル
	//float3 N = normalize(PSInput.WNormal);
	//視点方向のベクトル(自身の位置からカメラに向かうベクトル)
	float3 V = normalize(g_WorldViewPosition.xyz - PSInput.WPosition);
	//反射ベクトルを計算(カメラから物体に向かうベクトルを利用した計算なため-V) (V=視点から物体へ向かうベクトル,N=法線,Rは反射ベクトル)R=V-2N(N・V)
	float3 R = refract(-V, N,0.1);

	float3 CubemapColor = g_CubemapTexture.Sample(g_CubemapSampler, R).rgb;

	float4 OutputColor;
	OutputColor.rgb = CubemapColor;
	OutputColor.a = 1.0;


	return g_CubemapTexture.Sample(g_CubemapSampler, R);
}