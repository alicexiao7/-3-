#pragma once
#include "Tariff.h"

using namespace System::Collections::Generic;

namespace ATCWinForm
{
    public ref class ATC
    {
    private:
        List<Tariff^>^ data;

    public:
        ATC();

        void Add(Tariff^ t);
        void Remove(int index);

        List<Tariff^>^ GetAll();

        void SortByName();
        void SortByPrice();

        void SaveCSV(String^ path);
        void LoadCSV(String^ path);
    };
}
