#include <iostream>
#include <windows.h>
#include <string>
#include <limits>
#include <iomanip>
#include "ATC.h"

double getValidatedInput(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max)
            return value;
        std::cout << "Ошибка! Введите число от " << min << " до " << max << "\n";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::cin.ignore();
    std::getline(std::cin, s);
    return s;
}

void displayMenu() {
    std::cout << "\n=== МЕНЮ АТС ===\n";
    std::cout << "1. Добавить обычный тариф\n";
    std::cout << "2. Добавить льготный тариф\n";
    std::cout << "3. Показать все тарифы\n";
    std::cout << "4. Рассчитать среднюю стоимость\n";
    std::cout << "5. Выйти\n";
    std::cout << "Выберите действие: ";
}

int main() {
    SetConsoleOutputCP(1251);    // ← Windows-1251 — русский будет идеально
    SetConsoleCP(1251);          // ← для ввода тоже
    ATC atc;
    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ТАРИФАМИ АТС ===\n";
    std::cout << "Загружены начальные тарифы (4 шт.)\n";

    while (true) {
        displayMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
        }

        try {
            switch (choice) {
            case 1: {
                std::string name = getStringInput("Введите название тарифа: ");
                double price = getValidatedInput("Введите стоимость тарифа (0-1,000,000): ", 0, 1000000);
                atc.addRegularTariff(name, price);
                break;
            }
            case 2: {
                std::string name = getStringInput("Введите название тарифа: ");
                double price = getValidatedInput("Введите стоимость тарифа (0-1,000,000): ", 0, 1000000);
                double disc = getValidatedInput("Введите размер скидки (0-100%): ", 0, 100);
                atc.addDiscountTariff(name, price, disc);
                break;
            }
            case 3:
                atc.displayAllTariffs();
                break;
            case 4: {
                double avg = atc.calculateAverageCost();
                std::cout << "\nСредняя стоимость всех тарифов: "
                    << std::fixed << std::setprecision(2) << avg << " руб.\n";
                break;
            }
            case 5:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Выберите пункт от 1 до 5!\n";
            }
        }
        catch (const TariffException& e) {
            std::cout << "Ошибка тарифа: " << e.what() << "\n";
        }
        catch (...) {
            std::cout << "Неожиданная ошибка!\n";
        }
    }
    return 0;
}