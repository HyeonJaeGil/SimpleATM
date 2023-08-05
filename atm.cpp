#include "atm.h"
#include "bank.h"

// silence the output when running unit tests
#if BUILD_TEST
#define STREAM 0 && std::cout
#else
#define STREAM std::cerr
#endif

ATM::ATM(int balance) : balance_(balance) {
  bank_ = std::make_unique<Bank>();
  state_ = std::make_unique<State>(State::INITIAL);
  user_info_ = std::make_unique<UserInfo>();
}

bool ATM::insertCard(const std::string &card_number) {
  if (*state_ != State::INITIAL) {
    return false;
  }
  user_info_->card_number = card_number;
  *state_ = State::CARD_INSERTED;
  return true;
}

bool ATM::removeCard() {
  if (*state_ < State::CARD_INSERTED) {
    return false;
  }
  *state_ = State::INITIAL;
  user_info_.reset(new UserInfo());
  return true;
}

bool ATM::enterPIN(const int pin) {
  if (*state_ != State::CARD_INSERTED) {
    return false;
  }
  if (!bank_->checkPIN(user_info_->card_number, pin)) {
    STREAM << "PIN is incorrect." << std::endl;
    return false;
  }
  user_info_->pin = pin;
  *state_ = State::PIN_ENTERED;
  return true;
}

bool ATM::selectAccount(const int account) {
  if (*state_ < State::PIN_ENTERED) {
    return false;
  }
  user_info_->account = account;
  *state_ = State::ACCOUNT_SELECTED;
  return true;
}

int ATM::seeBalance() const {
  if (*state_ != State::ACCOUNT_SELECTED) {
    return -1;
  }
  return bank_->getAccountBalance(user_info_->card_number, user_info_->account);
}

bool ATM::deposit(int amount) {
  if (*state_ != State::ACCOUNT_SELECTED) {
    return false;
  }
  if (amount <= 0) {
    STREAM << "invalid deposit value." << std::endl;
    return false;
  }
  STREAM << "deposit " << amount << std::endl;
  balance_ += amount;
  return true;
}

bool ATM::withdraw(int amount) {
  if (*state_ != State::ACCOUNT_SELECTED) {
    return false;
  }
  if (amount <= 0) {
    STREAM << "invalid withdraw value." << std::endl;
    return false;
  }
  if (balance_ < amount) {
    STREAM << "not enough balance in ATM machine." << std::endl;
    return false;
  }
  if (bank_->getAccountBalance(user_info_->card_number, user_info_->account) < amount) {
    STREAM << "not enough balance in user's account." << std::endl;
    return false;
  }
  STREAM << "withdraw " << amount << std::endl;
  balance_ -= amount;
  return true;
}
