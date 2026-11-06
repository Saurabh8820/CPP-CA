// Public Speaking Practice Evaluator - CAP455 CA1 (Units I-II)
// Manual practice records, simple feedback, in-memory Create and Read.
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

const int MAX_SESSIONS = 50;

class PracticeSession {
private:
    int id;
    string speaker;
    string topic;
    int durationSec;
    int words;
    int fillers;
public:
    static int count;
    void setData(int id, string speaker, string topic,
                 int durationSec, int words, int fillers) {
        this->id = id;
        this->speaker = speaker;
        this->topic = topic;
        this->durationSec = durationSec;
        this->words = words;
        this->fillers = fillers;
    }
    inline int getId() const { return id; }
    friend void display(const PracticeSession &s);
};

int PracticeSession::count = 0;

void display(const PracticeSession &s) {
    double wpm = s.words * 60.0 / s.durationSec;
    double fillerPercent = s.fillers * 100.0 / s.words;
    string pace = wpm < 110 ? "Slow" : (wpm > 160 ? "Fast" : "Balanced");
    string feedback = fillerPercent <= 5 ? "Controlled" : "Reduce fillers";
    cout << "Session " << s.id << " | " << s.speaker << " | " << s.topic << '\n';
    cout << "Duration: " << s.durationSec << "s | Words: " << s.words
         << " | Fillers: " << s.fillers << '\n';
    cout << fixed << setprecision(1) << "Rate: " << wpm
         << " wpm | Filler rate: " << fillerPercent << "%\n";
    cout << "Pace: " << pace << " | Fillers: " << feedback << '\n';
}

// Whole-line integer parsing rejects non-numeric suffixes and decimals.
bool readInt(const string &prompt, int low, int high, int &value) {
    string line;
    while (cout << prompt, getline(cin, line)) {
        istringstream input(line);
        int candidate;
        char extra;
        if (input >> candidate && !(input >> extra)
            && candidate >= low && candidate <= high) {
            value = candidate;
            return true;
        }
        cout << "Invalid: enter an integer from " << low << " to " << high << ".\n";
    }
    return false;
}

bool readText(const string &prompt, string &value) {
    while (cout << prompt, getline(cin, value)) {
        if (value.find_first_not_of(" \t\r\n") != string::npos) return true;
        cout << "Text cannot be blank.\n";
    }
    return false;
}

PracticeSession* findById(PracticeSession list[], int id) {
    for (int i = 0; i < PracticeSession::count; ++i) {
        if (list[i].getId() == id) return &list[i];
    }
    return nullptr;
}

void addSession(PracticeSession list[]) {
    if (PracticeSession::count >= MAX_SESSIONS) {
        cout << "Practice log is full.\n";
        return;
    }
    int id, seconds, words, fillers;
    string speaker, topic;
    if (!readInt("Session ID (1-9999): ", 1, 9999, id)) return;
    if (findById(list, id)) {
        cout << "Error: session ID " << id << " already exists.\n";
        return;
    }
    if (!readText("Speaker name: ", speaker)) return;
    if (!readText("Speech topic: ", topic)) return;
    if (!readInt("Duration in seconds (30-1800): ", 30, 1800, seconds)) return;
    if (!readInt("Word count (1-5000): ", 1, 5000, words)) return;
    if (!readInt("Filler count (0-word count): ", 0, words, fillers)) return;
    list[PracticeSession::count].setData(id, speaker, topic, seconds, words, fillers);
    ++PracticeSession::count;
    cout << "Session added.\n";
}

void viewAll(PracticeSession list[]) {
    if (PracticeSession::count == 0) {
        cout << "No practice sessions yet.\n";
        return;
    }
    PracticeSession *p = list;
    for (int i = 0; i < PracticeSession::count; ++i, ++p) {
        display(*p);
    }
}

void searchSession(PracticeSession list[]) {
    int id;
    if (!readInt("Session ID to search: ", 1, 9999, id)) return;
    PracticeSession *p = findById(list, id);
    if (p) display(*p);
    else cout << "Session not found.\n";
}

int main() {
    PracticeSession list[MAX_SESSIONS];
    int choice;
    while (true) {
        cout << "\n=== Public Speaking Practice Evaluator ===\n"
             << "1. Add Session\n2. View All\n3. Search by ID\n0. Exit\n";
        if (!readInt("Choice: ", 0, 3, choice) || choice == 0) break;
        switch (choice) {
            case 1: addSession(list); break;
            case 2: viewAll(list); break;
            case 3: searchSession(list); break;
        }
    }
    cout << "Goodbye!\n";
    return 0;
}
