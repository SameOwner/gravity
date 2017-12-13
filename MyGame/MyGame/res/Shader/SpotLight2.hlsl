#include"DxLibShaderCommon.hlsli"
struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//�e�N�X�`�����W
	float3 WTangent:TEXCOORD1;//�ڐ�
	float3 WBinormal : TEXCOORD2;//�]�@��
	float3 WNormal:TEXCOORD3;//���[���h�@��
	float4 WPosition:TEXCOORD4;//���[���h���W
	float4 Position:SV_POSITION;//���K���f�o�C�X���_���W
};

cbuffer PixelShaderCB:register(b4) {
	//���ꂼ��float4�ɂ��Ă���̂́A�p�f�B���O��������邽��

	float4 g_WorldViewPosition;//���_�̈ʒu
	float4 g_WorldLightPosition;//���C�g�̈ʒu
	float4 g_LightAmbientColor;;//�����̃��C�g�̐F
	float4 g_LightDiffuseColor;//�g�U���ˌ��̃��C�g�̐F
	float4 g_LightSpecularColor;//���ʔ��ˌ��̃��C�g�̐F
	float4 g_LightDirection;//���C�g�̕���
	float g_LightRange;//���C�g�̋���
	float g_LightCosOuterAngle;//�X�|�b�g���C�g�̊O���p�x�̃R�T�C���l
	float g_LightCosInnerAngle;//�X�|�b�g���C�g�̓����p�x�̃R�T�C���l
	float padding;//�p�f�B���O
}
//�f�B�t���[�Y�}�b�v�e�N�X�`��
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);
//�@���}�b�v�e�N�X�`��
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);
//�X�y�L�����}�b�v�e�N�X�`��
SamplerState g_SpecularMapSampler:register(s2);
Texture2D g_SpecularMapTexture:register(t2);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//���C�g�����̃x�N�g��
	float3 lLightDir = g_WorldLightPosition.xyz - PSInput.WPosition.xyz;
	//�@���x�N�g��
	float3x3 matTBN = float3x3(normalize(PSInput.WTangent), normalize(PSInput.WBinormal), normalize(PSInput.WNormal));
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoord.xy).xyz*2.0 - 1.0), matTBN);
	//���_�����x�N�g��
	float3 V = normalize(g_WorldViewPosition.xyz - PSInput.WPosition.xyz);
	//���C�g�����x�N�g��
	float3 L= normalize(lLightDir);
	//�n�[�t�x�N�g��
	float3 H = normalize(L + V);

	//���C�g�܂ł̋��������߂�
	float lLightDistance = length(lLightDir);
	//�����ɂ�錸���̌v�Z
	float lRangeAttenuation = smoothstep(g_LightRange, 0.0, lLightDistance);
	//���C�g�̃x�N�g���ƃ��C�g�̕����x�N�g���̓��ς��v�Z
	float CosDir = dot(-L, normalize(g_LightDirection.xyz));
	//�X�|�b�g���C�g�̌��ʂ��v�Z
	float SpotEffect = smoothstep(g_LightCosOuterAngle, g_LightCosInnerAngle, CosDir);
	//�����ɂ�錸���ƍ���
	float Attenuation = lRangeAttenuation*SpotEffect;

	//�e�N�X�`���J���[�̎擾
	float4 TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);
	float4 TextureSpecularColor = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoord.xy);

	//�����̌v�Z
	float3 AmbientColor = g_LightAmbientColor.rgb*TextureDiffuseColor.rgb;
	//�g�U���ˌ��̌v�Z
	float Diffuse = max(dot(L, N), 0.0);
	float3 DiffuseColor = g_LightDiffuseColor.rgb*TextureDiffuseColor.rgb*g_Common.Material.Diffuse.rgb*Diffuse;
	//���ʔ��ˌ��̌v�Z
	float Specular = pow(max(dot(N, H), 0.0), g_Common.Material.Power);
	float3 SpecularColor = g_LightSpecularColor.rgb * TextureSpecularColor.rgb*g_Common.Material.Specular.rgb*Specular;
	//���ȏƖ��̌v�Z
	float3 EmissiveColor = TextureDiffuseColor.rgb*g_Common.Material.Ambient_Emissive.rgb;

	//�o�̓J���[�̌v�Z
	float4 OutputColor;
	OutputColor.rgb = (AmbientColor + DiffuseColor + SpecularColor)*Attenuation + EmissiveColor;
	OutputColor.a = TextureDiffuseColor.a;
	return OutputColor;


}