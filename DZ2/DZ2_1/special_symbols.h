#pragma once

#include <QString>
#include <optional>
#include <tuple>

class SpecialSymbols
{
public:
    SpecialSymbols() = default;

public:

    std::optional<std::tuple<QString, int, int>> GetSpec(const QString& line) const;
    QString Special(const QString& line, const std::tuple<QString, int, int>&spec) const;
};
