#include "filter.h"


std::string strip(std::string s) {
    std::string strippedString;
    for(int i=0; i< (int) s.size(); i++) {
        if(s[i] != ' ' && s[i] != '\n') {
            strippedString.push_back(s[i]);
        }
    }
    return strippedString;
}

std::vector<std::string> combineTokens(std::vector<std::string> &tokens) {
    int i = 0;
    int n = tokens.size();

    std::vector<std::string> processedTokens;

    while(i < n) {
        if(tokens[i] == "'") {
            // string value token splitted as |',VALUE,'| combine these tokens
            int j = i + 1;
            while(j < n && tokens[j] != "'") {
                j++;
            }
            std::string valuetoken = "";
            int k = i + 1;
            while(k < j)
            {
                valuetoken += (tokens[k] + " ");
                k++;
            }
            valuetoken.pop_back();
            processedTokens.push_back(valuetoken);
            i = j;
        }
        else if(tokens[i] == "(" && processedTokens.size() > 0 && processedTokens.back() == "IN") {
            // last token IN, next are the list of VALUES
            int j = i + 1;
        }
        i++;
    }
}

DataFrame* filter(DataFrame* df, std::string &filterString) {
    std::cout<<filterString<<std::endl;
    int n = filterString.size();
    // first split on operators (,),>,<,>=,<=,AND,OR,+,-,*,/,IN,
    std::vector<std::string> operators = {")","(",">","<","<=",">=","=","AND","OR","+","-","*","/","IN","'"};

    std::vector<std::string> filterTokens;
    int prev = 0;
     
    for(int i=0; i< (int) filterString.size(); i++) {
        for(std::string op: operators) {
            bool flag = true;
            for(int j=0; j< (int) op.size(); j++) {
                if(((i + j) >= n) || (filterString[i + j] != op[j])) {
                    flag = false;
                    break;
                }
            }

            if(flag) {
                //operator op matched at index i
                // a + b > 0
                if(i - prev > 0)
                {
                    // something there is before first token
                    std::string token = strip(filterString.substr(prev, i - prev));
                    if(token.size() > 0) // token is not whitespace
                        filterTokens.push_back(token);
                }
                filterTokens.push_back(strip(filterString.substr(i, op.size())));
                prev = i + op.size();
            }
        }
    }
    if(prev != n) {
        std::string token = strip(filterString.substr(prev, n - prev));
        if(token.size() > 0) // token is not whitespace
            filterTokens.push_back(token);
    }
    //combine IN lists and String constants

    // std::vector<std::string> tokens;
    // for(int i=0; i<filterTokens.size(); i++)
    // {
        
    // }

    

    for(std::string &s: filterTokens){
        std::cout<<"\""<<s<<"\""<<std::endl;
    }


    // int m = filterTokens.size();
    // for(int i=0; i<m ;i++) {
    //     if(filterTokens)
    // }

    return nullptr;
}
