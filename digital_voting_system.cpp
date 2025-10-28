#include <iostream>
#include <string>
using namespace std;

// ------------------ Linked List Node for Candidates ------------------
struct Candidate {
    int id;
    string name;
    int votes;
    Candidate* next;
};

// ------------------ Queue Node for Voters ------------------
struct Voter {
    int voterID;
    string voterName;
    Voter* next;
};

// ------------------ Queue Class ------------------
class VoterQueue {
    Voter* front;
    Voter* rear;

public:
    VoterQueue() {
        front = rear = nullptr;
    }

    // Add voter to queue
    void enqueue(int id, string name) {
        Voter* temp = new Voter{id, name, nullptr};
        if (rear == nullptr) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    // Remove voter from queue
    Voter* dequeue() {
        if (front == nullptr) return nullptr;
        Voter* temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        return temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// ------------------ Linked List Class for Candidates ------------------
class CandidateList {
    Candidate* head;

public:
    CandidateList() {
        head = nullptr;
    }

    // Add new candidate to linked list
    void addCandidate(int id, string name) {
        Candidate* newNode = new Candidate{id, name, 0, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Candidate* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    // Display all candidates
    void displayCandidates() {
        Candidate* temp = head;
        cout << "\nList of Candidates:\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << endl;
            temp = temp->next;
        }
    }

    // Record a vote for a candidate by ID
    void voteCandidate(int id) {
        Candidate* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                temp->votes++;
                cout << "Vote recorded for " << temp->name << " ✅\n";
                return;
            }
            temp = temp->next;
        }
        cout << "⚠️ Invalid Candidate ID!\n";
    }

    // Display final results with tie handling
    void displayResults() {
        if (head == nullptr) {
            cout << "\nNo candidates found!\n";
            return;
        }

        Candidate* temp = head;
        int maxVotes = 0;

        cout << "\n--- Final Vote Count ---\n";
        while (temp != nullptr) {
            cout << temp->name << " -> " << temp->votes << " votes\n";
            if (temp->votes > maxVotes)
                maxVotes = temp->votes;
            temp = temp->next;
        }

        // Check for tie
        temp = head;
        int countWinners = 0;
        cout << "\n🏆 Highest Votes: " << maxVotes << "\nWinners: ";
        while (temp != nullptr) {
            if (temp->votes == maxVotes) {
                cout << temp->name << "  ";
                countWinners++;
            }
            temp = temp->next;
        }

        if (countWinners > 1)
            cout << "\n🤝 It's a tie between " << countWinners << " candidates!\n";
        else
            cout << "\n🏆 Winner declared with " << maxVotes << " votes! 🏆\n";
    }
};

// ------------------ Main Function ------------------
int main() {
    CandidateList candidates;
    VoterQueue voters;

    int numCandidates, numVoters;
    string candidateNames[100]; // Array for temporary storage

    cout << "==============================\n";
    cout << "      DIGITAL VOTING SYSTEM    \n";
    cout << "==============================\n";

    // -------- Candidate Registration --------
    cout << "\nEnter number of candidates: ";
    cin >> numCandidates;
    cin.ignore();

    for (int i = 0; i < numCandidates; i++) {
        cout << "Enter name of candidate " << (i + 1) << ": ";
        getline(cin, candidateNames[i]);
        candidates.addCandidate(i + 1, candidateNames[i]);
    }

    // -------- Voter Registration --------
    cout << "\nEnter number of voters: ";
    cin >> numVoters;
    cin.ignore();

    for (int i = 0; i < numVoters; i++) {
        int id;
        string name;
        cout << "\nEnter Voter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Voter Name: ";
        getline(cin, name);
        voters.enqueue(id, name);
    }

    // -------- Voting Process --------
    cout << "\n--- Voting Process Started ---\n";
    while (!voters.isEmpty()) {
        Voter* currentVoter = voters.dequeue();
        cout << "\nVoter: " << currentVoter->voterName << " (ID: " << currentVoter->voterID << ")\n";
        candidates.displayCandidates();
        int choice;
        cout << "Enter Candidate ID to vote for: ";
        cin >> choice;
        candidates.voteCandidate(choice);
    }

    // -------- Display Final Results --------
    candidates.displayResults();

    cout << "\nThank you for using the Digital Voting System!\n";

    return 0;
}