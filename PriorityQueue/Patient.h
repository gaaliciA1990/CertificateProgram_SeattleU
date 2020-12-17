//
// Created by garci on 11/2/2020.
// Version 1.0
//

#ifndef P4_HIGHESTPRIORITY_PATIENT_H
#define P4_HIGHESTPRIORITY_PATIENT_H


#include <string>

enum Priority {
    IMMEDIATE = 1, EMERGENCY = 2, URGENT = 3, MINIMAL = 4
};

class Patient {
public:
    /**
     * Constructor for filling the priority code and name
     * @param pc    priority code
     * @param n     patient name
     */
    Patient(Priority pc, std::string &n);

    /**
     * This will compare the patients to determine who should be seen first
     * @return  negative number if the patient should be seen first, else
     *          positive number
     */
    int compareTo(Patient& otherPatient);

    /**
     * Get the name of the patients with the highest priority.
     * @return  patient name
     */
    std::string getPatientName();

    /**
     * This will return a string representation of my data
     * @return the string created
     */
    std::string toString();

private:
    std::string name;
    Priority priorityCode;
    int arrivalOrder;
    static int patientNum; // keeps track of patient numbers

    /**
     * Convert the priority codes to their string counterparts
     * @param code priority code to be converted
     * @return  the string code version
     */
    std::string enumString(Priority code);
};


#endif //P4_HIGHESTPRIORITY_PATIENT_H
