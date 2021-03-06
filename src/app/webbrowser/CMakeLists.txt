project(webbrowser-app)

find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Sql REQUIRED)

include_directories(
    ${CMAKE_BINARY_DIR}
    ${webbrowser-common_SOURCE_DIR}
    ${webbrowser-common_BINARY_DIR}
)

set(WEBBROWSER_APP_MODELS_SRC
    bookmarks-model.cpp
    bookmarks-folder-model.cpp
    bookmarks-folderlist-model.cpp
    downloads-model.cpp
    history-domain-model.cpp
    history-domainlist-model.cpp
    history-lastvisitdatelist-model.cpp
    history-model.cpp
    limit-proxy-model.cpp
    tabs-model.cpp
    text-search-filter-model.cpp
)

set(WEBBROWSER_APP_MODELS webbrowser-app-models)

add_library(${WEBBROWSER_APP_MODELS} STATIC ${WEBBROWSER_APP_MODELS_SRC})
target_link_libraries(${WEBBROWSER_APP_MODELS}
    Qt5::Core
    Qt5::Sql
)

set(WEBBROWSER_APP_SRC
    cache-deleter.cpp
    file-operations.cpp
    reparenter.cpp
    searchengine.cpp
    webbrowser-app.cpp
)

set(WEBBROWSER_APP webbrowser-app)

add_executable(${WEBBROWSER_APP} ${WEBBROWSER_APP_SRC})
target_link_libraries(${WEBBROWSER_APP}
    Qt5::Concurrent
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    ${COMMONLIB}
    ${WEBBROWSER_APP_MODELS}
)

install(TARGETS ${WEBBROWSER_APP}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

file(GLOB QML_FILES *.qml qmldir *.js)
install(FILES ${QML_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/webbrowser-app/webbrowser)

install(DIRECTORY assets
        DESTINATION ${CMAKE_INSTALL_DATADIR}/webbrowser-app/webbrowser
        FILES_MATCHING PATTERN *.png PATTERN *.svg PATTERN *.sci)

install(DIRECTORY searchengines
        DESTINATION ${CMAKE_INSTALL_DATADIR}/webbrowser-app/webbrowser
        FILES_MATCHING PATTERN *.xml)

configure_file(${DESKTOP_FILE}.in.in ${DESKTOP_FILE}.in @ONLY)
add_custom_target(${DESKTOP_FILE} ALL
                  COMMENT "Merging translations into ${DESKTOP_FILE}"
                  COMMAND ${INTLTOOL_MERGE} -d -u ${CMAKE_SOURCE_DIR}/po
                          ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE}.in ${DESKTOP_FILE})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE}
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(FILES "webbrowser-app.url-dispatcher"
        DESTINATION ${CMAKE_INSTALL_DATADIR}/url-dispatcher/urls)

install(FILES "webbrowser-app-content-hub.json"
    DESTINATION ${CMAKE_INSTALL_DATADIR}/content-hub/peers
    RENAME webbrowser-app
    )
