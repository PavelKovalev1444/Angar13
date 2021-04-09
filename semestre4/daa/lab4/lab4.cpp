#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

std::vector<int> prefix(const std::string& p){
    int n = p.length();
    std::vector<int> pi(p.length(), 0);
    for(int i = 1; i < n; i++){
        int j = pi[i - 1];
        while(j > 0 && p[i] != p[j]){
            j = pi[j - 1];
        }
        if(p[i] == p[j]){
            pi[i] = j + 1;
        }else{
            pi[i] = j;
        }
    }
    return pi;
}   

std::vector<int> kmp(std::string& A, std::string& B){
    int k = 0;
    std::vector<int> a;
    std::string tmp = B + "#" + A + A;
    std::vector<int> pi = prefix(tmp);
    int aSize = A.size();
    int bSize = B.size();
    for(int i = 0; i < 2*bSize; i++){
        if(pi[aSize + 1 + i] == aSize){
            a.push_back(i - aSize + 1);
        }
    }
    return a;
}

int main(){
    std::string A, B;
    std::cin >> A >> B;
    std::vector<int> res = kmp(A, B);
    if(res.empty()){
        std::cout << -1;
        return 0;
    }
    std::cout << res[0];
    return 0;
}