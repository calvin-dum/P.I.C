#include <iostream>
#include <fstream>
using namespace std;





int main() {
ofstream test;
test.open("name.txt", ios::app);
if (test.is_open())
{
test << "Hello world \n";
test.close();
}
else cout << "unable to open text";


return 0;
}
