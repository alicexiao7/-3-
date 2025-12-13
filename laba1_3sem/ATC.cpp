#include "ATC.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

ATC::ATC() : address_(""), subscriptionFee_(0.0), subscribers_(0) {}

void ATC::setAddress(const std::string& addr) {
    if (addr.empty()) {
        throw std::invalid_argument("Адрес не может быть пустым");
    }
    address_ = addr;
}

std::string ATC::getAddress() const {
    return address_;
}

void ATC::setSubscriptionFee(double fee) {
    if (fee <= 0) {
        throw std::invalid_argument("Абонентская плата должна быть положительной");
    }
    subscriptionFee_ = fee;
}

double ATC::getSubscriptionFee() const {
    return subscriptionFee_;
}

void ATC::setSubscribers(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Количество абонентов должно быть положительным");
    }
    subscribers_ = n;
}

double ATC::calculateTotalFee() const {
    return subscriptionFee_ * subscribers_;
}


void showMenu(){
    std::cout<<"1:Задать даннные для АТС"<< std::endl;
    std::cout<<"2:Посчитать сумму общей абонентской платы"<< std::endl;
    std::cout<<"3:Изменить абонентскую плату"<< std::endl;
    std::cout<<"4:Узнать абонентскую плату"<< std::endl;
    std::cout<<"5:Изменить число абонентов"<< std::endl;
    std::cout<<"6: Завершить сеанс"<< std::endl;
    std::cout<<"Выберите номер действия, которое хотите совершить: "<< std::endl;
}
// ==== ФУНКЦИИ ВАЛИДАЦИИ ====

int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым.\n";
            continue;
        }

        bool valid = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                valid = false;
                break;
            }
        }

        if (valid) {
            try {
                value = std::stoi(input);
                if (value > 0) return value;
            } catch (...) {}
        }
        std::cout << "Ошибка: введите положительное целое число.\n";
    }
}

double getValidDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым.\n";
            continue;
        }

        try {
            value = std::stod(input);
            if (value > 0) return value;
        } catch (...) {}
        std::cout << "Ошибка: введите положительное число.\n";
    }
}

std::string getValidString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым.\n";
            continue;
        }

        bool valid = true;
        for (char c : input) {
            if (!(std::isalpha(static_cast<unsigned char>(c)) || c == ' ' || c == ',' || c == '.')) {
                valid = false;
                break;
            }
        }

        if (valid) return input;

        std::cout << "Ошибка: допускаются только буквы, пробелы, запятые и точки.\n";
    }
}

