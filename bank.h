#pragma once
#include <iostream>
#include <string>
using namespace std;

// Bank class is a mock class for the real bank
// It contains sample APIs for checking PIN and getting user's account balance
class Bank {
public:
  Bank() = default;
  ~Bank() = default;

  bool checkPIN(const string &card_number, const int pin) {
    // always return true for our test case
    if (card_number == "0123456789" && pin == 1234) {
      return true;
    }
    return false;
  }
  int getAccountBalance(const string &card_number, const int account) {
    // always return 1e3 for now
    return 1e3;
  }
};