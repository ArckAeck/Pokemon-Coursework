#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

class Monster {
  private:
    string Name;
    string Type;
    int Health;
    string moves[4];
  public:
    Monster(string N, string T, int H, string M) {
      Name = N;
      Type = T;
      Health = H;
      moves[3] = M;
    }
    string GetMoves() {
      return moves[3];
    }

};  

int GenerateNumber(short min, short max) {
  srand(time(0));
  short RanNum = (rand()%(max - min + 1)) + min;
  return RanNum;
}








void Battle() {
  int NumberOfMonsters;
  string SelectedMonster;
  string MonsterTeam[] = {};
  Monster Pikachu("Pikachu","Electric",100,{"Thunderbolt","Shock"});
  //MonsterDictionary["Pikachu"] = Pikachu, MonsterDictionary["Charizard"] = Charizard, MonsterDictionary["Dragonite"] = Dragonite;
  while (true) {
    cout<<"\nHow many monsters would you like to fight with?\n1 - One Monster\n3 - Three Monsters\n6 - Six Monsters\n";
    cin>>NumberOfMonsters;
    if (NumberOfMonsters == 3 || NumberOfMonsters == 6) {
      cout<<NumberOfMonsters<<" Monsters for battle selected!\n";
      break;
    }  
    else if (NumberOfMonsters == 1) {
      cout<<NumberOfMonsters<<" Monster for battle selected!\n";
      break;
    }
    else {
      cout<<"Invalid Number of Monsters! Try Again!\n";
    } 
  }
  while (NumberOfMonsters > 0) {
    cout<<"Select a Monster to fight with!\n";
    cin>>SelectedMonster;
    NumberOfMonsters--;
  }
  
}

void BattleIndex() {
  cout<<"\nFeature not currently operational"<<endl;
}

void TypingInformation() {
  string Value;
  ifstream TypingFile("TypingMatchups.txt");
  if (!TypingFile) {
    cout<<"Error! File does not exist!"<<endl;
  } 
  else {
    while (!TypingFile.eof()) {
    TypingFile>>Value;
    cout<<Value<<endl;
    }
  }
  TypingFile.close();
}

int main() {
  int Userchoice;  
  while (true) {
    cout<<"\nWelcome to the monster battle simulator! what would you like to do?\n1 - Start a battle\n2 - Battle Index\n3 - Typing Information\n4 - Quit\n";
    cin>>Userchoice;
    if (Userchoice == 1) {
      cout<<"Start a battle has been selected!"<<endl;
      Battle();
    }
    else if (Userchoice == 2) {
      cout<<"Battle Index has been selected!"<<endl;
      BattleIndex();
      cout<<GenerateNumber(50,100);
    }
    else if (Userchoice == 3) {
      cout<<"Typing information has been selected!"<<endl;
      TypingInformation();
    }
    else if (Userchoice == 4) {
      cout<<"Exit has been selected program will now cease running!"<<endl;
      break;
    }
    else {
      cout<<"That is an invalid choice! Try again!\n\n\n";
    }
  }
  return 0;
}