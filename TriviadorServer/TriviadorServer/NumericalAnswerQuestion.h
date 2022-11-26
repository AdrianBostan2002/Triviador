#pragma once
#include "Question.hpp"
#include <iostream>
#include <string>

class NumericalAnswerQuestion: 
	public Question<int>
{
public:
	NumericalAnswerQuestion() = default;
	NumericalAnswerQuestion(const std::string& question, int rightAnswer);

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);
	/*friend bool operator==(const NumericalAnswerQuestion<T>& naq1, const NumericalAnswerQuestion<T>& naq2)
	{
		return naq1.m_rightAnswer == naq2.m_rightAnswer && naq1.m_question == naq2.m_question;
	}*/

};





