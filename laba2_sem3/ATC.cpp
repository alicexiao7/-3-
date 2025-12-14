#include "ATC.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

static std::string toLower(const std::string& s) {
    std::string r;
    r.reserve(s.size());
    for (unsigned char c : s)
        r.push_back(static_cast<char>(std::tolower(c)));
    return r;
}

std::string callTypeToString(CallType t) {
    switch (t) {
    case CallType::LOCAL:     return "LOCAL";
    case CallType::INTERCITY: return "INTERCITY";
    }
    return "UNKNOWN";
}


Tariff::Tariff()
    : city_(""), price_(0.0), type_(CallType::INTERCITY) {
}

Tariff::Tariff(const std::string& city, double price, CallType type)
    : city_(city), price_(price), type_(type) {
}

std::string Tariff::city() const {
    return city_;
}

double Tariff::price() const {
    return price_;
}

CallType Tariff::type() const {
    return type_;
}

void Tariff::print() const {
    std::cout << std::left << std::setw(20) << city_
        << std::setw(6) << price_ << " руб/мин "
        << callTypeToString(type_) << "\n";
}

Call::Call()
    : clientSurname_(""), city_(""), minutes_(0), type_(CallType::INTERCITY) {
}

Call::Call(const std::string& surname,
    const std::string& city,
    int minutes,
    CallType type)
    : clientSurname_(surname),
    city_(city),
    minutes_(minutes),
    type_(type) {
}

std::string Call::clientSurname() const {
    return clientSurname_;
}

std::string Call::city() const {
    return city_;
}

int Call::minutes() const {
    return minutes_;
}

CallType Call::type() const {
    return type_;
}

void Call::print() const {
    std::cout << "Client: " << clientSurname_
        << " To: " << city_
        << " " << minutes_ << " min "
        << callTypeToString(type_) << "\n";
}


Client::Client()
    : surname_(""), name_("") {
}

Client::Client(const std::string& surname, const std::string& name)
    : surname_(surname), name_(name) {
}

std::string Client::surname() const {
    return surname_;
}

std::string Client::name() const {
    return name_;
}

void Client::addCall(const Call& c) {
    calls_.push_back(c);
}

const std::vector<Call>& Client::calls() const {
    return calls_;
}

void Client::print() const {
    std::cout << surname_ << " (" << name_ << ")\n";
}

ATC::ATC() {}
ATC::~ATC() {}

ATC& ATC::instance() {
    static ATC instance;
    return instance;
}

ATC::TariffKey ATC::makeTariffKey(const std::string& cityLower, CallType t) {
    return cityLower + "#" + std::to_string(static_cast<int>(t));
}

bool ATC::addTariff(const Tariff& t) {
    TariffKey key = makeTariffKey(toLower(t.city()), t.type());
    tariffs_[key] = t;
    return true;
}

bool ATC::addClient(const Client& c) {
    std::string key = toLower(c.surname());
    if (clients_.find(key) != clients_.end())
        return false;

    clients_.emplace(key, c);
    return true;
}

bool ATC::registerCall(const Call& call) {
    std::string key = toLower(call.clientSurname());
    auto it = clients_.find(key);
    if (it == clients_.end())
        return false;

    it->second.addCall(call);
    return true;
}

double ATC::costForCall(const Call& call) const {
    TariffKey key = makeTariffKey(toLower(call.city()), call.type());
    auto it = tariffs_.find(key);
    if (it == tariffs_.end())
        return 0.0;

    return call.minutes() * it->second.price();
}

double ATC::costForClient(const std::string& surname) const {
    std::string key = toLower(surname);
    auto it = clients_.find(key);
    if (it == clients_.end())
        return -1.0;

    double sum = 0.0;
    for (const auto& c : it->second.calls())
        sum += costForCall(c);

    return sum;
}

double ATC::totalCostAllCalls() const {
    double sum = 0.0;
    for (const auto& p : clients_) {
        for (const auto& c : p.second.calls())
            sum += costForCall(c);
    }
    return sum;
}

void ATC::listTariffs() const {
    if (tariffs_.empty()) {
        std::cout << "Тарифов нет.\n";
        return;
    }
    for (const auto& p : tariffs_)
        p.second.print();
}

void ATC::listClients() const {
    if (clients_.empty()) {
        std::cout << "Клиентов нет.\n";
        return;
    }
    for (const auto& p : clients_)
        p.second.print();
}

void ATC::listAllCalls() const {
    std::cout << "ВСЕ ЗВОНКИ\n";
    for (const auto& p : clients_) {
        for (const auto& c : p.second.calls())
            c.print();
    }
}
