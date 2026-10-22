#ifdef NDEBUG
#undef NDEBUG
#endif
#include "engine/platform/display_modes.h"

#include <cassert>

int main() {
    const std::vector<glm::ivec2> listed{{1920, 1080}, {1280, 720}, {1920, 1080}, {0, 0}, {1600, 900}};
    const auto sizes = pt::UniqueDisplaySizes(listed);
    assert((sizes == std::vector<glm::ivec2>{{1280, 720}, {1600, 900}, {1920, 1080}}));
    assert((pt::ClosestDisplaySize(sizes, {1920, 1080}) == glm::ivec2(1920, 1080)));
    assert((pt::ClosestDisplaySize(sizes, {1900, 1050}) == glm::ivec2(1920, 1080)));
    assert((pt::ClosestDisplaySize({}, {1900, 1050}) == glm::ivec2(1900, 1050)));
    const auto pacing = [](double hz, int limit) {
        const pt::LimiterPacing p = pt::PacingOfLimit(hz, limit);
        return glm::ivec2(p.min_refreshes, p.max_refreshes);
    };
    assert((pacing(165.0, 60) == glm::ivec2(2, 3)));
    assert((pacing(144.0, 60) == glm::ivec2(2, 3)));
    assert((pacing(120.0, 60) == glm::ivec2(2, 2)));
    assert((pacing(239.76, 60) == glm::ivec2(4, 4)));
    assert((pacing(165.0, 55) == glm::ivec2(3, 3)));
    assert((pacing(59.94, 60) == glm::ivec2(0, 0)));
    assert((pacing(144.0, 0) == glm::ivec2(0, 0)));
    assert((pacing(60.0, 144) == glm::ivec2(0, 0)));
    assert((pacing(0.0, 60) == glm::ivec2(0, 0)));

    const std::vector<pt::DisplayModeInfo> modes{
        {2560, 1440, 165.0}, {2560, 1440, 240.0}, {2560, 1440, 60.0}, {2560, 1440, 144.0}, {2560, 1440, 59.94}, {2560, 1440, 240.0},
        {1920, 1080, 144.0}, {1920, 1080, 60.0}, {1920, 1080, 120.0}, {1280, 720, 0.0}};
    const glm::ivec2 qhd(2560, 1440), fhd(1920, 1080);
    assert((pt::RefreshRatesFor(modes, qhd) == std::vector<double>{240.0, 165.0, 144.0, 60.0, 59.94}));
    assert((pt::RefreshRatesFor(modes, fhd) == std::vector<double>{144.0, 120.0, 60.0}));
    assert(pt::RefreshRatesFor(modes, {1280, 720}).empty());
    assert(pt::RefreshRatesFor(modes, {3840, 2160}).empty());
    assert(pt::PickExclusiveMode(modes, qhd, 0.0) == 1);
    assert(pt::PickExclusiveMode(modes, fhd, 0.0) == 6);
    assert(pt::PickExclusiveMode(modes, qhd, 60.0) == 2);
    assert(pt::PickExclusiveMode(modes, qhd, 59.94) == 4);
    assert(pt::PickExclusiveMode(modes, qhd, 144.0) == 3);
    assert(pt::PickExclusiveMode(modes, qhd, 165.0) == 0);
    assert(pt::PickExclusiveMode(modes, qhd, 240.0) == 1);
    assert(pt::PickExclusiveMode(std::vector<pt::DisplayModeInfo>{{2560, 1440, 143.9809}, {2560, 1440, 59.951}}, qhd,
                                 static_cast<double>(143.981f)) == 0);
    assert(pt::PickExclusiveMode(modes, fhd, 240.0) == 6);
    assert(pt::PickExclusiveMode(modes, fhd, 165.0) == 6);
    assert(pt::PickExclusiveMode(modes, fhd, 60.0) == 7);
    assert(pt::PickExclusiveMode(modes, {1280, 720}, 144.0) == 9);
    assert(pt::PickExclusiveMode(modes, {3840, 2160}, 0.0) == -1);
    assert(pt::PickExclusiveMode({}, qhd, 0.0) == -1);
    assert(pt::RefreshRateText(144.0) == "144 Hz" && pt::RefreshRateText(59.94) == "59.94 Hz" && pt::RefreshRateText(239.998) == "240 Hz");
}
