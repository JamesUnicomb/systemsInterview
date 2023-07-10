#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include "md5.h"
using namespace std;

#define TRACE(msg) wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"

string baseurl = "http://localhost:8081/";
unordered_map<string, string> dictionary;

void handle_get(http_request request)
{
    TRACE(L"\nhandle GET\n");

    string s = request.relative_uri().to_string().c_str();
    s.erase(0, 1);

    wcout << request.relative_uri().to_string().c_str() << endl;

    http_response response(status_codes::MovedPermanently);
    response.headers().add(U("Location"), U(dictionary.find(s)->second));
    response.headers().add(U("Connection"), U("close"));

    request.reply(response);
}

void handle_request(
    http_request request,
    function<void(json::value const &, json::value &)> action)
{
    auto answer = json::value::object();

    request
        .extract_json()
        .then([&answer, &action](pplx::task<json::value> task)
              {
         try
         {
            auto const & jvalue = task.get();

            if (!jvalue.is_null())
            {
               action(jvalue, answer);
            }
         }
         catch (http_exception const & e)
         {
            wcout << e.what() << endl;
         } })
        .wait();

    request.reply(status_codes::OK, answer);
}

void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    handle_request(
        request,
        [](json::value const &jvalue, json::value &answer)
        {
            if (jvalue.has_field(utility::string_t("url")))
            {
                string url = jvalue.as_object().find(utility::string_t("url"))->second.as_string().c_str();
                string sh = md5(url);

                dictionary.insert({sh, url});

                string r = baseurl + sh;
                answer[utility::string_t("redirect")] = json::value::string(r);
            }
            else
            {
                answer[utility::string_t("error")] = json::value::string(utility::string_t("url not input"));
            }
        });
}

int main()
{
    http_listener listener(baseurl);

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);

    try
    {
        listener
            .open()
            .then([&listener]()
                  { TRACE(L"\nstarting to listen\n"); })
            .wait();

        while (true)
            ;
    }
    catch (exception const &e)
    {
        wcout << e.what() << endl;
    }

    listener.support(methods::GET, handle_get);
}