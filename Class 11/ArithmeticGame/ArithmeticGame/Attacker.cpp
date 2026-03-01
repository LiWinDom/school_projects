#include "Attacker.h"

uint16_t Attacker::GetHealth() const {
	return health_;
}

uint16_t Attacker::GetStrength() const {
	return strength_;
}

std::string Attacker::GetName() const {
	return name_;
}

void Attacker::SetHealth(const uint16_t& health) {
	health_ = health;
	return;
}

void Attacker::SetStrength(const uint16_t& strength) {
	strength_ = strength;
	return;
}


bool Attacker::IsAlive() const {
	return health_ > 0;
}

void Attacker::Damage(const uint16_t& strength) {
	if (strength > health_) {
		health_ = 0;
		return;
	}
	health_ -= strength;
	return;
}

void Attacker::Attack(Attacker* target) {
	target->Damage(strength_);
	return;
}