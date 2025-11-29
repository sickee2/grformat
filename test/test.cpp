// filepath: src/main.cpp
#include <gr/detail/toy_charconv.hh>
#include <gr/console.hh>

using namespace gr;
// namespace term = gr::console;

void test_re2();
void test_cbuf();
void test_chars_conv_performance();
void test_utf_convert();
void test_utf_iter();
void test_utf_iter2();
void test_cptr();
void test_endian();
void test_toy_format();
void test_toy_format_preformance();
void test_from_chars();
void test_iconv();
void test_logger();
void test_print();
void test_printable();
void test_stoi();
void test_utrim();
void test_upper_lower();
void test_utf_string();
void test_utf_iter_performance();

int main(){
  // test_re2();
  // test_cbuf();
  // test_chars_conv_performance();
  // test_utf_convert();
  // test_utf_iter();
  // test_utf_iter2();
  // test_cptr();
  // test_endian();
  // test_toy_format();
  // test_toy_format_preformance();
  // test_from_chars();
  // test_iconv();
  // test_logger();
  // test_print();
  // test_printable();
  // test_stoi();
  // test_utrim();
  // test_upper_lower();
  // test_utf_string();
  test_utf_iter_performance();

  // console::writeln("=== Testing explicit indexing with nested format ===");
  // for (int i = 0; i < 5; i++) {
  //   console::writeln("|{1:>{0}d}{2:>{3}}", i + 1, i, '|', 5 - i);
  // }

  // console::writeln("=== Testing automatic indexing with nested format ===");
  // for (int i = 0; i < 5; i++) {
  //   console::writeln("|{:>{}d}|", i + 1, 4);
  // }

  // console::writeln("|{1:>{0}}|", 3, 4);
  // console::writeln("|{:>{}}|", 1, 3);
  // for(int i = 1; i < 10; i++){
  //   console::writeln("|{:>{}}|", i, i);
  // }

  // console::writeln("|{0:>{1}.{2}f}|", 3.1415926, 20, 3);
  // console::writeln("|{:>{}}|", "hello", 20);
  return 0;
}
