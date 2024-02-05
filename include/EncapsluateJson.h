#ifndef ENCAPSLUATEJSON_H_
#define ENCAPSLUATEJSON_H_

#include "json_struct_def.h"
#include "rapidjson/allocators.h"
#include "rapidjson/document.h"
#include "struct_def.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <rapidjson/rapidjson.h>
#include <vector>

using namespace rapidjson;
enum ValueType {
  UnknownType = 0,
  Int32Type,
  Int64Type,
  Uint32Type,
  Uint64Type,
  FloatType,
  DoubleType,
  StringType,
};

class EncapsluateJson {
public:
  EncapsluateJson();
  ~EncapsluateJson();

  void InitRead(const char *json);
  void InitWriter();

public:
  // parse common type
  void parse(const char *, int32_t &);
  void parse(const char *, int64_t &);
  void parse(const char *, uint32_t &);
  void parse(const char *, uint64_t &);
  void parse(const char *, float &);
  void parse(const char *, double &);
  void parse(const char *, std::string &);
  void parse(const char *, const Value &);

  // parse object
  void parse_Login(const char *, Login &);

  // parse array
  void parse_Login_array(const char *, std::vector<Login> &);

public:
  // write json type
  void writeJson(const char *, const int32_t &);
  void writeJson(const char *, const int64_t &);
  void writeJson(const char *, const uint32_t &);
  void writeJson(const char *, const uint64_t &);
  void writeJson(const char *, const float &);
  void writeJson(const char *, const double &);
  void writeJson(const char *, const std::string &);

  void Append(const char *, const int32_t, Value &);
  void Append(const char *, const int64_t, Value &);
  void Append(const char *, const uint32_t, Value &);
  void Append(const char *, const uint64_t, Value &);
  void Append(const char *, const float, Value &);
  void Append(const char *, const double, Value &);
  void Append(const char *, const std::string &, Value &);

  // write object
  void writeObject(const char *, Value &);
  void writeObject(Value&, Value&);

public:
  std::string GetResultCharacters();

private:
  std::shared_ptr<rapidjson::Document> m_doc;
  Value::ConstMemberIterator m_val;

  Document::AllocatorType m_allocator;
};

#endif
