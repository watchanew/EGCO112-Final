#include "screen.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <time.h>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

class LL {
  NODE *hol;
  int size;

public:
  void add_node(NODE *&);
  void show_all();
  void show_name();
  void attacked(int, int, screen *);
  void all_attacked(int, screen *);
  void healed(int, int, screen *);
  void checkdeath(screen *);
  int getsize();
  string getname();
  NODE *gethol();
  void robotaction(LL *, screen *, LL *);
  void enemyaction(LL *, screen *);
  void robotscreen(screen *);
  void enemyscreen(screen *);
  void datascreen(screen *);
  void clear();
  ~LL();
  LL();
};

void LL::robotscreen(screen *S) {
  NODE *t = hol;
  int i;
  for (i = 0; i < size; i++) {
    t->setpo(i + 1);
    S->receive(t->getpo(), t->getnormal());
    S->receive_data(t);
    t = t->move_next();
  }
  S->show();
}

void LL::enemyscreen(screen *S) {
  NODE *t = hol;
  int i;
  for (i = 0; i < size; i++) {
    t->setpo(-(i + 1));
    S->receive(t->getpo(), t->getnormal());
    S->receive_data(t);
    t = t->move_next();
  }
  S->show();
}

void LL::datascreen(screen *S) {
  NODE *t = hol;
  int i;
  for (i = 0; i < size; i++) {
    S->receive_data(t);
    t = t->move_next();
  }
  S->show();
}

string LL::getname() {
  NODE *t = hol;
  return t->getname();
}

void LL::enemyaction(LL *R, screen *M) {
  sleep_for(milliseconds(1500));
  M->show();
  if (size == 0) {
    cout << "All enemy dead." << endl;
  } else if (R->size == 0) {
  } else {
    NODE *t = hol;
    int i;
    for (i = 0; i < size; i++) {
      if (R->size > 0) {
        sleep_for(seconds(1));
        srand(time(NULL));
        int robotnum = rand() % R->size + 1;
        int action = 1;
        M->attack(t);
        cout << t->getname() << " attack!!!" << endl;
        sleep_for(seconds(1));
        R->attacked(robotnum, t->attack(), M);
        if (t->move_next() != NULL) {
          t = t->move_next();
        }
        R->checkdeath(M);
      }
    }
  }
  cout << endl << "END TURN" << endl;
  sleep_for(seconds(2));
}

void LL::robotaction(LL *A, screen *M, LL *R) {
  M->show();
  sleep_for(milliseconds(1500));
  NODE *t = hol;
  int i, k, a;
  for (i = 0; i < size; i++) {
    M->receive_data(t);
    M->show();
    t->changecd_1(-1); //ทุกเทิร์น คูลดาวน์ลดอัตโนมัต
    k = 0;
    if (A->getsize() == 0) {
      cout << "no enemy left." << endl;
      t->renew_energy();
      M->receive(t->getpo(), t->getreenergy());
      M->show();
      sleep_for(seconds(1));
      M->receive(t->getpo(), t->getnormal());
      M->show();
    } else {
      cout << t->getname() << endl;
      sleep_for(milliseconds(500));
      if (t->geten() <= 0) {
        cout << "Wait for next turn, Energy isn't enough." << endl;
        t->renew_energy();
        M->receive(t->getpo(), t->getreenergy());
        M->show();
        sleep_for(seconds(1));
        M->receive(t->getpo(), t->getnormal());
        M->show();
      } else {
        int RA = 0;
        do {
          a = 0;
          try {
            t->RobotAction();
            cout << "Input: ";
            cin >> RA;
            if (cin.fail())
              throw 4;
            if (RA > 2 || RA < 0)
              throw "input choose be more or equal to 0 and less or equal to 2";
            if (RA == 2 && t->getcd_1() > 0) {
              cout << "This skill is not ready.\nWait " << t->getcd_1()
                   << " turn.";
              throw " ";
            }
            if (RA == 2 && t->geten() < 3) {
              throw "Energy isn't enough.";
            }

          } catch (int e) {
            cout << "Invalid input " << endl;
            cin.clear();
            cin.ignore(50, '\n');
            sleep_for(seconds(1));
            system("clear");
            M->show();
            a = 1;
          } catch (const char *e) {
            cin.clear();
            cin.ignore(50, '\n');
            cout << e << endl;
            sleep_for(seconds(2));
            system("clear");
            M->show();
            a = 1;
          }
        } while (a);

        switch (RA) {
        case 0:
          t->renew_energy();
          M->receive(t->getpo(), t->getreenergy());
          M->show();
          sleep_for(seconds(1));
          M->receive(t->getpo(), t->getnormal());
          M->show();
          break;
        case 1:
          int choose;
          do { // ---> exception
            cout << "Choose enemy" << endl;
            A->show_all();
            cout << "Input: ";
            a = 0;
            try {
              cin >> choose;
              if (cin.fail())
                throw 4;
              if (choose > A->getsize() || choose <= 0)
                throw "input choose be more than 0 and less or equal to ";

            } catch (int e) {
              cout << "Input choose be integer" << endl;
              cin.clear();
              cin.ignore(50, '\n');
              sleep_for(seconds(1));
              system("clear");
              M->show();
              a = 1;
            } catch (const char *e) {
              cin.clear();
              cin.ignore(50, '\n');
              int H = A->getsize();
              cout << e << H << endl;
              sleep_for(seconds(2));
              system("clear");
              M->show();
              a = 1;
            }
          } while (a);
          M->attack(t);
          A->attacked(choose, t->attack(), M);
          break;
        case 2:
          int Choose;
          if (t->gettype() == "Robot1") {
            do { // ---> exception
              cout << "Choose enemy" << endl;
              A->show_all();
              cout << "Input: ";
              a = 0;
              try {
                cin >> Choose;
                if (cin.fail())
                  throw 4;
                if (Choose > A->getsize() || Choose <= 0)
                  throw "input choose be more than 0 and less or equal to ";

              } catch (int e) {
                cout << "Input choose be integer" << endl;
                cin.clear();
                cin.ignore(50, '\n');
                sleep_for(seconds(1));
                system("clear");
                M->show();
                a = 1;
              } catch (const char *e) {
                cin.clear();
                cin.ignore(50, '\n');
                int H = A->getsize();
                cout << e << H << endl;
                sleep_for(seconds(2));
                system("clear");
                M->show();
                a = 1;
              }
            } while (a);
            M->skill(t);
            A->attacked(Choose, t->skill_1(), M);
          } else if (t->gettype() == "Robot2") {
            do { // ---> exception
              cout << "Choose an ally" << endl;
              this->show_name();
              cout << "Input: ";
              a = 0;
              try {
                cin >> Choose;
                if (cin.fail())
                  throw 4;
                if (Choose > R->getsize() || Choose <= 0)
                  throw "input choose be more than 0 and less or equal to ";

              } catch (int e) {
                cout << "Input choose be integer" << endl;
                cin.clear();
                cin.ignore(50, '\n');
                sleep_for(seconds(1));
                system("clear");
                M->show();
                a = 1;
              } catch (const char *e) {
                cin.clear();
                cin.ignore(50, '\n');
                int H = R->getsize();
                cout << e << H << endl;
                sleep_for(seconds(2));
                system("clear");
                M->show();
                a = 1;
              }
            } while (a);
            M->skill(t);
            this->healed(Choose, t->skill_1(), M);
          } else if (t->gettype() == "Robot3") {
            M->skill(t);
            A->all_attacked(t->skill_1(), M);
          }
          t->changecd_1(3); //ใช้สกิล ติดcd 2 เทิร์น
          break;
        default:
          cout << "WRONG" << endl;
          break;
        }
      }
      sleep_for(seconds(1));
      A->checkdeath(M);
    }
    M->receive_data(t);
    t = t->move_next();
  }
}

void LL::checkdeath(screen *M) {
  NODE *t = hol;
  NODE *p;
  int S = size;
  int i;
  for (i = 0; i < S; i++) {
    if (t->checkdeath() == 1) {
      M->receive_data(t);
      M->receive(t->getpo(), t->getdeath());
      if (t == hol) {
        hol = t->move_next();
        NODE *temp = t;
        delete temp;
        t = hol;
        size--;
      } else if (t->move_next() != NULL) {
        NODE *temp = t;
        t = t->move_next();
        t->insert(p);
        delete temp;
        size--;
      } else {
        delete t;
        size--;
      }
    } else {
      p = t;
      t = t->move_next();
    }
  }
}

int LL::getsize() { return size; }

LL::LL() {
  hol = NULL;
  size = 0;
}

LL::~LL() {
  int i;
  NODE *t;
  for (i = 0; i < size; i++) {
    t = hol;
    hol = hol->move_next();
    delete t;
  }
}

void LL::add_node(NODE *&A) {

  hol->insert(A);
  hol = A;

  size++;
}

void LL::show_all() {
  NODE *t = hol;
  int i;
  for (i = 0; i < size; i++) {
    cout << i + 1 << ".";
    t->show();
    t = t->move_next();
  }
}

void LL::show_name() {
  NODE *t = hol;
  int i;
  for (i = 0; i < size; i++) {
    cout << i + 1 << "." << t->getname() << endl;
    t = t->move_next();
  }
}

void LL::attacked(int x, int a, screen *M) {
  NODE *t = hol;
  for (int i = 1; i < x; i++) {
    t = t->move_next();
  }
  int b = t->takedamg(a);
  M->receive_data(t);
  M->shake(t);
  t->gettakedamg(b);
}

void LL::all_attacked(int a, screen *M) { //ยังมีปัญหา
  NODE *t = hol;
  int b;
  for (int i = 0; i < size; i++) {
    b = t->takedamg(a);
    t->gettakedamg(b);
    M->receive_data(t);
    M->receive(t->getpo(), t->getshake());
    t = t->move_next();
  }
  M->show();
  sleep_for(milliseconds(450));
  t = hol;
  for (int i = 0; i < size; i++) {
    M->receive_data(t);
    M->receive(t->getpo(), t->getnormal());
    t = t->move_next();
  }
  M->show();
}

void LL::healed(int x, int a, screen *M) {
  NODE *t = hol;
  for (int i = 1; i < x; i++) {
    t = t->move_next();
  }
  t->takeheal(a);
  M->receive_data(t);
  M->receive(t->getpo(), t->getreenergy());
  M->show();
  sleep_for(seconds(1));
  M->receive(t->getpo(), t->getnormal());
  M->show();
}

void LL::clear() {}

NODE *LL::gethol() { return hol; }
