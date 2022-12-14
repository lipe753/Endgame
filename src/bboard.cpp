#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <exception>

#include "bboard.hpp"

#include "rota.hpp"
#include "User.hpp"
#include "client.hpp"
#include "driver.hpp"
#include "adm.hpp"

bboard* bboard::instancia = nullptr;

bboard::bboard() : title("ENDGAME BUS") {}

bboard* bboard::get_instance() {
    if(instancia == nullptr) {
        instancia = new bboard();
    }

    return instancia;
}

void bboard::cadastrar(std::string& cargo, std::string& usuario, std::string& senha) {
    for(std::vector<User*>::iterator iterator = get_instance()->user_list.begin(); iterator != get_instance()->user_list.end(); iterator++) {
        if((*iterator)->available(usuario)) {
            throw std::exception();
        }
    }

    if(cargo == "client") {
        get_instance()->user_list.push_back(new client(usuario,senha));
    }

    if(cargo == "driver") {
        get_instance()->user_list.push_back(new driver(usuario,senha));
    }

    if(cargo == "adm") {
        get_instance()->user_list.push_back(new adm(usuario,senha));
    }
}

bool bboard::login() {
    std::string sn, pw;
    bool found = false;

    std::cout << "\nBEM VINDO A " << title << std::endl;

    while(!found) {
        std::cout << "\nDigite o seu usuario ('exit' para encerrar): ";
        std::cin >> sn;
        std::cin.clear();

        if(sn == "exit") {
            break;
        }

        std::cout << "Digite sua senha: ";
        std::cin >> pw;
        std::cin.clear();

        for(std::vector<User*>::iterator iterator = get_instance()->user_list.begin(); iterator != get_instance()->user_list.end(); iterator++) {
            if((*iterator)->check(sn, pw)) {
                std::cout << "\nAcesso concedido!" << std::endl;
                (*iterator)->painel();
                found = true;
                break;
            }
        }

        if(!found) {
            std::cout << "Usuario ou senha incorreta!" << std::endl;
        }
    }

    return found;
}

void bboard::adicionarRota(rota x) {
    get_instance()->rotas.push_back(x);
    return;
}

void bboard::removerRota(rota y) {
    for(std::vector<rota>::iterator iterator = get_instance()->rotas.begin(); iterator != get_instance()->rotas.end(); iterator++) {
        if(iterator->descricaoRota() == y.descricaoRota()) {
            get_instance()->rotas.erase(iterator);
            break;
        }
    }

    return;
}

void bboard::decrementarTicketDaRota(rota alvo) {
    for(int i = 0; i < get_instance()->rotas.size(); i++) {
        if(get_instance()->rotas[i].descricaoRota() == alvo.descricaoRota()) {
	if(bboard::get_instance()->rotas[i].getTickets()<= 0) {
    	throw std::exception();
    }
            get_instance()->rotas[i].decrementarTickets();
            break;
        }
    }

    return;
}


