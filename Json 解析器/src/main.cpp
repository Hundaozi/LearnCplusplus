
#include <any>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
struct JSONObject {
  // std::monostate
  // std::monostate类型通常在函数签名中作为占位符，用于表示某个函数不接受任何参数或不返回任何数据。
  std::variant<std::monostate,                             // null
               bool,                                       // true
               int,                                        // 1234
               double,                                     // 3.14
               std::string,                                // hello
               std::vector<JSONObject>,                    // 向量
               std::unordered_map<std::string, JSONObject> //{"hello":4490,
                                                           //"lulu":11111}
               >
      inner;

  std::any do_print() const { printf(inner); }
};
// std::string_view记录了对应的字符串指针和偏移位置，无需管理内存，相对std::string拥有一份字符串拷贝，如字符串查找和拷贝，效率更高
JSONObject parse(std::string_view json) {
  if (json.empty()) {
    return JSONObject{std::nullptr_t{}}; // null
  }
  if ('0' <= json[0] && json[0] <= '9') {
    return JSONObject{int{json[0] - '0'}}; // 整数
  }
  return JSONObject{std::nullptr_t{}};
};

int main() {
  std::string_view str3 = "123456789";
  std::cout << str3;
  parse(str3).do_print();
  return 0;
}