#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ========== ENUMERATIONS ========== //
enum Department {
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType {
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== EMERGENCY CASE CLASS ========== //
// Advanced Feature: priority_queue
class EmergencyCase {
private:
    int patientId;
    int severity;

public:
    EmergencyCase(int pid, int s);

    int getPatientId() const;
    int getSeverity() const;

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const;
};


// ========== PATIENT CLASS ========== //
class Patient {
private:
    int id;
    string name;
    int age;
    string contact;

    // Data Structures
    stack<string> medicalHistory;
    queue<string> testQueue;
    vector<string> prescriptions;

    bool isAdmitted;
    RoomType roomType;

    // Advanced Feature: Billing
    double bill;

public:
    // Constructor
    Patient(int pid, string n, int a, string c);

    // ========== ORIGINAL FEATURES ========== //

    void admitPatient(RoomType type);
    void dischargePatient();

    void addMedicalRecord(string record);

    void requestTest(string testName);
    string performTest();

    void displayHistory();

    int getId();
    string getName();

    bool getAdmissionStatus();


    // ========== NEW FEATURES ========== //

    // Medical Tests
    void displayPendingTests();

    // Prescriptions
    void addPrescription(string medicine);
    void displayPrescriptions();

    // Billing
    void addBill(double amount);
    double getBill();
    void displayBill();

    // Additional Getters
    int getAge();
    string getContact();
    RoomType getRoomType();
};


// ========== DOCTOR CLASS ========== //
class Doctor {
private:
    int id;
    string name;
    Department department;

    // Queue of patients waiting for doctor
    queue<int> appointmentQueue;

public:
    // Constructor
    Doctor(int did, string n, Department d);

    // ========== ORIGINAL FEATURES ========== //

    void addAppointment(int patientId);
    int seePatient();

    int getId();
    string getName();
    string getDepartment();


    // ========== NEW FEATURES ========== //

    // Display waiting patients
    void displayAppointments();

    // Cancel appointment
    void cancelAppointment(int patientId);

    // Number of waiting patients
    int getAppointmentCount();
};


// ========== HOSPITAL CLASS ========== //
class Hospital {
private:

    // Main collections
    vector<Patient> patients;
    vector<Doctor> doctors;

    // Original emergency queue
    queue<int> emergencyQueue;

    // Advanced emergency queue
    priority_queue<EmergencyCase> priorityEmergencyQueue;

    // Counters
    int patientCounter;
    int doctorCounter;

    // ========== ROOM MANAGEMENT ========== //

    int generalRooms;
    int icuRooms;
    int privateRooms;
    int semiPrivateRooms;


public:

    // Constructor
    Hospital();


    // =====================================================
    // ORIGINAL FEATURES
    // ===================================================== //

    int registerPatient(
        string name,
        int age,
        string contact
    );

    int addDoctor(
        string name,
        Department dept
    );

    void admitPatient(
        int patientId,
        RoomType type
    );

    void addEmergency(
        int patientId
    );

    int handleEmergency();

    void bookAppointment(
        int doctorId,
        int patientId
    );

    void displayPatientInfo(
        int patientId
    );

    void displayDoctorInfo(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 1
    // Find Patient
    // ===================================================== //

    Patient* findPatient(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 2
    // Find Doctor
    // ===================================================== //

    Doctor* findDoctor(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 3
    // Search Patient By Name
    // ===================================================== //

    void searchPatientByName(
        string name
    );


    // =====================================================
    // NEW FEATURE 4
    // Discharge Patient
    // ===================================================== //

    void dischargePatient(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 5
    // Request Medical Test
    // ===================================================== //

    void requestPatientTest(
        int patientId,
        string testName
    );


    // =====================================================
    // NEW FEATURE 6
    // Perform Medical Test
    // ===================================================== //

    void performPatientTest(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 7
    // Display Pending Tests
    // ===================================================== //

    void displayPatientTests(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 8
    // Add Prescription
    // ===================================================== //

    void prescribeMedicine(
        int patientId,
        string medicine
    );


    // =====================================================
    // NEW FEATURE 9
    // Display Prescriptions
    // ===================================================== //

    void displayPrescriptions(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 10
    // Patient Bill
    // ===================================================== //

    void displayPatientBill(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 11
    // Priority Emergency
    // ===================================================== //

    void addPriorityEmergency(
        int patientId,
        int severity
    );


    // =====================================================
    // NEW FEATURE 12
    // Handle Priority Emergency
    // ===================================================== //

    int handlePriorityEmergency();


    // =====================================================
    // NEW FEATURE 13
    // Room Availability
    // ===================================================== //

    bool isRoomAvailable(
        RoomType type
    );


    // =====================================================
    // NEW FEATURE 14
    // Display Room Status
    // ===================================================== //

    void displayRoomStatus();


    // =====================================================
    // NEW FEATURE 15
    // Display All Patients
    // ===================================================== //

    void displayAllPatients();


    // =====================================================
    // NEW FEATURE 16
    // Display All Doctors
    // ===================================================== //

    void displayAllDoctors();


    // =====================================================
    // NEW FEATURE 17
    // Display Doctor Appointments
    // ===================================================== //

    void displayDoctorAppointments(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 18
    // Cancel Appointment
    // ===================================================== //

    void cancelAppointment(
        int doctorId,
        int patientId
    );


    // =====================================================
    // NEW FEATURE 19
    // Doctor Sees Next Patient
    // ===================================================== //

    void doctorSeePatient(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 20
    // Hospital Statistics
    // ===================================================== //

    void displayStatistics();
};


// ========== MAIN PROGRAM ========== //
int main() {

    Hospital hospital;


    // =====================================================
    // TEST CASE 1
    // Registering patients
    // ===================================================== //

    int p1 =
        hospital.registerPatient(
            "John Doe",
            35,
            "555-1234"
        );

    int p2 =
        hospital.registerPatient(
            "Jane Smith",
            28,
            "555-5678"
        );

    int p3 =
        hospital.registerPatient(
            "Mike Johnson",
            45,
            "555-9012"
        );


    // =====================================================
    // TEST CASE 2
    // Adding doctors
    // ===================================================== //

    int d1 =
        hospital.addDoctor(
            "Dr. Smith",
            CARDIOLOGY
        );

    int d2 =
        hospital.addDoctor(
            "Dr. Brown",
            NEUROLOGY
        );

    int d3 =
        hospital.addDoctor(
            "Dr. Lee",
            PEDIATRICS
        );


    // =====================================================
    // TEST CASE 3
    // Admitting patients
    // ===================================================== //

    hospital.admitPatient(
        p1,
        PRIVATE_ROOM
    );

    hospital.admitPatient(
        p2,
        ICU
    );

    // Try admitting already admitted patient
    hospital.admitPatient(
        p1,
        SEMI_PRIVATE
    );


    // =====================================================
    // TEST CASE 4
    // Booking appointments
    // ===================================================== //

    hospital.bookAppointment(
        d1,
        p1
    );

    hospital.bookAppointment(
        d1,
        p2
    );

    hospital.bookAppointment(
        d2,
        p3
    );

    // Invalid doctor
    hospital.bookAppointment(
        999,
        p1
    );

    // Invalid patient
    hospital.bookAppointment(
        d1,
        999
    );


    // =====================================================
    // TEST CASE 5
    // Handling medical tests
    // ===================================================== //

    hospital.requestPatientTest(
        p1,
        "Blood Test"
    );

    hospital.requestPatientTest(
        p1,
        "X-Ray"
    );

    hospital.requestPatientTest(
        p1,
        "MRI"
    );

    hospital.displayPatientTests(
        p1
    );

    hospital.performPatientTest(
        p1
    );

    hospital.displayPatientTests(
        p1
    );


    // =====================================================
    // TEST CASE 6
    // Emergency cases
    // ===================================================== //

    hospital.addEmergency(p3);

    hospital.addEmergency(p1);

    int emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    // No more emergencies


    // =====================================================
    // TEST CASE 7
    // Discharging patients
    // ===================================================== //

    hospital.dischargePatient(
        p1
    );


    // =====================================================
    // TEST CASE 8
    // Displaying information
    // ===================================================== //

    hospital.displayPatientInfo(
        p1
    );

    hospital.displayPatientInfo(
        p2
    );

    hospital.displayPatientInfo(
        999
    );


    hospital.displayDoctorInfo(
        d1
    );

    hospital.displayDoctorInfo(
        d2
    );

    hospital.displayDoctorInfo(
        999
    );


    // =====================================================
    // TEST CASE 9
    // Doctor seeing patients
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.doctorSeePatient(
        d1
    );

    hospital.displayDoctorAppointments(
        d1
    );


    // =====================================================
    // TEST CASE 10
    // Search Patient
    // ===================================================== //

    hospital.searchPatientByName(
        "John Doe"
    );

    hospital.searchPatientByName(
        "Unknown Patient"
    );


    // =====================================================
    // TEST CASE 11
    // Prescriptions
    // ===================================================== //

    hospital.prescribeMedicine(
        p1,
        "Paracetamol"
    );

    hospital.prescribeMedicine(
        p1,
        "Antibiotic"
    );

    hospital.displayPrescriptions(
        p1
    );


    // =====================================================
    // TEST CASE 12
    // Patient Billing
    // ===================================================== //

    hospital.displayPatientBill(
        p1
    );

    hospital.displayPatientBill(
        p2
    );


    // =====================================================
    // TEST CASE 13
    // Priority Emergency
    // ===================================================== //

    hospital.addPriorityEmergency(
        p1,
        2
    );

    hospital.addPriorityEmergency(
        p2,
        5
    );

    hospital.addPriorityEmergency(
        p3,
        3
    );

    hospital.addPriorityEmergency(
        p1,
        4
    );


    // =====================================================
    // TEST CASE 14
    // Handle Priority Emergencies
    // ===================================================== //

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();


    // =====================================================
    // TEST CASE 15
    // Room Management
    // ===================================================== //

    hospital.displayRoomStatus();


    // =====================================================
    // TEST CASE 16
    // Display All Patients
    // ===================================================== //

    hospital.displayAllPatients();


    // =====================================================
    // TEST CASE 17
    // Display All Doctors
    // ===================================================== //

    hospital.displayAllDoctors();


    // =====================================================
    // TEST CASE 18
    // Cancel Appointment
    // ===================================================== //

    hospital.cancelAppointment(
        d1,
        p2
    );


    // =====================================================
    // TEST CASE 19
    // More Doctor Appointments
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.displayDoctorAppointments(
        d2
    );


    // =====================================================
    // TEST CASE 20
    // Hospital Statistics
    // ===================================================== //

    hospital.displayStatistics();


    // =====================================================
    // TEST CASE 21
    // Edge Cases
    // ===================================================== //

    Hospital emptyHospital;

    emptyHospital.displayPatientInfo(
        1
    );

    emptyHospital.displayDoctorInfo(
        1
    );

    emptyHospital.handleEmergency();

    emptyHospital.handlePriorityEmergency();

    emptyHospital.searchPatientByName(
        "John Doe"
    );

    emptyHospital.displayAllPatients();

    emptyHospital.displayAllDoctors();

    emptyHospital.displayStatistics();


    return 0;
}