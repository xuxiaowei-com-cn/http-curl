#define BUILDING_LIBCURL // 解决：无法解析的外部符号 __imp__curl_easy_init

#include <iostream> // 提供：cout、string
#include <curl/curl.h> // 提供：curl

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

int http(const string url)
{
	char* version = curl_version(); // libcurl 版本
	cout << "curl_version：" << version << endl;

	CURL* curl_handle = curl_easy_init(); // 启动 libcurl 简单会话，参见：https://curl.se/libcurl/c/curl_easy_init.html

	int code; // curl 代码
	int http_code; // http 代码
	string chunk; // http 响应

	code = curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str()); // 设置 URL，参见：https://curl.se/libcurl/c/curl_easy_setopt.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb); // 将所有数据发送到此函数，参见：https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk); // 我们将‘chunk’结构传递给回调函数，参见：https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	
	code = curl_easy_perform(curl_handle); // 执行阻塞文件传输，参见：https://curl.se/libcurl/c/curl_easy_perform.html

	code = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code); // 获取 http 响应代码，参见：https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html

	curl_easy_cleanup(curl_handle); // 结束一个 libcurl 简单句柄，参见：https://curl.se/libcurl/c/curl_easy_cleanup.html

	cout << "http_code：" << http_code << endl;
	cout << "response_data：" << chunk << endl;

	if (code == CURLcode::CURLE_OK) 
	{
		// curl 正常

		if (http_code == 200)
		{
			// http 正常

		}

	}

	return code;
}


int main()
{
	string url = "http://127.0.0.1:8080/ma";

	http(url);

	return 0;
}
