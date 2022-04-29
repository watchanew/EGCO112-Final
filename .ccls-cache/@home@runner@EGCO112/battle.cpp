#include "character.h"
#include "setenemy.h"

void stage1_battle(Robot R1)
{
  setenemy_stage1();
  for(int turn = 1; turn <= 10; turn++)
  {
    cout<<endl<<"TURN "<< turn <<endl;
    cout<<endl<<"YOUR TURN"<<endl;
    E1.takedamg(R1.RobotAction());
    E2.takedamg(R1.RobotAction());
    E3.takedamg(R1.RobotAction());
    cout<<endl<<"ENEMY TURN"<<endl;
    R1.takedamg(E1.enemyAction());
    R1.takedamg(E2.enemyAction());
    R1.takedamg(E3.enemyAction());
    cout<<endl<<"END TURN"<<endl;
    
    if(R1.gethp()<=0)
    {
      cout << "You lose."<<endl;
      turn = 11;
    }
    else if(E1.gethp()<=0&&E2.gethp()<=0&&E3.gethp()<=0)
    {
      cout << "You win."<<endl;
      turn = 11;
    }
    else if(turn == 10)
    {
      cout << "Time is over" <<endl;
    }
  }
  
}
void stage2_battle(Robot R1,Robot R2,enemy E1,enemy E2,enemy E3)
{
  for(int turn = 1; turn <= 10; turn++)
  {
    cout<<endl<<"TURN "<< turn <<endl;
    cout<<endl<<"YOUR TURN"<<endl;
    if(R1.gethp()>0){
      
    }
    E1.takedamg(R1.RobotAction());
    cout<<endl<<"ENEMY TURN"<<endl;
    R1.takedamg(E1.enemyAction());
    cout<<endl<<"END TURN"<<endl;
    

    if(R1.gethp()<=0&&R2.gethp()<=0)
    {
      cout << "You lose."<<endl;
      turn = 11;
    }
    else if(E1.gethp()<=0&&E2.gethp()<=0&&E3.gethp()<=0)
    {
      cout << "You win."<<endl;
      turn = 11;
    }
    else if(turn == 10)
    {
      cout << "Time is over" <<endl;
    }
  }
  
}

void stage3_battle()
{
  
}