
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int SIZE_OF_CACHE = 128;
int BLOCK_SIZE = 16;
int ASSOCIATIVITY = 1;
string REPLACEMENT_POLICY = "FIFO";
string WRITEBACK_POLICY = "WB";

vector<vector<int>> cacheSets(SIZE_OF_CACHE / BLOCK_SIZE, vector<int>(ASSOCIATIVITY));
vector<queue<int>> lruQueue(SIZE_OF_CACHE / BLOCK_SIZE);

void cacheAccess(string mode, int address){
    
    int bitsForSetIndex = log2(SIZE_OF_CACHE/BLOCK_SIZE);
    int bitsForBlockOffset = log2(BLOCK_SIZE);
    int bitsForTag = 32 - (bitsForSetIndex + bitsForBlockOffset);
    
    int setIndex = (address >> bitsForBlockOffset) & ((1 << bitsForSetIndex) - 1);
    
    int tag = (address >> (bitsForSetIndex + bitsForBlockOffset)) & ((1 << bitsForTag) - 1);
    
    cout << "Address: 0x" << hex << address;
    
    bool cacheHit = false;
    
    if(ASSOCIATIVITY != 0){
        cout << ", Set: 0x" << hex << setIndex;
        for (int i = 0; i < ASSOCIATIVITY; i++) {
            if (cacheSets[setIndex][i] == tag) {
                cacheHit = true;
                
                if (REPLACEMENT_POLICY == "LRU"){
                    queue<int> tempQueue;
                    while (!lruQueue[setIndex].empty()){
                        int currentTag = lruQueue[setIndex].front();
                        lruQueue[setIndex].pop();
                        if (currentTag != tag){
                            tempQueue.push(currentTag);
                        }
                    }
                    lruQueue[setIndex] = tempQueue;
                    lruQueue[setIndex].push(tag);
                    
                }
                
                break;
            }
            
        }
    }
    
    else{
        int bitsForBlockOffset = log2(BLOCK_SIZE);
        int bitsForTag = 32 - bitsForBlockOffset;
    
        int tag = (address >> bitsForBlockOffset) & ((1 << bitsForTag) - 1);
    
    }

    
    if(WRITEBACK_POLICY == "WT"){
        if( mode == "R"){
            if (cacheHit){
                cout << ", Hit, ";
            }
            
            else{
                cout << ", Miss, ";
                if (cacheSets[setIndex].size() == ASSOCIATIVITY){
                    if (REPLACEMENT_POLICY == "FIFO"){
                        cacheSets[setIndex].erase(cacheSets[setIndex].begin());
                        cacheSets[setIndex].push_back(tag);
                    }
                    else if(REPLACEMENT_POLICY == "RANDOM"){
                        int randomIndex = rand() % ASSOCIATIVITY;
                        cacheSets[setIndex][randomIndex] = tag;
                    }
                    else if(REPLACEMENT_POLICY == "LRU"){
                        
                        int LRTag = lruQueue[setIndex].front();
                        lruQueue[setIndex].pop();
                        
                        auto it = find(cacheSets[setIndex].begin(), cacheSets[setIndex].end(), LRTag);
                        
                        int position = distance(cacheSets[setIndex].begin(), it);
                        cacheSets[setIndex].erase(it);
                        cacheSets[setIndex][position] = tag;
                        
                        lruQueue[setIndex].push(tag);
  
                    }
                }
                else{
                    cacheSets[setIndex].push_back(tag);
                    if (REPLACEMENT_POLICY == "LRU"){
                        lruQueue[setIndex].push(tag);
                    }
                }
                
            }
        }
        
        if( mode == "W"){
            if (cacheHit){
                cout << ", Hit, ";
            }
            else{
                cout << ", Miss, ";
            }
        }
        
    }
    else if (WRITEBACK_POLICY == "WB"){
        if( mode == "R" || mode == "W"){
            if (cacheHit){
                cout << ", Hit, ";
            }
            
            else{
                cout << ", Miss, ";
                if (cacheSets[setIndex].size() == ASSOCIATIVITY){
                    if (REPLACEMENT_POLICY == "FIFO"){
                        cacheSets[setIndex].erase(cacheSets[setIndex].begin());
                        cacheSets[setIndex].push_back(tag);
                    }
                    else if(REPLACEMENT_POLICY == "RANDOM"){
                        int randomIndex = rand() % ASSOCIATIVITY;
                        cacheSets[setIndex][randomIndex] = tag;
                    }
                    else if(REPLACEMENT_POLICY == "LRU"){
                        
                        int LRTag = lruQueue[setIndex].front();
                        lruQueue[setIndex].pop();
                        
                        auto it = find(cacheSets[setIndex].begin(), cacheSets[setIndex].end(), LRTag);
                        
                        if (it != cacheSets[setIndex].end()){
                        int position = distance(cacheSets[setIndex].begin(), it);
                        cacheSets[setIndex].erase(it);
                        cacheSets[setIndex][position] = tag;
                        
                        lruQueue[setIndex].push(tag);
                        }

  
                    }
                }
                else{
                    cacheSets[setIndex].push_back(tag);
                    if (REPLACEMENT_POLICY == "LRU"){
                        lruQueue[setIndex].push(tag);
                    }
                }
                
            }
        }
        
    }
    
    cout << "Tag: 0x" << hex << tag << endl;

}


int main() {
    
    srand(time(nullptr));
    
    vector<pair<string, int>> input;

    string m;
    int adrs;
    
    ifstream access_file("/Users/dhatrireddy/Desktop/CompArch/cache.access");

    while (access_file >> m >> hex >> adrs) {
               input.push_back({m, adrs});
        }
    
    for (auto p : input){
        string mode = p.first.substr(0, 1);
        int address = p.second;
        
        cacheAccess(mode, address);
    }

    return 0;
}
