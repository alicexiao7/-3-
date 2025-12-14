#ifndef ATC_H
#define ATC_H

#include <string>
#include <unordered_map>
#include <vector>

// тип звонка
enum class CallType { LOCAL = 0, INTERCITY = 1 };

std::string callTypeToString(CallType t);


class Tariff {
    std::string city_;
    double price_;
    CallType type_;
public:
    Tariff();
    Tariff(const std::string& city, double price, CallType type);
    std::string city() const;
    double price() const;
    CallType type() const;
    void print() const;
};


class Call {
    std::string clientSurname_;
    std::string city_;
    int minutes_;
    CallType type_;
public:
    Call();
    Call(const std::string& surname, const std::string& city,
        int minutes, CallType type);
    std::string clientSurname() const;
    std::string city() const;
    int minutes() const;
    CallType type() const;
    void print() const;
};


class Client {
    std::string surname_;
    std::string name_;
    std::vector<Call> calls_;
public:
    Client();
    Client(const std::string& surname, const std::string& name);
    std::string surname() const;
    std::string name() const;
    void addCall(const Call& c);
    const std::vector<Call>& calls() const;
    void print() const;
};

class ATC {
private:
    using TariffKey = std::string;
    std::unordered_map<TariffKey, Tariff> tariffs_;
    std::unordered_map<std::string, Client> clients_;

    ATC();
    ~ATC();
    ATC(const ATC&) = delete;
    ATC& operator=(const ATC&) = delete;

    static TariffKey makeTariffKey(const std::string& cityLower, CallType t);

public:
    static ATC& instance();

    bool addTariff(const Tariff& t);
    bool addClient(const Client& c);
    bool registerCall(const Call& call);

    double costForCall(const Call& call) const;
    double costForClient(const std::string& surname) const;
    double totalCostAllCalls() const;

    void listTariffs() const;
    void listClients() const;
    void listAllCalls() const;
};

#endif
