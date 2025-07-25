#include <iostream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "parser.hpp"

using json = nlohmann::json;

namespace http
{

    json ParserMessage::parserHTTPrequest(std::string& MessageRequest){
        uint8_t LineIDX {};
        std::vector<std::string> SeparateLines {};

        while (true) {
            LineIDX = (MessageRequest.find('\n') == std::string::npos) ? 0 : MessageRequest.find('\n');
            if (LineIDX){
                if (LineIDX==1){
                    MessageRequest.erase(0, LineIDX + 1);
                    SeparateLines.emplace_back(MessageRequest);
                }
                else{
                    SeparateLines.emplace_back(MessageRequest.substr(0, LineIDX-1));
                    MessageRequest.erase(0, LineIDX + 1);
                }
            }
            else{    
                break;
            }
        }   

        parserHTTPrequest_Line(SeparateLines, ParsedHTTP_request);
        parserHTTPrequest_Header(SeparateLines, ParsedHTTP_request);
        parserHTTPrequest_Body(SeparateLines, ParsedHTTP_request);

        return ParsedHTTP_request;
    }

    const bool ParserMessage::parserHTTPrequest_Line(const std::vector<std::string>& MessageRequest, json& ModifySET){
        std::istringstream iss(MessageRequest[0]);
        std::string token {};
        const std::array<const char[13], 3> test {"Method", "Request-URL", "HTTP-Version"};
        uint8_t Idx {};

        while (std::getline(iss, token, ' ')) {
            ModifySET["Request-Line"][test[Idx]] = token;
            Idx++;
        }

        try {
            static const std::unordered_map<std::string, HTTPmethods> methodMap = {
                {"OPTIONS", HTTPmethods::OPTIONS},
                {"GET",     HTTPmethods::GET},
                {"HEAD",    HTTPmethods::HEAD},
                {"POST",    HTTPmethods::POST},
                {"PUT",     HTTPmethods::PUT},
                {"DELETE",  HTTPmethods::DELETE},
                {"TRACE",   HTTPmethods::TRACE},
                {"CONNECT", HTTPmethods::CONNECT},
                {"UNKNOWN", HTTPmethods::UNKNOWN}
            };

            const std::string& methodStr = ModifySET["Request-Line"]["Method"];
            auto it = methodMap.find(methodStr);
            if (it != methodMap.end()) {
                ExtractedMETHOD = it->second;
            } else {
                std::cerr << "Unsupported HTTP method: " << methodStr << '\n';
                ExtractedMETHOD = HTTPmethods::UNKNOWN;
                return false;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << '\n';
            return false;
        }
        return true;
    }

    const bool ParserMessage::parserHTTPrequest_Header(const std::vector<std::string>& MessageRequest, json& ModifySET){
        uint8_t TempNum {};
        std::string LineIdx {}, Text {}, EachLine {};

        for (size_t num = 1;num < MessageRequest.size()-1;num++){
            EachLine = MessageRequest[num];
            TempNum = EachLine.find(':');
            LineIdx = EachLine.substr(0, TempNum);
            Text = EachLine.substr(TempNum + 2, EachLine.length());
            ModifySET["Header"][LineIdx] = Text;
        }
        return true;
    }

    const bool ParserMessage::parserHTTPrequest_Body(const std::vector<std::string>& MessageRequest, json& ModifySET) const {
        
        ModifySET["Message-Body"] = MessageRequest.back();

        return true;
    }

} // namespace http