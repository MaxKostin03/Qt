#include "special_symbols.h"

#include <QHash>

namespace
{
QHash<QString, QString> hexHash
    {

            {"#@C@",   u8"\u00A9"},
            {"#@PRO@", u8"\u2030"},
            {"#@EUR@", u8"\u20AC"},
            {"#@RUB@", u8"\u20BD"},
            {"#@R@",   u8"\u00AE"},

    };
}

std::optional<std::tuple<QString, int, int>> SpecialSymbols::GetSpec(const QString& line) const
{
    QHash<QString, QString>::const_iterator i = hexHash.constBegin();
    while (i != hexHash.constEnd())
    {
        if(int index = line.indexOf(i.key()); index != -1)
        {
            return std::make_tuple(i.value(), index, i.key().length());
        }
        ++i;
    }
    return std::nullopt;
}

QString SpecialSymbols::Special(const QString& line, const std::tuple<QString, int, int>& spec) const
{
    QString formattedText {line};
    const auto& [lexeme, pos, length] = spec;

    formattedText.replace(pos, length, lexeme);
    return formattedText;
}
