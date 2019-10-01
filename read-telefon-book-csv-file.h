/* 
 * File:   read-telefon-book-csv-file.h
 * Author: tai-linh.du
 *
 * Created on 25. September 2019, 16:30
 */

#ifndef READ_TELEFON_BOOK_CSV_FILE_H
#define	READ_TELEFON_BOOK_CSV_FILE_H

#include<vector>
#include<string>
#include<cstring>

#include "telefon-book.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void removeCharsFromString( string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

int countOccurrencesOfCharInString (string s, char c){
    int count = 0;
    for (int i = 0; i < s.length(); i++){
        if(s.at(i) == c)
            count++;
    }
    return count;
}

int findIndexToSepareteTwoString (string s, char c){
    for (int i = 1; i < s.length(); i ++){
        if (s.at(i) == c){
            return i;
        }
    }
    
    return 0;
}

class ReadTelefonBookCSVFile {
public:
    ReadTelefonBookCSVFile(){}
    vector<TelefonBook> telefonbook ;
    void readFileAndInsertIntoTelefonBook (string filename){
        // File pointer 
        fstream fin; 

        // Open an existing file 
        fin.open(filename, ios::in); 

        // Read the Data from the file 
        // as String Vector 
        vector<string> allRows; 
        string line, word, temp; 
        
        int count = 0;

        // first line
        //getline(fin, line); 
        
        
        if (fin >> temp) { 

            getline(fin, line);
            //cout << line << endl;

            // used for breaking words 
            stringstream s(line); 

            // read every column data of a row and 
            // store it in a string variable, 'word' 
            while (getline(s, word, ',')) { 

                // add all the column data 
                // of a row to a vector     
                allRows.push_back(word); 
            } 
            
            int  i = 0;
            
            string firstName = "";

            while (i < allRows.size()){
                
                TelefonBook telefonBook {};
                
                if (firstName == ""){
                    removeCharsFromString(allRows[i], "\"");
                    telefonBook.firstName = allRows[i];
                    i++;
                } else {
                    telefonBook.firstName = firstName;
                    firstName = "";
                }
                                
                removeCharsFromString(allRows[i], "\"");
                telefonBook.lastName = allRows[i];
                i++;
                
                if( allRows[i].at(allRows[i].length()-1) == '"' || allRows[i].at(allRows[i].length()-2) == '"') {
                    removeCharsFromString(allRows[i], "\"");
                    telefonBook.companyName = allRows[i];
                    i++;
                    
                } else {
                    removeCharsFromString(allRows[i], "\"");
                    removeCharsFromString(allRows[i+1], "\"");
                    telefonBook.companyName = allRows[i] + allRows[i+1];
                    i += 2;
                  
                }
                
                // address
                removeCharsFromString(allRows[i], "\"");
                telefonBook.address = allRows[i];
                i++;
                
                // city
                removeCharsFromString(allRows[i], "\"");
                telefonBook.city = allRows[i];
                i++;
                
                // state
                removeCharsFromString(allRows[i], "\"");
                telefonBook.state = allRows[i];
                i++;
                
                // post
                removeCharsFromString(allRows[i], "\"");
                telefonBook.post = allRows[i];
                i++;
                
                // phone1
                removeCharsFromString(allRows[i], "\"");
                telefonBook.phone1 = allRows[i];
                i++;
                
                // phone2
                removeCharsFromString(allRows[i], "\"");
                telefonBook.phone2 = allRows[i];
                i++;
                
                // email
                removeCharsFromString(allRows[i], "\"");
                telefonBook.email = allRows[i];
                i++;
                
                // web
                
                if (countOccurrencesOfCharInString(allRows[i],'"') <= 2){
                    removeCharsFromString(allRows[i], "\"");
                    telefonBook.web = allRows[i];
                    
                } else { // >= 2 split string into 2 substring
                    int index = findIndexToSepareteTwoString(allRows[i],'"');
                    
                    if(index != 0){
                        
                        string web = "";
                        for (int j = 0; j < index; j++){
                            web += allRows[i].at(j);
                        }
                        removeCharsFromString(web, "\"");
                        telefonBook.web = web;
                        
                        firstName = "";
                        for (int j=index; j <allRows[i].length(); j++){
                            firstName += allRows[i].at(j);
                        }
                        removeCharsFromString(firstName, "\"");
                    }
                }
                i++;
                
                telefonbook.push_back(telefonBook);
                
            }

            count = 1; 

        } 
        if (count == 0) 
            cout << "Record not found\n"; 
    } 
    
    void showTelefonBook (){
        for(int i = 0; i< telefonbook.size(); i++){
            cout << i + 1 << ": " << telefonbook[i].firstName << " " << telefonbook[i].email << endl;
        }
    }
};

#endif	/* READ_TELEFON_BOOK_CSV_FILE_H */

