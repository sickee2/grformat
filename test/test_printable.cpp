#include <gr/utf.sequence.hh>
#include <cassert>
#include <iostream>

using namespace gr::uc;
void test_is_printable_basic() {
  std::cout << "Testing basic printable characters..." << std::endl;

  // ASCII printable characters
  assert(codepoint('A').is_printable()); // Uppercase letter
  assert(codepoint('z').is_printable()); // Lowercase letter
  assert(codepoint('0').is_printable()); // Digit
  assert(codepoint('!').is_printable()); // Punctuation
  assert(codepoint(' ').is_printable()); // Space

  std::cout << "✓ Basic printable characters test passed" << std::endl;
}

void test_is_printable_control_chars() {
  std::cout << "Testing control characters..." << std::endl;

  // C0 control characters
  assert(!codepoint(0x0000).is_printable()); // NULL
  assert(!codepoint(0x0001).is_printable()); // SOH
  assert(!codepoint(0x000A).is_printable()); // LF (not printable)
  assert(!codepoint(0x000D).is_printable()); // CR (not printable)
  assert(!codepoint(0x001F).is_printable()); // US

  // C1 control characters
  assert(!codepoint(0x007F).is_printable()); // DEL
  assert(!codepoint(0x0080).is_printable()); // PAD
  assert(!codepoint(0x009F).is_printable()); // APC

  std::cout << "✓ Control characters test passed" << std::endl;
}

void test_is_printable_whitespace() {
  std::cout << "Testing whitespace characters..." << std::endl;

  // Printable whitespace characters
  assert(codepoint(0x0009).is_printable()); // Tab (printable)
  assert(codepoint(0x0020).is_printable()); // Space (printable)
  assert(codepoint(0x00A0).is_printable()); // No-Break Space
  assert(codepoint(0x1680).is_printable()); // Ogham Space Mark
  assert(codepoint(0x2000).is_printable()); // En Quad (space)
  assert(codepoint(0x3000).is_printable()); // Ideographic Space

  // Non-printable whitespace characters (control characters)
  assert(!codepoint(0x000A).is_printable()); // LF (not printable)
  assert(!codepoint(0x000D).is_printable()); // CR (not printable)

  std::cout << "✓ Whitespace characters test passed" << std::endl;
}

void test_is_printable_format_chars() {
  std::cout << "Testing format characters..." << std::endl;

  // Format characters should not be printable (excluding spaces)
  assert(!codepoint(0x2001).is_printable()); // Em Quad (format character)
  assert(!codepoint(0x200F).is_printable()); // Format character
  assert(!codepoint(0x2028).is_printable()); // Line Separator
  assert(!codepoint(0x202F).is_printable()); // Narrow No-Break Space
  assert(
      !codepoint(0x205F).is_printable()); // Medium Mathematical Space
  assert(!codepoint(0x206F).is_printable()); // Format character
  assert(!codepoint(0xFEFF).is_printable()); // BOM

  std::cout << "✓ Format characters test passed" << std::endl;
}

void test_is_printable_non_characters() {
  std::cout << "Testing non-characters..." << std::endl;

  // Non-character block 1
  assert(!codepoint(0xFDD0).is_printable());
  assert(!codepoint(0xFDEF).is_printable());

  // Non-character pattern (0xFFFE-0xFFFF)
  assert(!codepoint(0xFFFE).is_printable());
  assert(!codepoint(0xFFFF).is_printable());
  assert(!codepoint(0x1FFFE).is_printable());
  assert(!codepoint(0x10FFFF).is_printable()); // Maximum code point, but non-character

  std::cout << "✓ Non-characters test passed" << std::endl;
}

void test_is_printable_private_use() {
  std::cout << "Testing private use areas..." << std::endl;

  // Private Use Areas
  assert(!codepoint(0xE000).is_printable());   // PUA start
  assert(!codepoint(0xF8FF).is_printable());   // PUA end
  assert(!codepoint(0xF0000).is_printable());  // SPUA-A start
  assert(!codepoint(0xFFFFD).is_printable());  // SPUA-A end
  assert(!codepoint(0x100000).is_printable()); // SPUA-B start
  assert(!codepoint(0x10FFFD).is_printable()); // SPUA-B end

  std::cout << "✓ Private use areas test passed" << std::endl;
}

void test_is_printable_unicode_chars() {
  std::cout << "Testing Unicode characters..." << std::endl;

  // Various Unicode characters should be printable
  assert(codepoint(0x00A9).is_printable());  // © Copyright symbol
  assert(codepoint(0x263A).is_printable());  // ☺ Smiley face
  assert(codepoint(0x4E2D).is_printable());  // 中 Chinese character
  assert(codepoint(0x1F600).is_printable()); // 😀 Emoji

  std::cout << "✓ Unicode characters test passed" << std::endl;
}

void test_is_printable_invalid() {
  std::cout << "Testing invalid code points..." << std::endl;

  // Invalid code points
  assert(!codepoint(0x110000).is_printable()); // Beyond Unicode range
  assert(!codepoint(0xD800).is_printable());   // High surrogate
  assert(!codepoint(0xDFFF).is_printable());   // Low surrogate

  std::cout << "✓ Invalid code points test passed" << std::endl;
}

void test_is_whitespace() {
  std::cout << "Testing is_whitespace method..." << std::endl;

  // Whitespace characters
  assert(codepoint(0x0020).is_whitespace()); // Space
  assert(codepoint(0x0009).is_whitespace()); // Tab
  assert(codepoint(0x3000).is_whitespace()); // Ideographic Space

  // Non-whitespace characters
  assert(!codepoint('A').is_whitespace());    // Letter
  assert(!codepoint('0').is_whitespace());    // Digit
  assert(!codepoint(0x00A1).is_whitespace()); // ¡ Inverted exclamation mark
  assert(!codepoint(0x0085).is_whitespace()); // Next Line (C1 control character)

  std::cout << "✓ is_whitespace test passed" << std::endl;
}

void debug_is_printable() {
  codepoint tab(0x0009);

  std::cout << "Debugging Tab character (0x0009):" << std::endl;
  std::cout << "is_valid(): " << tab.is_valid() << std::endl;
  std::cout << "is_whitespace(): " << tab.is_whitespace() << std::endl;
  std::cout << "is_printable(): " << tab.is_printable() << std::endl;

  // Step-by-step check of is_printable() logic (using updated logic)
  if (!tab.is_valid()) {
    std::cout << "Failed: Invalid code point" << std::endl;
    return;
  }

  // ASCII fast path (updated logic)
  if (tab.value() <= 0x7F) {
    bool ascii_result = (tab.value() >= 0x20 && tab.value() != 0x7F) ||
                        (tab.value() >= 0x09 && tab.value() <= 0x0D);
    std::cout << "ASCII path result: " << ascii_result << std::endl;
    if (ascii_result) {
      std::cout << "Success: ASCII path returned true" << std::endl;
      return;
    } else {
      std::cout << "ASCII path returned false, continuing with further checks" << std::endl;
    }
  }

  // Control character check
  bool control_check = (tab.value() >= 0x0001 && tab.value() <= 0x0008) ||
                       (tab.value() >= 0x000E && tab.value() <= 0x001F) ||
                       (tab.value() >= 0x007F && tab.value() <= 0x009F);
  std::cout << "Control character check: " << control_check << std::endl;
  if (control_check) {
    std::cout << "Failed: Identified as control character" << std::endl;
    return;
  }

  // Format character check
  bool format_check = (tab.value() >= 0x2001 && tab.value() <= 0x200F) ||
                      (tab.value() >= 0x2028 && tab.value() <= 0x202F) ||
                      (tab.value() >= 0x205F && tab.value() <= 0x206F) ||
                      (tab.value() == 0xFEFF);
  std::cout << "Format character check: " << format_check << std::endl;
  if (format_check) {
    std::cout << "Failed: Identified as format character" << std::endl;
    return;
  }

  // Non-character check
  bool nonchar_check = (tab.value() >= 0xFDD0 && tab.value() <= 0xFDEF) ||
                       ((tab.value() & 0xFFFE) == 0xFFFE);
  std::cout << "Non-character check: " << nonchar_check << std::endl;
  if (nonchar_check) {
    std::cout << "Failed: Identified as non-character" << std::endl;
    return;
  }

  // Private Use Area check
  bool pua_check = (tab.value() >= 0xE000 && tab.value() <= 0xF8FF) ||
                   (tab.value() >= 0xF0000 && tab.value() <= 0xFFFFD) ||
                   (tab.value() >= 0x100000 && tab.value() <= 0x10FFFD);
  std::cout << "Private Use Area check: " << pua_check << std::endl;
  if (pua_check) {
    std::cout << "Failed: Identified as Private Use Area" << std::endl;
    return;
  }

  // Whitespace character check
  bool whitespace_check = tab.is_whitespace();
  std::cout << "Whitespace character check: " << whitespace_check << std::endl;
  if (whitespace_check) {
    std::cout << "Success: Identified as whitespace character" << std::endl;
  } else {
    std::cout << "Failed: Not identified as whitespace character" << std::endl;
  }
}

void test_printable(){
  debug_is_printable();
  std::cout << "Starting codepoint::is_printable() tests..." << std::endl;

  try {
    test_is_printable_basic();
    test_is_printable_control_chars();
    test_is_printable_whitespace();
    test_is_printable_format_chars();
    test_is_printable_non_characters();
    test_is_printable_private_use();
    test_is_printable_unicode_chars();
    test_is_printable_invalid();
    test_is_whitespace();

    std::cout << "\n🎉 All tests passed!" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "❌ Test failed: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "❌ Unknown test failure" << std::endl;
  }
}
