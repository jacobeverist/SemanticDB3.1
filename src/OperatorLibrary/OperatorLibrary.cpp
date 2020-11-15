//
// Created by Garry Morrison on 21/09/2020.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "OperatorLibrary.h"
#include "../CompoundConstant/ConstantString.h"
#include "../Function/misc.h"
#include "FunctionOperatorLibrary.h"


Superposition split(const Ket k) {
    Superposition sp;
    for (const auto c: k.label()) {
        std::string s;
        s.push_back(c);
        sp.add(s, k.value());
    }
    return sp;
}

Superposition split(const Ket k, const std::string& delimiter) {
    if (delimiter.empty()) { return split(k); }
    Superposition sp;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::string s = k.label();
    double value = k.value();

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        sp.add(token, value);
    }
    sp.add(s.substr(pos_start), value);
    return sp;
}

Superposition op_split(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    // if (parameters.empty()) { return Superposition(); }  // Maybe return split(k) instead?
    if (parameters.empty()) { return split(k); }
    // std::string delim = std::dynamic_pointer_cast<ConstantString>(parameters[0])->get_string();
    std::string delim = parameters[0]->get_string();
    return split(k, delim);
}

Sequence ssplit(const Ket k) {
    Sequence seq;
    for (const auto c: k.label()) {
        // std::cout << c << std::endl;
        std::string s;
        s.push_back(c);
        // Ket k2(s, k.value());
        seq.append(s, k.value());
    }
    return seq;
}

Sequence ssplit(const Ket k, const std::string& delimiter) {
    if (delimiter.empty()) { return ssplit(k); }
    Sequence seq;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::string s = k.label();
    double value = k.value();

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);  // Maybe use string_view instead: https://www.youtube.com/watch?v=ZO68JEgoPeg
        pos_start = pos_end + delim_len;
        // Ket k2(token, value);
        seq.append(token, value);
    }
    // Ket k2(s.substr(pos_start), value);
    seq.append(s.substr(pos_start), value);
    return seq;
}

/*
Sequence ssplit(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    // if (parameters.empty()) { return Sequence(); }  // Maybe return ssplit(k) instead?
    if (parameters.empty()) { return ssplit(k); }
    // std::string delim = std::dynamic_pointer_cast<ConstantString>(parameters[0])->get_string();
    std::string delim = parameters[0]->get_string();
    return ssplit(k, delim);
}
*/

Sequence op_ssplit(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return ssplit(k); }
    std::string delim = parameters[0]->get_string();
    return ssplit(k, delim);
}


Ket extract_head(const Ket k) {
    ulong head_idx = ket_map.get_head_idx(k.label_idx());
    return Ket(head_idx, k.value());
}

Ket extract_tail(const Ket k) {
    ulong tail_idx = ket_map.get_tail_idx(k.label_idx());
    return Ket(tail_idx, k.value());
}

Ket extract_category(const Ket k) {
    ulong category_idx = ket_map.get_category_idx(k.label_idx());
    return Ket(category_idx, k.value());
}

Ket extract_value(const Ket k) {
    ulong value_idx = ket_map.get_value_idx(k.label_idx());
    return Ket(value_idx, k.value());
}

Ket push_float(const Ket k) {
    if (k.label_idx() == ket_map.get_idx("")) { return k;}
    std::string label = k.label();

    std::string s;
    if (label == " ") {
        s = "";
    } else {
        s = label + ": ";
    }
    return Ket(s + float_to_int(k.value(), default_decimal_places));
}

Ket pop_float(const Ket k) {
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); } // should never happen
    std::string value_str = ket_map.get_str(k_vec.back());
    try {
        double value = std::stod(value_str);
        if ( k_vec.size() == 1) {
            return Ket(" ", value);
        }
        k_vec.pop_back();
        ulong label_idx = ket_map.get_idx(k_vec);
        return Ket(label_idx, value * k.value());
    } catch (std::invalid_argument) {
        return k;
    }
}

Superposition rank(const Superposition& sp) {
    Superposition result;
    ulong pos = 0;
    for (const auto k: sp) {
        pos++;
        result.add(k.label_idx(), pos);
    }
    return result;
}

Sequence sp2seq(const Superposition &sp) {
    Sequence result;
    for (const auto k : sp) {
        result.append(k);
    }
    return result;
}

Superposition seq2sp(const Sequence &seq) {
    Superposition result;
    for (const auto &sp: seq) {
        result.add(sp);
    }
    return result;
}

Ket bar_chart(const Superposition &sp, const unsigned int width) {
    if (sp.size() == 0 || width <= 0) { return Ket(); }

    ulong max_len = 0;
    for (const auto k: sp) {
        max_len = std::max(k.label().size(), max_len);  // Is there a smarter way to do this?
    }
    // Superposition one = sp.rescale(width); // do we need .drop() too? Probably.
    Superposition one = sp.drop().rescale(width);
    std::cout << "----------" << std::endl;
    for (const auto k: one) {
        std::cout << std::left << std::setfill(' ') << std::setw(max_len) << k.label() << " : ";
        std::cout << std::setfill('|') << std::setw((ulong)k.value()) << "|" << std::endl;
    }
    std::cout << "----------" << std::endl;
    return Ket("bar chart");
}

Ket op_bar_chart(const Superposition &sp, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    unsigned int width = 10;
    if (parameters.empty()) {
        width = 10;
    } else {
        width = parameters[0]->get_int();
    }
    return bar_chart(sp, width);
}


Ket print_ket(const Ket k) {
    std::cout << k.label() << std::endl;
    return k;
}

Superposition op_relevant_kets(const Sequence &seq, ContextList &context, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Superposition(); }
    Superposition result;
    for (const auto &param: parameters ) {
        ulong op_idx = param->get_operator().get_idx();
        // Superposition tmp(context.relevant_kets(op_idx));
        // result.add(tmp);
        result.add(context.relevant_kets(op_idx));
    }
    return result;
}

Superposition op_similar_input(const Sequence &seq, ContextList &context, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        double score = simm(seq, pattern);
        if (score > 0) {
            result.add(label_idx, score);
        }
    }
    result.coeff_sort();
    switch (parameters.size()) {
        case 1: { return result; }
        case 2: {
            int stop = parameters[1]->get_int();
            return result.select(1, stop);
            }
        case 3: {
            int start = parameters[1]->get_int();
            int stop = parameters[2]->get_int();
            return result.select(start, stop);
        }
        default: return Superposition();  // Alternatively, we could return seq.
    }
}

// Wow! A lot of work just to subtract a number!!
Ket op_minus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
    split_idx.pop_back();
    if (split_idx.empty()) {
        return Ket(float_to_int(number - value, default_decimal_places), k.value());
    } else {
        std::string category = ket_map.get_str(split_idx) + ": ";
        return Ket(category + float_to_int(number - value, default_decimal_places), k.value());
    }
}

Ket op_plus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
    split_idx.pop_back();
    if (split_idx.empty()) {
        return Ket(float_to_int(number + value, default_decimal_places), k.value());
    } else {
        std::string category = ket_map.get_str(split_idx) + ": ";
        return Ket(category + float_to_int(number + value, default_decimal_places), k.value());
    }
}

Ket op_times_by(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
    split_idx.pop_back();
    if (split_idx.empty()) {
        return Ket(float_to_int(number * value, default_decimal_places), k.value());
    } else {
        std::string category = ket_map.get_str(split_idx) + ": ";
        return Ket(category + float_to_int(number * value, default_decimal_places), k.value());
    }
}

Ket op_divide_by(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    if (double_eq(value, 0)) { return k; } // prevent divide by zero.
    auto split_idx = k.label_split_idx();
    long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
    split_idx.pop_back();
    if (split_idx.empty()) {
        return Ket(float_to_int(number / value, default_decimal_places), k.value());
    } else {
        std::string category = ket_map.get_str(split_idx) + ": ";
        return Ket(category + float_to_int(number / value, default_decimal_places), k.value());
    }
}

Ket op_modulus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
    split_idx.pop_back();
    long long result = static_cast<long long>(number) % static_cast<long long>(value);
    if (split_idx.empty()) {
        return Ket(float_to_int(result, default_decimal_places), k.value());
    } else {
        std::string category = ket_map.get_str(split_idx) + ": ";
        return Ket(category + float_to_int(result, default_decimal_places), k.value());
    }
}

Ket op_toupper(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return k; }
    std::string label = k.label();
    for (const auto &elt: parameters) {
        int idx = elt->get_int() - 1;  // to-upper[1] changes case of first char, not the second.
        if (idx < 0 || idx >= label.size()) {
            continue;
        }
        if (label[idx] >= 'a' && label[idx] <= 'z') {  // assumes ASCII
            label[idx] = label[idx] - 32;
        }
    }
    return Ket(label, k.value());
}

Ket op_tolower(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.empty()) { return k; }
    std::string label = k.label();
    for (const auto &elt: parameters) {
        int idx = elt->get_int() - 1;  // to-lower[1] changes case of first char, not the second.
        if (idx < 0 || idx >= label.size()) {
            continue;
        }
        if (label[idx] >= 'A' && label[idx] <= 'Z') {  // assumes ASCII
            label[idx] = label[idx] + 32;
        }
    }
    return Ket(label, k.value());
}
