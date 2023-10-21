#ifndef CODEC_H
#define CODEC_H

#include <string>

template<typename EncryptionStrategyT>
class Codec
{
private:
    EncryptionStrategyT& encStrat_;

public:
    Codec(EncryptionStrategyT&& encStrat) : encStrat_{encStrat} {};
    ~Codec() = default;

    [[nodiscard]] inline std::string encode(const std::string &plainText)
    {
        return encStrat_.encode(plainText);
    }
    [[nodiscard]] inline std::string decode(const std::string& encodedData)
    {
        return encStrat_.decode(encodedData);
    }
};

#endif