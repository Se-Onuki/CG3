#include <iostream>
#include <stdint.h>

class Enemy
{
public:

	enum class State : uint32_t {
		kApproach,
		kFire,
		kLeave
	};

public:
	Enemy() = default;
	~Enemy() = default;

	void Init();
	void Update();
	void Draw();

	const auto &GetState() const { return enemyState_; }

private:

	float speed_ = 0.5f;

	float position_ = -10.f;

	Enemy::State enemyState_ = State::kApproach;

	void ApproachState();
	void FireState();
	void LeaveState();

	static void(Enemy:: *stateTable_[])();
	static const std::string kStateName_[];


};


int main(void) {
	Enemy enemy;
	enemy.Init();

	while (true) {
		if (enemy.GetState() == Enemy::State::kLeave) {
			break;
		}
		enemy.Update();

		enemy.Draw();

	}

	return 0;
}

void (Enemy:: *Enemy::stateTable_[])() = {	// staticの関数ポインタ配列の変数に、関数のアドレスを定義する。
	&Enemy::ApproachState,
	&Enemy::FireState,
	&Enemy::LeaveState
};

const std::string Enemy::kStateName_[] = {
	"ApproachState",
	"FireState",
	"LeaveState"
};

void Enemy::Init() {
}

void Enemy::Update() {
	uint32_t stateNumber = static_cast<uint32_t>(enemyState_);
	(this->*stateTable_[stateNumber])();
}

void Enemy::Draw() {
	std::cout << kStateName_[static_cast<size_t>(enemyState_)] << " : position [" << position_ << "]" << std::endl;
}

void Enemy::ApproachState() {
	position_ += speed_;

	if (position_ >= -3.f) {
		enemyState_ = State::kFire;
	}
}

void Enemy::FireState() {
	position_ += speed_;

	if (position_ >= 0.f) {
		enemyState_ = State::kLeave;
	}
}

void Enemy::LeaveState() {
}
