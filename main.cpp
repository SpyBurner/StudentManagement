#include "University.h"

int main(int argc, char const *argv[]) {

    University uni;

    while (true) {
        bool work = uni.operate();
        if (!work)
            break;
    }

    return 0;
}
