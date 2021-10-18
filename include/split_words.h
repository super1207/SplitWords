#pragma once

#include <vector>
#include <string>

std::vector<std::string> split_words(const std::string & input_str,double threshold);

//基于结巴分词器的在线演示，不要滥用，仅做测试
std::vector<std::string> split_words_jb(const std::string & input_str);


