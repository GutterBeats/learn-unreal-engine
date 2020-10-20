#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

void OutputWithDelay(string Text, int DelayMilliseconds, bool NewLine) {
    int Position = 0;

    char CharacterAtPosition;
    while (CharacterAtPosition = Text[Position]) {
        if (CharacterAtPosition == '\0') break;

        ++Position;

        cout << CharacterAtPosition;
        
        if (((Position + rand()) % 3) == 0) {
            Beep(1000, 20);
        }

        this_thread::sleep_for(chrono::milliseconds(DelayMilliseconds));
    }

    this_thread::sleep_for(chrono::seconds(1));

    if (NewLine) {
        cout << endl;
    }
}

void OutputWithDelay(string Text, bool NewLine) {
    OutputWithDelay(Text, 60, NewLine);
}

void OutputWithDelay(string Text, int DelayMilliseconds) {
    OutputWithDelay(Text, DelayMilliseconds, true);
}

void OutputWithDelay(string Text) {
    OutputWithDelay(Text, 60);
}

int main() {

    OutputWithDelay("Hello.");
    this_thread::sleep_for(chrono::seconds(1));

    OutputWithDelay("We have been watching you. ", false);
    OutputWithDelay("You've been brought to our attention due to the...skills you seem to possess.");
    OutputWithDelay("You will now demonstrate those skills with a series of three challenges.");
    OutputWithDelay("Should you pass these challenges, there may be certain", false);
    OutputWithDelay("...", 100, false);
    OutputWithDelay("rewards for you.");
    OutputWithDelay("Should you not pass, well...for your sake you better.");
    OutputWithDelay("Don't try to run...", false);
    OutputWithDelay("there is no escape.");
    OutputWithDelay("Let's begin, ", false);
    OutputWithDelay("shall we?");

    OutputWithDelay("The rules are as follows:", 10);
    OutputWithDelay("\t+ You are trying to guess 3 random numbers");
    OutputWithDelay("\t+ There are three challenges, but you are allowed only three mistakes.");
    OutputWithDelay("\t+ You will not be given additional tries should you get any correct. Once you've lost, you're lost.");
    OutputWithDelay("Here we go.");

    int MistakeCount = 0;
    int ChallengeCount = 0;

    int GuessA, GuessB, GuessC;

    while (ChallengeCount < 3) {
        OutputWithDelay("\t+ The 3 numbers add up to a sum of: ");
        OutputWithDelay("\t+ And the product of the 3 numbers is: ");
        cout << endl;

        cin >> GuessA;
        cin >> GuessB;
        cin >> GuessC;

        cout << GuessA << GuessB << GuessC;

        ++ChallengeCount;
    }

    return 0;
}

