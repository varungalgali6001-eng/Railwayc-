#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct Train {
    int trainNo;
    int arrivalMins;    // minutes from 00:00
    int departureMins;  // minutes from 00:00
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

    // Example: 10:30 AM
    string hh = to_string(hour12);
    string mm = (minute < 10) ? ("0" + to_string(minute)) : to_string(minute);

    return hh + ":" + mm + " " + ampm;
}

void printLine(char ch = '-', int n = 70) {
    for (int i = 0; i < n; i++) cout << ch;
    cout << "\n";
}

void viewTimetable(const vector<Train>& trains) {
    cout << "\n=== Railway Timetable ===\n";
    printLine();

    cout << left << setw(15) << "Train No"
         << setw(20) << "Arrival"
         << setw(20) << "Departure" << "\n";

    printLine();

    for (const auto& t : trains) {
        cout << left << setw(15) << t.trainNo
             << setw(20) << formatTime12(t.arrivalMins)
             << setw(20) << formatTime12(t.departureMins) << "\n";
    }

    printLine();
}

int findTrainIndexByNumber(const vector<Train>& trains, int trainNo) {
    for (int i = 0; i < (int)trains.size(); i++) {
        if (trains[i].trainNo == trainNo) return i;
    }
    return -1;
}

void searchTrain(const vector<Train>& trains) {
    cout << "\nEnter Train Number to search: ";
    int trainNo;
    cin >> trainNo;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a numeric train number.\n";
        return;
    }

    int idx = findTrainIndexByNumber(trains, trainNo);

    if (idx == -1) {
        cout << "Train not found for Train Number: " << trainNo << "\n";
        return;
    }

    // Example output style from screenshot: "Train Arrives at 10:30 AM"
    cout << "\n=== Train Schedule Found ===\n";
    cout << "Train Number: " << trains[idx].trainNo << "\n";
    cout << "Train Arrives at " << formatTime12(trains[idx].arrivalMins) << "\n";
    cout << "Train Departs at " << formatTime12(trains[idx].departureMins) << "\n";
}

int main() {
    // Sample timetable data (you can edit/extend this list)
    vector<Train> trains = {
        {101, toMinutes(10, 30), toMinutes(10, 45)},
        {202, toMinutes(12, 15), toMinutes(12, 35)},
        {303, toMinutes(15,  0), toMinutes(15, 20)},
        {404, toMinutes(18, 50), toMinutes(19, 10)},
        {505, toMinutes( 9,  5), toMinutes( 9, 25)}
    };

    int choice;

    while (true) {
        cout << "\n===== Sample Menu =====\n";
        cout << "1. View Timetable\n";
        cout << "2. Search Train\n";
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
                viewTimetable(trains);
                break;

            case 2:
                // Program flow requirement: timetable -> accept search input -> show schedule
                // (You can comment the next line if you don't want timetable before search)
                viewTimetable(trains);
                searchTrain(trains);
                break;

            case 3:
                cout << "Exiting... Thank you!\n";
                return 0;

            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}