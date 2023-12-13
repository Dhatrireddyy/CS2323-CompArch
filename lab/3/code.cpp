#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

string hexadecimalToBinary(string str){
    string ans;

    for(int i=0; i<str.length(); i++){
        switch(str[i]){
            case '0': ans += "0000";
            break;
            case '1': ans += "0001"; 
            break;
            case '2': ans += "0010";
            break;
            case '3': ans += "0011"; 
            break;
            case '4': ans += "0100"; 
            break;
            case '5': ans += "0101"; 
            break;
            case '6': ans += "0110"; 
            break;
            case '7': ans += "0111"; 
            break;
            case '8': ans += "1000"; 
            break;
            case '9': ans += "1001";
            break;
            case 'a': case 'A': ans += "1010"; 
            break;
            case 'b': case 'B': ans += "1011"; 
            break;
            case 'c': case 'C': ans += "1100"; 
            break;
            case 'd': case 'D': ans += "1101"; 
            break;
            case 'e': case 'E': ans += "1110"; 
            break;
            case 'f': case 'F': ans += "1111"; 
            break;
        }
    }

    return ans;
}

int binaryToDecimal(string str) {
    int decimal = 0;
    int base = 1;

    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

int twoscomplementToDecimal(string str){
    if (str[0] == '0'){
        return binaryToDecimal(str);
    }
    else if(str[0] == '1'){
        string inv_str = "";
        for(int i =0; i<str.length(); i++){
            if(str[i] == '0'){
                inv_str += "1";
            }
            else if(str[i] == '1'){
                inv_str += "0";
            }
        }
        int ans = binaryToDecimal(inv_str);
        return -1*(ans +1);
    }
}

string binaryToHexa(string str){

    string ans;

    int i =0;
    while (i < str.length()) {
        string substring = str.substr(i, 4);

        if (substring == "0000") ans += '0';
        else if (substring == "0001") ans += '1';
        else if (substring == "0010") ans += '2';
        else if (substring == "0011") ans += '3';
        else if (substring == "0100") ans += '4';
        else if (substring == "0101") ans += '5';
        else if (substring == "0110") ans += '6';
        else if (substring == "0111") ans += '7';
        else if (substring == "1000") ans += '8';
        else if (substring == "1001") ans += '9';
        else if (substring == "1010") ans += 'a';
        else if (substring == "1011") ans += 'b';
        else if (substring == "1100") ans += 'c';
        else if (substring == "1101") ans += 'd';
        else if (substring == "1110") ans += 'e';
        else if (substring == "1111") ans += 'f';

        i += 4;
    }

    return ans;
}

void decoder(vector<string> inputs){
    
    for(int i =0; i<inputs.size(); i++){
        string hex_str = inputs[i];
        string str = hexadecimalToBinary(hex_str);
        
        string opcode = str.substr(25, 7);
        string operation = "";
        
        //R-format
        if(opcode == "0110011"){
            string funct7 = str.substr(0, 7);
            string rs2 = str.substr(7, 5);
            string rs1 = str.substr(12, 5);
            string funct3 = str.substr(17, 3);
            string rd = str.substr(20, 5);
            
            int reg = binaryToDecimal(rd);
            int reg1 = binaryToDecimal(rs1);
            int reg2 = binaryToDecimal(rs2);
            
            if (funct7 == "0000000" and funct3 == "000"){
                operation = "add";
            }
            else if (funct7 == "0100000" and funct3 == "000")
            {
                operation = "sub";
            }
            else if (funct7 == "0000000" and funct3 == "100")
            {
                operation = "xor";
            }
            else if(funct7 == "0000000" and funct3 == "110")
            {
                operation = "or";
            }
            else if(funct7 == "0000000" and funct3 == "111"){
                operation = "and";
            }
            else if(funct7 == "0000000" and funct3 == "001"){
                operation = "sll";
            }
            else if(funct7 == "0000000" and funct3 == "101"){
                operation = "srl";
            }
            else if(funct7 == "0100000" and funct3 == "101"){
                operation = "sra"; 
            }
            
            string ans = operation + " x" + to_string(reg) + ", x" + to_string(reg1) + ", x" + to_string(reg2);
            
            cout << ans << endl;
        }
        
        //I-Format
        else if(opcode == "0010011" or opcode == "0000011" or opcode == "1100111"){
            
            string imm = str.substr(0, 12);
            string rs1 = str.substr(12, 5);
            string funct3 = str.substr(17, 3);
            string rd = str.substr(20, 5);
            
            int reg = binaryToDecimal(rd);
            int reg1 = binaryToDecimal(rs1);
            
            int imm_value =  twoscomplementToDecimal(imm);
            
            string funct7 = imm.substr(0, 6);
            reverse(funct7.begin(), funct7.end());
            
            if(opcode == "0010011"){
                
                if (funct3 == "000"){
                    operation = "addi";
                }
                else if (funct3 == "100"){
                    operation = "xori";
                }
                else if (funct3 == "110"){
                    operation = "ori";
                }
                else if (funct3 == "111"){
                    operation = "andi";
                }
                else if (funct3 == "001" and binaryToDecimal(funct7) == 0){
                    operation = "slli";
                    string temp = imm.substr(6, 7);
                    imm_value = binaryToDecimal(temp);
                }
                else if (funct3 == "101" and binaryToDecimal(funct7) == 0){
                    operation = "srli";
                    string temp = imm.substr(6, 7);
                    imm_value = binaryToDecimal(temp);
                } 
                else if(funct3 == "101" and binaryToDecimal(funct7) != 0){
                    operation = "srai";
                    string temp = imm.substr(6, 7);
                    imm_value = binaryToDecimal(temp);
                    
                }
                
                string ans = operation + " x" + to_string(reg) + ", x" + to_string(reg1) + ", " + to_string(imm_value);
                
                cout << ans << endl;
            }
            
            else if(opcode == "0000011"){
                
                if (funct3 == "000"){
                    operation = "lb";
                }
                else if (funct3 == "001"){
                    operation = "lh";
                }
                else if (funct3 == "010"){
                    operation = "lw";
                }
                else if (funct3 == "011"){
                    operation = "ld";
                }
                else if (funct3 == "100"){
                    operation = "lbu";
                }
                else if (funct3 == "101"){
                    operation = "lhu";
                }     
                else if(funct3 == "110"){
                    operation = "lwu";
                }
                
                string ans = operation + " x" + to_string(reg) + "," + to_string(imm_value) + "(x" +  to_string(reg1) + ")";
                cout << ans << endl;
            }
            
            else if(opcode == "1100111"){

                operation = "jalr";
                    
                string ans = operation + " x" + to_string(reg) + ", x" + to_string(reg1) + "," + to_string(imm_value);
                    
                cout << ans << endl;
                
            }
            
            
        }
        
        //S-format
        else if (opcode == "0100011"){
            string imm1 = str.substr(0, 7);
            string rs2 = str.substr(7, 5);
            string rs1 = str.substr(12, 5);
            string funct3 = str.substr(17, 3);
            string imm2 = str.substr(20, 5);
            string imm = imm1 + imm2;

            int imm_value = twoscomplementToDecimal(imm);

            int reg1 = binaryToDecimal(rs1);
            int reg2 = binaryToDecimal(rs2);
            
            if (funct3 == "000"){
                operation = "sb";
            }
            else if (funct3 == "001"){
                operation = "sh";
            }
            else if (funct3 == "010"){
                operation = "sw";
            }
            else if (funct3 == "011"){
                operation = "sd";
            }
            
            string ans = operation + " x" + to_string(reg2) + "," + to_string(imm_value) + "(x" + to_string(reg1) + ")";
            
            cout << ans << endl;
        }
        
        //B- Format
        else if(opcode == "1100011"){
            string imm1 = str.substr(0, 1);
            string imm2 = str.substr(1, 6);
            string rs2 = str.substr(7, 5);
            string rs1 = str.substr(12, 5);
            string funct3 = str.substr(17, 3);
            string imm3 = str.substr(20, 4);
            string imm4 = str.substr(24, 1);
            
            string imm = imm1 + imm4 + imm2 + imm3 + '0';
            
            int reg1 = binaryToDecimal(rs1);
            int reg2 = binaryToDecimal(rs2);
            
            int imm_value = twoscomplementToDecimal(imm);
            
            if (funct3 == "000"){
                operation = "beq";
            }
            else if (funct3 == "001"){
                operation = "bne";
            }
            else if (funct3 == "100"){
                operation = "blt";
            }
            else if (funct3 == "101"){
                operation = "bge";
            } 
            else if (funct3 == "110"){
                operation = "bltu";
            } 
            else if (funct3 == "111"){
                operation = "bgeu";
            } 
            
            string ans = operation + " x" + to_string(reg1) + ", x" + to_string(reg2) + ", " + to_string(imm_value);
            
            cout << ans << endl;
        }
        //J-Format
        else if(opcode == "1101111"){

            string temp = str.substr(0, 20);

            string rd = str.substr(20, 5);

            string imm1 = temp.substr(0, 1);
            string imm2 = temp.substr(1, 10);
            string imm3 = temp.substr(11, 1);
            string imm4 = temp.substr(12, 8);

            string imm = imm1 + imm4 + imm3 + imm2 + '0';
            
            int reg = binaryToDecimal(rd);
            int imm_value = twoscomplementToDecimal(imm);
            
            operation = "jal";
            
            string ans = operation + " x" + to_string(reg) + "," + to_string(imm_value);
            
            cout << ans << endl;
        }
        
        // U-Format
        else if (opcode == "0110111"){
            
            string imm = str.substr(0, 20);
            string rd = str.substr(20, 5);
            
            int reg = binaryToDecimal(rd);
            
            string imm_value =  binaryToHexa(imm);
            
            operation = "lui";
            
            string ans = operation + " x" + to_string(reg) + ", 0x" + imm_value;
            
            cout << ans << endl;
            
        }
    }
    return;
}

int main() {
    
    vector<string> input;

    string values[] = {"007201b3", "00720863", "00c0006f", "00533623", "100004b7", "00c50493"};
    
    // Uncomment the following line to use the second set of input values
    // string values[] = {"fd3b0793", "00947bb3", "0eb14863", "fd30b523", "87dfd1ef"};
    
    // Uncomment the following line to use the third set of input values
    // string values[] = {"4020d193", "0020d193", "00209193", "0070c183", "00c0a183", "0011e263"};

    for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        input.push_back(values[i]);
    }
    
    decoder(input);
    
    return 0;
}