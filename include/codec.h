#ifndef CODEC_H
#define CODEC_H

#include <string>
#include <FileReader.h>

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

    [[nodiscard]] inline std::string encodeFromFile(const std::string &fileName)
    {
        FileReader fr{};
        // TODO: Write result with header to file
        return encStrat_.encode(fr.readFile(fileName));
    }

    [[nodiscard]] inline std::string decodeFromFile(const std::string& encodedData)
    {
        assert(false) << "Not implemented yet!";
        return {};
    }
};

#endif