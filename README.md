# plivocpp
PlivoCPP

## Install ##
make

sudo make install

## Compile ##
g++ -std=c++11 test.cpp -o test -lplivocpp `pkg-config --libs --cflags curlpp`

## Sample Program ##
```
#include <plivocpp/PlivoAPI.hpp>

int main(void){
    std::string id = "...";
    std::string token = "...";

    plivo::PlivoAPI api(id, token);

    api.sendMessage("123456789012","123456789012","Teste");

    return 0;
}
```
