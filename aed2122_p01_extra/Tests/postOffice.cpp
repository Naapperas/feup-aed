#include "postOffice.h"
#include <string>
#include <algorithm>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

//--------

vector<Mail *> PostOffice::removePostman(string name) {
	vector<Mail *> res;

    for (auto it = this->postmen.begin(); it != this->postmen.end(); ++it)
        if (it->getName() == name) {
            res = it->getMail();
            this->postmen.erase(it);
            break;
        }

    return res;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
	vector<Mail *> res;

    balance = 0;
    for (auto it = this->mailToSend.begin(); it != this->mailToSend.end(); it++) {
        auto mail = *it;
        balance += mail->getPrice();

        if (this->firstZipCode < mail->getZipCode() && mail->getZipCode() < this->lastZipCode)
            this->addMailToDeliver(mail);
        else
            res.push_back(mail);

        this->mailToSend.erase(it--);
    }

	return res;
}


Postman PostOffice::addMailToPostman(Mail *m, string name) {

    for (auto& p : this->postmen)
        if (p.getName() == name) {
            p.addMail(m);
            return p;
        }

    throw NoPostmanException(name);
}

