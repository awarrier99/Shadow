#include "Operations.h"


std::map<const char*, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> CalcOperations::operation_map = {
        {TokenType::PLUS, CalcOperations::add},
        {TokenType::MINUS, CalcOperations::sub},
        {TokenType::MUL, CalcOperations::mul},
        {TokenType::DIV, CalcOperations::div}
};

std::shared_ptr<Data> add_num_num(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value + b_num.value));
}

std::shared_ptr<Data> add_num_str(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_str = dynamic_cast<String&>(*b);
    std::stringstream ss;
    ss << a_num.value;
    std::string concat = ss.str() + b_str.value;
    return std::shared_ptr<Data>(new String(concat));
}

std::shared_ptr<Data> add_str_num(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_str = dynamic_cast<String&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    std::stringstream ss;
    ss << b_num.value;
    std::string concat = a_str.value + ss.str();
    return std::shared_ptr<Data>(new String(concat));
}

std::shared_ptr<Data> add_str_str(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_str = dynamic_cast<String&>(*a);
    auto &b_str = dynamic_cast<String&>(*b);
    std::string concat = a_str.value + b_str.value;
    return std::shared_ptr<Data>(new String(concat));
}

std::map<std::pair<const char*, const char*>, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> CalcOperations::add_map = {
        {{Datatype::NUMBER, Datatype::NUMBER}, add_num_num},
        {{Datatype::NUMBER, Datatype::STRING}, add_num_str},
        {{Datatype::STRING, Datatype::NUMBER}, add_str_num},
        {{Datatype::STRING, Datatype::STRING}, add_str_str}
};

std::shared_ptr<Data> CalcOperations::add(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto key = std::make_pair(a->type, b->type);
    auto add_func = CalcOperations::add_map[key];
    if (!add_func) return nullptr;
    return add_func(a, b);
}

std::shared_ptr<Data> CalcOperations::sub(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto &a_num = dynamic_cast<Number&>(*a);
        auto &b_num = dynamic_cast<Number&>(*b);
        return std::shared_ptr<Data>(new Number(a_num.value - b_num.value));
    }

    return nullptr;
}

std::shared_ptr<Data> mul_num_num(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value * b_num.value));
}

std::shared_ptr<Data> mul_num_str(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_str = dynamic_cast<String&>(*b);
    std::stringstream ss;
    std::fill_n(std::ostream_iterator<std::string>(ss), a_num.value, b_str.value);
    std::string repeated = ss.str();
    return std::shared_ptr<Data>(new String(repeated));
}

std::shared_ptr<Data> mul_str_num(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto &a_str = dynamic_cast<String&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    std::stringstream ss;
    std::fill_n(std::ostream_iterator<std::string>(ss), b_num.value, a_str.value);
    std::string repeated = ss.str();
    return std::shared_ptr<Data>(new String(repeated));
}

std::map<std::pair<const char*, const char*>, std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> CalcOperations::mul_map = {
        {{Datatype::NUMBER, Datatype::NUMBER}, mul_num_num},
        {{Datatype::NUMBER, Datatype::STRING}, mul_num_str},
        {{Datatype::STRING, Datatype::NUMBER}, mul_str_num}
};

std::shared_ptr<Data> CalcOperations::mul(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    auto key = std::make_pair(a->type, b->type);
    auto mul_func = CalcOperations::mul_map[key];
    if (!mul_func) return nullptr;
    return mul_func(a, b);
}

std::shared_ptr<Data> CalcOperations::div(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto &a_num = dynamic_cast<Number&>(*a);
        auto &b_num = dynamic_cast<Number&>(*b);
        return std::shared_ptr<Data>(new Number(a_num.value / b_num.value));
    }

    return nullptr;
}

std::shared_ptr<Data> CalcOperations::mod(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->type == Datatype::NUMBER && b->type == Datatype::NUMBER) {
        auto &a_num = dynamic_cast<Number&>(*a);
        auto &b_num = dynamic_cast<Number&>(*b);
        return std::shared_ptr<Data>(new Number(std::fmod(a_num.value, b_num.value)));
    }

    return nullptr;
}

std::shared_ptr<Data> CalcOperations::operate(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b, const char* type) {
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

void AssignOperations::operate(std::shared_ptr<Symbol> &symbol, std::shared_ptr<Data> &b, const char* type, Memory* memory) {
    if (type == TokenType::EQ) return memory->assign(symbol, b);

    auto op_type = AssignOperations::operation_map[type];
    auto data = memory->retrieve(symbol);
    auto value = CalcOperations::operate(data, b, op_type);
    memory->assign(symbol, value);
}
