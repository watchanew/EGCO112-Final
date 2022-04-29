#include "NODE.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <time.h>
#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds
class character : public NODE     // mother class
{
protected:
  string name;
  int hp;       // health point
  int max_hp;   // hp สูงสุด
  int atk;      // attack point
  int df;       // defense point
  int cd_1 = 0; // cooldown skill1
  int po = 0;   // position

public:
  character(string n, int a, int c, int d) {
    max_hp = a;
    hp = a;
    df = c;
    atk = d;
    name = n;
  }
  int checkdeath() { //เช็คว่าตายหรือยัง
    if (hp <= 0) {
      return 1;
    } else
      return 0;
  }
  void setpo(int a) { po = a; } //ตั้งตำแหน่งในหน้าจอ
  int getpo() { return po; } //รับค่าตำแหน่ง
  int getcd_1() { return cd_1; }
  void changecd_1(int a) {
    cd_1 = cd_1 + a;
    if (cd_1 < 0) {
      cd_1 = 0;
    }
  }
  string getname() { return name; }
  int gethp() { return hp; }
  int getdf() { return df; }
  int getatk() { return atk; }
  int takedamg(int d) { //เลือดลด
    d = d - df;
    hp = hp - d;
    if (hp < 0) {
      hp = 0;
    }
    return d;
  }
  void gettakedamg(int d){
    cout << name << " take " << d << " damage." << endl;
    sleep_for(seconds(1));
  }

  void takeheal(int d) { //รับฟื้นฟูhp
    if (d + hp > max_hp) {
      d = max_hp - hp;
      hp = max_hp;
    } else
      hp = hp + d;
    cout << name << " was healed " << d << " HP." << endl;
    sleep_for(seconds(1));
  }
  void show() {
    cout << name << " HP:" << hp << "/" << max_hp << " def: " << df
         << " atk: " << atk << endl;
  }
  string getstat() {
    string a = name + " HP:" + to_string(hp) + "/" + to_string(max_hp) +
               " def: " + to_string(df) + " atk: " + to_string(atk);
    return a;
  }
  ~character() {}
};

class Robot : public character //หุ่นยนต์ฝั่งเรา Inheritances class
{
protected:
  int max_en; // enegy สูงสุดที่สามารถเก็บได้
  int en;
  int en_c = 0;
  string type;

public:
  Robot(string n, string t, int h, int e, int d, int a)
      : character(n, h, d, a) {
    max_en = e;
    en = e;
    type = t;
  }
  int attack(void) {
    int attack;
    srand(time(NULL));
    attack = atk;
    this->usedenergy(1);
    cout << "You just attacking on enemy with " << attack
         << " damage.\nUse 1 enegy " << name << " has " << en << " enegy left "
         << endl;
    return attack;
  }
  string gettype() { return type; }
  int geten() { return en; }
  bool check_reenergy(int t) {
    if ((en_c + 1) == t) {
      en_c = 0;
      return true;
    } else {
      en_c = t;
      return false;
    }
  }
  void usedenergy(int x) { en = en - x; }
  void renew_energy() {
    int d = 3;
    if (en + d > max_en) {
      d = max_en - en;
      en = max_en;
    } else {
      en = en + d;
    }
    cout << name << " restored " << d << " enegy." << endl;
    sleep_for(seconds(1));
  }
  ~Robot() {}
};

class robot1 : public Robot // Inheritances class from robot
{
private:
  string normal[5] = {"       __,_,   ", "      [_|_/    ", "      //       ",
                      "   _)(  )(_    ", "  `---''---`   "};
  string shake[5] = {"      __>_<    ", "     [_|_/     ", "     //        ",
                     "  _)(  )(_     ", " `---''---`    "};
  string death[5] = {"       __x_x   ", "      [_|_/    ", "      //       ",
                     "   _)(  )(_    ", "  `---''---`   "};
  string criti[5] = {"        __>_< /", "       [_|_/ / ", "       //   /  ",
                     "    _)(  ) |   ", "   `---''---`  "};
  string attack_1[5] = {"        __,_,  ", "       [_|_/   ", "       //  /   ",
                        "    _)(  ) |   ", "   `---''---`  "};
  string attack_2[5] = {"        __,_,  ", "       [_|_/   ", "       //      ",
                        "    _)(  ) /)  ", "   `---''---`  "};
  string reenergy[5] = {"   *  __^_^    ", "     [_|_/  *  ", "    * ||       ",
                        "   _)(  )(_    ", "  `---''---`   "};

public:
  robot1(string n = "C3P0", string t = "Robot1", int h = 7, int e = 5,
         int d = 1, int a = 4)
      : Robot(n, t, h, e, d, a) {}
  string getstat() {
    string a = "C3P0 HP:" + to_string(hp) + "/" + to_string(max_hp) +
               " def:" + to_string(df) + " EN:" + to_string(en) + "/" +
               to_string(max_en);
    //"C3P0 HP:5/5 def:5/5 EN:5/5"
    return a;
  }
  void RobotAction(void) {
    cout << "Pick your action!!!" << endl;
    cout << "0.Restore enegy   : use 1 turn" << endl;
    cout << "1.Attacking       : use 1 en : deal " << atk << " damage" << endl;
    cout << "2.Critical attack : use 3 en : deal " << atk * 2.5 << " damage";
    if (cd_1 > 0) {
      cout << ": cd " << cd_1 << " turn";
    }
    cout << endl << "=============================================" << endl;
  }
  int skill_1() {
    int attack;
    srand(time(NULL));
    attack = 2.5 * atk;
    this->usedenergy(3);
    cout << "You just use critical attack on enemy with " << attack
         << " damage.\nUse 3 enegy " << name << " has " << en << " energy left "
         << endl;
    return attack;
  }
  string *getnormal() {
    string *a = normal;
    if(hp<=0){
      a = death;
    }
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
  string *getreenergy() {
    string *a = reenergy;
    return a;
  }
  string *getskill() {
    string *a = criti;
    return a;
  }
  ~robot1() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : Boop Beep... " << endl;
      sleep_for(seconds(1));
      cout << endl << name << " was destroyed." << endl;
      sleep_for(seconds(1));
    }
  }
};

class robot2 : public Robot // Inheritances class from robot
{
private:
  string normal[5] = {"      _zC_     ", "      [Q_Q]    ", "      \\|+|/>   ",
                      "    _)(  )(_   ", "   `---''---`  "};
  string shake[5] = {"     _zC_      ", 
                     "     [v_v]     ", 
                     "      |/+|/    ",
                     "   _)(  )(_    ", 
                     "  `---''---`   "};
  string heal[5] = {"       _zC_    ", "    +  [*_*]   ", "       \\|+|/>+ ",
                    "     _)(  )(_  ", "    `---''---` "};
  string attack_1[5] = {"       _zC_    ", "       [Q_Q]0  ",
                        "       \\|+|/^  ", "     _)(  )(_  ",
                        "    `---''---` "};
  string attack_2[5] = {"       _zC_    ", "       [Q_Q]   ",
                        "       \\|+|/>00", "     _)(  )(_  ",
                        "    `---''---` "};
  string reenergy[5] = {"      _zC_     ", "      [-_-]zZ  ",
                        "      \\|+|/    ", "    _)(  )(_   ",
                        "   `---''---`  "};
  string death[5] = {"      _zC_     ", "      [XoX]    ", "       |/+|/   ",
                     "    _)(  )(_   ", "    _)(  )(_   "};

public:
  robot2(string n = "R3D2", string t = "Robot2", int h = 8, int e = 5,
         int d = 2, int a = 3)
      : Robot(n, t, h, e, d, a) {}
  int skill_1() {
    int heal;
    srand(time(NULL));
    heal = (1) * atk;
    this->usedenergy(3);
    cout << "You just use heal on an ally with " << heal
         << " damage.\nUse 3 enegy " << name << " has " << en << " energy left "
         << endl;
    return heal;
  }
  string getstat() {
    string a = "R3D2 HP:" + to_string(hp) + "/" + to_string(max_hp) +
               " def:" + to_string(df) + " EN:" + to_string(en) + "/" +
               to_string(max_en);
    return a;
  }
  void RobotAction(void) {
    cout << "Pick your action!!!" << endl;
    cout << "0.Restore enegy   : use 1 turn" << endl;
    cout << "1.Attacking       : use 1 en : deal " << atk << " damage" << endl;
    cout << "2.Heal            : use 3 en : heal " << atk << " HP";
    if (cd_1 > 0) {
      cout << ": cd " << cd_1 << " turn";
    }
    cout << endl << "=============================================" << endl;
  }
  string *getnormal() {
    string *a = normal;
    if(hp<=0){
      a = death;
    }
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
  string *getskill() {
    string *a = heal;
    return a;
  }
  string *getreenergy() {
    string *a = reenergy;
    return a;
  }
  ~robot2() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : system error... " << endl;
      sleep_for(seconds(1));
      cout << endl << name << " was destroyed." << endl;
      sleep_for(seconds(1));
    }
  }
};

class robot3 : public Robot // Inheritances class from robot
{
private:
  string normal[5] = {"      _***_    ", "   * /[/<X]    ", "    \\<[||]>*   ",
                      "     /./|./    ", "   '--''---`   "};
  string shake[5] = {"     _***_     ", "    /['><] *   ", "   |_>O|]>/    ",
                     "     |.|.|     ", "    '--''---`  "};
  string bomb[5] = {"    _***_      ", "   /[c<X]  _*_ ", "   |_[||]-<[_] ",
                    "    |./|.|     ", "   '--''---`   "};
  string attack_1[5] = {"      _***_    ", "     /[;<X]    ", "    |_[||]>o*  ",
                        "      |./|.|   ", "     '--''---` "};
  string attack_2[5] = {"      _***_    ", "     /[;<X] ,  ", "    |_[||]O))* ",
                        "      |./|.| ' ", "     '--''---` "};
  string reenergy[5] = {"      _***_    ", "     /[;--]    ", "    |_>||]<    ",
                        "      |.|.|    ", "     '--''---  "};
  string death[5] = {"      _***_    ", "     /['XX]    ", "    |_>O|]>    ",
                     "      |.|.|    ", "     '--''---` "};

public:
  robot3(string n = "JUNKCAT", string t = "Robot3", int h = 6, int e = 5,
         int d = 1, int a = 5)
      : Robot(n, t, h, e, d, a) {}
  void RobotAction(void) {
    cout << "Pick your action!!!" << endl;
    cout << "0.Restore enegy   : use 1 turn" << endl;
    cout << "1.Attacking       : use 1 en : deal " << atk << " damage" << endl;
    cout << "2.Fire in the hole: use 3 en : deal " << atk << " damage";
    if (cd_1 > 0) {
      cout << ": cd " << cd_1 << " turn";
    }
    cout << endl << "=============================================" << endl;
  }
  int skill_1() {
    int attack;
    srand(time(NULL));
    attack = 1 * atk;
    this->usedenergy(3);
    cout << "You just use fire in the hole on all enemy with " << attack
         << " damage.\nUse 3 enegy " << name << " has " << en << " energy left "
         << endl;
    return attack;
  }
  string getstat() {
    string a = "JUNKCAT HP:" + to_string(hp) + "/" + to_string(max_hp) +
               " def:" + to_string(df) + " EN:" + to_string(en) + "/" +
               to_string(max_en);
    return a;
  }
  string *getnormal() {
    string *a = normal;
    if(hp<=0){
      a = death;
    }
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
  string *getskill() {
    string *a = bomb;
    return a;
  }
  string *getreenergy() {
    string *a = reenergy;
    return a;
  }
  ~robot3() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : self-destruct in 3 2 1 " << endl;
      sleep_for(seconds(1));
      cout << endl << name << " was destroyed." << endl;
      sleep_for(seconds(1));
    }
  }
};

class enemy : public character //ฝั่งศัตรู //Inheritances class from character
{
private:
  string type;
public:
  enemy(string t, string n, int h, int d, int a) : character(n, h, d, a) {
    type = t;
  }
  int attack(void) {
    int attack;
    srand(time(NULL));
    attack = 1 * atk;
    return attack;
  }
  ~enemy() {}
};

class human : public enemy // Inheritances class from enemy
{
private:
  string normal[5] = {"      ____    ", "     (0 0 )   ", "     /|  |\\    ",
                      "      |__|     ", "      |  |     "};
  string shake[5] = {"       ____   ", "      (> < )  ", "      /|  |\\   ",
                     "       |__|    ", "      /  /     "};
  string death[5] = {"      ____    ", "     (X X )   ", "     /|  |\\    ",
                     "      |__|     ", "      |  |     "};
  string attack_1[5] = {"     ____     ", "    (0 0 )    ", "    -| \\|     ",
                        "     |__|      ", "     |  |      "};
  string attack_2[5] = {"     ____     ", "    (0 0 )    ", "   --| \\|     ",
                        "     |__|      ", "     |  |      "};
public:
  human(string n, string t = "human", int h = 2, int d = 0, int a = 2)
      : enemy(t, n, h, d, a) {}
  ~human() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : Nooooooo!!!!" << endl;
      sleep_for(seconds(1));
      cout << endl << "Human " << name << " is dead." << endl;
      sleep_for(seconds(1));
    }
  }
  string *getnormal() {
    string *a = normal;
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
};
class fat_human : public enemy // Inheritances class from enemy
{
private:
  string normal[5] = {"      |||||    ", "     ( ๐ ๐ )    ",
                      "    //     \\\\   ", "     \\ ๐๐๐ /      ",
                      "     ||    ||    "};
  string shake[5] = {"       |||||   ", "      ( @ @')   ",
                     "     //     \\\\  ", "      \\ ๐๐๐ /     ",
                     "      //    //   "};
  string death[5] = {"      |||||    ", "     ( x x )    ",
                     "    //     \\\\    ", "     \\ ๐๐๐ /      ",
                     "     ||    ||    "};
  string attack_1[5] = {"     |||||     ", "  \\ ( ๐ ๐ )     ",
                        "   \\/     \\\\    ", "    \\ ๐๐๐ /       ",
                        "    ||    ||     "};
  string attack_2[5] = {"     |||||     ", "    ( ๐ ๐ )     ",
                        "   //     \\ \\    ", "  / \\ ๐๐๐ /       ",
                        "    ||    ||     "};
public:
  fat_human(string n, string t = "fat human", int h = 4, int d = 1, int a = 3)
      : enemy(t, n, h, d, a) {}
  ~fat_human() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : My child, I'm sorry..." << endl;
      sleep_for(seconds(1));
      cout << endl << "Fat human " << name << " is dead." << endl;
      sleep_for(seconds(1));
    }
  }
  string *getnormal() {
    string *a = normal;
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
};
class soldier_human : public enemy // Inheritances class from enemy
{
private:
  string normal[5] = {"   ________( •̪●)   ", "   ▃▄▄▄▄▄███████ ] ",
                      "     ▂▄▅█████████▅▄▃▂  ", "   I███████████████████]. ",
                      "    ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤...    "};
  string shake[5] = {"    ________( •̪●)  ", "    ▃▄▄▄▄▄███████ ]",
                     "      ▂▄▅█████████▅▄▃▂ ", "    I███████████████████].",
                     "     ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤...   "};
  string death[5] = {"   ________( X )   ", "   ▃▄▄▄▄▄███████ ] ",
                     "     ▂▄▅█████████▅▄▃▂  ", "   I███████████████████]. ",
                     "    ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤...    "};
  string attack_1[5] = {" |________( •̪●)    ", "-o▃▄▄▄▄▄███████ ]  ",
                        " |  ▂▄▅█████████▅▄▃▂   ", "  I███████████████████].  ",
                        "   ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤...     "};
  string attack_2[5] = {"   ________( •̪●)   ", "***▃▄▄▄▄▄███████ ] ",
                        "     ▂▄▅█████████▅▄▃▂  ", "   I███████████████████]. ",
                        "    ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤...    "};
public:
  soldier_human(string n, string t = "Soldier human", int h = 5, int d = 2,
                int a = 3)
      : enemy(t, n, h, d, a) {}
  ~soldier_human() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : mission...";
      sleep_for(milliseconds(500));
      cout << "failed" << endl;
      sleep_for(seconds(1));
      cout << endl << "Soldier human " << name << " is dead." << endl;
      sleep_for(seconds(1));
    }
  }
  string *getnormal() {
    string *a = normal;
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
};
class super_human : public enemy // Inheritances class from enemy
{
private:
  string normal[5] = {
      "            _^_^_             ", "    *    ^, |@o@|  ,^         ",
      "       /VA^/|-v-|\\^AV\\   *  ", "      /VAV /| | |\\ VAV\\     ",
      "   * /AVAV/ /_I_\\ \\VAVA\\    "};
  string shake[5] = {"            _^_^_       ", "    ouch    |>o<|       ",
                     "          (\\     /)     ", "           (\\   /)      ",
                     "             (V)        "};
  string death[5] = {
      "            _^_^_             ", "    *    ^, |X_X|  ,^         ",
      "       /VA^/|-v-|\\^AV\\   *  ", "      /VAV /| | |\\ VAV\\     ",
      "   * /AVAV/ /_I_\\ \\VAVA\\    "};
  string attack_1[5] = {"            _^_^_        "
                        "            |@o@|        ",
                        "            (   )        ",
                        "             \\ /        ",
                        "              V          "};
  string attack_2[5] = {
      "            _^_^_             ", "      (!! ^___ |@o@| ___^     ",
      "       (!! \\  \\ _(_ /  /   ", "        (!! \\ \\  )  / /     ",
      "         (!!  \\VVVVV/       "};
public:
  super_human(string n, string t = "Super human", int h = 10, int d = 3,
              int a = 4)
      : enemy(t, n, h, d, a) {}
  ~super_human() {
    if (hp > 0) {
    } else {
      sleep_for(milliseconds(500));
      cout << endl << name << " : Superhuman....never...lost." << endl;
      sleep_for(seconds(1));
      cout << endl << "Super human " << name << " is dead." << endl;
      sleep_for(seconds(3));
    }
  }
  string *getnormal() {
    string *a = normal;
    return a;
  }
  string *getshake() {
    string *a = shake;
    return a;
  }
  string *getdeath() {
    string *a = death;
    return a;
  }
  string *getattack_1() {
    string *a = attack_1;
    return a;
  }
  string *getattack_2() {
    string *a = attack_2;
    return a;
  }
};
#endif