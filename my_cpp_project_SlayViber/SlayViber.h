//
//#ifndef SLAYVIBER_H
//#define SLAYVIBER_H
//
//#include <iostream>
//#include <string>
//
//class SlayViber {
//private: 
//	std::string name;
//public:
//	void function();
//};
//
//#endif
#ifndef SLAYVIBER_H
#define SLAYVIBER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class  SlayViber {
private:
    std::string username;
    std::string password;
    bool streaming;
    int followers;
    bool isRegistered;
    bool hasRestriction;
    std::vector<std::string> visitors;
public:
    static int userCount; //რეგისტრირებულ მომხმარებლების რაოდენობას ითვლის
    static const int MaxUsers = 100;//მომხმარებლების მაქსიმალური რაოდენობა
    static SlayViber users[MaxUsers];//სტატიკური ობიექტების მასივი რომელიც ინახავს ყველა რეკისტრირებულ მომხმარებელს
    int userChoice(const std::string&, const std::string&, const std::string&) const; //ყეველა საჯირო არჩევანს გააკეთებს მომხმარებული ამ ფუნქციის საშუალებით, მას აქვს ერთი ნაგულისხმევი პარამეტრი text3.
    //უპარამეტრო კონსტრუქტორი (default constructor), რომელიც ქმნის არარეგისტრირებულ მომხმარებელს. 
    SlayViber();
    //	პარამეტრიანი კონსტრუქტორი, რომელსაც გადასცემთ მნიშვნელობებს იმისათვის, რომ განსაზღვროთ ობიექტის username, password, followers (გაჩუმების პრინციპით მნიშვნელობით 0),  hasRestriction 
    //(გაჩუმების პრინციპით მნიშვნელობით false).
    SlayViber(std::string username, std::string password, bool streaming = false, int followers = 0, bool isRegistered = false, bool hasRestriction = false);

    ~SlayViber() = default;

    bool registration(); //ფუნქცია registration, რომელსაც გამოიძახებს კლასის არარეგისტრირებული ობიექტი და დაარეგისტრირებს ამ მომხმარებელს (ინტერაქციულ რეჟიმში). (მე ცოტა გასხვავებულად დავწერე რომ უფო დეტალური იყოს)

    bool isUsernameAlreadyTaken(const std::string&); //შეამოწმებს არის თუ არა username როდესმე გამოყენებული

    bool isAlreadyTaken(const std::string&, const std::string&); //შეამოწმებს არის თუ არა username და  password როდესმე გამოყენებული, ანუ მომხმარებელი მართლა რეგისტრირებულია თუ არა

    std::string get_Name()const;  //გეთერ ფუნქცია აბრუნებს username-ს, რადგან ის private ველში არ არის

    int get_f()const;  //გეთერ ფუნქცია აბრუნებს followers-ს, რადგან ის private ველში არ არის

    void set_followers(int);  //სეტერ ფუნქცია მნიშვნელობას ანიჯებს followers - ს, რადგან ის private ველში არ არის

    std::string get_password()const;  //გეთერ ფუნქცია აბრუნებს password - ს, რადგან ის private ველში არ არის

    void print()const; //ფუნქცია print, რომელიც გამოიტანს ინფორმაციას მომხმარებლის შესახებ ორგანიზებული ფორმით. 

    bool visit(SlayViber&); //ფუნქცია visit, რომელსაც იძახებს კლასის ობიექტი და პარამეტრად იღებს კლასის სხვა ობიექტს, ფუნქცია გამოიტანს მონახულებული მომხმარებლის შესახებ ინფორმაციას შეზღუდულ ფორმატში
    //ასევე, მომნახულებელმა მომხმარებელმა უნდა გადაწყვიტოს სურს თუ არა მონახულებული მომხმარებლის გამოწერა
    static void listAllUsers(); //ფუნქცია რომელის ეკრანზე ამობეჯდავს ყველა რეგისტრირებულ მომხმარებლის სახელს

    void seeVisitors()const; // მეთოდი(მემბერ ფუნქცია, ფუნქცია) ეკრანზე ამობეჯდავს ყველა  მომხმარებლის სახელს რომელიც შევიდა ობიექტის ფროპილზე

    void goLive();//ფუნქცია goLive, რომელსაც გამოიძახებს ობიექტი და ობიექტს განესაზღვროს Streaming – true. ფუნქციის მუშაობისას მომხმარებელის ან მოემატოს (5% -დან 40% მდე ) ან დააკლდეს ( 0% - დან 30% ) გამომწრების რაოდენობა შემთხვევითი პრინციპით. იმ შემთხვევაში, თუ მომხმარებელს დააკლდა გამომწერების 25% ზე მეტი, პლატფორმამ მომხმარებელი სავარაუდო წესების დარღვევის გამო შეზღუდავს დაუყოვნებლივ (hasRestriction – true) და გათიშავს ლაივიდან (Streaming – false).  
};
void listAndFollowUsers(SlayViber&); //ფუნქცია რომელის ეკრანზე ამობეჯდავს ყველა რეგისტრირებულ მომხმარებლის სახელს და მომხმარებელი ასევე აირჩევს ერთ მათგანს და დააფოლოვებს
int CorrectChoice();//მომხმარებელმა არ უნდა შეიტანოს 1/2/3/4/5/6-ს გარეშე მონაცემი
 //ჩემი კომპაილერი ამ კოდის ფრაგმენტის გარეშე არ მუშაობს
#endif
