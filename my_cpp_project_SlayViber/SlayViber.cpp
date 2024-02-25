//#include "SlayViber.h";
//#include <iostream>
//
//void SlayViber::function() {
//	std::cout << "It work!" << std::endl;
//}
#include "SlayViber.h"
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

int SlayViber::userCount = 0;
SlayViber SlayViber::users[SlayViber::MaxUsers];

int SlayViber::userChoice(const string& text1, const string& text2, const string& text3 = "") const { //ყეველა საჯირო არჩევანს გააკეთებს მომხმარებული ამ ფუნქციის საშუალებით, მას აქვს ერთი ნაგულისხმევი პარამეტრი text3.
    int choice;
    bool isValid = true;
    while (true) {
        if (isValid) {
            cout << "Select an operation:\n1. " << text1 << "\n2. " << text2;
            if (!text3.empty()) { //თუ text3 ცარიელი არ არის, ფუნქცია ამატებს მესამე არჩევანს
                cout << "\n3. " << text3;
            }
            cout << "\nEnter your choice (1/2";
            if (!text3.empty()) {
                cout << "/3"; //თუ text3 ცარიელი არ არის, ფუნქცია ამატებს მესამე არჩევანის შერჩევის შესაძლებლობას აღვნიშნულ ტექსტს
            }
            cout << "): ";
            cin >> choice;
        }
        else {
            cin.clear(); //გაათავისუფლებს cin-ს
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error, try again: Please enter 1";
            if (!text3.empty()) {//დამატებითი ტექსტის დამატება text3 არა ცარიელობის შემთხვევაში
                cout << "/2/3";
            }
            cout << ": ";
            cin >> choice;
            isValid = true;
        }

        if (choice >= 1 && choice <= (text3.empty() ? 2 : 3)) { //text3 თუ ცარიელი იქნება მაშინ არსებობს ორი შემთხვევა 1 ან 2, თუ არა მაშინ არსებობს 3 შემთხვევა
            return choice; //დააბრუნე choice(მომხმარებლის არჩევანი)
        }
        else {
            cout << "Error: ";
            isValid = false; //isValid იყებს false-ს და ციგლი გრძელდება სანამ მომხმარებელი სასურველ მონაცემს შეიყვანს
        }
    }
}

SlayViber::SlayViber() {
    this->username = "user000" + to_string(userCount); //default მომხმარებლის სახელი
    isRegistered = false; //არც საჯირო მაგრამ ზოგ შემთხვევისთვის მაინჩ დავწეროთ
}

SlayViber::SlayViber(string username, string password, bool streaming, int followers, bool isRegistered, bool hasRestriction) {
    this->username = username;
    this->password = password;
    this->streaming = streaming;
    this->followers = followers;
    this->isRegistered = isRegistered;
    this->hasRestriction = hasRestriction;
    userCount++;
    if (username.empty() && password.empty()) {//თუ username და password ველები ცარიელია მაშინ
        isRegistered = false;//რეგისტრირებული არ არის
    }
    else {
        isRegistered = true;//რეგისტრირებულია
        users[userCount - 1] = *this;// დაამატე რეგისტრირებული მომხმარებლების სიაში ობიექტი
    }
}

bool SlayViber::registration() {
    cout << "Welcome to our application. Please indicate whether you want to create an account or not." << endl;
    int choice = userChoice("Log in", "Sign up", "Continue without register");

    if (choice == 1) { //Log in-?
        string usernameT, passwordT;
        int attempts = 0; //ცდების რაოდენობა

        while (attempts < 3) { //თუ attempts 3ზე მეტი იქნება ციკლი მთავრდება
            cout << "Please enter your username and password: " << endl;
            cout << "Username: ";
            cin >> usernameT;
            cout << "Password: ";
            cin >> passwordT;
            //არის თუ არა რეგისტრირებული ობიექტი შემოტანილი მონაცემებით
            if (isAlreadyTaken(passwordT, usernameT)) {
                cout << "Welcome!" << endl;
                return true;
            }
            else {
                cout << "Username or Password is not correct. Do you want to try again?" << endl;
                int choice2 = userChoice("Yes", "Continue without registration");
                if (choice2 == 2) {
                    cout << "You are continuing to use the application without registering!\n";
                    return true; //ფუნცია მთავრდება
                    isRegistered = false; //მაგრამ მომხმრებლის რეგისტრაციის გარეშე
                }
                attempts++;
            }
        }
        if (attempts == 3) {//თუ ცდების რაოდენობა 3-ი ტოლი იქნება(attempts =0 იყო თავდაირველად)
            cout << "You need to wait for a while because there have been too many attempts." << endl;
            isRegistered = false;
            return false; //ფუნქცია აბრუნებს false-ს და მთავრდება
        }
    }

    if (choice == 2) {//Sign up
        bool isUsernameTaken = true;

        while (isUsernameTaken) {
            cout << "Enter a unique username: ";
            cin >> username;

            // არის თუ არა მომხმარებლის სხელი გამოყენებული
            isUsernameTaken = isUsernameAlreadyTaken(username);

            if (isUsernameTaken) {
                cout << "This username is already taken. Please choose a different one." << endl;
            }
        }

        cout << "Enter password: ";
        cin >> password; //პაროლის უნიკალურობა არაა საჯირო:]
        cout << "Congratulations, you have successfully registered. Thank you for choosing to use the application." << endl;
        isRegistered = true;
    }
    if (choice == 3) {// თუ არ სურს ანგარიშის შექმნას
        this->isRegistered = false;
        return true;
    }

}

bool SlayViber::isUsernameAlreadyTaken(const string& newUsername) {
    //გამოყენებულია მომხმარებლის სახელი?
    for (int i = 0; i < SlayViber::userCount; ++i) {
        if (SlayViber::users[i].get_Name() == newUsername) {//პირობა
            return true; // კი
        }
    }
    return false; // არა
}

bool SlayViber::isAlreadyTaken(const string& Password, const string& Username) {
    // შეამოწმებს ყველა მომხმარებლის და გეტყვის არის თუ არა Password და Username უნიკალური
    for (int i = 0; i < SlayViber::userCount; ++i) {
        if (SlayViber::users[i].get_password() == Password && SlayViber::users[i].get_Name() == Username) {
            return true; // Password და Username გამოყენებულია
        }
    }
    return false; //  Password და Username არ გამოყენებულია 
}

string SlayViber::get_Name()const {
    return username;
}

int SlayViber::get_f()const {
    return followers;
}

void SlayViber::set_followers(int f) {
    this->followers = f;
}

string SlayViber::get_password()const {
    return password;
}

void SlayViber::print()const {
    if (isRegistered) {//თუ მომხმარებელი რეგისტრირებულია
        cout << "User registered: \n";
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Followers: " << followers << endl;
        hasRestriction ? cout << "Has restriction.\n" : cout << "Has not restriction.\n";
    }
    else {//თუ მომხმარებელი არ არის რეგისტრირებულია
        cout << "User not registered: \n";
        cout << "Username: " << username << endl;
    }
}

bool SlayViber::visit(SlayViber& s) {
    cout << "username: " << s.get_Name() << endl;


    cout << "Do you wont to follow this user? \n";
    s.visitors.push_back(username); //visitors-ად დაამატე ვექტორს
    if (isRegistered) { //თუ რეგისტრირებულია

        int choice = userChoice("Yes", "No");
        if (choice == 1) {//დააპოლოვე
            if (this->username == s.username) {//საკუთარ თავს ვერ დააპოლოვებს
                cout << "You cannot follow yourself." << endl;
                return false;
            }
            s.followers++;//პოლოვერების რაოდენობა გაიზარდე თუ უნდა გადმოწერა მომხმარებელს
            cout << "You have started following the user " << s.get_Name() << endl;
        }
    }
    else {//თუ მომხმარებელი რეგისტრირებული არ არის ვერ დააპოლოვებს 
        cout << "To follow a user, you need to create an account. Do you want to create an account?\n";

        if (userChoice("Yes", "No") == 1) {
            registration();
            s.followers++;
            cout << "You have started following the user " << s.get_Name() << endl;
        }
    }

}

void SlayViber::listAllUsers() {
    cout << "List of all users:\n";
    for (int i = 0; i < userCount; ++i) {
        cout << "User " << i + 1 << ": " << users[i].get_Name() << endl;
    }
}

void SlayViber::seeVisitors()const { //ვინ შევიდა მომხმარებლის პროფილზე
    for (string i : visitors) {
        if (i.empty()) {
            cout << "user not found:(\n"; //არავინ:(
            break;
        }
        else { cout << i << ", "; }
    }
    cout << endl;
}

void SlayViber::goLive() {
    if (hasRestriction) { cout << "You cannot start a live broadcast, You have restriction"; }
    if (isRegistered && !hasRestriction) {//თუ რეგისტრირებულია და შეზღუდვა არ აქვს 
        streaming = true;
        srand(time(NULL));

        int initialFollowers = followers; // თავდაპირველი გამოწერების რაოდენობა
        while (streaming) {//მომხმარებელი სანამ სურს დამთავრება ლაივის მანამდე იმუშავებს
            // ან დააკლე ან გაიზარდე გადმოწერები
            int randomChoice = rand() % 2 + 1;


            if (randomChoice == 1) {
                int minFollowersIncrease = followers * 5 / 100;//5% დან
                int maxFollowersIncrease = followers * 40 / 100;//40 პროცენდამდე შეიძლება გაიზარდოს
                int followersIncrease = rand() % (maxFollowersIncrease - minFollowersIncrease + 1) + minFollowersIncrease; //გაიზარდე რანდომ მნიშვნელობით
                followers += followersIncrease;
            }
            else {
                int maxFollowersDecrease = followers * 30 / 100; //დააკლე 0% დან 30%დამდე
                int followersDecrease = rand() % (maxFollowersDecrease + 1);
                followers -= followersDecrease;
            }

            cout << "Streaming status: " << (streaming ? "Live" : "Offline") << endl;
            cout << "Followers: " << followers << endl;

            //თუ მომხმარებელს დააკლდა გამომწერების 25% ზე მეტი, პლატფორმამ მომხმარებელი სავარაუდო წესების დარღვევის გამო შეზღუდოს დაუყოვნებლივ (hasRestriction – true) და გათიშოს ლაივიდან (Streaming – false).  
            if (followers < 0.75 * initialFollowers) {
                hasRestriction = true;
                streaming = false; // დაამთავრე ლაივი
                cout << "Broadcast has been restricted due to significant follower loss." << endl;
                break;
            }

            int choice = userChoice("Press to stop streaming :", "Continue");
            if (choice == 1) {
                streaming = false;
            }
        }
    }
    if (isRegistered == false) { cout << "You cannot start a live broadcast without registering.\n"; }

}

void listAndFollowUsers(SlayViber& currentUser) {
    // ყველა მომხმარებლის სია
    SlayViber::listAllUsers();

    //გინდა თუ არა მომხმარებელს გადმოწერა
    cout << "Enter the username of the user you want to follow: ";
    string usernameToFollow;
    cin >> usernameToFollow;//სახელი სასურველ ადამიანს

    // თუ ვერ იპოვა მომხმარებელი
    bool userFound = false;
    for (int i = 0; i < SlayViber::userCount; ++i) {
        if (SlayViber::users[i].get_Name() == usernameToFollow) {
            //გადმოწერის პროცესი
            currentUser.visit(SlayViber::users[i]);
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        cout << "User not found. Please enter a valid username.\n";
    }
}

int CorrectChoice() { //ყეველა საჯირო არჩევანს გააკეთებს მომხმარებული ამ ფუნქციის საშუალებით, მას აქვს ერთი ნაგულისხმევი პარამეტრი text3.
    int choice;
    bool isValid = true;
    while (true) {
        if (isValid) {
            cin >> choice;
        }
        else {
            cin.clear(); //გაათავისუფლებს cin-ს
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error, try again: Please enter";

            cout << ": ";
            cin >> choice;
            isValid = true;
        }

        if (choice >= 1 && choice <= 6) { //text3 თუ ცარიელი იქნება მაშინ არსებობს ორი შემთხვევა 1 ან 2, თუ არა მაშინ არსებობს 3 შემთხვევა
            return choice; //დააბრუნე choice(მომხმარებლის არჩევანი)
        }
        else {
            cout << "Error: ";
            isValid = false;
        }
    }
}
