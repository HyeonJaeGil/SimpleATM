# Implementing a simple ATM controller

## How to build
tested on **Ubuntu 20.04 LTS**, both **local and docker** environment.

### Prerequisites
- install related packages
``` bash
sudo apt-get install cmake build-essential
```

### clone repository
``` bash
git clone https://github.com/HyeonJaeGil/SimpleATM.git
```

### Build and run unit tests
``` bash
cd /path/to/SimpleATM
mkdir build && cd build
cmake ..
make
./test_atm # run unit tests 
```

#### output
``` bash
$  ./test_atm 
[==========] Running 12 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 12 tests from AtmTest
[ RUN      ] AtmTest.MainWorkflow
[       OK ] AtmTest.MainWorkflow (0 ms)
[ RUN      ] AtmTest.InsertCardTwice
[       OK ] AtmTest.InsertCardTwice (0 ms)
[ RUN      ] AtmTest.enterPINSequentially
[       OK ] AtmTest.enterPINSequentially (0 ms)
[ RUN      ] AtmTest.enterPINTwice
[       OK ] AtmTest.enterPINTwice (0 ms)
[ RUN      ] AtmTest.selectAccountSequentially
[       OK ] AtmTest.selectAccountSequentially (0 ms)
[ RUN      ] AtmTest.selectAccountTwice
[       OK ] AtmTest.selectAccountTwice (0 ms)
[ RUN      ] AtmTest.seeBalanceSequentially
[       OK ] AtmTest.seeBalanceSequentially (0 ms)
[ RUN      ] AtmTest.depositSequentially
[       OK ] AtmTest.depositSequentially (0 ms)
[ RUN      ] AtmTest.withdrawSequentially
[       OK ] AtmTest.withdrawSequentially (0 ms)
[ RUN      ] AtmTest.withdrawInvalidAmount
[       OK ] AtmTest.withdrawInvalidAmount (0 ms)
[ RUN      ] AtmTest.depositInvalidAmount
[       OK ] AtmTest.depositInvalidAmount (0 ms)
[ RUN      ] AtmTest.RemoveCardTwice
[       OK ] AtmTest.RemoveCardTwice (0 ms)
[----------] 12 tests from AtmTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 12 tests.
```