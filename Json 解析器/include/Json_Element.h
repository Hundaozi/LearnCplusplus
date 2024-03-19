#pragma once
#include "error.h"
#include <cstddef>
#include <map>
#include <ostream>
#include <sstream>
#include <string_view>
#include <vector>

namespace hundaozi {
namespace json {
class JsonElement;
using JsonObject = std::map<std::string_view, JsonElement *>;
using JsonArray = std::vector<JsonElement *>;

class JsonElement {

public:
  enum class Type {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOL,
    JSON_NULL
  };
  Type get_type() { return type_; }

  union Value {
    JsonObject *value_object;
    JsonArray *value_array;
    std::string_view *value_string;
    float value_number;
    bool value_bool;
    std::nullptr_t value_null;
  };
  // 一系列重载
  auto value(JsonObject *value) {
    type_ = Type::JSON_OBJECT;
    value_.value_object = value;
  }
  auto value(JsonArray *value) {
    type_ = Type::JSON_ARRAY;
    value_.value_array = value;
  }
  auto value(std::string_view *value) {
    type_ = Type::JSON_STRING;
    value_.value_string = value;
  }
  auto value(float value) {
    type_ = Type::JSON_NUMBER;
    value_.value_number = value;
  }
  auto value(bool value) {
    type_ = Type::JSON_BOOL;
    value_.value_bool = value;
  }
  auto value(std::nullptr_t value) {
    type_ = Type::JSON_NULL;
    value_.value_null = nullptr;
  }

  JsonElement() : JsonElement(Type::JSON_NULL) {}

  JsonElement(const Type &type) : type_(type) {
    switch (type) {
    case Type::JSON_OBJECT:
      value_.value_object = new std::map<std::string_view, JsonElement *>;
      break;
    case Type::JSON_ARRAY:
      value_.value_array = new std::vector<JsonElement *>;
      break;
    case Type::JSON_STRING:
      value_.value_string = new std::string_view{""};
      break;
    case Type::JSON_NUMBER:
      value_.value_number = 0;
      break;
    case Type::JSON_BOOL:
      value_.value_bool = false;
      break;
    case Type::JSON_NULL:
      value_.value_null = nullptr;
      break;
    default:
      break;
    }
  };
  JsonElement(JsonObject *object) : type_(Type::JSON_OBJECT) {}
  JsonElement(JsonArray *array) : type_(Type::JSON_ARRAY) {}
  JsonElement(std::string_view *object) : type_(Type::JSON_STRING) {}
  JsonElement(float number) : type_(Type::JSON_NUMBER) {}
  JsonElement(bool val) : type_(Type::JSON_BOOL) {}
  JsonElement(std::nullptr_t value_null) : type_(Type::JSON_NULL) {}

  ~JsonElement() {}

  JsonArray *AsArray() {
    if (type_ == Type::JSON_ARRAY) {
      return value_.value_array;
    } else {
      Error("Type of JsonElement isn't JsonArray!");
      return nullptr;
    }
  }
  std::string_view *AsString() {
    if (type_ == Type::JSON_STRING) {
      return value_.value_string;
    } else {
      Error("Type of JsonElement isn't String!");
      return nullptr;
    }
  }

  auto AsNumber() {
    if (type_ == Type::JSON_NUMBER) {
      return value_.value_number;
    } else {
      Error("Type of JsonElement isn't Number!");
      return 0.0f;
    }
  }
  auto AsBoolean() {
    if (type_ == Type::JSON_BOOL) {
      return value_.value_bool;
    } else {
      Error("Type of JsonElement isn't Boolean!");
      return false;
    }
  }
  std::string_view Dumps() {
    std::stringstream ss;
    switch (type_) {
    case Type::JSON_OBJECT:
      ss << *(value_.value_object);
      break;
    case Type::JSON_ARRAY:
      ss << *(value_.value_array);
      break;
    case Type::JSON_STRING:
      ss << '\"' << *(value_.value_string) << '\"';
      break;
    case Type::JSON_NUMBER:
      ss << value_.value_number;
      break;
    case Type::JSON_BOOL:
      ss << (value_.value_bool == true ? "true" : "false");
      break;
    case Type::JSON_NULL:
      ss << "null";
      break;
    default:
      break;
    }
    return ss.str();
  }
  // 输出json对象
  friend std::ostream &operator<<(std::ostream &os, const JsonObject &object) {
    os << "{";
    for (auto it = object.begin(); it != object.end(); ++it) {
      os << '\"' << it->first << '\"' << ": " << it->second->Dumps();
      if (it != --object.end()) {
        os << ", ";
      }
    }
    os << "}";
    return os;
    // 输出json数值
    friend std::ostream &operator<<(std::ostream &os, const JsonArray &array) {
      os << "[";
      for (auto i = 0; i < array.size(); ++i) {
        os << array[i]->Dumps();
        if (i != array.size() - 1) {
          os << ", ";
        }
      }
      os << "]";
      return os;
    }

  private:
    Type type_;
    Value value_;
  };
} // namespace json
} // namespace hundaozi