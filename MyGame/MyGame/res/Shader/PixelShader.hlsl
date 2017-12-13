struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//�e�N�X�`�����W
	float3 WTangent:TEXCOORD1;//�ڐ�
	float3 WBinormal : TEXCOORD2;//�]�@��
	float3 WNormal:TEXCOORD3;//���[���h�@��
	float4 WPosition:TEXCOORD4;//���[���h���W
	float4 Position:SV_POSITION;//���K���f�o�C�X���_���W

};
//�@���}�b�v�e�N�X�`��
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);

//�L���[�u�}�b�v�e�N�X�`��
SamplerState g_CubemapSampler:register(s11);
TextureCube g_CubemapTexture:register(t11);

cbuffer PixelShaderCB:register(b4) {
	float4 g_WorldViewPosition;
}

//���t���N�V�����̌v�Z�����邽�߂ɁAWorld���W�n����Ƃ��Ă���
float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//�@���}�b�v�̕ϊ��s����쐬
	float3x3 matTBN = float3x3(normalize(PSInput.WTangent),normalize(PSInput.WBinormal),normalize(PSInput.WNormal));
	//�@���}�b�v����l������Ă���(TBN�}�g���N�X�Ń��[���h���W�n�ɍs��)
	float N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoord.xy).xyz*2.0 - 1.0), matTBN);
	//�@���x�N�g��
	//float3 N = normalize(PSInput.WNormal);
	//���_�����̃x�N�g��(���g�̈ʒu����J�����Ɍ������x�N�g��)
	float3 V = normalize(g_WorldViewPosition.xyz - PSInput.WPosition);
	//���˃x�N�g�����v�Z(�J�������畨�̂Ɍ������x�N�g���𗘗p�����v�Z�Ȃ���-V) (V=���_���畨�̂֌������x�N�g��,N=�@��,R�͔��˃x�N�g��)R=V-2N(N�EV)
	float3 R = refract(-V, N,0.1);

	float3 CubemapColor = g_CubemapTexture.Sample(g_CubemapSampler, R).rgb;

	float4 OutputColor;
	OutputColor.rgb = CubemapColor;
	OutputColor.a = 1.0;


	return g_CubemapTexture.Sample(g_CubemapSampler, R);
}