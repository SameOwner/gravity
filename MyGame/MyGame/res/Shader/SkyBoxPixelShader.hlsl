struct PS_INPUT {
	float3 TexCoord:TEXCOORD0;//�e�N�X�`�����W(Vector3)
};
SamplerState g_EnvMapSampler:register(s11);//11�Ԃɓ���Ă���̂́A���炭���p����Ă��Ȃ��ł��낤�ԍ��ł��邽��(�����Ńe�N�X�`����n�����߁A�㏑�����s���Ȃ��悤��)
TextureCube g_EnvMapTexture:register(t11);//11�Ԃɓ���Ă���̂́A���炭���p����Ă��Ȃ��ł��낤�ԍ��ł��邽��

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	return g_EnvMapTexture.Sample(g_EnvMapSampler,PSInput.TexCoord);
}