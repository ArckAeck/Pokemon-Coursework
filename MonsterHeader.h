#include <iostream>
#include <cmath>
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
    void SetHealth(int NewHealth) {
      Health = NewHealth;
    }
    void Attack(Monster Enemy) {
      string input;
      Enemy.SetHealth(Enemy.GetHealth() - GenerateNumber(1, 10));
      cout<<"Enemy "<<Enemy.GetName()<<"'s health is now at "<<Enemy.GetHealth();
      cin>>input;    
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
//Monster objects are created
Monster Pikacho("Pikacho","Electric",100,30), Charmanker("Charmanker","Fire",95,15), Dragonknight("Dragonknight","Dragon",130,50), Daggron("Daggron","Rock",120,25), Drenchninja("Drenchninja","Water",110,45), Raygaza("Raygaza","Dragon",150,60),Nyrados("Nyrados","Water",135,25), Tentadrool("Tentadrool","Water",100,140), Electafuzz("Electafuzz","Electric",110,120), Rapdos("Rapdos","Electric",100,160), Blaziben("Blaziben","Fire",120,120),Raixen("Raixen","Fire",130,130);