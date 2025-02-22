#include <iostream>
using namespace std;

const int MAX_SPECIALIZATIONS = 20;
const int MAX_QUEUE = 5;

string names[MAX_SPECIALIZATIONS + 1][MAX_QUEUE];
int status[MAX_SPECIALIZATIONS + 1][MAX_QUEUE];
int queue_length[MAX_SPECIALIZATIONS + 1];

// help in adding patient
void shift_right(int spec, string names[], int status[])
{
    int len = queue_length[spec];
    for (int i = len - 1; i >= 0; --i)
    {
        names[i + 1] = names[i];
        status[i + 1] = status[i];
    }
    queue_length[spec]++;
}

// help in removing patient
void shift_left(int spec, string names[], int status[])
{
    int len = queue_length[spec];
    for (int i = 0; i <= len; ++i)
    {
        names[i] = names[i + 1];
        status[i] = status[i + 1];
    }
    queue_length[spec]--;
}

void add_patient()
{
    int spec;
    int st;
    string name;

    cout << "Enter the patient info: ";
    cin >> spec >> name >> st;

    int pos = queue_length[spec];

    if (pos >= MAX_QUEUE)
    {
        cout << "Sorry ! we can't take another case\n";
        return;
    }

    if (st == 0)
    {
        names[spec][pos] = name;
        status[spec][pos] = st;
        queue_length[spec]++;
    }
    else
    {
        shift_right(spec, names[spec], status[spec]);
        names[spec][0] = name;
        status[spec][0] = st;
    }
}

void print_all_patients()
{
    cout <<"---------------------------------------\n";
    for (int i = 1; i <= MAX_SPECIALIZATIONS; i++)
    {
        if (queue_length[i] > 0)
        {
            cout << "There are " << queue_length[i] << " in the specialization " << i << endl;

            for (int j = 0; j < queue_length[i]; j++)
            {
                cout << names[i][j] << " ";
                if (status[i][j] == 1)
                {
                    cout << "urgent" << endl;
                }
                else
                {
                    cout << "reguler" << endl;
                }
            }
        }
        else
        {
            continue;
        }
    }
}

void dr_pickup()
{
    int spec;
    cout <<"Enter the specialization: ";
    cin >> spec;
    if (queue_length[spec] <= 0){
        cout <<"There is no patient left"<<endl;
    }else{
        cout <<names[spec][0]<< " palse go with the doctor"<<endl;
        shift_left(spec, names[spec],status[spec]);
    }
}

void display_menu()
{
    cout << "\nHospital System" << endl;
    cout << "1) Add new patient" << endl;
    cout << "2) Print all patients" << endl;
    cout << "3) Dr. pickup patient" << endl;
    cout << "4) Exit" << endl;
}

void hospital_system()
{
    int choice;
    while (true)
    {
        display_menu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (!(choice >= 1 && choice <= 4))
        {
            cout << "Invalid choice. Please enter a correct one." << endl;
            continue;
        }
        cout <<endl;

        switch (choice)
        {
        case 1:
            add_patient();
            break;
        case 2:
            print_all_patients();
            break;
        case 3:
            dr_pickup();
            break;
        case 4:
            cout << "Exiting..." << endl;
            return;
        }
    }
}

int main()
{
    hospital_system();
    return 0;
}