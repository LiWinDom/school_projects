#include "Enemy.h"

std::string Enemy::GetQuestion() const {
	return question_.GetQuestion();
};


bool Enemy::IsEnemy() const {
	return true;
}

bool Enemy::Check(const std::string& answer) const {
	return question_.Check(answer);
};