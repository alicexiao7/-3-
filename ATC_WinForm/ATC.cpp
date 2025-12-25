#include "ATC.h"
#include <fstream>

using namespace System::IO;

namespace ATCWinForm
{
    ATC::ATC()
    {
        data = gcnew List<Tariff^>();
    }

    void ATC::Add(Tariff^ t)
    {
        data->Add(t);
    }

    void ATC::Remove(int index)
    {
        if (index >= 0 && index < data->Count)
            data->RemoveAt(index);
    }

    List<Tariff^>^ ATC::GetAll()
    {
        return data;
    }

    void ATC::SortByName()
    {
        for (int i = 0; i < data->Count; i++)
            for (int j = i + 1; j < data->Count; j++)
                if (String::Compare(data[i]->Name, data[j]->Name) > 0)
                {
                    auto t = data[i];
                    data[i] = data[j];
                    data[j] = t;
                }
    }

    void ATC::SortByPrice()
    {
        for (int i = 0; i < data->Count; i++)
            for (int j = i + 1; j < data->Count; j++)
                if (data[i]->Price > data[j]->Price)
                {
                    auto t = data[i];
                    data[i] = data[j];
                    data[j] = t;
                }
    }

    void ATC::SaveCSV(String^ path)
    {
        StreamWriter^ sw = gcnew StreamWriter(path);
        for each (Tariff ^ t in data)
            sw->WriteLine(t->Name + "," + t->Price + "," + t->Discount);
        sw->Close();
    }

    void ATC::LoadCSV(String^ path)
    {
        data->Clear();
        auto lines = File::ReadAllLines(path);
        for each (String ^ line in lines)
        {
            auto p = line->Split(',');
            Add(gcnew Tariff(p[0],
                Convert::ToDouble(p[1]),
                Convert::ToDouble(p[2])));
        }
    }
}
