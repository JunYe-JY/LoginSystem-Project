#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ios>
#include <limits>
#include <cctype>
#include <algorithm>
#include <thread>
#include <chrono>

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
}

bool checkForUsersFile(){ //function that checks users.txt file exists
    ifstream file;
    file.open("users.txt");
    if (file){
        return true;
    }
    else{
        cout << "ERROR OPENING FILE" << endl;
        return false;
    }
    return false;
}

int mainSystemChoice(){ //function that asks for user option for switch case
    int userChoice;
    cout << "[OPTIONS: 1, 2, 3, 4]" << endl;
    cout << "ENTER OPTION NUMBER: ";
    cin >> userChoice;
    keyboardBuffer();
    while (userChoice <= 0 || userChoice >= 5){
        cout << endl << "INVALID OPTION: Can only enter: 1, 2, 3, 4" << endl;
        cout << "ENTER OPTION NUMBER: ";
        cin >> userChoice;
        keyboardBuffer();
    }
    return userChoice;
}

int loginSystemChoice(){ //function that asks for user option for switch case
    int userChoice;
    cout << "(OPTIONS: 1, 2, 3, 4, 5, 6 ,7)" << endl;
    cout << "ENTER OPTION NUMBER: ";
    cin >> userChoice;
    keyboardBuffer();
    while (userChoice < 1 || userChoice > 7){
        cout << endl << "INVALID INPUT: Can only enter: 1, 2, 3, 4, 5, 6, 7" << endl;
        cout << "ENTER OPTION NUMBER: ";
        cin >> userChoice;
        keyboardBuffer();
    }
    return userChoice;
}

bool validateNumbers(string& input){ //function that checks if the DOB is the appropriate length
    while (input.length() < 8 || input.length() > 8){
        cout << endl << "--INVALID INPUT: Not A Valid Number--";
        cout << endl << "[FORMAT: 00/00/0000]" << endl;
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
            cout << endl << "--INVALID INPUT: Cannot Contain Letters--" << endl;
            cout << endl << "[FORMAT: 00/00/0000]" << endl;
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
        cout << endl << "--INVALID INPUT: Month Does Not Exist--" << endl;
        cout << endl << "[FORMAT: 00/00/0000]" << endl;
        cout << "ENTER DATE OF BIRTH: ";
        cin >> input;
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
        cout << endl << "--INVALID INPUT: Date Does Not Exist--" << endl;
        cout << endl << "[FORMAT: 00/00/0000]" << endl;
        cout << "ENTER DATE OF BIRTH: ";
        cin >> input;
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
        cout << endl << "--INVALID INPUT: Year Does Not Exist--" << endl;
        cout << endl << "[FORMAT: 00/00/0000]" << endl;
        cout << "ENTER DATE OF BIRTH: ";
        cin >> input;
        delExtraChar(input);
        temp = input.substr(4, 4);
        year = stoi(temp);
    }
    return true;
}

bool validateUsername(string input){ //function that checks a Username for special characters
    int i;
    for (i = 0; i < input.length(); i++){
        if (isalnum(input[i]) == 0){
            cout << "--INVALID INPUT: No special characters allowed--" << endl;
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
        cout << "--File could not be opened--" << endl;
    }

    fileCredentials.close();
    while (i < credentials.size()){
        if (input == credentials[i]){
            fileCredentials.close();
            cout << "--INVALID INPUT: Username already exists--" << endl;
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
        cout << "--File could not be opened--" << endl;
        return false;
    }

    i = 0;
    while (i <= txtCredentials.size()){
        if (txtCredentials.empty()){
            cout << endl << "       --No Users Found, Please Register Account--";
            return false;
        }
        if (usernameInput == txtCredentials[i] && passwordInput == txtCredentials[i + 1]){
            return true;
            }
        i += 8;
    }
    return false;
}

string setUsername(){ //function that asks for user Username input
    string input;
    do{    
        cout << "ENTER USERNAME: ";
        getline(cin, input);
    }while (validateUsername(input) != 1 || usernameExists(input) != 1);
    return input;
}

string setPassword(){ //function that asks for user Password input
    string input;
    int i = 0;
    char c;
    cout << endl << "ENTER PASSWORD: ";
    getline(cin, input);
    return input;
}

string setFirstName(){ //function that asks for user First Name input
    string input;
    cout << endl << "ENTER FIRST NAME: ";
    cin >> input;
    return input;
}

string setLastName(){ //function that asks for user Last Name input
    string input;
    cout << endl << "ENTER LAST NAME: ";
    cin >> input;
    return input;
}

string setEmail(){ //function that asks for user Email input
    string input;
    bool findAt;
    cout << endl << "ENTER EMAIL: ";
    cin >> input;
    findAt = input.find('@') != string::npos;
    while (findAt == false){
        cout << endl << "EMAIL DOES NOT EXIST" << endl;
        cout << endl << "ENTER EMAIL: ";
        cin >> input;
        findAt = input.find('@') != string::npos;
    }
    return input;
}

bool phoneNumberCheck(string& input){
    int check = 0;
    if (input.length() < 10 || input.length() > 10){
        cout << endl << "INVALID INPUT: Not A Valid Number" << endl;
        return false;
    }
    for (int i = 0; i <= input.length(); i++){
        if (isalpha(input[i])){
            cout << endl << "INVALID INPUT: Cannot Contain Letters" << endl;
            return false;
        }
    }
    return true;
}

string setPhoneNumber(){ //function that asks for user Phone Number input
    string input, first3string, second3string, final4string, phoneIntReturn;
    int check = 0, check2 = 0;
    keyboardBuffer();
    cout << endl << "[FORMAT: 000 000 0000]";
    cout << endl << "ENTER PHONE NUMBER: ";
    getline(cin, input);
    delExtraChar(input);

    while (check != 1){
        check = 0;
        if (phoneNumberCheck(input)){
            check++;
        }
        else{
            cout << endl << "ENTER PHONE NUMBER: ";
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
    cout << endl << "--Please Enter Numerical Values for DOB--" << endl;
    cout << endl << "[FORMAT: 00/00/0000]" << endl;
    cout << "ENTER DATE OF BIRTH: ";
    getline(cin, input);
    delExtraChar(input);

    while(temp != 5){
        temp = 0;
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

void addUser(string userUsername, string userPassword, string userFirstName, string userLastName, string userEmail, string userPhoneNumber, string userDOB) {
    //function that inputs user information into a text file
    ofstream fileCredentials;

    fileCredentials.open("users.txt", ios::app);
    if (fileCredentials.is_open()){
        fileCredentials << userUsername << endl << userPassword << endl << userFirstName << endl << userLastName << endl << userEmail << endl << userPhoneNumber << endl << userDOB << "\n" << "\n";
        cout << endl << endl << "             --REGISTRATION COMPLETE--" << endl << endl << endl;
    }
    else{
        cout << "--File could not be opened--" << endl;
    }

    fileCredentials.close();
}

void setUserInformation(){ //function that calls functions to collect user information for registration
    string userUsername, userPassword, userFirstName, userLastName, userEmail, userDOB, userPhoneNumber;
    cout << endl << "                 --REGISTRATION--"<< endl;
    cout << "---------------------------------------------------" << endl << endl;
    userUsername = setUsername();
    userPassword = setPassword();
    userFirstName = setFirstName();
    userLastName = setLastName();
    userEmail = setEmail();
    userPhoneNumber = setPhoneNumber();
    userDOB = setDOB();

    addUser(userUsername, userPassword, userFirstName, userLastName, userEmail, userPhoneNumber, userDOB);
}

bool login(){ //function that accepts user input for Username and Password
    string usernameInput, passwordInput;
    cout << endl << "                    --LOGIN--" << endl;
    cout << "---------------------------------------------------" << endl << endl;
    cout << "ENTER USERNAME: ";
    cin >> usernameInput;
    cout << "ENTER PASSWORD: ";
    cin >> passwordInput;
    
    if (checkLogin(usernameInput, passwordInput)){
        cout << endl << endl << "               --LOGIN SUCCESSFUL--" << endl << endl;
        globalUsername = usernameInput;
        return true;
    }
    else{
        cout << endl << endl << "                  --LOGIN FAILED--" << endl << endl;
        return false;
    }
}

bool tryAgain(){ //function that is called after a failed attempt
    char choice;
    cout << "TRY ON MORE TIME? [Y/N]: ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        return true;
    }
    else{
        cout << "            --RETURNING TO MENU--" << endl;
        return false;
    }
}

bool usernameAndPasswordDisplay(){ //function that asks if 
    char choice;
    cout << endl << "Display Username and Password? [Y/N]: ";
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

void displayInformation(){ //function to display user information
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
        cout << "--File could not be opened--" << endl;

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
    cout << endl;
    cout << "FIRST NAME: " << txtCredentials[index + 2] << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "LAST NAME: " << txtCredentials[index + 3] << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "EMAIL: " << txtCredentials[index + 4] << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "PHONE NUMBER: " << txtCredentials[index + 5] << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "DATE OF BIRTH: " << txtCredentials[index + 6] << endl;
    this_thread::sleep_for(chrono::seconds(1));
    choice = usernameAndPasswordDisplay();
    if (choice){
        cout << endl;
        cout << "USERNAME: " << txtCredentials[index] << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "PASSWORD: " << txtCredentials[index + 1] << endl << endl;
        this_thread::sleep_for(chrono::seconds(1));
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
        cout << "--File could not be opened--" << endl;
    }
    if (txtCredentials.empty()){
        cout << endl << "      --File Is Empty, Please Register Account--" << endl << endl;
        return false;
    }
    fileCredentials.close();

    cout << endl << "         --CHANGE PASSWORD--" << endl;
    cout << "ENTER USERNAME: ";
    cin >> usernameInput;

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
        cout << endl << "USERNAME NOT FOUND" << endl << endl << endl << endl;
        return false;
    }

    cout << endl << "         --USERNAME FOUND--" << endl << endl;
    cout << "     --Names are case sensitive--" << endl;
    cout << "ENTER FIRST NAME: ";
    cin >> firstName;
    cout << "ENTER LAST NAME: ";
    cin >> lastName;
    cout << "ENTER EMAIL: ";
    cin >> email;
    
    if (firstName == txtCredentials[i + 2] && lastName == txtCredentials[i + 3] && email == txtCredentials[i + 4]){
        cout << endl << " --FIRST NAME, LAST NAME AND EMAIL MATCHES--" << endl << endl;
        cout << "ENTER NEW PASSWORD: ";
        cin >> newPassword;
    }
    else{
        cout << endl << "--First Name, Last Name, and email do not match--" << endl << endl << endl;
        return false;
    }

    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open ("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--" << endl;
        return false;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        if (i != passwordIndex){
            fileCredentialsWrite << txtCredentials[i] << endl;
        }
        else{
            fileCredentialsWrite << newPassword << endl;
        }
    }
    fileCredentialsWrite.close();
    cout << endl << endl << "        --PASSWORD CHANGED--" << endl << endl << endl;
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
        cout << "--File could not be opened--" << endl;
        return false;
    }
    fileCredentials.close();
    cout << endl << "         --CHANGE USERNAME--" << endl << endl;
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
        cout << endl << "USERNAME DOES NOT MATCH" << endl << endl << endl << endl;
        return false;
    }
    cout << endl << "         --USERNAME MATCHES--" << endl << endl;

    do{
        cout << "ENTER NEW USERNAME: ";
        getline(cin, newUsername);
    }while (validateUsername(newUsername) != 1 || usernameExists(newUsername) != 1);


    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--" << endl;
        return false;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        if (i != usernameIndex){
            fileCredentialsWrite << txtCredentials[i] << endl;
        }
        else{
            fileCredentialsWrite << newUsername << endl;
        }
    }
    fileCredentialsWrite.close();
    globalUsername = newUsername;
    cout << endl << endl << "        --USERNAME CHANGED--" << endl << endl << endl;
    return true;
}

bool changePhoneNumber(){ //function to change user Phone Number
    vector <string> txtCredentials;
    string usernameInput, newPhoneNumber, first3string, second3string, final4string, newPhoneWrite, line;
    int index, i = 0, check = 0;
    cout << endl << "     --CHANGE PHONE NUMBER--" << endl;
    cout << endl << "ENTER USERNAME: ";
    cin >> usernameInput;
    keyboardBuffer();
    if (usernameInput != globalUsername){
        cout << "USERNAME DOES NOT MATCH" << endl;
        return false;
    }
    cout << endl << "        --USERNAME MATCHES--" << endl;
    cout << endl << "[FORMAT: 000 000 0000]";
    cout << endl << "ENTER NEW PHONE NUMBER: ";
    getline (cin, newPhoneNumber);
    delExtraChar(newPhoneNumber);
    while (check != 1){
        check = 0;
        if (phoneNumberCheck(newPhoneNumber)){
            check++;
        }
        else{
            cout << endl << "ENTER PHONE NUMBER: ";
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
        cout << "--File could not be opened--" << endl;
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

    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--" << endl;
        return false;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        if (i != index){
            fileCredentialsWrite << txtCredentials[i] << endl;
        }
        else{
            fileCredentialsWrite << newPhoneWrite << endl;
        }
    }
    cout << endl << endl << "    --PHONE NUMBER CHANGED--" << endl << endl << endl;
    return true;
}

bool changeDOB(){ //function to change user DOB
    string DOBinput, month, date, year, DOB, usernameInput, line;
    vector <string> txtCredentials;
    int i = 0, temp = 0, index;
    cout << endl << "     --CHANGE PHONE NUMBER--" << endl;
    cout << endl << "ENTER USERNAME: ";
    cin >> usernameInput;
    keyboardBuffer();
    if (usernameInput != globalUsername){
        cout << "USERNAME DOES NOT MATCH" << endl;
        return false;
    }
    cout << "        --USERNAME MATCHES--" << endl << endl;
    cout << endl << "--Please Enter Numerical Values for DOB--" << endl;
    cout << endl << "[FORMAT: 00/00/0000]" << endl;
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
        cout << "--File could not be opened--" << endl;
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

    ofstream fileCredentialsWrite;
    fileCredentialsWrite.open("users.txt");
    if (fileCredentialsWrite.fail()){
        cout << "--File could not be opened--" << endl;
        return false;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        if (i != index){
            fileCredentialsWrite << txtCredentials[i] << endl;
        }
        else{
            fileCredentialsWrite << DOB << endl;
        }
    }
    cout << endl << endl << "   --DATE OF BIRTH CHANGED--" << endl << endl << endl;
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
        cout << "--File could not be opened--" << endl;
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
        cout << "--File could not be opened--" << endl;
        return;
    }
    for (i = 0; i < txtCredentials.size(); i++){
        fileCredentialsWrite << txtCredentials[i] << endl;
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

void loggedIntoSystem(){
    int input;
    do{
        cout << endl << "                  --SYSTEM MENU--"<< endl;
        cout << "---------------------------------------------------" << endl << endl;
        cout << "          1 --> Display Personal Information" << endl;
        cout << "          2 --> Change Username" << endl;
        cout << "          3 --> Change Password" << endl;
        cout << "          4 --> Change Phone Number" << endl;
        cout << "          5 --> Change DOB" << endl;
        cout << "          6 --> Delete Account" << endl;
        cout << "          7 --> Log Out" << endl << endl;
        input = loginSystemChoice();
        switch (input){
            case 1:{
                displayInformation(); //displays user information
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
                changePhoneNumberSystem(); //calls a function to change user Phone Number
                break;
            }
            case 5:{
                changeDOBSystem(); //calls a function to change user DOB
                break;
            }
            case 6:{
                deleteAccount();
                cout << endl << "                --ACCOUNT DELETED--" << endl << endl;
                return;
            }
            case 7:{
                cout << "               --ACCOUNT LOGGED OUT--" << endl;
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
        cout << "                   --LOGIN MENU--"<< endl;
        cout << "---------------------------------------------------" << endl << endl;
        cout << "             1 --> Account Registration" << endl;
        cout << "             2 --> Login" << endl;
        cout << "             3 --> Forget Password?" << endl;
        cout << "             4 --> End Program" << endl << endl << endl;

        input = mainSystemChoice();
        switch (input) {
            case 1:{
                setUserInformation(); //calls a function to register a user's information
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
                cout << endl << endl << "             PROGRAM SHUT DOWN" << endl;
                cout << "Thank you for using Jun's Personal Login Project!" << endl << endl;
            }
        }
    }while (input != 4);
    return 0;
}