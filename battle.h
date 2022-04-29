#include "interface.h"
#include "story.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

int battle(LL *A, LL *R, screen *S) {
  for (int turn = 1; turn <= 10; turn++) {
    A->datascreen(S);
    R->datascreen(S);
    S->getturn("TURN " + to_string(turn), "ROBOT TURN");
    int k = 0;
    sleep_for(seconds(1));
    R->robotaction(A, S, R);
    S->getturn("TURN " + to_string(turn), "ENEMY TURN");
    A->enemyaction(R, S);
    sleep_for(seconds(1));
    if (R->getsize() <= 0) {
      return 0;
    } else if (A->getsize() <= 0) {
      return 1;
    } else if (turn == 10) {
      cout << "Time is over" << endl;
      return 0;
    }
  }
  return 0;
}

int stage1_battle() // 1 Robot , 2 Human , 1 Fat human
{
  string a = "0";
  while (a != "1") {
    system("clear");
    cout << "======================== STAGE  1 =========================" << endl
         << endl;
    cout << stage1() << endl << endl;
    cout << "ENTER 1 TO CONTINUE" << endl;
    cin >> a;
  }
  LL A;
  LL R;
  int i;
  NODE *t;
  NODE *p;
  t = new human("Robert");
  A.add_node(t);
  t = new human("Teon");
  A.add_node(t);
  t = new fat_human("Raul");
  A.add_node(t);
  t = new robot1;
  R.add_node(t);
  screen S;
  S.getstage("STAGE  1");
  R.robotscreen(&S);
  A.enemyscreen(&S);
  if (battle(&A, &R, &S) == 1) {
    cout << "You win." << endl;
    return 1;
  } else {
    cout << "You lose." << endl;
    return 0;
  }
  sleep_for(seconds(3));
}

int stage2_battle() // 2 Robot ,  Wave1(3Human) ,Wave2(1Human,2Fat human)
{
  string a = "0";
  while (a != "1") {
    system("clear");
    cout << "======================== STAGE  2 =========================" << endl
         << endl;
    cout << stage2() << endl << endl;
    cout << "ENTER 1 TO CONTINUE" << endl;
    cin >> a;
  }
  LL A;
  LL R;
  int i;
  NODE *t;
  NODE *p;
  t = new human("Jerry");
  A.add_node(t);
  t = new human("Evan");
  A.add_node(t);
  t = new human("Tiger");
  A.add_node(t);
  t = new robot2;
  R.add_node(t);
  t = new robot1;
  R.add_node(t);
  screen S;
  S.getstage("STAGE  2");
  S.getwave("WAVE 1");
  R.robotscreen(&S);
  A.enemyscreen(&S);
  if (battle(&A, &R, &S) == 1) {
    cout << "You win." << endl;
    sleep_for(seconds(2));
    S.getwave("WAVE 2");
    t = new human("Gundam");
    A.add_node(t);
    t = new fat_human("Lumie");
    A.add_node(t);
    t = new fat_human("Mark");
    A.add_node(t);
    A.enemyscreen(&S);
    if (battle(&A, &R, &S) == 1) {
      cout << "You win." << endl;
      sleep_for(seconds(2));
      return 1;
    } else {
      cout << "You lose." << endl;
      return 0;
      sleep_for(seconds(3));
    }
  } else {
    cout << "You lose." << endl;
    return 0;
    sleep_for(seconds(3));
  }
}

int stage3_battle() // 2 Robot ,  Wave1(1Human,1Fat human) ,Wave2(1Soldier
                    // Human,2Fat human)
{
  string a = "0";
  while (a != "1") {
    system("clear");
    cout << "======================== STAGE  3 =========================" << endl
         << endl;
    cout << stage3() << endl << endl;
    cout << "ENTER 1 TO CONTINUE" << endl;
    cin >> a;
  }
  LL A;
  LL R;
  int i;
  NODE *t;
  NODE *p;
  t = new human("Devid");
  A.add_node(t);
  t = new fat_human("Wills");
  A.add_node(t);
  t = new robot2;
  R.add_node(t);
  t = new robot1;
  R.add_node(t);
  screen S;
  S.getstage("STAGE  3");
  S.getwave("WAVE 1");
  R.robotscreen(&S);
  A.enemyscreen(&S);
  if (battle(&A, &R, &S) == 1) {
    cout << "You win." << endl;
    sleep_for(seconds(2));
    S.getwave("WAVE 2");
    t = new soldier_human("Wanda");
    A.add_node(t);
    t = new fat_human("Vision");
    A.add_node(t);
    t = new fat_human("Tiny");
    A.add_node(t);
    A.enemyscreen(&S);
    if (battle(&A, &R, &S) == 1) {
      cout << "You win." << endl;
      sleep_for(seconds(2));
      return 1;
    } else {
      cout << "You lose." << endl;
      return 0;
      sleep_for(seconds(3));
    }
  } else {
    cout << "You lose." << endl;
    return 0;
    sleep_for(seconds(3));
  }
}

int stage4_battle() // 3 Robot ,  Wave1(1human, 1Soldier Human) ,Wave2(1Soldier
                    // Human,1Fat human,1human), Wave3(3 Soldier Human)
{
  string a = "0";
  while (a != "1") {
    system("clear");
    cout << "======================== STAGE  4 =========================" << endl
         << endl;
    cout << stage4() << endl << endl;
    cout << "ENTER 1 TO CONTINUE" << endl;
    cin >> a;
  }
  LL A;
  LL R;
  int i;
  NODE *t;
  NODE *p;
  t = new human("Lnwza");
  A.add_node(t);
  t = new soldier_human("Jean");
  A.add_node(t);
  t = new robot3;
  R.add_node(t);
  t = new robot2;
  R.add_node(t);
  t = new robot1;
  R.add_node(t);
  screen S;
  S.getstage("STAGE  4");
  S.getwave("WAVE 1");
  R.robotscreen(&S);
  A.enemyscreen(&S);
  if (battle(&A, &R, &S) == 1) {
    cout << "You win." << endl;
    sleep_for(seconds(2));
    S.getwave("WAVE 2");
    t = new soldier_human("Wendy");
    A.add_node(t);
    t = new fat_human("Abby");
    A.add_node(t);
    t = new human("Tony");
    A.add_node(t);
    A.enemyscreen(&S);
    if (battle(&A, &R, &S) == 1) {
      cout << "You win." << endl;
      sleep_for(seconds(2));
      S.getwave("WAVE 3");
      t = new soldier_human("Wendy");
      A.add_node(t);
      t = new fat_human("Abby");
      A.add_node(t);
      t = new human("Tony");
      A.add_node(t);
      A.enemyscreen(&S);
      if (battle(&A, &R, &S) == 1) {
        cout << "You win." << endl;
        sleep_for(seconds(2));
        return 1;
      } else {
        cout << "You lose." << endl;
        return 0;
        sleep_for(seconds(3));
      }
    } else {
      cout << "You lose." << endl;
      return 0;
      sleep_for(seconds(3));
    }

    return 0;
  } else {
    cout << "You lose." << endl;
    return 0;
    sleep_for(seconds(3));
  }
}

int stage5_battle() // 3 Robot ,  Wave1(1human,1Fat human,) ,Wave2(2 Soldier
                    // Human), Wave3(3 Soldier Human),WaveBoss(1Super Human)
{
  string a = "0";
  while (a != "1") {
    system("clear");
    cout << "======================== STAGE  5 =========================" << endl
         << endl;
    cout << stage5() << endl << endl;
    cout << "ENTER 1 TO CONTINUE" << endl;
    cin >> a;
  }
  LL A;
  LL R;
  int i;
  NODE *t;
  NODE *p;
  t = new human("Laica");
  A.add_node(t);
  t = new fat_human("Ukrit");
  A.add_node(t);
  t = new robot3;
  R.add_node(t);
  t = new robot2;
  R.add_node(t);
  t = new robot1;
  R.add_node(t);
  screen S;
  S.getstage("STAGE  5");
  S.getwave("WAVE 1");
  R.robotscreen(&S);
  A.enemyscreen(&S);
  if (battle(&A, &R, &S) == 1) {
    cout << "You win." << endl;
    sleep_for(seconds(2));
    S.getwave("WAVE 2");
    t = new soldier_human("Neyma");
    A.add_node(t);
    t = new soldier_human("Molly");
    A.add_node(t);
    A.enemyscreen(&S);
    if (battle(&A, &R, &S) == 1) {
      cout << "You win." << endl;
      sleep_for(seconds(2));
      S.getwave("WAVE 3");
      t = new soldier_human("Ning");
      A.add_node(t);
      t = new soldier_human("Ging");
      A.add_node(t);
      t = new soldier_human("Jing");
      A.add_node(t);
      A.enemyscreen(&S);
      if (battle(&A, &R, &S) == 1) {
        screen M;
        LL B;
        cout << "You win." << endl;
        M.getstage("STAGE  5");
        sleep_for(seconds(2));
        M.getwave("-BOSS-");
        t = new super_human("SUPER HUMAN");
        B.add_node(t); 
        R.robotscreen(&M);
        B.enemyscreen(&M);
        if (battle(&B, &R, &M) == 1) {
          cout << "You win." << endl;
          sleep_for(seconds(2));
          return 1;
        } else {
          cout << "You lose." << endl;
          return 0;
          sleep_for(seconds(3));
        }
      } else {
        cout << "You lose." << endl;
        return 0;
        sleep_for(seconds(3));
      }
    } else {
      cout << "You lose." << endl;
      return 0;
      sleep_for(seconds(3));
    }
    return 0;
  } else {
    cout << "You lose." << endl;
    return 0;
    sleep_for(seconds(3));
  }
}