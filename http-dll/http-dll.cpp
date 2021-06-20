#define BUILDING_LIBCURL // ������޷��������ⲿ���� __imp__curl_easy_init

#include <iostream> // �ṩ��cout��string
#include <curl/curl.h> // �ṩ��curl

using namespace std;

// ���ݵĻ�ȡ
// �μ���https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
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
	char* version = curl_version(); // libcurl �汾
	cout << "curl_version��" << version << endl;

	CURL* curl_handle = curl_easy_init(); // ���� libcurl �򵥻Ự���μ���https://curl.se/libcurl/c/curl_easy_init.html

	int code; // curl ����
	int http_code; // http ����
	string chunk; // http ��Ӧ

	code = curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str()); // ���� URL���μ���https://curl.se/libcurl/c/curl_easy_setopt.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb); // ���������ݷ��͵��˺������μ���https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk); // ���ǽ���chunk���ṹ���ݸ��ص��������μ���https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	
	code = curl_easy_perform(curl_handle); // ִ�������ļ����䣬�μ���https://curl.se/libcurl/c/curl_easy_perform.html

	code = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code); // ��ȡ http ��Ӧ���룬�μ���https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html

	curl_easy_cleanup(curl_handle); // ����һ�� libcurl �򵥾�����μ���https://curl.se/libcurl/c/curl_easy_cleanup.html

	cout << "http_code��" << http_code << endl;
	cout << "response_data��" << chunk << endl;

	if (code == CURLcode::CURLE_OK) 
	{
		// curl ����

		if (http_code == 200)
		{
			// http ����

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
