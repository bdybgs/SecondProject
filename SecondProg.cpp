#include <iostream>
#include <string>

using namespace std;

// Базовый класс для всех типов скважин
class Well {
protected:
    double volume;
public:
    Well(double vol) : volume(vol) {}
    virtual ~Well() {}
    virtual void displayInfo() const = 0; 
    double getVolume() const { return volume; }
    void setVolume(double vol) { volume = vol; }
};

// Класс для нефтяной скважины
class OilWell : public Well {
public:
    OilWell(double vol) : Well(vol) {}
    void displayInfo() const override {
        cout << "Нефтяная скважина, объем: " << volume << " баррелей" << endl;
    }
};

// Класс для газовой скважины
class GasWell : public Well {
public:
    GasWell(double vol) : Well(vol) {}
    void displayInfo() const override {
        cout << "Газовая скважина, объем: " << volume << " кубических метров" << endl;
    }
};

// Класс для нагнетательной скважины
class InjectionWell : public Well {
public:
    InjectionWell(double vol) : Well(vol) {}
    void displayInfo() const override {
        cout << "Нагнетательная скважина, объем: " << volume << " кубических метров" << endl;
    }
};

// Класс для нефтяного месторождения
class OilField {
private:
    double oilVolume;
    double gasVolume;
    double waterVolume;
    Well* wells[10]; 
    int numWells; 
public:
    OilField(double oilVol, double gasVol, double waterVol) : oilVolume(oilVol), gasVolume(gasVol), waterVolume(waterVol), numWells(0) {}
    ~OilField() {
        for (int i = 0; i < numWells; ++i) {
            delete wells[i];
        }
    }
    void addWell(Well* well) {
        if (numWells < 10) {
            wells[numWells++] = well;
        } else {
            cout << "Невозможно добавить больше скважин" << endl;
        }
    }
    void removeWell(int index) {
        if (index >= 0 && index < numWells) {
            delete wells[index];
            for (int i = index; i < numWells - 1; ++i) {
                wells[i] = wells[i + 1];
            }
            numWells--;
        } else {
            cout << "Неверный индекс скважины" << endl;
        }
    }
    void displayInfo() const {
        cout << "Объем нефти в месторождении: " << oilVolume << " баррелей" << endl;
        cout << "Объем газа в месторождении: " << gasVolume << " кубических метров" << endl;
        cout << "Объем воды в месторождении: " << waterVolume << " кубических метров" << endl;
        cout << "Скважины в месторождении:" << endl;
        for (int i = 0; i < numWells; ++i) {
            wells[i]->displayInfo();
        }
    }
};

int main() {
    OilField oilField(1000, 500, 200);
    
    OilWell* oilWell = new OilWell(50);
    GasWell* gasWell = new GasWell(200);
    InjectionWell* injectionWell = new InjectionWell(100);
    
    oilField.addWell(oilWell);
    oilField.addWell(gasWell);
    oilField.addWell(injectionWell);
    
    cout << "Информация о месторождении:" << endl;
    oilField.displayInfo();
    
    delete oilWell;
    delete gasWell;
    delete injectionWell;
    
    return 0;
}
