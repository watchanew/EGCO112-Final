#include <iostream>
using namespace std;
class NODE {
  NODE *next;

public:
  NODE();
  virtual void show() {}
  void insert(NODE *&);
  NODE *move_next();
  virtual int takedamg(int) {}
  virtual void takeheal(int) {}
  virtual int checkdeath() {}
  virtual int attack() {}
  virtual int skill_1() {}
  virtual void RobotAction() {}
  virtual int geten() {}
  virtual string gettype() {}
  virtual string getname() {}
  virtual string getstat() {}
  virtual int getcd_1() {}
  virtual int getpo() {}
  virtual void setpo(int) {}
  virtual void renew_energy() {}
  virtual void changecd_1(int) {}
  virtual string *getnormal() {}
  virtual string *getshake() {}
  virtual string *getdeath() {}
  virtual string *getattack_1() {}
  virtual string *getattack_2() {}
  virtual string *getskill(){}
  virtual string   *getreenergy() {}
  virtual void gettakedamg(int){}
  virtual ~NODE();
};

NODE::NODE() { next = NULL; }
NODE::~NODE() {}
NODE *NODE::move_next() { return next; }
void NODE::insert(NODE *&x) { x->next = this; }