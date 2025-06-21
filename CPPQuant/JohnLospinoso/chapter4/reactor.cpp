#include <cstdio>


struct NuclearReactor {
    static int heat;
    static int currentPower;

    static void powerUp(int power) {
        currentPower += power;

        if (currentPower > 2000)
        if (heat > 1000) {
            printf("Too hot");
        }
    }

};

int NuclearReactor::currentPower = 0;


int main() {
    NuclearReactor::powerUp(2000);
}
