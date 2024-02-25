//#include "SlayViber.h"
//#include <iostream>
//using namespace std;
//
//int main() {
//	SlayViber test;
//	test.function();
//}
#include "SlayViber.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


int main() {
    SlayViber user2("Giorgi", "Abuladze1", false, 120);
    SlayViber user3("John", "Abuladze2", false, 500);
    SlayViber k;
    k.set_followers(100);
    cout << "*************************\n";
    cout << "          TikTok         \n";
    cout << "*************************\n";
    if (k.registration() == false) {
        return 0;
    }

    /*
    k.visit(user2);
    cout << user2.get_f() << endl;
    user2.seeVisitors();*/
    cout << "Find new friends! \n";

    while (true) {
        cout << "Enter operation:\n";
        cout << "1. Find new friends.\n";
        cout << "2. See who visited your profile.\n";
        cout << "3. See your data.\n";
        cout << "4. List all users.\n";
        cout << "5. GO live.\n";
        cout << "6. Exit program.\n";

        int choice = CorrectChoice();

        if (choice == 1) {
            listAndFollowUsers(k);
        }
        else if (choice == 2) {
            k.seeVisitors();
        }
        else if (choice == 3) {
            k.print();
        }
        else if (choice == 4) {
            SlayViber::listAllUsers();
        }
        else if (choice == 5) {
            k.goLive();
        }
        else if (choice == 6) { break; }
        else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
