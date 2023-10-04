#include <iostream>
#include <bits/stdc++.h>


using namespace std;

string globalUsername;

void keyboardBuffer(){ //function that clears keyboard buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void delExtraChar(string &str){ //function that is called to delete extra characters
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), '-'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '/'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '('), str.end());
    str.erase(std::remove(str.begin(), str.end(), ')'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '#'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '$'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

}

bool checkForUsersFile(){ //function that checks users.txt file exists
    ifstream file;
    file.open("users.txt");
    if (file){
        return true;
    }
    return false;
}

int mainSystemChoice(){ //function that asks for user option for switch case
    int userChoice;
    cout << "[OPTIONS: 1, 2, 3, 4]\n";
    cout << "ENTER OPTION NUMBER: ";
    cin >> userChoice;
    keyboardBuffer();
    while (userChoice <= 0 || userChoice >= 5){
        cout << "\nINVALID OPTION: Can only enter: 1, 2, 3, 4\n";
        cout << "ENTER OPTION NUMBER: ";
        cin >> userChoice;
        keyboardBuffer();
    }
    return userChoice;
}

int loginSystemChoice(){ //function that asks for user option for switch case
    int userChoice;
    cout << "(OPTIONS: 1, 2, 3, 4, 5, 6, 7, 8)\n";
    cout << "ENTER OPTION NUMBER: ";
    cin >> userChoice;
    keyboardBuffer();
    while (userChoice < 1 || userChoice > 7){
        cout << "\nINVALID INPUT: Can only enter: 1, 2, 3, 4, 5, 6, 7, 8\n";
        cout << "ENTER OPTION NUMBER: ";
        cin >> userChoice;
        keyboardBuffer();
    }
    return userChoice;
}

bool changeDataFunction(vector <string> textData, string input, int index){
    int i;
    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--\n";
        return false;
    }
    for (i = 0; i < textData.size(); i++){
        if (i != index){
            fileCredentialsWrite << textData[i] << '\n';
        }
        else{
            fileCredentialsWrite << input << '\n';
        }
    }
    return true;
}

bool validateNumbers(string& input){ //function that checks if the DOB is the appropriate length
    while (input.length() < 8 || input.length() > 8){
        cout << "\n--INVALID INPUT: Not A Valid Number--";
        cout << "\n[FORMAT: 00/00/0000]\n";
        cout << "ENTER DATE OF BIRTH: ";
        getline(cin, input);
        delExtraChar(input);
    }
    return true;
}

bool validateLetters(string& input){ //function that checks if the DOB is contains letters
    int check = 0;
    for (int i = 0; i <= input.length(); i++){
        if (isalpha(input[i])){
            cout << "\n--INVALID INPUT: Cannot Contain Letters--\n";
            cout << "\n[FORMAT: 00/00/0000]\n";
            cout << "ENTER DATE OF BIRTH: ";
            getline(cin, input);
            delExtraChar(input);
            return false;
        }
    }
    return true;
}

bool validateMonth(string& input){ //function that checks if the Month is valid
    string temp;
    int month;
    temp = input.substr(0, 2);
    month = stoi(temp);

    while (month < 1 || month > 12){
        cout << "\n--INVALID INPUT: Month Does Not Exist--\n";
        cout << "\n[FORMAT: 00/00/0000]\n";
        cout << "ENTER DATE OF BIRTH: ";
        getline(cin, input);
        delExtraChar(input);
        temp = input.substr(0, 2);
        month = stoi(temp);
    }
    return true;
}

bool validateDate(string& input){ //function that checks if the Date is valid
    string temp;
    int date, month;
    temp = input.substr(2, 2);
    date = stoi(temp);

    while (date < 1 || date > 31){
        cout << "\n--INVALID INPUT: Date Does Not Exist--\n";
        cout << "\n[FORMAT: 00/00/0000]\n";
        cout << "ENTER DATE OF BIRTH: ";
        getline(cin, input);
        delExtraChar(input);
        temp = input.substr(2, 2);
        date = stoi(temp);
    }
    return true;
}

bool validateYear(string& input){ //function that checks if the Year is valid
    string temp;
    int year;
    temp = input.substr(4, 4);
    year = stoi(temp);
    while (year < 1900 || year > 2023){
        cout << "\n-INVALID INPUT: Year Does Not Exist--\n";
        cout << "\n[FORMAT: 00/00/0000]\n";
        cout << "ENTER DATE OF BIRTH: ";
        getline(cin,input);
        delExtraChar(input);
        temp = input.substr(4, 4);
        year = stoi(temp);
    }
    return true;
}

bool checkAlNum(string input){ //function that checks a Username for special characters
    int i;
    for (i = 0; i < input.length(); i++){
        if (isalnum(input[i]) == 0){
            cout << "--INVALID INPUT: No special characters allowed--\n";
            return false;
        }
    }
    return true;
}

bool usernameExists(string input){ //function that checks if there is an existing Username
    ifstream fileCredentials;
    int i = 0;
    string line;
    vector<string> credentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (getline(fileCredentials, line)){
            credentials.push_back(line);
        }
    }
    else{
        cout << "--File could not be opened--\n";
    }

    fileCredentials.close();
    while (i < credentials.size()){
        if (input == credentials[i]){
            fileCredentials.close();
            cout << "--INVALID INPUT: Username already exists--\n";
            return false;
        }
        i += 8;
    }
    return true;
}

bool checkLogin(string usernameInput, string passwordInput){ //function that checks if Username matches Password
    vector<string> txtCredentials;
    string text;
    int i = 0;
    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()) {
            while (getline(fileCredentials, text)){
                txtCredentials.push_back(text);
            }
        }
    }
    else{
        cout << "\t--File could not be opened--\n";
        return false;
    }
    if (txtCredentials.empty()){
        cout << "\n\t--File Is Empty, Please Register Account--\n\n";
        return false;
    }

    i = 0;
    while (i <= txtCredentials.size()){
        if (txtCredentials.empty()){
            cout << "\n\t--No Users Found, Please Register Account--";
            return false;
        }
        if (usernameInput == txtCredentials[i] && passwordInput == txtCredentials[i + 1]){
            return true;
            }
        i += 8;
    }
    return false;
}

bool checkEmail(string email){
    int dotCheck = -1, atCheck = -1, i;
    for (i = 0; i < email.length(); i++){
        if (email[i] == '@'){
            atCheck = i;
        }
        else if (email[i] == '.'){
            dotCheck = i;
        }
    }
    if (atCheck == -1 || dotCheck == -1){
        cout << "\nINVALID INPUT: Not A Valid Email\n";
        return false;
    }
    if (atCheck > dotCheck){
        cout << "\nINVALID INPUT: Not A Valid Email\n";
        return false;
    }
    return !(dotCheck >= (email.length()) - 1);
}

string setUsername(){ //function that asks for user Username input
    string input;
    do{    
        cout << "ENTER NEW USERNAME: ";
        getline(cin, input);
        while (input.length() < 3 || input.length() > 50){
            cout << "\nINVALID INPUT: Username must be more than 2 characters and less than 50 characters\n";
            cout << "ENTER NEW USERNAME: ";
            getline(cin, input);
        }
    }while (checkAlNum(input) != 1 || usernameExists(input) != 1);
    return input;
}

string setPassword(){ //function that asks for user Password input
    string input;
    int i = 0;
    cout << "\nENTER PASSWORD: ";
    getline(cin, input);
    while (input.length() < 3 || input.length() > 50){
        cout << "\nINVALID INPUT: Password must be more than 2 character and less than 50 characters\n";
        cout << "ENTER PASSWORD: ";
        getline(cin, input);
    }
    return input;
}

string setFirstName(){ //function that asks for user First Name input
    string input;
    cout << "\nENTER FIRST NAME: ";
    getline(cin, input);
    while (!checkAlNum(input)){
        cout << "\nENTER FIRST NAME: ";
        getline(cin, input);
    }
    return input;
}

string setLastName(){ //function that asks for user Last Name input
    string input;
    cout << "\nENTER LAST NAME: ";
    getline(cin, input);
    while (!checkAlNum(input)){
        cout << "\nENTER LAST NAME: ";
        getline(cin, input);
    }
    return input;
}

string setEmail(){ //function that asks for user Email input
    string input;
    bool findAt;
    cout << "\nENTER NEW EMAIL: ";
    getline(cin, input);
    while (!checkEmail(input)){
        cout << "\nENTER NEW EMAIL: ";
        getline(cin, input);
    }
    return input;
}

bool phoneNumberCheck(string& input){
    int check = 0;
    if (input.length() < 10 || input.length() > 10){
        cout << "\nINVALID INPUT: Not A Valid Number\n";
        return false;
    }
    for (int i = 0; i <= input.length(); i++){
        if (isalpha(input[i])){
            cout << "\nINVALID INPUT: Cannot Contain Letters\n";
            return false;
        }
    }
    return true;
}

string setPhoneNumber(){ //function that asks for user Phone Number input
    string input, first3string, second3string, final4string, phoneIntReturn;
    int check = 0, check2 = 0;
    cout << "\n[FORMAT: 000 000 0000]";
    cout << "\nENTER PHONE NUMBER: ";
    getline(cin, input);
    delExtraChar(input);

    while (check != 1){
        check = 0;
        if (phoneNumberCheck(input)){
            check++;
        }
        else{
            cout << "\nENTER PHONE NUMBER: ";
            getline(cin, input);
            delExtraChar(input);
        }
    }

    first3string = input.substr(0, 3);
    second3string = input.substr(3, 3);
    final4string = input.substr(6, 4);

    phoneIntReturn = first3string + '-' + second3string + '-' + final4string;

    return phoneIntReturn;
}

string setDOB(){ //function that asks for user DOB input
    string input, month, date, year, DOB;
    int temp = 0;
    cout << "\n\t--Please Enter Numerical Values for DOB--\n";
    cout << "\n[FORMAT: 00/00/0000]\n";
    cout << "ENTER DATE OF BIRTH: ";
    getline(cin, input);
    delExtraChar(input);

    while(temp != 6){
        temp = 0;
        if (checkAlNum(input)){
            temp ++;
        }
        else{
            cout << "\n[FORMAT: 00/00/0000]\n";
            cout << "ENTER DATE OF BIRTH: ";
        }
        if (validateNumbers(input)){
            temp ++;
        }
        if (validateLetters(input)){
            temp ++;
        }
        if (validateMonth(input)){
            temp ++;
        }
        if (validateDate(input)){
            temp ++;
        }
        if (validateYear(input)){
            temp ++;
        }
    }
    month = input.substr(0, 2);
    date = input.substr(2, 2);
    year = input.substr(4, 4);

    DOB = month + "-" + date + "-" + year;


    return DOB;
}

void registerData(string userUsername, string userPassword, string userFirstName, string userLastName, string userEmail, string userPhoneNumber, string userDOB) {
    //function that inputs user information into a text file
    ofstream fileCredentials;

    fileCredentials.open("users.txt", ios::app);
    if (fileCredentials.is_open()){
        fileCredentials << userUsername << '\n' << userPassword << '\n' << userFirstName << '\n' << userLastName << '\n' << userEmail << '\n' << userPhoneNumber << '\n' << userDOB << "\n" << "\n";
        cout << "\n\n\t     --REGISTRATION  COMPLETE--\n\n\n";
    }
    else{
        cout << "--File could not be opened--\n";
    }

    fileCredentials.close();
}

void setUserData(){ //function that calls functions to collect user information for registration
    string userUsername, userPassword, userFirstName, userLastName, userEmail, userDOB, userPhoneNumber;
    cout << "\n\t\t--REGISTRATION--\n";
    cout << "---------------------------------------------------\n\n";
    if(!checkForUsersFile()){
        ofstream requiredFile("users.txt");
        requiredFile.close();
    }
    userUsername = setUsername();
    userPassword = setPassword();
    userFirstName = setFirstName();
    userLastName = setLastName();
    userEmail = setEmail();
    userPhoneNumber = setPhoneNumber();
    userDOB = setDOB();

    registerData(userUsername, userPassword, userFirstName, userLastName, userEmail, userPhoneNumber, userDOB);
}

bool login(){ //function that accepts user input for Username and Password
    string usernameInput, passwordInput;
    cout << "\n\t\t   --LOGIN--\n";
    cout << "---------------------------------------------------\n\n";
    cout << "ENTER USERNAME: ";
    getline(cin, usernameInput);
    cout << "ENTER PASSWORD: ";
    getline(cin, passwordInput);
    
    if (checkLogin(usernameInput, passwordInput)){
        cout << "\n\n\t\t--LOGIN SUCCESSFUL--\n";
        globalUsername = usernameInput;
        return true;
    }
    else{
        cout << "\n\n\t\t   --LOGIN FAILED--\n";
        return false;
    }
}

bool tryAgain(){ //function that is called after a failed attempt
    char choice;
    cout << "TRY ON MORE TIME? [Y/N]: ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        keyboardBuffer();
        return true;
    }
    else{
        cout << "\t\t--RETURNING TO MENU--\n";
        return false;
    }
}

bool usernameAndPasswordDisplay(){ //function that asks if 
    char choice;
    cout << "\nDisplay Username and Password? [Y/N]: ";
    cin >> choice;
    while (isalpha(choice)){
        if (choice == 'y' || choice == 'Y'){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

void displayUserData(){ //function to display user information
    vector<string> txtCredentials;
    string line;
    int choice, index, i = 0;
    ifstream fileCredentials;
    fileCredentials.open ("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()) {
            while (getline(fileCredentials, line)){
                txtCredentials.push_back (line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";

    }
    while (i <= txtCredentials.size()){
        if (globalUsername != txtCredentials[i]){
            i += 8;
        }
        if (globalUsername == txtCredentials[i]){
            break;
        }
    }
    index = i;
    cout << '\n';
    cout << "FIRST NAME: " << txtCredentials[index + 2] << '\n';
    cout << "LAST NAME: " << txtCredentials[index + 3] << '\n';
    cout << "EMAIL: " << txtCredentials[index + 4] << '\n';
    cout << "PHONE NUMBER: " << txtCredentials[index + 5] << '\n';
    cout << "DATE OF BIRTH: " << txtCredentials[index + 6] << '\n';
    choice = usernameAndPasswordDisplay();
    if (choice){
        cout << '\n';
        cout << "USERNAME: " << txtCredentials[index] << '\n';
        cout << "PASSWORD: " << txtCredentials[index + 1] << '\n' << '\n';
    }
}

bool changePassword(){ //function to change user Password
    string usernameInput, line, firstName, lastName, email, newPassword;
    int passwordIndex, i = 0;
    vector<string> txtCredentials;
    
    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()){
            while (getline(fileCredentials, line)){
                txtCredentials.push_back (line);
            }
        }

    }
    else{
        cout << "--File could not be opened--\n";
    }
    if (txtCredentials.empty()){
        cout << "\n\t--File Is Empty, Please Register Account--\n\n";
        return false;
    }
    fileCredentials.close();

    cout << "\n\t--CHANGE PASSWORD--\n";
    cout << "ENTER USERNAME: ";
    getline(cin, usernameInput);

    while (i <= txtCredentials.size()){
        if (usernameInput != txtCredentials[i]){
            i += 8;
        }
        if (usernameInput == txtCredentials[i]){
            break;
        }
    }
    passwordIndex = i + 1;
    if (usernameInput != txtCredentials[i]){
        cout << "\n\t--USERNAME NOT FOUND--\n\n";
        return false;
    }

    cout << "\n\t--USERNAME FOUND--\n";
    cout << "  --Names are case sensitive--\n";
    cout << "ENTER FIRST NAME: ";
    getline(cin, firstName);
    cout << "ENTER LAST NAME: ";
    getline(cin, lastName);
    cout << "ENTER EMAIL: ";
    getline(cin, email);
    
    if (firstName == txtCredentials[i + 2] && lastName == txtCredentials[i + 3] && email == txtCredentials[i + 4]){
        cout << "\n--FIRST NAME, LAST NAME AND EMAIL MATCHES--\n";
        newPassword = setPassword();
    }
    else{
        cout << "\n--First Name, Last Name, and email do not match--\n\n";
        return false;
    }

    if(!changeDataFunction(txtCredentials, newPassword, passwordIndex)){
        cout << " --ERROR HAS OCCURRED--\n";
    }
    else{
        cout << "\n\n\t--PASSWORD CHANGED--\n\n\n";
    }
    return true;
}

bool changeUsername(){ //function to change user Username
    vector <string> txtCredentials;
    string newUsername, usernameInput, line;
    int usernameIndex, i = 0;

    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()){
            while(getline(fileCredentials, line)){
                txtCredentials.push_back(line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";
        return false;
    }
    fileCredentials.close();
    cout << "\n\t--CHANGE USERNAME--\n\n";
    cout << "ENTER PREVIOUS USERNAME: ";
    getline(cin, usernameInput);

    while (i <= txtCredentials.size()){
        if (usernameInput != txtCredentials[i]){
            i += 8;
        }
        if (usernameInput == txtCredentials[i]){
            break;
        }
    }
    usernameIndex = i;
    if (usernameInput != txtCredentials[i]){
        cout << "\nUSERNAME DOES NOT MATCH\n\n\n\n";
        return false;
    }
    cout << "\n\t--USERNAME MATCHES--\n\n";

    newUsername = setUsername();

    if(!changeDataFunction(txtCredentials, newUsername, usernameIndex)){
        cout << " --ERROR HAS OCCURRED--\n";
    }
    else{
        cout << "\n\n\t--USERNAME CHANGED--\n\n\n";
    }
    globalUsername = newUsername;
    return true;
}

bool changePhoneNumber(){ //function to change user Phone Number
    vector <string> txtCredentials;
    string usernameInput, newPhoneNumber, first3string, second3string, final4string, newPhoneWrite, line;
    int index, i = 0, check = 0;
    cout << "\n\t--CHANGE PHONE NUMBER--\n";
    cout << "\nENTER USERNAME: ";
    getline(cin, usernameInput);
    if (usernameInput != globalUsername){
        cout << "\nUSERNAME DOES NOT MATCH\n";
        return false;
    }
    cout << "\n\t--USERNAME MATCHES--\n\n";
    cout << "[FORMAT: 000 000 0000]\n";
    cout << "ENTER NEW PHONE NUMBER: ";
    getline (cin, newPhoneNumber);
    delExtraChar(newPhoneNumber);
    while (check != 1){
        check = 0;
        if (phoneNumberCheck(newPhoneNumber)){
            check++;
        }
        else{
            cout << "\nENTER PHONE NUMBER: ";
            getline(cin, newPhoneNumber);
            delExtraChar(newPhoneNumber);
        }
    }

    first3string = newPhoneNumber.substr(0, 3);
    second3string = newPhoneNumber.substr(3, 3);
    final4string = newPhoneNumber.substr(6, 4);

    newPhoneWrite = first3string + '-' + second3string + '-' + final4string;

    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()){
            while(getline(fileCredentials, line)){
                txtCredentials.push_back(line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";
        return false;
    }
    fileCredentials.close();
    while (i <= txtCredentials.size()){
        if (usernameInput != txtCredentials[i]){
            i += 8;
        }
        if (usernameInput == txtCredentials[i]){
            break;
        }
    }

    index = i + 5;

    if(!changeDataFunction(txtCredentials, newPhoneWrite, index)){
        cout << " --ERROR HAS OCCURRED--\n";
    }
    else{
        cout << "\n\n\t--PHONE NUMBER CHANGED--\n\n\n";
    }
    return true;
}

bool changeDOB(){ //function to change user DOB
    string DOBinput, month, date, year, DOB, usernameInput, line;
    vector <string> txtCredentials;
    int i = 0, temp = 0, index;
    cout << "\n\t--CHANGE PHONE NUMBER--\n";
    cout << "\nENTER USERNAME: ";
    getline(cin, usernameInput);
    if (usernameInput != globalUsername){
        cout << "USERNAME DOES NOT MATCH\n";
        return false;
    }
    cout << "\t--USERNAME MATCHES--\n\n";
    cout << "\n--Please Enter Numerical Values for DOB--\n";
    cout << "\n[FORMAT: 00/00/0000]\n";
    cout << "ENTER DATE OF BIRTH: ";
    getline(cin, DOBinput);
    delExtraChar(DOBinput);

    while(temp != 5){
        temp = 0;
        if (validateNumbers(DOBinput)){
            temp ++;
        }
        if (validateLetters(DOBinput)){
            temp ++;
        }
        if (validateMonth(DOBinput)){
            temp ++;
        }
        if (validateDate(DOBinput)){
            temp ++;
        }
        if (validateYear(DOBinput)){
            temp ++;
        }
    }
    month = DOBinput.substr(0, 2);
    date = DOBinput.substr(2, 2);
    year = DOBinput.substr(4, 4);

    DOB = month + "-" + date + "-" + year;

    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()){
            while(getline(fileCredentials, line)){
                txtCredentials.push_back(line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";
        return false;
    }
    fileCredentials.close();
    while (i <= txtCredentials.size()){
        if (usernameInput != txtCredentials[i]){
            i += 8;
        }
        if (usernameInput == txtCredentials[i]){
            break;
        }
    }

    index = i + 6;

    if(!changeDataFunction(txtCredentials, DOB, index)){
        cout << " --ERROR HAS OCCURRED--\n";
    }
    else{
        cout << "\n\n\t--DATE OF BIRTH CHANGED--\n\n\n";
    }
    return true;
}

bool changeEmail(){
    vector <string> txtCredentials;
    string passwordInput, usernameInput, line, newEmail;
    int emailIndex, i = 0;

    ifstream fileCredentials;
    fileCredentials.open("users.txt");
    if (fileCredentials.is_open()){
        while (!fileCredentials.eof()){
            while(getline(fileCredentials, line)){
                txtCredentials.push_back(line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";
        return false;
    }
    fileCredentials.close();
    cout << "\n\t\t--CHANGE EMAIL--\n\n";
    cout << "ENTER CURRENT USERNAME: ";
    getline(cin, usernameInput);
    cout << "ENTER CURRENT PASSWORD: ";
    getline(cin, passwordInput);

    while (i <= txtCredentials.size()){
        if (usernameInput != txtCredentials[i]){
            i += 8;
        }
        if (usernameInput == txtCredentials[i]){
            break;
        }
    }
    emailIndex = i + 4;

    if (usernameInput != txtCredentials[i] || passwordInput != txtCredentials[i + 1]){
        cout << "\n\t--USERNAME AND PASSWORD DOES NOT MATCH--\n";
        return false;
    }
    cout << "\n\t--USERNAME AND PASSWORD MATCHES--\n";
    newEmail = setEmail();    

    if(!changeDataFunction(txtCredentials, newEmail, emailIndex)){
        cout << " --ERROR HAS OCCURRED--\n";
    }
    else{
        cout << "\n\n\t\t--EMAIL CHANGED--\n\n\n";
    }
    return true;
}

void deleteAccount(){ //function to delete user information
    char choice;
    string line, line_2;
    int usernameIndex, i = 0;
    vector <string> txtCredentials;

    cout << "ARE YOU SURE WANT TO DELETE YOUR ACCOUNT? [Y/N]: ";
    cin >> choice;

    ifstream fileCredentialsRead;
    fileCredentialsRead.open("users.txt");
    if (fileCredentialsRead.is_open()){
        while (!fileCredentialsRead.eof()){
            while (getline(fileCredentialsRead, line)){
                txtCredentials.push_back(line);
            }
        }
    }
    else{
        cout << "--File could not be opened--\n";
        return;
    }
    fileCredentialsRead.close();
    while (i <= txtCredentials.size()){
        if (globalUsername != txtCredentials[i]){
            i += 8;
        }
        if (globalUsername == txtCredentials[i]){
            break;
        }
    }
    usernameIndex = i;
    txtCredentials.erase(txtCredentials.begin()+usernameIndex-1, txtCredentials.begin()+usernameIndex+7);
    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--\n";
        return;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        fileCredentialsWrite << txtCredentials[i] << '\n';
    }
    fileCredentialsWrite.close();
}

void changePhoneNumberSystem(){
    if (changePhoneNumber()){
        //calls the function to change Phone Number
        return;
    }
    else{
        if (tryAgain()){
            //calls function if user wants to try to change Phone Number again after a failed attempt
            changePhoneNumber(); //calls the function to change Phone Number
        }
        else{
            return;
        } 
    }
}

void forgetPasswordSystem(){
    if (changePassword()){
        //calls the function to change Password
        return;
    }
    else{
        if (tryAgain()){
            //calls function if user wants to try to change Password again after a failed attempt
            changePassword();
            //calls the function to change Phone Number
        }
        else{
            return;
        } 
    }
}

void changeUsernameSystem(){
    if (changeUsername()){
        //calls the function to change Username
        return;
    }
    else{
        if (tryAgain()){
            //calls function if user wants to try to change Username again after a failed attempt
            changeUsername();
            //calls the function to change Username
        }
        else{
            return;
        }
    }
}

void changeDOBSystem(){
    if (changeDOB()){
        //calls the function to change Date of Birth
        return;
    }
    else{
        if (tryAgain()){
            //calls function if user wants to try to change DOB again after a failed attempt
            changeDOB();
            //calls the function to change Date of Birth
        }
        else{
            return;
        }
    }
}

void changeEmailSystem(){
    if (changeEmail()){
        //calls the function to change Date of Birth
        return;
    }
    else{
        if (tryAgain()){
            //calls function if user wants to try to change DOB again after a failed attempt
            changeEmail();
            //calls the function to change Date of Birth
        }
        else{
            return;
        }
    }
}

void loggedIntoSystem(){
    int input;
    do{
        cout << "\n\t\t--SYSTEM MENU--\n";
        cout << "---------------------------------------------------\n\n";
        cout << "    Input 1 --> Display Personal Information\n";
        cout << "    Input 2 --> Change Username\n";
        cout << "    Input 3 --> Change Password\n";
        cout << "    Input 4 --> Change Email\n";
        cout << "    Input 5 --> Change Phone Number\n";
        cout << "    Input 6 --> Change DOB\n";
        cout << "    Input 7 --> Delete Account\n";
        cout << "    Input 8 --> Log Out\n\n";
        input = loginSystemChoice();
        switch (input){
            case 1:{
                displayUserData(); //displays user information
                break;
            }
            case 2:{
                changeUsernameSystem(); //calls a function to change user Username
                break;
            }
            case 3:{
                forgetPasswordSystem(); //calls a function to change user Password
                break;
            }
            case 4:{
                changeEmailSystem(); //calls a function to change user Email
                break;
            }
            case 5:{
                changePhoneNumberSystem(); //calls a function to change user Phone Number
                break;
            }
            case 6:{
                changeDOBSystem(); //calls a function to change user DOB
                break;
            }
            case 7:{
                deleteAccount();
                cout << "\n\t\t--ACCOUNT DELETED--\n\n";
                return;
            }
            case 8:{
                cout << "\n\t\t--ACCOUNT LOGGED OUT--\n";
                return;
            }
        }        
    }while (input != 7);
}

void loginSystem(){
    if (login()){
        //calls function to login
        loggedIntoSystem();
        //calls function that allows user to change their information after logging in successfully
        return;
    }
    else{
        if (tryAgain())
            //calls function if user wants to try to login again after a failed attempt
            if (login()){
                //calls function to login
                loggedIntoSystem();
                    //calls function that allows user to change their information after logging in successfully
                return;
            }
            else{
                return;
            }
        else
            return;
    }
}

int main(){
    int input;
    if (!checkForUsersFile()){
        ofstream requiredFile("users.txt");
        requiredFile.close();
    }
    do{
        cout << "                   --LOGIN MENU--\n";
        cout << "---------------------------------------------------\n\n";
        cout << "       Input 1 --> Account Registration\n";
        cout << "       Input 2 --> Login\n";
        cout << "       Input 3 --> Forget Password?\n";
        cout << "       Input 4 --> End Program\n\n\n";

        input = mainSystemChoice();
        switch (input) {
            case 1:{
                setUserData(); //calls a function to register a user's information
                break;
            }
            case 2:{
                loginSystem(); //calls a function to allow user to log in
                break;
            }
            case 3:{
                forgetPasswordSystem(); //calls a function to change user Password without logging in
                break;
            }
            case 4:{
                cout << "\n\n\t\tPROGRAM SHUT DOWN\n";
                cout << "\n\nThank you for using Jun's Personal Login Project!\n\n";
            }
        }
    }while (input != 4);
    return 0;
}
