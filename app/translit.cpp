#include "transliterator.h"
#include <vector>

std::wstring Transliterator::transliterate(std::string text) {

    struct Rule {
        std::string latin;
        std::wstring cyr;
    };

    std::vector<Rule> rules = {
        {"shch", L"щ"},
        {"zh", L"ж"},
        {"kh", L"х"},
        {"ch", L"ч"},
        {"sh", L"ш"},
        {"yu", L"ю"},
        {"ya", L"я"},
        {"yi", L"ы"},

        {"a", L"а"}, {"b", L"б"}, {"v", L"в"}, {"g", L"г"},
        {"d", L"д"}, {"e", L"е"}, {"z", L"з"}, {"i", L"и"},
        {"y", L"й"}, {"k", L"к"}, {"l", L"л"}, {"m", L"м"},
        {"n", L"н"}, {"o", L"о"}, {"p", L"п"}, {"r", L"р"},
        {"s", L"с"}, {"t", L"т"}, {"u", L"у"}, {"f", L"ф"},
        {"c", L"ц"}
    };

    std::wstring result;
    size_t i = 0;

    while (i < text.size()) {
        bool matched = false;

        for (auto &r : rules) {
            if (i + r.latin.size() <= text.size() &&
                text.substr(i, r.latin.size()) == r.latin) {

                result += r.cyr;
                i += r.latin.size();
                matched = true;
                break;
            }
        }

        if (!matched) {
            result += (wchar_t)text[i];
            i++;
        }
    }

    return result;
}