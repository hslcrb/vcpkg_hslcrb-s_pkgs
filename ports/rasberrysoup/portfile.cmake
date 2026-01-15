vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO hslcrb/vcpkg_hslcrb-s_pkgs
    REF v1.0.0
    SHA512 0 # 설치 시도 후 실제 해시값으로 업데이트
    HEAD_REF main
)

set(SOURCE_PATH "${SOURCE_PATH}/Rasberrysoup-src")

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
