#include "Operations.h"


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

std::shared_ptr<Data> Operations::add(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    std::map<std::pair<Datatype, Datatype>,
            std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> operation_map = {
            {{NUM, NUM}, add_num_num},
            {{NUM, STR}, add_num_str},
            {{STR, NUM}, add_str_num},
            {{STR, STR}, add_str_str}
    };

    auto key = std::make_pair(a->datatype, b->datatype);
    auto add_func = operation_map[key];
    if (!add_func) return nullptr;
    return add_func(a, b);
}

std::shared_ptr<Data> Operations::sub(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->datatype == NUM && b->datatype == NUM) {
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

std::shared_ptr<Data> Operations::mul(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    std::map<std::pair<Datatype, Datatype>,
            std::function<std::shared_ptr<Data>(std::shared_ptr<Data>&, std::shared_ptr<Data>&)>> operation_map = {
            {{NUM, NUM}, mul_num_num},
            {{NUM, STR}, mul_num_str},
            {{STR, NUM}, mul_str_num}
    };

    auto key = std::make_pair(a->datatype, b->datatype);
    auto mul_func = operation_map[key];
    if (!mul_func) return nullptr;
    return mul_func(a, b);
}

std::shared_ptr<Data> Operations::div(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->datatype == NUM && b->datatype == NUM) {
        auto &a_num = dynamic_cast<Number&>(*a);
        auto &b_num = dynamic_cast<Number&>(*b);
        return std::shared_ptr<Data>(new Number(a_num.value / b_num.value));
    }

    return nullptr;
}

std::shared_ptr<Data> Operations::mod(std::shared_ptr<Data> &a, std::shared_ptr<Data> &b) {
    if (a->datatype == NUM && b->datatype == NUM) {
        auto &a_num = dynamic_cast<Number&>(*a);
        auto &b_num = dynamic_cast<Number&>(*b);
        return std::shared_ptr<Data>(new Number(std::fmod(a_num.value, b_num.value)));
    }

    return nullptr;
}
