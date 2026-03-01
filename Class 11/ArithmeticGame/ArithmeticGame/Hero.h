#pragma once
#include <string>

#include "Attacker.h"

class Hero final : public Attacker 
{
public:
	Hero(const uint16_t& health, const uint16_t& strength, const std::string& name) :
		Attacker(health, strength, name) {};

	virtual ~Hero() {};

	virtual uint16_t GetMoney() const final;

	virtual uint16_t GetExperience() const final;

	virtual void SetMoney(const uint16_t&) final;

	virtual void SetExperience(const uint16_t&) final;


	virtual bool IsEnemy() const;

private:
	uint16_t money_ = 0, experience_ = 0;
};

