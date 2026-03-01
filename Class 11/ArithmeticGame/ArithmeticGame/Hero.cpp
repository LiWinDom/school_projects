#include "Hero.h"

uint16_t Hero::GetMoney() const {
	return money_;
};

uint16_t Hero::GetExperience() const {
	return experience_;
};

void Hero::SetMoney(const uint16_t& money) {
	money_ = money;
	return;
};

void Hero::SetExperience(const uint16_t& exp) {
	experience_ = exp;
};


bool Hero::IsEnemy() const {
	return false;
}