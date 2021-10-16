# Split_Words

## 简介

基于 [http://api.pullword.com/](http://api.pullword.com/) 的在线中文分词库。

## 编译环境

* 支持 C++11 以上的编译器
* CMake 3.15 及以上
* Git
* 能访问 Github 的网络

## 使用

```cpp
#include <split_words.h>
#include <iostream>

using namespace std;

int main()
{
    while (true)
    {
        try
        {
            string input;
            cout << "输入一句话：" << endl;
            getline(cin, input);
            cout << "您输入的是：'" << input << "'" << endl;
            if (input == "exit")
                break;
            //第二个参数的范围是[0,1]，越小出现的词越多
            vector<string> vec = split_words(input, 0.5);
            cout << "分词结果如下：" << endl;
            for (size_t i = 0; i < vec.size(); ++i)
            {
                cout << i + 1 << "：\t'" << vec[i] << "'" << endl;
            }
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << "\n";
        }
    }
    return 0;
}
```

Hava fun ！

## 开源协议

WTFPL
