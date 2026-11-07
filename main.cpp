#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct ClimateRecord {
    string city;
    double temperature;
    double rainfall;
};

// Display climate records
void displayRecords(const vector<ClimateRecord>& records) {
    cout << "\n";
    cout << left << setw(20) << "City"
         << setw(18) << "Temperature"
         << setw(15) << "Rainfall" << endl;

    cout << string(53, '-') << endl;

    for (const auto& r : records) {
        cout << left << setw(20) << r.city
             << setw(18) << r.temperature
             << setw(15) << r.rainfall << endl;
    }
}

// Quick Sort
int partition(vector<ClimateRecord>& a, int low, int high,
              int choice) {
    double pivot = (choice == 1)
        ? a[high].temperature : a[high].rainfall;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        double value = (choice == 1)
            ? a[j].temperature : a[j].rainfall;

        if (value <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<ClimateRecord>& a, int low, int high,
               int choice) {
    if (low < high) {
        int pi = partition(a, low, high, choice);

        quickSort(a, low, pi - 1, choice);
        quickSort(a, pi + 1, high, choice);
    }
}

// Merge Sort
void merge(vector<ClimateRecord>& a, int left, int mid,
           int right, int choice) {
    vector<ClimateRecord> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        double x = (choice == 1)
            ? a[i].temperature : a[i].rainfall;

        double y = (choice == 1)
            ? a[j].temperature : a[j].rainfall;

        if (x <= y) {
            temp.push_back(a[i++]);
        } else {
            temp.push_back(a[j++]);
        }
    }

    while (i <= mid)
        temp.push_back(a[i++]);

    while (j <= right)
        temp.push_back(a[j++]);

    for (int k = 0; k < (int)temp.size(); k++)
        a[left + k] = temp[k];
}

void mergeSort(vector<ClimateRecord>& a, int left, int right,
               int choice) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid, choice);
        mergeSort(a, mid + 1, right, choice);

        merge(a, left, mid, right, choice);
    }
}

// Find extreme temperatures
void findExtremes(const vector<ClimateRecord>& records) {
    if (records.empty()) {
        cout << "\nNo climate records available.\n";
        return;
    }

    auto highest = max_element(
        records.begin(), records.end(),
        [](const ClimateRecord& a, const ClimateRecord& b) {
            return a.temperature < b.temperature;
        });

    auto lowest = min_element(
        records.begin(), records.end(),
        [](const ClimateRecord& a, const ClimateRecord& b) {
            return a.temperature < b.temperature;
        });

    cout << "\n--- Temperature Analysis ---\n";

    cout << "Highest Temperature: "
         << highest->city << " ("
         << highest->temperature << " C)\n";

    cout << "Lowest Temperature: "
         << lowest->city << " ("
         << lowest->temperature << " C)\n";
}

// Compare sorting algorithms
void compareAlgorithms(const vector<ClimateRecord>& records,
                       int choice) {
    if (records.empty()) {
        cout << "\nNo records available.\n";
        return;
    }

    vector<ClimateRecord> q = records;
    vector<ClimateRecord> m = records;

    auto start1 = high_resolution_clock::now();
    quickSort(q, 0, (int)q.size() - 1, choice);
    auto end1 = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    mergeSort(m, 0, (int)m.size() - 1, choice);
    auto end2 = high_resolution_clock::now();

    double quickTime =
        duration<double, milli>(end1 - start1).count();

    double mergeTime =
        duration<double, milli>(end2 - start2).count();

    cout << fixed << setprecision(6);

    cout << "\n--- Algorithm Performance ---\n";
    cout << "Quick Sort Time: " << quickTime << " ms\n";
    cout << "Merge Sort Time: " << mergeTime << " ms\n";

    cout << "\nQuick Sort Complexity:\n";
    cout << "Average: O(n log n)\n";
    cout << "Worst: O(n^2)\n";

    cout << "\nMerge Sort Complexity:\n";
    cout << "Average: O(n log n)\n";
    cout << "Worst: O(n log n)\n";
}

// Main Function
int main() {
    vector<ClimateRecord> records = {
        {"Hyderabad", 35.5, 12.5},
        {"Delhi", 39.2, 8.0},
        {"Mumbai", 31.4, 45.6},
        {"Chennai", 34.8, 32.2},
        {"Kolkata", 33.1, 28.5},
        {"Bangalore", 27.5, 18.4},
        {"Vijayawada", 37.2, 15.0},
        {"Visakhapatnam", 30.8, 40.2}
    };

    int mainChoice, sortChoice;

    do {
        cout << "\n========================================\n";
        cout << " CLIMATE TIME-SERIES SORTING & RANKING\n";
        cout << "========================================\n";

        cout << "1. Display Climate Records\n";
        cout << "2. Sort Using Quick Sort\n";
        cout << "3. Sort Using Merge Sort\n";
        cout << "4. Find Highest and Lowest Temperature\n";
        cout << "5. Compare Algorithm Execution Times\n";
        cout << "6. Add Climate Record\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                displayRecords(records);
                break;

            case 2:
            case 3:
            case 5:
                cout << "\nSort By:\n";
                cout << "1. Temperature\n";
                cout << "2. Rainfall\n";
                cout << "Enter choice: ";
                cin >> sortChoice;

                if (sortChoice != 1 && sortChoice != 2) {
                    cout << "Invalid sorting choice!\n";
                    break;
                }

                if (mainChoice == 2) {
                    quickSort(records, 0,
                              (int)records.size() - 1,
                              sortChoice);
                    cout << "\nQuick Sort Completed!\n";
                    displayRecords(records);
                }
                else if (mainChoice == 3) {
                    mergeSort(records, 0,
                              (int)records.size() - 1,
                              sortChoice);
                    cout << "\nMerge Sort Completed!\n";
                    displayRecords(records);
                }
                else {
                    compareAlgorithms(records, sortChoice);
                }
                break;

            case 4:
                findExtremes(records);
                break;

            case 6: {
                ClimateRecord r;

                cout << "Enter city name: ";
                cin >> r.city;

                cout << "Enter temperature: ";
                cin >> r.temperature;

                cout << "Enter rainfall: ";
                cin >> r.rainfall;

                records.push_back(r);

                cout << "\nClimate record added successfully!\n";
                break;
            }

            case 7:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (mainChoice != 7);

    return 0;
}
