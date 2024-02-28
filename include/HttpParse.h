#ifndef HTTPPARSE_H_
#define HTTPPARSE_H_

class HttpParse {
    public:
        HttpParse();
        ~HttpParse();

    public:
        void init();
        void parserAddr(const char* );
        const char* getParseInfo();
        void getRequestMethod();

    private:
        void parseGetRequest(const char* );
        void parsePostRequest(const char* );
        void parsePutRequest(const char* );
        void parseDeleteRequest(const char* );
        void parsePatchRequest(const char* );
        void parseHeadRequest(const char* );
        void parseOptionsRequest(const char* );

    private:
        void extraParam(const char* );
        void extraHeader(const char* );
        void extraJson(const char* );
};

#endif
