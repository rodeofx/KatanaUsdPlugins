set(PXR_PACKAGE pxrUsdInRdo)

set(vtKatana_LIBRARY "")
if (NOT ${KATANA_API_VERSION} VERSION_LESS "3.0.0")
    set(vtKatana_LIBRARY "vtKatana")
endif()

pxr_plugin(${PXR_PACKAGE}
    KATANA_PLUGIN
    LIBRARIES
        katanaPluginApi
        usdVol
        usdKatana
        ${vtKatana_LIBRARY}
    
    PRIVATE_HEADERS
        declareCoreOps.h
    
    CPPFILES
        register.cpp
        openVDBAsset.cpp
        volume.cpp
)
