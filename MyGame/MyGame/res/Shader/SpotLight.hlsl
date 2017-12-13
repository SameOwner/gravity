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
	//�J�������猩���A�Ώۂ��烉�C�g�Ɍ������x�N�g��(Light�̃p�����[�^�͊��ɃJ������ɕϊ�����Ă���)
	float3 lLightDir = g_Common.Light[0].Position - PSInput.VPosition.xyz;

	float3x3 matTBN = float3x3(normalize(PSInput.VTangent), normalize(PSInput.VBinormal), normalize(PSInput.VNormal));
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoords0_1.xy).xyz*2.0 - 1.0), matTBN);
	float3 V = normalize(-PSInput.VPosition);
	float3 L = normalize(lLightDir);
	float3 H = normalize(L + V);//���C�g�����Ǝ��_�����̐^��
	
	//������2��
	float lLightDistancePow2 = dot(lLightDir, lLightDir);

	//�������̌v�Z  lLightGen=1/(�����l0+�����l1*����+�����l2*(����*����))
	float lLightAttenuation =
		1.0 / (g_Common.Light[0].Attenuation0//��茸��
			+ g_Common.Light[0].Attenuation1*sqrt(lLightDistancePow2)//����
			+ g_Common.Light[0].Attenuation2*lLightDistancePow2);//�����̓��

	//�L���͈͊O�������猸������0�ɂ���=���C�g�̌��E�l RangePow2�����[�g���O���Ȃ��l�Ȃ��߁A����������ɂ��� float step(float y,float x){return (x>=y)? 1.0f:0.0f};
	//step�͍��ӂ��傫�����1,�E�ӂ��傫�����0��Ԃ�
	float lRangeAttenuation = step(lLightDistancePow2, g_Common.Light[0].RangePow2);
	//���C�g�����x�N�g���ƃ��C�g�ʒu���璸�_�ʒu�ւ̃x�N�g���̓���(=Cos a)���v�Z
	float lLightDirectionCosA = dot(normalize(-lLightDir), g_Common.Light[0].Direction.xyz);
	//�X�|�b�g���C�g�����v�Z pow(((Cos a-Cos f)/(Cos q-Cos f)),falloff) SpotLightParam�͂��ꂼ��(Cos a-Cos f)��1/(Cos q-Cos f)�̌v�Z���ʂ������Ă���
	float lLightSpotEffect =
		saturate(pow(abs(max(lLightDirectionCosA - g_Common.Light[0].SpotParam0, 0.0f)//saturate��Clamp����֐�
			*g_Common.Light[0].SpotParam1), g_Common.Light[0].FallOff));

	float Attenuation = lLightAttenuation *lRangeAttenuation *lLightSpotEffect;


	//�e�N�X�`���J���[�̎擾
	float4 TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoords0_1.xy);
	float4 TextureSpecularColor = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoords0_1.xy);

	//����
	float3 AmbientColor = g_Common.Light[0].Ambient.rgb*TextureDiffuseColor.rgb;

	//�g�U���ˌ�
	float Diffuse = max(dot(L, N), 0.0);
	float3 DiffuseColor = g_Common.Light[0].Diffuse.rgb*TextureDiffuseColor.rgb*g_Common.Material.Diffuse.rgb*Diffuse;

	//���ʔ��ˌ�
	float Specular = pow(max(dot(N, H), 0.0), g_Common.Material.Power);
	float3 SpecularColor = g_Common.Light[0].Specular.rgb*TextureSpecularColor.rgb*g_Common.Material.Specular.rgb*Specular;

	//���ȏƖ�
	float3 EmissiveColor = TextureDiffuseColor.rgb*g_Common.Material.Ambient_Emissive.rgb;

	float4 OutputColor;
	OutputColor.rgb = (AmbientColor + DiffuseColor + SpecularColor)*Attenuation + EmissiveColor;//Attenuation�����C�g���x�A�����̌v�Z�͍ŏI�I�ɂ͕`�抄��0�`1(1�𒴂��ĉߏ�ɐF��t���鎖���\?)��\������
	OutputColor.a = TextureDiffuseColor.a;
	return OutputColor;

}