#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<string>> tokenise(vector<string> inputStrings) {
    vector<vector<string>> output;

    for (string input : inputStrings) {
        vector<string> subOutput;
        stringstream ss(input);
        string token;

        while (getline(ss, token, ',')) {
            size_t start = token.find_first_not_of(' ');
            size_t end = token.find_last_not_of(' ');
            token = token.substr(start, end - start + 1);

            stringstream token_ss(token);
            while (token_ss >> token) {
                subOutput.push_back(token);
            }
        }

        output.push_back(subOutput);
    }

    return output;
}

bool isR(int i, vector<vector<string>> tokens){
    if(tokens[i][0] == "add" || tokens[i][0] == "sub" || tokens[i][0] == "or" || tokens[i][0] == "and"){
        return true;
    }
    return false;
}

bool isLd( int i, vector<vector<string>> tokens){
    if(tokens[i][0] == "ld"){
        return true;
    }
    return false;
}

bool R_R(int i, int next, vector<vector<string>> tokens){
    if(isR(i, tokens) && isR(i, tokens) && (tokens[i][1]==tokens[next][2] || tokens[i][1]==tokens[next][3])){
        return true;
    }
    return false;

}

bool ld_R(int i, int next, vector<vector<string>> tokens){
    if(isLd(i, tokens) && isR(next, tokens) && (tokens[i][1]==tokens[next][2] || tokens[i][1]==tokens[next][3] ) ){
        return true;
    }
    
    return false;
}

bool R_Ld(int i, int next, vector<vector<string>> tokens){
    if(isR(i, tokens) && isLd(next, tokens)){
        string s1 = tokens[i][1];
        string s2 = tokens[next][2];
        size_t found = s2.find(s1);
        if (found != string::npos){
            return true;
        }
    }
    return false;
}

bool Ld_Ld(int i, int next, vector<vector<string>> tokens){
    if(isLd(i, tokens) && isLd(next, tokens)){
        string s1 = tokens[i][1];
        string s2 = tokens[next][2];
        size_t found = s2.find(s1);
        if (found != string::npos){
            return true;
        }
    }
    return false;
}

void case1(vector<string> strings){
    
    vector<vector<string>> tokens = tokenise(strings);
    
    int num;
    int count = 0;
    
    int n = strings.size();
    
    
    vector<int> marked(n, 0);
    
    for(int i =0; i<n; i++){
        if (!marked[i]){
            cout << strings[i] << endl;
            marked[i] = 1;
        }
       
        if((i+1<n) && 
        (R_R(i, i+1, tokens) || 
        ld_R(i, i+1, tokens) || 
        R_Ld(i, i+1, tokens)|| 
        Ld_Ld(i, i+1, tokens)
        )){
            num = 2;
            count += num;
            while(num>0){
                cout <<"nop"<<endl;
                num--;
            }
            cout << strings[i+1] << endl;
            marked[i+1] = 1;
            
        }

        if((i+2<n) && 
        ((ld_R(i, i+2, tokens) && !ld_R(i+1, i+2, tokens)) ||
        (R_R(i, i+2, tokens) && !R_R(i+1, i+2, tokens)) ||
        (R_Ld(i, i+2, tokens) && !R_Ld(i+1, i+2, tokens)) ||
        (Ld_Ld(i, i+2, tokens) && !Ld_Ld(i+1, i+2, tokens))
        )){
            num = 1;
            count += num;
            cout << strings[i+1] << endl;
            marked[i+1] = 1;
            while(num>0){
                cout <<"nop"<<endl;
                num--;
            }
            
            cout << strings[i+2] << endl;
            marked[i+2] = 1;
        }
        
    }
    
    int total_count = 5 + count + (n-1);

    cout << "Total:" << total_count << " cycles" << endl;

    return;
}

void case2(vector<string> strings){
    
    vector<vector<string>> tokens = tokenise(strings);
    int count = 0;
    int n = strings.size();
    
    vector<int> marked(n, 0);
    
    for(int i =0; i<n; i++){
        
        if (!marked[i]){
            cout << strings[i] << endl;
            marked[i] = 1;
        }
        
        if(ld_R(i, i+1, tokens) && i+1<n){
            cout << "nop" << endl;
            count++;
            cout << strings[i+1] << endl;
            marked[i+1] = 1;
        }
        
    }
    
    int total_count = 5 + count + (n-1);
    
    cout << "Total:" << total_count << " cycles" << endl;
    return;
}


int main() {
    vector<string> instructions; 
    string line;

    while (getline(cin, line) && !line.empty()) {
        instructions.push_back(line); 
    }
    
    cout << "Case(1): Assuming no data forwarding and no hazard detection is implemented" << endl;
    
    cout << "Case(2): Assuming that data forwarding without hazard detection is implemented" << endl;  
    
    cout << "Enter the case number:";
    
    int a;
    cin >> a;
    
    if(a ==1){
        case1(instructions);
    }
    else{
        case2(instructions);
    }
    
    return 0;
}



