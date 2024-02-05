#include "EncapsluateJson.h"
#include "json_struct_def.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "struct_def.h"
#include "gmock/gmock.h"
#include <cstdint>
#include <iterator>

EncapsluateJson::EncapsluateJson() : m_doc(new rapidjson::Document()) {}

EncapsluateJson::~EncapsluateJson() {}

void EncapsluateJson::InitRead(const char *json) { m_doc->Parse(json); }

void EncapsluateJson::InitWriter() {
  m_doc->SetObject();
  m_allocator = m_doc->GetAllocator();
}

void EncapsluateJson::parse(const char *lv, int32_t &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsInt()) {
    rv = m_val->value.GetInt();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, int64_t &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsInt64()) {
    rv = m_val->value.GetInt64();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, uint32_t &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsUint()) {
    rv = m_val->value.GetUint();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, uint64_t &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsUint64()) {
    rv = m_val->value.GetUint64();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, float &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsFloat()) {
    rv = m_val->value.GetFloat();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, double &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsDouble()) {
    rv = m_val->value.GetDouble();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, std::string &rv) {
  m_val = m_doc->FindMember(lv);
  if (m_val != m_doc->MemberEnd() && m_val->value.IsString()) {
    rv = m_val->value.GetString();
  } else {
    rv = "";
  }
}

void EncapsluateJson::parse_Login(const char *lv, Login &rv) {
  parse("userid", rv.userid);
  parse("password", rv.password);
}

void EncapsluateJson::parse_Login_array(const char *lv,
                                        std::vector<Login> &rv) {
  m_val = m_doc->FindMember(lv);
  for (auto itr = m_val->value.Begin(); itr != m_val->value.End(); ++itr) {
    Login tmp;
    tmp.userid = itr->FindMember("userid")->value.GetString();
    tmp.password = itr->FindMember("password")->value.GetString();
    rv.push_back(tmp);
  }
}

std::string EncapsluateJson::GetResultCharacters() {
  StringBuffer sb;
  PrettyWriter<StringBuffer> writer(sb);
  m_doc->Accept(writer);
  return sb.GetString();
}

void EncapsluateJson::writeJson(const char *lv, const int32_t &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const int64_t &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const uint32_t &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const uint64_t &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const float &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const double &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeJson(const char *lv, const std::string &rv) {
  Value key(lv, m_allocator);
  Value keyVal;
  keyVal.SetString(rv.c_str(), rv.length(), m_allocator);
  m_doc->AddMember(key, keyVal, m_allocator);
}

void EncapsluateJson::writeObject(const char *lv, Value &rv) {
  Value key(lv, m_allocator);
  m_doc->AddMember(key, rv, m_allocator);
}

void EncapsluateJson::writeObject(Value& lv, Value &rv) {
  m_doc->AddMember(lv, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const int32_t rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const int64_t rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const uint32_t rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const uint64_t rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const float rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const double rv, Value &val) {
  Value key(lv, m_allocator);
  val.AddMember(key, rv, m_allocator);
}

void EncapsluateJson::Append(const char *lv, const std::string &rv,
        Value &val) {
  Value key(lv, m_allocator);
  Value keyVal;
  keyVal.SetString(rv.c_str(), rv.length(), m_allocator);
  val.AddMember(key, keyVal, m_allocator);
}
