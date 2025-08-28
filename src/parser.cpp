#include "parser.hpp"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

namespace http
{

ParserMessage::ParserMessage() : extracted_method(HTTPmethods::UNKNOWN) {}

json ParserMessage::ParserHttPrequest(std::string& message_request)
{
    size_t                   line_idx{};
    std::vector<std::string> separate_lines{};

    while (true)
    {
        line_idx =
            (message_request.find('\n') == std::string::npos) ? 0 : message_request.find('\n');
        if (line_idx != 0U)
        {
            if (line_idx == 1)
            {
                message_request.erase(0, line_idx + 1);
                separate_lines.emplace_back(message_request);
            }
            else
            {
                separate_lines.emplace_back(message_request.substr(0, line_idx - 1));
                message_request.erase(0, line_idx + 1);
            }
        }
        else
        {
            break;
        }
    }

    ParserHttPrequestLine(separate_lines, parsed_http_request);
    ParserHttPrequestHeader(separate_lines, parsed_http_request);
    ParserHttPrequestBody(separate_lines, parsed_http_request);

    return parsed_http_request;
}

bool ParserMessage::ParserHttPrequestLine(const std::vector<std::string>& message_request,
                                          json&                           modify_set)
{
    std::istringstream                              iss(message_request[0]);
    std::string                                     token{};
    const std::array<const std::array<char, 13>, 3> test{"Method", "Request-URL", "HTTP-Version"};
    uint8_t                                         idx{};

    while (std::getline(iss, token, ' '))
    {
        if (!modify_set.contains("Request-Line") || !modify_set["Request-Line"].is_object())
        {
            modify_set["Request-Line"] = json::object();
        }

        modify_set["Request-Line"][std::string(test[idx].data())] = token;

        idx++;
    }

    try
    {
        static const std::unordered_map<std::string, HTTPmethods> method_in_map = {
            {"OPTIONS", HTTPmethods::OPTIONS}, {"GET", HTTPmethods::GET},
            {"HEAD", HTTPmethods::HEAD},       {"POST", HTTPmethods::POST},
            {"PUT", HTTPmethods::PUT},         {"DELETE", HTTPmethods::DELETE},
            {"TRACE", HTTPmethods::TRACE},     {"CONNECT", HTTPmethods::CONNECT},
            {"UNKNOWN", HTTPmethods::UNKNOWN}};

        const std::string& method_to_string = modify_set["Request-Line"]["Method"];
        auto               iterator_map     = method_in_map.find(method_to_string);
        if (iterator_map != method_in_map.end())
        {
            extracted_method = iterator_map->second;
        }
        else
        {
            std::cerr << "Unsupported HTTP method: " << method_to_string << '\n';
            extracted_method = HTTPmethods::UNKNOWN;
            return false;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return false;
    }
    return true;
}

bool ParserMessage::ParserHttPrequestHeader(const std::vector<std::string>& message_request,
                                            json&                           modify_set)
{
    size_t      temp_number{};
    std::string line_idx{};
    std::string text{};
    std::string each_line{};

    for (size_t num = 1; num < message_request.size() - 1; num++)
    {
        each_line                      = message_request[num];
        temp_number                    = each_line.find(':');
        line_idx                       = each_line.substr(0, temp_number);
        text                           = each_line.substr(temp_number + 2, each_line.length());
        modify_set["Header"][line_idx] = text;
    }
    return true;
}

bool ParserMessage::ParserHttPrequestBody(const std::vector<std::string>& message_request,
                                          json&                           modify_set)
{
    modify_set["Message-Body"] = message_request.back();

    return true;
}

} // namespace http