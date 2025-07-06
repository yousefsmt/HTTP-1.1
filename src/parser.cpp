#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "parser.hpp"

using json = nlohmann::json;

http::ParserMessage::ParserMessage(){}
http::ParserMessage::~ParserMessage(){}

json http::ParserMessage::parserHTTPrequest(std::string& MessageRequest){
    json *Modify_JSONrequest = &HTTPmessage_request;
    HTTPmethods *Modify_Methods = &method;
    int LineIDX {}, ImportMethod {};
    std::vector<std::string> SeparateLines {};
    std::string EachLine {};

    while (true) {
        LineIDX = (MessageRequest.find('\n') == std::string::npos) ? 0 : MessageRequest.find('\n');
        if (LineIDX){
            SeparateLines.push_back(MessageRequest.substr(0, LineIDX));
            MessageRequest.erase(0, LineIDX+1);
        }
        else{    
            break;
        }
    }

    parserHTTPrequest_Line(SeparateLines[0], Modify_JSONrequest);

    SeparateLines.erase(SeparateLines.begin());
    for (std::string i : SeparateLines)
        EachLine += i + '\n';
    EachLine.erase(EachLine.end()-1);
    
    parserHTTPrequest_Header(EachLine, Modify_JSONrequest);

    MessageRequest.erase(MessageRequest.begin());
    MessageRequest.erase(MessageRequest.end()-1);
    parserHTTPrequest_Body(MessageRequest, Modify_JSONrequest);

    *Modify_Methods = StringToHTTPMethod(HTTPmessage_request["Request-Line"][0]);

    return HTTPmessage_request;
}

bool http::ParserMessage::parserHTTPrequest_Line(std::string& MessageRequest, json *ModifySET){
    int LineIDX {}, IDX {};
    std::string SeparateLines[3] {};

    while (true) {
        LineIDX = (MessageRequest.find(' ') == std::string::npos) ? 0 : MessageRequest.find(' ');
        if (LineIDX){
            SeparateLines[IDX] = MessageRequest.substr(0, LineIDX);
            MessageRequest.erase(0, LineIDX+1);
            IDX++;
        }
        else{    
            break;
        }
    }
    SeparateLines[2] = MessageRequest;
    *ModifySET = json::object( {{"Request-Line", SeparateLines}});
    
    return 1;
}

bool http::ParserMessage::parserHTTPrequest_Header(std::string& MessageRequest, json *ModifySET){
    int LineIDX {}, TempNum {};
    std::vector<std::string> LineIdx {}, Text {};
    std::string EachLine {};

    while (true) {
        LineIDX = (MessageRequest.find('\n') == std::string::npos) ? 0 : MessageRequest.find('\n');
        if (LineIDX){
            EachLine = MessageRequest.substr(0, LineIDX);
            TempNum = EachLine.find(':');
            LineIdx.push_back(EachLine.substr(0, TempNum));
            Text.push_back(EachLine.substr(TempNum+2, EachLine.length()));
            MessageRequest.erase(0, LineIDX+1);
        }
        else{    
            break;
        }
    }

    TempNum = MessageRequest.find(':');
    LineIdx.push_back(MessageRequest.substr(0, TempNum));
    Text.push_back(MessageRequest.substr(TempNum+2, MessageRequest.length()));

    if (ModifySET) {
        for (size_t i = 0; i < std::min(Text.size(), LineIdx.size()); ++i) {
            (*ModifySET)["Header"][LineIdx[i]] = Text[i];
        }
    }
    else
        return 0;

    return 1;
}

bool http::ParserMessage::parserHTTPrequest_Body(std::string& MessageRequest, json *ModifySET){
    
    (*ModifySET)["Message-Body"] = MessageRequest;

    return 1;
}

http::HTTPmethods http::ParserMessage::StringToHTTPMethod(const std::string& s) {
    auto it = MethodMAP.find(s);
    if (it != MethodMAP.end()) return it->second;
    throw std::invalid_argument("Unknown HTTP method: " + s);
}

std::string http::ParserMessage::CreateHTTP_Response(){
    std::string x {};

    return x;
}