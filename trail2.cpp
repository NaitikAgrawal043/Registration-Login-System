#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Login
{
private:
    string LoginId, Password, SecurityQuestion, SecurityAnswer;

public:
    Login()
    {
        LoginId = "";
        Password = "";
        SecurityQuestion = "";
        SecurityAnswer = "";
    }

    void setId(string Id) { LoginId = Id; }
    void setPassword(string pw) { Password = pw; }
    void setSecurityQuestion(string question) { SecurityQuestion = question; }
    void setSecurityAnswer(string answer) { SecurityAnswer = answer; }

    string getId() { return LoginId; }
    string getPassword() { return Password; }
    string getSecurityQuestion() { return SecurityQuestion; }
    string getSecurityAnswer() { return SecurityAnswer; }
};

void registration(Login &l)
{
    system("cls");
    string Id, PassWord, question, answer;

    cout << "\tEnter Login Id: ";
    cin >> Id;
    l.setId(Id);

start:
    cout << "\tEnter a strong password (minimum 8 characters): ";
    cin >> PassWord;
    if (PassWord.length() < 8)
    {
        cout << "\tPassword must have at least 8 characters. Try again." << endl;
        goto start;
    }
    l.setPassword(PassWord);

    cout << "\tSet a security question (e.g., What is your favorite color? withoot space, use underscores): ";
    cin.ignore();
    getline(cin, question);
    l.setSecurityQuestion(question);

    cout << "\tSet the answer to your security question: ";
    getline(cin, answer);
    l.setSecurityAnswer(answer);

    ofstream outfile("login.txt", ios::app);
    if (!outfile)
    {
        cout << "\tError: Unable to open file!" << endl;
    }
    else
    {
        outfile << l.getId() << " " << l.getPassword() << " " << l.getSecurityQuestion() << " " << l.getSecurityAnswer() << endl;
        cout << "\tUser Registered Successfully!" << endl;
    }
    outfile.close();

    Sleep(3000);
}

void login(Login &l)
{
    system("cls");
    string Id, PassWord;
    cout << "\tEnter Login Id: ";
    cin >> Id;
    cout << "\tEnter Password: ";
    cin >> PassWord;

    ifstream infile("login.txt");
    if (!infile)
    {
        cout << "\tError: Unable to open file!" << endl;
    }
    else
    {
        string line;
        bool found = false;
        while (getline(infile, line))
        {
            stringstream ss(line);
            string userId, userPW, question, answer;
            ss >> userId >> userPW >> ws;
            getline(ss, question, ' ');
            getline(ss, answer);

            if (Id == userId && PassWord == userPW)
            {
                found = true;
                cout << "\tPlease Wait..." << endl;
                Sleep(1500);
                system("cls");
                cout << "\tWelcome to your dashboard, " << userId << "!" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "\tError: Incorrect Login Id or Password!" << endl;
        }
        infile.close();
    }
    Sleep(3000);
}

void forgotPassword(Login &l)
{
    system("cls");
    string Id, answer;
    cout << "\tEnter your Login Id: ";
    cin >> Id;

    ifstream infile("login.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile)
    {
        cout << "\tError: Unable to open file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line))
    {
        stringstream ss(line);
        string userId, userPW, question, correctAnswer;
        ss >> userId >> userPW >> ws;
        getline(ss, question, ' ');
        getline(ss, correctAnswer);

        if (Id == userId)
        {
            found = true;
            cout << "\tSecurity Question: " << question << endl;
            cout << "\tEnter your answer: ";
            cin.ignore();
            getline(cin, answer);

            if (answer == correctAnswer)
            {
                string newPassword;
            newPass:
                cout << "\tEnter a new password (minimum 8 characters): ";
                cin >> newPassword;
                if (newPassword.length() < 8)
                {
                    cout << "\tPassword must have at least 8 characters. Try again." << endl;
                    goto newPass;
                }
                userPW = newPassword; // Update the password
                cout << "\tPassword reset successful!" << endl;
            }
            else
            {
                cout << "\tError: Incorrect answer to the security question!" << endl;
            }
        }
        // Write the updated or unchanged user data back to the temp file
        tempFile << userId << " " << userPW << " " << question << " " << correctAnswer << endl;
    }

    infile.close();
    tempFile.close();

    // Replace the original file with the updated file
    remove("login.txt");
    rename("temp.txt", "login.txt");

    if (!found)
    {
        cout << "\tError: Login Id not found!" << endl;
    }

    Sleep(3000);
}


int main()
{
    Login l;

    while (true)
    {
        system("cls");
        int choice;
        cout << "\tWelcome to Registration and Login System" << endl;
        cout << "\t1. Register" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t3. Forgot Password" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registration(l);
            break;
        case 2:
            login(l);
            break;
        case 3:
            forgotPassword(l);
            break;
        case 4:
            cout << "\tGoodbye!" << endl;
            return 0;
        default:
            cout << "\tInvalid choice! Try again." << endl;
        }
        Sleep(3000);
    }
}
