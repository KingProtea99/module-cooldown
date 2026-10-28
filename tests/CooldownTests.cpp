// 쿨타임 모듈 시험: 틱 번호로만 세는지, 결과가 틱레이트와 무관하게 정해지는지
#include "cooldown/sim/Cooldown.h"
#include "cooldown/view/CooldownView.h"

#include "mealkit/core/Hash.h"

#include <cstdio>

static int g_failed = 0;
#define CHECK(x)                                                                                                       \
    do {                                                                                                               \
        if (!(x)) {                                                                                                    \
            std::printf("%s(%d): FAIL %s\n", __FILE__, __LINE__, #x);                                                  \
            ++g_failed;                                                                                                \
        }                                                                                                              \
    } while (0)

int main() {
    cooldown::Cooldown c;
    CHECK(cooldown::ready(c, 0));
    CHECK(cooldown::readiness(c, 0) == 1.0f);

    // 30틱 쿨타임: 10틱에 쓰면 40틱부터 다시 준비
    CHECK(cooldown::tryUse(c, 10, 30));
    CHECK(!cooldown::ready(c, 39));
    CHECK(!cooldown::tryUse(c, 39, 30));
    CHECK(cooldown::remaining(c, 25) == 15);
    CHECK(cooldown::readiness(c, 25) == 0.5f);
    CHECK(cooldown::ready(c, 40));
    CHECK(cooldown::tryUse(c, 40, 30));
    CHECK(c.timer.readyTick == 70);

    cooldown::reset(c);
    CHECK(cooldown::ready(c, 41));

    // 상태가 필드로 선언돼 해시에 들어간다 (WorldState 필드로 넣으면 디싱크 검사가 본다)
    cooldown::Cooldown a, b;
    cooldown::start(a, 5, 60);
    cooldown::start(b, 5, 60);
    mealkit::Hasher ha, hb;
    mealkit::reflect::hashStruct(mealkit::reflect::typeOf<cooldown::Cooldown>(), &a, ha);
    mealkit::reflect::hashStruct(mealkit::reflect::typeOf<cooldown::Cooldown>(), &b, hb);
    CHECK(ha.value == hb.value);
    cooldown::start(b, 6, 60);
    mealkit::Hasher hc;
    mealkit::reflect::hashStruct(mealkit::reflect::typeOf<cooldown::Cooldown>(), &b, hc);
    CHECK(ha.value != hc.value);

    std::printf(g_failed ? "cooldown tests: %d failed\n" : "cooldown tests: all passed\n", g_failed);
    return g_failed ? 1 : 0;
}
