#include "TextBasedMenu.h"
#include<iostream>
#include<vector>

using namespace std;

int main(){
    MasterMenu menu;

    while (true){
        bool res = menu.operate();
        if (!res) break;
    }

    return 0;
}