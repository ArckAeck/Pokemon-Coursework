#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
#include "MonsterHeader.h"
using namespace std;
void DestroyMonster(map<int, Monster> &monsterMap, Monster &monster) { //removes monster from map
    for (auto it = monsterMap.begin(); it != monsterMap.end(); ++it) {
        if (it->second.GetName() == monster.GetName()) { 
            monsterMap.erase(it);
            return; 
        }
    }
}
void PlayerSwitchMonster(map<int, Monster> &Map, Monster &SelectedMonster) {
  int Input;
  while (true) {
    cout<<"Please select the monster you would like to switch your current monster to!"<<endl;
    for (auto& pair : Map) {
      cout<<pair.first<<" - "<<pair.second.GetName()<<endl; //Displays all monsters in map
        }
    cin>>Input;
    auto it=Map.find(Input);
    if (it != Map.end()) { //If name is in map but is currently selected
      if (it->second.GetName() == SelectedMonster.GetName()) { 
        cout<<"You already have this monster selected!"<<endl;
        continue;
      }
      SelectedMonster = it->second;
      cout<<"Player has switched monster to: "<<SelectedMonster.GetName()<<"\nCurrent Player Monster:"<<endl;
      SelectedMonster.OutputStats(); //If name is in map but isn't currently selected and currentmonster parameter is switched
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type entered! Try Again!\n";
      continue;
      //If wrong data type is entered error 
    }
    else {
      cout<<"Invalid monster number entered! Try again!\n";
      //if invalid number is entered for monster key
      continue;
    }
  }
  }
void BotSwitchMonster(map<int, Monster> &Map, Monster &SelectedMonster) {
  while (true) {
    int RandomNumber = GenerateNumber(1,Map.size());
    auto it=Map.find(RandomNumber);
    if (it != Map.end()) {
      if (it->second.GetName() == SelectedMonster.GetName()) {
        continue; //if random number generated key is equal to current monster key then try again
      }
      SelectedMonster = it->second;
      cout<<"Computer has switched monster to: "<<SelectedMonster.GetName()<<"\nCurrent Computer Monster:"<<endl;
      SelectedMonster.OutputStats(); //random number generated key is not equal to current monster key and currentmonster parameter is switched
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
    cout<<"What would you like to do?\n1 - Use a move\n2 - Switch current monster\nYour current monster statics"<<endl;
    Player.OutputStats(); //Users current monster selects what they want to do
    cin>>Input;
    if (Input == 1) {
      Player.Attack(Enemy,"Player");
      break; //if user selects 1 then player attacks enemy function is run
    }
    else if (Input == 2) {
      PlayerSwitchMonster(Map, Player);
      //if user selects 2 then player switches monster function is run
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type entered! Try Again!\n";
      //if user inputs wrong data type 
    }
    else {
      cout<<"Invalid number entered! Try again!\n";
      //user enters invalid number then error is displayed
    }
  }
  }
void BotBattleMenu(map<int, Monster> &Map,Monster &Bot, Monster &Enemy) {
  int RandomSelection = GenerateNumber(1,2);
  if (RandomSelection == 1) {
    Bot.Attack(Enemy,"Computer");
    //Bot randomly selects what it would like to do if 1 it chooses to attack
  }
  else {
    BotSwitchMonster(Map, Bot);
    //else just switches monster
  } 
}
void GameplayLoop(map<int, Monster> &PlayerTeam, Monster &Player,map<int, Monster> EnemyTeam, Monster &Enemy, string BattleType) {
  if (BattleType == "PVE") {
    //if battle is PVE then this is run
  while (true) {
    if (Player.GetSpeed() > Enemy.GetSpeed()) {
      cout<<"\nPlayer 1's speed is faster than computer so they have their turn!\n"<<endl;
      //whoever has fastest speed gets first turn
      PlayerBattleMenu(PlayerTeam,Player,Enemy);
      if (Enemy.IsAlive() == false) {
        cout<<Enemy.GetName()<<" has fainted!";
        //if enemy loses all their health
         DestroyMonster(EnemyTeam, Enemy);
        //Remove enemy from their map
        if (EnemyTeam.size() == 0) {
          cout<<"Player has won the battle!"; 
          //if enemy has no remaining monsters
          break;
        } 
        BotSwitchMonster(EnemyTeam, Enemy);  
        //now its the enemies turn
      }
      BotBattleMenu(EnemyTeam,Enemy,Player);  
      if (Player.IsAlive() == false) {
        cout<<Player.GetName()<<" has fainted!";
        //if player loses all their health
        DestroyMonster(PlayerTeam, Player);
        if (PlayerTeam.size() == 0) {
          //if player loses all their monsters computer wins
          cout<<"Computer has won the battle!";
          break;
        }
        /* ALL THE CODE BELOW USES THE SAME LOGIC AS THIS PART JUST FOR DIFFERENT OUTCOMES SO IS NOT COMMENTED*/
        PlayerSwitchMonster(PlayerTeam, Player);
        
      }
      else {
        continue;
          }
    }
    else {
      cout<<"\nComputer's speed is faster than player's so they have their turn!\n";
      BotBattleMenu(EnemyTeam,Enemy,Player); 
      if (Player.IsAlive() == false) {
        cout<<Player.GetName()<<" has fainted!";
        DestroyMonster(PlayerTeam, Player);
        if (PlayerTeam.size() == 0) {
          cout<<Player.GetName()<<"Computer has won the battle!"<<endl;
          break;
        }
        PlayerSwitchMonster(PlayerTeam, Player);
      }
      PlayerBattleMenu(PlayerTeam,Player,Enemy);
      if (Enemy.IsAlive() == false) {
        cout<<Enemy.GetName()<<" has fainted!";
        DestroyMonster(EnemyTeam, Enemy);
        if (EnemyTeam.size() == 0) {
          cout<<"Player has won the battle!"<<endl;
          break;
        }
        BotSwitchMonster(EnemyTeam, Enemy);
      } 
      else {
      continue;
      }   
    }
  }
}
  else {
    while (true) {
    if (Player.GetSpeed() > Enemy.GetSpeed()) {
      cout<<"\nPlayer 1's speed is faster than player 2 so they have their turn!";
      PlayerBattleMenu(PlayerTeam,Player,Enemy);
      if (Enemy.IsAlive() == false) {
        cout<<Enemy.GetName()<<" has fainted!";
        DestroyMonster(EnemyTeam, Enemy);
        if (EnemyTeam.size() == 0) {
          cout<<"Player has won the battle!"; 
           break;
        }
        PlayerSwitchMonster(EnemyTeam, Enemy);
      }
      PlayerBattleMenu(EnemyTeam,Enemy,Player);  
      if (Player.IsAlive() == false) {
        cout<<Player.GetName()<<" has fainted!";
        DestroyMonster(PlayerTeam, Player);
        if (PlayerTeam.size() == 0) {
          cout<<"Player 2 has won the battle!";
          break;
        }  
        PlayerSwitchMonster(PlayerTeam, Player);
      }
      else {
        continue;
      }
    }
      else {
        cout<<"\nPlayer 2's speed is faster than player 1's so they have their turn!";
        PlayerBattleMenu(EnemyTeam,Enemy,Player); 
        if (Player.IsAlive() == false)
          cout<<Player.GetName()<<" has fainted!";
          DestroyMonster(PlayerTeam, Player);
          if (PlayerTeam.size() == 0) {
            cout<<"Player 2 has won the battle!"<<endl;
            break;
          }
          PlayerSwitchMonster(PlayerTeam, Player);
        }
        PlayerBattleMenu(PlayerTeam,Player,Enemy);
        if (Enemy.IsAlive() == false) {
          cout<<Enemy.GetName()<<" has fainted!";
          DestroyMonster(EnemyTeam, Enemy);
          if (EnemyTeam.size() == 0) {
            cout<<"Player has won the battle!"<<endl;
            break;
          }
          PlayerSwitchMonster(EnemyTeam, Enemy);
        }
        else {
        continue;
        }
    }
  }
}
void MonsterSelection() {
  int NumberOfMonsters,NumberOfMonsters2,BattleType,SelectedMonster,Position = 1; 
  string MonsterTeam[] = {};
  map<int, Monster> MonsterList,Player1Monsters, Player2Monsters, BotMonsters; 
  MonsterList.insert(pair<int, Monster>(1,Pikacho)), MonsterList.insert(pair<int, Monster>(2,Charmanker)), MonsterList.insert(pair<int, Monster>(3,Dragonknight)), MonsterList.insert(pair<int, Monster>(4,Kingda)), MonsterList.insert(pair<int, Monster>(5,Drenchninja)), MonsterList.insert(pair<int, Monster>(6,Raygaza)), MonsterList.insert(pair<int, Monster>(7,Nyrados)),MonsterList.insert(pair<int, Monster>(8,Tentadrool)),MonsterList.insert(pair<int, Monster>(9,Electafuzz)),MonsterList.insert(pair<int, Monster>(10,Rapdos)),MonsterList.insert(pair<int, Monster>(11,Blaziben)),MonsterList.insert(pair<int, Monster>(12,Raixen)); // Monster objects are inserted into the MonsterList map alongside corresponding indentifying key numbers
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
      // Wrong data type entered
    }
    else {
      cout<<"Invalid Number of Monsters! Try Again!\n";
      // Number outside of range entered
    } 
  }
  NumberOfMonsters2 = NumberOfMonsters;
  cout<<"Here is the list of available monsters to choose:\n";
  
  while (NumberOfMonsters > 0) {
    for (auto& pair : MonsterList) {
      cout<<pair.first<<" - "<<pair.second.GetName()<<" Type: "<<pair.second.GetType()<<endl;
        }
    // Displays key,value from the map
    cout<<"Enter the number of the monster you'd like to choose! "<<NumberOfMonsters<<" choices remaining!"<<endl;
    cin>>SelectedMonster;
    auto it=MonsterList.find(SelectedMonster);
    if (it != MonsterList.end()) {
      NumberOfMonsters--;
      Player1Monsters.insert(pair<int, Monster>(Position,it->second));
      MonsterList.erase(SelectedMonster);
      Position++;
      // If key is valid then number of monsters left is decremented and monster is inserted into the player's map and the key is removed from monsterlist and its position is incremented
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Invalid! Please select the number for which monster you would like to select\n"<<endl;
      // Wrong data type entered
    }
    else {
      cout<<"That is not a valid Monster! Try Again!"<<endl;
      // Number outside of range entered
    }
    for (auto& pair : Player1Monsters) {
      cout<<"Player1 Monster: "<<pair.second.GetName()<<"\n"<<endl;
        }
    //Display Map
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
        int NewNumber = GenerateNumber(1,12);
        //Computer will randomly generate number in the range of keys and continue until equal to player map size
        auto it=MonsterList.find(NewNumber);
        if (it != MonsterList.end()) {
          BotMonsters.insert(pair<int, Monster>(EnemyNumber,it->second));
          MonsterList.erase(NewNumber);
          EnemySize++;
          EnemyNumber++;
          //key and value is inserted into bot map
          cout<<"CPU Monster picked: "<<NewNumber<<endl;
              
        } 
        else {
          continue;
          //It will continue to generate one until it finds one in the map
        } 
      }
      cout<<"The CPU Team has been selected here it is!\n"<<endl;
      for (auto& pair : BotMonsters) {
        cout<<"CPU Monster: "<<pair.second.GetName()<<"\n"<<endl;
          }
      //Displays CPU team
      Monster OpponentMonster = BotMonsters.begin()->second;
      cout<<"Player 1's starting monster is: "<<endl;
      CurrentMonster.OutputStats();
      cout<<"Computer's starting monster is: "<<endl;
      OpponentMonster.OutputStats();
      //Displays information on starting pokemon and runs gameplay function 
      GameplayLoop(Player1Monsters,CurrentMonster,BotMonsters,OpponentMonster,"PVE");   
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
            //Player 2 has the same selection process as player 1 inserted into their own map
            
          }
          else if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout<<"Invalid! Please select the number for which monster you would like to select\n"<<endl;
            //wrong data type entered
          }
          else {
            cout<<"That is not a valid Monster! Try Again!"<<endl;
            //Number outside range
          }
          for (auto& pair : Player2Monsters) {
            cout<<"Player2 Monster: "<<pair.second.GetName()<<"\n"<<endl;
              }
          //Display player 2 map
      }
      Monster OpponentMonster = Player2Monsters.begin()->second;
      cout<<"Player 1's starting monster is: "<<endl;
      CurrentMonster.OutputStats();
      cout<<"Player 2's starting monster is: "<<endl;
      OpponentMonster.OutputStats();
      //Dislay each starting monsters information and run gameplay loop 
      GameplayLoop(Player1Monsters,CurrentMonster,Player2Monsters,OpponentMonster,"PVP");
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Wrong data type! Try again!"<<endl;
      //wrong data type entered
    }
    else {
      cout<<"Invalid Battle Type! Try Again!"<<endl;
      //number outside range entered
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
      bool found = false;
      ifstream TypingFile("BattleIndex.txt"); //opens battle index file
      cout<<"Enter the name of the monster you would like to search for!";
      cin>>Search;
      unsigned int curLine = 0;
      while(getline(TypingFile, Line)) {
          curLine++;
          //Increment to the next line 
          if (Line.find(Search) != string::npos) {
              //If search is found output line
              cout<<Line<<endl;
              found = true;
              break;
            }
          else {
            continue;
          }
      }
      TypingFile.close();
      if (found == false) {
        cout<<"Sorry that monster could not be found";
        //If keyword is not found 
      }
      break;
    }
    else if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout<<"Invalid! Wrong data type!\n\n\n"<<endl;
      continue;
      //If invalid data type is entered
    }
    else {
      cout<<"Invalid Number! Try Again!\n\n\n"<<endl;
      //If number out of range is entered
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