#pragma once

//���f��ID
enum class MODEL_ID {
	MODEL_PLAYER,
	MODEL_SKYBOX,
	MODEL_STAGE,
	MODEL_CAR,
	MODEL_ENEMY,
	MODEL_CITIZEN_USAUSA,

};
enum class SPRITE_ID {
	SPRITE_FLOATGAUGE,//���V�Q�[�W�X�v���C�g
	SPRITE_FLOATGAUGE_FRAME,//���V�Q�[�W�g�X�v���C�g
	SPRITE_WINDEFFECT,//���G�t�F�N�g�X�v���C�g
	SPRITE_FIELDMAP,//�t�B�[���h�}�b�v�X�v���C�g
	SPRITE_TITLEBACK,//�^�C�g���o�b�N�X�v���C�g
	SPRITE_TITLELOGO,//�^�C�g�����S�X�v���C�g
	SPRITE_TITLEBUTTON,//�^�C�g���{�^���X�v���C�g
	SPRITE_GAMECLEAR,//�Q�[���N���A�X�v���C�g
	FADE_SPRITE,//�t�F�[�h�X�v���C�g
};
enum class BGM_ID {
	SOUND_TITLE,
	SOUND_GAME,
	SOUND_CLEAR
};
enum class SE_ID {
	SELECT_SE,//�I��
	RUN_SE,//����
	WIND_SE,//�ړ�������
	JUMP_SE,//�W�����v
	LAND_SE,//���n
	HIT_SE,//�ڐG
};
enum class FONT_ID {
	FONT_COUNT,//�J�E���g�p�t�H���g
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
	Hit_Car,
	Hit_Bullet,
};

//Actor�̃O���[�v����
enum class ActorGroup {
	ETCETERA_ACTOR,//�Q�[���Ɋ֗^���Ȃ��A�N�^�[
	PLAYER_ACTOR,//�v���C���[
	CAR_ACTOR,//�ԃA�N�^�[
	POINT_ACTOR,//�`�F�b�N�|�C���g
	ENEMY_ACTOR,//�G
	CITIZEN_ACTOR,//�Z��
};