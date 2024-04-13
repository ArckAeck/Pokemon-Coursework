#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
#include <iterator>
using namespace std;

// Function to generate a random number between a minimum and maximum value
int GenerateNumber(short min, short max) {
  srand(time(0));
  short RanNum = (rand()%(max - min + 1)) + min;
  return RanNum;
}
class Monster {
  private:
    string Name;
    string Type;
    int Health;
    int Speed;
  public:
    Monster(string N, string T, int H, int S) {
      Name = N;
      Type = T;
      Health = H;
      Speed = S;
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
    int GetSpeed() {
      return Speed;
    }
    void SetHealth(int NewHealth) {
      Health = NewHealth;
    }
    void Attack(Monster Enemy) {
      string input;
      Enemy.SetHealth(Enemy.GetHealth() - GenerateNumber(1, 10));
      cout<<Enemy.GetHealth();
      cin>>input;
      
    }
    void OutputStats() {
      cout<<"\nName: "<<GetName()<<"\nType: "<<GetType()<<"\nHealth: "<<GetHealth()<<"\nSpeed: "<<GetSpeed()<<endl;
    }
    bool IsAlive() {
      if (Health > 0) {
        return true;
      }
      else {
        return false;
      }
    }
};  
class FireMonster : public Monster {
  public:
    int CheckDamage(int PrevDamage, Monster Enemy) {
      if (Enemy.GetType() == "Water") {
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was not very effective!";
      }
      else if (Enemy.GetType() == "Dragon") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was very effective!";
      }
      return PrevDamage;
    }
    void Attack(Monster Enemy) {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening;
      while (true) {
        cout<<"Here Are the Available Moves 1 - Flamethrower\n2 - Flame of Life\n3 - Blaze Kick"<<endl;
        cin>>AttackChoice;
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Flamethrower"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Flamethrower did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Enemy.SetHealth(Enemy.GetHealth() - TypeDamage);
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Flame of life"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Flame of life was activated!"<<endl;
            SetHealth(GetHealth() + HPChange);
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
          } 
          else {
            cout<<"Flame of life failed! "<<GetHealth()<< "'s Health remains the same";
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Blaze Kick"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          if (ChanceOfHappening == 2) {
            cout<<"Blaze Kick was activated!"<<endl;
            Enemy.SetHealth(Enemy.GetHealth() + HPChange);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
          }      
          else {
            cout<<"Blaze Kick failed! "<<Enemy.GetName()<<"'s Health remains the same";
          }
        }       
        else if (cin.fail()) {
          cin.clear();
          cin.ignore();
          cout<<"That is the wrong data type! Try again!\n";
        }
        else {
          cout<<"Invalid move number entered! Try again!\n";
        }
    }
  }
};

class WaterMonster : public Monster {
  public:
    int CheckDamage(int PrevDamage, Monster Enemy) {
      if (Enemy.GetType() == "Fire") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was very effective!";
      }
      else if (Enemy.GetType() == "Dragon") {
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was not very effective!";
      }
      return PrevDamage;
    }
  void Attack(Monster Enemy) {
    while (true) {
      cout<<"Here Are the Available Moves 1 - Water Gun\n2 - Waterfall\n3 - Water Jet"<<endl;
    }
  }
};
void PlayerSwitchMonster(map<int, Monster> &Map, Monster &SelectedMonster) {
  int Input;
  while (true) {
    cout<<"Please select the monster you would like to switch your current monster to!"<<endl;
    for (auto& pair : Map) {
      cout<<pair.first<<" - "<<pair.second.GetName()<<endl;
        }
    cin>>Input;
    auto it=Map.find(Input);
    if (it != Map.end()) {
      SelectedMonster = it->second;
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type entered! Try Again!\n";
      continue;
    }
    else {
      cout<<"Invalid monster number entered! Try again!\n";
      continue;
    }
  }
  }
void BotSwitchMonster(map<int, Monster> &Map, Monster &SelectedMonster) {
  while (true) {
    int RandomNumber = GenerateNumber(1,Map.size());
    auto it=Map.find(RandomNumber);
    if (it != Map.end()) {
      SelectedMonster = it->second;
      cout<<"CPU has switched monster!"<<endl;
      break;
    }
    else {
      continue;
    }
  }
  }
void PlayerBattleMenu(map<int, Monster> &Map,Monster &Player, Monster &Enemy) {
  int Input;
  while (true) {
    cout<<"What would you like to do?\n1 - Use a move\n2 - Switch current monster"<<endl;
    cin>>Input;
    if (Input == 1) {
      Player.Attack(Enemy);
      break;
    }
    else if (Input == 2) {
      PlayerSwitchMonster(Map, Player);
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type entered! Try Again!\n";
    }
    else {
      cout<<"Invalid number entered! Try again!\n";
    }
  }
  }
void BotBattleMenu(map<int, Monster> &Map,Monster &Bot, Monster &Enemy) {
  int RandomSelection = GenerateNumber(1,2);
  if (RandomSelection == 1) {
    Bot.Attack(Enemy);
  }
  else {
    BotSwitchMonster(Map, Bot);
  }
  
}

void MonsterSelection() {
  int NumberOfMonsters,NumberOfMonsters2,BattleType,SelectedMonster,Position = 1; 
  string MonsterTeam[] = {};
  map<int, Monster> MonsterList,Player1Monsters, Player2Monsters, BotMonsters; /* 4 maps are created using
            an intenger as a key and storing a monster object as the value*/
  Monster Pikacho("Pikacho","Electric",100,30), Charmanker("Charmanker","Fire",95,15), Dragonknight("Dragonknight","Dragon",130,50), Daggron("Daggron","Rock",120,25), Drenchninja("Drenchninja","Water",110,45), Raygaza("Raygaza","Dragon",150,60) ; // Monster objects are created
  MonsterList.insert(pair<int, Monster>(1,Pikacho)), MonsterList.insert(pair<int, Monster>(2,Charmanker)), MonsterList.insert(pair<int, Monster>(3,Dragonknight)), MonsterList.insert(pair<int, Monster>(4,Daggron)), MonsterList.insert(pair<int, Monster>(5,Drenchninja)), MonsterList.insert(pair<int, Monster>(6,Raygaza)); // Monster objects are inserted into the MonsterList map alongside corresponding indentifying key numbers
  while (true) {
    cout<<"\nHow many monsters would you like to fight with?\n1 - One Monster\n3 - Three Monsters\n6 - Six Monsters\n";
    cin>>NumberOfMonsters;
    if (NumberOfMonsters == 3 || NumberOfMonsters == 6) {
      cout<<NumberOfMonsters<<" Monsters for battle selected!\n";
      break; //
    }  
    else if (NumberOfMonsters == 1) {
      cout<<NumberOfMonsters<<" Monster for battle selected!\n"; /* if statement for if a user enters 1 as the number of monsters
          they would like to fight with it is separated for grammatical sense and since it is valid loop is ended */
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
      cout<<pair.first<<" - "<<pair.second.GetName()<<" Type: "<<pair.second.GetType()<<endl;
        }
    cout<<"Enter the number of the monster you'd like to choose! "<<NumberOfMonsters<<" choices remaining!"<<endl;
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
  Monster CurrentMonster = Player1Monsters.begin()->second;
  while (true) {
    cout<<"\nSelect a Battle Type!\n1 - PVE Battle\n2 - PVP Battle"<<endl;
    cin>>BattleType;
    if (BattleType == 1) {
      cout<<"PVE Battle has been selected!"<<endl;
      int EnemySize = 0, EnemyNumber = 1;
      while (EnemySize < Player1Monsters.size()) {
        int NewNumber = GenerateNumber(1,6);
        auto it=MonsterList.find(NewNumber);
        if (it != MonsterList.end()) {
          BotMonsters.insert(pair<int, Monster>(EnemyNumber,it->second));
          MonsterList.erase(NewNumber);
          EnemySize++;
          EnemyNumber++;
          cout<<"CPU Monster picked: "<<NewNumber<<endl;
              
        } 
        else {
          continue;
        } 
      }
      cout<<"The CPU Team has been selected here it is!\n"<<endl;
      for (auto& pair : BotMonsters) {
        cout<<"CPU Monster: "<<pair.second.GetName()<<"\n"<<endl;
          }
      Monster OpponentMonster = BotMonsters.begin()->second;
      BotSwitchMonster(BotMonsters, OpponentMonster);
      CurrentMonster.OutputStats();
      OpponentMonster.OutputStats();
      while (CurrentMonster.GetHealth() > 0 && OpponentMonster.GetHealth() > 0) {
        if (CurrentMonster.GetSpeed() > OpponentMonster.GetSpeed()) {
          PlayerBattleMenu(Player1Monsters,CurrentMonster,OpponentMonster);
          BotBattleMenu(BotMonsters,OpponentMonster,CurrentMonster);  
        }
        else {
          cout<<"k bruh";
        }
      }
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
            NumberOfMonsters2--;
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
      }
      Monster OpponentMonster = Player2Monsters.begin()->second;
      CurrentMonster.OutputStats();
      OpponentMonster.OutputStats();
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
  int Choice;
  while (true) {
    cout<<"\nWhat would you like to do?\n1 - Display entire battle index\n2 - Search for a Monster in battle index"<<endl;
    cin>>Choice;
    ifstream TypingFile("BattleIndex.txt"); //opens battle index file 
    if (Choice == 1) {
      string line;
        ifstream BattleIndexFile("BattleIndex.txt");
        if (BattleIndexFile.is_open()) { //checks if battle index file is open
          while (getline(BattleIndexFile, line)) {  //while loop to read each line of the file
            cout <<line<< endl; 
          }
          BattleIndexFile.close(); //file is closed
        }
        else {
          cerr<<"File was unable to be opened!"; //error message if file is not open  
        }
        break;
      }
    else if (Choice == 2) {
      string Search,Line;
      ifstream TypingFile("BattleIndex.txt"); //opens battle index file
      cout<<"Enter the name of the monster you would like to search for!";
      cin>>Search;
      unsigned int curLine = 0;
      while(getline(TypingFile, Line)) {
          curLine++;
          if (Line.find(Search) != string::npos) {
              cout<<Line<<endl;
            }
          else {
            cout<<"Monster not found!"<<endl;
            }
        TypingFile.close();
        cout<<"Search Complete!";
        break;
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

void TypingInformation() { //function to display typing information from a text file 
  string line;
  ifstream TypingFile("TypingMatchups.txt"); //file is opened
  if (TypingFile.is_open()) { //checks if typing matchups file is open
    while (getline(TypingFile, line)) { //while loop to read each line of the file
      cout <<line<< endl; 
    }
    TypingFile.close(); //file is closed
  }
  else {
    cerr<<"File was unable to be opened!";  //error message if file is not open 
  }
}

int main() { //function for running main menu that displays all the options a user can choose from 
  int Userchoice;  
  while (true) {
    cout<<"\nWelcome to the monster battle simulator! what would you like to do?\n1 - Start a battle\n2 - Battle Index\n3 - Typing Information\n4 - Quit\n";
    cin>>Userchoice;
    if (Userchoice == 1) {
      cout<<"Start a battle has been selected!"<<endl;
      MonsterSelection(); //if user enters 1 then the function for selecting monsters for battles is run
    }
    else if (Userchoice == 2) {
      cout<<"Battle Index has been selected!"<<endl;
      BattleIndex(); //if user enters 2 then battle index function is run 
    }
    else if (Userchoice == 3) {
      cout<<"Typing information has been selected!"<<endl;
      TypingInformation(); //if user enters 3 then function for displaying information from typingmatchups text file is run
    }
    else if (Userchoice == 4) {
      cout<<"Exit has been selected program will now cease running!"<<endl;
      break; //this is the option for quitting the program it is the only option to stop the loop 
    }
    else if (cin.fail()) {
      cin.clear(); //clears the error flag input   
      cin.ignore(); //ignore the remaining input 
      cout<<"Invalid! Wrong data type!\n\n\n"<<endl; //error testing for if a user enters anything other than a number
    }
     
    else {
      cout<<"That is an invalid Number! Try again!\n\n\n"; //error tests if number is out of range 
    
    }
  }
  return 0;
}