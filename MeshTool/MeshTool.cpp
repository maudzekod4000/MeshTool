#include <iostream>

#include "lib/rapidjson-1.1.0/rapidjson.h"
#include "lib/rapidjson-1.1.0/writer.h"
#include "lib/rapidjson-1.1.0/stringbuffer.h"
#include "lib/rapidjson-1.1.0/document.h"

#include "src/files/FileReader.h"

using namespace rapidjson;
using namespace std;
int main()
{
  FileReader reader;
  reader.load("task_input/pyramid.json");
  cout << reader.getText() << endl;
  reader.~FileReader();
  
  // 1. Parse a JSON string into DOM.
  const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
  Document d;
  d.Parse(json);

  // 2. Modify it by DOM.
  Value& s = d["stars"];
  s.SetInt(s.GetInt() + 1);

  // 3. Stringify the DOM
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  d.Accept(writer);

  // Output {"project":"rapidjson","stars":11}
  std::cout << buffer.GetString() << std::endl;
  return 0;
}
