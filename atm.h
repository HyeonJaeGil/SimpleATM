#pragma once
#include "bank.h"
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class ATM {
public:
  // manage the state with enum class
  enum class State { INITIAL = 0, CARD_INSERTED = 1, PIN_ENTERED = 2, ACCOUNT_SELECTED = 3 };

  struct UserInfo {
    string card_number;
    int pin;
    int account;
  };

  ATM(int balance = 1e5);
  ~ATM() = default;

  bool insertCard(const string &card_number);
  bool enterPIN(const int pin);
  bool selectAccount(const int account);
  int seeBalance() const;
  bool deposit(int amount);
  bool withdraw(int amount);
  bool removeCard();

private:
  unique_ptr<Bank> bank_;
  unique_ptr<State> state_;
  unique_ptr<UserInfo> user_info_;
  int balance_; // ATM's balance
};