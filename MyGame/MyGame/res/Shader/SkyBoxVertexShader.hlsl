#include"DxLibVertexShader.hlsli"

struct VS_INPUT {

	float4 Position :POSITION;//���[�J�����W
};

struct VS_OUTPUT {
	float3 TexCoord:TEXCOORD0;//�e�N�X�`�����W(6�ʍ��W�̂��߁AVector3�Ƃ��ēn��)
	float4 Position:SV_POSITION;//���W(�v���W�F�N�V�������W�n�֕ϊ��ς̂���)


};

//�X�J�C�{�b�N�X�p�̃V�F�[�_�[�A�J�����ɋ߂Â���������=�J�����ɂ�镽�s�ړ����s��Ȃ��悤�ɂ���
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;
	float4 lViewPosition;

	//���_���W�n�ɕϊ��A�J�����̈ʒu�͍l�����Ȃ��悤�ɂ���(�J�����ɋ߂Â������Ȃ��悤�ɂ���)
	lViewPosition.x = dot(VSInput.Position.xyz, g_Base.ViewMatrix[0].xyz);
	lViewPosition.y = dot(VSInput.Position.xyz, g_Base.ViewMatrix[1].xyz);
	lViewPosition.z = dot(VSInput.Position.xyz, g_Base.ViewMatrix[2].xyz);
	lViewPosition.w = 1.0;

	//Projection(���K���f�o�C�X���W�n)�ւ̕ϊ����s��
	VSOutput.Position.x = dot(lViewPosition, g_Base.ProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, g_Base.ProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, g_Base.ProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, g_Base.ProjectionMatrix[3]);
	//���f���̃��[�J�����W�����̂܂܃e�N�X�`�����W�ɓ���鎖�ŁA
	VSOutput.TexCoord.xyz = VSInput.Position.xyz;

	return VSOutput;
}