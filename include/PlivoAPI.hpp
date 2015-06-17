#ifndef PLIVOCPP_PLIVOAPI_HPP
#define PLIVOCPP_PLIVOAPI_HPP

#include <curl/curl.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>

#include <list>
#include <memory>
#include <string>

namespace plivo{
    #define PLIVO_VERSION "v1"
    #define PLIVO_URL "https://api.plivo.com"

    class PlivoAPI{
        private:
            typedef std::pair < std::string, std::string > StringPair;
            typedef std::list < StringPair > StringPairList;

        public:
            PlivoAPI(std::string auth_id, std::string auth_token)
                : PlivoAPI(auth_id, auth_token, PLIVO_URL){};

            PlivoAPI(
                std::string auth_id
                ,std::string auth_token
                ,std::string url)
                : PlivoAPI(auth_id, auth_token, url, PLIVO_VERSION){};

            PlivoAPI(
                std::string auth_id
                ,std::string auth_token
                ,std::string url
                ,std::string version);

            inline void setUrl(std::string url){setUrl(url, PLIVO_VERSION);}

            void setUrl(std::string url, std::string version);

            void sendMessage(std::string source_number
                ,std::string destination_number
                ,std::string message)
                {sendMessage(source_number
                    ,destination_number
                    ,message
                    ,std::list<StringPair>());}

            void sendMessage(std::string source_number
                ,std::string destination_number
                ,std::string message
                ,StringPairList optionals);

        private:
            std::string trimRightSlash(std::string str);

            void postRequest(std::string path){
                postRequest(path, std::list<StringPair>());}

            std::string postRequest(std::string path, StringPairList data);

            std::string listToJson(StringPairList data);

        private:
            std::string auth_id_;
            std::string auth_token_;
            std::string url_;
            std::string api_;
            std::string user_agent_;
            std::list<std::string> headers_;

    };
};

#endif//PLIVOCPP_PLIVOAPI_HPP
