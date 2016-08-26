// http://www.cs.cmu.edu/~cburch/survey/recurse/hanoiimpl.html
#include <cstdio>

// tower recursively prints instructions for moving disks from source peg to destination peg using spare peg for spare storage
void tower(int numOfRings, int source, int destination, int spare)
{
    if (numOfRings == 1) {
        printf("%d --> %d\n", source, destination);
        return;
    }

    tower(numOfRings - 1, source, spare, destination); // move c - 1 disks from source to spare /

    printf("%d --> %d\n", source, destination); // move last disk from source to destination

    tower(numOfRings - 1, spare, destination, source); // move c - 1 disks from spare to destination
}

int main(void)
{
    int n = 0; // number of disks
    printf("Enter the starting number of disks: ");
    scanf("%d", &n);
    // print instructions for moving disks from peg 1 to peg 3 using peg 2 for spare storage
    tower(n, 1, 3, 2);
}
