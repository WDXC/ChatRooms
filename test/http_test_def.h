#ifndef HTTP_TEST_DEF_H
#define HTTP_TEST_DEF_H

#include <string>

// request parser
std::string get_request_string = "GET /path/to/resource?param1=value1&param2=value2 HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string post_request_string = "POST /path/to/resource HTTP/1.1\r\nHost: example.com\r\nContent-Length: 13\r\n\r\nHello, World!";
std::string put_request_string = "PUT /path/to/resource HTTP/1.1\r\nHost: example.com\r\nContent-Length: 11\r\n\r\nHello, World";
std::string delete_request_string = "DELETE /path/to/resource HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string patch_request_string = "PATCH /path/to/resource HTTP/1.1\r\nHost: example.com\r\nContent-Length: 11\r\n\r\nHello, World";
std::string head_request_string = "HEAD /path/to/resource HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string options_request_string = "OPTIONS /path/to/resource HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string request_header_string = "GET /path/to/resource HTTP/1.1\r\nHost: example.com\r\nUser-Agent: TestClient\r\nAccept: */*\r\n\r\n";
std::string request_complex_string = "GET /users/123 HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string request_urlencode_string = "GET /path/to/resource?param1=value%20with%20space HTTP/1.1\r\nHost: example.com\r\n\r\n";
std::string upload_file_request = "POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW\r\n\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\nContent-Type: text/plain\r\n\r\nFile content\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW--\r\n";
std::string multi_request_string = "POST /submit-form HTTP/1.1\r\nHost: example.com\r\nContent-Type: multipart/form-data; boundary=------------------------a1b2c3d4e5f6\r\n\r\n--------------------------a1b2c3d4e5f6\r\nContent-Disposition: form-data; name=\"text\"\r\n\r\nSome text\r\n--------------------------a1b2c3d4e5f6\r\nContent-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\nContent-Type: text/plain\r\n\r\nFile content\r\n--------------------------a1b2c3d4e5f6--\r\n";
std::string illegal_request_string = "GET /path/to/resource HTTP/1.1\r\n\r\n";


#endif
