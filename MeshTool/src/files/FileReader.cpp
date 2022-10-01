#include "FileReader.h"

#include <fstream>

bool FileReader::load(std::string path)
{
  std::ifstream in(path, std::ios::in | std::ios::binary);

  if (in)
  {
    in.seekg(0, std::ios::end);
    text.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&text[0], text.size());
    in.close();

    return true;
  }

  return false;
}

const std::string& FileReader::getText() const
{
  return text;
}
