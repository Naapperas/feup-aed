#include "parque.h"
#include <algorithm>
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot) {};

unsigned ParqueEstacionamento::getNumMaximoClientes() const { return this->numMaximoClientes; };

unsigned ParqueEstacionamento::getNumLugares() const { return this->lotacao; };

int ParqueEstacionamento::posicaoCliente(const string & nome) const {

    for (auto i = 0; i < this->clientes.size(); ++i)
        if (this->clientes.at(i).nome == nome) return i;

    return -1;
};

bool ParqueEstacionamento::adicionaCliente(const string & nome) {

    if (this->clientes.size() == this->getNumMaximoClientes()) return false;

    this->clientes.push_back({nome, false});
    return true;
};

bool ParqueEstacionamento::entrar(const string & nome) {

    if (this->posicaoCliente(nome) == -1 || this->clientes.at(this->posicaoCliente(nome)).presente || this->vagas == 0)
        return false;

    this->clientes.at(this->posicaoCliente(nome)).presente = true;
    this->vagas--;

    return true;
};

bool ParqueEstacionamento::retiraCliente(const string & nome) {

    if (this->posicaoCliente(nome) == -1 || this->clientes.at(this->posicaoCliente(nome)).presente)
        return false;

    this->clientes.erase(this->clientes.cbegin() + this->posicaoCliente(nome));

    return true;
}

bool ParqueEstacionamento::sair(const string & nome) {

    if (this->posicaoCliente(nome) == -1 || !this->clientes.at(this->posicaoCliente(nome)).presente)
        return false;

    this->clientes.at(this->posicaoCliente(nome)).presente = false;

    return true;
};

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    vector<InfoCartao> ret;
    std::copy_if(this->clientes.begin(), this->clientes.end(), std::back_inserter(ret), [](InfoCartao i){ return i.presente; });
    return ret.size();
};

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return this->clientes.size();
};


