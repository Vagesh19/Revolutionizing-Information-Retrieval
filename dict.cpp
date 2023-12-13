// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){

    noice = new haash(10103);    
}

Dict::~Dict(){
//	delete noice;   
}

void Dict::toLower(string &s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = std::tolower(c);
        }
    }
}



void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
	int i = 0;
	string s= ""; 
	
	while (i < sentence.length()){
		for ( i; i <sentence.length() ; i++){
            
			if (sentence[i] == '.' || sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '"' || sentence[i] == '\'' || sentence[i] == '-' || sentence[i] == ':' || sentence[i] == '!' || sentence[i] == '(' || sentence[i] == ')' || sentence[i] == '?' || sentence[i] == '[' || sentence[i] == ']' || sentence[i] == ';' || sentence[i] == '@'){
                if (s== ""){
					break;
				}
				else{
					toLower(s);
					noice->insert(s);
					s = "";
					break;
					
				}
				
				
			}
			else{
				s = s + sentence[i];
			}
		}
		if (!s.empty()){
			toLower(s);
			noice->insert(s);
			s= "";
		}
		i++;
		
	}
	
    // Implement your function here  
    return;
}

int Dict::get_word_count(string word){
    toLower(word); 
	int k = noice->search(word);
	return k;	
}

void Dict::dump_dictionary(string filename){ 
    ofstream MyFile(filename);
    for(SymbolTable* v : noice->arr){
        if(v->get_root()!=NULL){
            vector<SymNode*> stack;
            stack.push_back(v->get_root());
            while(!stack.empty()){
                SymNode* temp1= stack.back();
                stack.pop_back();
                MyFile<< temp1->key << ", " << to_string(noice->search(temp1->key))<<endl;
                if(temp1->left!=NULL){
                    stack.push_back(temp1->left);
                }
                if(temp1->right!=NULL){
                    stack.push_back(temp1->right);
                }
            }
        }
    }
    MyFile.close();
    return;
}


//
// int main() {
//    Dict myDictionary; // Create an instance of the dictionary

//    // Insert some sentences into the dictionary
//    myDictionary.insert_sentence(1, 0, 0, 1, "a      bbbbb   a");
//    myDictionary.insert_sentence(1, 0, 0, 2, "Another 12341b fasufh 324832 dasdkjab 23h2 dasjdsu sam 312 2i1u3j wdiuacsdu sda/. d ndv ,.caple sentence.");

//    myDictionary.dump_dictionary("dictionary.txt");

//    // Retrieve word counts
//    int count1 = myDictionary.get_word_count("bbbbb");
//    int count2 = myDictionary.get_word_count("a");
//    int count3 = myDictionary.get_word_count("sam");

//    cout<<"count1 "<<count1<<" count2 "<<count2<<endl;
//    cout<<" count3 "<<count3<<endl;


//    return 0;
// }
