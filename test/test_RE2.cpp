#include <gr/console.hh>

void test_re2(){
  using namespace gr;
  using namespace gr::console;
  // 原始字符串包含数字
  gr::str::u8 text = "Hello world! Email: test@example.com, Phone: 123-456-7890, ID: 98765";

  writeln("--> spilt by re2: ");
  auto array = text.split_by_re2(R"(\s+)");
  for(auto &i : array){
    writeln("[{}] ",i);
  }
  writeln();
  // 先测试提取功能，再测试替换
  writeln("Original: {}", text);

  // 1. 先提取数字
  bool has_digits = text.contains(R"(\d+)");
  writeln("Contains digits: {}", has_digits);

  writeln("--> extract by re2: ");
  auto all_numbers = text.extract_all(R"(\d+)");
  writeln("All numbers: ");
  for (const auto& num : all_numbers) {
    write("{} ", num);
  }
  writeln();

  // 2. 提取电话号码
  writeln("--> extract phone number by re2: ");
  auto phone_number = text.extract(R"((\d{3}-\d{3}-\d{4}))");
  writeln("{}", phone_number);

  writeln("--> replace phone number by re2: ");
  // 3. 然后替换电话号码
  text.replace_by_re2_inplace(R"(\d{3}-\d{3}-\d{4})", "***-***-****");
  writeln("After phone replacement: {}", text);

  // 4. 验证替换后是否还有数字（ID部分）
  has_digits = text.contains(R"(\d+)");
  writeln("Still contains digits after replacement: {}", has_digits);

  // 5. 迭代器拷贝
  gr::str::u8 k(text.begin(), text.end());
  writeln("-->: {}", k);
}

