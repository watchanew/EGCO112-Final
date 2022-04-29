#include <iostream>
#include "character.h"
using namespace std;
//humansetup ("human","name",1,1,1)
//fat_humansetup ("fat human","name",2,2,2)

void set_stage1(){//human 2ตัว fat human 1ตัว
  enemy human1("human","Robert",1,1,1);
  enemy human2("human","Teon",1,1,1);
  enemy fat_human1 ("fat human","Raul",2,2,2);
}
void set_stage2(){//human 2ตัว fat human 1ตัว
  enemy human1(),human2(),fat_human1();
}
void set_stage3(){//human 2ตัว fat human 1ตัว
  enemy human1(),human2(),fat_human1();
}
