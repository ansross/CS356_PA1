#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iterator>
using namespace std;

bool DEBUG = true;

string makeIntoKey(string word){
	string key = "";
	for(int i=0; i<word.length(); ++i){
		//if not duplicate, add 
		//if at 10 letters, done
		if(key.find_first_of(word[i]) == string::npos){
			key += word[i];
		}
		if(key.length()==10){
			break;
		}
	}
	return key;
}

void  getKey(string &key, int keyNum){
	//TODO!!!! TAKE ON SENTENCES NOT JUST SINGLE WORDS
	key="";
	string word="";
	while(key.length() < 10){
		key="";
		cout<<"enter keyword "<<keyNum<<"\n";
		cin>>word;
		//case doesn't matter
		for(int i=0; i<word.length(); ++i){
			word[i] = tolower(word[i]);
		}
		cout<<"keyword 1 is: " << word<<endl;
		key = makeIntoKey(word);
		if(key.length()<10){
			cout<<"word does not contain at least 10 unique letters, please try again"<<endl;
		}
	}
	if(DEBUG)   {
	    cout<< "key: "<<key<<endl;
	}
}

void print(vector< vector<char> > table, int numRows){
    for(int row=0; row<numRows; ++row){
       for(int col=0; col<10; ++col){
            cout<<table[row][col]<<"\t";
       }
       cout<<endl;
    }
    cout<<"Printed done"<<endl;
}

bool isSpaceOrPunctuation(char c){
    return !isalpha(c);}

void createTranspositionTable(vector<vector <char > > &transpositionTable, const string &sentence, const string &key){
         int numRows = ceil((double)sentence.size()/10)+1;
            cout<<"NumRows: "<<numRows<<endl;
;
            transpositionTable.resize(numRows);
            for(int i=0; i<numRows; ++i){
                transpositionTable[i].resize(10);
            }
            //string::iterator sentIter = sentence.begin();
            int sentIter = 0;
            for(int row =0; row<numRows; ++row){
                for(int col =0; col<10; ++col){
                   if(row!=0 && sentIter < sentence.size()){//sentIter<sentence.end()){
                        transpositionTable[row][col] = toupper(sentence[sentIter]);//(*sentIter);
                        ++sentIter;
                   }
                   else if(row !=0 && sentIter>=sentence.size()
                		   //sentIter>=sentence.end()
                		   && col<10){
                        transpositionTable[row][col] = 'X';
                   }
                   else if(row == 0){
                        transpositionTable[row][col] = key[col];
                   }
                }
            }
            print(transpositionTable, numRows);

}

string createTransposition(const vector<vector<char> > &table, const string &key){
	cout<<"Creating transposition"<<endl;
	string transposition = "";
	string sortedKey = key.substr();
	sort(sortedKey.begin(), sortedKey.end());
	vector<int> orderedIndicies;
	for(string::iterator iter = sortedKey.begin(); iter < sortedKey.end(); ++iter){
		orderedIndicies.push_back(key.find(*iter));
	}
	for(vector<int>::iterator iter = orderedIndicies.begin(); iter <orderedIndicies.end(); ++iter){
		cout<<*iter<<" ";
	}
	cout <<endl;
	int printedLetterCount = 0;
	for(int i=0; i<10; ++i){
		for(int row = 1; row<table.size(); ++row){
			transposition+=toupper(table.at(row).at(orderedIndicies.at(i)));
			printedLetterCount ++;
			if(printedLetterCount%5==0){
				transposition +=' ';
			}
		}
	}
	cout<<"Transposition: \n"<<transposition<<endl;
	return transposition;

}

string transpose(string &sentence, string &key){
    //no spaces
    sentence.erase(remove_if(sentence.begin(), sentence.end(), isSpaceOrPunctuation),sentence.end());
    vector< vector<char> > transpositionTable;
    createTranspositionTable(transpositionTable, sentence, key);
    string transposition = createTransposition(transpositionTable, key);
    return transposition;


}

int main(){
    string sampleText = "be at the third pillar from the left outside the lyceum theatre tonight at seven.";
	string keyOne="";
	string keyTwo="";
	getKey(keyOne, 1);
	getKey(keyTwo, 2);
	string firstTranspostion = transpose(sampleText,keyOne);
	return 0;
	
}

