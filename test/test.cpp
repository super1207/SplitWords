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