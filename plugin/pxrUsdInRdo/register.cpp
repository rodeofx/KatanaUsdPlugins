#include "pxrUsdInRdo/declareCoreOps.h"

#include "pxr/pxr.h"

#include "pxr/usd/usdVol/volume.h"
#include "pxr/usd/usdVol/openVDBAsset.h"

#include "usdKatana/bootstrap.h"
#include "vtKatana/bootstrap.h"

PXR_NAMESPACE_USING_DIRECTIVE

DEFINE_GEOLIBOP_PLUGIN (PxrUsdInRdo_VolumeOp);
DEFINE_GEOLIBOP_PLUGIN (PxrUsdInRdo_OpenVDBAssetOp);

void registerPlugins() {

    USD_OP_REGISTER_PLUGIN(PxrUsdInRdo_VolumeOp, "PxrUsdInRdo_VolumeOp", 0, 1);
    USD_OP_REGISTER_PLUGIN(PxrUsdInRdo_OpenVDBAssetOp,
            "PxrUsdInRdo_OpenVDBAssetOp", 0, 1);

    PxrUsdKatanaUsdInPluginRegistry::RegisterUsdType<UsdVolVolume>(
            "PxrUsdInRdo_VolumeOp");
    PxrUsdKatanaUsdInPluginRegistry::RegisterUsdType<UsdVolOpenVDBAsset>(
            "PxrUsdInRdo_OpenVDBAssetOp");

    PxrUsdKatanaBootstrap();
    PxrVtKatanaBootstrap();
}
