#include "Question.h"

std::string Question::GetQuestion() const {
	return question_;
};


bool Question::Check(std::string entered) const {
	if (!(parameters_ & QUESTION_CASE_SENSITIVE)) {
		toLowercase(entered);
	}
	if (parameters_ & QUESTION_IGNORE_SPACES) {
		removeSpaces(entered);
	}
	return answer_ == entered;
}


void Question::toLowercase(std::string& str) const {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return;
}

void Question::removeSpaces(std::string& str) const {
	remove_if(str.begin(), str.end(), isspace);
	return;
}