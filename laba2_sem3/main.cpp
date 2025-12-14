#include "ATC.h"
#include <iostream>
#include <sstream>
#include <climits>

// ---------- helpers ----------
int readInt(const std::string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    while (true) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);

        std::stringstream ss(s);
        int v;
        if (ss >> v && ss.eof() && v >= minVal && v <= maxVal)
            return v;

        std::cout << "Ошибка ввода.\n";
    }
}

double readDouble(const std::string& prompt, double minVal = 0.0) {
    while (true) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);

        std::stringstream ss(s);
        double v;
        if (ss >> v && ss.eof() && v >= minVal)
            return v;

        std::cout << "Ошибка ввода.\n";
    }
}

std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s.empty() ? "-" : s;
}

// ---------- demo ----------
void seedDemoData() {
    ATC& atc = ATC::instance();
    atc.addTariff(Tariff("Moscow", 1.0, CallType::LOCAL));
    atc.addTariff(Tariff("SPb", 2.5, CallType::INTERCITY));

    atc.addClient(Client("Ivanov", "Ivan"));
    atc.addClient(Client("Petrov", "Petr"));

    atc.registerCall(Call("Ivanov", "SPb", 5, CallType::INTERCITY));
    atc.registerCall(Call("Petrov", "Moscow", 3, CallType::LOCAL));
}

int main() {
    seedDemoData();
    ATC& atc = ATC::instance();

    bool running = true;
    while (running) {
        std::cout << "\nМЕНЮ\n"
            << "1) Показать тарифы\n"
            << "2) Добавить тариф\n"
            << "3) Показать клиентов\n"
            << "4) Добавить клиента\n"
            << "5) Зарегистрировать звонок\n"
            << "6) Стоимость звонков клиента\n"
            << "7) Общая стоимость звонков\n"
            << "8) Все звонки\n"
            << "9) Выход\n";

        int choice = readInt("Выбор: ", 1, 9);

        switch (choice) {
        case 1:
            atc.listTariffs();
            break;

        case 2: {
            std::string city = readString("Город: ");
            double price = readDouble("Цена за минуту: ");
            int t = readInt("Тип (0-LOCAL, 1-INTERCITY): ", 0, 1);
            atc.addTariff(Tariff(city, price, static_cast<CallType>(t)));
            break;
        }

        case 3:
            atc.listClients();
            break;

        case 4: {
            std::string s = readString("Фамилия: ");
            std::string n = readString("Имя: ");
            if (!atc.addClient(Client(s, n)))
                std::cout << "Клиент уже существует.\n";
            break;
        }

        case 5: {
            std::string s = readString("Фамилия клиента: ");
            std::string city = readString("Город: ");
            int min = readInt("Минуты: ", 1);
            int t = readInt("Тип (0-LOCAL, 1-INTERCITY): ", 0, 1);
            if (!atc.registerCall(Call(s, city, min, static_cast<CallType>(t))))
                std::cout << "Клиент не найден.\n";
            break;
        }

        case 6: {
            std::string s = readString("Фамилия: ");
            double cost = atc.costForClient(s);
            if (cost < 0)
                std::cout << "Клиент не найден.\n";
            else
                std::cout << "Стоимость: " << cost << " руб.\n";
            break;
        }

        case 7:
            std::cout << "Общая стоимость: "
                << atc.totalCostAllCalls() << " руб.\n";
            break;

        case 8:
            atc.listAllCalls();
            break;

        case 9:
            running = false;
            break;
        }
    }

    std::cout << "Завершение программы.\n";
    return 0;
}
