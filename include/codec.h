#ifndef CODEC_H
#define CODEC_H

#include <string>
#include <memory>
#include "IEncryptionStrategy.h"

class Codec
{
private:
    IEncryptionStrategy& encStrat_;

public:
    Codec(IEncryptionStrategy& encStrat) : encStrat_{encStrat} {};
    ~Codec() = default;

    template<typename T>
    T encode(const T &plainText)
    {
        return encStrat_.encode(plainText);
    }
    template<typename T>
    T decode(const T& encodedData)
    {
        return encStrat_.decode(encodedData);
    }
};

#endif