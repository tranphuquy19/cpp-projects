/* 
    A Simple HTTP file sender
    author: Quy Tran <tranphuquy19@gmail.com>
    date: 2021-09-09
    version: 1.0

    Build command: gcc file-client.cpp -lstdc++ -lcurl -o file-client.out
    Usage: ./file-client.out [url] [method] [data]
*/

#include <iostream>
#include <curl/curl.h>
#include <sys/stat.h>

void send_file_data_to_server(const char *file_name, const char *server_url)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    struct stat file_info;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(file_name, "rb");
        curl_easy_setopt(curl, CURLOPT_URL, server_url);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) -1);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: file-client <file_name> <server_url>" << std::endl;
        return 1;
    }
    send_file_data_to_server(argv[1], argv[2]);
}