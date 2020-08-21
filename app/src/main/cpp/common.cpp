//
// Created by Tony on 2019-08-01.
//

#include <string>      // std::string
#include <android/log.h>
#include "base64.h"
#include "tinyjson.hpp"
#include "sha256.h"
#include "aes.h"

#define LOG_TAG "Codec"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__)

using namespace std;
using namespace tiny;

static const uint8_t AES_KEY[] = "creative-jdy(#-~-#)2019-07-29-00";
static const uint8_t AES_IV[] = "iv_byte_creative";

std::string getFileKey(string jwt) {

    int start = jwt.find_first_of(".");
    int end = jwt.find_last_of(".");
    int len = end - start - 1;
    string payload = jwt.substr(start + 1, len);
    string json_str = base64_decode(payload);

    TinyJson json;
    json.ReadJson(json_str);

    // 为每一个渠道来的用户，生成单独的文件加密密钥
    string sub = json.Get<string>("sub");
    string iss = json.Get<string>("iss");
    string file_key = sha256(sub + iss);

    return file_key;
}

std::string sign(std::map<std::string, std::string> resultmap, std::string jwt) {

    int start = jwt.find_first_of(".");
    int end = jwt.find_last_of(".");
    int len = end - start - 1;
    string payload = jwt.substr(start + 1, len);
    string json_str = base64_decode(payload);
    TinyJson json;
    json.ReadJson(json_str);

    string s = json.Get<string>("s");

    char *salt = AES_CBC_PKCS7_Encrypt(s.c_str(), AES_KEY, AES_IV);//AES CBC PKCS7Padding加密后的 salt

    string saltKey = "salt";

    resultmap.insert(pair<string, string>(saltKey, salt));

    string result;
    map<string, string>::iterator iter;
    for (iter = resultmap.begin(); iter != resultmap.end(); ++iter) {
        result = result + (*iter).first + (*iter).second;
    }

    resultmap.clear();
    string output = sha256(result);
    return output;
}