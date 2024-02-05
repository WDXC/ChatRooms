#ifndef ENCAPSLUATEJSON_H_
#define ENCAPSLUATEJSON_H_

#include "json_struct_def.h"
#include "rapidjson/document.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <rapidjson/rapidjson.h>
#include <vector>

#define PARSESTRUCT(name) void parse_##name(const char *, name &);
#define PARSEARRAY(name)                                                       \
  void parse_##name##_array(const char *, std::vector<name> &);

using namespace rapidjson;

enum ValueType {
  UnknownType = 0,
  IntType = 1,
  FloatType,
  DoubleType,
  LongDoubleType,
  UIntType,
  StringType,
};

class EncapsluateJson {
public:
  EncapsluateJson(const char *json);
  ~EncapsluateJson();

public:
  // parse common type
  void parse(const char *, int32_t &);
  void parse(const char *, int64_t &);
  void parse(const char *, uint32_t &);
  void parse(const char *, uint64_t &);
  void parse(const char *, float &);
  void parse(const char *, double &);
  void parse(const char *, std::string &);

public:
  // parse object
  PARSESTRUCT(Login);

public:
  // parse array
  PARSEARRAY(Login);

private:
  std::shared_ptr<Document> m_doc;
};

#endif
