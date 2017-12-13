struct PS_INPUT {
	float3 TexCoord:TEXCOORD0;//テクスチャ座標(Vector3)
};
SamplerState g_EnvMapSampler:register(s11);//11番に入れているのは、恐らく利用されていないであろう番号であるため(自分でテクスチャを渡すため、上書きが行われないように)
TextureCube g_EnvMapTexture:register(t11);//11番に入れているのは、恐らく利用されていないであろう番号であるため

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	return g_EnvMapTexture.Sample(g_EnvMapSampler,PSInput.TexCoord);
}