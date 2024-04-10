#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
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
    void SetHealth(int NewHealth) {
      Health = NewHealth;
    }
    void Battle(Monster Enemy) {
      cout<<Enemy.GetHealth();      
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
  int NumberOfMonsters,NumberOfMonsters2,BattleType,SelectedMonster,Position = 1;
  string MonsterTeam[] = {};
  map<int, Monster> MonsterList,Player1Monsters, Player2Monsters;
  Monster Pikacho("Pikacho","Electric",100), Charmanker("Charmanker","Fire",95), Dragonknight("Dragonknight","Dragon",130), Mewthree("Mewthree","Pyschic",120), Garthwomp("Garthwomp","Dragon",110), Raygaza("Raygaza","Dragon",150) ;
  MonsterList.insert(pair<int, Monster>(1,Pikacho)), MonsterList.insert(pair<int, Monster>(2,Charmanker)), MonsterList.insert(pair<int, Monster>(3,Dragonknight)), MonsterList.insert(pair<int, Monster>(4,Mewthree)), MonsterList.insert(pair<int, Monster>(5,Garthwomp)), MonsterList.insert(pair<int, Monster>(6,Raygaza));
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
  NumberOfMonsters2 = NumberOfMonsters;
  cout<<"Here is the list of available monsters to choose:\n";
  while (NumberOfMonsters > 0) {
    for (auto& pair : MonsterList) {
      cout<<pair.first<<" - "<<pair.second.GetName()<<endl;
        }
    cout<<"Select a Monster to fight with! "<<NumberOfMonsters<<" choices remaining!"<<endl;
    cin>>SelectedMonster;
    auto it=MonsterList.find(SelectedMonster);
    if (it != MonsterList.end()) {
      NumberOfMonsters--;
      Player1Monsters.insert(pair<int, Monster>(Position,it->second));
      MonsterList.erase(SelectedMonster);
      Position++;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Invalid! Please select the number for which monster you would like to select\n"<<endl;
    }
    else {
      cout<<"That is not a valid Monster! Try Again!"<<endl;
    }
    for (auto& pair : Player1Monsters) {
      cout<<"Player1 Monster: "<<pair.second.GetName()<<"\n"<<endl;
        }
  }
  cout<<"All Choices have been made for Player 1's team!";
  while (true) {
    cout<<"\nSelect a Battle Type!\n1 - PVE Battle\n2 - PVP Battle"<<endl;
    cin>>BattleType;
    if (BattleType == 1) {
      cout<<"PVE Battle has been selected!"<<endl;
      int EnemySize = 0;
      map<int, Monster> BotMonsters;
      while (EnemySize < Player1Monsters.size()) {
        int NewNumber = GenerateNumber(1,6);
        auto it=MonsterList.find(SelectedMonster);
        if (it != MonsterList.end()) {
          BotMonsters.insert(pair<int, Monster>(NewNumber,it->second));
          cout<<"CPU picked Monster: "<<NewNumber<<"\n"<<endl;
          MonsterList.erase(NewNumber);
          EnemySize++;
        } 
        else {
          continue;
        } 
      }
      Charmanker.Battle(Dragonknight);
      break;
    }
    else if (BattleType == 2) {
      cout<<"PVP Battle has been selected!"<<endl;
        while (NumberOfMonsters2 > 0) {
          for (auto& pair : MonsterList) {
            cout<<pair.first<<" - "<<pair.second.GetName()<<endl;
              }
          cout<<"Player 2! Select a Monster to fight with! "<<NumberOfMonsters2<<" choices remaining!"<<endl;
          cin>>SelectedMonster;
          auto it=MonsterList.find(SelectedMonster);
          if (it!= MonsterList.end()) {
            NumberOfMonsters--;
            Player2Monsters.insert(pair<int, Monster>(Position,it->second));
            MonsterList.erase(SelectedMonster);
            Position++;
          }
          else if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout<<"Invalid! Please select the number for which monster you would like to select\n"<<endl;
          }
          else {
            cout<<"That is not a valid Monster! Try Again!"<<endl;
          }
          for (auto& pair : Player2Monsters) {
            cout<<"Player2 Monster: "<<pair.second.GetName()<<"\n"<<endl;
              }
      break;
      }
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
  int Choice;
  cout<<"\nWhat would you like to do?\n1 - Display entire battle index\n2 - Search for a Monster in battle index"<<endl;
  cin>>Choice;
  while (true) {
    ifstream TypingFile("BattleIndex.txt");
    if (Choice == 1) {
      string line;
        ifstream BattleIndexFile("BattleIndex.txt");
        if (BattleIndexFile.is_open()) {
          while (getline(BattleIndexFile, line)) { 
            cout <<line<< endl; 
          }
          BattleIndexFile.close();
        }
        else {
          cerr<<"File was unable to be opened!"; 
        }
        break;
      }
    else if (Choice == 2) {
      string Search,Line;
      int offset;
      ifstream TypingFile("BattleIndex.txt");
      TypingFile.open("BattleIndex.txt");
      cout<<"Enter the name of the monster you would like to search for!";
      cin>>Search;
      if(TypingFile.is_open()) {
        while (!TypingFile.eof()) {
          getline(TypingFile,Line);
          if ((offset = Line.find(Search, 0)) != string::npos)
          {
              cout << "The word has been found " << Search << endl;
          }
          TypingFile.close(); 
        }
      } 
      else {
        cerr<<"File not found!";
      }
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Invalid! Wrong data type!\n\n\n"<<endl;
      continue;
    }
    else {
      cout<<"Invalid Number! Try Again!\n\n\n"<<endl;
      continue;
    }
  }
}

void TypingInformation() {
  string line;
  ifstream TypingFile("TypingMatchups.txt");
  if (TypingFile.is_open()) {
    while (getline(TypingFile, line)) { 
      cout <<line<< endl; 
    }
    TypingFile.close();
  }
  else {
    cerr<<"File was unable to be opened!"; 
  }
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