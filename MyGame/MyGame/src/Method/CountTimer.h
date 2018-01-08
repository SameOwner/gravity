#pragma once

//回数を数える(nカウント目に通知する)
//*例:count_=60 60回呼ばれたらtrue
class CountTimer {
public:
	CountTimer() {

	}
	//回数を設定
	void set(int count) {
		count_ = count;
	}
	bool operator ()() {
		count_--;
		return count_ <= 0;
	}
private:
	int count_{ 0 };//実行回数
};