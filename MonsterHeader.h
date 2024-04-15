#include <iostream>
#include <cmath>
#include <map>
using namespace std;
#pragma once
//Function to generate random Numbers within a range 
int GenerateNumber(short min, short max) {
  srand(time(0)); //Seeding the random number generator with time 
  short RanNum = (rand()%(max - min + 1)) + min; //Generating a random number within the range
  return RanNum;
}
class Monster {  //Create the monster class
  private:
    string Name;
    string Type;
    int Health;
    int Speed;
  public:
    Monster(string N, string T, int H, int S) { //Calling upon the monster class to keep attributes private but accessible by methods
      Name = N;
      Type = T;
      Health = H;
      Speed = S;
    }
    //Getter and setter methods for the monster class
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
    void SetHealth(int &NewHealth) {
      Health = NewHealth;
    }
    //Method for monster class to attack that is virtual so it is abstract and can be overwritten by the child classes
    virtual void Attack(Monster &Enemy,string Attacker) {
      int Damage;
      if (Attacker == "Computer") {
        Damage = GenerateNumber(1,10);
        Health =  Enemy.GetHealth() - Damage;
        cout << "The computer attacked you for " << Damage << " damage!" << endl;
        Enemy.SetHealth(Health);
        cout<<"Your health is now at"<<GetHealth();
        
      }
      else {
        Damage = GenerateNumber(1,10);
        Health =  Enemy.GetHealth() - Damage;
        Enemy.SetHealth(Health);
        cout<<"Enemy "<<Enemy.GetName()<<"'s health is now at "<<Enemy.GetHealth();   
        }
    }
    void OutputStats() {
      cout<<"\nName: "<<GetName()<<"\nType: "<<GetType()<<"\nHealth: "<<GetHealth()<<"\nSpeed: "<<GetSpeed()<<"\n"<<endl;
    }
 //Checks if monster is alive returns boolean
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
    FireMonster(string N, string T, int H, int S) : Monster(N, T, H, S) { //Constructor for the fire monster class uses the monster class constructor attributes for Firemonster
    }
    int CheckDamage(int PrevDamage, Monster &Enemy) {
      if (Enemy.GetType() == "Water") { 
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was not very effective!";
        //Uses enemy and damage as parameters to check an attacks effectiveness for typing advantages and disadvantages
        
      }
      else if (Enemy.GetType() == "Dragon") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was very effective!";
        //Uses enemy and damage as parameters to check an attacks effectiveness for typing advantages and disadvantages
      }
      return PrevDamage;
    }
    void Attack(Monster &Enemy,string attacker) override {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Flamethrower\n2 - Flame of Life\n3 - Blaze Kick"<<endl;
          cin>>AttackChoice;
          //Checks the type of attacker if it is a user the program will give them the choice to choose what they would like to do
          }
        else {
          AttackChoice = GenerateNumber(1,3);
          //If the attacker is the computer the program will choose a random attack
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Flamethrower"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          //Generates number for attack and checks typing advantages 
          cout<<"Flamethrower did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
          //New health is set for the enemy
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Flame of life"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          //has a 1 in 3 chance of occuring as some moves may not work every single time 
          if (ChanceOfHappening == 3) {
            cout<<"Flame of life was activated!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
            //This type of move heals rather than does damage to enemy and it is applied to users HP
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
          } 
          else {
            cout<<"Flame of life failed! "<<GetHealth()<< "'s Health remains the same";
            //Otherwise do nothing the move has failed
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Blaze Kick"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          if (ChanceOfHappening == 2) {
            //has a 1 in 2 chance of occuring as some moves may not work every single time 
            cout<<"Blaze Kick was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
          }      
          else {
            cout<<"Blaze Kick failed! "<<Enemy.GetName()<<"'s Health remains the same";
            //Otherwise do nothing the move has failed
          }
        }       
        else if (cin.fail()) {
          cin.clear();
          cin.ignore();
          cout<<"That is the wrong data type! Try again!\n";
          //Checks if data type entered is wrong console is cleared and leftover data stream is removed
        }
        else {
          cout<<"Invalid move number entered! Try again!\n";
          //Otherwise invalid number out of range was entered
        }
    }
  }
};
class WaterMonster : public Monster {
  public:
    WaterMonster(string N, string T, int H, int S) : Monster(N, T, H, S) { //Constructor for the water monster class uses the monster class constructor attributes for Firemonster
    }
    //Uses enemy and damage as parameters to check an attacks effectiveness for typing advantages and disadvantages
    int CheckDamage(int PrevDamage, Monster &Enemy) {
      if (Enemy.GetType() == "Fire") { 
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was very effective!";
      }
      else if (Enemy.GetType() == "Electric") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was not very effective!";
      }
      return PrevDamage;
    }
    void Attack(Monster &Enemy,string attacker) override {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        //Checks the type of attacker if it is a user the program will give them the choice to choose what they would like to do
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Water Gun\n2 - Flood\n3 - Splash"<<endl;
          cin>>AttackChoice;
          }
        else {
          AttackChoice = GenerateNumber(1,3);
          //If the attacker is the computer the program will choose a random attack
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Water Gun"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          //Generates number for attack and checks typing advantages 
          cout<<"Watergun "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
          //New health is set for the enemy
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Flood"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Flood worked!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
            //This type of move heals rather than does damage to enemy and it is applied to users HP
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
          } 
          else {
            cout<<"Flood failed! "<<GetHealth()<< "'s Health remains the same";
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Splash"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          //1 in 2 chance of occuring as some moves may not work every single time
          if (ChanceOfHappening == 2) {
            cout<<"Splash was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
            //New health is set for the enemy
          }      
          else {
            cout<<"Splash failed! "<<Enemy.GetName()<<"'s Health remains the same";
          }
        }       
        else if (cin.fail()) {
          cin.clear();
          cin.ignore();
          cout<<"That is the wrong data type! Try again!\n";
          //Checks if data type entered is wrong console is cleared and leftover data stream is removed
        }
        else {
          cout<<"Invalid move number entered! Try again!\n";
          //Otherwise invalid number out of range was entered
        }
    }
  }
};
class DragonMonster : public Monster {
  public:
    DragonMonster(string N, string T, int H, int S) : Monster(N, T, H, S) { //Constructor for the dragon monster class uses the monster class constructor attributes for Firemonster
    }
    //Uses enemy and damage as parameters to check an attacks effectiveness for typing advantages and disadvantages
    int CheckDamage(int PrevDamage, Monster &Enemy) {
      if (Enemy.GetType() == "Dragon") {
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was very effective!";
      }
      else if (Enemy.GetType() == "Fire") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was not very effective!";
      }
      return PrevDamage;
    }
    void Attack(Monster &Enemy,string attacker) override {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Gust\n2 - Sword of the Dragon\n3 - Dragonbeam"<<endl;
          cin>>AttackChoice;
          //Checks the type of attacker if it is a user the program will give them the choice to choose what they would like to do
          }
        else {
          AttackChoice = GenerateNumber(1,3);
          //If the attacker is the computer the program will choose a random attack
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Water Gun"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Watergun did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
          //New health is set for the enemy
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Sword of the Dragon"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          //has a 1 in 3 chance of occuring as some moves may not work every single time
          if (ChanceOfHappening == 3) {
            cout<<"Sword of the Dragon worked!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
          } 
          else {
            cout<<"Sword of the Dragon failed! "<<GetHealth()<< "'s Health remains the same";
            //Otherwise attack fails 
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Dragonbeam"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          //has a 1 in 2 chance of occuring as some moves may not work every single time
          if (ChanceOfHappening == 2) {
            cout<<"Dragonbeam was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
            //New health is set for the enemy
          
          }      
          else {
            cout<<"Dragonbeam failed! "<<Enemy.GetName()<<"'s Health remains the same";
            //Otherwise attack fails 
          }
        }       
        else if (cin.fail()) {
          cin.clear();
          cin.ignore();
          cout<<"That is the wrong data type! Try again!\n";
          //Checks if data type entered is wrong console is cleared and leftover data stream is removed
        }
        else {
          cout<<"Invalid move number entered! Try again!\n";
          //Otherwise invalid number out of range was entered
        }
    }
  }
};
class ElectricMonster : public Monster { //Constructor for the dragon monster class uses the monster class constructor attributes for Firemonster
  public:
    ElectricMonster(string N, string T, int H, int S) : Monster(N, T, H, S) {
    } //Uses enemy and damage as parameters to check an attacks effectiveness for typing advantages and disadvantages
    int CheckDamage(int PrevDamage, Monster &Enemy) {
      if (Enemy.GetType() == "Dragon") {
        PrevDamage /= GenerateNumber(2,3);
        cout<<"It was not very effective!";
      }
      else if (Enemy.GetType() == "Water") {
        PrevDamage *= GenerateNumber(2,3);
        cout<<"It was very effective!";
      }
      return PrevDamage;
    }
    void Attack(Monster &Enemy,string attacker) override {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Bolt\n2 - Spark\n3 - Thundershock"<<endl;
          cin>>AttackChoice;
          //Checks the type of attacker if it is a user the program will give them the choice to choose what they would like to do
          }
        else {
          AttackChoice = GenerateNumber(1,3);
          //If the attacker is the computer the program will choose a random attack
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Bolt"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          //Generates number for attack and checks typing advantages
          cout<<"Bolt did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
          //New health is set for the enemy
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Spark"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Spark worked!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
            //This type of move heals rather than does damage to enemy and it is applied to users HP
          } 
          else {
            cout<<"Spark failed! "<<GetHealth()<< "'s Health remains the same";
            //Otherwise attack fails
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Thundershock"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          //has a 1 in 2 chance of occuring as some moves may not work every single time
          if (ChanceOfHappening == 2) {
            cout<<"Thundershock was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
            //New health is set for the enemy
          }      
          else {
            cout<<"Thudershock failed! "<<Enemy.GetName()<<"'s Health remains the same";
            //otherwise attack fails 
          }
        }       
        else if (cin.fail()) {
          cin.clear();
          cin.ignore();
          cout<<"That is the wrong data type! Try again!\n";
          //Checks if data type entered is wrong console is cleared and leftover data stream is removed
        }
        else {
          cout<<"Invalid move number entered! Try again!\n";
          //Otherwise invalid number out of range was entered
        }
    }
  }
};

//Monster objects are created from each child class 
FireMonster Charmanker("Charmanker","Fire",95,15), Blaziben("Blaziben","Fire",120,120),Raixen("Raixen","Fire",130,130);
WaterMonster Drenchninja("Drenchninja","Water",110,45), Nyrados("Nyrados","Water",135,25),Tentadrool("Tentadrool","Water",100,140);
DragonMonster Dragonknight("Dragonknight","Dragon",130,50), Raygaza("Raygaza","Dragon",150,60), Kingda("Kingda","Dragon",120,105); 
ElectricMonster Pikacho("Pikacho","Electric",100,30),Rapdos("Rapdos","Electric",100,160), Electafuzz("Electafuzz","Electric",110,120); 