/* 
    A simple HTTP server that handles GET and POST requests.
    author: Quy Tran <tranphuquy19@gmail.com>
    date: 2021-09-09
    version: 1.0

    Build command: gcc http-server.cpp -lstdc++ -o http-server.out
    Usage: ./http-server.out [port=8080]
*/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <map>

#define PORT 8080

using namespace std;

string get_accept(string request);
string get_accept_encoding(string request);
string get_endpoint(string request);
string get_host(string request);
string get_http_version(string request);
string get_user_agent(string request);

string render_http_template(string strTemplate, std::string data[]);
string render_http_template(string strTemplate, map<string, string> data);
string read_text_file(string file_path);

string decode_uri_component(string uri);

map<string, string> parse_request(string request);
map<string, string> parse_body_post_request(string request);
void print_body_request(map<string, string> data);

// create a socket and bind it to a port
int create_socket(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        cerr << "Error creating socket" << endl;
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        cerr << "Error binding socket" << endl;
        exit(1);
    }

    return sock;
}

// listen for connections on a socket
void listen_socket(int sock)
{
    if (listen(sock, 5) < 0)
    {
        cerr << "Error listening on socket" << endl;
        exit(1);
    }
}

// accept a connection on a socket
int accept_connection(int sock)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0)
    {
        cerr << "Error accepting connection" << endl;
        exit(1);
    }
    return client_sock;
}

// read a request from a socket
string read_request(int sock)
{
    char buffer[1024];
    int n = read(sock, buffer, sizeof(buffer));
    if (n < 0)
    {
        cerr << "Error reading from socket" << endl;
        exit(1);
    }
    return string(buffer);
}

// write a response to a socket
void write_response(int sock, string response)
{
    write(sock, response.c_str(), response.length());
}

void redirect(string response, string url)
{
    response = "HTTP/1.1 301 Moved Permanently\r\n";
    response += "Location: " + url + "\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: 0\r\n";
    response += "\r\n";
}

// handle a GET request
void handle_get(int sock, string request)
{
    string html = read_text_file("index.html");
    string htmlRendered = render_http_template(html, {
            {"title", "Hello, World!"},
            {"header", "Hello, World!"},
            {"content", "This is a simple HTTP server."},
        });

    string response = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Content-Length: " +
                      std::to_string(htmlRendered.length()) + "\r\n"
                                                              "\r\n" +
                      htmlRendered;

    write_response(sock, response);
}

// handle a POST request
void handle_post(int sock, string request)
{
    map<string, string> data = parse_body_post_request(request);
    // print_body_request(data);
    data["header"] = "Hello, World!";
    string html = read_text_file("profile.html");
    string htmlRendered = render_http_template(html, data);

    string response = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Content-Length: " +
                      std::to_string(htmlRendered.length()) + "\r\n"
                                                              "\r\n" +
                      htmlRendered;

    write_response(sock, response);
}

// handle a request
void handle_request(int sock, string request)
{
    string method = request.substr(0, request.find(" "));
    if (method == "GET")
    {
        handle_get(sock, request);
    }
    else if (method == "POST")
    {
        handle_post(sock, request);
    }
    else
    {
        string response = "HTTP/1.1 404 Not Found\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: 12\r\n"
                          "\r\n"
                          "Hello, world!\r\n";

        write_response(sock, response);
    }
}

// handle a client
void handle_client(int sock)
{
    string request = read_request(sock);

    cout << "HOST: " << get_host(request) << endl;
    cout << "USER-AGENT: " << get_user_agent(request) << endl;
    cout << "ACCEPT: " << get_accept(request) << endl;
    cout << "ACCEPT-ENCODING: " << get_accept_encoding(request) << endl;
    cout << "HTTP-VERSION: " << get_http_version(request) << endl;
    cout << "ENDPOINT: " << get_endpoint(request) << endl;
    cout << "===============================" << endl;

    handle_request(sock, request);
    close(sock);
}

string get_endpoint(string request)
{
    string endpoint = request.substr(request.find(" ") + 1);
    endpoint = endpoint.substr(0, endpoint.find(" "));
    return endpoint;
}

string get_http_version(string request)
{
    string http_version = request.substr(request.find("HTTP/") + 5);
    http_version = http_version.substr(0, http_version.find("\r\n"));
    return http_version;
}

string get_user_agent(string request)
{
    string user_agent = request.substr(request.find("User-Agent: ") + 12);
    user_agent = user_agent.substr(0, user_agent.find("\r\n"));
    return user_agent;
}

string get_host(string request)
{
    string host = request.substr(request.find("Host: ") + 6);
    host = host.substr(0, host.find("\r\n"));
    return host;
}

string get_accept(string request)
{
    string accept = request.substr(request.find("Accept: ") + 8);
    accept = accept.substr(0, accept.find("\r\n"));
    return accept;
}

string get_accept_encoding(string request)
{
    string accept_encoding = request.substr(request.find("Accept-Encoding: ") + 17);
    accept_encoding = accept_encoding.substr(0, accept_encoding.find("\r\n"));
    return accept_encoding;
}

string render_http_template(string strTemplate, std::string data[])
{
    string result = strTemplate;
    for (int i = 0; i < data->length(); i++)
    {
        result = result.replace(result.find("{" + data[i] + "}"), data[i].length() + 2, data[i]);
    }
    return result;
}

string render_http_template(string strTemplate, map<string, string> data)
{
    string result = strTemplate;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        result = result.replace(result.find("{" + it->first + "}"), it->first.length() + 2, it->second);
    }
    return result;
}

string read_text_file(string file_name)
{
    ifstream file(file_name);
    string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return str;
}

map<string, string> parse_request(string request)
{
    map<string, string> data;
    string key = "";
    string value = "";
    bool is_key = true;
    for (int i = 0; i < request.length(); i++)
    {
        if (request[i] == '=')
        {
            is_key = false;
        }
        else if (request[i] == '&')
        {
            data[key] = value;
            key = "";
            value = "";
            is_key = true;
        }
        else
        {
            if (is_key)
            {
                key += request[i];
            }
            else
            {
                value += request[i];
            }
        }
    }
    data[key] = value;
    return data;
}

map<string, string> parse_body_post_request(string request)
{
    string body = request.substr(request.find("\r\n\r\n") + 4);
    body = decode_uri_component(body);
    return parse_request(body);
}

string decode_uri_component(string uri)
{
    string result = "";
    for (int i = 0; i < uri.length(); i++)
    {
        if (uri[i] == '%')
        {
            string hex = uri.substr(i + 1, 2);
            int value = std::stoi(hex, nullptr, 16);
            result += char(value);
            i += 2;
        }
        else
        {
            result += uri[i];
        }
    }
    return result;
}

void print_body_request(map<string, string> data)
{
    for (auto it = data.begin(); it != data.end(); it++)
    {
        cout << it->first << ": " << decode_uri_component(it->second) << endl;
    }
}

// main function
int main(int argc, char *argv[])
{
    int port = PORT;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }
    else
    {
        cout << "Using default port: " << PORT << endl;
    }

    int sock = create_socket(port);
    listen_socket(sock);

    cout << "Listening on port " << port << endl;

    while (true)
    {
        int client_sock = accept_connection(sock);
        handle_client(client_sock);
    }

    return 0;
}