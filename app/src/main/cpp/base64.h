//
// Created by Tony on 2019/7/29.
//

#ifndef BLOWFISH_JNI_BASE64_H
#define BLOWFISH_JNI_BASE64_H

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif //BLOWFISH_JNI_BASE64_H
