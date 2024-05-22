#include "binson.hpp"

#include <binson_light.h>

#include <string.h>
#include <stdexcept>

using namespace std;

void ifRuntimeError(bool x, const char *msg)
{
    if (!(x))
        throw std::runtime_error(msg);
}

void CheckParserState(binson_parser *p)
{
    if (p->error_flags != BINSON_ERROR_NONE)
        throw std::runtime_error("Parse error");
}

const std::array<std::string, 8> BinsonValue::typeToString
{
    {
        "noneType",
        "boolType",
        "intType",
        "doubleType",
        "stringType",
        "binaryType",
        "objectType",
        "arrayType"
    }
};

Binson & Binson::put(const std::string &key, const BinsonValue &v)
{
    m_items[key] = move(v);
    return *this;
}

Binson & Binson::put(const std::string &key, Binson o)
{
    m_items[key] = BinsonValue(move(o));
    return *this;
}

Binson & Binson::put(const string &key, const uint8_t *data, size_t size)
{
    vector<uint8_t> v(data, data + size);
    m_items[key] = BinsonValue(v);
    return *this;
}

const BinsonValue &Binson::get(const string &key) const
{
    if (!hasKey(key))
        throw std::out_of_range("Key '" + key + "' does not exist");
    else
        return m_items.at(key);
}

bool Binson::hasKey(const string &key) const
{
    return m_items.find(key) != m_items.end();
}

void Binson::clear()
{
    m_items.clear();
}

void Binson::seralizeItem(binson_writer *w, const BinsonValue &val) const
{
    switch(val.myType())
    {
    case BinsonValue::Types::noneType:
        break;
    case BinsonValue::Types::boolType:
        binson_write_boolean(w, val.getBool());
        break;
    case BinsonValue::Types::intType:
        binson_write_integer(w, val.getInt());
        break;
    case BinsonValue::Types::doubleType:
        binson_write_double(w, val.getDouble());
        break;
    case BinsonValue::Types::stringType:
        binson_write_string_with_len(w,
                                     val.getString().data(),
                                     val.getString().size());
        break;
    case BinsonValue::Types::binaryType:
        binson_write_bytes(w, val.getBin().data(), val.getBin().size());
        break;
    case BinsonValue::Types::objectType:
        binson_write_object_begin(w);
        val.getObject().seralizeItems(w);
        binson_write_object_end(w);
        break;
    case BinsonValue::Types::arrayType:
        binson_write_array_begin(w);
        for (auto &arrayValue : val.getArray())
        {
            seralizeItem(w, arrayValue);
        }
        binson_write_array_end(w);
        break;
    default:
        throw runtime_error("Unknown binson type");
    }
}

void Binson::seralizeItems(binson_writer *w) const
{
    for (auto &item: m_items)
    {
        binson_write_name_with_len(w, item.first.c_str(), item.first.size());
        seralizeItem(w, item.second);
    }
}

std::vector<uint8_t> Binson::serialize() const
{
    vector<uint8_t> data;
    data.resize(1000);
    binson_writer w;
    binson_writer_init(&w, data.data(), data.size());
    serialize(&w);
    if (w.error_flags == BINSON_ERROR_RANGE)
    {
        data.resize(binson_writer_get_counter(&w));
        binson_writer_init(&w, data.data(), data.size());
        serialize(&w);
    }

    if (w.error_flags == BINSON_ERROR_NONE)
        data.resize(binson_writer_get_counter(&w));
    else
        data.clear();

    return data;
}

void Binson::serialize(binson_writer *w) const
{
    binson_write_object_begin(w);
    seralizeItems(w);
    binson_write_object_end(w);
}

BinsonValue Binson::deseralizeItem(binson_parser *p)
{
    uint8_t t = binson_parser_get_type(p);
    CheckParserState(p);

    switch(t)
    {
    case BINSON_ID_BOOLEAN:
    {
        bool val = binson_parser_get_boolean(p);
        CheckParserState(p);
        return BinsonValue(val);
    }
        break;
    case BINSON_ID_INTEGER:
    {
        int64_t val = binson_parser_get_integer(p);
        CheckParserState(p);
        return BinsonValue(val);
    }
        break;
    case BINSON_ID_DOUBLE:
    {
        double val = binson_parser_get_double(p);
        CheckParserState(p);
        return BinsonValue(val);
    }
        break;
    case BINSON_ID_STRING:
    {
        bbuf *buf;
        buf = binson_parser_get_string_bbuf(p);
        CheckParserState(p);
        if (buf)
            return BinsonValue(string(reinterpret_cast<const char*>(buf->bptr), buf->bsize));
        else
            throw runtime_error("Parse error, missing string");
    }
        break;
    case BINSON_ID_BYTES:
    {
        bbuf *buf;
        buf = binson_parser_get_bytes_bbuf(p);
        CheckParserState(p);
        if (buf)
            return BinsonValue(vector<uint8_t>(buf->bptr, buf->bptr + buf->bsize));
        else
            throw runtime_error("Parse error, missing data");
    }
        break;
    case BINSON_ID_OBJECT:
    {
        ifRuntimeError(binson_parser_go_into_object(p), "Parse error");
        Binson b;
        b.deseralizeItems(p);
        ifRuntimeError(binson_parser_leave_object(p), "Parse error");
        return BinsonValue(b);
    }
        break;
    case BINSON_ID_ARRAY:
    {
        ifRuntimeError(binson_parser_go_into_array(p), "Parse error");
        vector<BinsonValue> array;
        while(binson_parser_next(p))
        {
            array.push_back(deseralizeItem(p));
        }
        ifRuntimeError(binson_parser_leave_array(p), "Parse error");
        return array;
    }
        break;
    default:
        throw runtime_error("Unknown type");
    }
    return BinsonValue();
}

void Binson::deseralizeItems(binson_parser *p)
{
    while(binson_parser_next(p))
    {
        bbuf *buf;
        buf = binson_parser_get_name(p);
        CheckParserState(p);
        if (buf == nullptr)
            throw std::runtime_error("buf is null");
        if (buf->bptr == nullptr)
            throw std::runtime_error("buf->bptr is null");
        string name(reinterpret_cast<const char*>(buf->bptr), buf->bsize);
        put(name, deseralizeItem(p));
    }
    CheckParserState(p);
}

void Binson::deserialize(const std::vector<uint8_t> &data)
{
    BINSON_PARSER_DEF(p);
    clear();

    binson_parser_init(&p, const_cast<uint8_t*>(data.data()), data.size());
    binson_parser_go_into_object(&p);
    deseralizeItems(&p);
    binson_parser_leave_object(&p);
}

void Binson::deserialize(const uint8_t *data, size_t size)
{
    BINSON_PARSER_DEF(p);
    clear();

    ifRuntimeError(binson_parser_init(&p, const_cast<uint8_t*>(data), size), "Parser init error");
    deserialize(&p);
}

void Binson::deserialize(binson_parser *p)
{
    clear();
    ifRuntimeError(binson_parser_reset(p), "Parser reset error");
    ifRuntimeError(binson_parser_go_into_object(p), "Parse error");
    deseralizeItems(p);
    ifRuntimeError(binson_parser_leave_object(p), "Parse error");
}

#ifdef BINSON_PARSER_WITH_PRINT
string Binson::toStr() const
{
    BINSON_PARSER_DEF(p);
    vector<char> str_vector(10);
    vector<uint8_t> stream = serialize();
    if (stream.empty())
        return string();

    bool result = false;
    size_t size = str_vector.capacity();

    if (!binson_parser_init(&p, stream.data(), stream.size()))
    {
        return string();
    }

    result = binson_parser_to_string(&p, str_vector.data(), &size, true);
    if (!result)
    {
        str_vector.resize(size);
    }
    result = binson_parser_to_string(&p, str_vector.data(), &size, true);
    if (!result)
    {
        return string();
    }

    return string(str_vector.data(), size);;
}
#endif

BinsonValue::BinsonValue()
{

}

BinsonValue::BinsonValue(bool val)
{
    m_val.b = val;
    m_val.setType(Types::boolType);
}

BinsonValue::BinsonValue(int64_t val)
{
    m_val.i = val;
    m_val.setType(Types::intType);
}

BinsonValue::BinsonValue(int val)
{
    m_val.i = val;
    m_val.setType(Types::intType);
}

BinsonValue::BinsonValue(double val)
{
    m_val.d = val;
    m_val.setType(Types::doubleType);
}

BinsonValue::BinsonValue(string &&val)
{
    m_val.str = move(val);
    m_val.setType(Types::stringType);
}

BinsonValue::BinsonValue(const string &val)
{
    m_val.str = val;
    m_val.setType(Types::stringType);
}

BinsonValue::BinsonValue(const char *str)
{
    m_val.str = string(str);
    m_val.setType(Types::stringType);
}

BinsonValue::BinsonValue(std::vector<uint8_t> &&val)
{
    m_val.bin = move(val);
    m_val.setType(Types::binaryType);
}

BinsonValue::BinsonValue(const std::vector<uint8_t> &val)
{
    m_val.bin = val;
    m_val.setType(Types::binaryType);
}

BinsonValue::BinsonValue(Binson &&val)
{
    m_val.o = move(val);
    m_val.setType(Types::objectType);
}

BinsonValue::BinsonValue(const Binson &val)
{
    m_val.o = val;
    m_val.setType(Types::objectType);
}

BinsonValue::BinsonValue(std::vector<BinsonValue> &&val)
{
    m_val.a = move(val);
    m_val.setType(Types::arrayType);
}

BinsonValue::BinsonValue(const std::vector<BinsonValue> &val)
{
    m_val.a = val;
    m_val.setType(Types::arrayType);
}

BinsonValue BinsonValue::operator=(bool &&val)
{
    m_val.b = move(val);
    m_val.setType(Types::boolType);
    return *this;
}

BinsonValue BinsonValue::operator=(int64_t &&val)
{
    m_val.i = move(val);
    m_val.setType(Types::intType);
    return *this;
}

BinsonValue BinsonValue::operator=(int &&val)
{
    m_val.i = val;
    m_val.setType(Types::intType);
    return *this;
}

BinsonValue BinsonValue::operator=(double &&val)
{
    m_val.d = move(val);
    m_val.setType(Types::doubleType);
    return *this;
}

BinsonValue BinsonValue::operator=(string &&val)
{
    m_val.str = move(val);
    m_val.setType(Types::stringType);
    return *this;
}

BinsonValue BinsonValue::operator=(std::vector<uint8_t> &&val)
{
    m_val.bin = move(val);
    m_val.setType(Types::binaryType);
    return *this;
}

BinsonValue BinsonValue::operator=(Binson &&val)
{
    m_val.o = move(val);
    m_val.setType(Types::objectType);
    return *this;
}

BinsonValue BinsonValue::operator=(std::vector<BinsonValue> &&val)
{
    m_val.a = move(val);
    m_val.setType(Types::arrayType);
    return *this;
}

bool BinsonValue::getBool() const
{
    checkType(Types::boolType);
    return m_val.b;
}

int64_t BinsonValue::getInt() const
{
    checkType(Types::intType);
    return m_val.i;
}

double BinsonValue::getDouble() const
{
    checkType(Types::doubleType);
    return m_val.d;
}

const string & BinsonValue::getString() const
{
    checkType(Types::stringType);
    return m_val.str;
}

const std::vector<uint8_t> & BinsonValue::getBin() const
{
    checkType(Types::binaryType);
    return m_val.bin;
}

const Binson & BinsonValue::getObject() const
{
    checkType(Types::objectType);
    return m_val.o;
}

const std::vector<BinsonValue> & BinsonValue::getArray() const
{
    checkType(Types::arrayType);
    return m_val.a;
}
