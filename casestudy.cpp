#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct Train {
    int trainNo;
    int arrivalMins;
    int departureMins;
};

int toMinutes(int hour24, int minute) {
    return hour24 * 60 + minute;
}

string formatTime12(int totalMins) {
    int hour24 = totalMins / 60;
    int minute = totalMins % 60;

    string ampm = (hour24 >= 12) ? "PM" : "AM";
    int hour12 = hour24 % 12;
    if (hour12 == 0) hour12 = 12;

    string hh = to_string(hour12);
    string mm = (minute < 10) ? ("0" + to_string(minute)) : to_string(minute);

    return hh + ":" + mm + " " + ampm;
}

void printLine(char ch = '-', int n = 70) {
    for (int i = 0; i < n; i++) {
        cout << ch;
    }
    cout << "\n";
}

void viewTimetable(Train trains[], int size) {
    if (size == 0) {
        cout << "\nNo train records available.\n";
        return;
    }

    cout << "\n=== Railway Timetable ===\n";
    printLine();

    cout << left << setw(15) << "Train No"
         << setw(20) << "Arrival"
         << setw(20) << "Departure" << "\n";

    printLine();

    for (int i = 0; i < size; i++) {
        cout << left << setw(15) << trains[i].trainNo
             << setw(20) << formatTime12(trains[i].arrivalMins)
             << setw(20) << formatTime12(trains[i].departureMins) << "\n";
    }

    printLine();
}

int findTrainIndexByNumber(Train trains[], int size, int trainNo) {
    for (int i = 0; i < size; i++) {
        if (trains[i].trainNo == trainNo) {
            return i;
        }
    }
    return -1;
}

void searchTrain(Train trains[], int size) {
    cout << "\nEnter Train Number to search: ";
    int trainNo;
    cin >> trainNo;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a numeric train number.\n";
        return;
    }

    int idx = findTrainIndexByNumber(trains, size, trainNo);

    if (idx == -1) {
        cout << "Train not found for Train Number: " << trainNo << "\n";
        return;
    }

    cout << "\n=== Train Schedule Found ===\n";
    cout << "Train Number: " << trains[idx].trainNo << "\n";
    cout << "Train Arrives at " << formatTime12(trains[idx].arrivalMins) << "\n";
    cout << "Train Departs at " << formatTime12(trains[idx].departureMins) << "\n";
}

void addTrain(Train trains[], int &size, int maxSize) {
    if (size >= maxSize) {
        cout << "\nCannot add more trains. Storage is full.\n";
        return;
    }

    int trainNo, arrH, arrM, depH, depM;

    cout << "\nEnter new Train Number: ";
    cin >> trainNo;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid train number.\n";
        return;
    }

    if (findTrainIndexByNumber(trains, size, trainNo) != -1) {
        cout << "Train number already exists.\n";
        return;
    }

    cout << "Enter Arrival Time (HH MM): ";
    cin >> arrH >> arrM;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid arrival time.\n";
        return;
    }

    cout << "Enter Departure Time (HH MM): ";
    cin >> depH >> depM;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid departure time.\n";
        return;
    }

    trains[size].trainNo = trainNo;
    trains[size].arrivalMins = toMinutes(arrH, arrM);
    trains[size].departureMins = toMinutes(depH, depM);
    size++;

    cout << "New train added successfully.\n";
}

void adminMenu(Train trains[], int &size, int maxSize) {
    int choice;

    while (true) {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. View Timetable\n";
        cout << "2. Add New Train\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        switch (choice) {
            case 1:
                viewTimetable(trains, size);
                break;
            case 2:
                addTrain(trains, size, maxSize);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}

void userMenu(Train trains[], int size) {
    int choice;

    while (true) {
        cout << "\n===== USER MENU =====\n";
        cout << "1. View Timetable\n";
        cout << "2. Search Train\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        switch (choice) {
            case 1:
                viewTimetable(trains, size);
                break;
            case 2:
                viewTimetable(trains, size);
                searchTrain(trains, size);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}

int main() {
    const int MAX_TRAINS = 20;

    Train trains[MAX_TRAINS] = {
        {101, toMinutes(10, 30), toMinutes(10, 45)},
        {202, toMinutes(12, 15), toMinutes(12, 35)},
        {303, toMinutes(15,  0), toMinutes(15, 20)},
        {404, toMinutes(18, 50), toMinutes(19, 10)},
        {505, toMinutes( 9,  5), toMinutes( 9, 25)},
        {606, toMinutes( 7, 45), toMinutes( 8,  0)},
        {707, toMinutes(13, 10), toMinutes(13, 30)},
        {808, toMinutes(16, 40), toMinutes(17,  0)}
    };

    int size = 8;
    int choice;

    while (true) {
        cout << "\n===== RAILWAY TIMETABLE MANAGEMENT SYSTEM =====\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        switch (choice) {
            case 1:
                adminMenu(trains, size, MAX_TRAINS);
                break;
            case 2:
                userMenu(trains, size);
                break;
            case 3:
                cout << "Exiting... Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}