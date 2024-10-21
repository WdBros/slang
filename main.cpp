#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <iostream>

using std::string;
using std::vector;
using std::map;
using std::find_if; using std::find_if_not;

using std::cout; using std::cin; using std::endl;

typedef vector<string> program;
typedef map<string, void (*)()> program_relations;
typedef map<string, program::const_iterator> label_collection;

int reg = 0;
int val = 0;
string lab = "";
vector<string>::const_iterator cur;

map<string, program::const_iterator> labels;
map<string, void (*)()> relations;
vector<string> p;
vector<string>::const_iterator program_end;

bool is_label(const string& val) {
    return val[0] == ':';
}

void say() {
    cout << (char) reg;
}

void bre() {
    cout << endl;
}

void sto() {
    // cout << "Storing " << val << "!" << endl;
    reg = val;
}

void add() {
    reg = reg + val;
}

void sub() {
    reg = reg - val;
}

void mul() {
    reg = reg * val;
}

void div() {
    reg = reg / val;
}

void ifl() {
    if (reg < val) cur = labels[lab];
}

void ifg() {
    if (reg > val) cur = labels[lab];
}

void ife() {
    if (reg == val) cur = labels[lab];
}

bool space(char c) {
    return isspace(c);
}

bool not_space(char c) {
    return !isspace(c);
}

vector<string> split(const string& input) {
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = input.begin();
    while (i != input.end()) {
        i = find_if(i, input.end(), not_space);

        iter j = find_if(i, input.end(), space);

        if (i != input.end()) {
            ret.push_back(string(i, j));
        }
        i = j;
    }
    return ret;
}

void read_program(std::istream& fin) {
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) p.push_back(line);
    }
    program_end = p.end();
}

void initialize_rules() {
    relations["say"] = say;
    relations["bre"] = bre;
    relations["sto"] = sto;
    relations["add"] = add;
    relations["sub"] = sub;
    relations["mul"] = mul;
    relations["div"] = div;
    relations["ifl"] = ifl;
    relations["ifg"] = ifg;
    relations["ife"] = ife;
}

void execute_program() {
    cur = p.begin();
    
    while (cur != p.end()) {
        if (is_label(*cur)) {
            labels[*cur] = cur;
        }
        cur++;
    }
    
    cur = p.begin();

    while (cur != p.end()) {
        if (is_label(*cur)) { cur++; continue; }

        vector<string> line = split(*cur);
        if (line.size() >= 3) {
            lab = line[2];
        }
        if (line.size() >= 2) {
            val = std::stoi(line[1]);
        }
        relations[line[0]]();
        // cout << "We here." << endl;

        cur++;
    }
}

int main() {
    // if (argc < 1) {
    //     cout << "No argument provided." << endl;
    //     return 1;
    // }

    read_program(cin);
    initialize_rules();
    execute_program();

    return 0;
}
