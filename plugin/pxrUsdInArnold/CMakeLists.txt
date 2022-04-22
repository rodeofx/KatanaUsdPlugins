set(PXR_PACKAGE pxrUsdInArnold)

set(vtKatana_LIBRARY "")
if (NOT ${KATANA_API_VERSION} VERSION_LESS "3.0.0")
    set(vtKatana_LIBRARY "vtKatana")
endif()

pxr_plugin(${PXR_PACKAGE}
    KATANA_PLUGIN
    LIBRARIES
        katanaPluginApi
        usdGeom
        usdKatana
        ${vtKatana_LIBRARY}

    PRIVATE_HEADERS
        declareCoreOps.h

    CPPFILES
        register.cpp
        arnoldGeometryDecorator.cpp
)
