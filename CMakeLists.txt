cmake_minimum_required(VERSION 3.16)

project(TPpoo2da VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ClaseEstrategiaIA.cpp ClaseEstrategiaIA.h
    claseiaavanzada.cpp claseiaavanzada.h
    claseiabasica.cpp claseiabasica.h
    claseiaintermedia.cpp claseiaintermedia.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TPpoo2da
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Partida.h Partida.cpp
        MotorCombate.h MotorCombate.cpp
        # CORREGIDO: Eliminar duplicados
        ConfiguracionDanio.h ConfiguracionDanio.cpp
        tipoelemento.h
        carta.h carta.cpp
        jugador.h jugador.cpp
        jugadorhumano.h jugadorhumano.cpp
        jugadoria.h jugadoria.cpp
        cartawidget.h cartawidget.cpp cartawidget.ui
        menuprincipal.h menuprincipal.cpp menuprincipal.ui
        configuracionjuego.h configuracionjuego.cpp
        fabricaia.h fabricaia.cpp
        configuraciondao.h
        configuraciondaofiletxt.h configuraciondaofiletxt.cpp
        partidadao.h
        partidadaofiletxt.h partidadaofiletxt.cpp
    )
else()
    # ... (resto igual)
endif()

target_link_libraries(TPpoo2da PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# config.txt y partidas/ se leen y guardan en la carpeta del proyecto (no en la de build).
target_compile_definitions(TPpoo2da PRIVATE DIRECTORIO_DATOS="${CMAKE_CURRENT_SOURCE_DIR}")

# Auto-chequeo de archivos (usa Qt Core solo para las carpetas). Apagado por defecto para que Qt Creator muestre solo
# TPpoo2da; para usarlo: cmake -DBUILD_TESTS=ON ... y compilar el target test_archivos.
option(BUILD_TESTS "Compilar test_archivos" OFF)

if(BUILD_TESTS)
    add_executable(test_archivos
        test_archivos.cpp
        configuracionjuego.cpp configuraciondaofiletxt.cpp partidadaofiletxt.cpp fabricaia.cpp
        Partida.cpp MotorCombate.cpp ConfiguracionDanio.cpp carta.cpp
        jugador.cpp jugadorhumano.cpp jugadoria.cpp
        claseiabasica.cpp claseiaintermedia.cpp claseiaavanzada.cpp
    )
    target_link_libraries(test_archivos PRIVATE Qt${QT_VERSION_MAJOR}::Core)
endif()

set_target_properties(TPpoo2da PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE  # CORREGIDO: TRUE para evitar conflictos de consola en Windows
)

include(GNUInstallDirs)

install(TARGETS TPpoo2da
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TPpoo2da)
endif()