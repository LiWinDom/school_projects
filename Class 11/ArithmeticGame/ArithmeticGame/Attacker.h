#pragma once
#include <algorithm>
#include <string>

class Attacker abstract
{
public:
	Attacker(const uint16_t& health, const uint16_t& strength, const std::string& name = "") :
		health_(health), strength_(strength), name_(name) {}

	virtual ~Attacker() {}

	virtual uint16_t GetHealth() const final;

	virtual uint16_t GetStrength() const final;

	virtual std::string GetName() const final;

	virtual void SetHealth(const uint16_t&) final;

	virtual void SetStrength(const uint16_t&) final;


	virtual bool IsAlive() const final;

	virtual bool IsEnemy() = 0;

	virtual void Damage(const uint16_t&) final;

	virtual void Attack(Attacker*) final;

protected:
	uint16_t health_, strength_;
	const std::string name_;
};

