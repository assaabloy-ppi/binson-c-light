#ifndef BINSON_HPP
#define BINSON_HPP

#include <map>
#include <string>
#include <vector>
#include <stdint.h>

#include <binson_light.h>

class BinsonValue;

class Binson
{
public:

    Binson& put(const std::string &key, const BinsonValue &v);
    Binson& put(const std::string &key, Binson o);
    Binson& put(const std::string &key, const uint8_t *data, size_t size);
    BinsonValue get(const std::string &key);
    bool hasKey(const std::string &key);

    void clear();
    std::vector<uint8_t> serialize();
    void serialize(binson_writer *w);
    bool deserialize(const std::vector<uint8_t> &data);
    bool deserialize(const uint8_t *data, size_t size);
    bool deserialize(binson_parser *p);
    std::string toStr();

private:
    void seralizeItem(binson_writer *w, BinsonValue &val);
    void seralizeItems(binson_writer *w);
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

    template <class T>
    bool isType(T t) const {
        bool res = m_val.myType() == findType(t);
        return res;
    }
    Types myType() const { return m_val.myType(); }

    bool getBool(){ bool v = false; get(v); return v; }
    int64_t getInt() { int64_t v = 0; get(v); return v; };
    double getDouble() { double v = 0; get(v); return v; };
    std::string getString(){ std::string v; get(v); return v; }
    std::vector<uint8_t> getBin(){ std::vector<uint8_t> v; get(v); return v; }
    Binson getObject(){ Binson v; get(v); return v; }
    std::vector<BinsonValue> getArray(){ std::vector<BinsonValue> v; get(v); return v; }
private:

    std::string typeToString[8] =
    {
        "noneType",
        "boolType",
        "intType",
        "doubleType",
        "stringType",
        "binaryType",
        "objectType",
        "arrayType",
    };

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

        void get(bool &val) const { val = b; }
        void get(int64_t &val) const { val = i; }
        void get(int &val) const { val = i; }
        void get(double &val) const { val = d; }
        void get(std::string &val) const { val = str; }
        void get(std::vector<uint8_t> &val) const { val = bin; }
        void get(Binson &val) const { val = o; }
        void get(std::vector<BinsonValue> &val) const { val = a; }

        void setType(Types t){ tinfo = t; }

        Types myType() const { return tinfo; }
    } m_val;

    template<class T>
    void get (T &val) const
    {
        if (!isType(val))
            throw std::runtime_error("Wrong type req(" +
                                     typeToString[(int)findType(val)] + ") actual(" +
                                     typeToString[(int)m_val.myType()] + ")");
        else
        {
            m_val.get(val);
        }
    }

    static Types findType(bool &val) {(void)val; return Types::boolType; }
    static Types findType(int64_t &val) {(void)val; return Types::intType; }
    static Types findType(int &val) {(void)val; return Types::intType; }
    static Types findType(double &val) {(void)val; return Types::doubleType; }
    static Types findType(std::string &val) {(void)val; return Types::stringType; }
    static Types findType(std::vector<uint8_t> &val) {(void)val; return Types::binaryType; }
    static Types findType(Binson &val) {(void)val; return Types::objectType; }
    static Types findType(std::vector<BinsonValue> &val) {(void)val; return Types::arrayType; }
};

#endif // BINSON_HPP
