#include "test.hh"
#include "gr/format.hh"
#include <gr/logger.hh>
#include "gr/performance.hh"
#include <charconv>
#include <cstdint>
#include <fmt/format.h>
#include <gr/console.hh>
using namespace gr;
// namespace term = gr::console;

void test_float_fmt_vs_toy_fmt() {
  float data[] = {
      3.141592653589793f, 31.41592653589793f, 314.1592653589793f,
      3141.592653589793f, 31415.92653589793f,
  };
  double data_d[] = {
      3.141592653589793, 31.41592653589793, 314.1592653589793,
      3141.592653589793, 31415.92653589793,
  };

  double test_cases[] = {
      // 常规值
      0.0,
      1.0,
      10.0,
      100.0,
      1000.0,
      0.1,
      0.01,
      0.001,
      123.456,
      123456.789,
      0.000123456,
      123456789.0,

      // 边界值
      1e-308,       // double 最小值
      1e308,        // double 最大值
      2.22507e-308, // 最小正规格化数

      // 特殊值
      std::numeric_limits<double>::infinity(),
      -std::numeric_limits<double>::infinity(),
      std::numeric_limits<double>::quiet_NaN(),

      // 负数
      -3.141592653589793,
      -31415.92653589793,
      -1e-308,
  };
  console::writeln("== float test fixed");
  unsigned iteration = 100000;
  {
    performance::timer timer("fmt");
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = fmt::format("{:.4f}", v);
      }
    }
  }
  {
    performance::timer timer("toy");
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = toy::format("{:.4f}", v);
      }
    }
  }
  console::writeln("== float test scientific");
  {
    performance::timer timer("fmt");
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = fmt::format("{:.4e}", v);
      }
    }
  }
  {
    performance::timer timer("toy");
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = toy::format("{:.4e}", v);
      }
    }
  }

  console::writeln("\n=======================================");
  console::writeln("==== float test");
  for (auto v : data) {
    // auto result_fmt_fixed = fmt::format("{:.4f}", v);
    // auto result_toy_fixed = toy::format("{:.4f}", v);
    auto result_fmt_sci = fmt::format("{:.4e}", v);
    auto result_toy_sci = toy::format("{:.4e}", v);
    // console::writeln("fixed :{} => {}", result_fmt_fixed, result_toy_fixed);
    console::writeln("scientific :{} => {}", result_fmt_sci, result_toy_sci);
  }
  console::writeln("\n==== double test");
  for (auto v : data_d) {
    // auto result_fmt_fixed = fmt::format("{:.4f}", v);
    // auto result_toy_fixed = toy::format("{:.4f}", v);
    auto result_fmt_sci = fmt::format("{:.4e}", v);
    auto result_toy_sci = toy::format("{:.4e}", v);
    // console::writeln("fixed :{} => {}", result_fmt_fixed, result_toy_fixed);
    console::writeln("scientific :{} => {}", result_fmt_sci, result_toy_sci);
  }

  console::writeln("\n==== test cases");
  for (auto v : test_cases) {
    try {
      auto result_fmt = fmt::format("{:.6e}", v);
      auto result_toy = toy::format("{:.6e}", v);

      // 对于 NaN，直接比较字符串可能有问题
      if (std::isnan(v)) {
        console::writeln("NaN test: fmt='{}', toy='{}'", result_fmt,
                         result_toy);
      } else {
        console::writeln("{:.6e} => fmt='{}', toy='{}'", v, result_fmt,
                         result_toy);
      }
    } catch (const std::exception &e) {
      console::writeln("Error for {}: {}", v, e.what());
    }
  }

  console::writeln("\n==== test cases general");
  for (auto v : test_cases) {
    auto result_fmt = fmt::format("{:g}", v);
    auto result_toy = toy::format("{:g}", v);
    console::writeln("{:g} => fmt='{}', toy='{}'", v, result_fmt, result_toy);
  }
}

void test_integer_fmt_vs_toy() {
  int64_t data[] = {
      -31415926535,   314159265358,     3141592653589,
      31415926535897, 3141592653589793,
  };

  // console::writeln("{}", data[0]);

  unsigned iteration = 100000;

  console::writeln("\n== test iteration {}", iteration);

  console::writeln("\n== test integer base 10");
  uint64_t fmt_dur = 0, toy_dur = 0;
  {
    performance::timer timer("fmt", fmt_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = fmt::format("{}", v);
      }
    }
  }
  {
    performance::timer timer("toy", toy_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = toy::format("{}", v);
      }
    }
  }

  console::writeln(" ==> {:.1f}%", (double)(fmt_dur) / toy_dur * 100);

  console::writeln("\n== test integer base 16");
  {
    performance::timer timer("fmt", fmt_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = fmt::format("{:x}", v);
      }
    }
  }
  {
    performance::timer timer("toy", toy_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = toy::format("{:x}", v);
      }
    }
  }

  console::writeln(" ==> {:.1f}%", (double)(fmt_dur) / toy_dur * 100);

  console::writeln("\n== test integer base 8");
  {
    performance::timer timer("fmt", fmt_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = fmt::format("{:o}", v);
      }
    }
  }
  {
    performance::timer timer("toy", toy_dur);
    for (unsigned i = 0; i < iteration; i++) {
      for (auto v : data) {
        auto result = toy::format("{:o}", v);
      }
    }
  }
  console::writeln(" ==> {:.1f}%", (double)(fmt_dur) / toy_dur * 100);
}
void micro_benchmark() {
  console::writeln("\n== Integer formatting breakdown");

  unsigned loop = 1;
  int64_t test_value = 31415;
  unsigned iteration = 100000;

  for (unsigned lp = 0; lp < loop; lp++) {
    console::writeln("loop iteration {}", lp);
    {
      uint64_t itoss_time = 0;
      performance::timer timer("\tstd::to_chars", itoss_time);
      for (unsigned i = 0; i < iteration; i++) {
        char buffer[32]{};
        auto [ptr, len] = std::to_chars(buffer, buffer + 32, test_value, 10);
        (void)ptr;
      }
    }
    {
      uint64_t itoss_time = 0;
      performance::timer timer("\titoss only", itoss_time);
      for (unsigned i = 0; i < iteration; i++) {
        char buffer[32]{};
        auto [ptr, len] = toy::itoss(buffer, 32, test_value, 10);
        (void)ptr;
      }
    }
    {
      uint64_t itoss_time = 0;
      performance::timer timer("\tcopy n itoss only", itoss_time);
      for (unsigned i = 0; i < iteration; i++) {
        char buffer[32]{};
        auto [ptr, len] = toy::itoss(buffer, 32, test_value, 10);
        // str::u8 buffer_content;
        toy::format_output_context buffer_content;
        buffer_content.reserve(128);
        toy::format_output out(buffer_content);
        out.put(ptr, len);
        (void)out;
      }
    }
    {
      uint64_t itoss_time = 0;
      performance::timer timer("\tcopy 3 times itoss only", itoss_time);
      // str::u8 buffer_content;
      toy::format_output_context buffer_content;
      toy::format_output out(buffer_content);
      for (unsigned i = 0; i < iteration; i++) {
        for(int j = 0; j < 3; j++){
          char buffer[32]{};
          auto [ptr, len] = toy::itoss(buffer, 32, test_value, 10);
          out.put(ptr, len);
        }
        (void)out;

      }
    }

    {
      uint64_t itoss_time = 0;
      performance::timer timer("\tcopy 3 times toy::detail::format_integer_impl", itoss_time);
      // str::u8 buffer_content;
      toy::format_output_context buffer_content;
      toy::format_output out(buffer_content);
      toy::format_spec spec;
      spec.type = 'd';
      for (unsigned i = 0; i < iteration; i++) {
        for(int j = 0; j < 3; j++){
          toy::detail::format_integer_impl(out, test_value, spec);
        }
        (void)out;

      }
    }

    {
      uint64_t toy_format_time = 0;
      performance::timer timer("\ttoy::format", toy_format_time);
      for (unsigned i = 0; i < iteration; i++) {
        auto s = toy::format("{}", test_value);
        (void)s;
      }
    }
    {
      uint64_t fmt_format_time = 0;
      performance::timer timer("\tfmt::format", fmt_format_time);
      for (unsigned i = 0; i < iteration; i++) {
        auto s = fmt::format("{}", test_value);
        (void)s;
      }
    }
    uint64_t toy_format_time = 0;
    {
      performance::timer timer("\ttoy::format multity {} {} {}", toy_format_time);
      for (unsigned i = 0; i < iteration; i++) {
        auto s = toy::format("{2} {1} {0}", test_value + 1, test_value + 2, test_value + 3);
        (void)s;
      }
    }
    uint64_t fmt_format_time = 0;
    {
      performance::timer timer("\tfmt::format multity {} {} {}", fmt_format_time);
      for (unsigned i = 0; i < iteration; i++) {
        auto s = fmt::format("{2} {1} {0}", test_value + 1, test_value + 2, test_value + 3);
        (void)s;
      }
    }
    console::writeln("\tdifference: {}", toy_format_time - fmt_format_time);
  }
}

struct format_spec {
  format_spec() = default;
  int16_t width = -1;
  int16_t precision = -1;
  unsigned char fill = ' ';
  unsigned char align = '\0';
  unsigned char type = '\0';
  unsigned char sign:6 = '-';
  bool alternate:2 = false;
  const char *fmt_beg = nullptr;
  const char *fmt_end = nullptr;
  inline str::u8v get_pattern() const {
    return str::u8v(fmt_beg, fmt_end - fmt_beg);
  }
};



int main() {

  // toy::xbuf x;
  // x.reserve(100);
  // x.append("abcd");
  //
  // console::writeln("{}", x);
  // gr::str::u8 ss;
  // ss.hack_with_cbuf(x.to_cbuf());

  // console::writeln("{}", 123);
  // test_float_fmt_vs_toy_fmt();

  // test_integer_fmt_vs_toy();

  micro_benchmark();
  // console::writeln("sizeof spec: {}", sizeof(format_spec));
  //
  // const char* pattern = "test";
  // format_spec spec{};
  // spec.type = 'd';
  // console::writeln("{} {}", spec.type, char(spec.sign));
  // spec.sign = '+';
  // spec.fmt_beg = pattern;
  // console::writeln("{} {}", spec.type, char(spec.sign));
  //
  // console::writeln("{:b} {:b} | {:b} {:b} {:b}", '-', '+', '<', '>', '^');
  return 0;
}
