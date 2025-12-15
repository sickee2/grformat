import gr.tools;

int main(){
  using namespace gr;
  auto fmt = toy::format("{}", 1234);
  console::writeln(fmt);
  return 0;
}
