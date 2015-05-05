#pragma once

#include <string>

namespace Models {

    enum class Article {
        A,
        AN,
        THE,
        EMPTY,
        UNKNOWN
    };
    
    inline std::string articleToStr(Article a) {
        switch(a) {
            case Article::A:
                return "A";
            case Article::AN:
                return "AN";
            case Article::THE:
                return "THE";
            case Article::EMPTY:
                return " ";
            case Article::UNKNOWN:
                return " ? ";
        }
        return "xxx";
    }
    
    inline Article articleFromStr(const std::string str) {
        if(str == "a") {
            return Article::A;
        }
        if(str == "an") {
            return Article::AN;
        }
        if(str == "the") {
            return Article::THE;
        }
        if(str == "-") {
            return Article::EMPTY;
        }
        return Article::EMPTY;
    }

}