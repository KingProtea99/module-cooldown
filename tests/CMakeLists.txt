# 모듈 단위 시험 (프로젝트에 복사되지 않는다). 엔진 코어(mealkit_core)에 링크해 혼자 빌드한다:
#   cmake -S tests -B build/tests -G Ninja -DMEALKIT_ROOT=<엔진 폴더> -DMEALKIT_HEADLESS_ONLY=ON
#   cmake --build build/tests && build\tests\bin\cooldown_tests
# 모듈 코드는 프로젝트에서처럼 #include "cooldown/..."로 읽는다 (빌드 폴더에 전달 헤더를 만든다).
cmake_minimum_required(VERSION 3.25)
project(cooldown_tests LANGUAGES CXX)
file(TO_CMAKE_PATH "${MEALKIT_ROOT}" MEALKIT_ROOT)
include(${MEALKIT_ROOT}/cmake/MealKit.cmake)

get_filename_component(module_dir "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
file(GLOB_RECURSE module_headers CONFIGURE_DEPENDS "${module_dir}/sim/*.h" "${module_dir}/view/*.h")
foreach(h IN LISTS module_headers)
    file(RELATIVE_PATH rel "${module_dir}" "${h}")
    file(CONFIGURE OUTPUT "${CMAKE_BINARY_DIR}/inc/cooldown/${rel}" CONTENT "#include \"${h}\"\n" @ONLY)
endforeach()

add_executable(cooldown_tests CooldownTests.cpp)
target_link_libraries(cooldown_tests PRIVATE mealkit_core)
target_include_directories(cooldown_tests PRIVATE "${CMAKE_BINARY_DIR}/inc")
