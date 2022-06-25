#include <string>


std::string getUrl(std::string text)
{
    int url_start = text.find("http");
    int url_end = text.find("\"", url_start + 1);
    return text.substr(url_start, url_end - url_start);
}
