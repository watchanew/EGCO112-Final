#include "battle.h"
#include <chrono>
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

int main() {
  string c;
  int b;
  do {
    int menu;
    system("clear"); // clear screen
    openwindow();
    cout << "--> 1 START GAME <--" << endl;
    cout << "--> 2 HOW TO PLAY <--" << endl;
    cout << "--> 3 ABOUT US <--" << endl;
    cout << "--> 4 EXIT <--" << endl;
    cout << "=======================" << endl;
    b = 0;
    try {
      cin >> menu;
      if (cin.fail())
        throw "Invalid input";
      if (menu > 4 || menu < 1)
        throw "Wrong number please try again";
    } catch (int e) {
      cout << e << endl;
      cin.clear();
      cin.ignore(50, '\n');
      sleep_for(seconds(1));
      system("clear");
      b = 1;
    } catch (const char *e) {
      cout << e << endl;
      cin.clear();
      cin.ignore(50, '\n');
      sleep_for(seconds(2));
      system("clear");
      b = 1;
    }
    switch (menu) {
    case 1:
      if (stage1_battle() == 1) {
        sleep_for(seconds(2));
        system("clear");
        cout << "==================== STAGE CLEAR =====================" << endl
             << endl;
        sleep_for(seconds(2));
        if (stage2_battle() == 1) {
          sleep_for(seconds(2));
          system("clear");
          cout << "==================== STAGE CLEAR ====================="
               << endl
               << endl;
          sleep_for(seconds(2));
          if (stage3_battle() == 1) {
            sleep_for(seconds(2));
            system("clear");
            cout << "==================== STAGE CLEAR ====================="
                 << endl
                 << endl;
            sleep_for(seconds(2));
            if (stage4_battle() == 1) {
              sleep_for(seconds(2));
              system("clear");
              cout << "==================== STAGE CLEAR ====================="
                   << endl
                   << endl;
              sleep_for(seconds(2));
              if (stage5_battle() == 1) {
                sleep_for(seconds(2));
                system("clear");
                cout << "==================== STAGE CLEAR "
                        "====================="
                     << endl
                     << endl;
                sleep_for(seconds(2));
                cout << end() << endl;
                system("clear");
                cout << endcredit() << endl;
              } else {
                sleep_for(seconds(2));
                cout << "Return to menu" << endl;
                sleep_for(seconds(3));
                system("clear");
              }
            } else {
              sleep_for(seconds(2));
              cout << "Return to menu" << endl;
              sleep_for(seconds(3));
              system("clear");
            }
          } else {
            sleep_for(seconds(2));
            cout << "Return to menu" << endl;
            sleep_for(seconds(3));
            system("clear");
          }
        } else {
          sleep_for(seconds(2));
          cout << "Return to menu" << endl;
          sleep_for(seconds(3));
          system("clear");
        }
      } else {
        sleep_for(seconds(2));
        cout << "Return to menu" << endl;
        sleep_for(seconds(3));
        system("clear");
      }

    case 2:
      cout << "how to play .." << endl;
      cout << "1. Choose the enemy you want to attack" << endl;
      cout << "2. Choose Skill" << endl;
      cout << "3. Let's play it" << endl;
      cout << endl << "Press anything to return to menu" << endl;
      cin >> c;
      break;
    case 3:
      cout << "About Us.." << endl;
      cout << "6413110" << endl;
      cout << "6413112" << endl;
      cout << "6413210" << endl;
      cout << "6413223" << endl;
      cout << endl << "Press anything to return to menu" << endl;
      cin >> c;
      break;
    case 4:
      exit(0);
      break;
    }
  } while (b == 0);
  return 0;
}