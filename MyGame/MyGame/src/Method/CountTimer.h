#pragma once

//�񐔂𐔂���(n�J�E���g�ڂɒʒm����)
//*��:count_=60 60��Ă΂ꂽ��true
class CountTimer {
public:
	CountTimer() {

	}
	//�񐔂�ݒ�
	void set(int count) {
		count_ = count;
	}
	bool operator ()() {
		count_--;
		return count_ <= 0;
	}
private:
	int count_{ 0 };//���s��
};