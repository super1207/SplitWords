#include <split_words.h>
#include <json/json.h>
#include <httplib.h>
#include <exception>

using namespace std;
using namespace httplib;

/* 忽略jsoncpp reader 的弃用警告 */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace std;

class MyException : public exception
{
public:
    MyException() : message("Error.") {}
    MyException(string str) : message(str) {}
    ~MyException() throw()
    {
    }
    virtual const char *what() const throw()
    {
        return message.c_str();
    }

private:
    string message;
};

vector<string> split_words(const string &input_str, double threshold)
{
    try
    {
        httplib::Client cli("http://api.pullword.com");
        httplib::Params params;
        params.emplace("source", input_str);
        auto res = cli.Get((append_query_params("/get.php", params) + "&param1=" + to_string(threshold) + "&param2=0&json=1").c_str());
        if (!res)
        {
            throw MyException("get response error:the response is null");
        }
        if (res->status != 200)
        {
            throw MyException("the response code is not 200:" + to_string(res->status));
        }
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(res->body, root) || !root.isArray())
        {
            throw MyException("the response json can't be parse:" + res->body);
        }
        vector<string> ret_vec;
        try
        {
            for (auto &it : root)
            {
                ret_vec.push_back(it["t"].asString());
            }
        }
        catch (const std::exception &e)
        {
            throw MyException("can't get data from the response json:" + res->body + e.what());
        }
        return ret_vec;
    }
    catch (const MyException &e)
    {
        throw runtime_error(e.what());
    }
    catch (const exception &e)
    {
        throw runtime_error(string("unkonw error:") + e.what());
    }
}

vector<string> split_words_jb(const string &input_str)
{
    try
    {
        httplib::Client cli("http://cppjieba-webdemo.herokuapp.com");
        httplib::Params params;
        params.emplace("sentence", input_str);
        auto res = cli.Post("/",params);
        if (!res)
        {
            throw MyException("get response error:the response is null");
        }
        if (res->status != 200)
        {
            throw MyException("the response code is not 200:" + to_string(res->status));
        }
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(res->body, root) || !root.isArray())
        {
            throw MyException("the response json can't be parse:" + res->body);
        }
        vector<string> ret_vec;
        try
        {
            for (auto &it : root)
            {
                ret_vec.push_back(it.asString());
            }
        }
        catch (const std::exception &e)
        {
            throw MyException("can't get data from the response json:" + res->body + e.what());
        }
        return ret_vec;
    }
    catch (const MyException &e)
    {
        throw runtime_error(e.what());
    }
    catch (const exception &e)
    {
        throw runtime_error(string("unkonw error:") + e.what());
    }
}