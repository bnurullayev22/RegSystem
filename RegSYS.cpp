#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <regex>


using namespace std;
namespace fs = std::filesystem;

class Applicant {
private:
    string passport;
    string password;
    string firstName;
    string lastName;
    string email;
    string phone;
    string dateOfBirth;
    string faculty;
    string branch;
    string degree;
    string studyType;
    string nationality;
    string address;
    string securityAnswer;
    string educationLevel;
    string grade;

    bool doesFileExistInDirectory(const string& filename, const string& directory = ".") {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().filename() == filename) {
                return true;
            }
        }
        return false;
    }

    bool isValidEmail(const string& email) {
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);
        return atPos != string::npos && dotPos != string::npos && dotPos > atPos;
    }

    bool isValidPhoneNumber(const string& phone) {
        if (phone.length() < 10 || phone.length() > 15) return false;
        return all_of(phone.begin(), phone.end(), ::isdigit);
    }

    void clearInputBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string chooseEducationLevel() {
        cout << "\nChoose the highest level of education completed:\n";
        cout << "1. School\n";
        cout << "2. College\n";
        cout << "3. Bachelor Degree\n";
        cout << "4. Master Degree\n";
        cout << "5. PhD\n";
        cout << "Enter the number: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") return "School";
        else if (choice == "2") return "College";
        else if (choice == "3") return "Bachelor Degree";
        else if (choice == "4") return "Master Degree";
        else if (choice == "5") return "PhD";
        else return "Unknown";
    }
    string inputGrade() {
        string gradeInput;
        cout << "\nEnter your diploma/attestat grade (e.g., 4.5 or 90): ";
        getline(cin, gradeInput);

        while (!regex_match(gradeInput, regex(R"(^\d+(\.\d+)?$)"))) {
            cout << "Invalid grade format. Please enter a valid number: ";
            getline(cin, gradeInput);
        }

        return gradeInput;
    }

    string chooseBranch() {
        cout << "\nSelect a university branch:\n";
        cout << "1. Tashkent\n";
        cout << "2. Samarkhand\n";
        cout << "3. Namangan\n";
        cout << "Enter branch number: ";

        string branchChoice;
        getline(cin, branchChoice);

        if (branchChoice == "1") return "Tashkent";
        else if (branchChoice == "2") return "Samarkhand";
        else if (branchChoice == "3") return "Namangan";
        else return "Unknown branch";
    }

    string chooseStudyType() {
        cout << "\nChoose a type of education:\n";
        cout << "1. Full-time\n";
        cout << "2. Evening\n";
        cout << "3. Extramural\n";
        cout << "Enter number: ";

        string studyTypeChoice;
        getline(cin, studyTypeChoice);

        if (studyTypeChoice == "1") return "Full-time";
        else if (studyTypeChoice == "2") return "Evening";
        else if (studyTypeChoice == "3") return "Extramural";
        else return "Unknown";
    }

    string inputDateOfBirth() {
        string months[] = { "January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December" };
        cout << "\nSelect your birth month:\n";
        for (int i = 0; i < 12; ++i) {
            cout << i + 1 << ". " << months[i] << "\n";
        }
        cout << "Enter the number corresponding to your birth month: ";

        int monthChoice;
        cin >> monthChoice;
        cin.ignore();
        if (monthChoice < 1 || monthChoice > 12) {
            cout << "Invalid month. Defaulting to January.\n";
            monthChoice = 1;
        }
        string month = months[monthChoice - 1];

        cout << "Enter your birth day (1-31): ";
        int day;
        cin >> day;
        cin.ignore(); 
        if (day < 1 || day > 31) {
            cout << "Invalid day. Defaulting to 1.\n";
            day = 1;
        }

        cout << "Enter your birth year (e.g., 1990): ";
        int year;
        cin >> year;
        cin.ignore(); 

        return to_string(day) + " " + month + " " + to_string(year);
    }


public:
    Applicant() = default;
    void registerApplicant() {
        system("cls");
        cout << "=== Registration of the applicant ===\n";
        string directory = "."; 

        do {
            cout << "Enter passport data: ";
            getline(cin, passport);

            if (doesFileExistInDirectory(passport + ".txt", directory)) {
                cout << "File with the name" << passport << ".txt already exists. Registration is impossible.\n";
                cout << "Try another passport.\n";
            }
            else {
                break;
            }
        } while (true);

        cout << "Password: ";
        getline(cin, password);
        cout << "Name: ";
        getline(cin, firstName);
        cout << "Surname: ";
        getline(cin, lastName);
        cout << "Name of your first school: ";
        getline(cin, securityAnswer);
        dateOfBirth = inputDateOfBirth();

        do {
            cout << "email: ";
            getline(cin, email);
            if (!isValidEmail(email)) {
                cout << "Incorrect email.Try again.\n";
            }
        } while (!isValidEmail(email));

        do {
            cout << "Phone Number: ";
            getline(cin, phone);
            if (!isValidPhoneNumber(phone)) {
                cout << "Incorrect phone.\n";
            }
        } while (!isValidPhoneNumber(phone));

        faculty = chooseFaculty();
        branch = chooseBranch();
        studyType = chooseStudyType();
        educationLevel = chooseEducationLevel();
        grade = inputGrade();

        cout << "Nationality: ";
        getline(cin, nationality);
        cout << "Adress: ";
        getline(cin, address);

        cout << "Choose degree:\n1. Bachelor\n2. Master\n3. PhD\n";
        string degreeChoice;
        getline(cin, degreeChoice);
        if (degreeChoice == "1") degree = "Bachelor";
        else if (degreeChoice == "2") degree = "Master";
        else if (degreeChoice == "3") degree = "PhD";
        else degree = "Unknown degree";

        string filename = passport + ".txt";
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error while opening file!\n";
            return;
        }

        file << "Passport: " << passport << "\n"
            << "Password: " << password << "\n"
            << "FirstName: " << firstName << "\n"
            << "LastName: " << lastName << "\n"
            << "SecurityCheck: " << securityAnswer << "\n"
            << "Email: " << email << "\n"
            << "DateOfBirth: " << dateOfBirth << "\n"
            << "Phone: " << phone << "\n"
            << "Faculty: " << faculty << "\n"
            << "Branch: " << branch << "\n"
            << "StudyType: " << studyType << "\n"
            << "Nationality: " << nationality << "\n"
            << "Address: " << address << "\n"
            << "Degree: " << degree << "\n"
            << "Education Level: " << educationLevel << "\n"
            << "Grade: " << grade << "\n";

        file.close();
        cout << "Registration completed!: " << filename << "\n";
    }


    bool loginApplicant() {
        system("cls");
        string inputPassport, inputPassword;
        cout << "=== Login ===\n";
        cout << "Passport: ";
        getline(cin, inputPassport);
        cout << "Password: ";
        getline(cin, inputPassword);

        string filename = inputPassport + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error while opening file!\n";
            return false;
        }

        string line;
        string passport, password, firstName, lastName, securityAnswer, email, phone, faculty, branch, studyType, nationality, address, degree, educationLevel, grade;

        while (getline(file, line)) {
            if (line.find("Passport: ") == 0) passport = line.substr(10);
            else if (line.find("Password: ") == 0) password = line.substr(10);
            else if (line.find("FirstName: ") == 0) firstName = line.substr(11);
            else if (line.find("LastName: ") == 0) lastName = line.substr(10);
            else if (line.find("SecurityCheck: ") == 0) securityAnswer = line.substr(15);
            else if (line.find("Email: ") == 0) email = line.substr(7);
            else if (line.find("DateOfBirth: ") == 0) dateOfBirth = line.substr(13);
            else if (line.find("Phone: ") == 0) phone = line.substr(7);
            else if (line.find("Faculty: ") == 0) faculty = line.substr(9);
            else if (line.find("Branch: ") == 0) branch = line.substr(8);
            else if (line.find("StudyType: ") == 0) studyType = line.substr(11);
            else if (line.find("Nationality: ") == 0) nationality = line.substr(13);
            else if (line.find("Address: ") == 0) address = line.substr(9);
            else if (line.find("Degree: ") == 0) degree = line.substr(8);
            else if (line.find("Education Level: ") == 0) educationLevel = line.substr(17);
            else if (line.find("Grade: ") == 0) grade = line.substr(7);

        }

        file.close();

        if (passport == inputPassport && password == inputPassword) {
            cout << "\n=== Apllicant Data ===\n";
            cout << "Passport: " << passport << "\n";
            cout << "Name: " << firstName << "\n";
            cout << "Surname: " << lastName << "\n";
            cout << "SecurityCheck: " << securityAnswer << "\n";
            cout << "Email: " << email << "\n";
            cout << "Date of Birth: " << dateOfBirth << "\n";
            cout << "Phone: " << phone << "\n";
            cout << "Faculty: " << faculty << "\n";
            cout << "Branch: " << branch << "\n";
            cout << "Study Type: " << studyType << "\n";
            cout << "Nationality: " << nationality << "\n";
            cout << "Adress " << address << "\n";
            cout << "Degree: " << degree << "\n";
            cout << "Education Level: " << educationLevel << "\n";
            cout << "Grade: " << grade << "\n";

            return true;
        }

        cout << "Incorrect Data.\n";
        cout << "Do you want to restore? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            if (restorePassword(inputPassport)) {
                cout << "Password is changed.\n";
                return loginApplicant();
            }
            else {
                cout << "Error!.\n";
                return false;
            }
        }

        return false;
    }

    bool restorePassword(const string& inputPassport) {
        string filename = inputPassport + ".txt";
        ifstream file(filename); 
        if (!file.is_open()) {
            cerr << "Error while opening file for changing.\n";
            return false;
        }

        string line;
        string securityAnswer, storedAnswer, newPassword;

        string fileContent;
        while (getline(file, line)) {
            fileContent += line + "\n";
            if (line.find("SecurityCheck: ") == 0) storedAnswer = line.substr(15);
        }

        file.close(); 

        cout << "Your first school: " << securityAnswer << "\n";
        getline(cin, securityAnswer);

        if (securityAnswer == storedAnswer) {
            cout << "Answer is correct. Enter new password: ";
            getline(cin, newPassword);

            size_t pos = fileContent.find("Password: ");
            if (pos != string::npos) {
                size_t endPos = fileContent.find("\n", pos);
                fileContent.replace(pos, endPos - pos, "Password: " + newPassword);
            }

            ofstream outFile(filename, ios::trunc);
            if (!outFile.is_open()) {
                cerr << "Error.\n";
                return false;
            }

            outFile << fileContent;
            outFile.close();
            cout << "Password is changed.\n";
            return true;
        }
        else {
            cout << "Incorrect!.\n";
        }

        return false;
    }
    static string chooseFaculty () {
        cout << "Select the Department: \n";
        cout << "1. School of Engineering \n";
        cout << "2. School of business and finance \n";
        cout << "3. School of Education \n";
        cout << "4. School of Arts \n";
        cout << "5. School of Medicine \n";
        cout << "Enter the department number:";

        string departmentChoice;
        getline(cin, departmentChoice);

        if (departmentChoice == "1") {
            
            cout << "\nFaculties of the School of Engineering:\n";
            cout << "1. Mechatronics\n";
            cout << "2. Electrical Engineering\n";
            cout << "3. Mechanical Engineering\n";
            cout << "4. Elevator Engineering\n";
            cout << "5. Programming\n";
            cout << "6. Construction\n";
            cout << "7. Energy\n";
            cout << "8. Architecture\n";
            cout << "9. Drive\n";
            cout << "10. Space Technologies\n";
            cout << "Enter the faculty number: ";


            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") return "Mechatronics";
            else if (facultyChoice == "2") return "Electrical Engineering";
            else if (facultyChoice == "3")return "Mechanical Engineering";
            else if (facultyChoice == "4") return "Elevator Engineering";
            else if (facultyChoice == "5") return "Programming";
            else if (facultyChoice == "6") return "Construction";
            else if (facultyChoice == "7") return "Energy";
            else if (facultyChoice == "8") return "Architecture";
            else if (facultyChoice == "9") return "Drive";
            else if (facultyChoice == "10") return "Space Technologies";

            else return "Unknown";
        }
        else if (departmentChoice == "2") {
            cout << "\nFaculties of the School of Business and Finance:\n";
            cout << "1. Finance\n";
            cout << "2. Accounting\n";
            cout << "3. Banking\n";
            cout << "4. Tourism\n";
            cout << "5. Marketing\n";
            cout << "6. Business\n";
            cout << "7. International Relations\n";
            cout << "Enter the faculty number: ";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") return "Finance";
            else if (facultyChoice == "2") return "Accounting";
            else if (facultyChoice == "3") return "Banking";
            else if (facultyChoice == "4") return "Tourism";
            else if (facultyChoice == "5") return "Marketing";
            else if (facultyChoice == "6") return "Business";
            else if (facultyChoice == "7") return "International Relations";

            else return "Unknown";
        }
        else if (departmentChoice == "3") {
            cout << "\nFaculties of the School of Education:\n";
            cout << "1. Translation Studies\n";
            cout << "2. Pedagogy\n";
            cout << "3. History\n";
            cout << "4. English\n";
            cout << "5. Primary Education\n";
            cout << "6. Preschool Education\n";
            cout << "7. Philology\n";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") return "Translation Studies";
            else if (facultyChoice == "2") return "Pedagogy";
            else if (facultyChoice == "3") return "History";
            else if (facultyChoice == "4") return "English";
            else if (facultyChoice == "5") return "Primary Education";
            else if (facultyChoice == "6") return "Preschool Education";
            else if (facultyChoice == "7") return "Philology";

            else return "Unknown";
        }
        else if (departmentChoice == "4") {
            cout << "\nFaculties of the School of Arts:\n";
            cout << "1. Design\n";
            cout << "2. Painting\n";
            cout << "3. Aesthetics\n";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") return "Design";
            else if (facultyChoice == "2") return "Painting";
            else if (facultyChoice == "3") return "Aesthetics";

            else return "Unknown";
            
        }
        else if (departmentChoice == "5") {
            cout << "\nFaculties of the School of Medicine:\n";
            cout << "1. Dentistry\n";
            cout << "2. General Medicine\n";
            cout << "3. Nursing\n";
            cout << "4. Pediatrics\n";


            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") return "Dentistry";
            else if (facultyChoice == "2") return "General Medicine";
            else if (facultyChoice == "3") return "Nursing";
            else if (facultyChoice == "4") return "Pediatrics";

            else return "Unknown faculty";
        }
        else {
            return "Unknown department";
        }
    }
    
};

class Admin {
private:
    struct AdminCredentials {
        string name;
        string passport;
        string password;
    };
    vector<AdminCredentials> admins = {
        {"Behzod", "AD0408693", "2307807", },
        {"Aziz", "KIUT", "ISE", }
    };

public:
    bool loginAdmin() {
        string inputPassport, inputPassword;
        cout << "=== Administrator login ===\n";
        cout << "Enter your passport details: ";
        getline(cin, inputPassport);
        cout << "Enter password: ";
        getline(cin, inputPassword);

        for (const auto& admin : admins) {
            if (inputPassport == admin.passport && inputPassword == admin.password) {
                cout << "Administrator login " << admin.name << " completed successfully.\n";
                adminMenu();
                return true;
            }
        }
        cout << "Incorrect passport details or password.\n";
        return false;
    }

    void adminMenu() {
        system("cls");
        bool adminRunning = true;
        while (adminRunning) {
            cout << "\n=== Admin Menu ===\n";
            cout << "1. View all applicants\n";
            cout << "2. Filtering applicants\n"; 
            cout << "3. Editing\n";
            cout << "4. Removing an applicant\n";
            cout << "5. Exit admin menu\n";
            cout << "Select an option: ";

            string choice;
            getline(cin, choice);

            switch (stoi(choice)) {
            case 1:
                showAllApplicants();
                break;
            case 2:
                filterApplicants();
                break;
            case 3:
                editApplicant();
                break;
            case 4:
                deleteApplicant();
                break;
            case 5:
                adminRunning = false;
                break;
            default:
                cout << "Incorrect selection. Please try again.\n";
            }
        }
    }

    void filterApplicants() {
        system("cls");
        cout << "\n=== Filtering applicants ===\n";
        cout << "Select filter criteria:\n";
        cout << "1. By faculty\n";
        cout << "2. By degree\n";
        cout << "Enter the criterion number: ";

        string criterion;
        getline(cin, criterion);

        string value;
        if (criterion == "1") {
            cout << "Enter a value to filter: ";
            getline(cin, value);
        }
        else if (criterion == "2") {
            cout << "\nSelect a degree:\n";
            cout << "1. Bachelor\n";
            cout << "2. Master\n";
            cout << "3. PhD\n";
            cout << "Enter the number corresponding to the degree: ";

            string degreeOption;
            getline(cin, degreeOption);

            if (degreeOption == "1") {
                value = "Bachelor";
            }
            else if (degreeOption == "2") {
                value = "Master";
            }
            else if (degreeOption == "3") {
                value = "PhD";
            }
            else {
                cout << "Invalid option. Returning to menu.\n";
                return;
            }
        }
        else {
            cout << "Invalid criterion number. Returning to menu.\n";
            return;
        }

        cout << "\n=== Filtering results ===\n";
        bool found = false;

        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.path().extension() == ".txt") {
                ifstream file(entry.path());
                if (file.is_open()) {
                    string line;
                    bool match = false;

                    while (getline(file, line)) {
                        if ((criterion == "1" && line.find("Faculty: ") == 0 && line.substr(9) == value) ||
                            (criterion == "2" && line.find("Degree: ") == 0 && line.substr(8) == value)) {
                            match = true;
                        }
                    }

                    file.close();

                    if (match) {
                        ifstream fileToDisplay(entry.path());
                        while (getline(fileToDisplay, line)) {
                            cout << line << endl;
                        }
                        fileToDisplay.close();
                        cout << "-------------------\n";
                        found = true;
                    }
                }
            }
        }

        if (!found) {
            cout << "No applicants matching the criteria were found..\n";
        }
    }

    void editApplicant() {
        string passport;
        cout << "Enter the applicant's passport details for editing: ";
        getline(cin, passport);

        string filename = passport + ".txt";
        if (!fs::exists(filename)) {
            cout << "Applicant with the specified passport data not found.\n";
            return;
        }

        vector<string> lines;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        cout << "\n=== Applicant's details ===\n";
        for (size_t i = 0; i < lines.size(); ++i) {
            cout << i + 1 << ". " << lines[i] << endl;
        }

        cout << "\nEnter line number to edit or 0 to exit: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= lines.size()) {
            string newValue;
            cout << "Enter a new value: ";
            getline(cin, newValue);

            size_t pos = lines[choice - 1].find(": ");
            if (pos != string::npos) {
                lines[choice - 1] = lines[choice - 1].substr(0, pos + 2) + newValue;
            }

            ofstream outFile(filename);
            for (const auto& l : lines) {
                outFile << l << "\n";
            }
            outFile.close();
            cout << "Data updated successfully.\n";
        }
        else {
            cout << "Exit edit mode.\n";
        }
    }


    void showAllApplicants() {
        cout << "\n=== Data of all applicants ===\n";
        vector<string> applicants;
        int index = 1; 

        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.path().extension() == ".txt") {
                ifstream file(entry.path());
                if (file.is_open()) {
                    string line, firstName, lastName, passport, faculty;
                    while (getline(file, line)) {
                        if (line.find("FirstName: ") == 0) {
                            firstName = line.substr(11);
                        }
                        else if (line.find("LastName: ") == 0) {
                            lastName = line.substr(10);
                        }
                        else if (line.find("Passport: ") == 0) {
                            passport = line.substr(10); 
                        }
                        else if (line.find("Faculty: ") == 0) {
                            faculty = line.substr(9); 
                        }
                    }
                    file.close();
                    cout << index << ". " << "Name: " << firstName << ", Surname: " << lastName
                        << ", Passport: " << passport << ", Faculty: " << faculty << endl;

                    applicants.push_back(entry.path().string());
                    index++;
                }
            }
        }

        if (applicants.empty()) {
            cout << "Not Found.\n";
            return;
        }

        cout << "\nEnter the number of the applicant to view his data in detail, or 0 to exit: ";
        int choice;
        cin >> choice;
        cin.ignore(); 

        if (choice > 0 && choice <= applicants.size()) {
            string selectedFile = applicants[choice - 1];
            ifstream file(selectedFile);
            if (file.is_open()) {
                cout << "\n=== Detailed data from the applicant ===\n";
                string line;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            }
            else {
                cerr << "Error: " << selectedFile << endl;
            }
        }
        else if (choice == 0) {
            cout << "Exit to main menu.\n";
        }
        else {
            cout << "Incorrect choise!\n";
        }
    }


    void deleteApplicant() {
        string passport;
        cout << "Enter the passport details of the applicant you want to remove: ";
        getline(cin, passport);
        string filename = passport + ".txt";

        if (fs::exists(filename)) {
            fs::remove(filename);
            cout << "Applicant with a passport " << passport << " successfully removed.\n";
        }
        else {
            cout << "File with such passport not found.\n";
        }
    }
};

class GuestMode {
public:
    void showInfo() {
        system("cls");
        cout << "\n=== Guest mode ===\n";
        cout << "1. About the company\n";
        cout << "2. About the University\n";
        cout << "3. Return to main menu\n";
        cout << "Select an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            showCompanyInfo();
        }
        else if (choice == "2") {
            showUniInfo();
        }
        else if (choice == "3") {
            return;
        }
        else {
            cout << "Incorrect selection. Please try again.\n";
            showInfo();
        }
    }

private:
    void showUniInfo() {
        system("cls");
        cout << "\n=== About the University ===\n";
        cout << "1. Description of the University\n";
        cout << "2. Faculties\n";
        cout << "3. Branches\n";
        cout << "4. Return to guest mode\n";
        cout << "Select an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            showUniSelf();
        }
        else if (choice == "2") {
            showFaculties();
        }
        else if (choice == "3") {
            showFillials();
        }
        else if (choice == "4") {
            showInfo();
        }
        else {
            cout << "Incorrect selection. Please try again.\n";
            showUniInfo();
        }
    }

    void showCompanyInfo() {
        system("cls");
        cout << "\n=== Company information ===\n";
        cout << "1. Company History\n";
        cout << "2. Founders\n";
        cout << "3. Company Values\n";
        cout << "4. Return to guest mode\n";
        cout << "Select an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            showCompanyHistory();
        }
        else if (choice == "2") {
            showCompanyFounders();
        }
        else if (choice == "3") {
            showCompanyValues();
        }
        else if (choice == "4") {
            showInfo();
        }
        else {
            cout << "Incorrect selection. Please try again.\n";
            showCompanyInfo();
        }
    }

    void showUniSelf() {
        cout << "\n=== Description of the University ===\n";
        cout << "Our customer is KIUT, one of the leading universities in Uzbekistan..\n";
        cout << "KIUT was founded with the aim of providing\n";
        cout << "high-quality education and the introduction of international educational standards in Uzbekistan.\n";
        cout << "Over the years, KIUT has become one of the leading universities in the country, offering students\n";
        cout << "a wide range of educational programs and development opportunities.\n";
        cout << "Press Enter to return...";
        cin.get();
        showUniInfo();
    }

    void showFaculties() {
        system("cls");
        cout << "Select department:\n";
        cout << "1. School of Engineering\n";
        cout << "2. School of Business and Finance\n";
        cout << "3. School of Education\n";
        cout << "4. School of Arts\n";
        cout << "5. School of Medicine\n";
        cout << "Enter department number: ";

        string departmentChoice;
        getline(cin, departmentChoice);

        if (departmentChoice == "1") {

            cout << "\nSchool of Engineering Faculties:\n";
            cout << "1. Mechatronics\n";
            cout << "2. Electrical Engineering\n";
            cout << "3. Mechanical Engineering\n";
            cout << "4. Elevator Engineering\n";
            cout << "5. Programming\n";
            cout << "6. Construction\n";
            cout << "7. Energy\n";
            cout << "8. Architecture\n";
            cout << "9. Movement\n";
            cout << "10. Space Technologies\n";
            cout << "Enter the faculty number: ";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") showMechatronicsInfo();
            else if (facultyChoice == "2") showElectronicsInfo();
            else if (facultyChoice == "3") showMachineInfo();
            else if (facultyChoice == "4") showLiftInfo();
            else if (facultyChoice == "5") showProgInfo();
            else if (facultyChoice == "6") showBuildingInfo();
            else if (facultyChoice == "7") showEnergyInfo();
            else if (facultyChoice == "8") showArchiInfo();
            else if (facultyChoice == "9")  showDriveInfo();
            else if (facultyChoice == "10") showSpaceInfo();

            else cout << "Unknown faculty";
        }
        else if (departmentChoice == "2") {
            cout << "\nSchool of Business and Finance Faculties:\n";
            cout << "1. Finance\n";
            cout << "2. Accounting\n";
            cout << "3. Banking\n";
            cout << "4. Tourism\n";
            cout << "5. Marketing\n";
            cout << "6. Business\n";
            cout << "7. International Relations\n";
            cout << "Enter the faculty number: ";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") showFinanceInfo();
            else if (facultyChoice == "2") showACCInfo();
            else if (facultyChoice == "3") showBankInfo();
            else if (facultyChoice == "4") showTurismInfo();
            else if (facultyChoice == "5") showMarketingInfo();
            else if (facultyChoice == "6") showBusinessInfo();
            else if (facultyChoice == "7") showInterCultureInfo();

            else cout << "Unknown faculty";
        }
        else if (departmentChoice == "3") {
            cout << "\nFaculties of the School of Education:\n";
            cout << "1. Translation Studies\n";
            cout << "2. Pedagogy\n";
            cout << "3. History\n";
            cout << "4. English\n";
            cout << "5. Primary Education\n";
            cout << "6. Pre-school Education\n";
            cout << "7. Philology\n";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") showTransleteInfo();
            else if (facultyChoice == "2") showPedTeachInfo();
            else if (facultyChoice == "3") showHistoryInfo();
            else if (facultyChoice == "4") showEnglishInfo();
            else if (facultyChoice == "5") showNachalnoeShkolaInfo();
            else if (facultyChoice == "6") showDetsadInfo();
            else if (facultyChoice == "7") showFiloInfo();

            else cout << "Unknown faculty";
        }

        else if (departmentChoice == "4") {
            cout << "\nFaculties of the School of Arts:\n";
            cout << "1. Design\n";
            cout << "2. Painting\n";
            cout << "3. Aesthetics\n";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") showDizaynInfo();
            else if (facultyChoice == "2") showPaintInfo();
            else if (facultyChoice == "3") showEstetInfo();

            else cout << "Unknown faculty";

        }
        else if (departmentChoice == "5") {
            cout << "\nSchool of Medicine Departments:\n";
            cout << "1. Dentistry\n";
            cout << "2. General Medicine\n";
            cout << "3. Nurse\n";
            cout << "4. Pediatrician\n";

            string facultyChoice;
            getline(cin, facultyChoice);

            if (facultyChoice == "1") showTeethDocInfo();
            else if (facultyChoice == "2") showMedWorkInfo();
            else if (facultyChoice == "3") showMedSisInfo();
            else if (facultyChoice == "4") showPedDocInfo();

            else cout << "Unknown faculty";
        }
        else {
            cout << "Unknown department";
            cin.get();
            showUniInfo();
        }
    }
        
    void showMechatronicsInfo() {
        cout << "\n=== Mechatronics ===\n";
        cout << "Mechatronics combines mechanics, electronics and computer science.\n";
        cout << "This faculty trains specialists in the field of automation, robotics and intelligent systems.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }
    
    void showElectronicsInfo() {
        cout << "\n=== Electrical Engineering ===\n";
        cout << "The Faculty of Electrical Engineering trains specialists in the field of design and maintenance of electrical systems.\n";
        cout << "Graduates work on the creation of energy systems, electrical equipment and modern devices such as electric cars and smart homes.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showMachineInfo() {
        cout << "\n=== Mechanical Engineering ===\n";
        cout << "Mechanical engineering is a fundamental engineering field that deals with the design and production of machines and mechanisms.\n";
        cout << "Students study mechanical principles, materials science and manufacturing technology.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showLiftInfo() {
        cout << "\n=== Lift Engineering ===\n";
        cout << "The faculty specializes in the design, installation and maintenance of elevators and escalators.\n";
        cout << "Students study the mechanics of lifting devices, safety and modern automated control systems.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void  showProgInfo() {
        cout << "\n=== Programming ===\n";
        cout << "The Faculty of Programming trains specialists in the field of software development.\n";
        cout << "Key areas: web development, mobile applications, artificial intelligence and cybersecurity.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 19 900 000 sum\nEvening education: 16 900 000 sum\nExtramural education: 14 400 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showBuildingInfo() {
        cout << "\n=== Civil Engineering ===\n";
        cout << "Students of the Faculty of Civil Engineering study architecture, design and construction of buildings and infrastructure..\n";
        cout << "Particular attention is paid to sustainable and energy-efficient technologies.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 16 950 000 sum\nEvening education: 14 900 000 sum\nExtramural education: 11 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showEnergyInfo() {
        cout << "\n=== Renewable Energy ===\n";
        cout << "The faculty trains specialists in renewable energy sources, nuclear energy and energy systems..\n";
        cout << "Students study the generation, transmission and management of energy resources.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showArchiInfo() {
        cout << "\n=== Architecture and Urban DesignSpecial ===\n";
        cout << "The Faculty of Architecture trains future architects and designers of buildings and interiors.\n";
        cout << "Students study planning, urbanism, design and restoration.\n";
        cout << "Exams: Mathematics, Сreative exam and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 13 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showDriveInfo() {
        cout << "\n=== Traffic management ===\n";
        cout << "The faculty studies transport systems.\n";
        cout << "Students study the design and operation of vehicles and infrastructure.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showSpaceInfo() {
        cout << "\n=== Space Technology new ===\n";
        cout << "The faculty trains specialists in the field of space engineering and research programs..\n";
        cout << "Students learn about the design of satellites, rockets and space systems.\n";
        cout << "Exams: Mathematics and Physics.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 9 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showFinanceInfo() {
        cout << "\n=== Finance ===\n";
        cout << "The faculty trains specialists in the field of financial management, investments and financial analysis..\n";
        cout << "Students study corporate finance, financial markets, risk analysis and strategic planning.\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 900 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showACCInfo() {
        cout << "\n=== Accounting ===\n";
        cout << "The faculty specializes in training specialists in accounting, auditing and taxation.\n";
        cout << "Students study accounting standards, financial reporting and analysis.\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 900 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showBankInfo() {
        cout << "\n=== Banking ===\n";
        cout << "The faculty trains specialists in banking operations and financial services management.\n";
        cout << "Students study lending, asset management, banking risks and international banking.\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 900 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showTurismInfo() {
        cout << "\n=== Tourism ===\n";
        cout << "The Faculty of Tourism trains specialists in the field of tourism business and hospitality management.\n";
        cout << "Students study tourism marketing, tour organization and hotel management.\n";
        cout << "Exams: History and English.\n";
        cout << "Tuition fee: Full time education: 19 000 000 sum\nEvening education: 16 200 000 sum\nExtramural education: 14 400 000 sum.\n";
        cout << "Press Enter to return to faculty selection..."; 
        cin.ignore();
        cin.get();
    }

    void showMarketingInfo() {
        cout << "\n=== International Marketing ===\n";
        cout << "The Faculty of Marketing trains specialists in the development and implementation of marketing strategies.\n";
        cout << "Students study consumer behavior, digital marketing, branding and PR.\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 950 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showBusinessInfo() {
        cout << "\n=== Business Management ===\n";
        cout << "The Faculty of Business teaches the basics of entrepreneurship, management and strategic planning.\n";
        cout << "Students study human resources management, business analytics and economics.\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 950 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showInterCultureInfo() {
        cout << "\n=== International economic relations ===\n";
        cout << "The faculty trains specialists in diplomacy, global politics and international law.\n";
        cout << "Students study global politics, international security and economic diplomacy..\n";
        cout << "Exams: Mathematics and English.\n";
        cout << "Tuition fee: Full time education: 21 950 000 sum\nEvening education: 17 900 000 sum\nExtramural education: 13 950 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showTransleteInfo() {
        cout << "\n=== Translation studies (Chineese and English languages) ===\n";
        cout << "The faculty teaches translation and intercultural communication skills..\n";
        cout << "Students study translation theory, simultaneous and written translation practice, and cultural studies..\n";
        cout << "Exams: English.\n";
        cout << "Tuition fee: Full time education: 19 900 000 sum\nEvening education: 16 200 000 sum\nExtramural education: 14 400 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showPedTeachInfo() {
        cout << "\n=== Special Pedagogy ===\n";
        cout << "The faculty trains specialists in teaching and educating children.\n";
        cout << "Students study teaching methods, educational psychology and educational management.\n";
        cout << "Exams: English and Biology.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 12 960 000 sum\nExtramural education: 10 800 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showHistoryInfo() {
        cout << "\n=== History ===\n";
        cout << "The faculty offers an in-depth study of human history and cultural processes..\n";
        cout << "Students study world history, archaeology, historical sources and data analysis..\n";
        cout << "Exams: English and History.\n";
        cout << "Tuition fee: Full time education: 17 950 000 sum\nEvening education: 12 960 000 sum\nExtramural education: 10 800 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showEnglishInfo() {
        cout << "\n=== English Education ===\n";
        cout << "The Faculty of English trains specialists in linguistics, literature and teaching English.\n";
        cout << "Students study grammar, stylistics, British and American literature, and intercultural communication..\n";
        cout << "Exams: English.\n";
        cout << "Tuition fee: Full time education: 19 950 000 sum\nEvening education: 16 200 000 sum\nExtramural education: 12 000 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showNachalnoeShkolaInfo() {
        cout << "\n=== Primary education ===\n";
        cout << "The faculty trains future primary school teachers in the basics of teaching and raising children..\n";
        cout << "Students study pedagogy, early childhood psychology and teaching methods for various subjects..\n";
        cout << "Exams: English.\n";
        cout << "Tuition fee: Full time education: 18 000 000 sum\nEvening education: 12 960 000 sum\nExtramural education: 10 800 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showDetsadInfo() {
        cout << "\n=== Preschool education ===\n";
        cout << "The faculty trains specialists to work with preschool children.\n";
        cout << "Students study developmental psychology, methods of child development and upbringing, and child psychology..\n";
        cout << "Exams: English and Biology.\n";
        cout << "Tuition fee: Full time education: 18 000 000 sum\nEvening education: 12 960 000 sum\nExtramural education: 12 000 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showFiloInfo() {
        cout << "\n=== Korean Philology ===\n";
        cout << "The Faculty of Korean Philology studies the language, literature and culture of korean people.\n";
        cout << "Students study linguistics, textual criticism and literary criticism.\n";
        cout << "Exams: Topik.\n";
        cout << "Tuition fee: Full time education: 19 950 000 sum\nEvening education: 16 200 000 sum\nExtramural education: 10 800 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showDizaynInfo() {
        cout << "\n=== Fashion Design ===\n";
        cout << "The Faculty of Design teaches the creation of visual and functional solutions in various fields..\n";
        cout << "Students study graphic, industrial and digital design, as well as the basics of composition and color science..\n";
        cout << "Exams: Сreative Exam.\n";
        cout << "Tuition fee: Full time education: 19 000 000 sum\nEvening education: 14 590 000 sum\nExtramural education: 11 590 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showPaintInfo() {
        cout << "\n=== Painting ===\n";
        cout << "The Faculty of Painting offers in-depth study of fine art and various techniques.\n";
        cout << "Students study painting, drawing, art history and techniques for working with various materials..\n";
        cout << "Exams: Сreative Exam.\n";
        cout << "Tuition fee: Full time education: 18 000 000 sum\nEvening education: 12 960 000 sum\nExtramural education: 10 800 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showEstetInfo() {
        cout << "\n=== Beauty Aesthetics ===\n";
        cout << "The Faculty of Aesthetics studies the philosophical and theoretical foundations of beauty and art.\n";
        cout << "Students study art history, aesthetic theories and philosophy of culture..\n";
        cout << "Exams: Biology and Chemistry.\n";
        cout << "Tuition fee: Full time education: 19 900 000 sum\nEvening education: 15 900 000 sum\nExtramural education: 11 900 000 sum.\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showTeethDocInfo() {
        cout << "\n=== Dentistry ===\n";
        cout << "The Faculty of Dentistry trains specialists in dental care, treatment of oral diseases and maxillofacial surgery.\n";
        cout << "Students study anatomy, orthodontics, therapeutic and surgical dentistry.\n";
        cout << "Exams: Biology and Chemistry.\n";
        cout << "Tuition fee: Full time education: 29 900 000\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showMedWorkInfo() {
        cout << "\n=== General Medicine ===\n";
        cout << "The Faculty of General Medicine teaches diagnostics, treatment and prevention of diseases.\n";
        cout << "Students study clinical medicine, physiology, pathophysiology and pharmacology.\n";
        cout << "Exams: Biology and Chemistry.\n";
        cout << "Tuition fee: Full time education: 29 900 000\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showMedSisInfo() {
        cout << "\n=== Nursing  ===\n";
        cout << "The Faculty of Nursing provides training in patient care, basic medical care and emergency care.\n";
        cout << "Students study anatomy, patient care, pharmacology and basic psychology.\n";
        cout << "Exams: Biology and Chemistry.\n";
        cout << "Tuition fee: Full time education: 19 500 000 sum\nEvening education: 16 900 000 sum\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showPedDocInfo() {
        cout << "\n=== Pediatrics  ===\n";
        cout << "The Faculty of Pediatrics specializes in the diagnosis and treatment of diseases in children and adolescents..\n";
        cout << "Students study child physiology, immunology, infectious diseases and the basics of childhood psychology.\n";
        cout << "Exams: Biology and Chemistry.\n";
        cout << "Tuition fee: Full time education: 29 900 000\n";
        cout << "Press Enter to return to faculty selection...";
        cin.ignore();
        cin.get();
    }

    void showFillials() {
        cout << "\n=== Branches ===\n";
        cout << "Branches in Samarkand, Namangan and Tashkent.\n";
        cout << "Press Enter to return...";
        cin.get();
        showUniInfo();
    }

    void showCompanyHistory() {
        cout << "\n=== Company History ===\n";
        cout << "Our company was founded in 2024 by two classmates., \n";
        cout << "who have joined forces to create a product.\n";
        cout << "In just three months of hard work, we managed to develop and bring to market\n";
        cout << "a decision that became the basis of our success.\n";
        cout << "Press Enter to return...";
        cin.get();
        showCompanyInfo();
    }

    void showCompanyFounders() {
        cout << "\n=== Founders of the company ===\n";
        cout << "1. Technical Director\n";
        cout << "2. Marketing Manager\n";
        cout << "Press Enter to return...";
        cin.get();
        showCompanyInfo();
    }

    void showCompanyValues() {
        cout << "\n=== Company Values ===\n";
        cout << "Innovation, quality and responsibility.\n";
        cout << "Press Enter to return...";
        cin.get();
        showCompanyInfo();
    }
};

void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Applicant applicant;
    Admin admin;
    GuestMode guestMode;  
    bool running = true;

    while (running) {
        clearConsole();
        cout << "\n=== Applicant Enrollment System ===\n";
        cout << "1. Registration\n";
        cout << "2. Log In\n";
        cout << "3. Admin\n";
        cout << "4. Guest\n";  
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        string choice;
        getline(cin, choice);

        switch (stoi(choice)) {
        case 1:
            applicant.registerApplicant();
            break;
        case 2:
            if (applicant.loginApplicant()) {
                cout << "\nPress Enter to return to the main menu.";
                cin.ignore();
            }
            break;
        case 3:
            if (admin.loginAdmin()) {
                cout << "\nPress Enter to return to the main menu.";
                cin.ignore();
            }
            break;
        case 4:
            guestMode.showInfo(); 
            break;
        case 5:
            cout << "Exit the program.\n";
            running = false;
            break;
        default:
            cout << "Incorrect selection. Please try again..\n";
        }
    }

    return 0;
}
