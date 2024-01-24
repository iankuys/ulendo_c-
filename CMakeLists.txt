include (FindPkgConfig)

pkg_check_modules (CURLPP REQUIRED curlpp)
target_link_libraries (your_project_name ${CURLPP_LDFLAGS})
find_package(curlpp REQUIRED)
target_link_libraries(your_project_name curlpp::curlpp)
