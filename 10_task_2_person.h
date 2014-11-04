#ifndef _10_TASK_2_PERSON_H_
#define _10_TASK_2_PERSON_H_

#include "10_task_2_includes.h"

class Person 
{
private:
	static const int LIMIT = 25;
	string lname; // Person�s last name
	char fname[LIMIT]; // Person�s first name
public:
	Person() {lname = ""; fname[0] = '\0'; } // #1
	Person(const string & ln, const char * fn = "Heyyou"); // #2
	// the following methods display lname and fname
	void Show() const; // firstname lastname format
	void FormalShow() const; // lastname, firstname format
};

#endif