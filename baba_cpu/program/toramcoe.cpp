#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

string s;
FILE *fp;

void write(string line,char c) {
    string s0, s1, s2, s3;
    s0 += line[6];
    s0 += line[7];
    s1 += line[4];
    s1 += line[5];
    s2 += line[2];
    s2 += line[3];
    s3 += line[0];
    s3 += line[1];

    fp = freopen("ram0.coe", "a", stdout);
    cout << s0 << c << endl;
    fclose(fp);

    fp = freopen("ram1.coe", "a", stdout);
    cout << s1 << c << endl;
    fclose(fp);

    fp = freopen("ram2.coe", "a", stdout);
    cout << s2 << c << endl;
    fclose(fp);

    fp = freopen("ram3.coe", "a", stdout);
    cout << s3 << c << endl;
    fclose(fp);

}

int main() {
    freopen("/users/franky/desktop/crt.ram.txt", "r", stdin);
    string last_line=""; 
	string line;

    fp = freopen("ram0.coe", "w", stdout);
    cout << "memory_initialization_radix=16;" << endl;
    cout << "memory_initialization_vector=" << endl;
    fclose(fp);


    fp = freopen("ram1.coe", "w", stdout);
    cout << "memory_initialization_radix=16;" << endl;
    cout << "memory_initialization_vector=" << endl;
    fclose(fp);

    fp = freopen("ram2.coe", "w", stdout);
    cout << "memory_initialization_radix=16;" << endl;
    cout << "memory_initialization_vector=" << endl;
    fclose(fp);

    fp = freopen("ram3.coe", "w", stdout);
    cout << "memory_initialization_radix=16;" << endl;
    cout << "memory_initialization_vector=" << endl;
    fclose(fp);

    while(cin >> line) {

        if(line.length() != 8) {
            return -1;
        }
        if(last_line!="") write(last_line,',');
        last_line = line;
    }
	write(last_line,';');
	return 0;

}
