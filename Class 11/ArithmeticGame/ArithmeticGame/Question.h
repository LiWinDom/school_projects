#pragma once
#define QUESTION_NONE			0
#define QUESTION_CASE_SENSITIVE 1 << 0
#define QUESTION_IGNORE_SPACES  1 << 1
#define QUESTION_DEFAULT QUESTION_IGNORE_SPACES

#include <algorithm>
#include <string>

class Question final
{
public:
	Question(const std::string& question, const std::string& answer, const uint8_t& parameters = QUESTION_DEFAULT) :
		question_(question), answer_(answer), parameters_(parameters) {
		if (!(parameters_ & QUESTION_CASE_SENSITIVE)) {
			toLowercase(answer_);
		}
		if (parameters_ & QUESTION_IGNORE_SPACES) {
			removeSpaces(answer_);
		}
	}

	virtual ~Question() {};

	virtual std::string GetQuestion() const final;


	virtual bool Check(std::string) const final;

private:
	const std::string question_;
	std::string answer_;
	const uint8_t parameters_;

	virtual void toLowercase(std::string&) const final;

	virtual void removeSpaces(std::string&) const final;
};
