#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    ostream_iterator<string> oo(cout);
    *oo = "Hi! \n";
    int x;
    cin >> x;
    *oo = "Bye!";
    return 0;
}
