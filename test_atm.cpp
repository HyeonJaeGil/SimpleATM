#include "atm.h"
#include <gtest/gtest.h>

class User {
public:
  User(std::string card_number, int pin, int account)
      : card_number_(card_number), pin_(pin), account_(account) {}
  ~User() = default;

  std::string getCardNumber() const { return card_number_; }
  int getPIN() const { return pin_; }
  int getAccount() const { return account_; }

private:
  std::string card_number_;
  int pin_;
  int account_;
};

class AtmTest : public ::testing::Test {
protected:
  AtmTest() : user("0123456789", 1234, 1), atm(1e5) {}

  User user;
  ATM atm;
};

TEST_F(AtmTest, MainWorkflow) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.seeBalance());
  ASSERT_TRUE(atm.deposit(1));
  ASSERT_TRUE(atm.withdraw(1));
  ASSERT_TRUE(atm.removeCard());
}

TEST_F(AtmTest, InsertCardTwice) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_FALSE(atm.insertCard(user.getCardNumber()));
}

TEST_F(AtmTest, enterPINSequentially) {
  ASSERT_FALSE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
}

TEST_F(AtmTest, enterPINTwice) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_FALSE(atm.enterPIN(1111)); // wrong PIN
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_FALSE(atm.enterPIN(user.getPIN())); // already entered
}

TEST_F(AtmTest, selectAccountSequentially) {
  ASSERT_FALSE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_FALSE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
}

TEST_F(AtmTest, selectAccountTwice) { // ok to select account twice
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
}

TEST_F(AtmTest, seeBalanceSequentially) {
  ASSERT_EQ(atm.seeBalance(), -1);
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_EQ(atm.seeBalance(), -1);
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_EQ(atm.seeBalance(), -1);
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_GE(atm.seeBalance(), 0);
}

TEST_F(AtmTest, depositSequentially) {
  ASSERT_FALSE(atm.deposit(1));
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_FALSE(atm.deposit(1));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_FALSE(atm.deposit(1));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.deposit(1));
  ASSERT_TRUE(atm.deposit(1));
}

TEST_F(AtmTest, withdrawSequentially) {
  ASSERT_FALSE(atm.withdraw(1));
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_FALSE(atm.withdraw(1));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_FALSE(atm.withdraw(1));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_TRUE(atm.withdraw(1));
  ASSERT_TRUE(atm.withdraw(1));
}

TEST_F(AtmTest, withdrawInvalidAmount) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_FALSE(atm.withdraw(1e6));
  ASSERT_FALSE(atm.withdraw(-1));
}

TEST_F(AtmTest, depositInvalidAmount) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.enterPIN(user.getPIN()));
  ASSERT_TRUE(atm.selectAccount(user.getAccount()));
  ASSERT_FALSE(atm.deposit(-1));
}

TEST_F(AtmTest, RemoveCardTwice) {
  ASSERT_TRUE(atm.insertCard(user.getCardNumber()));
  ASSERT_TRUE(atm.removeCard());
  ASSERT_FALSE(atm.removeCard());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}