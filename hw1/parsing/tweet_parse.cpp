#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
    Questions to ask
    1.If the input file doesn't exist when you try to open it, just print a message and quit. ???
*/

int main(int argc, char* argv[]){

    if(argc != 2){
        //User did not provide enough resources.
        return -1;
    }

    ifstream in_file(argv[1]);
    
    if(in_file.fail()){
        //No such file exist.??
        cout << "No such file exist." << endl;
        return -1;
    }

    string myLine;
    stringstream buff;
    
    vector<string> user_container;
    vector<string> hash_container;

    int cnt_tweet = 0;

    while(!in_file.eof()){

        getline(in_file,myLine,'\n');

        if(myLine != ""){
            
            //increment the number of tweet.
            cnt_tweet++;

            buff << myLine;
            string temp;
            while(buff >> temp){

                //variable to store a word which has rid of first char.
                string modified = "";

                if(temp[0] == '@'){
                    
                    for(unsigned int i = 1; i < temp.length(); i++){
                        modified += temp[i];   
                    }

                    
                    //assume the word is there.
                    bool check1 = true;
                    //for loop for vector.
                    for(unsigned int i = 0; i < user_container.size(); i++){
                        
                        if(user_container[i].length() == modified.length()){

                            unsigned int count = 0;
                            for(unsigned int j = 0; j < modified.length(); j++){
                                if(user_container[i][j] == modified[j]){
                                    count++;
                                }
                            }
                            if(count == modified.length()){
                                check1 = false;
                            }
                            
                        }
                        
                        if(!check1){
                            //same word is found.
                            break;
                        }
                        //reset it 
                        check1 = true;
                    }
                    
                    if(check1){
                        user_container.push_back(modified);
                    }

                    
                }
                else if(temp[0] == '#'){
                    //cout << temp << endl;
                    for(unsigned int i = 1; i < temp.length(); i++){
                        modified += temp[i];   
                    }

                    bool check2 = true;
                    for(unsigned int i = 0; i < hash_container.size(); i++){

                        if(hash_container[i].length() == modified.length()){
                            unsigned int count = 0;
                            for(unsigned int j = 0; j < modified.length(); j++){
                                if(hash_container[i][j] == modified[j]){
                                    count++;
                                }
                            }
                            if(count == modified.length()){
                                check2 = false;
                            }
                        }

                        if(!check2){
                            //same word is found.
                            break;
                        }
                        //reset it 
                        check2 = true;
                    }
                    //cout << modified << endl;

                    if(check2){
                        hash_container.push_back(modified);
                    }
                    
                }
               
            }

            //clear the buff. 
            buff.clear();
    	    buff.str("");

        }
    }

    cout << "1. Number of tweets=" << cnt_tweet << endl;
    cout << "2. Unique users" << endl;
    for(unsigned int i = 0; i < user_container.size(); i++){
        cout << user_container[i] << endl;
    }
    cout << "3. Unique hashtags" << endl;
    for(unsigned int i = 0; i < hash_container.size(); i++){
        cout << hash_container[i] << endl;
    }



    return 0;
}