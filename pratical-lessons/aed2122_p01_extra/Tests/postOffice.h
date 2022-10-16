#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "mail.h"
#include "postman.h"
#include <vector>


class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	vector<Mail *> removePostman(string name);
	vector<Mail *> endOfDay(unsigned int &balance);
	Postman addMailToPostman(Mail *m, string name);
};

class NoPostmanException
{
    string postmanName;

public:
    NoPostmanException (string postmanName) : postmanName(postmanName) {};
    string getName() const {return this->postmanName; }
};






#endif /* SRC_POSTOFFICE_H_ */
