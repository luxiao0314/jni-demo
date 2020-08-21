//
// Created by Tony on 2019-08-01.
//

#ifndef BLOWFISH_JNI_COMMON_H
#define BLOWFISH_JNI_COMMON_H

std::string getFileKey(std::string jwt);

std::string sign(std::map<std::string, std::string> resultmap,std::string jwt);

#endif //BLOWFISH_JNI_COMMON_H
