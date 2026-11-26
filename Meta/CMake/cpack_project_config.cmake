# The archives keep a relocatable layout of Ladybird's components, while the Linux packages install into a fixed
# directory and group the components into the browser package and its debug symbols package.
if (CPACK_GENERATOR MATCHES "^(DEB|RPM)$")
    set(CPACK_PACKAGING_INSTALL_PREFIX "${CPACK_LADYBIRD_PACKAGE_INSTALL_PREFIX}")
    set(CPACK_PACKAGE_RELOCATABLE OFF)
    set(CPACK_COMPONENT_LADYBIRD_RUNTIME_GROUP Browser)
    set(CPACK_COMPONENT_LADYBIRD_SYSTEMINTEGRATION_GROUP Browser)
    set(CPACK_COMPONENT_LADYBIRD_SYSTEMSYMBOLS_GROUP DebugSymbols)
    set(CPACK_PRE_BUILD_SCRIPTS "${CMAKE_CURRENT_LIST_DIR}/cpack_package_format.cmake")
endif()

# 本 fork 的包面向多个发行版（Ubuntu 22.04+ / Debian 12+ / Deepin 25+），
# 因此版本号与文件名里不带发行版标识，统一使用 release 号 1。
if (CPACK_GENERATOR STREQUAL "DEB")
    set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
    set(CPACK_DEBIAN_DEBUGSYMBOLS_PACKAGE_DEPENDS
        "ladybird (= ${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_RELEASE})")
endif()
