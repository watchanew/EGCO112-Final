#include <iostream>
#include <stdlib.h>
#include "LL.h"
using namespace std;

void openwindow()
{
  system("cls");
  //system("Color 0A"); //red color 
  cout<<"Hello, Welcome to Energy War"<<endl;
  cout<<"_____________      __ "<<endl;
  cout<<"\\   _____/  \\    /   \\"<<endl;
  cout<<" |    __)_\\   \\/\\/   /"<<endl;
  cout<<" |        \\         / "<<endl;
  cout<<"/_______  / \\__/\\  / "<<endl;
  cout<<"        \\/       \\/   "<<endl;
  cout<<"=======================" <<endl;
}

void menu()
{
  cout<<"--> START GAME <--" <<endl;
  cout<<"--> HOW TO PLAY <--" <<endl;
  cout<<"--> ABOUT US <--" <<endl;
  cout<<"--> EXIT<--" <<endl;
}