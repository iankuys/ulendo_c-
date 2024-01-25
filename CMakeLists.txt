include (FindPkgConfig)

pkg_check_modules (CURLPP REQUIRED curlpp)
target_link_libraries (ulendo_rpi ${CURLPP_LDFLAGS})
find_package(curlpp REQUIRED)
target_link_libraries(ulendo_rpi curlpp::curlpp)
