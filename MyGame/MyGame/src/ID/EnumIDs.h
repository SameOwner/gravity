#pragma once

//���f��ID
enum class MODEL_ID {
	MODEL_PLAYER,
	MODEL_SKYBOX,
	MODEL_STAGE,
};
enum class SPRITE_ID {
	SPRITE_FLOATGAUGE,//���V�Q�[�W�X�v���C�g
	SPRITE_WINDEFFECT//���G�t�F�N�g�X�v���C�g
};
enum class BGM_ID {

};
enum class SE_ID {

};
enum class FONT_ID {

};
//Effekseer�𗘗p�����G�t�F�N�g�pID
enum class EFFECT_ID {

};
//�Q�[�����ŗ��p����V�[����񋓂���
enum class SceneType {
	SCENE_TITLE,
	SCENE_LOADING,
	SCENE_GAMEPLAY,
	SCENE_GAMEOVER,
	SCENE_CLEAR,
	SCENE_CREDIT,
	SCENE_EXIT,//�_�~�[�V�[��

};

//���b�Z�[�W�ɂ��Actor�Ԃ̑���
enum class EventMessage {

};

//Actor�̃O���[�v����
enum class ActorGroup {
	ETCETERA_ACTOR,//�Q�[���Ɋ֗^���Ȃ��A�N�^�[
	PLAYER_ACTOR,//�v���C���[
	POINT_ACTOR,//�`�F�b�N�|�C���g
};