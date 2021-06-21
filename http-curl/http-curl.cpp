#define BUILDING_LIBCURL // ������޷��������ⲿ���� __imp__curl_easy_init

#include <iostream> // �ṩ��cout��string
#include <curl/curl.h> // �ṩ��curl
#include <json/json.h> // �ṩ��json

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

// http ����
int http(string url, string method, char body[], int& http_code, string& chunk)
{
	char* version = curl_version(); // libcurl �汾
	cout << "curl_version��" << version << endl;

	CURL* curl_handle = curl_easy_init(); // ���� libcurl �򵥻Ự���μ���https://curl.se/libcurl/c/curl_easy_init.html

	int code; // curl ����

	code = curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str()); // ���� URL���μ���https://curl.se/libcurl/c/curl_easy_setopt.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb); // ���������ݷ��͵��˺������μ���https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	code = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk); // ���ǽ���chunk���ṹ���ݸ��ص��������μ���https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html

	if (method == "GET")
	{
		// GET ����

	}
	else if (method == "POST") {
		// POST ����

		// Header
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "content-type:application/json");
		code = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

		code = curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, body); // ����POST������
	}
	else {
		// ʹ�� GET ����

	}

	code = curl_easy_perform(curl_handle); // ִ�������ļ����䣬�μ���https://curl.se/libcurl/c/curl_easy_perform.html

	code = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code); // ��ȡ http ��Ӧ���룬�μ���https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html ���μ���https://everything.curl.dev/libcurl-http/responses#http-response-code

	curl_easy_cleanup(curl_handle); // ����һ�� libcurl �򵥾�����μ���https://curl.se/libcurl/c/curl_easy_cleanup.html

	if (code == CURLcode::CURLE_OK)
	{
		// curl ����

		if (http_code == 200)
		{
			// http ����

			const char* str = chunk.data();

			Json::CharReaderBuilder b;
			Json::CharReader* reader(b.newCharReader());
			Json::Value root;
			JSONCPP_STRING errs;
			bool ok = reader->parse(str, str + strlen(str), &root, &errs);
			if (ok && errs.size() == 0)
			{
				string uuid = root["uuid"].asString();

				cout << "uuid��" << uuid << endl;
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

	int http_code; // http ����
	string chunk; // http ��Ӧ

	int curl_code = http(url, method, body, http_code, chunk);

	cout << endl;
	cout << "curl ���ý�����" << endl;
	cout << "curl_code��" << curl_code << endl;
	cout << "http_code��" << http_code << endl;
	cout << "response_data��" << chunk << endl;

	cout << endl;
	cout << "curl ��Ӧ���룺" << endl;
	cout << CURLE_OK << "������" << endl;
	cout << CURLE_COULDNT_CONNECT << "���޷�����" << endl;

	cout << endl;
	cout << "http ��Ӧ���룺" << endl;
	cout << 200 << "������" << endl;
	cout << 404 << "��δ����" << endl;
	cout << 405 << "������������" << endl;
	cout << 500 << "���쳣" << endl;
	cout << "�������룺��ο���https://baike.baidu.com/item/HTTP%E7%8A%B6%E6%80%81%E7%A0%81/5053660" << endl;

	return 0;
}
