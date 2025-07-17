#include <iostream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "parser.hpp"

using json = nlohmann::json;

namespace http
{

    json ParserMessage::parserHTTPrequest(std::string& MessageRequest){
        int LineIDX {}, ImportMethod {};
        std::vector<std::string> SeparateLines {};
        std::string EachLine {};

        while (true) {
            LineIDX = (MessageRequest.find('\n') == std::string::npos) ? 0 : MessageRequest.find('\n');
            if (LineIDX){
                if (LineIDX==1){
                    MessageRequest.erase(0, LineIDX+1);
                    SeparateLines.emplace_back(MessageRequest);
                }
                else{
                    SeparateLines.emplace_back(MessageRequest.substr(0, LineIDX-1));
                    MessageRequest.erase(0, LineIDX+1);
                }
            }
            else{    
                break;
            }
        }   

        parserHTTPrequest_Line(SeparateLines, HTTPmessage_request);
        parserHTTPrequest_Header(SeparateLines, HTTPmessage_request);
        parserHTTPrequest_Body(SeparateLines, HTTPmessage_request);

        return HTTPmessage_request;
    }

    int ParserMessage::parserHTTPrequest_Line(const std::vector<std::string>& MessageRequest, json& ModifySET){
        std::istringstream iss(MessageRequest[0]);
        std::string token {};
        std::vector<std::string> test {"Method", "Request-URL", "HTTP-Version"};
        int i {};

        while (std::getline(iss, token, ' ')) {
            ModifySET["Request-Line"][test[i]] = token;
            i++;
        }
        
        return 1;
    }

    int ParserMessage::parserHTTPrequest_Header(const std::vector<std::string>& MessageRequest, json& ModifySET){
        int TempNum {};
        std::string LineIdx {}, Text {}, EachLine {};

        for (size_t num = 1;num < MessageRequest.size()-1;num++){
            EachLine = MessageRequest[num];
            TempNum = EachLine.find(':');
            LineIdx = EachLine.substr(0, TempNum);
            Text = EachLine.substr(TempNum+2, EachLine.length());
            ModifySET["Header"][LineIdx] = Text;
        }

        return 1;
    }

    int ParserMessage::parserHTTPrequest_Body(const std::vector<std::string>& MessageRequest, json& ModifySET){
        
        ModifySET["Message-Body"] = MessageRequest.back();

        return 1;
    }

    HTTPmethods ParserMessage::StringToHTTPMethod(const std::string& s) {
        auto it = MethodMAP.find(s);
        if (it != MethodMAP.end()) return it->second;
        throw std::invalid_argument("Unknown HTTP method: " + s);
    }

    std::string ParserMessage::CreateHTTP_Response(){
        std::string x {};

        return x;
    }
} // namespace http