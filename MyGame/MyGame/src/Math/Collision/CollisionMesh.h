#pragma once
#include<DxLib.h>
#include"../Vector3.h"
#include"../Matrix.h"
#include"CollisionTriangle.h"
#include<cmath>
#include"../../Graphic/DebugDraw.h"
#include"../../Conv/DXConverter.h"

class CollisionMesh {
public:
	CollisionMesh(int model) :model_{ model } {
	}
	//���b�V���Ɛ����̓����蔻��
	bool collide_line(const VECTOR& start, const VECTOR& end, VECTOR* point = nullptr, VECTOR* normal = nullptr)const {
		//�������Ă��邩�𒲂ׂāA��_�Ɩ@����Ԃ�
		const auto coll_poly = MV1CollCheck_Line(model_, 0, start, end);
		//��_�Ɩ@���f�[�^������
		if (coll_poly.HitFlag == TRUE) {
			if (point != nullptr) {
				*point = coll_poly.HitPosition;
			}
			if (normal != nullptr) {
				*normal = coll_poly.Normal;
			}
		}
		return coll_poly.HitFlag == TRUE;
	}
	//���b�V���Ƌ��̂̓����蔻��
	bool collide_sphere(const VECTOR& center, float radius, VECTOR* result = nullptr)const {
		//���f���Ƌ��̂̓����蔻��֐��A����������������
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//�Փ˔���f�[�^�̍폜�Acoll_poly�̓������m�ۂ𓮓I�ɍs���Ă��邽�߁APoly�p��delete����̊֐����ĂԕK�v������
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//���ʂƓ_�̏Փˊ֌W���̓��ꕨ
			PLANE_POINT_RESULT plane_point_result;
			//�������ʂƓ_�̓����蔻����s���A���ʏ�Ɉ�ԋ߂��_�𒲂ׂ��肵�Ă����
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//���ʂ̂����D���ȓ_�A���ʏ�ł����position[0]�łȂ��Ă��ǂ�
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//����ɖ������ʂƁA���g�̓_�̍ł��߂��_�̏�񓙂�����
				);

			//�O�p�`�̒��ɁA�������ʂ̂�����ԋ߂��_�������Ă��邩�𒲂ׂ�=�O�p�`�̒��ɒ��S�_�������Ă��邩�𒲂ׂ�
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//�ʂɓ������Ă���A�ʂ̖@�������ɉ����o���A�傫����offset�A�߂荞�ݕ����������o��
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//�@�������ɉ����o���x�N�g���̌v�Z
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//�|���S���ƕӂ̔���
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	bool collide_sphere(const VECTOR& center,const VECTOR& previous, float radius, VECTOR* result = nullptr)const {
		//���f���Ƌ��̂̓����蔻��֐��A����������������
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//�Փ˔���f�[�^�̍폜�Acoll_poly�̓������m�ۂ𓮓I�ɍs���Ă��邽�߁APoly�p��delete����̊֐����ĂԕK�v������
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//���ʂƓ_�̏Փˊ֌W���̓��ꕨ
			PLANE_POINT_RESULT plane_point_result;
			//�������ʂƓ_�̓����蔻����s���A���ʏ�Ɉ�ԋ߂��_�𒲂ׂ��肵�Ă����
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//���ʂ̂����D���ȓ_�A���ʏ�ł����position[0]�łȂ��Ă��ǂ�
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//����ɖ������ʂƁA���g�̓_�̍ł��߂��_�̏�񓙂�����
			);

			//�O�p�`�̒��ɁA�������ʂ̂�����ԋ߂��_�������Ă��邩�𒲂ׂ�=�O�p�`�̒��ɒ��S�_�������Ă��邩�𒲂ׂ�
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
			).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//�ʂɓ������Ă���A�ʂ̖@�������ɉ����o���A�傫����offset�A�߂荞�ݕ����������o��
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//�@�������ɉ����o���x�N�g���̌v�Z
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//�|���S���ƕӂ̔���
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
			).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	bool collide_capsule(const VECTOR& start, const VECTOR& end, float radius, VECTOR* result = nullptr) {
		//�����������ǂ���
		bool isHit = false;

		//�n�_�A�I�_���擾
		VECTOR resultstart=start;
		VECTOR resultend=end;

		//��������ɂ��������o��������s��
		if (collide_sphere(resultend, radius, &resultend)) {
			//��������̉����o���x�N�g�����쐬
			Vector3 moveVecbottom = VSub(resultend, end);
			//�J�v�Z���̎n�_�ɉ����o����K�p
			resultstart = VAdd(resultstart, moveVecbottom);
			isHit = true;
		}
		//���������o�����_�̎n�_�A�I�_����ۑ�
		VECTOR savestart = resultstart;
		VECTOR saveend = resultend;

		//������ɂ��������o��������s��
		if (collide_sphere(resultstart, radius, &resultstart)) {
			//������̉����o���x�N�g�����쐬
			Vector3 moveVectop = VSub(resultstart, savestart);
			//�J�v�Z���̏I�_�ɉ����o����K�p
			resultend = VAdd(resultend, moveVectop);
			isHit = true;
		}
		//�����܂łŎn�_�I�_�̉����o��������

		//���S���v�Z���ĕԂ�
		//if(isHit)*result = (resultstart+ resultend)*0.5f;

		// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, resultstart, resultend, radius);

		for (int i = 0; i < HitDim.HitNum; i++) {
			VECTOR triangle[4]{
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2],
				HitDim.Dim[i].Position[0]
			};

			for (int loop = 0; loop < 3; loop++) {
				SEGMENT_SEGMENT_RESULT seg_seg_result;
				Segment_Segment_Analyse(&resultstart, &resultend, &triangle[i], &triangle[i + 1], &seg_seg_result);
				const auto distance = std::sqrt(seg_seg_result.SegA_SegB_MinDist_Square);
				if (distance <= radius) {
					isHit = true;
					VECTOR offset = VScale(VNorm(VSub(seg_seg_result.SegA_MinDist_Pos, seg_seg_result.SegB_MinDist_Pos)), radius - distance);
					resultstart = VAdd(resultstart, offset);
					resultend = VAdd(resultend, offset);
				}
			}
		}
		if (isHit)*result = (resultstart + resultend)*0.5f;

		//�|���S�����J������
		MV1CollResultPolyDimTerminate(HitDim);

		return isHit;

	}
	bool collide_capsule(const VECTOR& start1, const VECTOR& end1, float radius1, const VECTOR& start2, const VECTOR& end2, float radius2, VECTOR* result1 = nullptr, VECTOR* result2 = nullptr) {
		//�����������ǂ���
		bool isHit = false;

		//�n�_�A�I�_���擾
		VECTOR resultstart1 = start1;
		VECTOR resultend1 = end1;
		VECTOR resultstart2 = start2;
		VECTOR resultend2 = end2;

		if (collide_sphere(resultend1, radius1, &resultend1)) {
			//��������̉����o���x�N�g�����쐬
			Vector3 moveVecbottom = VSub(resultend1, end1);
			//�J�v�Z���̎n�_�ɉ����o����K�p
			resultend2 = VAdd(resultend2, moveVecbottom);
			isHit = true;
		}
		if (collide_sphere(resultend2, radius2, &resultend2)) {
			//��������̉����o���x�N�g�����쐬
			Vector3 moveVecbottom2 = VSub(resultend2, end2);
			//�J�v�Z���̎n�_�ɉ����o����K�p
			resultend1 = VAdd(resultend1, moveVecbottom2);
			isHit = true;
		}

		//���S���v�Z���ĕԂ�
		if (isHit) {
			*result1 = resultend1;
			*result2 = resultend2;
		}
		return isHit;

	}

private:
	int model_;
};