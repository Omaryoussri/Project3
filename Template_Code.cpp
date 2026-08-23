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
    EmergencyCase(int pid, int s){
        patientId = pid;
        severity = s;
    }

    int getPatientId() const{
        return patientId;
    }
    int getSeverity() const{
        return severity;
    }

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const{
        return this -> getSeverity() < other.getSeverity();
    }
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

    void addMedicalRecord(string record)
	{
		medicalHistory.push(record);
	}

    void requestTest(string testName)
	{
		// Add a test to the back of the queue
		testQueue.push(testName);

		// Add an event to the medical history
		addMedicalRecord("Test requested: " + testName);
	}
	
    string performTest()
	{
		// Check if there are no pending tests
		if (testQueue.empty())
		{
			return "No tests pending";
		}

		// Get the first requested test
		string testName = testQueue.front();

		// Remove from the queue
		testQueue.pop();

		// Record the performed test
		addMedicalRecord("Test performed: " + testName);

		// Each performed test costs $300
		addBill(300);

		// Return the name of the performed test
		return testName;
	}

    void displayHistory()
	{
		cout << "Medical History for " << name << " (ID: " << id << "):" << endl;

		// Make copy without popping the original stack
		stack<string> temp = medicalHistory;

		// LIFO Stack
		while (!temp.empty())
		{
			cout << "- " << temp.top() << endl;
			temp.pop();
		}
	}

    int getId();
    string getName();

    bool getAdmissionStatus();


    // ========== NEW FEATURES ========== //

    // Medical Tests
    void displayPendingTests()
	{
		cout << "Pending Tests:" << endl;

		// Make a copy to not remove them from the original queue
		queue<string> temp = testQueue;

		// FIFO Queue
		while (!temp.empty())
		{
			cout << "- " << temp.front() << endl;
			temp.pop();
		}
	}

    // Prescriptions
    void addPrescription(string medicine)
	{
		// Add the medicine to prescriptions vector
		prescriptions.push_back(medicine);

		// Record prescription in the medical history
		addMedicalRecord("Prescription added: " + medicine);

		// Each prescription costs $100
		addBill(100);
	}
	
    void displayPrescriptions()
	{
		if (prescriptions.empty())
		{
			cout << "No prescriptions found." << endl;
			return;
		}

		cout << "Prescriptions:" << endl;

		// Display medicines ordered by when they are added
		for (const string& medicine : prescriptions)
		{
			cout << "- " << medicine << endl;
		}
	}

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
    Doctor(int did, string n, Department d){
        id = did;
        name = n;
        department = d;
    }

    // ========== ORIGINAL FEATURES ========== //

    void addAppointment(int patientId){
        appointmentQueue.push(patientId);
    }
    int seePatient(){
        if(appointmentQueue.empty()){
            return -1; // No patients waiting
        }
        int patientId = appointmentQueue.front();
        appointmentQueue.pop();
        return patientId;
    }

    int getId(){
        return id;
    }
    string getName(){
        return name;
    }
    string getDepartment(){
        return department+"";
    }


    // ========== NEW FEATURES ========== //

    // Display waiting patients
    void displayAppointments(){
        queue<int> tempQueue = appointmentQueue; // Copy to not modify original queue
        if(tempQueue.empty()){
            cout << "No patients waiting for doctor " << name << endl;
            return;
        }
        else{
            cout << "Patients waiting for doctor " << name << ":" << endl;
            while(!tempQueue.empty()){
                cout << "- Patient ID: " << tempQueue.front() << endl;
                tempQueue.pop();
            }
        }
    }

    // Cancel appointment
    void cancelAppointment(int patientId){
        if(appointmentQueue.empty()){
            cout << "No appointments avaliable "<< endl;
            return;
        }
        else{
            queue<int> tempQueue;
            bool found = false;

            // Transfer all patients except the one to cancel
            while(!appointmentQueue.empty()){
                int currentPatientId = appointmentQueue.front();
                appointmentQueue.pop();
                if(currentPatientId == patientId && !found){
                    found = true;
                    continue; // Skip adding this patients first occurence to the temp queue
                }
                tempQueue.push(currentPatientId);
            }

            // Restore the original queue
            appointmentQueue = tempQueue;

            if(found){
                cout << "Appointment cancelled successfully." << endl;
            }
            else{
                cout << "Appointment not found." << patientId << endl;
            }
        }
    }

    // Number of waiting patients
    int getAppointmentCount(){
        return appointmentQueue.size();
    }
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
    Hospital(){
        patientCounter = 1;
        doctorCounter = 1;

        generalRooms = 20;
        icuRooms = 5;
        privateRooms = 10;
        semiPrivateRooms = 10;

        patients = {};      
        doctors = {};  
    };


    // =====================================================
    // ORIGINAL FEATURES
    // ===================================================== //

    int registerPatient(
        string name,
        int age,
        string contact
    ){
        int patientId = patientCounter++;
        Patient newPatient(patientId, name, age, contact);
        patients.push_back(newPatient);
        cout << "Patient registered with ID: " << patientId << endl;
        return patientId;
    };

    int addDoctor(
        string name,
        Department dept
    ){
        int doctorId = doctorCounter++;
        Doctor newDoctor(doctorId, name, dept);
        doctors.push_back(newDoctor);
        cout << "Doctor added with ID: " << doctorId << endl;
        return doctorId;
    };

    void admitPatient(
        int patientId,
        RoomType type
    ){
        Patient* patientPtr = findPatient(patientId);
        if(patientPtr){
            // // handle in Patient class instead
            // if(p.getAdmissionStatus()){
            //     cout << "Patient with ID " << patientId << " is already admitted." << endl;
            //     return;
            // }

            if(isRoomAvailable(type)){
                patientPtr->admitPatient(type);
                // // decrement room count based on type?
                // switch(type){
                //     case GENERAL_WARD:
                //         generalRooms--;
                //         break;
                //     case ICU:
                //         icuRooms--;
                //         break;
                //     case PRIVATE_ROOM:
                //         privateRooms--;
                //         break;
                //     case SEMI_PRIVATE:
                //         semiPrivateRooms--;
                //         break;
                // }
                return;
            }
            else{
                cout << "No room available for this room type." << endl;
                return;
            } 
        }
        else {
            cout << "Patient with ID " << patientId << " not found." << endl;
            return;
        }
    };

    void addEmergency(int patientId){
        emergencyQueue.push(patientId);
    }

    int handleEmergency(){
        if(emergencyQueue.empty()){
            cout << "No emergencies in queue" << endl;
            return -1;
        }
        //Stores and returns popped element in case needed after operation
        int handledEmergency = emergencyQueue.front();
        emergencyQueue.pop();
        return handledEmergency;
    };

    void bookAppointment(
        int doctorId,
        int patientId
    ){
        Doctor* doctorPtr = findDoctor(doctorId);
        Patient* patientPtr = findPatient(patientId);

        bool doctorFound = (doctorPtr != nullptr);
        bool patientFound = (patientPtr != nullptr);

        if(!doctorFound){
            cout << "Doctor with ID " << doctorId << " not found." << endl;
        }
        if(!patientFound){
            cout << "Patient with ID " << patientId << " not found." << endl;
        }
        if(doctorFound && patientFound){
            doctorPtr->addAppointment(patientId);
            cout << "Appointment booked for patient " << patientId << " with doctor " << doctorId << endl;
        }
    };

    void displayPatientInfo(int patientId){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            cout << "Patient Information:\n";
            cout << "ID: " << p->getId() << "\nName: " << p->getName() << "\n";
            cout << "Admission Status: " << (p->getAdmissionStatus() ? "Admitted" : "Not Admitted") << "\n";
        }
        else{
            cout << "Patient with ID " << patientId << " not found." << endl;
        }
    }

    void displayDoctorInfo(int doctorId){
        Doctor* d = findDoctor(doctorId);
        if(d != nullptr){
            cout << "Doctor Information:\n";
            cout << "ID: " << d->getId() << "\nName: " << d->getName() << "\n";
            cout << "Department: " << d->getDepartment() << "\n";
        }
        else {
            cout << "Doctor with ID " << doctorId << " not found." << endl;
        }
    }


    // =====================================================
    // NEW FEATURE 1
    // Find Patient
    // ===================================================== //

    Patient* findPatient(
        int patientId
    ){
        for(auto& p : patients){
            if(p.getId() == patientId){
                return &p;
            }
        }
        return nullptr;
    };


    // =====================================================
    // NEW FEATURE 2
    // Find Doctor
    // ===================================================== //

    Doctor* findDoctor(
        int doctorId
    ){
        for(auto& d : doctors){
            if(d.getId() == doctorId){
                return &d;
            }
        }
        return nullptr;
    };


    // =====================================================
    // NEW FEATURE 3
    // Search Patient By Name
    // ===================================================== //

    void searchPatientByName(string name){
        bool found = false;
        for(auto& p : patients){
            if(p.getName() == name){
                cout << "Patient Found:\n";
                cout << "ID: " << p.getId() << "\nName: " << p.getName() 
                    << "\nAge: " << p.getAge() << "\nContact: " << p.getContact() << "\n";
                found = true;
            }
        }
        if (!found) cout << "Patient not found." << endl;
    }


    // =====================================================
    // NEW FEATURE 4
    // Discharge Patient
    // ===================================================== //

    void dischargePatient(
        int patientId
    ){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            if(p->getAdmissionStatus()){
                p->dischargePatient();
                cout << "Patient with ID " << patientId << " has been discharged." << endl;
            }
            else{
                cout << "Patient with ID " << patientId << " is not admitted." << endl;
            }
        }
        else{
            cout << "Patient with ID " << patientId << " not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 5
    // Request Medical Test
    // ===================================================== //

    void requestPatientTest(
        int patientId,
        string testName
    ){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            p->requestTest(testName);
            cout << "Test '" << testName << "' requested for patient ID " << patientId << endl;
        }
        else{
            cout << "Patient with ID " << patientId << " not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 6
    // Perform Medical Test
    // ===================================================== //

    void performPatientTest(
        int patientId
    ){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            string testResult = p->performTest();
            if(!testResult.empty()){
                cout << "Performed test for patient ID " << patientId << ": " << testResult << endl;
            }
            else{
                cout << "No pending tests for patient ID " << patientId << endl;
            }
        }
        else{
            cout << "Patient with ID " << patientId << " not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 7
    // Display Pending Tests
    // ===================================================== //

    void displayPatientTests(int patientId){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            p->displayPendingTests();
        }
        else{
            cout << "Patient not found." << endl;
        }
    }


    // =====================================================
    // NEW FEATURE 8
    // Add Prescription
    // ===================================================== //

    void prescribeMedicine(
        int patientId,
        string medicine
    ){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            p->addPrescription(medicine);
            cout << "Prescribed '" << medicine << "' to patient ID " << patientId << endl;
        }
        else{
            cout << "Patient not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 9
    // Display Prescriptions
    // ===================================================== //

    void displayPrescriptions(int patientId){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            p->displayPrescriptions();
        }
        else{
            cout << "Patient not found." << endl;
        }
    }


    // =====================================================
    // NEW FEATURE 10
    // Patient Bill
    // ===================================================== //

    void displayPatientBill(int patientId){
        Patient* p = findPatient(patientId);
        if(p != nullptr){
            p->displayBill();
        }
        else{
            cout << "Patient not found." << endl;
        }
    }


    // =====================================================
    // NEW FEATURE 11
    // Priority Emergency
    // ===================================================== //

    void addPriorityEmergency(int patientId, int severity){
        //Make sure the patient exists in records and that the severity level is bounded between 1 and 5 as planned
        if(findPatient(patientId) && severity <= 5 && severity >= 1){
            priorityEmergencyQueue.push(EmergencyCase(patientId, severity));
        }
        else{
            cout << "Error adding patient to priorityEmergencyQueue!" << endl;
            return;
        }
    }


    // =====================================================
    // NEW FEATURE 12
    // Handle Priority Emergency
    // ===================================================== //

    int handlePriorityEmergency(){
        if(priorityEmergencyQueue.empty()){
            cout << "No priority emergencies." << endl;
            return -1;
        }
        //Create a copy of object so we can pop and still return info from it
        EmergencyCase temp = priorityEmergencyQueue.top();
        priorityEmergencyQueue.pop();
        cout << "Handling patient " << temp.getPatientId() << " with severity : " << temp.getSeverity() << endl;
        return temp.getPatientId();
    }


    // =====================================================
    // NEW FEATURE 13
    // Room Availability
    // ===================================================== //

    bool isRoomAvailable(
        RoomType type
    ){
        switch(type){
            case GENERAL_WARD:
                return generalRooms > 0;
            case ICU:
                return icuRooms > 0;
            case PRIVATE_ROOM:
                return privateRooms > 0;
            case SEMI_PRIVATE:
                return semiPrivateRooms > 0;
            default:
                return false;
        }
    };


    // =====================================================
    // NEW FEATURE 14
    // Display Room Status
    // ===================================================== //

    void displayRoomStatus(){
        cout << "========== ROOM STATUS ==========\n";
        cout << "General Ward: " << generalRooms << "\n";
        cout << "ICU: " << icuRooms << "\n";
        cout << "Private Rooms: " << privateRooms << "\n";
        cout << "Semi Private Rooms: " << semiPrivateRooms << "\n";
    }


    // =====================================================
    // NEW FEATURE 15
    // Display All Patients
    // ===================================================== //

    void displayAllPatients(){
        cout << "========== ALL PATIENTS ==========\n";
    for (auto& p : patients) {
        cout << "ID: " << p.getId() << " | Name: " << p.getName() << " | Age: " << p.getAge() << " | Status: " << (p.getAdmissionStatus() ? "Admitted" : "Not Admitted") << "\n";
    }
    }


    // =====================================================
    // NEW FEATURE 16
    // Display All Doctors
    // ===================================================== //

    void displayAllDoctors(){
        cout << "========== ALL DOCTORS ==========\n";
    for (auto& d : doctors) {
        cout << "ID: " << d.getId() << " | Name: " << d.getName() << " | Department: " << d.getDepartment() << " | Appointments: " << d.getAppointmentCount() << "\n";
    }
    }


    // =====================================================
    // NEW FEATURE 17
    // Display Doctor Appointments
    // ===================================================== //

    void displayDoctorAppointments(int doctorId){
        Doctor* d = findDoctor(doctorId);
        if(d != nullptr){
            cout << "Appointments for " << d->getName() << ":\n";
            d->displayAppointments();
        }
        else{
            cout << "Doctor not found." << endl;
        }
    }


    // =====================================================
    // NEW FEATURE 18
    // Cancel Appointment
    // ===================================================== //

    void cancelAppointment(
        int doctorId,
        int patientId
    ){
        Doctor* doctorPtr = findDoctor(doctorId);
        if(doctorPtr != nullptr){
            doctorPtr->cancelAppointment(patientId);
        }
        else{
            cout << "Doctor with ID " << doctorId << " not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 19
    // Doctor Sees Next Patient
    // ===================================================== //

    void doctorSeePatient(
        int doctorId
    ){
        Doctor* doctorPtr = findDoctor(doctorId);
        if(doctorPtr != nullptr){
            int patientId = doctorPtr->seePatient();
            if(patientId != -1){
                cout << "Doctor " << doctorPtr->getName() << " is seeing patient with ID: " << patientId << endl;
            }
            else{
                cout << "No patients in queue for doctor " << doctorPtr->getName() << endl;
            }
        }
        else{
            cout << "Doctor with ID " << doctorId << " not found." << endl;
        }
    };


    // =====================================================
    // NEW FEATURE 20
    // Hospital Statistics
    // ===================================================== //

    void displayStatistics(){
        int admittedCount = 0;
        double totalBilled = 0;

        for (auto& p : patients) {
            if (p.getAdmissionStatus()) {
                admittedCount++;
            }
            totalBilled += p.getBill();
        }

        cout << "========== HOSPITAL STATISTICS ==========\n";
        cout << "Total Patients: " << patients.size() << "\n";
        cout << "Total Doctors: " << doctors.size() << "\n";
        cout << "Admitted Patients: " << admittedCount << "\n";
        cout << "Waiting Emergencies: " << emergencyQueue.size() << "\n";
        cout << "Priority Emergencies: " << priorityEmergencyQueue.size() << "\n";
        cout << "Total Generated Bills: $" << totalBilled << "\n";
        cout << "=========================================\n";
    }
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