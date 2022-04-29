#include <iostream>
#include <string>
#include "battle.h"
using namespace std;

class ambient
{
  public :
    bool am = 0;
  //การเกิดฝนอาจจะทำให้การโจมตีปกติมีค่าน้อยลง 
  //ถ้า bool am สุ่มมาแล้วได้ 1 จะลดประสิทธิภาพโจมตี 5% 
};
void main() 
{ 
  robot1 R1();
  stage1_battle(R1);
}
  
/*
  void interface (void)
{
 ถ้า ให้ A โจมตี 
 = please select option
  1 = Hit
  2 = Run
  cout << "==== Time : ==== \n"; 
  cout << "==== Status ==== \n";
  //Human
  //cout << " Name :  " << endl;
  
  cout << " Damage : " << endl;
  cout << " Defense : " << endl;
  cout << " HP : " << endl;
  //Robot (ฝั่งเรา)
  cout << " Damage : " << endl;
  cout << " Defense : " << endl;
  cout << " HP : " << endl;
  cout << " Energy : " << endl;
}

  
*/
