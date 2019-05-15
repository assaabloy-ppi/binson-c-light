#ifndef BINSON_HPP
#define BINSON_HPP

#include <map>
#include <string>
#include <vector>
#include <array>
#include <stdint.h>

#include <binson_light.h>

class BinsonValue;

class Binson
{
public:

    Binson& put(const std::string &key, const BinsonValue &v);
    Binson& put(const std::string &key, Binson o);
    Binson& put(const std::string &key, const uint8_t *data, size_t size);
    const BinsonValue & get(const std::string &key) const;
    bool hasKey(const std::string &key) const;

    void clear();
    std::vector<uint8_t> serialize() const;
    void serialize(binson_writer *w) const;
    void deserialize(const std::vector<uint8_t> &data);
    void deserialize(const uint8_t *data, size_t size);
    void deserialize(binson_parser *p);
    #ifdef BINSON_PARSER_WITH_PRINT
    std::string toStr() const;
    #endif
    std::map<std::string, BinsonValue>::const_iterator begin() const { return m_items.begin(); }
    std::map<std::string, BinsonValue>::const_iterator end() const { return m_items.end(); }

private:
    void seralizeItem(binson_writer *w, const BinsonValue &val) const;
    void seralizeItems(binson_writer *w) const;
    BinsonValue deseralizeItem(binson_parser *p);
    void deseralizeItems(binson_parser *p);

    std::map<std::string, BinsonValue> m_items;
};


class BinsonValue
{
public:
    enum class Types
    {
        noneType,
        boolType,
        intType,
        doubleType,
        stringType,
        binaryType,
        objectType,
        arrayType,
    };

    BinsonValue();
    BinsonValue(const char *str);
    BinsonValue(bool val);
    BinsonValue(int64_t val);
    BinsonValue(int val);
    BinsonValue(double val);
    BinsonValue(std::string &&val);
    BinsonValue(const std::string &val);
    BinsonValue(std::vector<uint8_t> &&val);
    BinsonValue(const std::vector<uint8_t> &val);
    BinsonValue(Binson &&val);
    BinsonValue(const Binson &val);
    BinsonValue(std::vector<BinsonValue> &&val);
    BinsonValue(const std::vector<BinsonValue> &val);

    BinsonValue operator=(bool &&val);
    BinsonValue operator=(int64_t &&val);
    BinsonValue operator=(int &&val);
    BinsonValue operator=(double &&val);
    BinsonValue operator=(std::string &&val);
    BinsonValue operator=(std::vector<uint8_t> &&val);
    BinsonValue operator=(Binson &&val);
    BinsonValue operator=(std::vector<BinsonValue> &&val);

    Types myType() const { return m_val.myType(); }

    bool getBool() const;
    int64_t getInt() const;
    double getDouble() const;
    const std::string & getString() const;
    const std::vector<uint8_t> & getBin() const;
    const Binson & getObject() const;
    const std::vector<BinsonValue> & getArray() const;

private:

    static const std::array<std::string, 8> typeToString;

    class InternalValue
    {
    public:
        bool b;
        int64_t i;
        double d;
        std::string str;
        std::vector<uint8_t> bin;
        Binson o;
        std::vector<BinsonValue> a;
        Types tinfo;
    public:
        InternalValue():b(false), tinfo(Types::noneType){ }

        void setType(Types t){ tinfo = t; }

        Types myType() const { return tinfo; }
    } m_val;

    void checkType(Types expected) const
    {
        if (myType() != expected)
        {
            throw std::runtime_error("Wrong type req(" +
                                     typeToString[(int)expected] + ") actual(" +
                                     typeToString[(int)m_val.myType()] + ")");

        }
    }
};

#endif // BINSON_HPP
