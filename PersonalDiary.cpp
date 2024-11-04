#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// ����, ������������� ����� � ��������
class DiaryEntry {
private:
    string date; // ���� �� ������
    string content; // ���������� �� ������

public:
    // �����������
    DiaryEntry(string d, string c) : date(d), content(c) {}

    // ����� ������ �� ������
    string getDate() const {
        return date;
    }

    // ����� ������������ �� ������
    string getContent() const {
        return content;
    }

    // ������ ������ �� ���������
    void printEntry() const {
        cout << "[" << date << "] " << content << endl;
    }
};

// ����, ���������� ��������
class Diary {
private:
    vector<DiaryEntry> entries; // ������ � ������

public:
    // ������ ��� �����
    void addEntry(string date, string content) {
        entries.emplace_back(date, content);
    }

    // ������� ����� �� ������
    void deleteEntry(int index) {
        if (index < 0 || index >= entries.size()) {
            throw out_of_range("��������� ������ �� ������.");
        }
        entries.erase(entries.begin() + index);
    }

    // ������ ������ ������
    void printAllEntries() const {
        if (entries.empty()) {
            cout << "���� �������� ������." << endl;
            return;
        }
        for (int i = 0; i < entries.size(); i++) {
            cout << i + 1 << ". ";
            entries[i].printEntry();
        }
    }

    // ������� ������ ������ � ������� ����
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            throw runtime_error("�� ���� �� �� ������ ������ �� �����.");
        }
        for (const auto& entry : entries) {
            file << entry.getDate() << "|" << entry.getContent() << endl;
        }
        file.close();
    }

    // ������� ������ �� ������� ����
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            throw runtime_error("�� ���� �� �� ������ ������ �� ������.");
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
        cout << "\n����:\n";
        cout << "1. ������ �����\n";
        cout << "2. ������ �����\n";
        cout << "3. ��������� �� ������\n";
        cout << "4. ��������� �� ������ ��� ����\n";
        cout << "5. ��������� �� ������ �� ����\n";
        cout << "6. �����\n";
        cout << "�����: ";
        cin >> choice;
        cin.ignore(); // ���������� �� ����� ���

        switch (choice) {
        case 1: {
            string date, content;
            cout << "�������� ���� (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "�������� ���������� �� ������: ";
            getline(cin, content);
            diary.addEntry(date, content);
            cout << "������� � ������� �������!" << endl;
            break;
        }
        case 2: {
            int index;
            cout << "�������� ����� �� ������ �� ���������: ";
            cin >> index;
            try {
                diary.deleteEntry(index - 1); // -1 �� �������� �� �������
                cout << "������� � ������ �������!" << endl;
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
            cout << "�������� ��� �� ���� �� �����: ";
            cin >> filename;
            try {
                diary.saveToFile(filename);
                cout << "�������� �� �������� �������!" << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 5: {
            string filename;
            cout << "�������� ��� �� ���� �� ���������: ";
            cin >> filename;
            try {
                diary.loadFromFile(filename);
                cout << "�������� �� �������� �������!" << endl;
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 6:
            cout << "����� �� ����������." << endl;
            break;
        default:
            cout << "��������� �����! �������� ������." << endl;
        }
    } while (choice != 6);

    return 0;
}
