#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

class Monster {
  private:
    string Name;
    string Type;
    int Health;
  public:
    Monster(string N, string T, int H) {
      Name = N;
      Type = T;
      Health = H;
    }
    string GetName() {
      return Name; 
    }
    string GetType() {
      return Type;
    }
    int GetHealth() {
      return Health;
    }
};  

class FireMonster : public Monster {
  public:
    void SelectMove(class Monster Enemy) {
      cout<<"Here Are the Available Moves 1 - Flamethrower\n2 - Flame Charge\n3 - Blaze Kick"<<endl;
      if (Enemy.GetType() == "Water") {
        cout<<"Not Very Effective"<<endl;
        
        
      }
    }

};

int GenerateNumber(short min, short max) {
  srand(time(0));
  short RanNum = (rand()%(max - min + 1)) + min;
  return RanNum;
}
void RandomSelect(map<string,Monster> MonsterMap) {
  cout<<"Feature currently out of comission";
}




void Battle() {
  int Position = 1;
  int NumberOfMonsters;
  int BattleType;
  string SelectedMonster;
  string MonsterTeam[] = {};
  map<string, Monster> MonsterList;
  map<int, Monster> Player1Monsters;
  Monster Pikacho("Pikacho","Electric",100);
  Monster Charmanker("Charmanker","Fire",95);
  Monster Dragonknight("Dragonknight","Dragon",130);
  Monster Mewthree("Mewthree","Pyschic",120);
  MonsterList.insert(pair<string, Monster>("Pikacho",Pikacho));
  MonsterList.insert(pair<string, Monster>("Charmanker",Charmanker));
  MonsterList.insert(pair<string, Monster>("Dragonknight",Dragonknight));
  MonsterList.insert(pair<string, Monster>("Mewthree",Mewthree));
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
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type entered! Try Again!\n";
    }
    else {
      cout<<"Invalid Number of Monsters! Try Again!\n";
    } 
  }
  cout<<"Here is the list of available monsters to choose:\n";
  while (NumberOfMonsters > 0) {
    for (const auto &[key,value] : MonsterList ) {
      cout<<key<<endl;
    }
    cout<<"Select a Monster to fight with! "<<NumberOfMonsters<<" choices remaining!"<<endl;
    cin>>SelectedMonster;
    if (MonsterList.find(SelectedMonster) != MonsterList.end()) {
      cout<<"You have selected Monster! "<<SelectedMonster<<"\n"<<endl;
      NumberOfMonsters--;
      Player1Monsters.insert(pair<int, Monster>(Position,Pikacho));
      MonsterList.erase(SelectedMonster);
      Position++;
    }
    else {
      cout<<"That is not a valid Monster! Try Again!"<<endl;
    }
    for (const auto &[key,value] : Player1Monsters ) {
      cout<<"Player1 Monster: "<<key<<"\n"<<endl;
    }
  }
  cout<<"All Choices have been made for Player 1's team!";
  while (true) {
    cout<<"\nSelect a Battle Type!\n1 - PVE Battle\n2 - PVP Battle"<<endl;
    cin>>BattleType;
    if (BattleType == 1) {
      cout<<"PVE Battle has been selected!"<<endl;
      for (int n = 0; n < Player1Monsters.size(); n++) {
        cout<<"here for a sec"<<endl;        
      }
      break;
    }
    else if (BattleType == 2) {
      cout<<"PVP Battle has been selected!"<<endl;
      for (const auto &[key,value] : MonsterList ) {
        cout<<key<<endl;
      }
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type! Try again!"<<endl;
    }
    else {
      cout<<"Invalid Battle Type! Try Again!"<<endl;
    }
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
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Invalid! Wrong data type!\n\n\n"<<endl;
    }
      
    else {
      cout<<"That is an invalid Number! Try again!\n\n\n";
    
    }
  }
  return 0;
}