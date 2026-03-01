#pragma once
#include <string>

#include "Attacker.h"
#include "Question.h"

class Enemy abstract : public Attacker
{
public:
	Enemy(const uint16_t& health, const uint16_t& strength, const std::string& name, const Question question, const uint16_t& money) :
		Attacker(health, strength, name), question_(question), money_(money) {};

	virtual ~Enemy() {};

	virtual std::string GetQuestion() const final;


	virtual bool IsEnemy() const final;

	virtual bool Check(const std::string& answer) const final;

protected:
	const uint16_t money_;

	const Question question_;
};

