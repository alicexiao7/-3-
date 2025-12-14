#pragma once
#include <string>
#include <iostream>
#include <exception>


class Service {
public:
    virtual std::string getServiceType() const = 0;
    virtual ~Service() = default;
};

class TariffUser : virtual public Service {
public:
    std::string getServiceType() const override { return "TariffUser"; }
};

class DiscountUser : virtual public Service {
public:
    std::string getServiceType() const override { return "DiscountUser"; }
};

class VIPUser : public TariffUser, public DiscountUser {
public:
    std::string getServiceType() const override { return "VIPUser"; }
};

// Исключение для тарифов
class TariffException : public std::exception {
    std::string message;
public:
    explicit TariffException(const std::string& msg);
    const char* what() const noexcept override;
};

// Базовый класс тарифа
class Tariff {
protected:
    std::string tariffName;
    double basePrice;
public:
    Tariff(const std::string& name = "", double price = 0.0);
    virtual ~Tariff() = default;

    virtual double calculateCost() const;
    virtual void show() const;

    std::string getName() const;
    double getBasePrice() const;


    virtual bool isDiscountTariff() const { return false; }
    virtual double getDiscountValue() const { return 0.0; }


    virtual Tariff* operator+(const Tariff& other) const;
};


class DiscountTariff : public Tariff {
    double discount; // процент (0..100)
public:
    DiscountTariff(const std::string& name = "", double price = 0.0, double disc = 0.0);

    double calculateCost() const override;
    void show() const override;

    bool isDiscountTariff() const override { return true; }
    double getDiscountValue() const override { return discount; }
};
