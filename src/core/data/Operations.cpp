#include "Operations.h"


std::map<const char*, opfunc> CalcOperations::operation_map = {
        {TokenType::PLUS, CalcOperations::add},
        {TokenType::MINUS, CalcOperations::sub},
        {TokenType::MUL, CalcOperations::mul},
        {TokenType::DIV, CalcOperations::div}
};

data_ptr CalcOperations::add(data_ptr &a, data_ptr &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto a_num = std::static_pointer_cast<long double>(a->value);
        auto b_num = std::static_pointer_cast<long double>(b->value);
        auto data = void_ptr(new long double(*a_num + *b_num));
        return data_ptr(new Data(Datatype::NUMBER, data));
    }

    if (a->type == Datatype::NUMBER) {
        auto b_str = std::static_pointer_cast<std::string>(b->value);
        auto concat = void_ptr(new std::string(a->display() + *b_str));
        return data_ptr(new Data(Datatype::STRING, concat));
    }

    if (b->type == Datatype::NUMBER) {
        auto a_str = std::static_pointer_cast<std::string>(a->value);
        auto concat = void_ptr(new std::string(*a_str + b->display()));
        return data_ptr(new Data(Datatype::STRING, concat));
    }

    auto a_str = std::static_pointer_cast<std::string>(a->value);
    auto b_str = std::static_pointer_cast<std::string>(b->value);
    auto concat = void_ptr(new std::string(*a_str + *b_str));
    return data_ptr(new Data(Datatype::STRING, concat));
}

data_ptr CalcOperations::sub(data_ptr &a, data_ptr &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto a_num = std::static_pointer_cast<long double>(a->value);
        auto b_num = std::static_pointer_cast<long double>(b->value);
        auto data = void_ptr(new long double(*a_num - *b_num));
        return data_ptr(new Data(Datatype::NUMBER, data));
    }

    return nullptr;
}

data_ptr CalcOperations::mul(data_ptr &a, data_ptr &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto a_num = std::static_pointer_cast<long double>(a->value);
        auto b_num = std::static_pointer_cast<long double>(b->value);
        auto data = void_ptr(new long double(*a_num * *b_num));
        return data_ptr(new Data(Datatype::NUMBER, data));
    }

    long double n;
    std::string str;
    if (a->type == Datatype::NUMBER) {
        n = *std::static_pointer_cast<long double>(a->value);
        str = *std::static_pointer_cast<std::string>(b->value);
    } else {
        str = *std::static_pointer_cast<std::string>(a->value);
        n = *std::static_pointer_cast<long double>(b->value);
    }
    std::stringstream ss;
    std::fill_n(std::ostream_iterator<std::string>(ss), n, str);
    auto repeated = void_ptr(new std::string(ss.str()));
    return data_ptr(new Data(Datatype::STRING, repeated));
}

data_ptr CalcOperations::div(data_ptr &a, data_ptr &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto a_num = std::static_pointer_cast<long double>(a->value);
        auto b_num = std::static_pointer_cast<long double>(b->value);
        auto data = void_ptr(new long double(*a_num / *b_num));
        return data_ptr(new Data(Datatype::NUMBER, data));
    }

    return nullptr;
}

data_ptr CalcOperations::mod(data_ptr &a, data_ptr &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto a_num = std::static_pointer_cast<long double>(a->value);
        auto b_num = std::static_pointer_cast<long double>(b->value);
        auto data = void_ptr(new long double(std::fmod(*a_num, *b_num)));
        return data_ptr(new Data(Datatype::NUMBER, data));
    }

    return nullptr;
}

data_ptr CalcOperations::operate(data_ptr &a, data_ptr &b, const char* type) {
    auto op_func = CalcOperations::operation_map[type];
    return op_func(a, b);
}

std::map<const char*, const char*> AssignOperations::operation_map = {
        {TokenType::PLUSEQ, TokenType::PLUS},
        {TokenType::MINUSEQ, TokenType::MINUS},
        {TokenType::MULEQ, TokenType::MUL},
        {TokenType::DIVEQ, TokenType::DIV},
        {TokenType::EXPEQ, TokenType::EXP},
        {TokenType::MODEQ, TokenType::MOD}
};

void AssignOperations::operate(symbol_ptr &symbol, data_ptr &b, const char* type, namespace_ptr &record) {
    if (type == TokenType::EQ) return record->assign(symbol, b);

    auto op_type = AssignOperations::operation_map[type];
    auto data = record->retrieve(symbol);
    auto value = CalcOperations::operate(data, b, op_type);
    record->assign(symbol, value);
}
