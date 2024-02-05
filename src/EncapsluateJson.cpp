#include "EncapsluateJson.h"
#include "json_struct_def.h"
#include "struct_def.h"

EncapsluateJson::EncapsluateJson(const char *json) : m_doc(new Document()) {
  m_doc->Parse(json);
}

EncapsluateJson::~EncapsluateJson() {}

void EncapsluateJson::parse(const char *lv, int32_t &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsInt()) {
    rv = it->value.GetInt();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, int64_t &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsInt64()) {
    rv = it->value.GetInt64();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, uint32_t &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsUint()) {
    rv = it->value.GetUint();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, uint64_t &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsUint64()) {
    rv = it->value.GetUint64();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, float &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsFloat()) {
    rv = it->value.GetFloat();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, double &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsDouble()) {
    rv = it->value.GetDouble();
  } else {
    rv = -1;
  }
}

void EncapsluateJson::parse(const char *lv, std::string &rv) {
  const auto &it = m_doc->FindMember(lv);
  if (it != m_doc->MemberEnd() && it->value.IsString()) {
    rv = it->value.GetString();
  } else {
    rv = "";
  }
}

void EncapsluateJson::parse_Login(const char* lv, Login& rv) {
    JsonLogin mylogin(&rv, sizeof(rv)/sizeof(Login));
    for (auto x : mylogin) {
        parse("userid", x.userid);
        rv.userid = x.userid;
        parse("password", x.password);
        rv.password = x.password;
    }
}

void EncapsluateJson::parse_Login_array(const char* lv, std::vector<Login>& rv) {
    for (auto y : mylogin) {
        parse("userid", y.userid);
        parse("password", y.password);
        x.userid = y.userid;
        x.password = y.password;
    }
}
