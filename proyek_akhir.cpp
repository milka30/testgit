#include <iostream>
#include <string>

using namespace std;

// Node queue
struct Node {
    string name;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;
const int MAX_QUEUE = 1; // Maksimal user yg boleh nunggu
int queueSize = 0;

string owner = "Najwa";
string currentPlayer = "";

// Cek apakah user sudah ada di queue
bool isInQueue(string name) {
    Node* temp = front;
    while (temp != nullptr) {
        if (temp->name == name) return true;
        temp = temp->next;
    }
    return false;

}

// Enqueue (dengan cek full queue dan duplicate)

void enqueue(string name) {
    if (queueSize >= MAX_QUEUE) {
        cout << "Queue is full! " << name << " cannot be added.\n";
        return;
    }
    if (isInQueue(name)) {
        cout << name << " is already in the queue.\n";
        return;
    }

    Node* newNode = new Node{name, nullptr};
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    queueSize++;
    cout << name << " added to the queue.\n";
}


// Dequeue
string dequeue() {
    if (front == nullptr) return "";

    Node* temp = front;
    string name = temp->name;
    front = front->next;
    if (front == nullptr) rear = nullptr;

    delete temp;
    queueSize--;
    return name;
}

// Remove specific name dari queue
void removeFromQueue(string name) {
    Node* prev = nullptr;
    Node* curr = front;

    while (curr != nullptr) {
        if (curr->name == name) {
            if (prev == nullptr) {
                // front
                front = curr->next;
                if (rear == curr) rear = nullptr;
            } else {
                prev->next = curr->next;
                if (rear == curr) rear = prev;
            }
            delete curr;
            queueSize--;
            cout << name << " removed from the queue.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << name << " is not in the queue.\n";
}

// Minta akses main
void requestAccess(string user) {
    if (currentPlayer == "") {
        currentPlayer = user;
        cout << user << " is now playing the game!\n";
    } else if (user == owner) {
        if (currentPlayer != owner) {
            cout << owner << " (owner) wants to play. Kicking " << currentPlayer << "...\n";
            cout << currentPlayer << " has been kicked.\n";
            currentPlayer = owner;
        } else {
            cout << owner << " is already playing.\n";
        }
    } else {
        enqueue(user);
    }
}

// Selesai main
void finishPlaying() {
    if (currentPlayer != "") {
        cout << currentPlayer << " has finished playing.\n";
        currentPlayer = "";
    }

    // Prioritaskan owner kalau ada di queue
    if (isInQueue(owner)) {
        removeFromQueue(owner);
        currentPlayer = owner;
        cout << owner << " (owner) is now playing from the queue!\n";
    } else if (front != nullptr) {
        currentPlayer = dequeue();
        cout << currentPlayer << " is now playing from the queue!\n";
    }
}

// Tampilkan status
void showStatus() {
    cout << "\n--- STATUS ---\n";
    cout << "Current player: " << (currentPlayer.empty() ? "None" : currentPlayer) << endl;
    cout << "Queue (" << queueSize << "/" << MAX_QUEUE << "): ";
    Node* temp = front;
    if (!temp) cout << "Empty";
    while (temp != nullptr) {
        cout << temp->name;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << "\n--------------\n";
}

// MAIN
int main() {
    requestAccess("Restu");
    requestAccess("Milka");
    requestAccess("Nicholas");

    requestAccess("Najwa"); // owner force masuk

    showStatus();

    finishPlaying(); // Wawa main
    finishPlaying(); // next in queue
    removeFromQueue("Milka"); // force remove

    showStatus();
}