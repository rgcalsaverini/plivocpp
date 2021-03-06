#include "PlivoAPI.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

plivo::PlivoAPI::PlivoAPI(
        std::string auth_id
        ,std::string auth_token
        ,std::string url
        ,std::string version){

    setUrl(url, version);
    auth_id_ = auth_id;
    auth_token_ = auth_token;
    api_ = url_ + "/Account/" + auth_id;
    user_agent_ = "PythonPlivo"; //TODO: Test with PlivoCPP
}

void plivo::PlivoAPI::setUrl(std::string url, std::string version){
    std::string trimmed_url = trimRightSlash(url);
    url_ = trimmed_url + "/" + version;

}

std::string plivo::PlivoAPI::trimRightSlash(std::string str){
    size_t last_slash = str.find_last_of("/");

    if(last_slash == str.length()-1){
        str.erase(str.length()-1);
    }

    return str;
}

std::string plivo::PlivoAPI::postRequest(std::string path, plivo::PlivoAPI::StringPairList data){
    curlpp::Easy request;
    std::string json_data = listToJson(data);
    std::string basic_auth_credentials = auth_id_ + ":" + auth_token_;
    std::string request_url = api_ + "/" + trimRightSlash(path) + "/";

    headers_.push_back("Content-Type: application/json");

    request.setOpt(new curlpp::options::Url(request_url));
    request.setOpt(new curlpp::options::Port(443));
    request.setOpt(new curlpp::options::UserAgent(user_agent_));
    request.setOpt(new curlpp::options::HttpHeader(headers_));
    request.setOpt(new curlpp::options::HttpAuth(CURLAUTH_BASIC));
    request.setOpt(new curlpp::options::UserPwd(basic_auth_credentials));
    request.setOpt(new curlpp::options::Post(true));
    request.setOpt(new curlpp::options::PostFields(json_data));

    std::ostringstream os_stream;

    try{
        os_stream << request;
    }catch(curlpp::LibcurlRuntimeError &e){
        std::cout << "Error: " << e.what() << "\n";
        return "";
    }

    return os_stream.str();
}

std::string  plivo::PlivoAPI::listToJson(plivo::PlivoAPI::StringPairList data){
    std::string json = "{";

    for(StringPairList::iterator attribute  = data.begin()
            ; attribute != data.end()
            ; ++attribute){

        if(attribute != data.begin())
            json += ", ";

        json += "\"" + attribute->first + "\":\"" + attribute->second + "\"";
    }

    json += "}";

    return json;
}

void plivo::PlivoAPI::sendMessage(
        std::string source_number
        ,std::string destination_number
        ,std::string message
        ,StringPairList options){

    options.push_back({"src",source_number});
    options.push_back({"dst",destination_number});
    options.push_back({"text",message});

    std::string response = postRequest("Message", options);
    //std::cout << "Return:(\n" << response << ")\n";
}
