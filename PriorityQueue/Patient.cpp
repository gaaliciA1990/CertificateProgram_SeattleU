//
// Created by garci on 11/2/2020.
// Version 1.0
//

using namespace std;

#include "Patient.h"

// Initialize the patient number to zero
int Patient::patientNum = 1;

Patient::Patient(Priority pc, string& n) {
    priorityCode = pc;
    name = n;
    arrivalOrder = patientNum;
    patientNum++;
}

int Patient::compareTo(Patient& otherPatient) {
    if (this->priorityCode == otherPatient.priorityCode) {
        if (this->arrivalOrder < otherPatient.arrivalOrder) {
            return -1;
        }
        else {
            return 1;
        }
    }
    if (this->priorityCode < otherPatient.priorityCode) {
        return -1;
    }
    else {
        return 1;
    }
}

std::string Patient::toString() {
    return name + " { priority = " + enumString(priorityCode) + ", arrive order"
                    " = " + std::to_string(arrivalOrder) + "}";
}

std::string Patient::enumString(Priority code) {
    switch (code) {
        case IMMEDIATE:
            return "Immediate";
        case EMERGENCY:
            return "Emergency";
        case URGENT:
            return "Urgent";
        case MINIMAL:
            return "Minimal";
        default:
            break;
    }
}

std::string Patient::getPatientName() {
    return name;
}
