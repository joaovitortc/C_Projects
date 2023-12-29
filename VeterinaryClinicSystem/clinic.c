#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(struct Patient* patient,
                         struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data); 
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }

    } while (selection);

}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(struct Patient patient[], int max, int fmt) {
    int i = 0;

    if (patient[0].patientNumber != 0) {

        displayPatientTableHeader();

        for (i = 0; i < max; i++) {
            if (patient[i].patientNumber != 0) {
                displayPatientData(&patient[i], fmt);
            }
        }
        printf("\n");
    }
    else
        printf("***No records found ***");
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(struct Patient patient[], int max) {
    char option;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        option = getchar();
        clearInputBuffer();
        printf("\n");

        if (option == '1') {
            searchPatientByPatientNumber(patient, max);
        }
        else if (option == '2') {
            searchPatientByPhoneNumber(patient, max);

        }
        else if (option == '0') {
            return;
        }
        else
            printf("invalid character?");

    } while (option != '0');
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i;
    int free = 0; // flag to check is there is a free spot
    int freeIndex = -1;

    for (i = 0; i <= (max - 1); i++) {                       // **had to change this (max - 1) to work on matrix **
        // don't know why :)
        if (patient[i].patientNumber == 0) {
            free = 1;
            freeIndex = i;
            break;
        }

    }

    if (free == 0) {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else {

        patient[freeIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[freeIndex]);
        printf("*** New patient record added ***\n\n");

    }

    return;
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
    int num;
    int indexToEdit;
    printf("Enter the patient number: ");
    scanf("%d", &num);
    clearInputBuffer();
    printf("\n");

    //the function returns -1 for not found and the index of the patient found [if found]
    indexToEdit = findPatientIndexByPatientNum(num, patient, max);

    //if its found (different than -1), call the edit function
    if (indexToEdit != -1) {
        menuPatientEdit(&patient[indexToEdit]);

    }
    else
        printf("\nERROR: Patient record not found!\n\n");


}


// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
    int num;
    int indexToDel;
    char selection;

    printf("Enter the patient number: ");
    scanf("%d", &num);
    clearInputBuffer();
    printf("\n");

    //the function returns -1 for not found and the index of the patient found [if found]
    indexToDel = findPatientIndexByPatientNum(num, patient, max);

    //if its found (different than -1), call the edit function
    if (indexToDel != -1) {
        displayPatientData(&patient[indexToDel], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");

        if (selection == 'y') {
            strcpy(patient[indexToDel].name, "");
            patient[indexToDel].patientNumber = 0;
            strcpy(patient[indexToDel].phone.description, "");
            strcpy(patient[indexToDel].phone.number, "");
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }

    }
    else
        printf("ERROR: Patient record not found!\n\n");
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) {
    int i;
    int index = 0;

    data->appointments = sortAppoint(data->appointments, MAX_APPOINTMENTS);

    displayScheduleTableHeader(&data->appointments->date, 1);


    for (i = 0; i < MAX_APPOINTMENTS; i++) {
        if (data->appointments[i].patientNum != 0) {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNum, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], 1);
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {

struct Date date;
int i, index = 0, wasFound = 0;

getDate(&date);

printf("\n");

data->appointments = sortAppoint(data->appointments, MAX_APPOINTMENTS);
displayScheduleTableHeader(&date, 0);

for (i = 0; i < MAX_APPOINTMENTS; i++) {

    //Compare if the date input by the user is the same as any date in the appoint array
    if ((date.year == data->appointments[i].date.year) && 
        (date.month == data->appointments[i].date.month) && 
        (date.day == data->appointments[i].date.day)) 
    {    
        // if the date is the same, find the index (position of the array) of the patient that has the appointment and display

        index = findPatientIndexByPatientNum(data->appointments[i].patientNum, data->patients, data->maxPatient);
        displayScheduleData(&data->patients[index], &data->appointments[i], 0);
        wasFound = 1;
    }
}

if (wasFound == 0) {
    printf("Nothing was Found on this date\n");
}

printf("\n");
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appoint, int maxAppointments, struct Patient* patient, int maxPatient)
{
    struct Appointment tempAppoint;
    int done = 0;
    int freeIndex = 0;

    if (checkPatientNum(&tempAppoint, patient, maxPatient) == 0) {

        done = 0;
        do {
            getDate(&tempAppoint.date);
            getTime(&tempAppoint.time);

            freeIndex = checkSpot(&tempAppoint, appoint, maxAppointments);

            if (freeIndex == -1) {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else {
                appoint[freeIndex].date.day = tempAppoint.date.day;
                appoint[freeIndex].date.month = tempAppoint.date.month;
                appoint[freeIndex].date.year = tempAppoint.date.year;
                appoint[freeIndex].time.hour = tempAppoint.time.hour;
                appoint[freeIndex].time.min = tempAppoint.time.min;
                appoint[freeIndex].patientNum = tempAppoint.patientNum;

                done = 1;
                printf("\n*** Appointment scheduled! ***\n\n");
            }

        } while (done != 1);

    }

}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoint, int maxAppointments, struct Patient* patient, int maxPatient) {
    struct Appointment tempAppoint;
    int i, indexToDel = -1, indexPatient = 0;
    int selection;

    if (checkPatientNum(&tempAppoint, patient, maxPatient) == 0) {

        getDate(&tempAppoint.date);

        for (i = 0; i < maxAppointments; i++) {
            if (tempAppoint.patientNum == appoint[i].patientNum &&
                tempAppoint.date.day == appoint[i].date.day &&
                tempAppoint.date.month == appoint[i].date.month &&
                tempAppoint.date.year == appoint[i].date.year)
            {
                indexToDel = i;
            }
        }

        if (indexToDel == -1) {
            printf("Record Not Found\n");
        }
        else {
            indexPatient = findPatientIndexByPatientNum(appoint[indexToDel].patientNum, patient, maxPatient);
            printf("\n");
            displayPatientData(&patient[indexPatient], FMT_FORM);

            printf("Are you sure you want to remove this appointment (y,n): ");
            selection = (inputCharOption("yn") == 'y');

            if (selection) {
                appoint[indexToDel].date.day = 0;
                appoint[indexToDel].date.month = 0;
                appoint[indexToDel].date.year = 0;
                appoint[indexToDel].patientNum = 0;
                appoint[indexToDel].time.hour = 0;
                appoint[indexToDel].time.min = 0;

                printf("\nAppointment record has been removed!\n\n");
            }
        }


        i = 0;

    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Patient Number validation for user input
int checkPatientNum(struct Appointment* tempAppoint, struct Patient* patient, int maxPatient) {

    int notFound = 0;

    printf("Patient Number: ");
    tempAppoint->patientNum = inputIntPositive();
    if (findPatientIndexByPatientNum(tempAppoint->patientNum, patient, maxPatient) != -1) {
        notFound = 0;
    }  
    else {
        printf("ERROR: Patient record not found!\n\n");
        notFound = 1;
    }


    return notFound;
}

// Check if there's available appointment slot
int checkSpot(struct Appointment* temp, struct Appointment* appoint, int maxAppointments) {
    int available = 1;
    int i;
    int freeIndex = -1;

    for (i = 0; i < maxAppointments; i++) {
        if (temp->date.day == appoint[i].date.day &&
            temp->date.month == appoint[i].date.month &&
            temp->date.year == appoint[i].date.year &&
            temp->time.hour == appoint[i].time.hour &&
            temp->time.min == appoint[i].time.min)
        {
            available = 0;
        }
    }

    if (available == 1) {
        for (i = 0; i <= (maxAppointments - 1); i++) {
            if (appoint[i].patientNum == 0) {
                freeIndex = i;
                break;
            }
        }
    }
 
    return freeIndex;
}

// Get time
void getTime(struct Time* time) {
    int done = 0;
  
    do {
        printf("Hour (0-23)  : ");
        time->hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        time->min = inputIntRange(0, 59);

        if ((time->hour < START_TIME || time->hour > END_TIME) || (time->min != 0 && time->min != 30) || (time->hour == END_TIME && time->min != 0))  {
            printf("ERROR: Time must be between %d:00 and %d:00 in 30 minute intervals.\n\n", START_TIME, END_TIME);
        }
        else {
            done = 1;
        }

    } while (done != 1);
}

// Get date
void getDate(struct Date* date) {

    printf("Year        : ");
    date->year = inputInt();
    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);

    switch (date->month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        printf("Day (1-31)  : ");
        date->day = inputIntRange(1, 31);
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        printf("Day (1-30)  : ");
        date->day = inputIntRange(1, 30);
        break;
    case 2:
        if (date->year % 4 == 0) {
            printf("Day (1-29)  : ");
            date->day = inputIntRange(1, 29);
        }
        else {
            printf("Day (1-28)  : ");
            date->day = inputIntRange(1, 28);
        }
        break;

    }

}


// Swap Appointments
void swapAppointments(struct Appointment* a, struct Appointment* b) {
    struct Appointment temp = *a;
    *a = *b;
    *b = temp;
}


// Sorting array

struct Appointment* sortAppoint(struct Appointment* appoint, int max) {
    int i, j;
    for (i = 0; i < max - 1; i++) {
        for (j = 0; j < max - i - 1; j++) {
            // Compare dates first
            if (appoint[j].date.year > appoint[j + 1].date.year ||
                (appoint[j].date.year == appoint[j + 1].date.year &&
                    appoint[j].date.month > appoint[j + 1].date.month) ||
                (appoint[j].date.year == appoint[j + 1].date.year &&
                    appoint[j].date.month == appoint[j + 1].date.month &&
                    appoint[j].date.day > appoint[j + 1].date.day) ||
                // Compare times if dates are the same
                (appoint[j].date.year == appoint[j + 1].date.year &&
                    appoint[j].date.month == appoint[j + 1].date.month &&
                    appoint[j].date.day == appoint[j + 1].date.day &&
                    appoint[j].time.hour > appoint[j + 1].time.hour) ||
                (appoint[j].date.year == appoint[j + 1].date.year &&
                    appoint[j].date.month == appoint[j + 1].date.month &&
                    appoint[j].date.day == appoint[j + 1].date.day &&
                    appoint[j].time.hour == appoint[j + 1].time.hour &&
                    appoint[j].time.min > appoint[j + 1].time.min)) {
                swapAppointments(&appoint[j], &appoint[j + 1]);
            }
        }
    }

    return appoint;
}


// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(struct Patient patient[], int max) {
    int patientNumber;
    int index;

    printf("Search by patient number: ");
    scanf(" %d", &patientNumber);
    clearInputBuffer();

    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    printf("\n");

    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
        printf("*** No records found ***\n");

    printf("\n");
    suspend();
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(struct Patient patient[], int max) {
    char str[PHONE_LEN + 1];
    int i, q = 0; // for iterations
    int diff = 0, found = 0; //flags

    printf("Search by phone number: ");
    // getting the string from the user

    str[0] = '\0';

    inputCString(str, 10, 10);

    printf("\n");

    displayPatientTableHeader();

    //checking for each character of both strings
    for (i = 0; i <= max; i++) {
        for (q = 0; q < PHONE_LEN && str[q] != '\0'; q++) {
            if (str[q] != patient[i].phone.number[q])
                diff = 1;
        }
        //displaying the correct one (if there is)
        if (diff == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }

        diff = 0; //resetting flag for next patient
    }
    // if it didn't find anything, displaying this
    if (found != 1) {
        printf("\n*** No records found ***\n");

    }

    printf("\n");
    suspend();
}


// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int i;
    int largest = 0;

    for (i = 0; i <= (max - 1); i++) {
        if (patient[i].patientNumber >= largest) {
            largest = patient[i].patientNumber;
        }
    }
    return largest + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i;
    int ret = -1; //what's gonna be returned

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            ret = i;
            break;
        }
    }

    return ret;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {

    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, 15);
    printf("\n");
    inputPhoneData(&patient->phone);


}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
    int selection = 0;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    scanf("%d", &selection);
    getchar();
    printf("\n");

    if (selection == 4) {
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "\0");

    }
    else {
        if (selection == 1)
            strcpy(phone->description, "CELL");
        if (selection == 2)
            strcpy(phone->description, "HOME");
        if (selection == 3)
            strcpy(phone->description, "WORK");

        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        printf("\n");
    }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max) {

    FILE *file = NULL;
    int i, nrecs = 0;

    file = fopen(datafile, "r");

    if (file != NULL) {

        for (i = 0; i < max; i++) {
            fscanf(file, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
                patients[i].name,
                patients[i].phone.description,
                patients[i].phone.number);
                
            nrecs++;
        }
    }
    else
        printf("error");

    fclose(file);

    return nrecs;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* file = NULL;
    int i, nrecs = 0;

    file = fopen(datafile, "r");

    if (file != NULL) {

        for (i = 0; i < max; i++) {

            if (fscanf(file, "%d,%d,%d,%d,%d,%d",
                &appoints[i].patientNum,
                &appoints[i].date.year,
                &appoints[i].date.month,
                &appoints[i].date.day,
                &appoints[i].time.hour,
                &appoints[i].time.min) == 6)
                {
                    ++nrecs;
            }
            else
                break;
        }
    }
    else
        printf("error");

    fclose(file);

    return nrecs;
}