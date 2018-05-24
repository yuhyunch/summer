#include <string>
#include <iostream>
#include <fstream> // for input and output file.

using namespace std;


/*
    Questions to ask
    1. Why I can't assign the input ant output right into infile and outfile?
*/

int main(int argc, char* argv[]){

    if(argc != 3){
        //user didn't provide enough sources. ERROR!
        return 0;
    }

    ifstream in_file(argv[1]);

    if(in_file.fail()){
        //user provided inappropriate files.
        return 0;
  	}

    //reading the total number of integers in the file.
    unsigned int num;
    in_file >> num;
    
    if(in_file.fail()){
        //ERROR occured during reading an input file.
        return 0;
        //after this no other format error is there.
    }

    int* container = new int[num];

    //variable to store the integer.
    int temp;
    //variable to count the index of array.
    int pos = 0;

    //store all the integers in container.
    while( in_file >> temp){
        container[pos] = temp;
        pos++;
    }

    in_file.close();

    ofstream out_file(argv[2]);

    if(num == 0){
        out_file << 0 << endl;
        delete [] container;
        return 0;
    }

    //if the total number of integers are even number
    if(num%2 == 0){
        for(unsigned int i = 0; i < num/2; i++){
            out_file << container[i] + container[num-i-1] << endl;
        }
    }
    else{
        for(unsigned int i = 0; i < num/2 + 1; i++){
            if(i == num/2){
                out_file << container[i]*2 << endl;
            }
            else{
                out_file << container[i] + container[num-i-1] << endl;
            }
        }
    }

    out_file.close();

    delete [] container;

    return 0;
}