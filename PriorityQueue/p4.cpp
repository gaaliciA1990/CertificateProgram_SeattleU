//
// Created by Kevin Lundeen on 10/21/20.
// Updated by Alicia Garcia on 11/2/20
// version 1.0
//

#include <fstream>

#include "PatientPriorityQueue.h"
#include "Patient.h"

using namespace std;

const std::string WHITESPACE = " \n\r\t\f\v";

/**
 * Prints help menu.
 */
void help() {
    cout << "add <priority-code> <patient-name>" << endl
         << "            Adds the patient to the triage system." << endl
         << "            <priority-code> must be one of the 4 accepted priority codes:"
         << endl
         << "                1. immediate 2. emergency 3. urgent 4. minimal"
         << endl
         << "            <patient-name>: patient's full legal name (may contain spaces)"
         << endl
         << "next        Announces the patient to be seen next. Takes into account the"
         << endl
         << "            type of emergency and the patient's arrival order."
         << endl
         << "peek        Displays the patient that is next in line, but keeps in queue"
         << endl
         << "list        Displays the list of all patients that are still waiting"
         << endl
         << "            in the order that they have arrived."
         << endl
         << "load <file> Reads the file and executes the command on each line"
         << endl
         << "help        Displays this menu" << endl
         << "quit        Exits the program" << endl;
}

/**
 * Prints welcome message.
 */
void welcome() {
    cout << "Welcome to the Patient Triage Program. Here, you will be able "
            "to\nmanage your patient queue based off of priority. To see the "
            "menu,\ntype in 'help'." << endl;
}

/**
 * Prints farewell message.
 */
void goodbye() {
    cout << "Thank you for using the Patient Triage Program. Have a nice "
            "day!" << endl;
}

/**
 * Delimits (by space) the string from user or file input.
 * @param s string from user or file input (return value is also erased from it)
 * @return the substring of s up to the first space (or to end of string if no
 *         spaces)
 */
string delimitBySpace(string &s) {
    const char delimiter = ' ';
    string result;
    int pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    } else {
        result = s;
    }
    return result;
}

/**
 * This method will remove leading spaces
 * @param s string to trim
 * @return  the trimmed string
 */
std::string ltrim(const string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

/**
 * This method will remove trailing spaces
 * @param s string to trim
 * @return  the trimmed string
 */
std::string rtrim(const string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

/**
 * This method will call ltrim and rtrim to removed leading and trailing spaces
 * @param s string to trim
 * @return  the trimmed string
 */
std::string trim(const string &s) {
    return rtrim(ltrim(s));
}

/**
 * Adds the patient to the waiting room.
 * @param line     command line
 * @param priQueue queue to manipulate
 */
void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;

    // get priority and name
    priority = delimitBySpace(line);

    if (priority.length() == 0) {
        cout << "Error: no priority code given." << endl;
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given." << endl;
        return;
    }

    priority = trim(priority);
    name = trim(name);

    Priority code; // create an enum variable to hold the new priority code
    // Check if the code is valid and assign the enum value
    if (priority == "immediate") {
        code = IMMEDIATE;
    }
    else if(priority == "emergency") {
        code = EMERGENCY;
    }
    else if (priority == "urgent") {
        code = URGENT;
    }
    else if (priority == "minimal") {
        code = MINIMAL;
    }
    else {
        cout << "Error: invalid priority code." << endl;
        return;
    }
    // Create the patient object
    Patient newPatient(code, name);

    // add patient to the priority queue
    priQueue.enqueue(&newPatient);
    cout << "Added patient \"" << name << "\" to the priority system." << endl;
}

/**
 * Displays the next patient in the waiting room that will be called.
 * @param priQueue queue to manipulate
 */
void peekNextCmd(PatientPriorityQueue &priQueue) {
    cout << "Highest priority patient to be called next: " << priQueue.peek()
    .getPatientName() << endl;
}

/**
 * Removes a patient from the waiting room and displays the name on the screen.
 * @param priQueue queue to manipulate
 */
void removePatientCmd(PatientPriorityQueue &priQueue) {
    if (priQueue.empty()) {
        cout << "Nobody is in the queue." << endl;
    }
    else {
        cout << "This patient will now be seen: " << priQueue.dequeue()
        .getPatientName() <<  endl;
    }
}

/**
 * Displays the list of patients in the waiting room.
 * @param priQueue queue to manipulate
 */
void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    // TODO: shows patient detail in arbitrary heap order (root first)
    PatientPriorityQueue *copy = new PatientPriorityQueue(priQueue);
    while(!copy->empty()) {
        cout << copy->dequeue().toString() << endl;
    }
}

// forward declare:
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue);

/**
 * Process the line entered from the user or read from a file.
 * @param line     command text
 * @param priQueue queue to manipulate
 * @return         false to quit; true otherwise
 */
bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

/**
 * Reads a text file with each command on a separate line and executes the
 * lines as if they were typed into the command prompt.
 * @param filename  of file with text commands
 * @param priQueue  queue to manipulate
 */
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    infile.open(filename);
    if (infile) {
        string line;
        while (getline(infile, line)) {
            cout << endl << "triage> " << line;
            cout << endl;
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file." << endl;
    }
    infile.close();
}

/**
 * Main entry into triage program.
 * @return EXIT_SUCCESS
 */
int main() {
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    string line;
    do {
        cout << endl << "triage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    goodbye();
    return EXIT_SUCCESS;
}
