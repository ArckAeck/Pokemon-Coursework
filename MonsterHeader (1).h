#include <iostream>
#include <cmath>
#include <map>
using namespace std;
#pragma once
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
    void SetHealth(int &NewHealth) {
      Health = NewHealth;
    }
    virtual void Attack(Monster &Enemy,string Attacker) {
      int Damage;
      if (Attacker == "Computer") {
        int Damage = GenerateNumber(1,10);
        cout << "The computer attacked you for " << Damage << " damage!" << endl;
      }
      else {
      Damage = Enemy.GetHealth() - GenerateNumber(1, 10);
      Enemy.SetHealth(Damage);
      cout<<"Enemy "<<Enemy.GetName()<<"'s health is now at "<<Enemy.GetHealth();   
      }
    }
    void OutputStats() {
      cout<<"\nName: "<<GetName()<<"\nType: "<<GetType()<<"\nHealth: "<<GetHealth()<<"\nSpeed: "<<GetSpeed()<<"\n"<<endl;
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
    FireMonster(string N, string T, int H, int S) : Monster(N, T, H, S) {
    }
    int CheckDamage(int PrevDamage, Monster &Enemy) {
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
    void Attack(Monster &Enemy,string attacker) override {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Flamethrower\n2 - Flame of Life\n3 - Blaze Kick"<<endl;
          cin>>AttackChoice;
          }
        else {
          AttackChoice = GenerateNumber(1,3);
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Flamethrower"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Flamethrower did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Flame of life"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Flame of life was activated!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
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
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
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
    WaterMonster(string N, string T, int H, int S) : Monster(N, T, H, S) {
    }
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
        if (attacker == "Player") {
          cout<<"Here Are the Available Moves 1 - Water Gun\n2 - Flood\n3 - Splash"<<endl;
          cin>>AttackChoice;
          }
        else {
          AttackChoice = GenerateNumber(1,3);
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Water Gun"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Watergun "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Flood"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Flood worked!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
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
          if (ChanceOfHappening == 2) {
            cout<<"Splash was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
          }      
          else {
            cout<<"Splash failed! "<<Enemy.GetName()<<"'s Health remains the same";
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
class DragonMonster : public Monster {
  public:
    DragonMonster(string N, string T, int H, int S) : Monster(N, T, H, S) {
    }
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
          }
        else {
          AttackChoice = GenerateNumber(1,3);
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Water Gun"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Watergun did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
        }
        else if (AttackChoice == 2) {
          cout<<GetName()<<" Used Sword of the Dragon"<<endl;
          HPChange = GenerateNumber(20,100);
          ChanceOfHappening = GenerateNumber(1,3);
          if (ChanceOfHappening == 3) {
            cout<<"Sword of the Dragon worked!"<<endl;
            Health = GetHealth() + HPChange;
            SetHealth(Health);
            cout<<GetName()<<"'s Health is now "<<GetHealth()<<endl;
          } 
          else {
            cout<<"Sword of the Dragon failed! "<<GetHealth()<< "'s Health remains the same";
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Dragonbeam"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          if (ChanceOfHappening == 2) {
            cout<<"Dragonbeam was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
          }      
          else {
            cout<<"Dragonbeam failed! "<<Enemy.GetName()<<"'s Health remains the same";
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
class ElectricMonster : public Monster {
  public:
    ElectricMonster(string N, string T, int H, int S) : Monster(N, T, H, S) {
    }
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
          }
        else {
          AttackChoice = GenerateNumber(1,3);
        }
        if (AttackChoice == 1) {
          cout<<GetName()<<" Used Bolt"<<endl;
          HPChange = GenerateNumber(30,45);
          TypeDamage = CheckDamage(HPChange, Enemy);
          cout<<"Bolt did "<<TypeDamage<<"\n"<<Enemy.GetName()<<"'s Health is now"<<Enemy.GetHealth();
          Health = Enemy.GetHealth() - TypeDamage;
          Enemy.SetHealth(Health);
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
          } 
          else {
            cout<<"Spark failed! "<<GetHealth()<< "'s Health remains the same";
          }
        }
        else if (AttackChoice == 3) {
          cout<<GetName()<<" Used Thundershock"<<endl;
          HPChange = GenerateNumber(75,100);
          ChanceOfHappening = GenerateNumber(1,2);
          if (ChanceOfHappening == 2) {
            cout<<"Thundershock was activated!"<<endl;
            Health = Enemy.GetHealth() + HPChange;
            Enemy.SetHealth(Health);
            cout<<Enemy.GetName()<<"'s Health is now "<<Enemy.GetHealth()<<endl;
          }      
          else {
            cout<<"Thudershock failed! "<<Enemy.GetName()<<"'s Health remains the same";
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

//Monster objects are created
FireMonster Charmanker("Charmanker","Fire",95,15), Blaziben("Blaziben","Fire",120,120),Raixen("Raixen","Fire",130,130);
WaterMonster Drenchninja("Drenchninja","Water",110,45), Nyrados("Nyrados","Water",135,25),Tentadrool("Tentadrool","Water",100,140);
DragonMonster Dragonknight("Dragonknight","Dragon",130,50), Raygaza("Raygaza","Dragon",150,60), Kingda("Kingda","Dragon",120,105); 
ElectricMonster Pikacho("Pikacho","Electric",100,30),Rapdos("Rapdos","Electric",100,160), Electafuzz("Electafuzz","Electric",110,120); 

