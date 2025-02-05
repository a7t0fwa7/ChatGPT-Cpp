#include "../include/ChatGPT.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../include/Error.h"

OpenAI::ChatGPT::ChatGPT(const std::string& token):m_token{token},m_link{"https://api.openai.com/v1/chat/completions"} {

}

OpenAI::ChatCompletion OpenAI::ChatGPT::sendRequest(const std::string& role,const std::string& content) {
    auto json="{\n"
                    "  \"model\": \"gpt-3.5-turbo\",\n"
                    "  \"messages\": [{\"role\": \""+role+"\", \"content\": \""+content+"\"}]\n"
                    "}";
    auto response = cpr::Post(cpr::Url{m_link},cpr::Body{json},cpr::Bearer({m_token}),cpr::Header{{"Content-Type","application/json"}}).text;
    OpenAI::ChatCompletion chatCompletion;
    nlohmann::json j=nlohmann::json::parse(response);
    if(!j.contains("error")) {
        from_json(j, chatCompletion);
    }else{
        throw OpenAI::Error{j.dump()};
    }
    return chatCompletion;
}
