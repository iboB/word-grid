// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "LoadLanguageFromDir.hpp"

#include <core/Language.hpp>
#include <core/LanguageBuilder.hpp>
#include <core/LetterSequenceFromUtf8.hpp>

#include <huse/json/Deserializer.hpp>

namespace server::util
{

namespace
{
std::vector<char> readFile(const char* path)
{
    auto f = fopen(path, "rb");

    if (!f) return {};

    int pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, pos, SEEK_SET);

    std::vector<char> r(fileSize);

    fread(r.data(), 1, fileSize, f);

    fclose(f);
    return r;
}

void deserializeSeqToScoreVec(huse::DeserializerNode& n, core::Alphabet& ab)
{
    auto jab = n.obj();

    for (auto q = jab.nextkey(); q; q = jab.nextkey())
    {
        auto& elem = ab.emplace_back();
        core::LetterSequence_FromUtf8(elem, q.name);
        q->val(elem.score);
    }
}

} // namespace

core::Language loadLanguageFromDir(std::string_view dir)
{
    std::string index = std::string(dir) + "/index.json";
    auto buf = readFile(index.c_str());

    core::LanguageBuilder b;

    auto d = huse::json::Deserializer::fromMutableString(buf.data(), buf.size());
    auto obj = d.obj();

    {
        std::string_view name;
        obj.val("name", name);
        b.setDisplayName(std::string(name));
    }

    {
        uint32_t len;
        obj.val("min_word", len);
        b.setMinWordLength(len);
    }

    {
        core::Alphabet ab;
        obj.cval("alphabet", ab, deserializeSeqToScoreVec);
        b.setAlphabet(std::move(ab));
    }

    {
        core::Specials sp;
        obj.cval("specials", sp, deserializeSeqToScoreVec);
        b.setSpecials(std::move(sp));
    }

    {
        core::LetterConversionTable lt;
        auto jlt = obj.obj("conversion");

        for (auto q = jlt.nextkey(); q; q = jlt.nextkey())
        {
            core::LetterSequence<1> letter;
            letter.resize(1);
            core::LetterSequence_FromUtf8(letter, q.name);

            std::string_view utf8Target;
            q->val(utf8Target);
            core::LetterConversionTarget target;
            core::LetterSequence_FromUtf8(target, utf8Target);

            lt[letter.front()] = target;
        }
        b.setConversionTable(std::move(lt));
    }

    {
        std::string dic;
        obj.val("dictionary", dic);
        std::string index = std::string(dir) + '/' + dic;
        auto buf = readFile(index.c_str());
        b.setDictionaryUtf8Buffer(std::move(buf));
    }

    auto res = b.getLanguage();
    if (!res) throw std::runtime_error("Missing fields");
    return std::move(*res);
}

} // namespace server::util
