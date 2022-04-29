#include "character.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

class screen {
private:
  string free = "               ";
  string stage;
  string wave = "               ";
  string turn[2];
  string po1[6] = {"               ", "               ", "               ",
                   "               ", "               ", "               "};
  string po2[6] = {"               ", "               ", "               ",
                   "               ", "               ", "                        "};
  string po3[6] = {"               ", "               ", "               ",
                   "               ", "               ", "                           "};
  string po_1[6] = {"               ", "               ", "               ",
                    "               ", "               ", "               "};
  string po_2[6] = {"               ", "               ", "               ",
                    "               ", "               ", "               "};
  string po_3[6] = {"               ", "               ", "               ",
                    "               ", "               ", "               "};
  string battledata[10];

public:
  screen();
  void receive(int, string *);
  void receive_data(NODE *);
  void show();
  void reset();
  void shake(NODE *);
  void attack(NODE *);
  void skill(NODE *);
  void getstage(string);
  void getwave(string);
  void getturn(string, string);
  ~screen();
};

screen::screen() {}
screen::~screen() {}

void screen::receive(int po, string *A) {
  switch (po) {
  case 1:
    for (int i = 0; i < 5; i++) {
      po1[i] = *(A + i);
    }
    break;
  case 2:
    for (int i = 0; i < 5; i++) {
      po2[i] = *(A + i);
    }
    break;
  case 3:
    for (int i = 0; i < 5; i++) {
      po3[i] = *(A + i);
    }
    break;
  case -1:
    for (int i = 0; i < 5; i++) {
      po_1[i] = *(A + i);
    }
    break;
  case -2:
    for (int i = 0; i < 5; i++) {
      po_2[i] = *(A + i);
    }
    break;
  case -3:
    for (int i = 0; i < 5; i++) {
      po_3[i] = *(A + i);
    }
    break;
  };
}

void screen::receive_data(NODE *t) {
  int po = t->getpo();
  switch (po) {
  case 1:
    po1[5] = t->getstat();
    break;
  case 2:
    po2[5] = t->getstat();
    break;
  case 3:
    po3[5] = t->getstat();
    break;
  case -1:
    po_1[5] = t->getstat();
    break;
  case -2:
    po_2[5] = t->getstat();
    break;
  case -3:
    po_3[5] = t->getstat();
    break;
  }
}

void screen::shake(NODE *t) {
  int po = t->getpo();
  sleep_for(milliseconds(350));
  this->receive(po, t->getshake());
  this->receive_data(t);
  this->show();
  sleep_for(milliseconds(450));
  this->receive(po, t->getnormal());
  this->show();
}

void screen::attack(NODE *t) {
  int po = t->getpo();
  this->receive(po, t->getattack_1());
  this->receive_data(t);
  this->show();
  sleep_for(milliseconds(250));
  this->receive(po, t->getattack_2());
  this->show();
  sleep_for(milliseconds(650));
  this->receive(po, t->getnormal());
  this->show();
}

void screen::skill(NODE *t) {
  int po = t->getpo();
  this->receive(po, t->getskill());
  this->receive_data(t);
  this->show();
  sleep_for(milliseconds(1000));
  this->receive(po, t->getnormal());
  this->show();
}

void screen::getstage(string a){
  stage = "======================== "+ a +" =========================";
}

void screen::getwave(string a){
  wave = "                          "+ a +"                          ";
}

void screen::getturn(string a, string b){
  turn[0] = "======================== "+ a +" =========================";
  turn[1] = "                       "+ b +"                        ";
}

void screen::show() {
  system("clear");
  cout << stage << endl << wave << endl;
  for (int i = 0; i < 6; i++) {
    if (i == 5) {
      cout << po1[i] << "      " << po_1[i] << endl;
    } else {
      cout << po1[i] << free << po_1[i] << endl;
    }
  }
  for (int i = 0; i < 6; i++) {
    if (i == 5) {
      cout << po2[i] << "      " << po_2[i] << endl;
    } else {
      cout << po2[i] << free << po_2[i] << endl;
    }
  }
  for (int i = 0; i < 6; i++) {
    if (i == 5) {
      cout << po3[i] << "   " << po_3[i] << endl;
    } else {
      cout << po3[i] << free << po_3[i] << endl;
    }
  }
  cout << endl << turn[0] << endl << turn[1] << endl<< endl;
}