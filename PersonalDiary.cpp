#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Клас, представляващ запис в дневника
class DiaryEntry {
private:
    string date; // Дата на записа
    string content; // Съдържание на записа

public:
    // Конструктор
    DiaryEntry(string d, string c) : date(d), content(c) {}

    // Връща датата на записа
    string getDate() const {
        return date;
    }

    // Връща съдържанието на записа
    string getContent() const {
        return content;
    }

    // Печата записа на конзолата
    void printEntry() const {
        cout << "[" << date << "] " << content << endl;
    }
};

// Клас, управляващ дневника
class Diary {
private:
    vector<DiaryEntry> entries; // Списък с записи

public:
    // Добавя нов запис
    void addEntry(string date, string content) {
        entries.emplace_back(date, content);
    }

    // Изтрива запис по индекс
    void deleteEntry(int index) {
        if (index < 0 || index >= entries.size()) {
            throw out_of_range("Невалиден индекс на записа.");
        }
        entries.erase(entries.begin() + index);
    }

    // Печата всички записи
    void printAllEntries() const {
        if (entries.empty()) {
            cout << "Няма записани записи." << endl;
            return;
        }
        for (int i = 0; i < entries.size(); i++) {
            cout << i + 1 << ". ";
            entries[i].printEntry();
        }
    }

    // Записва всички записи в текстов файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            throw runtime_error("Не може да се отвори файлът за запис.");
        }
        for (const auto& entry : entries) {
            file << entry.getDate() << "|" << entry.getContent() << endl;
        }
        file.close();
    }

    // Зарежда записи от текстов файл
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            throw runtime_error("Не може да се отвори файлът за четене.");
        }
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find('|');
            if (delimiterPos != string::npos) {
                string date = line.substr(0, delimiterPos);
                string content = line.substr(delimiterPos + 1);
                addEntry(date, content);
            }
        }
        file.close();
    }
};

int main() {
    system("chcp 1251 > nul");
    Diary diary;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добави запис\n";
        cout << "2. Изтрий запис\n";
        cout << "3. Извеждане на записи\n";
        cout << "4. Записване на записи във файл\n";
        cout << "5. Зареждане на записи от файл\n";
        cout << "6. Изход\n";
        cout << "Избор: ";
        cin >> choice;
        cin.ignore(); // Игнориране на новия ред

        switch (choice) {
        case 1: {
            string date, content;
            cout << "Въведете дата (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Въведете съдържание на записа: ";
            getline(cin, content);
            diary.addEntry(date, content);
            cout << "Записът е добавен успешно!" << endl;
            break;
        }
        case 2: {
            int index;
            cout << "Въведете номер на записа за изтриване: ";
            cin >> index;
            try {
                diary.deleteEntry(index - 1); // -1 за корекция на индекса
                cout << "Записът е изтрит успешно!" << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 3:
            diary.printAllEntries();
            break;
        case 4: {
            string filename;
            cout << "Въведете име на файл за запис: ";
            cin >> filename;
            try {
                diary.saveToFile(filename);
                cout << "Записите са запазени успешно!" << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 5: {
            string filename;
            cout << "Въведете име на файл за зареждане: ";
            cin >> filename;
            try {
                diary.loadFromFile(filename);
                cout << "Записите са заредени успешно!" << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 6:
            cout << "Изход от програмата." << endl;
            break;
        default:
            cout << "Невалиден избор! Опитайте отново." << endl;
        }
    } while (choice != 6);

    return 0;
}
