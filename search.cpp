#include "search.h"

SearchEngine::SearchEngine(){
	dem.clear();
	sen.clear();
	
}

void SearchEngine::toLowerr(string &s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = std::tolower(c);
        }
    }
}
void SearchEngine::prefix(vector <int> &l, string s){
    int n = s.length();
    int i = 1;
    int j = 0;
    int temp = 0;
    while(temp < n){
        l.push_back(0);
        temp++;
    }
    while(i<n){
        if(s[i]==s[j])
        {
            
            l[i++] = ++j;
        }
        else{
            if(j!=0)
            {
                j = l[j-1];
            }
            else{
                ++i;
            }
        }
    }
	return;
}
SearchEngine::~SearchEngine(){
    for(vector<int> v: dem){
        v.clear();
    }
    dem.clear();
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<int> tempdem;
    tempdem.push_back(book_code);
    tempdem.push_back(page);
    tempdem.push_back(paragraph);
    tempdem.push_back(sentence_no);
    dem.push_back(tempdem);
	toLowerr(sentence);
    sen.push_back(sentence);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    vector<int> l;
    prefix(l,pattern);
    Node* first;
    Node* last;
    n_matches = 0;
    toLowerr(pattern);
    for(int m=0; m<sen.size(); m++){
        string sentence=sen[m];
        int pos;
        int i,j;
        i=0;
        j=0;
        while(i<sentence.size()){
            if(sentence[i]==pattern[j]){
                i++;j++;
            }
            else{
                if(j!=0){
                    j=l[j-1];
                }
                else{
                    i++;
                }
            }
            if(j==pattern.size()){
                Node* temp=new Node(dem[m][0],dem[m][1],dem[m][2],dem[m][3],i-pattern.length());
                if(n_matches!=0){
                    temp->left=last;
                    last->right=temp;
                }
                else{
                    first=temp;
                }
                last=temp;
                n_matches++;
                j=0;
            }
        }
    }
    return first;
}