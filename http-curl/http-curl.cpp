#define BUILDING_LIBCURL // 解决：无法解析的外部符号 __imp__curl_easy_init

#include <iostream> // 提供：cout、string
#include <curl/curl.h> // 提供：curl
#include <json/json.h> // 提供：json

using namespace std;

// 数据的获取
// 参见：https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
static size_t cb(void* data, size_t size, size_t nmemb, void* userp)
{
	string* str = dynamic_cast<string*>((string*)userp);

	if (0 == size || NULL == data) {
		return -1;
	}

	char* char_data = (char*)data;
	str->append(char_data, nmemb * size);
	return nmemb * size;
}

// http 请求
int http(string url, string method, char body[], int& http_code, string& chunk)
{
	char* version = curl_version(); // libcurl 版本
	cout << "curl_version：" << version << endl;

	CURL* curl_handle = curl_easy_init(); // 启动 libcurl 简单会话，参见：https://curl.se/libcurl/c/curl_easy_init.html

	int code; // curl 代码

	code = curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str()); // 设置 URL，参见：https://curl.se/libcurl/c/curl_easy_setopt.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb); // 将所有数据发送到此函数，参见：https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk); // 我们将‘chunk’结构传递给回调函数，参见：https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html

	if (method == "GET")
	{
		// GET 请求

	}
	else if (method == "POST") {
		// POST 请求

		// Header
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "content-type:application/json");
		code = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

		code = curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, body); // 设置POST的数据
	}
	else {
		// 使用 GET 请求

	}

	code = curl_easy_perform(curl_handle); // 执行阻塞文件传输，参见：https://curl.se/libcurl/c/curl_easy_perform.html

	code = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code); // 获取 http 响应代码，参见：https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html ，参见：https://everything.curl.dev/libcurl-http/responses#http-response-code

	curl_easy_cleanup(curl_handle); // 结束一个 libcurl 简单句柄，参见：https://curl.se/libcurl/c/curl_easy_cleanup.html

	if (code == CURLcode::CURLE_OK)
	{
		// curl 正常

		if (http_code == 200)
		{
			// http 正常

			const char* str = chunk.data();

			Json::CharReaderBuilder b;
			Json::CharReader* reader(b.newCharReader());
			Json::Value root;
			JSONCPP_STRING errs;
			bool ok = reader->parse(str, str + strlen(str), &root, &errs);
			if (ok && errs.size() == 0)
			{
				string uuid = root["uuid"].asString();

				cout << "uuid：" << uuid << endl;
			}
			delete reader;
		}

	}

	return code;
}


int main()
{
	string url = "http://127.0.0.1:8080/ma";
	string method = "POST";
	char body[] = "{\"msg\"=\"hello\"}";

	int http_code; // http 代码
	string chunk; // http 响应

	int curl_code = http(url, method, body, http_code, chunk);

	cout << endl;
	cout << "curl 调用结束：" << endl;
	cout << "curl_code：" << curl_code << endl;
	cout << "http_code：" << http_code << endl;
	cout << "response_data：" << chunk << endl;

	cout << endl;
	cout << "curl 响应代码：" << endl;
	cout << CURLE_OK << "：正常" << endl;
	cout << CURLE_COULDNT_CONNECT << "：无法连接" << endl;

	cout << endl;
	cout << "http 响应代码：" << endl;
	cout << 200 << "：正常" << endl;
	cout << 404 << "：未发现" << endl;
	cout << 405 << "：方法不允许" << endl;
	cout << 500 << "：异常" << endl;
	cout << "其他代码：请参考：https://baike.baidu.com/item/HTTP%E7%8A%B6%E6%80%81%E7%A0%81/5053660" << endl;

	return 0;
}
