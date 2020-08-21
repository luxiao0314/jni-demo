//
// Created by Tony on 2019/7/25.
//
#pragma once

#ifndef BLOWFISH_JNI_BLOWFISH_H
#define BLOWFISH_JNI_BLOWFISH_H


#include <stdint.h>
#include <cstddef>
#include <vector>

class Blowfish {
public:
    Blowfish(const std::vector<char> &key);
    std::vector<char> Encrypt(const std::vector<char> &src) const;
    std::vector<char> Decrypt(const std::vector<char> &src) const;

private:
    void SetKey(const char *key, size_t byte_length);
    void EncryptBlock(uint32_t *left, uint32_t *right) const;
    void DecryptBlock(uint32_t *left, uint32_t *right) const;
    uint32_t Feistel(uint32_t value) const;

private:
    uint32_t pary_[18];
    uint32_t sbox_[4][256];
};

#endif //BLOWFISH_JNI_BLOWFISH_H
