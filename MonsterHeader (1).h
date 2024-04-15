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
    void Attack(Monster Enemy,string Attacker) {
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
    void Attack(Monster &Enemy) {
      int AttackChoice, HPChange, TypeDamage, ChanceOfHappening,Health;
      while (true) {
        cout<<"Here Are the Available Moves 1 - Flamethrower\n2 - Flame of Life\n3 - Blaze Kick"<<endl;
        cin>>AttackChoice;
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
    int CheckDamage(int PrevDamage, Monster &Enemy) {
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

//Monster objects are created
Monster Pikacho("Pikacho","Electric",100,30), Charmanker("Charmanker","Fire",95,15), Dragonknight("Dragonknight","Dragon",130,50), Daggron("Daggron","Rock",120,25), Drenchninja("Drenchninja","Water",110,45), Raygaza("Raygaza","Dragon",150,60),Nyrados("Nyrados","Water",135,25), Tentadrool("Tentadrool","Water",100,140), Electafuzz("Electafuzz","Electric",110,120), Rapdos("Rapdos","Electric",100,160), Blaziben("Blaziben","Fire",120,120),Raixen("Raixen","Fire",130,130);

