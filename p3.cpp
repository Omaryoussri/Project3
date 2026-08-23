```cpp
Patient::Patient(int pid, string n, int a, string c)
{
    id = pid;
    name = n;
    age = a;
    contact = c;
    isAdmitted = false;
    bill = 0;
}

void Patient::admitPatient(RoomType type)
{
    if (isAdmitted)
    {
        cout << "Patient is already admitted." << endl;
        return;
    }

    isAdmitted = true;
    roomType = type;

    medicalHistory.push("Patient admitted to hospital");

    switch (type)
    {
        case GENERAL_WARD:
            bill += 500;
            break;

        case ICU:
            bill += 3000;
            break;

        case PRIVATE_ROOM:
            bill += 1500;
            break;

        case SEMI_PRIVATE:
            bill += 1000;
            break;
    }
}

void Patient::dischargePatient()
{
    if (!isAdmitted)
    {
        cout << "Patient is not currently admitted." << endl;
        return;
    }

    isAdmitted = false;
    medicalHistory.push("Patient discharged from hospital");
}

void Patient::addBill(double amount)
{
    bill += amount;
}

double Patient::getBill()
{
    return bill;
}

void Patient::displayBill()
{
    cout << "========== PATIENT BILL ==========" << endl;
    cout << "Patient ID: " << id << endl;
    cout << "Patient Name: " << name << endl;
    cout << "Total Bill: $" << bill << endl;
    cout << "=========" << endl;
}

int Patient::getId()
{
    return id;
}

string Patient::getName()
{
    return name;
}

int Patient::getAge()
{
    return age;
}

string Patient::getContact()
{
    return contact;
}

bool Patient::getAdmissionStatus()
{
    return isAdmitted;
}

RoomType Patient::getRoomType()
{
    return roomType;
}
```
