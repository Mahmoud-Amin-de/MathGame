#include<iostream> 
#include<cstdlib>
#include<ctime>
using namespace std;


enum enQuestionsLevel { EasyLevel = 1, MediumLevel = 2, HardLevel = 3, MixLevel = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOperation = 5 };

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionsList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

string GetOperationTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";

	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}



void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [ " << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
	cout << GetOperationTypeSymbol(Quizz.QuestionsList[QuestionNumber].OperationType);
	cout << "\n__________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer == Quizz.QuestionsList[QuestionNumber].CorrectAnswer)
	{
		Quizz.NumberOfRightAnswers++;
		Quizz.QuestionsList[QuestionNumber].AnswerResult = true;

		cout << "Right Answer :-) \n";
	}
	else
	{
		Quizz.NumberOfWrongAnswers++;
		Quizz.QuestionsList[QuestionNumber].AnswerResult = false;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is : ";
		cout << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}

	cout << endl;

	SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);


}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enOperationType GetRandomOperationType() {
	return (enOperationType)RandomNumber(1, 4);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "-----------------------------\n\n";
	cout << "Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n---------------------------\n\n";


	cout << "Number of Questions:     " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level:         " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType:                  " << GetOperationTypeSymbol(Quizz.OperationType) << "\n";
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "------------------------------\n";

}

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::MixLevel)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOperation)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::MediumLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}


}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
	}
}

enOperationType ReadOperationsType()
{
	short OperationType = 1;
	do
	{
		cout << "Enter Operations Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType >5);

	return (enOperationType)OperationType;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel >4);

	return (enQuestionsLevel)QuestionsLevel;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions Do You Want To Answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);

	return NumberOfQuestions;
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OperationType = ReadOperationsType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{

		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N ? ";
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	// Seeds the random number generator
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

