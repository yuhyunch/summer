#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
    Questions?
    1. what is cerr?
    2. in the skeleton code it has the declared function at the top. Do we need it?

*/

void readWords(char* filename, vector<vector<string> >& words);
// client interface

void generateSentences(vector<vector<string> >& words, ofstream& ofile);
// recursive helper function

void genHelper(vector<vector<string> >& words, ofstream& ofile, int currentOption, string sentence, int& numSentences);

void readWords(char* filename, vector<vector<string> >& words){

    ifstream in_file(filename);

    if(in_file.fail()){
        //how to terminate the code itself..?
        return;
    }

    string myLine;
    stringstream buff;
    vector<string> inner;

    int count = 0;

    while(!in_file.eof()){       

        getline(in_file,myLine,'\n');
        buff << myLine;

        if(count == 0 || count == 3){
            inner.push_back("");
        }

        string temp;
        while(buff >> temp){
            inner.push_back(temp);
        }

        //add the inner vector to outer vector
        words.push_back(inner);
        //clear the inner vector for another line.
        inner.clear();

        //clear the buff
        buff.clear();
        buff.str("");

        count++;
    }
}

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile){

    int numSentences = 0; 
    int currentOption = 0;

    genHelper(words, ofile, currentOption, "The", numSentences);
    ofile << numSentences << " sentences.";
    
}

// recursive helper function
void genHelper(vector<vector<string> >& words, ofstream& ofile, int currentOption, string sentence, int& numSentences){

    if(currentOption == 0){
        for(unsigned int i = 0; i < words[0].size(); i++ ){
            
            string temp = sentence;
            if(words[0][i] != ""){
                temp += " ";
            }
            temp += words[0][i];
            
            currentOption = 1;
            genHelper(words, ofile, currentOption, temp, numSentences);
        }
    }
    else if(currentOption == 1){
        for(unsigned int i = 0; i < words[1].size(); i++ ){
            
            string temp = sentence;
            if(words[1][i] != ""){
                temp += " ";
            }
            temp += words[1][i];
            
            currentOption = 2;
            genHelper(words, ofile, currentOption, temp, numSentences);
        }

    }
    else if(currentOption == 2){
        for(unsigned int i = 0; i < words[2].size(); i++ ){
            string temp = sentence;
            if(words[2][i] != ""){
                temp += " ";
            }
            temp += words[2][i];
            
            currentOption = 3;
            genHelper(words, ofile, currentOption, temp, numSentences);
        }

    }
    else{
        for(unsigned int i = 0; i < words[3].size(); i++ ){
            string temp = sentence;
            if(words[3][i] != ""){
                temp += " ";
            }
            temp += words[3][i];
            temp += ".";
            numSentences++;
            ofile << temp << endl;
        }

    }

}

int main(int argc, char* argv[]){

    if(argc < 3){
        cerr << "Usage ./sentences input_file output_file" << endl;
    }

    vector<vector<string> > words;

    //call a function to read the input file.
    readWords(argv[1], words);

    // Check the status of parsing
    if(words.size() < 4){
        cerr << "Input file requires 4 lines of words" << endl;
        return 1;
    }

    for(unsigned int i = 0; i < words.size(); i++){
        for(unsigned int j = 0; j < words[i].size(); j++){
            cout << words[i][j] << " ";
        }
        cout << endl;
    }

    // Open the output file
    ofstream ofile(argv[2]);
 
    // generate all the sentence options writing them to ofile
    generateSentences(words, ofile);

    ofile.close();    

    return 0;
}