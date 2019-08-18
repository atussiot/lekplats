#include <map>

/*
 *  Some code to play around with Van Eck's sequence.
 *  Not actually generating the sequence itself (but that would be easy).
 *  Instead use a lookup map which is enough to progress through the sequence while keeping stats
 *  about what is produced.
 *
 *  References:
 *      - https://en.wikipedia.org/wiki/Van_Eck%27s_sequence
 *      - https://oeis.org/A181391
 */

struct ValInfo
{
    const int first;
    int last, count = 1;
    ValInfo(const int index) : first(index), last(index) {}
};

using VanEckLookUp = std::map<int, ValInfo>;

VanEckLookUp generate_van_eck_seq_stats(const int iterations, const int n0 = 0);
int first_missing_value(const VanEckLookUp& van_eck_values);
int highest_value(const VanEckLookUp& van_eck_values);

