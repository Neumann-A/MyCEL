#pragma once

#include <string_view>
#include <chrono>
#include <fmt/format.h>


namespace MyCEL
{
    struct build_metainfo {
        std::string_view date;
        std::string_view time;
    };

    struct git_metainfo {
        std::string_view branch;    // git rev-parse --abbrev-ref HEAD
        std::string_view sha;       // git rev-parse HEAD
        std::string_view describe;  // git describe --always --dirty --tags
    };

    inline std::string format_git_metainfo(const git_metainfo& info) {
        return fmt::format("{}:{} ()",info.branch, info.sha, info.describe);
    }

    inline std::string to_string(const git_metainfo& info) {
        return format_git_metainfo(info);
    }
}
