#include <van_eck_sequence.h>

VanEckLookUp generate_van_eck_seq_stats(const int iterations, const int n0) {
    VanEckLookUp S;
    int val_at_i = n0, i = 0;

    while (i < iterations) {
        auto info = S.find(val_at_i);
        if (info == S.end()) {
            S.emplace(std::make_pair(val_at_i, ValInfo(i)));
            val_at_i = 0;
        } else {
            val_at_i = i - info->second.last;
            info->second.last = i;
            ++info->second.count;
        }
        ++i;
    }

    return S;
}

int first_missing_value(const VanEckLookUp& van_eck_values) {
    int previous = -1; // FIXME: Not true if the marking value is not 0
    auto it = van_eck_values.begin();
    while (it->first == previous + 1) { previous = it->first; ++it; }
    return previous + 1;
}

int highest_value(const VanEckLookUp& van_eck_values)
{ return (--van_eck_values.end())->first; }

